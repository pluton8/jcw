#include "crosswordinfo.h"

CrosswordInfo::CrosswordInfo(const QString& name, const QString& author, const QString& date,
		const QString& comment, QWidget* parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	nameLineEdit = new QLineEdit(name, this);
	nameLineEdit->setReadOnly(true);
	nameLineEdit->setMinimumWidth(120);
	nameLabel = new QLabel(trUtf8("&Name:"), this);
	nameLabel->setBuddy(nameLineEdit);
	
	authorLineEdit = new QLineEdit(author, this);
	authorLineEdit->setReadOnly(true);
	authorLabel = new QLabel(trUtf8("&Author:"), this);
	authorLabel->setBuddy(authorLineEdit);
	
	dateLineEdit = new QLineEdit(date, this);
	dateLineEdit->setReadOnly(true);
	dateLabel = new QLabel(trUtf8("&Date:"), this);
	dateLabel->setBuddy(dateLineEdit);
	
	commentTextEdit = new QTextEdit(comment, this);
	commentTextEdit->setReadOnly(true);
	commentTextEdit->setMinimumHeight(50);
	commentLabel = new QLabel(trUtf8("&Comment:"), this);
	commentLabel->setBuddy(commentTextEdit);
	
	okPushButton = new QPushButton(trUtf8("&OK"), this);
	connect(okPushButton, SIGNAL(clicked()), this, SLOT(close()));
	
	QGridLayout* gridLayout = new QGridLayout(this);
	gridLayout->addWidget(nameLabel, 0, 0);
	gridLayout->addWidget(nameLineEdit, 0, 1);
	gridLayout->addWidget(authorLabel, 1, 0);
	gridLayout->addWidget(authorLineEdit, 1, 1);
	gridLayout->addWidget(dateLabel, 2, 0);
	gridLayout->addWidget(dateLineEdit, 2, 1);
	gridLayout->addWidget(commentLabel, 3, 0);
	gridLayout->addWidget(commentTextEdit, 4, 0, 1, 2);
	gridLayout->addWidget(okPushButton, 5, 0, 1, 2, Qt::AlignHCenter);
	setLayout(gridLayout);
	
	setWindowTitle(trUtf8("Crossword info"));
}

/*CrosswordInfo::~CrosswordInfo()
{
	qDebug() << "destructor";
}
*/