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

#include "newcwdialog.h"

NewCWDialog::NewCWDialog(QWidget* parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	setWindowModality(Qt::ApplicationModal);
	setWindowTitle(trUtf8("New crossword"));
	
	QLabel* selectTypeLabel = new QLabel(trUtf8("&Select crossword type:"), this);
	typeComboBox = new QComboBox(this);
	typeComboBox->addItem(trUtf8("Classic"), NULL);
	cwType = CWType::ctClassic;
	selectTypeLabel->setBuddy(typeComboBox);
	
	QLabel* widthLabel = new QLabel(trUtf8("Field &width:"), this);
	widthSpinBox = new QSpinBox(this);
	widthSpinBox->setRange(5, 200);
	widthLabel->setBuddy(widthSpinBox);
	
	QLabel* heightLabel = new QLabel(trUtf8("Field &height:"), this);
	heightSpinBox = new QSpinBox(this);
	heightSpinBox->setRange(5, 200);
	heightLabel->setBuddy(heightSpinBox);
	
	QGroupBox* groupBox = new QGroupBox(this);
	QVBoxLayout* vlayout = new QVBoxLayout(groupBox);
	paintRadioButton = new QRadioButton(trUtf8("&Paint the crossword"), groupBox);
	vlayout->addWidget(paintRadioButton);
	paintRadioButton->setChecked(true);
	fillRadioButton = new QRadioButton(trUtf8("&Fill the headers"), groupBox);
	connect(fillRadioButton, SIGNAL(toggled(bool)), SLOT(radioToggled(bool)));
	vlayout->addWidget(fillRadioButton);
	groupBox->setLayout(vlayout);
	
	hdrGroupBox = new QGroupBox(this);
	QGridLayout* hdrLayout = new QGridLayout(hdrGroupBox);
	
	QLabel* leftWidthLabel = new QLabel(trUtf8("&Left header width:"), hdrGroupBox);
	leftWidthSpinBox = new QSpinBox(hdrGroupBox);
	leftWidthSpinBox->setRange(5, 50);
	leftWidthLabel->setBuddy(leftWidthSpinBox);
	
	QLabel* topHeightLabel = new QLabel(trUtf8("&Top header height:"), hdrGroupBox);
	topHeightSpinBox = new QSpinBox(hdrGroupBox);
	topHeightSpinBox->setRange(5, 50);
	topHeightLabel->setBuddy(topHeightSpinBox);
	
	hdrLayout->addWidget(leftWidthLabel,	0, 0, Qt::AlignLeft);
	hdrLayout->addWidget(leftWidthSpinBox,	0, 1, Qt::AlignRight);
	hdrLayout->addWidget(topHeightLabel,	1, 0, Qt::AlignLeft);
	hdrLayout->addWidget(topHeightSpinBox,	1, 1, Qt::AlignRight);
	hdrGroupBox->setLayout(hdrLayout);
	hdrGroupBox->setEnabled(false);
	
	QPushButton* okButton = new QPushButton(trUtf8("&OK"), this);
	connect(okButton, SIGNAL(clicked()), SLOT(accept()));
	QPushButton* cancelButton = new QPushButton(trUtf8("&Cancel"), this);
	connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
	
	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(selectTypeLabel,	0, 0, Qt::AlignLeft);
	layout->addWidget(typeComboBox,		0, 1, Qt::AlignRight);
	layout->addWidget(widthLabel,		1, 0, Qt::AlignLeft);
	layout->addWidget(widthSpinBox,		1, 1, Qt::AlignRight);
	layout->addWidget(heightLabel,		2, 0, Qt::AlignLeft);
	layout->addWidget(heightSpinBox,	2, 1, Qt::AlignRight);
	layout->addWidget(groupBox,			3, 0, 1, 2);
	layout->addWidget(hdrGroupBox,		4, 0, 1, 2);
	layout->addWidget(okButton,			5, 0, Qt::AlignHCenter);
	layout->addWidget(cancelButton,		5, 1, Qt::AlignHCenter);
	setLayout(layout);
}

void NewCWDialog::radioToggled(bool checked)
{
	hdrGroupBox->setEnabled(checked);
}

CWType::CrosswordType NewCWDialog::getCWType()
{
	return cwType;
}

quint16 NewCWDialog::getCWWidth()
{
	return widthSpinBox->value();
}

quint16 NewCWDialog::getCWHeight()
{
	return heightSpinBox->value();
}

quint16 NewCWDialog::getLWidth()
{
	return leftWidthSpinBox->value();
}

quint16 NewCWDialog::getTHeight()
{
	return topHeightSpinBox->value();
}
