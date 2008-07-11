#ifndef RECTCROSSWORD_H
#define RECTCROSSWORD_H

#include <QtGui>
#include "abstractcrossword.h"

class RectCrossword : public AbstractCrossword
{
Q_OBJECT

public:
	RectCrossword(QWidget* parent = NULL, Qt::WindowFlags f = 0);
	//enum CellState { csUndef = 0 };			// возможные состояния клеток
	
protected:
	//CellState** field;			// поле
	qint16**	thdr;				// заголовок сверху
	qint16**	lhdr;				// заголовок слева
	quint16		fw;					// ширина поля, штук клеток
	quint16		fh;					// высота поля, штук клеток
	quint16		th;					// высота верхнего заголовка, штук клеток
	quint16		lw;					// ширина левого заголовка, штук клеток
};

#endif
