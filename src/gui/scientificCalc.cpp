#include <numbers>

#include "./ui_Calc.h"
#include "./gui/Calc.h"
#include "./core/core.h"
#include "./core/utility.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	gui/scientificCalc.cpp
 	Calc definitions specific for Scientific mode.
///////////////////////////////////////////////////////////
*/

///////////////////////////////////////////////////////////
//	SCIENTIFIC BUTTONS									 //
///////////////////////////////////////////////////////////

// Inserts pi.
void Calc::piButtonPressed()
{
	QString pi_str{};
	pi_str.setNum(std::numbers::pi, core_->config.disp_format, Config::display_prec);
	curr_display_->setText(pi_str);
	curr_display_input_mode_ = input_mode::substitute;
}

// Inserts e.
void Calc::eButtonPressed()
{
	QString e_str{};
	e_str.setNum(std::numbers::e, core_->config.disp_format, Config::display_prec);
	curr_display_->setText(e_str);
	curr_display_input_mode_ = input_mode::substitute;
}

// Generates random number from 0 to 1.
void Calc::randButtonPressed()
{
	const auto rand = core::rand();
	const auto rand_str = core_->resultFormatter(rand);

	curr_display_->setText(rand_str);
	curr_display_input_mode_ = input_mode::substitute;
}

void Calc::logBase2ButtonPressed()
{
	unaryButtonPressed(core::log2);
}

void Calc::logBase10ButtonPressed()
{
	unaryButtonPressed(std::log10l);
}

void Calc::lnButtonPressed()
{
	unaryButtonPressed(std::logl);
}

void Calc::factorialButtonPressed()
{
	unaryButtonPressed(core::real_fact);
}

void Calc::expButtonPressed()
{
	unaryButtonPressed(core::exp);
}

void Calc::e10ToXButtonPressed()
{
	unaryButtonPressed(core::_10_to_x);
}

void Calc::absButtonPressed()
{
	unaryButtonPressed(std::fabsl);
}

void Calc::inverseButtonPressed()
{
	unaryButtonPressed(core::inv);
}

///////////////////////////////////////////////////////////
//	SCIENTIFIC FUNCTIONS (MENU BAR)						 //
///////////////////////////////////////////////////////////

void Calc::sinClicked()
{
	unaryButtonPressed(std::sinl);
}

void Calc::cosClicked()
{
	unaryButtonPressed(std::cosl);
}

void Calc::tanClicked()
{
	unaryButtonPressed(core::tan);
}

void Calc::cotClicked()
{
	unaryButtonPressed(core::cot);
}

void Calc::secClicked()
{
	unaryButtonPressed(core::sec);
}

void Calc::cscClicked()
{
	unaryButtonPressed(core::csc);
}

void Calc::arcsinClicked()
{
	unaryButtonPressed(core::asin);
}

void Calc::arccosClicked()
{
	unaryButtonPressed(core::asin);
}

void Calc::arctanClicked()
{
	unaryButtonPressed(std::atanl);
}

void Calc::arccotClicked()
{
	unaryButtonPressed(core::acot);
}

void Calc::arcsecClicked()
{
	unaryButtonPressed(core::asec);
}

void Calc::arccscClicked()
{
	unaryButtonPressed(core::acsc);
}

void Calc::sinhClicked()
{
	unaryButtonPressed(std::sinhl);
}

void Calc::coshClicked()
{
	unaryButtonPressed(std::coshl);
}

void Calc::tanhClicked()
{
	unaryButtonPressed(std::tanhl);
}

void Calc::cothClicked()
{
	unaryButtonPressed(core::coth);
}

void Calc::sechClicked()
{
	unaryButtonPressed(core::sech);
}

void Calc::cschClicked()
{
	unaryButtonPressed(core::csch);
}

void Calc::arsinhClicked()
{
	unaryButtonPressed(std::asinhl);
}

void Calc::arcoshClicked()
{
	unaryButtonPressed(core::acosh);
}

void Calc::artanhClicked()
{
	unaryButtonPressed(core::atanh);
}

void Calc::arcothClicked()
{
	unaryButtonPressed(core::acoth);
}

void Calc::arsechClicked()
{
	unaryButtonPressed(core::asech);
}

void Calc::arcschClicked()
{
	unaryButtonPressed(core::acsch);
}