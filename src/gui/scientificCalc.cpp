#include <numbers>
#include <stdexcept>

#include "./ui_Calc.h"
#include "./gui/Calc.h"
#include "./core/core.h"
#include "./core/utility.h"

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
	unaryButtonPressed(core::acsc);
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
	unaryButtonPressed(core::coth);
}

void Calc::sechClicked() const
{
	unaryButtonPressed(core::sech);
}

void Calc::cschClicked() const
{
	unaryButtonPressed(core::csch);
}

void Calc::arsinhClicked() const
{
	unaryButtonPressed(std::asinh);
}

void Calc::arcoshClicked() const
{
	unaryButtonPressed(core::acosh);
}

void Calc::artanhClicked() const
{
	unaryButtonPressed(core::atanh);
}

void Calc::arcothClicked() const
{
	unaryButtonPressed(core::acoth);
}

void Calc::arsechClicked() const
{
	unaryButtonPressed(core::asech);
}

void Calc::arcschClicked() const
{
	unaryButtonPressed(core::acsch);
}