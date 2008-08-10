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

#ifndef NEWCWDIALOG_H
#define NEWCWDIALOG_H

#include <QtGui>
#include "cwtype.h"

class NewCWDialog : public QDialog
{
Q_OBJECT
	
public:
	NewCWDialog(QWidget* parent = NULL, Qt::WindowFlags flags =
			Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	CWType::CrosswordType getCWType();
	quint16 getCWWidth();
	quint16 getCWHeight();
	quint16 getLWidth();
	quint16 getTHeight();
	
protected:
	QComboBox*				typeComboBox;
	QSpinBox*				widthSpinBox;
	QSpinBox*				heightSpinBox;
	QRadioButton*			paintRadioButton;
	QRadioButton*			fillRadioButton;
	QGroupBox*				hdrGroupBox;
	QSpinBox*				leftWidthSpinBox;
	QSpinBox*				topHeightSpinBox;
	CWType::CrosswordType	cwType;
	
	
protected slots:
	void radioToggled(bool checked);
};

#endif
