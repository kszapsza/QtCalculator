#include "Calc.h"
#include "Settings.h"

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

 	basicCalc.cpp
 	Common Calc definitions for both modes.
///////////////////////////////////////////////////////////
*/

///////////////////////////////////////////////////////////
//	MENU BAR											 //
///////////////////////////////////////////////////////////

void Calc::menuFileOptions()
{
	Settings settings(this);
	settings.setModal(true);
	settings.exec();
}

// Changing view mode to Basic in [View] tab
void Calc::menuViewBasicTriggered()
{
	if (ui->modes->currentIndex() != static_cast<int>(mode::basic))
	{
		clearButtonPressed();		
		ui->modes->setCurrentIndex(static_cast<int>(mode::basic));
		ui->menuFunctions->menuAction()->setVisible(false);

		qInfo("void Calc::menuViewModeChanged(): Enabled Mode::basic");
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
		
		ui->modes->setCurrentIndex(static_cast<int>(mode::scientific));
		ui->menuFunctions->menuAction()->setVisible(true);
		
		qInfo("void Calc::menuViewModeChanged(): Enabled Mode::scientific");
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
	// Establish pointer to the button pressed.
	const auto *button = dynamic_cast<QPushButton*>(sender());
	const QString button_value = button->text();
	const QString display_value = curr_display_->text();
	
	QString formatted_lhs_value{};
	formatted_lhs_value.setNum(core_->data.getLhs(), core_->config.disp_format, Config::display_prec);

	QString formatted_last_result{};
	formatted_last_result.setNum(core_->data.getLastResult(), core_->config.disp_format, Config::display_prec);

	// SUBSTITUTION CONDITIONS: compare display value...
	// 1st: ...to lhs ignoring formatting mode (user input is always in basic format),
	// 2nd: ...to lhs taking into account format (formatted results might be in lhs),
	// 3rd: ...to initial value w/o formatting,
	// 4th: ...to last result with formatting,
	// 5th: ...errors.
	 
	if (display_value == QString::number(core_->data.getLhs()) 
		|| display_value == formatted_lhs_value
		|| display_value == QString::number(core_->config.init_value)
		|| (display_value == formatted_last_result && core_->data.getSubsequentEqualPresses())
		|| display_value == "Err" || display_value == "nan" || display_value == "Inf")
	{
		curr_display_->setText(button_value);
	}
	// ELSE CONCATENATE
	else
	{
		const QString new_value = display_value + button_value;
		curr_display_->setText(new_value);
	}
	
	core_->data.resetSubsequentEqualPresses();
}

void Calc::commaButtonPressed()
{
	core_->data.resetSubsequentEqualPresses();
	
	const QString display_value = curr_display_->text();
	curr_display_->setText(display_value + '.');
}

///////////////////////////////////////////////////////////
//	(COMMON) TWO-ARGUMENT OPERATIONS					 //
///////////////////////////////////////////////////////////

// Math two-argument operation buttons: [/], [*], [−], [+].
void Calc::mathButtonPressed()
{
	core_->data.resetSubsequentEqualPresses();
	
	// If in sequential operation, evaluate queued operation and treat its result
	// as lhs argument for the next operation now being entered.
	if (core_->data.isInSequentialOperation())
	{
		// The lhs is already saved, save rhs from display,
		// perform operation and put the result on screen.
		core_->data.takeRhsFromDisp(curr_display_);
		
		const QString prev_op_result = performBinaryOperation();
		curr_display_->setText(prev_op_result); 
	}

	// If first operation, lhs = previously put number,
	// if in sequence, lhs = prev result, evaluated above.
	core_->data.takeLhsFromDisp(curr_display_);

	// Operation enum mapping to key labels.
	const QMap<QPushButton*, operation> op_names
	{
		{ui->button_div,		operation::division},
		{ui->button_div_sci,	operation::division},
		{ui->button_mul,		operation::multiplication},
		{ui->button_mul_sci,	operation::multiplication},
		{ui->button_sub,		operation::subtraction},
		{ui->button_sub_sci,	operation::subtraction},
		{ui->button_add,		operation::addition},
		{ui->button_add_sci,	operation::addition},
		{ui->button_log_basey,	operation::log_base_y},
		{ui->button_modulo,		operation::modulo},
		{ui->button_x_to_y,		operation::power}
	};

	// Establish pointer to the button pressed.
	auto *button = qobject_cast<QPushButton*>(sender());

	// Set op_decision basing on the label of the button pressed.
	core_->data.setOpDecision(op_names[button]);

	// Begin (or maintain) sequential operation state until [=] is pressed.
	core_->data.beginSequential();
}

// Procedure when pressing [=] button.
void Calc::equalButtonPressed()
{
	// Record [=] presses count.
	core_->data.subsequentEqualPressesIncrement();

	// Set result as lhs and leave rhs unchanged if [=] is pressed more than once.
	if (core_->data.getSubsequentEqualPresses() > 1)
	{
		core_->data.takeLhsFromDisp(curr_display_);
	}
	// Otherwise, current value on display is normally treated as rhs.
	else
	{
		core_->data.takeRhsFromDisp(curr_display_);
	}	
	
	curr_display_->setText(performBinaryOperation());
	core_->data.endSequential();
}

// Procedure when pressing [%] button. The method of calculation is different than usual.
// Pressing [%] ends sequential operation the same way as [=].
void Calc::percentButtonPressed()
{
	// Reset [=] presses count.
	core_->data.resetSubsequentEqualPresses();
	
	// Save current display state as rhs value.
	core_->data.takeRhsFromDisp(curr_display_);

	double result{};
	QString str_result{};
	bool err{ false };
	
	union
	{
		double percentage_fraction{};
		double percentage_of_lhs;
	};

	switch (core_->data.getOpDecision())
	{
	case operation::division:
		percentage_fraction = core_->data.getRhs() / 100;
		[[unlikely]] if (percentage_fraction == 0)			
			err = true;
		else
			result = core_->data.getLhs() / percentage_fraction;
		break;
	case operation::multiplication:
		percentage_fraction = core_->data.getRhs() / 100;
		result = core_->data.getLhs() * percentage_fraction;
		break;
	case operation::subtraction:
		percentage_of_lhs = (core_->data.getRhs() / 100) * core_->data.getLhs();
		result = core_->data.getLhs() - percentage_of_lhs;
		break;
	case operation::addition:
		percentage_of_lhs = (core_->data.getRhs() / 100) * core_->data.getLhs();
		result = core_->data.getLhs() + percentage_of_lhs;
		break;
	case operation::none:		
	default:
		str_result = curr_display_->text();
		break;
	}

	if (!err)
	{
		core_->data.setLastResult(result);
		str_result.setNum(result, core_->config.disp_format, Config::display_prec);
	}
	else
	{
		str_result = "Err";
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);		
	}
	
	core_->data.endSequential();
	curr_display_->setText(str_result);
}

