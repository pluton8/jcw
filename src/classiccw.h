#ifndef CLASSICCW_H
#define CLASSICCW_H

#include <QtGui>
#include <QtXml>
#include "rectcrossword.h"

class ClassicCW : public RectCrossword
{
Q_OBJECT
	
public:
	ClassicCW(const QDomElement& root, QWidget* parent = NULL, Qt::WindowFlags f = 0);
	~ClassicCW();
	enum CellState { csUndef = 0, csEmpty, csFilled };		// состояния клеток
	
protected:
	CellState**	field;			// поле
	quint16		fX;				// текущая выделенная
	quint16		fY;				// клетка
	quint16		oldFX;			// предыдущая выделенная
	quint16		oldFY;			// клетка
	
	void paintEvent(QPaintEvent* event);				// метод рисования
	void wheelEvent(QWheelEvent* event);				// скроллинг
	void mouseMoveEvent(QMouseEvent* event);			// движение мыши
	void mousePressEvent(QMouseEvent* event);			// клик мыши
	void keyPressEvent(QKeyEvent* event);				// нажатие клавиши клавиатуры
	
	bool calcHighlightXY(const QPoint& originPoint);	// вычисляет координаты выделенной клетки
				// возвращает true, если было изменение
};

#endif
