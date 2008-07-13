#include "rectcrossword.h"

RectCrossword::RectCrossword(QWidget* parent, Qt::WindowFlags f)
	: AbstractCrossword(parent, f)
{
	fw = fh = th = lw = 0;
	thdr = lhdr = NULL;
}

void RectCrossword::sizes(quint16* fw, quint16* fh, quint16* th, quint16* lw)
{
	if (fw != NULL)
		*fw = this->fw;
	if (fh != NULL)
		*fh = this->fh;
	if (th != NULL)
		*th = this->th;
	if (lw != NULL)
		*lw = this->lw;
}

qint16** RectCrossword::getThdr()
{
	return thdr;
}

qint16** RectCrossword::getLhdr()
{
	return lhdr;
}
