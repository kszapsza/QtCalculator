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
	performUnaryOperation(log2);
}

void Calc::logBase10ButtonPressed()
{
	performUnaryOperation(log10);
}

void Calc::lnButtonPressed()
{
	performUnaryOperation(log);
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
	performUnaryOperation(fabs);
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