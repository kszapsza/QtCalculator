#include "Calc.h"
#include "./ui_Calc.h"

#include <cmath>
#include <random>
#include <chrono>
#include <numbers>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	scientificCalc.cpp
 	Calc definitions specific for Scientific mode.
///////////////////////////////////////////////////////////
*/

template<typename T>
concept Float = std::is_floating_point_v<T>;

template<typename Float>
bool flpnt_equal(const Float a, const Float b)
	requires std::is_floating_point_v<Float>
{
	return std::abs(std::abs(a) - std::abs(b))
		<= std::numeric_limits<Float>::epsilon() * std::max(std::abs(a), std::abs(b));
}

template<typename Float>
bool flpnt_equal(const Float a, const Float b, const unsigned int factor)
	requires std::is_floating_point_v<Float>
{
	return std::abs(std::abs(a) - std::abs(b))
		<= std::numeric_limits<Float>::epsilon() * factor;
}

///////////////////////////////////////////////////////////
//	SCIENTIFIC BUTTONS									 //
///////////////////////////////////////////////////////////

void Calc::piButtonPressed() const
{
	QString pi_str{};
	pi_str.setNum(std::numbers::pi, config_.disp_format, Config::display_prec);
	curr_display_->setText(pi_str);
}

void Calc::eButtonPressed() const
{
	QString e_str{};
	e_str.setNum(std::numbers::e, config_.disp_format, Config::display_prec);
	curr_display_->setText(e_str);
}

void Calc::randButtonPressed()
{
	const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::minstd_rand eng(seed);

	const auto rand = static_cast<double>(eng()) / std::minstd_rand::max();
	data_.lhs = rand;

	QString rand_str{};
	rand_str.setNum(rand, config_.disp_format, Config::display_prec);
	curr_display_->setText(rand_str);
}

void Calc::logBase2ButtonPressed()
{
	const dbl_ptr log2_ldbl = [](const double r) -> double { return std::logl(r) / std::logl(2); };
	performUnaryOperation(log2_ldbl);
}

void Calc::logBase10ButtonPressed()
{
	performUnaryOperation(std::log10);
}

void Calc::lnButtonPressed()
{
	performUnaryOperation(std::log);
}

void Calc::factorialButtonPressed()
{
	const dbl_ptr real_fact = [](const double r) -> double { return std::tgamma(r + 1); };
	performUnaryOperation(real_fact);
}

void Calc::expButtonPressed()
{
	const dbl_ptr exp = [](const double r) -> double { return std::pow(std::numbers::e, r); };
	performUnaryOperation(exp);
}

void Calc::e10ToXButtonPressed()
{
	const dbl_ptr _10_to_x = [](const double r) -> double { return std::pow(10, r); };
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
		str_result.setNum(1 / data_.unary, config_.disp_format, Config::display_prec);
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
	const double curr_display_dbl = curr_display_->text().toDouble();

	// If input % pi == pi/2, raise an error.
	const double pi_modulo = std::fmod(curr_display_dbl, std::numbers::pi);

	// Factor is display value or pi (whichever is greater) because modulo precision
	// depends on those two (and pi decision is constant).
	[[unlikely]] if (flpnt_equal(std::fabs(pi_modulo), std::numbers::pi/2,
		std::max(std::fabs(curr_display_dbl), std::numbers::pi)))
	{
		curr_display_->setText("Err");
		ui->statusbar->showMessage("Tangent is indeterminate for multiples of pi/2!", 2000);
	}
	else
	{
		performUnaryOperation(std::tan);
	}
}

void Calc::cotClicked()
{
	const dbl_ptr cot = [](const double r) { return 1 / std::tan(r); };
	const auto curr_display_dbl = curr_display_->text().toDouble();

	// If input % pi == 0, raise an error.
	const double pi_modulo = std::fmod(curr_display_dbl, std::numbers::pi);

	// Factor is display value or pi (whichever is greater) because modulo precision
	// depends on those two (and pi decision is constant).
	[[unlikely]] if (flpnt_equal(std::fabs(pi_modulo), 0.0,
		std::max(std::fabs(curr_display_dbl), std::numbers::pi)))
	{		
		ui->statusbar->showMessage("Cotangent is indeterminate for multiples of pi!", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(cot);
	}
}

void Calc::secClicked()
{
	const dbl_ptr sec = [](const double r) { return 1 / std::cos(r); };
	const auto curr_display_dbl = curr_display_->text().toDouble();
	
	[[likely]] if (std::cos(curr_display_dbl) != 0)
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
	const dbl_ptr csc = [](const double r) { return 1 / std::sin(r); };
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
	const dbl_ptr arccot = [](const double r) -> double { return (std::numbers::pi / 2) - std::atan(r); };
	performUnaryOperation(arccot);
}

void Calc::arcsecClicked()
{
	const dbl_ptr arcsec = [](const double r) -> double { return std::acos(1 / r ); };	
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
	const dbl_ptr arccsc = [](const double r) -> double { return std::asin(1 / r ); };	
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
	performUnaryOperation(std::sinh);
}

void Calc::coshClicked()
{
	performUnaryOperation(std::cosh);
}

void Calc::tanhClicked()
{
	performUnaryOperation(std::tanh);
}

void Calc::cothClicked()
{
	const dbl_ptr coth = [](const double r) -> double { return std::coshl(r) / std::sinhl(r); };
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
	const dbl_ptr sech = [](const double r) noexcept -> double { return 1 / std::coshl(r); };	
	performUnaryOperation(sech);
}

void Calc::cschClicked()
{
	const dbl_ptr csch = [](const double r) -> double { return 1 / std::sinhl(r); };
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
	performUnaryOperation(std::asinh);
}

void Calc::arcoshClicked()
{
	const double curr_display_dbl = curr_display_->text().toDouble();
	
	[[likely]] if (curr_display_dbl >= 1)
	{
		performUnaryOperation(std::acosh);
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
		performUnaryOperation(std::atanh);
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
	const dbl_ptr arcoth = [](const double r) -> double
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
	const dbl_ptr arsech = [](const double r) -> double
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
	const dbl_ptr arcsch = [](const double r) -> double
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