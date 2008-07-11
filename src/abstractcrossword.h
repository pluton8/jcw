#ifndef ABSTRACTCROSSWORD_H
#define ABSTRACTCROSSWORD_H

#include <QtGui>
#include "crosswordinfo.h"

class AbstractCrossword : public QWidget//QGraphicsView//
{
Q_OBJECT

public:
    AbstractCrossword(QWidget* parent = 0, Qt::WindowFlags f = 0);
	//enum CellState { csUndef = 0 };			// возможные состояния клеток
	bool isNeedDelete() const;
	void showInfo();
	
protected:
	quint16			cellSize;					// размер клетки, пикселей
	quint16			margin;						// отступ от края виджета
	bool			needDelete;					// ставим флаг при ошибке в конструкторе
	QString			name;						// название кроссворда
	QString			author;						// автор
	QString			date;						// дата создания
	QString			comment;					// юзерский коммент
	CrosswordInfo*	ciDialog;
	static const quint16 MIN_CELLSIZE = 10;		// минимальный размер клетки
	//virtual void paintEvent(QPaintEvent* event);
	
/*protected slots:
	void ciDialogDestroyed();*/
};

#endif
