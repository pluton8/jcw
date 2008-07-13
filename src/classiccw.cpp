#include "classiccw.h"

// макрос, устанавливающий флаг ошибки
#define setDeleting \
	{ \
		needDelete = true; \
		return; \
	}

// проверка флага ok
#define checkOk \
	if (!ok) \
		setDeleting;

ClassicCW::ClassicCW(const QDomElement& root, QWidget* parent, Qt::WindowFlags f)
	: RectCrossword(parent, f)
{
	QDomElement domElem = root.toElement();
	bool ok;
	fw = domElem.attribute("width").toUInt(&ok);
	checkOk;
	fh = domElem.attribute("height").toUInt(&ok);
	checkOk;
	name = domElem.attribute("name");
	author = domElem.attribute("author");
	date = domElem.attribute("date");
	//comment = domElem.attribute("comment");
	quint16 i;
	quint16 j;
	field = new CellState* [fw];		// создание двумерного динамического массива
	bzero(field, fw * sizeof(CellState*));
	for (i = 0; i < fw; i++)
	{
		field[i] = new CellState[fh];
		bzero(field[i], fh * sizeof(CellState));
	}
	
	QStringList list;
	QStringList list2;
	QDomNodeList nodes = root.elementsByTagName("topheader");
	if (!nodes.isEmpty())
	{
		domElem = nodes.item(0).toElement();
		if (!domElem.isNull())
		{
			th = domElem.attribute("height").toUInt(&ok);
			checkOk;
			list = domElem.text().split(';', QString::SkipEmptyParts);
			if (list.size() != fw)
				setDeleting;
			thdr = new qint16* [fw];
			bzero(thdr, fw * sizeof(qint16*));
			for (i = 0; i < fw; i++)
			{
				thdr[i] = new qint16[th];
				bzero(thdr[i], th * sizeof(qint16));
				list2 = list.at(i).split(',', QString::SkipEmptyParts);
				for (j = 0; j < list2.size(); j++)
				{
					thdr[i][j] = list2.at(j).toInt(&ok);
					checkOk;
				}
			}
		}
	}
	else
		setDeleting;
	
	nodes = root.elementsByTagName("leftheader");
	if (!nodes.isEmpty())
	{
		domElem = nodes.item(0).toElement();
		if (!domElem.isNull())
		{
			lw = domElem.attribute("width").toUInt(&ok);
			checkOk;
			list = domElem.text().split(';', QString::SkipEmptyParts);
			if (list.size() != fh)
				setDeleting;
			lhdr = new qint16* [lw];
			bzero(lhdr, lw * sizeof(qint16*));
			for (i = 0; i < lw; i++)
			{
				lhdr[i] = new qint16[fh];
				bzero(lhdr[i], fh * sizeof(qint16));
			}
			for (i = 0; i < fh; i++)
			{
				list2 = list.at(i).split(',', QString::SkipEmptyParts);
				//qDebug() << list2;
				for (j = 0; j < list2.size(); j++)
				{
					lhdr[lw - j - 1][i] = list2.at(j).toInt(&ok);
					checkOk;
				}
			}
		}
	}
	else
		setDeleting;
	
	nodes = root.elementsByTagName("field");
	if (!nodes.isEmpty())
	{
		domElem = nodes.item(0).toElement();
		if (!domElem.isNull())
		{
			nodes = domElem.elementsByTagName("cell");
			for (i = 0; i < nodes.length(); i++)
			{
				quint16 x = nodes.item(i).toElement().attribute("col").toUInt(&ok);
				checkOk;
				quint16 y = nodes.item(i).toElement().attribute("row").toUInt(&ok);
				checkOk;
				field[x][y] = nodes.item(i).toElement().attribute("state") == "filled" ? csFilled : csEmpty;
			}
		}
	}
	
	nodes = root.elementsByTagName("comment");
	if (!nodes.isEmpty())
	{
		domElem = nodes.item(0).toElement();
		if (!domElem.isNull())
			comment = domElem.text();
	}
	
	keyFillPressed = false;
	keyEmptyPressed = false;
	keyUndefPressed = false;
	fX = oldFX = lw;
	fY = oldFY = th;
	setMouseTracking(true);				// включаем отслеживание движения мыши
	setFocusPolicy(Qt::StrongFocus);
	/*show();
	setFocus(Qt::TabFocusReason);		// <<< не работает
	qDebug() << qApp->focusWidget();*/
}

