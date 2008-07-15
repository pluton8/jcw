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

#ifndef ABSTRACTCROSSWORD_H
#define ABSTRACTCROSSWORD_H

#include <QtGui>
#include "crosswordinfo.h"

class AbstractCrossword : public QWidget
{
Q_OBJECT

public:
    AbstractCrossword(QWidget* parent = 0, Qt::WindowFlags f = 0);
	//enum CellState { csUndef = 0 };			// возможные состояния клеток
	bool isNeedDelete() const;					// возвращает флаг ошибки
	QString getName() const;					// возвращает название кроссворда
	quint16 getNumCorrections();
	
public slots:
	void showInfo();							// показ диалога с инфой
	virtual void clearField();					// очистка поля
	
protected:
	quint16			cellSize;					// размер клетки, пикселей
	quint16			margin;						// отступ от края виджета
	bool			needDelete;					// ставим флаг при ошибке в конструкторе
	QString			name;						// название кроссворда
	QString			author;						// автор
	QString			date;						// дата создания
	QString			comment;					// юзерский коммент
	CrosswordInfo*	ciDialog;					// указатель на диалог инфо
	quint16			numCorrections;				// количество исправлений при решении
	static const quint16 MIN_CELLSIZE = 10;		// минимальный размер клетки
	
signals:
	void cellStateChanged(quint16, quint16);
};

#endif
