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

///////////////////////////////////////////////////////////
//	SCIENTIFIC BUTTONS									 //
///////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////
//	SCIENTIFIC FUNCTIONS (MENU BAR)						 //
///////////////////////////////////////////////////////////

void Calc::sinClicked()
{
	performUnaryOperation(std::sin);
}

void Calc::cosClicked()
{
	performUnaryOperation(std::cos);
}

void Calc::tanClicked()
{
	performUnaryOperation(std::tan);
}

void Calc::cotClicked()
{
	const ldbl_ptr ctg = [](const long double r) { return 1 / std::tan(r); };
	
	[[likely]] if (std::tan(curr_display_->text().toDouble()) != 0)
	{		
		performUnaryOperation(ctg);
	}
	else
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::secClicked()
{
	const ldbl_ptr sec = [](const long double r) { return 1 / std::cos(r); };
	
	[[likely]] if (std::cos(curr_display_->text().toDouble()) != 0)
	{
		performUnaryOperation(sec);
	}
	else
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::cscClicked()
{
	const ldbl_ptr csc = [](const long double r) { return 1 / std::sin(r); };
	const auto curr_display_dbl = curr_display_->text().toDouble();
	
	[[likely]] if (std::sin(curr_display_dbl) != 0)
	{
		performUnaryOperation(csc);		
	}
	else
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arcsinClicked()
{
	const auto curr_display_dbl = curr_display_->text().toDouble();
	
	[[likely]] if (curr_display_dbl >= -1 && curr_display_dbl <= 1)
	{
		performUnaryOperation(std::asin);
	}
	else
	{
		ui->statusbar->showMessage("Arcsine is only definite in [-1, 1]", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arccosClicked()
{
	const auto curr_display_dbl = curr_display_->text().toDouble();
	
	[[likely]] if (curr_display_dbl >= -1 && curr_display_dbl <= 1)
	{
		performUnaryOperation(std::acos);
	}
	else
	{
		ui->statusbar->showMessage("Arccosine is only definite in [-1, 1]", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arctanClicked()
{
	performUnaryOperation(std::atan);
}

void Calc::arccotClicked()
{
	const ldbl_ptr arccot = [](const ldbl r) -> ldbl { return Constants::pi_2 - std::atan(r); };
	performUnaryOperation(arccot);
}

void Calc::arcsecClicked()
{
	const ldbl_ptr arcsec = [](const ldbl r) -> ldbl { return std::acos(1 / r ); };	
	const double curr_display_dbl = curr_display_->text().toDouble();	

	[[likely]] if (curr_display_dbl != 0)
	{
		[[likely]] if (const double curr_display_inverted_dbl = 1 / curr_display_dbl;
			curr_display_inverted_dbl >= -1 && curr_display_inverted_dbl <= 1)
		{
			performUnaryOperation(arcsec);
		}
		else
		{
			ui->statusbar->showMessage("Arcsecant is only definite in "
				" (-infty, -1) u (1, +infty)", 2000);
			curr_display_->setText("Err");
		}
	}
	else
	{
		ui->statusbar->showMessage("Arcsecant is only definite in "
			"(-infty, -1) u (1, +infty)", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arccscClicked()
{
	const ldbl_ptr arccsc = [](const ldbl r) -> ldbl { return std::asin(1 / r ); };	
	const double curr_display_dbl = curr_display_->text().toDouble();

	[[likely]] if (curr_display_dbl != 0)
	{
		[[likely]] if (const double curr_display_inverted_dbl = 1 / curr_display_dbl;
			curr_display_inverted_dbl >= -1 && curr_display_inverted_dbl <= 1)
		{
			performUnaryOperation(arccsc);
		}
		else
		{
			ui->statusbar->showMessage("Arccosecant is only definite in "
				"(-infty, -1) u (1, +infty)", 2000);
			curr_display_->setText("Err");
		}
	}
	else
	{
		ui->statusbar->showMessage("Arccosecant is only definite in "
			"(-infty, -1) u (1, +infty)", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::sinhClicked()
{
	performUnaryOperation(std::sinhl);
}

void Calc::coshClicked()
{
	performUnaryOperation(std::coshl);
}

void Calc::tanhClicked()
{
	performUnaryOperation(std::tanhl);
}

void Calc::cothClicked()
{
	const ldbl_ptr coth = [](const ldbl r) -> ldbl { return std::coshl(r) / std::sinhl(r); };
	const double curr_display_dbl = curr_display_->text().toDouble();

	[[likely]] if (std::sinhl(curr_display_dbl) != 0)
	{
		performUnaryOperation(coth);
	}
	else
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::sechClicked()
{
	const ldbl_ptr sech = [](const ldbl r) noexcept -> ldbl { return 1 / std::coshl(r); };	
	performUnaryOperation(sech);
}

void Calc::cschClicked()
{
	const ldbl_ptr csch = [](const ldbl r) -> ldbl { return 1 / std::sinhl(r); };
	const double curr_display_dbl = curr_display_->text().toDouble();

	[[likely]] if (std::sinhl(curr_display_dbl) != 0)
	{
		performUnaryOperation(csch);
	}
	else
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arsinhClicked()
{
	performUnaryOperation(std::asinhl);
}

void Calc::arcoshClicked()
{
	const double curr_display_dbl = curr_display_->text().toDouble();
	
	[[likely]] if (curr_display_dbl >= 1)
	{
		performUnaryOperation(std::acoshl);
	}
	else
	{
		ui->statusbar->showMessage("Area hyperbolic cosinus is only "
			"definite in [1, infty]", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::artanhClicked()
{
	const double curr_display_dbl = curr_display_->text().toDouble();
	
	[[likely]] if (curr_display_dbl > -1 && curr_display_dbl < 1)
	{
		performUnaryOperation(std::atanhl);
	}
	else
	{
		ui->statusbar->showMessage("Area hyperbolic tangent is only "
			"definite in (-1, 1)", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arcothClicked()
{
	const ldbl_ptr arcoth = [](const ldbl r) -> ldbl
	{
		return 0.5 * std::log((r+1)/(r-1));
	};
	
	const double curr_display_dbl = curr_display_->text().toDouble();
	
	[[likely]] if (curr_display_dbl < -1 || curr_display_dbl > 1)
	{
		performUnaryOperation(arcoth);
	}
	else
	{
		ui->statusbar->showMessage("Area hyperbolic cotangent is only "
			"definite in (-infty, -1) u (1, infty)", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arsechClicked()
{
	const ldbl_ptr arsech = [](const ldbl r) -> ldbl
	{
		return std::log(std::sqrt((1/r) - 1) * std::sqrt((1/r) + 1) + (1/r));
	};

	const double curr_display_dbl = curr_display_->text().toDouble();

	[[likely]] if (curr_display_dbl > 0 && curr_display_dbl <= 1)
	{
		performUnaryOperation(arsech);
	}
	else
	{
		ui->statusbar->showMessage("Area hyperbolic secant is only "
			"definite in (0, 1]", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arcschClicked()
{
	const ldbl_ptr arcsch = [](const ldbl r) -> ldbl
	{
		return std::log(std::sqrt(1 + (1 / (r*r))) + (1/r));
	};

	const double curr_display_dbl = curr_display_->text().toDouble();

	[[likely]] if (curr_display_dbl != 0)
	{
		performUnaryOperation(arcsch);
	}
	else
	{
		ui->statusbar->showMessage("Area hyperbolic cosecant is "
			"indefinite for 0", 2000);
		curr_display_->setText("Err");
	}
}