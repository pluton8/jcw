/****************************
Project:	jcw
Author:		pluton
JabberID:	j8@jabber.ru
License:	see ../LICENSE file
Date:		07.2008+
Site:		http://sourceforge.net/projects/jcw/
****************************/

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
