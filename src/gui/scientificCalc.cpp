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

///////////////////////////////////////////////////////////
//	SCIENTIFIC BUTTONS									 //
///////////////////////////////////////////////////////////

void Calc::piButtonPressed() const
{
	QString pi_str{};
	pi_str.setNum(std::numbers::pi, core_->config.disp_format, Config::display_prec);
	curr_display_->setText(pi_str);
}

void Calc::eButtonPressed() const
{
	QString e_str{};
	e_str.setNum(std::numbers::e, core_->config.disp_format, Config::display_prec);
	curr_display_->setText(e_str);
}

void Calc::randButtonPressed() const
{
	const auto rand = core::rand();
	const auto rand_str = core_->toQString(rand);
	
	curr_display_->setText(rand_str);
}

void Calc::logBase2ButtonPressed() const
{	
	core_->data.takeUnaryFromDisp(curr_display_);
	
	const auto res = core_->performUnaryOperation(core::log2);
	const auto res_str = core_->toQString(res);
	
	curr_display_->setText(res_str);
}

void Calc::logBase10ButtonPressed() const
{
	core_->data.takeUnaryFromDisp(curr_display_);

	const auto res = core_->performUnaryOperation(std::log10);
	const auto res_str = core_->toQString(res);
	
	curr_display_->setText(res_str);
}

void Calc::lnButtonPressed() const
{
	core_->data.takeUnaryFromDisp(curr_display_);

	const auto res = core_->performUnaryOperation(std::log);
	const auto res_str = core_->toQString(res);
	
	curr_display_->setText(res_str);
}

void Calc::factorialButtonPressed() const
{
	core_->data.takeUnaryFromDisp(curr_display_);

	const auto res = core_->performUnaryOperation(core::real_fact);
	const auto res_str = core_->toQString(res);
	
	curr_display_->setText(res_str);
}

void Calc::expButtonPressed() const
{		
	core_->data.takeUnaryFromDisp(curr_display_);

	const auto res = core_->performUnaryOperation(core::exp);
	const auto res_str = core_->toQString(res);
	
	curr_display_->setText(res_str);
}

void Calc::e10ToXButtonPressed() const
{
	core_->data.takeUnaryFromDisp(curr_display_);

	const auto res = core_->performUnaryOperation(core::_10_to_x);
	const auto res_str = core_->toQString(res);
	
	curr_display_->setText(res_str);
}

void Calc::absButtonPressed() const
{
	core_->data.takeUnaryFromDisp(curr_display_);

	const auto res = core_->performUnaryOperation(std::fabs);
	const auto res_str = core_->toQString(res);
	
	curr_display_->setText(res_str);
}

void Calc::inverseButtonPressed() const
{
	core_->data.takeUnaryFromDisp(curr_display_);
	
	try
	{
		const auto res = core_->performUnaryOperation(std::fabs);
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
//	SCIENTIFIC FUNCTIONS (MENU BAR)						 //
///////////////////////////////////////////////////////////

void Calc::sinClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(std::sin);
}

void Calc::cosClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(std::cos);
}

void Calc::tanClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);

	// Factor is display value or pi (whichever is greater) because modulo precision
	// depends on those two (and pi decision is constant).
	[[unlikely]] if (core::nearly_equal(std::cos(core_->data.getUnary()), 0.0, std::fabs(core_->data.getUnary())))
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
	core_->data.takeUnaryFromDisp(curr_display_);

	// Factor is display value or pi (whichever is greater) because modulo precision
	// depends on those two (and pi decision is constant).
	[[unlikely]] if (core::nearly_equal(std::sin(core_->data.getUnary()), 0.0, std::fabs(core_->data.getUnary())))
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
	core_->data.takeUnaryFromDisp(curr_display_);
	
	[[unlikely]] if (core::nearly_equal(std::cos(core_->data.getUnary()), 0.0, std::fabs(core_->data.getUnary())))
	{
		ui->statusbar->showMessage("Secant is indeterminate for multiples of pi/2!", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(sec);
	}
}

void Calc::cscClicked()
{
	const dbl_ptr csc = [](const double r) { return 1 / std::sin(r); };
	core_->data.takeUnaryFromDisp(curr_display_);
	
	[[unlikely]] if (core::nearly_equal(std::sin(core_->data.getUnary()), 0.0, std::fabs(core_->data.getUnary())))
	{
		ui->statusbar->showMessage("Secant is indeterminate for multiples of pi!", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(csc);		
	}
}

void Calc::arcsinClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	
	[[unlikely]] if (core_->data.getUnary() < -1 || core_->data.getUnary() > 1)
	{
		ui->statusbar->showMessage("Arcsine is only definite in [-1, 1]", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(std::asin);
	}
}

void Calc::arccosClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	
	[[unlikely]] if (core_->data.getUnary() < -1 || core_->data.getUnary() > 1)
	{
		ui->statusbar->showMessage("Arccosine is only definite in [-1, 1]", 2000);
		curr_display_->setText("Err");
	}
	else
	{
		performUnaryOperation(std::acos);
	}
}

void Calc::arctanClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(std::atan);
}

void Calc::arccotClicked()
{
	const dbl_ptr arccot = [](const double r) -> double { return (std::numbers::pi / 2) - std::atan(r); };
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(arccot);
}

void Calc::arcsecClicked()
{
	const dbl_ptr arcsec = [](const double r) -> double { return std::acos(1 / r ); };	
	core_->data.takeUnaryFromDisp(curr_display_);

	[[likely]] if (core_->data.getUnary() != 0)
	{
		[[likely]] if (const double curr_display_inverted_dbl = 1 / core_->data.getUnary();
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

void Calc::sinhClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(std::sinh);
}

void Calc::coshClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(std::cosh);
}

void Calc::tanhClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(std::tanh);
}

void Calc::cothClicked()
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

void Calc::sechClicked()
{
	const dbl_ptr sech = [](const double r) noexcept -> double { return 1 / std::coshl(r); };
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(sech);
}

void Calc::cschClicked()
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

void Calc::arsinhClicked()
{
	core_->data.takeUnaryFromDisp(curr_display_);
	performUnaryOperation(std::asinh);
}

void Calc::arcoshClicked()
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

void Calc::artanhClicked()
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

void Calc::arcothClicked()
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

void Calc::arsechClicked()
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

void Calc::arcschClicked()
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