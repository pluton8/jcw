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

#ifndef CROSSWORDINFODIALOG_H
#define CROSSWORDINFODIALOG_H

#include <QtGui>

class CrosswordInfoDialog : public QDialog
{
Q_OBJECT
	
public:
	CrosswordInfoDialog(const QString& name = QString(), const QString& author = QString(),
			const QString& date = QString(), const QString& comment = QString(),
			QWidget* parent = NULL, Qt::WindowFlags f = Qt::Dialog);
	
protected:
	QLineEdit*		nameLineEdit;
	QLineEdit*		authorLineEdit;
	QLineEdit*		dateLineEdit;
	QTextEdit*		commentTextEdit;
	
};

#endif
