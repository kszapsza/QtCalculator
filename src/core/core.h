#pragma once
#include <random>

#include <QLineEdit>
#include <QString>

#include "./core/data.h"
#include "./core/enums.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 	
 	core/core.h
///////////////////////////////////////////////////////////
*/

/// CONFIGURATION ///

struct Config
{
	double init_value{ 0.0 };
	mode init_mode{ mode::scientific };
	char disp_format{ 'g' };
	static constexpr int display_prec{ 16 };
};

struct CalcCore
{
	Data data{};
	Config config{};

	CalcCore()
	{
		loadConfig();
	}
	void loadConfig();

	[[nodiscard]] QString resultFormatter(double result) const;

	[[nodiscard]] QString performBinaryOperation() const;
	[[nodiscard]] QString performBinaryPercentOperation() const;
	[[nodiscard]] double performUnaryOperation(const std::function<double(double)>& func);

	[[nodiscard]] QString toQString(double dbl_result) const;
	[[nodiscard]] double round(double dbl_result) const;
};