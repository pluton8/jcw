#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui>
#include <QtXml>
#include "classiccw.h"
#include "fieldcheckerthread.h"

class MainWnd : public QMainWindow
{
Q_OBJECT

public:
	MainWnd(QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);
	~MainWnd();

protected:
	QScrollArea*		scrollArea;
	AbstractCrossword*	crossword;
	//QWidget*			centralWidget;
	QMenuBar*			menuBar;
	QMenu*				menu;
	QToolBar*			toolBar;
	QStatusBar*			statusBar;
	QLabel*				checkResultLabel;
	//QAction*			action;
	QAction*			openCWAction;
	QAction*			showInfoAction;
	QAction*			quitAction;
	QAction*			aboutAction;
	QAction*			clearFieldAction;
	QString*			windowName;
	FieldCheckerThread	fieldChecker;
	
protected slots:
	void openCrossword();
};

#endif