ClassicCW::~ClassicCW()
{
	// ^^^ надо бы удалить всё, что мы тама создали
	quint16 i;
	if (lhdr != NULL)
	{
		for (i = 0; i < lw; i++)
			if (lhdr[i] != NULL)
				delete[] lhdr[i];
		delete[] lhdr;
	}
	if (thdr != NULL)
	{
		for (i = 0; i < fw; i++)
			if (thdr[i] != NULL)
				delete[] thdr[i];
		delete[] thdr;
	}
	if (field != NULL)
	{
		for (i = 0; i < fw; i++)
			if (field[i] != NULL)
				delete[] field[i];
		delete[] field;
	}
}

void ClassicCW::paintEvent(QPaintEvent* /*event*/)
{
	QPainter painter(this);			// объект QPainter для рисования
	
	QSize fieldSize((margin * 2) + (cellSize * (lw + fw)), (margin * 2) + (cellSize * (th + fh)));
	QSize parentSize = parentWidget()->size();
	resize(fieldSize.expandedTo(parentSize));
	QPen penNormal = painter.pen();			// перо рисования границ
	penNormal.setWidth(1);
	QPen penBold = painter.pen();			// перо рисования жирных границ
	penBold.setWidth(2);
	QFont font = painter.font();
	font.setPointSize(cellSize * 0.7);		// установка размера фонта в зависимости от размера клетки
	painter.setFont(font);
	quint16 i;
	quint16 j;
	quint16 pointX = margin + lw * cellSize;	// координаты начальной точки поля
	quint16 pointY = margin + th * cellSize;
	
	/*		рисуем линии поля и цфиры		*/
	quint16 bottomY = (fh + th) * cellSize;	// нижняя координата Y верхнего заголовка
	quint16 rigthX = fw * cellSize;			// правая координата X верхнего заголовка
	painter.save();
	painter.translate(pointX, margin);
	for (i = 0; i <= fw; i++)				// рисуем вертикальные линии
		if (i % 5 == 0 || i == fw)			// каждую 5 границу рисуем жирнее
		{
			painter.setPen(penBold);
			painter.drawLine(i * cellSize, 0, i * cellSize, bottomY);
			painter.setPen(penNormal);
		}
		else
			painter.drawLine(i * cellSize, 0, i * cellSize, bottomY);
	
	painter.setPen(penBold);
	painter.drawLine(0, 0, rigthX, 0);
	painter.setPen(penNormal);
	for (i = 1; i < th; i++)				// рисуем горизонтальные линии
		painter.drawLine(0, i * cellSize, rigthX, i * cellSize);
	
	for (i = 0; i < fw; i++)
		for (j = 0; j < th; j++)
			if (thdr[i][j] != 0)
			{
				painter.drawText(i * cellSize, (th - j - 1) * cellSize, cellSize, cellSize,
						Qt::AlignCenter, QString::number(qAbs(thdr[i][j])));
				if (thdr[i][j] < 0)
					painter.drawLine((i + 1) * cellSize, (th - j - 1) * cellSize, 
							i * cellSize, (th - j) * cellSize);
			}
	
	painter.restore();
	
	bottomY = fh * cellSize;
	rigthX = (fw + lw) * cellSize;
	painter.save();
	painter.translate(margin, pointY);
	for (i = 0; i <= fh; i++)				// рисуем горизонтальные линии
		if (i % 5 == 0 || i == fh)			// каждую 5 границу рисуем жирнее
		{
			painter.setPen(penBold);
			painter.drawLine(0, i * cellSize, rigthX, i * cellSize);
			painter.setPen(penNormal);
		}
		else
			painter.drawLine(0, i * cellSize, rigthX, i * cellSize);
	
	painter.setPen(penBold);
	painter.drawLine(0, 0, 0, bottomY);
	painter.setPen(penNormal);
	for (i = 1; i < lw; i++)				// рисуем вертикальные линии
		painter.drawLine(i * cellSize, 0, i * cellSize, bottomY);
	
	for (i = 0; i < fh; i++)
		for (j = 0; j < lw; j++)
			if (lhdr[j][i] != 0)
			{
				painter.drawText(j * cellSize, i * cellSize, cellSize, cellSize,
						Qt::AlignCenter, QString::number(qAbs(lhdr[j][i])));
				if (lhdr[j][i] < 0)
					painter.drawLine((j + 1) * cellSize, i * cellSize,
							j * cellSize, (i + 1) * cellSize);
			}
	
	painter.restore();
	
	painter.save();
	painter.translate(pointX, pointY);
	painter.setBrush(Qt::SolidPattern);
	int pointRadius = cellSize * 0.1;
	for (i = 0; i < fw; i++)
		for (j = 0; j < fh; j++)
			switch (field[i][j])
			{
				case csFilled:
					painter.drawRect(i * cellSize, j * cellSize, cellSize, cellSize);
					break;
				case csEmpty:
					painter.drawEllipse((i + 0.5) * cellSize - pointRadius, (j + 0.5) * cellSize -
							pointRadius, pointRadius * 2, pointRadius * 2);
					break;
				/*case csUndef:
					break;*/
			}
	painter.restore();
	
	/*		рисуем размеры поля		*/
	font.setPointSize(cellSize * 1.2);
	painter.setFont(font);
	painter.drawText(margin, margin, lw * cellSize, th * cellSize, Qt::AlignCenter,
			QString("%1x%2").arg(fw).arg(fh));
	
	painter.setPen(Qt::red);
	painter.drawRect(margin + fX * cellSize, margin + fY * cellSize, cellSize, cellSize);
	
	if (hasFocus())
	{
		QStyleOptionFocusRect option;
		option.initFrom(this);
		//option.backgroundColor = palette().light().color();
		style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, &painter, this);
	}
}

