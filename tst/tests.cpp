#define CALC_TESTS

#include <numbers>

#include <QApplication>
#include <gtest/gtest.h>

#include "core/core.h"
#include "core/utility.h"
#include "gui/Calc.h"

namespace calc_tests
{
	namespace binary
	{
		TEST(division, one_by_zero)
		{
			auto core = std::make_unique<CalcCore>();
			
			core->data.setLhs(1);
			core->data.setRhs(0);
			core->data.setOpDecision(operation::division);
			
			EXPECT_ANY_THROW(core->performBinaryOperation());
		}
		TEST(division, one_by_two)
		{
			auto core = std::make_unique<CalcCore>();
			
			core->data.setLhs(1);
			core->data.setRhs(2);
			core->data.setOpDecision(operation::division);
			
			const double result_dbl = core->performBinaryOperation();
			const QString result = core->toQString(result_dbl);
			
			ASSERT_EQ(result, "0.5");
		}
		TEST(division, one_by_three)
		{
			auto core = std::make_unique<CalcCore>();
			
			core->data.setLhs(1);
			core->data.setRhs(3);
			core->data.setOpDecision(operation::division);
			
			const double result_dbl = core->performBinaryOperation();
			const QString result = core->toQString(result_dbl);
			
			QString expected{};
			expected.setNum(1.0 / 3.0, core->config.disp_format, Config::display_prec);
			
			ASSERT_EQ(result, expected);
		}
	}

	namespace unary
	{
	}

	namespace functions
	{
		TEST(sin, sin_0)
		{
			auto core = std::make_unique<CalcCore>();

			core->data.setUnary(0);			
			const double res = core->performUnaryOperation(std::sin);
			
			const QString actual = core->toQString(res);			
			const QString expected{ "0" };

			ASSERT_EQ(actual, expected) << "\n\n\n"
				<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
		}
		TEST(sin, sin_pi_6)
		{
			auto core = std::make_unique<CalcCore>();
			
			const double pi_rounded = core->round(std::numbers::pi);
			core->data.setUnary(core->round(pi_rounded / 6));
			
			const double res = core->performUnaryOperation(std::sin);			
			const QString actual = core->toQString(res);			
			const QString expected{ "0.5" };

			ASSERT_EQ(actual, expected) << "\n\n\n"
				<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
		}
		TEST(sin, sin_pi_2)
		{
			auto core = std::make_unique<CalcCore>();
			
			const double pi_rounded = core->round(std::numbers::pi);
			core->data.setUnary(core->round(pi_rounded / 2));
			
			const double res = core->performUnaryOperation(std::sin);			
			const QString actual = core->toQString(res);			
			const QString expected{ "1" };

			ASSERT_EQ(actual, expected) << "\n\n\n"
				<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
		}
		TEST(sin, sin_pi)
		{
			auto core = std::make_unique<CalcCore>();
			
			const double pi_rounded = core->round(std::numbers::pi);
			core->data.setUnary(pi_rounded);
			
			const double res = core->performUnaryOperation(std::sin);			
			const QString actual = core->toQString(res);			
			const QString expected{ "0" };

			ASSERT_EQ(actual, expected) << "\n\n\n"
				<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
		}		
		
		TEST(tan, tan_0)
		{
			auto core = std::make_unique<CalcCore>();
			core->data.setUnary(0);
			
			const double res = core->performUnaryOperation(core::tan);			
			const QString actual = core->toQString(res);			
			const QString expected{ "0" };

			ASSERT_EQ(actual, expected) << "\n\n\n"
				<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
		}
		TEST(tan, tan_pi_2)
		{			
			auto core = std::make_unique<CalcCore>();
			
			const double pi_rounded = core->round(std::numbers::pi);
			core->data.setUnary(core->round(pi_rounded / 2));

			EXPECT_ANY_THROW(core->performUnaryOperation(core::tan));
		}
		TEST(tan, tan_pi_2_mult)
		{
			auto core = std::make_unique<CalcCore>();
			
			const double pi_rounded = core->round(std::numbers::pi);
			core->data.setUnary(core->round(pi_rounded * 15.5));

			EXPECT_ANY_THROW(core->performUnaryOperation(core::tan));
		}
		TEST(tan, tan_pi_2_big)
		{
			auto core = std::make_unique<CalcCore>();
			
			const double pi_rounded = core->round(std::numbers::pi);
			core->data.setUnary(core->round(pi_rounded * 15000.5));

			EXPECT_ANY_THROW(core->performUnaryOperation(core::tan));
		}
		TEST(tan, tan_pi)
		{
			auto core = std::make_unique<CalcCore>();

			const double pi_rounded = core->round(std::numbers::pi);
			core->data.setUnary(pi_rounded);
			
			const double res = core->performUnaryOperation(core::tan);			
			const QString actual = core->toQString(res);			
			const QString expected{ "0" };

			ASSERT_EQ(actual, expected) << "\n\n\n"
				<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
		}		
	}
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}