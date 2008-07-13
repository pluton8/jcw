#ifndef RECTCROSSWORD_H
#define RECTCROSSWORD_H

#include <QtGui>
#include "abstractcrossword.h"

//class AbstractCrossword;

class RectCrossword : public AbstractCrossword
{
Q_OBJECT

public:
	RectCrossword(QWidget* parent = NULL, Qt::WindowFlags f = 0);
	//enum CellState { csUndef = 0 };			// возможные состояния клеток
	void sizes(quint16* fw, quint16* fh, quint16* th, quint16* lw);		// возвращает размеры
	qint16** getThdr();
	qint16** getLhdr();
	
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
