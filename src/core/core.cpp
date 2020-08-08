#include <cmath>
#include <stdexcept>

#include <QFile>
#include <QTextStream>

#include "./core/core.h"
#include "./core/utility.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 	
 	core/core.cpp
///////////////////////////////////////////////////////////
*/

void CalcCore::loadConfig()
{
	QFile config_file("config.dat");	

	if (config_file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream config_str(&config_file);
		auto nl_flush = [&](){ char nl{}; config_str >> nl; };

		config_str >> config.init_value;

		int init_mode_in{};
		config_str >> init_mode_in;
		config.init_mode = static_cast<mode>(init_mode_in);

		nl_flush();			
		config_str >> config.disp_format;
		nl_flush();
	}

	config_file.close();
}

// Core function performing operation stored in buffer.
// Used both by [=] button and math buttons.
double CalcCore::performBinaryOperation() const
{
	double result{};
	QString str_result{};

	switch (data.getOpDecision())
	{
	case operation::division:
		if (data.getRhs() == 0)
			throw std::runtime_error("Can't divide by zero!");
		else
			result = data.getLhs() / data.getRhs();
		break;
	case operation::multiplication:
		result = data.getLhs() * data.getRhs();
		break;
	case operation::subtraction:
		result = data.getLhs() - data.getRhs();
		break;
	case operation::addition:
		result = data.getLhs() + data.getRhs();
		break;
	case operation::log_base_y:
		if (const auto denom = std::log(data.getRhs()); denom == 0)
			throw std::runtime_error("Can't divide by zero!");
		else
			result = std::log(data.getLhs()) / denom;
		break;
	case operation::modulo:
		result = static_cast<int>(data.getLhs()) % static_cast<int>(data.getRhs());
		break;
	case operation::power:
		result = std::pow(data.getLhs(), data.getRhs());
		break;
	case operation::none:
	default:
		break;
	}

	return result;
}

double CalcCore::performBinaryPercentOperation() const
{
	double result{};
	QString str_result{};
	
	union
	{
		double percentage_fraction{};
		double percentage_of_lhs;
	};

	switch (data.getOpDecision())
	{
	case operation::division:
		percentage_fraction = data.getRhs() / 100;
		[[unlikely]] if (percentage_fraction == 0)			
			throw std::runtime_error("Can't divide by zero!");
		else
			result = data.getLhs() / percentage_fraction;
		break;
	case operation::multiplication:
		percentage_fraction = data.getRhs() / 100;
		result = data.getLhs() * percentage_fraction;
		break;
	case operation::subtraction:
		percentage_of_lhs = (data.getRhs() / 100) * data.getLhs();
		result = data.getLhs() - percentage_of_lhs;
		break;
	case operation::addition:
		percentage_of_lhs = (data.getRhs() / 100) * data.getLhs();
		result = data.getLhs() + percentage_of_lhs;
		break;
	case operation::none:		
	default:
		break;
	}

	return result;
}

// Evaluates unary operation from data_.unary and shows result.
double CalcCore::performUnaryOperation(double (*func)(double))
{
	data.resetSubsequentEqualPresses();
	
	auto result = static_cast<double>(func(data.getUnary()));

	if (core::nearly_equal(result, 0.0, std::fabs(data.getUnary())))
		result = 0.0;
	
	data.setLastResult(result);	
	return result;
}

QString CalcCore::toQString(const double dbl_result) const
{
	QString str_result{};
	return str_result.setNum(dbl_result, config.disp_format, Config::display_prec);
}

double CalcCore::round(const double dbl_result) const
{
	QString str_result{};
	return str_result.setNum(dbl_result, config.disp_format, Config::display_prec).toDouble();
}