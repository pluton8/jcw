#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui>
#include <QtXml>
#include "classiccw.h"

class MainWnd : public QMainWindow
{
Q_OBJECT

public:
	MainWnd(QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

protected:
	QScrollArea*		scrollArea;
	AbstractCrossword*	crossword;
	//QWidget*			centralWidget;
	QMenuBar*			menuBar;
	QMenu*				menu;
	QToolBar*			toolBar;
	QStatusBar*			statusBar;
	//QAction*			action;
	QAction*			openCWAction;
	QAction*			showInfoAction;
	QAction*			quitAction;
	QAction*			aboutAction;
	
protected slots:
	void openCrossword();
	void showInfo();
};

#endif
