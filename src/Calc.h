#ifndef CALC_H
#define CALC_H

#ifndef CALC_TESTS
#include "./ui_Calc.h"
#else
// ?
#endif // CALC_TESTS

#include <QMainWindow>
#include <QActionGroup>
#include <QLineEdit>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 	
 	Calc.h
 	Calc class main header.
///////////////////////////////////////////////////////////
*/

QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

/// TYPEDEFS ///

#define CONSTANT static constexpr double
typedef double (*dbl_ptr)(double);

/// UTILITY FUNCTIONS ///

// Compares if two floats (a, b) are nearly equal with precision of epsilon
// automatically multiplied by a or b, whichever is greater.
// This won't work accurately enough if a and b precision depends on
// some previous operations, use second overload with custom factor instead then.
//
// Gives satisfying results indepentently of order of magnitude of pair (a, b),
// but may work unexpectedly if their *individual* order of magnitude differs strongly.

template<typename Float>
bool nearly_equal(const Float a, const Float b)
	requires std::is_floating_point_v<Float>
{
	return std::abs(std::abs(a) - std::abs(b))
		<= std::numeric_limits<Float>::epsilon() * std::max(std::abs(a), std::abs(b));
}

// Compares if two floats (a, b) are nearly equal with precision of epsilon
// multiplied by custom factor (eps_factor). Useful, if either a or b
// precision is already result of some previous operation, consider:
// 
//	a = std::sin(x), then epsilon factor might be set to std::fabs(x), or e.g.:
//	b = std::fmod(x, y), then std::max(std::fabs(x), std::fabs(y)) may be used
//	as a coefficient.
//
// Gives satisfying results indepentently of order of magnitude of pair (a, b),
// but may work unexpectedly if their *individual* order of magnitude differs strongly.

template<typename Float>
bool nearly_equal(const Float a, const Float b, const Float eps_factor)
	requires std::is_floating_point_v<Float>
{
	return std::abs(std::abs(a) - std::abs(b))
		<= std::numeric_limits<Float>::epsilon() * eps_factor;
}

/// ENUMERATION TYPES ///

enum class operation : int
{
	none = 0, division = 1, multiplication = 2, subtraction = 3,
	addition = 4, log_base_y = 5, modulo = 6, power = 7
};

enum class mode : int
{
	basic = 0, scientific = 1
};

/// STRUCTURES ///

struct Config
{
	double init_value{ 0.0 };
	mode init_mode{ mode::scientific };
	char disp_format{ 'g' };

	// Higher precision doesn't make sense for doubles,
	// lower precision causes severe problems with functions.
	static constexpr int display_prec{ 18 };
};

class Data
{
	// Allows to perform sequential operations such as 2*2*2 = 8
	bool sequential_operation{ false };	
	// Allows to perform sequential operations such as 2*3[=][=][=] = 54.
	uint8_t subsequent_equal_presses{ 0 };

	double last_result{ 0.0 };
	double lhs{ 0.0 };
	double rhs{ 1.0 };
	double unary{ 0.0 };

	// Data::memory for [MRC], [M+], [M−] buttons.
	double memory{ 0.0 };

	// Operation decision memory for binary operations.
	operation op_decision{ operation::none };

public:

/// GETTERS ///

	[[nodiscard]] bool isInSequentialOperation() const		{ return sequential_operation; }
	[[nodiscard]] uint8_t getSubsequentEqualPresses() const	{ return subsequent_equal_presses; }
	[[nodiscard]] double getLastResult() const				{ return last_result; }
	[[nodiscard]] double getLhs() const						{ return lhs; }
	[[nodiscard]] double getRhs() const						{ return rhs; }
	[[nodiscard]] double getUnary() const					{ return unary; }
	[[nodiscard]] double getMemory() const					{ return memory; }
	[[nodiscard]] operation getOpDecision() const			{ return op_decision; }

/// SETTERS ///

#ifdef CALC_TESTS // Unit tests only!
	void setLhs(const double lhs)							{ this->lhs = lhs; }
	void setRhs(const double rhs)							{ this->rhs = rhs; }
	void setUnary(const double unary)						{ this->unary = unary; }
#endif	

	// We only want to set values in data if shown on display!
	void takeLhsFromDisp(const QLineEdit* const disp) 		{ lhs = disp->text().toDouble(); }
	void takeRhsFromDisp(const QLineEdit* const disp)		{ rhs = disp->text().toDouble(); }
	void takeUnaryFromDisp(const QLineEdit* const disp)		{ unary = disp->text().toDouble(); }

	void setLastResult(const double result)					{ this->last_result = result; }
	void setOpDecision(const operation op)					{ op_decision = op; }

	void beginSequential()									{ sequential_operation = true; }
	void endSequential()									{ sequential_operation = false; }

	void subsequentEqualPressesIncrement()					{ ++subsequent_equal_presses; }
	void resetSubsequentEqualPresses()						{ subsequent_equal_presses = 0; }

	void reset()
	{
		sequential_operation = false;
		subsequent_equal_presses = 0;
		last_result = 0.0;
		lhs = 0.0;
		rhs = 1.0;
		unary = 0.0;
		memory = 0.0;
		op_decision = operation::none;
	}
		
	void addToMemory (const double mem)						{ memory += mem; }
	void subtractFromMemory (const double mem)				{ memory -= mem; }
	void resetMemory()										{ memory = 0.0; }
};

/// CALC ///

class Calc final : public QMainWindow
{
    Q_OBJECT

public:
	explicit Calc(QWidget *parent = nullptr);
    ~Calc() override;
		
	Data data_;
	
private:
    Ui::Calc *ui;
	Config config_{};
	
	QActionGroup* calc_modes_;
	QLineEdit* curr_display_;

	void loadConfig();

	[[nodiscard]] QString performBinaryOperation();	
	void performUnaryOperation(dbl_ptr func);

	friend class Settings;

private slots:
	
// basicCalc.cpp
	
	void numButtonPressed();
	void commaButtonPressed();	
	void mathButtonPressed();
	
	void equalButtonPressed();
	void percentButtonPressed();	

	void squareButtonPressed();
	void sqrtButtonPressed();

	void backspaceButtonPressed() const;
	void clearButtonPressed();
	void signButtonPressed();

	void memButtonPressed();
	void memAddButtonPressed();
	void memSubButtonPressed();

	void menuFileOptions();
	void menuViewBasicTriggered();
	void menuViewScientificTriggered();

// scientificCalc.cpp

	void piButtonPressed() const;
	void eButtonPressed() const;
	void randButtonPressed();
	
	void logBase2ButtonPressed();
	void logBase10ButtonPressed();
	void lnButtonPressed();

	void factorialButtonPressed();	
	void expButtonPressed();
	void e10ToXButtonPressed();
	
	void absButtonPressed();
	void inverseButtonPressed();

	void sinClicked();
	void cosClicked();
	void tanClicked();
	void cotClicked();
	void secClicked();
	void cscClicked();

	void arcsinClicked();
	void arccosClicked();
	void arctanClicked();
	void arccotClicked();
	void arcsecClicked();
	void arccscClicked();

	void sinhClicked();
	void coshClicked();
	void tanhClicked();
	void cothClicked();
	void sechClicked();
	void cschClicked();

	void arsinhClicked();
	void arcoshClicked();
	void artanhClicked();
	void arcothClicked();
	void arsechClicked();
	void arcschClicked();
};
#endif // CALC_H