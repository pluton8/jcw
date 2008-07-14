#ifndef FIELDCHECKERTHREAD_H
#define FIELDCHECKERTHREAD_H

#include <QtGui>
#include "classiccw.h"

//class ClassicCW;

class FieldCheckerThread : public QThread
{
Q_OBJECT
	
public:
	FieldCheckerThread(QWidget* parent = NULL);
	//~FieldCheckerThread();
	void run();
	enum CrosswordType { ctNone, ctClassic };
	void setCrossword(AbstractCrossword* crossword, CrosswordType cwType);
	
public slots:
	void check(quint16 fX, quint16 fY);
	
protected:
	AbstractCrossword*	crossword;
	CrosswordType		cwType;
	quint16				fw;
	quint16				fh;
	quint16				th;
	quint16				lw;
	
signals:
	void solved();
	void resultTextChanged(QString);
};

#endif
