#include "mainwnd.h"

MainWnd::MainWnd(QWidget* parent, Qt::WindowFlags f)
	: QMainWindow(parent, f)
{
	crossword = NULL;
	
	/*		настройки глав окна 	*/
	/*if (this->objectName().isEmpty())
		this->setObjectName(QString::fromUtf8("MainWnd"));*/
	this->setWindowTitle("jcw");
	this->setGeometry(150, 150, 800, 600);
	
	/*		создаём меню и тулбар		*/
	menuBar = new QMenuBar(this);
	toolBar = new QToolBar(trUtf8("Standart"), this);
	
	menu = new QMenu(trUtf8("&File"), menuBar);
	menuBar->addMenu(menu);
	
	openCWAction = new QAction(trUtf8("&Open crossword..."), menu);		// открыть файл
	openCWAction->setShortcut(Qt::CTRL + Qt::Key_O);
	connect(openCWAction, SIGNAL(triggered()), this, SLOT(openCrossword()));
	menu->addAction(openCWAction);
	toolBar->addAction(openCWAction);
	showInfoAction = new QAction(trUtf8("&Show info..."), menu);			// показать инфу о кроссворде
	showInfoAction->setShortcut(Qt::CTRL + Qt::Key_I);
	showInfoAction->setEnabled(false);
	connect(showInfoAction, SIGNAL(triggered()), this, SLOT(showInfo()));
	menu->addAction(showInfoAction);
	toolBar->addAction(showInfoAction);
	menu->addSeparator();
	toolBar->addSeparator();
	quitAction = new QAction(trUtf8("&Quit"), menu);					// выход
	quitAction->setShortcut(Qt::ALT + Qt::Key_F4);
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
	menu->addAction(quitAction);
	toolBar->addAction(quitAction);
	
	menu = new QMenu(trUtf8("&About"), menuBar);
	menuBar->addMenu(menu);
	aboutAction = menu->addAction(trUtf8("About &Qt"), qApp, SLOT(aboutQt()), Qt::SHIFT + Qt::Key_F1);
	
	this->setMenuBar(menuBar);
	this->addToolBar(Qt::TopToolBarArea, toolBar);
	
	/*		добавляем статусбар		*/
	statusBar = new QStatusBar(this);
	statusBar->showMessage("hello, world!");
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
	
	QFile file("newchannel.jcw");
	QDomDocument domDoc;
	domDoc.setContent(&file);
	crossword = new ClassicCW(domDoc.documentElement());
	crossword->setGeometry(3, 3, 695, 495);
	scrollArea->setWidget(crossword);
	showInfoAction->setEnabled(true);
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
		QMessageBox::critical(this, trUtf8("Error"), trUtf8("Invalid file (") + errorMsg +
				trUtf8(")\nError line: ") + QString::number(errorLine) + trUtf8("\nError column: ") +
				QString::number(errorCol));
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
				crossword = new ClassicCW(domDoc.documentElement());
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
				}
			}
			else
				QMessageBox::warning(this, trUtf8("Warning"),
						trUtf8("This type of crossword not supported"));
		}
	}
	
	file.close();
}

void MainWnd::showInfo()
{
	if (crossword != NULL)
		crossword->showInfo();
}