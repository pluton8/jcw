#include "abstractcrossword.h"

AbstractCrossword::AbstractCrossword(QWidget* parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	cellSize = 15;
	margin = 20;
	needDelete = false;
//	name = author = date = NULL;
	ciDialog = NULL;
}

bool AbstractCrossword::isNeedDelete() const
{
	return needDelete;
}

void AbstractCrossword::showInfo()
{
	if (ciDialog == NULL)
		ciDialog = new CrosswordInfo(name, author, date, comment, this);
	ciDialog->show();
//	connect(ciDialog, SIGNAL(destroyed(QObject*)), this, SLOT(ciDialogDestroyed()));
}

/*void AbstractCrossword::ciDialogDestroyed()
{
	qDebug() << "ciDialogDestroyed";
	delete ciDialog;
	ciDialog = NULL;
}*/

//void AbstractCrossword::paintEvent(QPaintEvent* /*event*/)
/*{
	//qDebug() << "paint";
	QPainter paint(this);
	//paint.fillRect(rect(), QBrush(Qt::darkBlue));
}*/
