#include "Calc.h"
#include "./ui_Calc.h"

#include <QPushButton>
#include <QtMath>
#include <QMap>
#include <QStackedWidget>

#ifdef QT_DEBUG
#include <QDebug>
#endif

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
///////////////////////////////////////////////////////////
*/

///////////////////////////////////////////////////////////
//	MENU BAR											 //
///////////////////////////////////////////////////////////

// Changing view mode in [View] tab
void Calc::menuViewModeChanged()
{
	clearButtonPressed();
	
	if (ui->modes->currentIndex() != static_cast<int>(mode::basic))
	{
		qInfo("void Calc::menuViewModeChanged(): Enabled Mode::basic");
		ui->modes->setCurrentIndex(static_cast<int>(mode::basic));
		ui->statusbar->showMessage("Changed mode to Basic.", 2000);
	}
	else /* if (ui->modes->currentIndex() != static_cast<int>(Mode::scientific)) */		
	{
		qInfo("void Calc::menuViewModeChanged(): Enabled Mode::scientific");
		ui->modes->setCurrentIndex(static_cast<int>(mode::scientific));
		ui->statusbar->showMessage("Changed mode to Scientific.", 2000);
	}	
}

///////////////////////////////////////////////////////////
//	INPUT												 //
///////////////////////////////////////////////////////////

// Putting numbers in using [0~9] buttons.
void Calc::numButtonPressed()
{
	// Reset [=] presses count.
	data.subsequent_equal_presses = 0;
	
	// Establish pointer to the button pressed.
	const auto *button = dynamic_cast<QPushButton*>(sender());
	const QString button_value = button->text();
	const QString display_value = ui->display->text();

	if (display_value == QString::number(data.lhs)
		|| display_value == "0" )
	{
		ui->display->setText(button_value);
	}
	else
	{
		const QString new_value = display_value + button_value;
		ui->display->setText(new_value);
	}
}

void Calc::commaButtonPressed()
{
	// Reset [=] presses count.
	data.subsequent_equal_presses = 0;
	
	const QString display_value = ui->display->text();
	const QString new_value = display_value + '.';
	ui->display->setText(new_value);
}

///////////////////////////////////////////////////////////
//	TWO-ARGUMENT OPERATIONS								 //
///////////////////////////////////////////////////////////

// Core function performing operation stored in buffer.
// Used both by [=] button and math buttons.
[[nodiscard]] QString Calc::performOperation() const
{
	// Result string.
	QString str_result{};

	switch (data.op_decision)
	{
	case operation::none:		
		str_result = ui->display->text();
		break;
	case operation::division:
		if (data.rhs == 0)
		{
			ui->statusbar->showMessage("Cannot divide by zero!", 2000);
			str_result = "Err";
		}
		else str_result = QString::number(data.lhs / data.rhs);
		break;
	case operation::multiplication:
		str_result = QString::number(data.lhs * data.rhs);
		break;
	case operation::subtraction:
		str_result = QString::number(data.lhs - data.rhs);
		break;
	case operation::addition:
		str_result = QString::number(data.lhs + data.rhs);
		break;
	}

	return str_result;
}

// Math two-argument operation buttons: [/], [*], [−], [+].
void Calc::mathButtonPressed()
{
	// Reset [=] presses count.
	data.subsequent_equal_presses = 0;
	
	// If in sequential operation, evaluate queued operation and treat its result
	// as lhs argument for the next operation now being entered.
	if (data.sequential_operation)
	{
		// The lhs is already saved, save rhs from display,
		// perform operation and put the result on screen.
		data.rhs = ui->display->text().toDouble();
		const QString prev_op_result = performOperation();
		ui->display->setText(prev_op_result); 
	}

	// If first operation, lhs = previously put number,
	// if in sequence, lhs = prev result, evaluated above.
	data.lhs = ui->display->text().toDouble();

	// Operation enum mapping to key labels.
	QMap<QString, operation> op_names
	{
		{"/", operation::division},
		{"*", operation::multiplication},
		{"−", operation::subtraction}, // − (U+2212)!
		{"+", operation::addition}
	};

	// Establish pointer to the button pressed.
	const auto *button = qobject_cast<QPushButton*>(sender());
	const QString button_label = button->text();

	// Set op_decision basing on the label of the button pressed.
	data.op_decision = op_names[button_label];

	// Begin (or maintain) sequential operation state until [=] is pressed.
	data.sequential_operation = true;
}

