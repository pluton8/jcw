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
	QBitArray* getRowsRes();
	QBitArray* getColsRes();
	
protected:
	//CellState** field;			// поле
	qint16**	thdr;				// заголовок сверху
	qint16**	lhdr;				// заголовок слева
	QBitArray*	rowsRes;			// массив битов для хранения результатов правильности
	QBitArray*	colsRes;			//    решения строки/столбца
	quint16		fw;					// ширина поля, штук клеток
	quint16		fh;					// высота поля, штук клеток
	quint16		th;					// высота верхнего заголовка, штук клеток
	quint16		lw;					// ширина левого заголовка, штук клеток
};

#endif
