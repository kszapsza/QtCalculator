//
// Created by kszap on 18.08.2020.
//
#pragma once
#include "./core/enums.h"
#include "./core/systems.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	core/data.h
///////////////////////////////////////////////////////////
*/

enum class operation;
enum class mode;
enum class numeric_systems;

class Data
{
	// Allows to perform sequential operations such as 2*2*2 = 8
	bool sequential_operation{ false };
	// Allows to perform sequential operations such as 2*3[=][=][=] = 54.
	std::uint8_t subsequent_equal_presses{ 0 };

	double last_result{ 0.0 };
	double lhs{ 0.0 };
	double rhs{ 1.0 };
	double unary{ 0.0 };

	// Data::memory for [MRC], [M+], [M−] buttons.
	double memory{ 0.0 };

	// Operation decision memory for binary operations.
	operation op_decision{ operation::none };

	// Currently used numeric system.
	numeric_systems numsys{ numeric_systems::dec };

public:

	// TODO: encapsulating calc_mode field
	// Current calc mode.
	mode calc_mode{ mode::basic };

/// GETTERS ///

	[[nodiscard]] bool isInSequentialOperation() const
	{
		return sequential_operation;
	}
	[[nodiscard]] std::uint8_t getSubsequentEqualPresses() const
	{
		return subsequent_equal_presses;
	}
	[[nodiscard]] double getLastResult() const
	{
		return last_result;
	}
	[[nodiscard]] double getLhs() const
	{
		return lhs;
	}
	[[nodiscard]] double getRhs() const
	{
		return rhs;
	}
	[[nodiscard]] double getUnary() const
	{
		return unary;
	}
	[[nodiscard]] double getMemory() const
	{
		return memory;
	}
	[[nodiscard]] operation getOpDecision() const
	{
		return op_decision;
	}
	[[nodiscard]] numeric_systems getNumsys() const
	{
		return numsys;
	}

/// SETTERS ///

#ifdef CALC_TESTS
	void setLhs(const double lhs)							{ this->lhs = lhs; }
	void setRhs(const double rhs)							{ this->rhs = rhs; }
	void setUnary(const double unary)						{ this->unary = unary; }
#endif

	// Gets display state and changes number system if neccessary to perform calculations.
	[[nodiscard]] double inputFormatter(const QLineEdit* const display) const
	{
		auto display_std_str = display->text().toStdString();

		switch (getNumsys())
		{
		default:
		case numeric_systems::dec:
			return display->text().toDouble();
		case numeric_systems::bin:
			return core::bin_dec(display_std_str);
		case numeric_systems::hex:
			return core::hex_dec(display_std_str);
		case numeric_systems::oct:
			return core::oct_dec(display_std_str);
		}
	}

	// We only want to set values in data if shown on display!
	void takeLhsFromDisp(const QLineEdit* const disp)
	{
		lhs = inputFormatter(disp);
	}
	void takeRhsFromDisp(const QLineEdit* const disp)
	{
		rhs = inputFormatter(disp);
	}
	void takeUnaryFromDisp(const QLineEdit* const disp)
	{
		unary = inputFormatter(disp);
	}

	void setLastResult(const double result)
	{
		this->last_result = result;
	}
	void setOpDecision(const operation op)
	{
		op_decision = op;
	}

	void beginSequential()
	{
		sequential_operation = true;
	}
	void endSequential()
	{
		sequential_operation = false;
	}

	void subsequentEqualPressesIncrement()
	{
		++subsequent_equal_presses;
	}
	void resetSubsequentEqualPresses()
	{
		subsequent_equal_presses = 0;
	}

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

	void resetNumsys()
	{
		numsys = numeric_systems::dec;
	}

	void setNumsys(const numeric_systems new_numsys)
	{
		numsys = new_numsys;
	}

	void addToMemory(const double mem)
	{
		memory += mem;
	}
	void subtractFromMemory(const double mem)
	{
		memory -= mem;
	}
	void resetMemory()
	{
		memory = 0.0;
	}
};