// Procedure when pressing [=] button.
void Calc::equalButtonPressed()
{
	// Record [=] presses count.
	data.subsequent_equal_presses++;

	// Set result as lhs and leave rhs unchanged if [=] is pressed more than once.
	if (const auto curr_display = ui->display->text().toDouble();
		data.subsequent_equal_presses > 1)
	{
		data.lhs = curr_display;
	}
	// Otherwise, current value on display is normally treated as rhs.
	else
	{
		data.rhs = curr_display;
	}	
	
	ui->display->setText(performOperation());
	data.sequential_operation = false;
}

// Procedure when pressing [%] button. The method of calculation is different than usual.
// Pressing [%] ends sequential operation the same way as [=].
void Calc::percentButtonPressed()
{
	// Reset [=] presses count.
	data.subsequent_equal_presses = 0;
	
	// Save current display state as rhs value.
	data.rhs = ui->display->text().toDouble();

	QString str_result{};
	union
	{
		double percentage_fraction{};
		double percentage_of_lhs;
	};

	switch (data.op_decision)
	{
	case operation::none:
		str_result = ui->display->text();
		break;
	case operation::division:
		percentage_fraction = data.rhs / 100;
		if (percentage_fraction == 0)
		{
			ui->statusbar->showMessage("Cannot divide by zero!", 2000);
			str_result = "Err";
		}
		else str_result = QString::number(data.lhs / percentage_fraction);
		break;
	case operation::multiplication:
		percentage_fraction = data.rhs / 100;
		str_result = QString::number(data.lhs * percentage_fraction);
		break;
	case operation::subtraction:
		percentage_of_lhs = (data.rhs / 100) * data.lhs;
		str_result = QString::number(data.lhs - percentage_of_lhs);
		break;
	case operation::addition:
		percentage_of_lhs = (data.rhs / 100) * data.lhs;
		str_result = QString::number(data.lhs + percentage_of_lhs);
		break;
	}

	ui->display->setText(str_result);
	data.sequential_operation = false;
}

///////////////////////////////////////////////////////////
//	SINGLE-ARGUMENT OPERATIONS							 //
///////////////////////////////////////////////////////////

// Square button [x²].
void Calc::squareButtonPressed()
{
	// Reset [=] presses count.
	data.subsequent_equal_presses = 0;
	
	// Save current display state as base value.
	data.unary = ui->display->text().toDouble();

	// Evaluate and show square.
	const QString str_result = QString::number(qPow(data.unary, 2));
	ui->display->setText(str_result);
}

// Square root button [√‾].
void Calc::sqrtButtonPressed()
{
	// Reset [=] presses count.
	data.subsequent_equal_presses = 0;
	
	// Save current display state as base value.
	data.unary = ui->display->text().toDouble();

	// Evaluate and show square.
	const qreal sqrt_result = qSqrt(data.unary);
	const QString str_result = QString::number(sqrt_result);
	ui->display->setText(str_result);
}

// [⌫] (Backspace) button functionality.
void Calc::backspaceButtonPressed() const
{
	if (ui->display->text().length() > 1)
	{
		ui->display->backspace();
	}
	else
	{
		ui->display->setText("0");
	}
}

// Clearing the display and buffer with [C] button.
void Calc::clearButtonPressed()
{
	// Reset [=] presses count.
	data.subsequent_equal_presses = 0;
	
	// Clear the display.
	ui->display->setText(QString::number(Data::init_calc_value));

	// Flush the buffer.
	data.op_decision = operation::none;
	data.lhs = 0.0;
	data.rhs = 1.0;
}

// Changing display value sign with [±] button.
void Calc::signButtonPressed()
{
	// Reset [=] presses count.
	data.subsequent_equal_presses = 0;
	
	const QString curr_value = ui->display->text();
	const double dbl_curr_value = curr_value.toDouble();
	const double dbl_new_value = dbl_curr_value * -1;
	ui->display->setText(QString::number(dbl_new_value));
}

///////////////////////////////////////////////////////////
//	MEMORY												 //
///////////////////////////////////////////////////////////

void Calc::memButtonPressed()
{
	const QString curr_value = ui->display->text();

	if (data.memory == curr_value.toDouble())
	{
		data.memory = Data::init_calc_value;
		ui->statusbar->showMessage("Memory cleaned.", 2000);
	}
	else
	{
		ui->statusbar->showMessage("Memory recalled.", 2000);
	}

	ui->display->setText(QString::number(data.memory));
}

void Calc::memAddButtonPressed()
{
	const QString curr_value = ui->display->text();
	data.memory += curr_value.toDouble();
	ui->statusbar->showMessage("Added to memory.", 2000);
}

void Calc::memSubButtonPressed()
{
	const QString curr_value = ui->display->text();
	data.memory -= curr_value.toDouble();
	ui->statusbar->showMessage("Subtracted from memory.", 2000);
}