/****************************
Проект:		Project:	jcw
Автор:		Author:		pluton
Связь:		JabberID:	j8@jabber.ru
Лицензия:	License:	see ../LICENSE file
Дата:		Date:		07.2008+
Сайт:		Site:		http://sourceforge.net/projects/jcw/
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