bool ClassicCW::calcHighlightXY(const QPoint& originPoint)
{
	bool changed = false;
	fX = (originPoint.x() - margin) / cellSize;					// координата клетки
	fY = (originPoint.y() - margin) / cellSize;					// на поле
	if ((fX < lw && fY < th) || (fX >= fw + lw) || (fY >= fh + th))
		//если выделенная клетка не находится в области поля или заголовков, восстанавливаем предыдущее значение
	{
		fX = oldFX;
		fY = oldFY;
	}
	else if (fX != oldFX || fY != oldFY)
	{
		changed = true;
		update();
		oldFX = fX;
		oldFY = fY;
	}
	return changed;
}

void ClassicCW::mouseMoveEvent(QMouseEvent* event)
{
	if (calcHighlightXY(event->pos()))
	{
		Qt::MouseButton button = Qt::NoButton;
		if (event->buttons().testFlag(Qt::LeftButton))			// если двигаем мышу, и
			button =  Qt::LeftButton;
		else if (event->buttons().testFlag(Qt::RightButton))	// нажата одна из кнопок
			button =  Qt::RightButton;
		else if (event->buttons().testFlag(Qt::MidButton))		// то генерим событие
			button =  Qt::MidButton;
		if (button != Qt::NoButton)								// нажатия кнопки
		{
			QMouseEvent* mouseEvent = new QMouseEvent(QEvent::MouseButtonPress, event->pos(),
					button, event->buttons(), event->modifiers());
			mousePressEvent(mouseEvent);
		}
	}
	event->accept();
}

void ClassicCW::mousePressEvent(QMouseEvent* event)
{
	calcHighlightXY(event->pos());
	CellState newState;
	switch (event->button())
	{
		case Qt::LeftButton:
			newState = csFilled;
			break;
		case Qt::MidButton:
			newState = csUndef;
			break;
		case Qt::RightButton:
			newState = csEmpty;
			break;
	}
	changeCellState(newState);
	event->accept();
	update();
}

void ClassicCW::wheelEvent(QWheelEvent* event)
{
	if (event->modifiers().testFlag(Qt::ControlModifier))
	{									// если нажат Ctrl, то изменяем размер клетки
		quint16 d = qAbs(event->delta() / 120);
		if (event->delta() > 0)			// скроллинг вверх
			cellSize += d;
		else
			if (cellSize + d > MIN_CELLSIZE)
				cellSize -= d;
	}
	else if (event->modifiers().testFlag(Qt::ShiftModifier))
	{									// если нажат Shift, то включаем горизонтальный скроллинг
		QWheelEvent* ev = new QWheelEvent(event->pos(), event->delta(), event->buttons(),
				event->modifiers(), Qt::Horizontal);
		qApp->postEvent(parentWidget(), ev);
	}
	else
	{
		event->setAccepted(false);
		return;
	}
	update();
	calcHighlightXY(event->pos());
	event->setAccepted(true);
	return;
}

