#include <cmath>

#include <QFile>
#include <QTextStream>

#include "basicCore.h"

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
	
// Evaluates unary operation from data_.unary and shows result.
double CalcCore::performUnaryOperation(const dbl_ptr func)
{
	data.resetSubsequentEqualPresses();
	data.setLastResult(static_cast<double>(func(data.getUnary())));
	
	// Round to zero if unary result is less than epsilon.
	double result = data.getLastResult();		
	result = calc_core::nearly_equal(result, 0.0, std::fabs(data.getUnary())) ? 0.0 : result;
	
	return result;
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