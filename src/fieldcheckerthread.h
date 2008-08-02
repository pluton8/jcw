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

#ifndef FIELDCHECKERTHREAD_H
#define FIELDCHECKERTHREAD_H

#include <QtGui>
#include "classiccw.h"

//class ClassicCW;

class FieldCheckerThread : public QThread
{
Q_OBJECT
	
public:
	FieldCheckerThread(QWidget* parent = NULL);
	//~FieldCheckerThread();
	void run();
	enum CrosswordType { ctNone, ctClassic };
	void setCrossword(AbstractCrossword* crossword, CrosswordType cwType);
	
public slots:
	void check(quint16 fX, quint16 fY);
	
protected:
	AbstractCrossword*		crossword;
	CrosswordType			cwType;
	ClassicCW::CellState**	field;
	QBitArray*				rowsRes;
	QBitArray*				colsRes;
	quint16					fw;
	quint16					fh;
	quint16					th;
	quint16					lw;
	qint16**				thdr;
	qint16**				lhdr;
	void updateProgress();
	
signals:
	void solved();
	void resultTextChanged(QString);
	void progressChanged(int);
};

#endif
