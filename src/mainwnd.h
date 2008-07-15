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
	QProgressBar*		solveProgress;
	QLabel*				solvingTimeLabel;		// показывает время решения в статусбаре
	QTimer*				solvingTimer;			// считает время решения
	QTime				solvingTime;
	
	//QAction*			action;
	QAction*			openCWAction;
	QAction*			showInfoAction;
	QAction*			quitAction;
	QAction*			aboutAction;
	QAction*			clearFieldAction;
	QString*			windowName;
	FieldCheckerThread	fieldChecker;
	
protected slots:
	void openCrossword();			// открыть кроссворд
	void solved();					// кроссворд решён
	void solvingTimerTimeout();		// обновить время решения
};

#endif
