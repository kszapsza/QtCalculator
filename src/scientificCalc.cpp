#include "Calc.h"
#include "./ui_Calc.h"

#include <cmath>
#include <random>
#include <chrono>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	scientificCalc.cpp
 	Calc definitions specific for Scientific mode.
///////////////////////////////////////////////////////////
*/

void Calc::piButtonPressed()
{
	QString pi_str{};
	pi_str.setNum(Constants::pi, config_.disp_format, config_.display_prec);
	curr_display_->setText(pi_str);
	data_.lhs = Constants::pi;
}

void Calc::eButtonPressed()
{
	QString e_str{};
	e_str.setNum(Constants::e, config_.disp_format, config_.display_prec);
	curr_display_->setText(e_str);
	data_.lhs = Constants::e;
}

void Calc::randButtonPressed()
{
	const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::minstd_rand eng(seed);

	const auto rand = static_cast<double>(eng()) / std::minstd_rand::max();
	data_.lhs = rand;

	QString rand_str{};
	rand_str.setNum(rand, config_.disp_format, config_.display_prec);
	curr_display_->setText(rand_str);
}

void Calc::logBase2ButtonPressed()
{
	const ldbl_ptr log2_ldbl = [](const ldbl r) -> ldbl { return std::logl(r) / std::logl(2); };
	performUnaryOperation(log2_ldbl);
}

void Calc::logBase10ButtonPressed()
{
	performUnaryOperation(std::log10l);
}

void Calc::lnButtonPressed()
{
	performUnaryOperation(std::logl);
}

void Calc::factorialButtonPressed()
{
	const ldbl_ptr real_fact = [](const ldbl r) -> ldbl { return std::tgamma(r + 1); };
	performUnaryOperation(real_fact);
}

void Calc::expButtonPressed()
{
	const ldbl_ptr exp = [](const ldbl r) -> ldbl { return std::pow(Constants::e, r); };
	performUnaryOperation(exp);
}

void Calc::e10ToXButtonPressed()
{
	const ldbl_ptr _10_to_x = [](const ldbl r) -> ldbl { return std::pow(10, r); };
	performUnaryOperation(_10_to_x);
}

void Calc::absButtonPressed()
{
	performUnaryOperation(std::fabs);
}

void Calc::inverseButtonPressed()
{
	// Save current display state as argument.
	data_.unary = curr_display_->text().toDouble();

	QString str_result{};
	
	[[unlikely]] if (data_.unary == 0)
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		str_result = "Err";
	}
	else
	{		
		// Reset [=] presses count.
		data_.subsequent_equal_presses = 0;

		// Evaluate and show inverted value.		
		str_result.setNum(1 / data_.unary, config_.disp_format, config_.display_prec);
	}
	
	curr_display_->setText(str_result);
}