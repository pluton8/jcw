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
