#ifndef CROSSWORDINFO_H
#define CROSSWORDINFO_H

#include <QtGui>

class CrosswordInfo : public QDialog
{
Q_OBJECT
	
public:
	CrosswordInfo(const QString& name = QString(), const QString& author = QString(),
			const QString& date = QString(), const QString& comment = QString(),
			QWidget* parent = NULL, Qt::WindowFlags f = Qt::Dialog);
	
protected:
	QLabel*			nameLabel;
	QLabel*			authorLabel;
	QLabel*			dateLabel;
	QLabel*			commentLabel;
	QLineEdit*		nameLineEdit;
	QLineEdit*		authorLineEdit;
	QLineEdit*		dateLineEdit;
	QTextEdit*		commentTextEdit;
	QPushButton*	okPushButton;
	
};

#endif
