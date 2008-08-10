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

#include "crosswordinfodialog.h"

CrosswordInfoDialog::CrosswordInfoDialog(const QString& name, const QString& author,
		const QString& date, const QString& comment, QWidget* parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	nameLineEdit = new QLineEdit(name, this);
	nameLineEdit->setReadOnly(true);
	nameLineEdit->setMinimumWidth(120);
	QLabel* nameLabel = new QLabel(trUtf8("&Name:"), this);
	nameLabel->setBuddy(nameLineEdit);
	
	authorLineEdit = new QLineEdit(author, this);
	authorLineEdit->setReadOnly(true);
	QLabel* authorLabel = new QLabel(trUtf8("&Author:"), this);
	authorLabel->setBuddy(authorLineEdit);
	
	dateLineEdit = new QLineEdit(date, this);
	dateLineEdit->setReadOnly(true);
	QLabel* dateLabel = new QLabel(trUtf8("&Date:"), this);
	dateLabel->setBuddy(dateLineEdit);
	
	commentTextEdit = new QTextEdit(comment, this);
	commentTextEdit->setReadOnly(true);
	commentTextEdit->setMinimumHeight(50);
	QLabel* commentLabel = new QLabel(trUtf8("&Comment:"), this);
	commentLabel->setBuddy(commentTextEdit);
	
	QPushButton* okPushButton = new QPushButton(trUtf8("&OK"), this);
	connect(okPushButton, SIGNAL(clicked()), this, SLOT(close()));
	
	QGridLayout* gridLayout = new QGridLayout(this);
	gridLayout->addWidget(nameLabel,		0, 0);
	gridLayout->addWidget(nameLineEdit,		0, 1);
	gridLayout->addWidget(authorLabel,		1, 0);
	gridLayout->addWidget(authorLineEdit,	1, 1);
	gridLayout->addWidget(dateLabel,		2, 0);
	gridLayout->addWidget(dateLineEdit,		2, 1);
	gridLayout->addWidget(commentLabel,		3, 0);
	gridLayout->addWidget(commentTextEdit,	4, 0, 1, 2);
	gridLayout->addWidget(okPushButton,		5, 0, 1, 2, Qt::AlignHCenter);
	setLayout(gridLayout);
	
	setWindowTitle(trUtf8("Crossword info"));
}
