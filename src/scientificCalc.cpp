#include "Calc.h"
#include "./ui_Calc.h"

#include <cmath>
#include <random>
#include <chrono>

#ifdef QT_DEBUG
#include <QDebug>
#endif

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	basicCalc.cpp
 	Calc definitions for Scientific mode.
///////////////////////////////////////////////////////////
*/

void Calc::piButtonPressed() const
{
	QString pi_str{};
	pi_str.setNum(Constants::pi, config_.disp_format, config_.display_prec);
	curr_display_->setText(pi_str);
}

void Calc::eButtonPressed() const
{
	QString e_str{};
	e_str.setNum(Constants::e, config_.disp_format, config_.display_prec);
	curr_display_->setText(e_str);
}

void Calc::randButtonPressed() const
{
	const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::minstd_rand eng(seed);

	const auto rand = static_cast<double>(eng()) / std::minstd_rand::max();

	QString rand_str{};
	rand_str.setNum(rand, config_.disp_format, config_.display_prec);
	curr_display_->setText(rand_str);
}

void Calc::logBaseYButtonPressed()
{
}

void Calc::logBase2ButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Save current display state as base value.
	data_.unary = curr_display_->text().toDouble();

	// Evaluate and show log2.
	QString str_result{};
	str_result.setNum(log2(data_.unary), config_.disp_format, config_.display_prec);
	curr_display_->setText(str_result);
}

void Calc::logBase10ButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Save current display state as base value.
	data_.unary = curr_display_->text().toDouble();

	// Evaluate and show log10.
	QString str_result{};
	str_result.setNum(log10(data_.unary), config_.disp_format, config_.display_prec);
	curr_display_->setText(str_result);
}

void Calc::lnButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Save current display state as argument.
	data_.unary = curr_display_->text().toDouble();

	// Evaluate and show ln.
	QString str_result{};
	str_result.setNum(log(data_.unary), config_.disp_format, config_.display_prec);
	curr_display_->setText(str_result);
}

void Calc::factorialButtonPressed()
{
}

void Calc::moduloButtonPressed()
{
}

void Calc::expButtonPressed()
{
}

void Calc::e10ToXButtonPressed()
{
}

void Calc::xToYButtonPressed()
{
}

void Calc::absButtonPressed()
{
	// Reset [=] presses count.
	data_.subsequent_equal_presses = 0;
	
	// Save current display state as argument
	data_.unary = curr_display_->text().toDouble();

	// Evaluate and show absolute value.
	QString str_result{};
	str_result.setNum(fabs(data_.unary), config_.disp_format, config_.display_prec);
	curr_display_->setText(str_result);
}

void Calc::inverseButtonPressed()
{
	// Save current display state as argument.
	data_.unary = curr_display_->text().toDouble();

	QString str_result{};
	
	if (data_.unary != 0)
	{
		// Reset [=] presses count.
		data_.subsequent_equal_presses = 0;

		// Evaluate and show inverted value.		
		str_result.setNum(1 / data_.unary, config_.disp_format, config_.display_prec);		
	}
	else
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		str_result = "Err";
	}
	
	curr_display_->setText(str_result);
}