#include "fieldcheckerthread.h"

FieldCheckerThread::FieldCheckerThread(QWidget* parent)
	: QThread(parent)
{
	//qDebug() << "constructor";
	cwType = ctNone;
	fw = fh = th = lw = 0;
	crossword = NULL;
}

/*FieldCheckerThread::~FieldCheckerThread()
{
	qDebug() << "destructor";
}
*/
void FieldCheckerThread::run()
{
	//for (int i=0;i<200000000;i++);
	//qDebug() << "yo!";
	//exec();
	//check();
}

void FieldCheckerThread::check(quint16 fX, quint16 fY)
{
	/*		так как я ничё лучше не придумал, то проверка осуществляется следующим образом:
			изменённая строка и столбец преобразуются в текстовый эквивалент, потом
			составляется регэксп по соответствующим заголовкам, строки проверяются по
			этим регэкспам. странно оно, конечно, работает :))))
			у кого будут мысли получше - пишите		*/
	//qDebug() << "check";
	if (cwType == ctClassic)
	{
		ClassicCW::CellState** field = ((ClassicCW*) crossword)->getField();
		qint16** thdr = ((ClassicCW*) crossword)->getThdr();
		qint16** lhdr = ((ClassicCW*) crossword)->getLhdr();
		
		/*		преобразовываем строку поля в текст		*/
		QString row(fw, '_');
		quint16 i;
		for (i = 0; i < fw; i++)
			row[i] = (quint8)field[i][fY];
		//qDebug() << row;
		/*		нужно составить паттерн регэкспа для проверки		*/
		QString rowPattern("^[_.]*");		// <- это только начало :)
		for (i = 0; i < lw; i++)
		{
			quint16 num = qAbs(lhdr[lw - i - 1][fY]);
			//qDebug() << num;
			if (num == 0)					// останавливаемся на нуле
				break;
			if (i != 0)						// каждый раз, кроме первого, добавляем разделитель блоков
				rowPattern.append("[_.]+");
			if (num == 1)					// если число == 1, то добавляем * с повтором 1 раз
				rowPattern.append("\\*?");
			else							// иначе добавляем * с повтором 1...num раз
				rowPattern.append(QString("\\*{0,%1}").arg(num));
		}
		rowPattern.append("[_.]*$");		// <- конец регэкспа
		//qDebug() << pattern;
		
		/*		преобразовываем столбец поля в текст		*/
		QString col(fh, '_');
		for (i = 0; i < fh; i++)
			col[i] = (quint8)field[fX][i];
		//qDebug() << col;
		
		QString colPattern("^[_.]*");
		for (i = 0; i < th; i++)
		{
			quint16 num = qAbs(thdr[fX][i]);
			if (num == 0)
				break;
			if (i != 0)
				colPattern.append("[_.]+");
			if (num == 1)
				colPattern.append("\\*?");
			else
				colPattern.append(QString("\\*{0,%1}").arg(num));
		}
		colPattern.append("[_.]*$");		// <- конец регэкспа
		//qDebug() << colPattern;
		
		emit resultTextChanged(QString("row #%1: %2; col #%3: %4").arg(fY + 1).
				arg(row.contains(QRegExp(rowPattern)) ? "ok" : "blah-blah-blah").arg(fX + 1).
				arg(col.contains(QRegExp(colPattern)) ? "ok" : "blah-blah-blah"));
	}
}

void FieldCheckerThread::setCrossword(AbstractCrossword* crossword, CrosswordType cwType)
{
	//qDebug() << crossword->getName();
	this->crossword = crossword;
	this->cwType = cwType;
	//cwType = ctClassic;
	connect(crossword, SIGNAL(cellStateChanged(quint16, quint16)), this, SLOT(check(quint16, quint16)));
	((RectCrossword*) crossword)->sizes(&fw, &fh, &th, &lw);
}
