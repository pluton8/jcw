/**********************************************************************************
 *  jcw - this is a environment for solving japan crosswords by users on computer *
 *  Copyright (C) 2008 by pluton <plutonpluton@mail.ru>                           *
 *                                                                                *
 *  This program is free software; you can redistribute it and/or modify          *
 *  it under the terms of the GNU General Public License as published by          *
 *  the Free Software Foundation; either version 2 of the License, or             *
 *  (at your option) any later version.                                           *
 *                                                                                *
 *  This program is distributed in the hope that it will be useful,               *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
 *  GNU General Public License for more details.                                  *
 *                                                                                *
 *  You should have received a copy of the GNU General Public License along       *
 *  with this program; if not, write to the Free Software Foundation, Inc.,       *
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.                   *
 *********************************************************************************/

#ifndef CLASSICCW_H
#define CLASSICCW_H

#include <QtGui>
#include <QtXml>
#include "rectcrossword.h"

class ClassicCW : public RectCrossword
{
Q_OBJECT
	
public:
	ClassicCW(const QDomElement& root, QTime* time, QWidget* parent = NULL, Qt::WindowFlags f = 0);
	~ClassicCW();
	enum CellState { csUndef = 0, csEmpty, csFilled };		// состояния клеток
	CellState** getField();
	void save(QFile* file);
	void updatePixmap();
	
protected:
	CellState**	field;				// поле
	quint16		fX;					// текущая выделенная
	quint16		fY;					//		клетка
	quint16		oldFX;				// предыдущая выделенная
	quint16		oldFY;				//		клетка
	bool		keyFillPressed;		// флаг, показывающий зажата ли кнопка закрашивания
	bool		keyEmptyPressed;
	bool		keyUndefPressed;
	
	void paintEvent(QPaintEvent* event);				// метод рисования
	void wheelEvent(QWheelEvent* event);				// скроллинг
	void mouseMoveEvent(QMouseEvent* event);			// движение мыши
	void mousePressEvent(QMouseEvent* event);			// клик мыши
	void keyPressEvent(QKeyEvent* event);				// нажатие клавиши клавиатуры
	void keyReleaseEvent(QKeyEvent* event);
	
	bool calcHighlightXY(const QPoint& originPoint);	// вычисляет координаты выделенной клетки
														// возвращает true, если было изменение
	void changeCellState(CellState newState);			// изменяет состояние клетки (fX;fY) на newState
	void clearField();									// очистка поля
	void updateProgress();								// обновить прогресс (после загрузки файла)
};

#endif
