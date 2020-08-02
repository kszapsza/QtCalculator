#include <cmath>

#include <QFile>
#include <QTextStream>

#include "basicCore.h"

#include <stdexcept>

namespace core
{
	// Generates random real number between 0 and 1.
	double rand()
	{
		const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
	    std::minstd_rand eng(seed);
		return static_cast<double>(eng()) / std::minstd_rand::max();
	}

	// Evaluates log base 2 logarithm.
	inline double log2(const double r)
	{
		return std::log(r) / std::log(2.0);
	}

	// Evaluates factorial for any real number.
	inline double real_fact(const double r)
	{
		return std::tgamma(r + 1);
	}

	// Exponential function (e base).
	inline double exp(const double r)
	{
		return std::pow(std::numbers::e, r);
	}

	// Exponential function (10 base).
	inline double _10_to_x(const double r)
	{
		return std::pow(10, r);
	}

	// Evaluates 1/x.
	double inv(const double r)
	{
		[[unlikely]] if (r == 0)
			throw std::runtime_error("Can't divide by zero!");
		
		return 1 / r;		
	}

	double tan(const double r)
	{
		[[unlikely]] if (nearly_equal(std::cos(r), 0.0, std::fabs(r)))
			throw std::runtime_error("Tangent is indeterminate for multiples of pi/2!");
		
		return std::tan(r);
	}

	double cot(const double r)
	{
		[[unlikely]] if (nearly_equal(std::sin(r), 0.0, std::fabs(r)))
			throw std::runtime_error("Cotangent is indeterminate for multiples of pi!");
		
		return 1 / std::tan(r);
	}

	double sec(const double r)
	{
		[[unlikely]] if (nearly_equal(std::cos(r), 0.0, std::fabs(r)))
			throw std::runtime_error("Secant is indeterminate for multiples of pi/2!");
		
		return 1 / std::cos(r);
	}

	double csc(const double r)
	{
		[[unlikely]] if (nearly_equal(std::sin(r), 0.0, std::fabs(r)))
			throw std::runtime_error("Cosecant is indeterminate for multiples of pi!");
		
		return 1 / std::sin(r);
	}
}

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
[[nodiscard]] QString CalcCore::performBinaryOperation(const double lhs, const double rhs, const operation op)
{
	double result{};
	QString str_result{};
	bool err{ false };

	switch (op)
	{
	case operation::division:
		[[unlikely]] if (rhs == 0)
			err = true;
		else
			result = lhs / rhs;
		break;
	case operation::multiplication:
		result = lhs * rhs;
		break;
	case operation::subtraction:
		result = lhs - rhs;
		break;
	case operation::addition:
		result = lhs + rhs;
		break;
	case operation::log_base_y:
		[[unlikely]] if (const double denom = std::log(rhs); denom == 0)
			err = true;
		else
			result = std::log(lhs) / denom;
		break;
	case operation::modulo:
		result = static_cast<int>(lhs) % static_cast<int>(rhs);
		break;
	case operation::power:
		result = std::pow(lhs, rhs);
		break;
	case operation::none:
	default:
		break;
	}

	if (!err)
	{
		data.setLastResult(result);
		str_result.setNum(result, config.disp_format, Config::display_prec);
	}
	else
	{
		str_result = "Err";
		//ui->statusbar->showMessage("Cannot divide by zero!", 2000);
	}

	return str_result;
}

// Evaluates unary operation from data_.unary and shows result.
double CalcCore::performUnaryOperation(const dbl_ptr func)
{
	data.resetSubsequentEqualPresses();
	data.setLastResult(static_cast<double>(func(data.getUnary())));
	
	// Round to zero if unary result is less than epsilon.
	double result = data.getLastResult();		
	result = core::nearly_equal(result, 0.0, std::fabs(data.getUnary())) ? 0.0 : result;
	
	return result;
}

QString CalcCore::toQString(const double dbl_result) const
{
	QString str_result{};
	return str_result.setNum(dbl_result, config.disp_format, Config::display_prec);
}