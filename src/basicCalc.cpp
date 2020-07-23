#include "Calc.h"
#include "./ui_Calc.h"

#include <QPushButton>
#include <QtMath>
#include <QMap>
#include <QStackedWidget>

#include <cmath>

#ifdef QT_DEBUG
#include <QDebug>
#endif

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	basicCalc.cpp
 	Calc definitions for Basic mode.
///////////////////////////////////////////////////////////
*/

///////////////////////////////////////////////////////////
//	MENU BAR											 //
///////////////////////////////////////////////////////////

// Changing view mode to Basic in [View] tab
void Calc::menuViewBasicTriggered()
{
	if (ui->modes->currentIndex() != static_cast<int>(mode::basic))
	{
		clearButtonPressed();
		qInfo("void Calc::menuViewModeChanged(): Enabled Mode::basic");
		ui->modes->setCurrentIndex(static_cast<int>(mode::basic));
		ui->statusbar->showMessage("Changed mode to Basic.", 2000);
		curr_display_ = ui->display;
	}
}

// Changing view mode to Scientific in [View] tab
void Calc::menuViewScientificTriggered()
{
	if (ui->modes->currentIndex() != static_cast<int>(mode::scientific))
	{
		clearButtonPressed();
		qInfo("void Calc::menuViewModeChanged(): Enabled Mode::scientific");
		ui->modes->setCurrentIndex(static_cast<int>(mode::scientific));
		ui->statusbar->showMessage("Changed mode to Scientific.", 2000);
		curr_display_ = ui->display_sci;
	}
}

///////////////////////////////////////////////////////////
//	INPUT												 //
///////////////////////////////////////////////////////////

// Putting numbers in using [0~9] buttons.
void Calc::numButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Establish pointer to the button pressed.
	const auto *button = dynamic_cast<QPushButton*>(sender());
	const QString button_value = button->text();
	const QString display_value = curr_display_->text();

	if (display_value == QString::number(data_.lhs)
		|| display_value == "0" )
	{
		curr_display_->setText(button_value);
	}
	else
	{
		const QString new_value = display_value + button_value;
		curr_display_->setText(new_value);
	}
}

void Calc::commaButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	const QString display_value = curr_display_->text();
	const QString new_value = display_value + '.';
	curr_display_->setText(new_value);
}

///////////////////////////////////////////////////////////
//	TWO-ARGUMENT OPERATIONS								 //
///////////////////////////////////////////////////////////

// Core function performing operation stored in buffer.
// Used both by [=] button and math buttons.
[[nodiscard]] QString Calc::performOperation() const
{
	double result{};
	QString str_result{};

	switch (data_.op_decision)
	{
	case operation::none:		
		str_result = curr_display_->text();
		break;
	case operation::division:
		if (data_.rhs == 0)
		{
			ui->statusbar->showMessage("Cannot divide by zero!", 2000);
			str_result = "Err";
		}
		else
		{
			result = data_.lhs / data_.rhs;
			str_result.setNum(result, config_.disp_format, config_.display_prec);
		}
		break;
	case operation::multiplication:
		result = data_.lhs * data_.rhs;
		str_result.setNum(result, config_.disp_format, config_.display_prec);
		break;
	case operation::subtraction:
		result = data_.lhs - data_.rhs;
		str_result.setNum(result, config_.disp_format, config_.display_prec);
		break;
	case operation::addition:
		result = data_.lhs + data_.rhs;
		str_result.setNum(result, config_.disp_format, config_.display_prec);
		break;
	}

	return str_result;
}

// Math two-argument operation buttons: [/], [*], [−], [+].
void Calc::mathButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// If in sequential operation, evaluate queued operation and treat its result
	// as lhs argument for the next operation now being entered.
	if (data_.sequential_operation)
	{
		// The lhs is already saved, save rhs from display,
		// perform operation and put the result on screen.
		data_.rhs = curr_display_->text().toDouble();
		const QString prev_op_result = performOperation();
		curr_display_->setText(prev_op_result); 
	}

	// If first operation, lhs = previously put number,
	// if in sequence, lhs = prev result, evaluated above.
	data_.lhs = curr_display_->text().toDouble();

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
	data_.op_decision = op_names[button_label];

	// Begin (or maintain) sequential operation state until [=] is pressed.
	data_.sequential_operation = true;
}

