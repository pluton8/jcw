/****************************
Проект:		Project:	jcw
Автор:		Author:		pluton
Связь:		JabberID:	j8@jabber.ru
			E-mail:		plutonpluton@mail.ru
Лицензия:	License:	GPL (see ../LICENSE file)
Дата:		Date:		07.2008+
Сайт:		Site:		http://sourceforge.net/projects/jcw/
****************************/

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

#include <QtGui>
#include "mainwnd.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	/*QTranslator translator;
	translator.load("jcw_ru", ".");
	app.installTranslator(&translator);*/
	MainWnd mainWnd;
	mainWnd.show();
	//mainWnd.dumpObjectTree();
	return app.exec();
}
