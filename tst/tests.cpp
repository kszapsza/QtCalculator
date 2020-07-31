#define CALC_TESTS

#include "gtest/gtest.h"
#include "./Calc.h"

namespace calc_tests
{
	namespace binary
	{
		/*TEST(division_test, zero)
		{
			Calc calc{ nullptr };
			calc.data.lhs = 1;
			calc.data.rhs = 0;
			calc.data.op_decision = operation::division;
			
			const auto result = calc.performBinaryOperation();
			EXPECT_TRUE(result == "Err");
		}*/
		TEST(test, test_karwa)
		{
			EXPECT_TRUE(0 == 0);
		}
	}

	namespace unary
	{
		
	}
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}