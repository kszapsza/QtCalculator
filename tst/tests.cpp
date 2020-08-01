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

class CalcTests : public testing::Test
{
protected:
	Calc* calc = nullptr;
	
	void SetUp() override
	{
		calc = new Calc{};
	}

	void TearDown() override
	{
		delete calc;
	}
};

namespace calc_tests
{
	namespace binary
	{
		TEST_F(CalcTests, one_by_zero)
		{
			//auto calc = std::make_unique<Calc>(nullptr);
			
			calc->data_.setLhs(1);
			calc->data_.setRhs(0);
			calc->data_.setOpDecision(operation::division);
			
			const auto result = calc->performBinaryOperation();
			ASSERT_EQ(result, "Err");
		}
		TEST_F(CalcTests, one_by_two)
		{
			//auto calc = std::make_unique<Calc>(nullptr);
			
			calc->data_.setLhs(1);
			calc->data_.setRhs(2);
			calc->data_.setOpDecision(operation::division);
			
			const auto result = calc->performBinaryOperation();
			ASSERT_EQ(result, "0.5");
		}
		TEST_F(CalcTests, one_by_three)
		{
			//auto calc = std::make_unique<Calc>(nullptr);
			
			calc->data_.setLhs(1);
			calc->data_.setRhs(3);
			calc->data_.setOpDecision(operation::division);
			
			const auto result = calc->performBinaryOperation();
			
			QString expected{};
			expected.setNum(1.0 / 3.0, calc->config_.disp_format, Config::display_prec);
			
			ASSERT_EQ(result, expected);
		}
	}

	namespace unary
	{
	}

	namespace functions
	{
		namespace sine
		{
			TEST_F(CalcTests, sin_0)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				calc->getCurrDisplay()->setText(disp_rounding(0));

				calc->sinClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "0" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
			TEST_F(CalcTests, sin_pi_6)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				const double pi_rounded = disp_rounding(std::numbers::pi).toDouble();
				calc->getCurrDisplay()->setText(disp_rounding(pi_rounded / 6));

				calc->sinClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "0.5" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
			TEST_F(CalcTests, sin_pi_2)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				const double pi_rounded = disp_rounding(std::numbers::pi).toDouble();
				const QString pi_2_rounded = disp_rounding(pi_rounded / 2);

				calc->getCurrDisplay()->setText(pi_2_rounded);

				calc->sinClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "1" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
			TEST_F(CalcTests, sin_pi)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				calc->getCurrDisplay()->setText(disp_rounding(std::numbers::pi));

				calc->sinClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "0" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
		}
		
		namespace tangent
		{
			TEST_F(CalcTests, tan_0)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				calc->getCurrDisplay()->setText(disp_rounding(0));

				calc->tanClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "0" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
			TEST_F(CalcTests, tan_pi_2)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				// Prepare pi rounded like the Calc display does!
				const double pi_rounded = disp_rounding(std::numbers::pi).toDouble();
				const QString pi_2_rounded = disp_rounding(pi_rounded / 2);

				calc->getCurrDisplay()->setText(pi_2_rounded);

				calc->tanClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "Err" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
			TEST_F(CalcTests, tan_pi_2_mult)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				// Prepare pi rounded like the Calc display does!
				const double pi_rounded = disp_rounding(std::numbers::pi).toDouble();
				const QString pi_mult_rounded = disp_rounding(pi_rounded * 15.5);

				calc->getCurrDisplay()->setText(pi_mult_rounded);

				calc->tanClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "Err" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
			TEST_F(CalcTests, tan_pi_2_big)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				// Prepare pi rounded like the Calc display does!
				const double pi_rounded = disp_rounding(std::numbers::pi).toDouble();
				const QString pi_mult_rounded = disp_rounding(pi_rounded * 15000.5);

				calc->getCurrDisplay()->setText(pi_mult_rounded);

				calc->tanClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "Err" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
			TEST_F(CalcTests, tan_pi)
			{
				//auto calc = std::make_unique<Calc>(nullptr);
				calc->menuViewScientificTriggered(); // just in case

				calc->getCurrDisplay()->setText(disp_rounding(std::numbers::pi));

				calc->tanClicked();
				const QString actual{ calc->getCurrDisplay()->text() };
				const QString expected{ "0" };

				ASSERT_EQ(actual, expected) << "\n\n\n"
					<< "Expected: " << expected.toStdString() << "\nActual: " << actual.toStdString();
			}
		}
	}
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}