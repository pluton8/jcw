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

#include "abstractcrossword.h"

AbstractCrossword::AbstractCrossword(QWidget* parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	cellSize = 20;
	margin = 20;
	needDelete = isSolved = false;
	ciDialog = NULL;
	numCorrections = 0;
}

bool AbstractCrossword::isNeedDelete() const
{
	return needDelete;
}

void AbstractCrossword::showInfo()
{
	if (ciDialog == NULL)
		ciDialog = new CrosswordInfo(name, author, date, comment, this);
	ciDialog->show();
}

QString AbstractCrossword::getName() const
{
	return name;
}

void AbstractCrossword::clearField()
{
}

quint16 AbstractCrossword::getNumCorrections()
{
	return numCorrections;
}

void AbstractCrossword::solved()
{
	isSolved = true;
}

void AbstractCrossword::save(QFile*/* file*/)
{
}
