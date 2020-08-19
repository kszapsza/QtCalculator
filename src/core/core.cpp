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

// Result formatter rounding result and changing number system if neccessary.
[[nodiscard]] QString CalcCore::resultFormatter(double result) const
{
	QString converted_qstr{};

	if (data.calc_mode == mode::programmer)
	{
		auto int_result{ static_cast<std::int64_t>(result) };

		switch (data.getNumsys())
		{
		case numeric_systems::dec:
			converted_qstr = QString::fromStdString(std::to_string(int_result));
			break;
		case numeric_systems::bin:
			converted_qstr = QString::fromStdString(core::dec_bin(int_result));
			break;
		case numeric_systems::hex:
			converted_qstr = QString::fromStdString(core::dec_hex(int_result));
			break;
		case numeric_systems::oct:
			converted_qstr = QString::fromStdString(core::dec_oct(int_result));
			break;
		}
	}
	else
	{
		switch (data.getNumsys())
		{
		case numeric_systems::dec:
			converted_qstr.setNum(result, config.disp_format, Config::display_prec);
			break;
		case numeric_systems::bin:
			converted_qstr = QString::fromStdString(core::dec_bin(result));
			break;
		case numeric_systems::hex:
			converted_qstr = QString::fromStdString(core::dec_hex(result));
			break;
		case numeric_systems::oct:
			converted_qstr = QString::fromStdString(core::dec_oct(result));
			break;
		}
	}

	return converted_qstr;
}

// Core function performing operation stored in buffer.
// Used both by [=] button and math buttons.
double CalcCore::performBinaryOperation() const
{
	double result{};
	QString str_result{};

	switch (data.getOpDecision())
	{
	case operation::none:
	default:
		break;
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
	case operation::none:
	default:
		break;
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
	}

	return result;
}

// Evaluates unary operation from data.unary and shows result.
double CalcCore::performUnaryOperation(const std::function<double(double)>& func)
{
	data.resetSubsequentEqualPresses();
	
	auto result = static_cast<double>(func(data.getUnary()));

	// For trigonometric functions	
	if (core::nearly_equal(result, 0.0, std::fabs(data.getUnary()) * 2))
	{
		result = 0.0;
	}
	if (core::nearly_equal(result, 0.5, std::fabs(data.getUnary()) * 2))
	{
		result = 0.5;
	}
	
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