///////////////////////////////////////////////////////////
//	SINGLE-ARGUMENT OPERATIONS (BASIC)					 //
///////////////////////////////////////////////////////////

// Evaluates unary operation from core_->data.unary and shows result.
void Calc::performUnaryOperation(const dbl_ptr func)
{
	core_->data.resetSubsequentEqualPresses();	
	core_->data.setLastResult(static_cast<double>(func(core_->data.getUnary())));
	
	// Round to zero if unary result is less than epsilon.
	double result = core_->data.getLastResult();
	
	result = calc_core::nearly_equal(result, 0.0, std::fabs(core_->data.getUnary())) ? 0.0 : result;
	
	QString str_result{};
	str_result.setNum(result, core_->config.disp_format, Config::display_prec);
	
	curr_display_->setText(str_result);
}

// Square button [x²].
void Calc::squareButtonPressed()
{
	const dbl_ptr square = [](const double x){ return std::pow(x, 2); };
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(square);
}

// Square root button [√‾].
void Calc::sqrtButtonPressed()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(std::sqrt);
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
		const QString init_txt = QString::number(core_->config.init_value);
		curr_display_->setText(init_txt);
	}
}

// Clearing the display and buffer with [C] button.
void Calc::clearButtonPressed()
{
	curr_display_->setText(QString::number(core_->config.init_value));
	core_->data.reset();
}

// Changing display value sign with [±] button.
void Calc::signButtonPressed()
{
	// Reset [=] presses count.
	core_->data.resetSubsequentEqualPresses();

	// Remove or add minus sign on display.	
	QString curr_value = curr_display_->text();
	QString new_value;
	
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

	if (core_->data.getMemory() == curr_value.toDouble())
	{
		core_->data.resetMemory();
		ui->statusbar->showMessage("Memory cleaned.", 2000);
	}
	else
	{
		ui->statusbar->showMessage("Memory recalled.", 2000);
	}

	curr_display_->setText(QString::number(core_->data.getMemory()));
}

void Calc::memAddButtonPressed()
{
	const double curr_value = curr_display_->text().toDouble();
	core_->data.addToMemory(curr_value);
	ui->statusbar->showMessage("Added to memory.", 2000);	
}

void Calc::memSubButtonPressed()
{
	const double curr_value = curr_display_->text().toDouble();
	core_->data.subtractFromMemory(curr_value);
	ui->statusbar->showMessage("Subtracted from memory.", 2000);
}
