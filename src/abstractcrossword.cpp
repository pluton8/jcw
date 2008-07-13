#include "abstractcrossword.h"

AbstractCrossword::AbstractCrossword(QWidget* parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	cellSize = 20;
	margin = 20;
	needDelete = false;
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
}

QString AbstractCrossword::getName() const
{
	return name;
}

void AbstractCrossword::clearField()
{
}
