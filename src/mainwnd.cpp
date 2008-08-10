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

#include "mainwnd.h"

MainWnd::MainWnd(QWidget* parent, Qt::WindowFlags f)
	: QMainWindow(parent, f)
{
	crossword = NULL;
	
	/*		настройки глав окна 	*/
	/*if (this->objectName().isEmpty())
		this->setObjectName(QString::fromUtf8("MainWnd"));*/
	windowName = new QString("jcw");
	this->setWindowTitle(*windowName);
	this->setGeometry(150, 150, 800, 600);
	
	/*		создаём меню и тулбар		*/
	menuBar = new QMenuBar(this);
	toolBar = new QToolBar(trUtf8("Standart"), this);
	
	menu = new QMenu(trUtf8("&File"), menuBar);
	menuBar->addMenu(menu);
	
	newCWAction = new QAction(trUtf8("&New crossword..."), menu);		// создать файл
	newCWAction->setShortcut(Qt::CTRL + Qt::Key_N);
	newCWAction->setIcon(QIcon(":/pics/filenew.png"));
	connect(newCWAction, SIGNAL(triggered()), SLOT(newCrossword()));
	menu->addAction(newCWAction);
	toolBar->addAction(newCWAction);
	
	openCWAction = new QAction(trUtf8("&Open crossword..."), menu);		// открыть файл
	openCWAction->setShortcut(Qt::CTRL + Qt::Key_O);
	openCWAction->setIcon(QIcon(":/pics/fileopen.png"));
	connect(openCWAction, SIGNAL(triggered()), SLOT(openCrossword()));
	menu->addAction(openCWAction);
	toolBar->addAction(openCWAction);
	
	saveCWAction = new QAction(trUtf8("&Save crossword..."), menu);		// сохранить файл
	saveCWAction->setShortcut(Qt::CTRL + Qt::Key_S);
	saveCWAction->setIcon(QIcon(":/pics/filesave.png"));
	saveCWAction->setEnabled(false);
	connect(saveCWAction, SIGNAL(triggered()), SLOT(saveCrossword()));
	menu->addAction(saveCWAction);
	toolBar->addAction(saveCWAction);
	
	showInfoAction = new QAction(trUtf8("Show &info..."), menu);		// показать инфу о кроссворде
	showInfoAction->setShortcut(Qt::CTRL + Qt::Key_I);
	showInfoAction->setEnabled(false);
	//connect(showInfoAction, SIGNAL(triggered()), this, SLOT(showInfo()));
	menu->addAction(showInfoAction);
	toolBar->addAction(showInfoAction);
	
	clearFieldAction = new QAction(trUtf8("&Clear field"), menu);		// очистка поля
	clearFieldAction->setShortcut(Qt::CTRL + Qt::Key_C);
	clearFieldAction->setEnabled(false);
	//connect(clearFieldAction, SIGNAL(triggered()), this, SLOT(clearField()));
	menu->addAction(clearFieldAction);
	toolBar->addAction(clearFieldAction);
	
	menu->addSeparator();
	toolBar->addSeparator();
	
	quitAction = new QAction(trUtf8("&Quit"), menu);					// выход
	quitAction->setShortcut(Qt::ALT + Qt::Key_F4);
	quitAction->setIcon(QIcon(":/pics/quit.png"));
	connect(quitAction, SIGNAL(triggered()), SLOT(close()));
	menu->addAction(quitAction);
	toolBar->addAction(quitAction);
	
	menu = new QMenu(trUtf8("&About"), menuBar);
	menuBar->addMenu(menu);
	aboutAction = menu->addAction(trUtf8("About &Qt..."), qApp, SLOT(aboutQt()), Qt::SHIFT + Qt::Key_F1);
	
	this->setMenuBar(menuBar);
	this->addToolBar(Qt::TopToolBarArea, toolBar);
	
	/*		добавляем статусбар		*/
	statusBar = new QStatusBar(this);
	//statusBar->showMessage("hello, world!");
	solveProgress = new QProgressBar(statusBar);
	//solveProgress->resize(10, solveProgress->height());
	statusBar->addWidget(solveProgress);
	checkResultLabel = new QLabel("---", statusBar);
	statusBar->addWidget(checkResultLabel);
	solvingTimeLabel = new QLabel(statusBar);
	statusBar->addWidget(solvingTimeLabel);
	this->setStatusBar(statusBar);
	
	/*		добавляем виджеты		*/
	//centralWidget = new QWidget(this);
	//centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
	//centralWidget->setGeometry(0, 0, 800, 600);
	scrollArea = new QScrollArea(this);
	//scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
	//scrollArea->setGeometry(10, 10, 700, 500);
	//scrollArea->setWidgetResizable(true);
	this->setCentralWidget(scrollArea);
	//crossword = new ClassicCW(scrollArea);
	//crossword->setGeometry(3, 3, 695, 495);
	//scrollArea->setWidget(crossword);
	scrollArea->show();
	
	//cwType = ctNone;
	fieldChecker.start();
	connect(&fieldChecker, SIGNAL(resultTextChanged(QString)), checkResultLabel, SLOT(setText(QString)));
	//fieldChecker.setResultLabel(checkResultLabel);
	//connect(this, SIGNAL(cellStateChanged()), &fieldChecker, SLOT(check()));
	
	/*	убрать это потом:	*/
	/*QFile file("newchannel.jcw");
	QDomDocument domDoc;
	domDoc.setContent(&file);
	crossword = new ClassicCW(domDoc.documentElement());
	crossword->setGeometry(3, 3, 695, 495);
	scrollArea->setWidget(crossword);
	showInfoAction->setEnabled(true);
	if (!crossword->getName().isEmpty())
		setWindowTitle(QString("%1 - %2").arg(*windowName).arg(crossword->getName()));
	fieldChecker.setCrossword(crossword, FieldCheckerThread::ctClassic);
	connect(&fieldChecker, SIGNAL(solved()), this, SLOT(solved()));
	connect(showInfoAction, SIGNAL(triggered()), crossword, SLOT(showInfo()));
	connect(clearFieldAction, SIGNAL(triggered()), crossword, SLOT(clearField()));
	solveProgress->setValue(0);
	connect(crossword, SIGNAL(progressChanged(int)), solveProgress, SLOT(setValue(int)));*/
}

