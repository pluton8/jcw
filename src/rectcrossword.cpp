#include "rectcrossword.h"

RectCrossword::RectCrossword(QWidget* parent, Qt::WindowFlags f)
	: AbstractCrossword(parent, f)
{
	fw = fh = th = lw = 0;
	thdr = lhdr = NULL;
}
