#pragma once
#include <random>

#include <QLineEdit>
#include <QString>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 	
 	core/core.h
///////////////////////////////////////////////////////////
*/

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

/// CONFIGURATION ///

struct Config
{
	double init_value{ 0.0 };
	mode init_mode{ mode::scientific };
	char disp_format{ 'g' };
	static constexpr int display_prec{ 16 };
};

/// DATA ///

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

#ifdef CALC_TESTS
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

struct CalcCore
{
	Data data{};
	Config config{};

	CalcCore() { loadConfig(); }
	void loadConfig();	
	
	double performBinaryOperation() const;
	double performBinaryPercentOperation() const;
	double performUnaryOperation(double (*func)(double));
	QString toQString(double dbl_result) const;
	double round(double dbl_result) const;
};