MainWnd::~MainWnd()
{
	fieldChecker.exit();
}

void MainWnd::openCrossword()
{
	QString fileName = QFileDialog::getOpenFileName(this, trUtf8("Open crossword"), NULL,
			trUtf8("Crosswords (*.jcw);;All files(*)"));
	if (fileName == NULL)					// если ничё не выбрано, то выход
		return;
	
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))	// если ошибка открытия файла
	{
		QMessageBox::critical(this, trUtf8("Error"), trUtf8("Can't open file"));
		return;
	}
	
	QDomDocument domDoc;
	QString errorMsg;
	int errorLine;
	int errorCol;
	if (!domDoc.setContent(&file, &errorMsg, &errorLine, &errorCol))	// если ошибка парсинга файла
	{
		/*QMessageBox::critical(this, trUtf8("Error"), trUtf8("Invalid file (") + errorMsg +
				trUtf8(")\nError line: ") + QString::number(errorLine) + trUtf8("\nError column: ") +
				QString::number(errorCol));*/
		QMessageBox::critical(this, trUtf8("Error"), QString(trUtf8(
				"Invalid file (%1)\nError line: %2\nError column: %3")).arg(errorMsg).arg(
				QString::number(errorLine)).arg(QString::number(errorCol)));
		return;
	}
	
	QDomElement domElement = domDoc.documentElement();
	if ((!domElement.isNull()) && domElement.isElement())
	{
		domElement = domElement.toElement();
		if ((!domElement.isNull()) && (domElement.tagName() == "crossword"))
		{
			QString type = domElement.attribute("type");
			if (type == "classic")			// если тип известен, добавляем соответствующий виджет
			{
				if (crossword != NULL)
					delete crossword;
				crossword = new ClassicCW(domDoc.documentElement(), &solvingTime);
				if (crossword->isNeedDelete())
				{
					QMessageBox::critical(this, trUtf8("Error"), trUtf8("Invalid values in file"));
					delete crossword;
					crossword = NULL;
					showInfoAction->setEnabled(false);
				}
				else
				{
					crossword->setGeometry(3, 3, 695, 495);
					scrollArea->setWidget(crossword);
					showInfoAction->setEnabled(true);
					clearFieldAction->setEnabled(true);
					saveCWAction->setEnabled(true);
					if (!crossword->getName().isEmpty())
						setWindowTitle(QString("%1 - %2").arg(*windowName).arg(crossword->getName()));
					fieldChecker.setCrossword(crossword, CWType::ctClassic);
					connect(&fieldChecker, SIGNAL(solved()), SLOT(solved()));
					connect(showInfoAction, SIGNAL(triggered()), crossword, SLOT(showInfo()));
					connect(clearFieldAction, SIGNAL(triggered()), crossword, SLOT(clearField()));
					//solveProgress->setValue(0);
					connect(&fieldChecker, SIGNAL(progressChanged(int)), solveProgress, SLOT(setValue(int)));
					crossword->updateProgress();
					solvingTimer = new QTimer(crossword);
					solvingTimer->setInterval(1000);
					connect(solvingTimer, SIGNAL(timeout()), SLOT(solvingTimerTimeout()));
					solvingTimer->start();
				}
			}
			else
				QMessageBox::warning(this, trUtf8("Warning"),
						trUtf8("This type of crossword not supported"));
		}
	}
	
	file.close();
}

void MainWnd::solved()
{
	solvingTimer->stop();
	crossword->updatePixmap();
	QMessageBox::information(this, trUtf8("Crossword solved"), QString(trUtf8(
			"You win!\nCongratulations and blah-blah-blah\nElapsed time to solving: %1\nCorrections count: %2").
			arg(solvingTime.toString("H:mm:ss")).arg(crossword->getNumCorrections())));
	crossword->solved();
	clearFieldAction->setEnabled(false);
	saveCWAction->setEnabled(false);
}

void MainWnd::solvingTimerTimeout()
{
	solvingTime = solvingTime.addSecs(1);
	solvingTimeLabel->setText(QString(trUtf8("Elapsed time: %1")).arg(solvingTime.toString("H:mm:ss")));
}

void MainWnd::saveCrossword()
{
	QString fileName = QFileDialog::getSaveFileName(this, trUtf8("Save crossword"), NULL,
			trUtf8("Crosswords (*.jcw);;All files(*)"));
	if (fileName == NULL)					// если ничё не выбрано, то выход
		return;
	
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(this, trUtf8("Error"), trUtf8("Can't save to file"));
		return;
	}
	
	crossword->save(&file);
	file.close();
}

void MainWnd::newCrossword()
{
	NewCWDialog* newDialog = new NewCWDialog(this);
	if (newDialog->exec() != QDialog::Accepted)
		return;
	CWType::CrosswordType cwType = newDialog->getCWType();
	quint16 cwWidth = newDialog->getCWWidth();
	quint16 cwHeight = newDialog->getCWHeight();
	quint16 lWidth = newDialog->getLWidth();
	quint16 tHeight = newDialog->getTHeight();
}