#define checkPressedKeys \
		if (keyFillPressed) \
			changeCellState(csFilled); \
		else if (keyEmptyPressed) \
			changeCellState(csEmpty); \
		else if (keyUndefPressed) \
			changeCellState(csUndef);


void ClassicCW::keyPressEvent(QKeyEvent* event)
{
	//qDebug() << QString::number(event->key(), 16);
	switch (event->key())
	{
		case Qt::Key_Up:
			if (fY > th || (fX > lw - 1 && fY > 0))
			{
				fY--;
				checkPressedKeys;
			}
			break;
		case Qt::Key_Down:
			if (fY < fh + th - 1)
			{
				fY++;
				checkPressedKeys;
			}
			break;
		case Qt::Key_Left:
			if (fX > lw || (fY > th - 1 && fX > 0))
			{
				fX--;
				checkPressedKeys;
			}
			break;
		case Qt::Key_Right:
			if (fX < fw + lw - 1)
			{
				fX++;
				checkPressedKeys;
			}
			break;
		case Qt::Key_Z:									// Z -> закрашено
			changeCellState(csFilled);
			keyFillPressed = true;
			break;
		case Qt::Key_X:									// X -> пусто
			changeCellState(csEmpty);
			keyEmptyPressed = true;
			break;
		case Qt::Key_C:									// C -> неизвестно
			changeCellState(csUndef);
			keyUndefPressed = true;
			break;
		case Qt::Key_Plus:								// + -> увеличить размер клетки
			cellSize++;
			break;
		case Qt::Key_Minus:								// - -> уменьшить размер клетки
			if (cellSize > MIN_CELLSIZE)
				cellSize--;
			break;
		default:
			QWidget::keyPressEvent(event);
			return;
	}
	update();
}

void ClassicCW::keyReleaseEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Z:
			keyFillPressed = false;
			break;
		case Qt::Key_X:
			keyEmptyPressed = false;
			break;
		case Qt::Key_C:
			keyUndefPressed = false;
			break;
		default:
			QWidget::keyReleaseEvent(event);
			return;
	}
}

void ClassicCW::changeCellState(CellState newState)
{
	quint16 fieldX = fX - lw;
	quint16 fieldY = fY - th;
	if (fX >= lw && fX < fw + lw && fY >= th && fY < th + fh)	// если попали на поле
		field[fieldX][fieldY] = newState;
	else if (fX < lw && fY >= th && fY < fh + th)	// если попали в левый заголовок
		lhdr[fX][fieldY] *= -1;
		/*field[fX][fieldY] *= -1;
		src/classiccw.cpp:266: error: no match for 'operator*=' in '*((*(((ClassicCW*)this)->ClassicCW::field + ((ClassicCW::CellState**)(((unsigned int)((ClassicCW*)this)->ClassicCW::fX) * 4u)))) + ((ClassicCW::CellState*)(((unsigned int)fieldY) * 4u))) *= -0x000000000000001'
		^^^^^ фигасе ошибка
		*/
	else if (fX >= lw && fX < lw + fw && fY < th)	// если попали в верхний заголовок
		thdr[fieldX][th - fY - 1] *= -1;
	
	// надо запустить чекалку поля
	emit cellStateChanged();
}

void ClassicCW::clearField()
{
	quint16 i;
	quint16 j;
	for (i = 0; i < fw; i++)
	{
		for (j = 0; j < fh; j++)
			field[i][j] = csUndef;
		for (j = 0; j < th; j++)
			thdr[i][j] = qAbs(thdr[i][j]);
	}
	for (i = 0; i < lw; i++)
		for (j = 0; j < fh; j++)
			lhdr[i][j] = qAbs(lhdr[i][j]);
	update();
}

ClassicCW::CellState** ClassicCW::getField()
{
	return field;
}
