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

#include "rectcrossword.h"

RectCrossword::RectCrossword(QTime* time, QWidget* parent, Qt::WindowFlags f)
	: AbstractCrossword(time, parent, f)
{
	fw = fh = th = lw = 0;
	thdr = lhdr = NULL;
	rowsRes = colsRes = NULL;
}

void RectCrossword::sizes(quint16* fw, quint16* fh, quint16* th, quint16* lw)
{
	if (fw != NULL)
		*fw = this->fw;
	if (fh != NULL)
		*fh = this->fh;
	if (th != NULL)
		*th = this->th;
	if (lw != NULL)
		*lw = this->lw;
}

qint16** RectCrossword::getThdr()
{
	return thdr;
}

qint16** RectCrossword::getLhdr()
{
	return lhdr;
}

QBitArray* RectCrossword::getRowsRes()
{
	return rowsRes;
}

QBitArray* RectCrossword::getColsRes()
{
	return colsRes;
}
