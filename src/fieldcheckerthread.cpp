#include "fieldcheckerthread.h"

FieldCheckerThread::FieldCheckerThread(QWidget* parent)
	: QThread(parent)
{
	//qDebug() << "constructor";
	cwType = ctNone;
	resultLabel = NULL;
	fw = fh = th = lw = 0;
	crossword = NULL;
}

/*FieldCheckerThread::~FieldCheckerThread()
{
	qDebug() << "destructor";
}
*/
void FieldCheckerThread::run()
{
	//for (int i=0;i<200000000;i++);
	//qDebug() << "yo!";
	exec();
	//check();
}

void FieldCheckerThread::check()
{
	//qDebug() << "check";
	if (cwType == ctClassic)
	{
		ClassicCW::CellState** field = ((ClassicCW*) crossword)->getField();
		qint16** thdr = ((ClassicCW*) crossword)->getThdr();
		qint16** lhdr = ((ClassicCW*) crossword)->getLhdr();
		
		
		
		//resultLabel->setText("nothing found");
	}
}

void FieldCheckerThread::setCrossword(AbstractCrossword* crossword, CrosswordType cwType)
{
	//qDebug() << crossword->getName();
	this->crossword = crossword;
	this->cwType = cwType;
	//cwType = ctClassic;
	connect(crossword, SIGNAL(cellStateChanged()), this, SLOT(check()));
	((RectCrossword*) crossword)->sizes(&fw, &fh, &th, &lw);
}

void FieldCheckerThread::setResultLabel(QLabel* resultLabel)
{
	this->resultLabel = resultLabel;
}
