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

#include "fieldcheckerthread.h"

FieldCheckerThread::FieldCheckerThread(QWidget* parent)
	: QThread(parent)
{
	//qDebug() << "constructor";
	cwType = ctNone;
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
	//exec();
	//check();
}

void FieldCheckerThread::check(quint16 fX, quint16 fY)
{
	if (cwType == ctClassic)
	{
		if (fX == quint16(-1) && fY == quint16(-1))			// если координаты == -1, то надо обновить весь прогресс
		{
			updateProgress();
			return;
		}
		else if (fX == quint16(-2) && fY == quint16(-2))	// если координаты == -2, то надо сбросить прогресс
		{
			emit resultTextChanged(trUtf8("ready"));
			emit progressChanged(0);
			return;
		}
		
		/*		преобразовываем строку поля в текст		*/
		QString row(fw, '_');
		quint16 i;
		for (i = 0; i < fw; i++)
			switch (field[i][fY])
			{
				case ClassicCW::csUndef:
					row[i] = '_';
					break;
				case ClassicCW::csEmpty:
					row[i] = '.';
					break;
				case ClassicCW::csFilled:
					row[i] = '*';
					break;
			}
		//qDebug() << row;
		/*		нужно составить паттерн регэкспа для проверки		*/
		QString rowPattern("^[_.]*");		// <- это только начало :)
		for (i = 0; i < lw; i++)
		{
			quint16 num = qAbs(lhdr[lw - i - 1][fY]);
			if (num == 0)					// останавливаемся на нуле
				break;
			if (i != 0)						// каждый раз, кроме первого, добавляем разделитель блоков
				rowPattern.append("[_.]+");
			rowPattern.append(QString("\\*{%1}").arg(num));
		}
		rowPattern.append("[_.]*$");		// <- конец регэкспа
		
		/*		преобразовываем столбец поля в текст		*/
		QString col(fh, '_');
		for (i = 0; i < fh; i++)
			switch (field[fX][i])
			{
				case ClassicCW::csUndef:
					col[i] = '_';
					break;
				case ClassicCW::csEmpty:
					col[i] = '.';
					break;
				case ClassicCW::csFilled:
					col[i] = '*';
					break;
			}
		
		QString colPattern("^[_.]*");
		for (i = 0; i < th; i++)
		{
			quint16 num = qAbs(thdr[fX][i]);
			if (num == 0)
				break;
			if (i != 0)
				colPattern.append("[_.]+");
			colPattern.append(QString("\\*{%1}").arg(num));
		}
		colPattern.append("[_.]*$");		// <- конец регэкспа
		
		rowsRes->setBit(fY, row.contains(QRegExp(rowPattern)));
		colsRes->setBit(fX, col.contains(QRegExp(colPattern)));
		
		emit resultTextChanged(QString(trUtf8("row #%1: %2; col #%3: %4")).
				arg(fY + 1).arg(rowsRes->at(fY) ? trUtf8("ok") : trUtf8("bad")).
				arg(fX + 1).arg(colsRes->at(fX) ? trUtf8("ok") : trUtf8("bad")));
		
		/*		посчитаем прогресс решения		*/
		quint16 validLines = 0;
		/*		и проверяем, полностью ли решён кроссворд		*/
		bool isSolved = true;
		for (i = 0; i < fh; i++)
			if (!rowsRes->at(i))
				isSolved = false;
			else
				validLines++;
		for (i = 0; i < fw; i++)
			if (!colsRes->at(i))
				isSolved = false;
			else
				validLines++;
		
		emit progressChanged(validLines * 100 / (fw + fh));
		if (isSolved)
			emit solved();
	}
}

void FieldCheckerThread::setCrossword(AbstractCrossword* crossword, CrosswordType cwType)
{
	//qDebug() << crossword->getName();
	this->crossword = crossword;
	this->cwType = cwType;
	//cwType = ctClassic;
	connect(crossword, SIGNAL(cellStateChanged(quint16, quint16)), this, SLOT(check(quint16, quint16)));
	((RectCrossword*) crossword)->sizes(&fw, &fh, &th, &lw);
	thdr = ((ClassicCW*) crossword)->getThdr();
	lhdr = ((ClassicCW*) crossword)->getLhdr();
	field = ((ClassicCW*) crossword)->getField();
	rowsRes = ((RectCrossword*) crossword)->getRowsRes();
	colsRes = ((RectCrossword*) crossword)->getColsRes();
}

void FieldCheckerThread::updateProgress()
{
	if (cwType == ctClassic)
	{
		quint16 i;
		quint16 j;
		/*		циклом преобразовываем строки поля в текст		*/
		for (j = 0; j < fh; j++)
		{
			QString row(fw, '_');
			for (i = 0; i < fw; i++)
				switch (field[i][j])
			{
				case ClassicCW::csUndef:
					row[i] = '_';
					break;
				case ClassicCW::csEmpty:
					row[i] = '.';
					break;
				case ClassicCW::csFilled:
					row[i] = '*';
					break;
			}
			QString rowPattern("^[_.]*");
			for (i = 0; i < lw; i++)
			{
				quint16 num = qAbs(lhdr[lw - i - 1][j]);
				if (num == 0)
					break;
				if (i != 0)
					rowPattern.append("[_.]+");
				rowPattern.append(QString("\\*{%1}").arg(num));
			}
			rowPattern.append("[_.]*$");
			rowsRes->setBit(j, row.contains(QRegExp(rowPattern)));
		}
		
		/*		циклом преобразовываем столбцы поля в текст		*/
		for (j = 0; j < fw; j++)
		{
			QString col(fh, '_');
			for (i = 0; i < fh; i++)
				switch (field[j][i])
			{
				case ClassicCW::csUndef:
					col[i] = '_';
					break;
				case ClassicCW::csEmpty:
					col[i] = '.';
					break;
				case ClassicCW::csFilled:
					col[i] = '*';
					break;
			}
			
			QString colPattern("^[_.]*");
			for (i = 0; i < th; i++)
			{
				quint16 num = qAbs(thdr[j][i]);
				if (num == 0)
					break;
				if (i != 0)
					colPattern.append("[_.]+");
				colPattern.append(QString("\\*{%1}").arg(num));
			}
			colPattern.append("[_.]*$");
			colsRes->setBit(j, col.contains(QRegExp(colPattern)));
		}
		
		emit resultTextChanged(trUtf8("ready"));
		
		quint16 validLines = 0;
		bool isSolved = true;
		for (i = 0; i < fh; i++)
			if (!rowsRes->at(i))
				isSolved = false;
		else
			validLines++;
		for (i = 0; i < fw; i++)
			if (!colsRes->at(i))
				isSolved = false;
		else
			validLines++;
		
		emit progressChanged(validLines * 100 / (fw + fh));
		if (isSolved)
			emit solved();
	}
}