// Procedure when pressing [=] button.
void Calc::equalButtonPressed()
{
	// Record [=] presses count.
	data_.subsequent_equal_presses++;

	// Set result as lhs and leave rhs unchanged if [=] is pressed more than once.
	if (const auto curr_display = curr_display_->text().toDouble();
		data_.subsequent_equal_presses > 1)
	{
		data_.lhs = curr_display;
	}
	// Otherwise, current value on display is normally treated as rhs.
	else
	{
		data_.rhs = curr_display;
	}	
	
	curr_display_->setText(performOperation());
	data_.sequential_operation = false;
}

// Procedure when pressing [%] button. The method of calculation is different than usual.
// Pressing [%] ends sequential operation the same way as [=].
void Calc::percentButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Save current display state as rhs value.
	data_.rhs = curr_display_->text().toDouble();

	double result{};
	QString str_result{};
	
	union
	{
		double percentage_fraction{};
		double percentage_of_lhs;
	};

	switch (data_.op_decision)
	{
	case operation::none:
		str_result = curr_display_->text();
		break;
	case operation::division:
		percentage_fraction = data_.rhs / 100;
		if (percentage_fraction == 0)
		{
			ui->statusbar->showMessage("Cannot divide by zero!", 2000);
			str_result = "Err";
		}
		else 
		{
			result = data_.lhs / percentage_fraction;
			str_result.setNum(result, config_.disp_format, config_.display_prec);
		}
		break;
	case operation::multiplication:
		percentage_fraction = data_.rhs / 100;
		result = data_.lhs * percentage_fraction;
		str_result.setNum(result, config_.disp_format, config_.display_prec);
		break;
	case operation::subtraction:
		percentage_of_lhs = (data_.rhs / 100) * data_.lhs;
		result = data_.lhs - percentage_of_lhs;
		str_result.setNum(result, config_.disp_format, config_.display_prec);
		break;
	case operation::addition:
		percentage_of_lhs = (data_.rhs / 100) * data_.lhs;
		result = data_.lhs + percentage_of_lhs;
		str_result.setNum(result, config_.disp_format, config_.display_prec);
		break;
	}

	curr_display_->setText(str_result);
	data_.sequential_operation = false;
}

///////////////////////////////////////////////////////////
//	SINGLE-ARGUMENT OPERATIONS							 //
///////////////////////////////////////////////////////////

// Square button [x²].
void Calc::squareButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Save current display state as base value.
	data_.unary = curr_display_->text().toDouble();

	// Evaluate and show square.
	QString str_result;
	str_result.setNum(qPow(data_.unary, 2), config_.disp_format, config_.display_prec);
	curr_display_->setText(str_result);
}

// Square root button [√‾].
void Calc::sqrtButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Save current display state as base value.
	data_.unary = curr_display_->text().toDouble();

	// Evaluate and show square.	
	QString str_result{};
	const qreal result = qSqrt(data_.unary);
	
	str_result.setNum(result, config_.disp_format, config_.display_prec);
	curr_display_->setText(str_result);
}

// [⌫] (Backspace) button functionality.
void Calc::backspaceButtonPressed() const
{
	if (curr_display_->text().length() > 1)
	{
		curr_display_->backspace();
	}
	else
	{
		curr_display_->setText("0");
	}
}

// Clearing the display and buffer with [C] button.
void Calc::clearButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Clear the display.
	curr_display_->setText(QString::number(config_.init_calc_value));

	// Flush the buffer.
	data_.op_decision = operation::none;
	data_.lhs = 0.0;
	data_.rhs = 1.0;
}

// Changing display value sign with [±] button.
void Calc::signButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;	

	// Remove or add minus sign on display.	
	QString curr_value = curr_display_->text();
	QString new_value{};
	
	if (curr_value[0] == '-')
	{
		new_value = curr_value.remove(0, 1);
	}
	else
	{
		new_value = '-' + curr_value;
	}
	
	curr_display_->setText(new_value);
}

///////////////////////////////////////////////////////////
//	MEMORY												 //
///////////////////////////////////////////////////////////

void Calc::memButtonPressed()
{
	const QString curr_value = curr_display_->text();

	if (data_.memory == curr_value.toDouble())
	{
		data_.memory = config_.init_calc_value;
		ui->statusbar->showMessage("Memory cleaned.", 2000);
	}
	else
	{
		ui->statusbar->showMessage("Memory recalled.", 2000);
	}

	curr_display_->setText(QString::number(data_.memory));
}

void Calc::memAddButtonPressed()
{
	const QString curr_value = curr_display_->text();
	data_.memory += curr_value.toDouble();
	ui->statusbar->showMessage("Added to memory.", 2000);	
}

void Calc::memSubButtonPressed()
{
	const QString curr_value = curr_display_->text();
	data_.memory -= curr_value.toDouble();
	ui->statusbar->showMessage("Subtracted from memory.", 2000);
}