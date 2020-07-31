#define CALC_TESTS

#include <numbers>
#include <QApplication>
#include <gtest/gtest.h>

#include "Calc.h"

// Emulates how does display round values using Config::display_prec.
[[nodiscard]] QString disp_rounding(const double num)
{
	QString res{};
	return res.setNum(num, 'g', Config::display_prec);
}

namespace calc_tests
{
	namespace binary
	{
		TEST(division, one_by_zero)
		{			
			Calc calc{ nullptr };
			calc.data_.setLhs(1);
			calc.data_.setRhs(0);
			calc.data_.setOpDecision(operation::division);
			
			const auto result = calc.performBinaryOperation();
			ASSERT_EQ(result, "Err");
		}

		TEST(division, one_by_two)
		{
			Calc calc{ nullptr };
			calc.data_.setLhs(1);
			calc.data_.setRhs(2);
			calc.data_.setOpDecision(operation::division);
			
			const auto result = calc.performBinaryOperation();
			ASSERT_EQ(result, "0.5");
		}

		TEST(division, one_by_three)
		{
			Calc calc{ nullptr };
			calc.data_.setLhs(1);
			calc.data_.setRhs(3);
			calc.data_.setOpDecision(operation::division);
			
			const auto result = calc.performBinaryOperation();
			
			QString expected{};
			expected.setNum(1.0 / 3.0, calc.config_.disp_format, Config::display_prec);
			
			ASSERT_EQ(result, expected);
		}
	}

	namespace unary
	{
	}

	namespace functions
	{
		TEST(tan, tan_0)
		{
			Calc calc{ nullptr };
			calc.menuViewScientificTriggered(); // just in case

			calc.getCurrDisplay()->setText(disp_rounding(0));
			
			calc.tanClicked();
			const QString actual{calc.getCurrDisplay()->text()};
			const QString expected{"0"};
			
			ASSERT_EQ(actual, expected);
		}
		
		TEST(tan, tan_pi_2)
		{
			Calc calc{ nullptr };
			calc.menuViewScientificTriggered(); // just in case

			// Prepare pi rounded like the Calc display does!
			const auto pi = disp_rounding(std::numbers::pi).toDouble();
			calc.getCurrDisplay()->setText(disp_rounding(pi / 2));
			
			calc.tanClicked();
			const QString actual{calc.getCurrDisplay()->text()};
			const QString expected{"Err"};
			
			ASSERT_EQ(actual, expected);
		}
		
		TEST(tan, tan_pi_2_mult)
		{
			Calc calc{ nullptr };
			calc.menuViewScientificTriggered(); // just in case

			// Prepare pi rounded like the Calc display does!
			const double pi = disp_rounding(std::numbers::pi).toDouble();
			calc.getCurrDisplay()->setText(disp_rounding(pi * 15.5));
			
			calc.tanClicked();
			const QString actual{calc.getCurrDisplay()->text()};
			const QString expected{"Err"};
			
			ASSERT_EQ(actual, expected);
		}

		TEST(tan, tan_pi_2_big)
		{
			Calc calc{ nullptr };
			calc.menuViewScientificTriggered(); // just in case

			// Prepare pi rounded like the Calc display does!
			const double pi = disp_rounding(std::numbers::pi).toDouble();
			calc.getCurrDisplay()->setText(disp_rounding(pi * 15000.5));
			
			calc.tanClicked();
			const QString actual{calc.getCurrDisplay()->text()};
			const QString expected{"Err"};
			
			ASSERT_EQ(actual, expected);
		}

		TEST(tan, tan_pi)
		{
			Calc calc{ nullptr };
			calc.menuViewScientificTriggered(); // just in case

			calc.getCurrDisplay()->setText(disp_rounding(std::numbers::pi));
			
			calc.tanClicked();
			const QString actual{calc.getCurrDisplay()->text()};
			const QString expected{"0"};
			
			ASSERT_EQ(actual, expected);
		}
	}
}

int main(int argc, char *argv[])
{	
	QApplication a(argc, argv);
	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}