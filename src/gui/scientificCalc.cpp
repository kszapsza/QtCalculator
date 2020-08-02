#include "Calc.h"
#include "./ui_Calc.h"

#include <cmath>
#include <random>
#include <chrono>
#include <numbers>
#include <stdexcept>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	scientificCalc.cpp
 	Calc definitions specific for Scientific mode.
///////////////////////////////////////////////////////////
*/

// Calls core functions saving input from display, performs requested operation,
// converts result to QString and catches possible runtime exceptions.
void Calc::unaryButtonPressed(const dbl_ptr func) const
{
	core_->data.takeUnaryFromDisp(curr_display_);

	try
	{
		const auto res = core_->performUnaryOperation(func);
		const auto res_str = core_->toQString(res);
		curr_display_->setText(res_str);
	}
	catch (const std::runtime_error& except)
	{
		curr_display_->setText("Err");
		ui->statusbar->showMessage(except.what(), 2000);
	}
}

///////////////////////////////////////////////////////////
//	SCIENTIFIC BUTTONS									 //
///////////////////////////////////////////////////////////

// Inserts pi.
void Calc::piButtonPressed() const
{
	QString pi_str{};
	pi_str.setNum(std::numbers::pi, core_->config.disp_format, Config::display_prec);
	curr_display_->setText(pi_str);
}

// Inserts e.
void Calc::eButtonPressed() const
{
	QString e_str{};
	e_str.setNum(std::numbers::e, core_->config.disp_format, Config::display_prec);
	curr_display_->setText(e_str);
}

// Generates random number from 0 to 1.
void Calc::randButtonPressed() const
{
	const auto rand = core::rand();
	const auto rand_str = core_->toQString(rand);
	
	curr_display_->setText(rand_str);
}

void Calc::logBase2ButtonPressed() const
{	
	unaryButtonPressed(core::log2);
}

void Calc::logBase10ButtonPressed() const
{
	unaryButtonPressed(std::log10);
}

void Calc::lnButtonPressed() const
{
	unaryButtonPressed(std::log);
}

void Calc::factorialButtonPressed() const
{
	unaryButtonPressed(core::real_fact);
}

void Calc::expButtonPressed() const
{		
	unaryButtonPressed(core::exp);
}

void Calc::e10ToXButtonPressed() const
{
	unaryButtonPressed(core::_10_to_x);
}

void Calc::absButtonPressed() const
{
	unaryButtonPressed(std::fabs);
}

void Calc::inverseButtonPressed() const
{
	unaryButtonPressed(std::fabs);
}

///////////////////////////////////////////////////////////
//	SCIENTIFIC FUNCTIONS (MENU BAR)						 //
///////////////////////////////////////////////////////////

void Calc::sinClicked() const
{
	unaryButtonPressed(std::sin);
}

void Calc::cosClicked() const
{
	unaryButtonPressed(std::cos);
}

void Calc::tanClicked() const
{
	unaryButtonPressed(core::tan);
}

void Calc::cotClicked() const
{
	unaryButtonPressed(core::cot);
}

void Calc::secClicked() const
{
	unaryButtonPressed(core::sec);
}

void Calc::cscClicked() const
{
	unaryButtonPressed(core::csc);
}

void Calc::arcsinClicked() const
{
	unaryButtonPressed(core::asin);
}

void Calc::arccosClicked() const
{
	unaryButtonPressed(core::asin);
}

void Calc::arctanClicked() const
{
	unaryButtonPressed(std::atan);
}

void Calc::arccotClicked() const
{
	unaryButtonPressed(core::acot);
}

void Calc::arcsecClicked() const
{
	unaryButtonPressed(core::asec);
}

void Calc::arccscClicked() const
{
	const dbl_ptr arccsc = [](const double r) -> double { return std::asin(1 / r ); };	
	core_->data.takeUnaryFromDisp(curr_display_);

	[[likely]] if (core_->data.getUnary() != 0)
	{
		[[likely]] if (const double curr_display_inverted_dbl = 1 / core_->data.getUnary();
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

void Calc::sinhClicked() const
{
	unaryButtonPressed(std::sinh);
}

void Calc::coshClicked() const
{
	unaryButtonPressed(std::cosh);
}

void Calc::tanhClicked() const
{
	unaryButtonPressed(std::tanh);
}

void Calc::cothClicked() const
{
	const dbl_ptr coth = [](const double r) -> double { return std::cosh(r) / std::sinh(r); };
	core_->data.takeUnaryFromDisp(curr_display_);

	[[likely]] if (std::sinhl(core_->data.getUnary()) != 0)
	{
		performUnaryOperation(coth);
	}
	else
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::sechClicked() const
{
	const dbl_ptr sech = [](const double r) noexcept -> double { return 1 / std::coshl(r); };
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(sech);
}

void Calc::cschClicked() const
{
	const dbl_ptr csch = [](const double r) -> double { return 1.0 / std::sinh(r); };
	core_->data.takeUnaryFromDisp(curr_display_);

	[[likely]] if (std::sinhl(core_->data.getUnary()) != 0)
	{
		performUnaryOperation(csch);
	}
	else
	{
		ui->statusbar->showMessage("Cannot divide by zero!", 2000);
		curr_display_->setText("Err");
	}
}

void Calc::arsinhClicked() const
{
	unaryButtonPressed(std::asinh);
}

void Calc::arcoshClicked() const
{
	core_->data.takeUnaryFromDisp(curr_display_);
	
	[[unlikely]] if (core_->data.getUnary() < 1)
	{
		ui->statusbar->showMessage("Area hyperbolic cosinus is only "
		                           "definite in [1, infty]", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(std::acosh);
	}
}

void Calc::artanhClicked() const
{
	core_->data.takeUnaryFromDisp(curr_display_);
	
	[[unlikely]] if (core_->data.getUnary() <= -1 || core_->data.getUnary() >= 1)
	{
		ui->statusbar->showMessage("Area hyperbolic tangent is only "
		                           "definite in (-1, 1)", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(std::atanh);
	}
}

void Calc::arcothClicked() const
{
	const dbl_ptr arcoth = [](const double r) -> double
	{
		return 0.5 * std::log((r+1)/(r-1));
	};
	
	core_->data.takeUnaryFromDisp(curr_display_);
	
	[[unlikely]] if (core_->data.getUnary() >= -1 && core_->data.getUnary() <= 1)
	{
		ui->statusbar->showMessage("Area hyperbolic cotangent is only "
		                           "definite in (-infty, -1) u (1, infty)", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(arcoth);
	}
}

void Calc::arsechClicked() const
{
	const dbl_ptr arsech = [](const double r) -> double
	{
		return std::log(std::sqrt((1/r) - 1) * std::sqrt((1/r) + 1) + (1/r));
	};

	core_->data.takeUnaryFromDisp(curr_display_);

	[[unlikely]] if (core_->data.getUnary() <= 0 || core_->data.getUnary() > 1)
	{
		ui->statusbar->showMessage("Area hyperbolic secant is only "
		                           "definite in (0, 1]", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(arsech);
	}
}

void Calc::arcschClicked() const
{
	const dbl_ptr arcsch = [](const double r) -> double
	{
		return std::log(std::sqrt(1 + (1 / (r*r))) + (1/r));
	};

	core_->data.takeUnaryFromDisp(curr_display_);

	[[unlikely]] if (core_->data.getUnary() == 0)
	{
		ui->statusbar->showMessage("Area hyperbolic cosecant is "
		                           "indefinite for 0", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(arcsch);
	}
}