//
// Created by kszap on 17.08.2020.
//

#include <gtest/gtest.h>
#include "core/systems.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	tst/tests.cpp
 	Unit tests for core implementation of number systems
 	conversions: decimal/binary/octal/hexadecimal.
///////////////////////////////////////////////////////////
*/

namespace calc_tests::numeric_systems
{
	namespace from_dec
	{
		// *** *** DEC -> BIN *** *** //

		TEST(dec_to_bin, zero)
		{
			EXPECT_EQ(dec_bin(0), "0");
		}
		TEST(dec_to_bin, one)
		{
			EXPECT_EQ(dec_bin(1), "1");
		}
		TEST(dec_to_bin, small1)
		{
			EXPECT_EQ(dec_bin(42), "101010");
		}
		TEST(dec_to_bin, small2)
		{
			EXPECT_EQ(dec_bin(194), "11000010");
		}
		TEST(dec_to_bin, big1)
		{
			EXPECT_EQ(dec_bin(154001), "100101100110010001");
		}
		TEST(dec_to_bin, big2)
		{
			EXPECT_EQ(dec_bin(654098), "10011111101100010010");
		}
		TEST(dec_to_bin, huge1)
		{
			EXPECT_EQ(dec_bin(2564999787), "10011000111000101100101001101011");
		}
		TEST(dec_to_bin, huge2)
		{
			EXPECT_EQ(dec_bin(192564999787), "10110011010101110001001011011001101011");
		}

		// *** *** DEC -> OCT *** *** //

		TEST(dec_to_oct, zero)
		{
			EXPECT_EQ(dec_oct(0), "0");
		}
		TEST(dec_to_oct, one)
		{
			EXPECT_EQ(dec_oct(1), "1");
		}
		TEST(dec_to_oct, two)
		{
			EXPECT_EQ(dec_oct(2), "2");
		}
		TEST(dec_to_oct, three)
		{
			EXPECT_EQ(dec_oct(3), "3");
		}
		TEST(dec_to_oct, four)
		{
			EXPECT_EQ(dec_oct(4), "4");
		}
		TEST(dec_to_oct, five)
		{
			EXPECT_EQ(dec_oct(5), "5");
		}
		TEST(dec_to_oct, six)
		{
			EXPECT_EQ(dec_oct(6), "6");
		}
		TEST(dec_to_oct, seven)
		{
			EXPECT_EQ(dec_oct(7), "7");
		}
		TEST(dec_to_oct, small1)
		{
			EXPECT_EQ(dec_oct(42), "52");
		}
		TEST(dec_to_oct, small2)
		{
			EXPECT_EQ(dec_oct(194), "302");
		}
		TEST(dec_to_oct, big1)
		{
			EXPECT_EQ(dec_oct(154001), "454621");
		}
		TEST(dec_to_oct, big2)
		{
			EXPECT_EQ(dec_oct(654098), "2375422");
		}
		TEST(dec_to_oct, huge1)
		{
			EXPECT_EQ(dec_oct(2564999787), "23070545153");
		}
		TEST(dec_to_oct, huge2)
		{
			EXPECT_EQ(dec_oct(192564999787), "2632561133153");
		}

		// *** *** DEC -> HEX *** *** //

		TEST(dec_to_hex, zero)
		{
			EXPECT_EQ(dec_hex(0), "0");
		}
		TEST(dec_to_hex, one)
		{
			EXPECT_EQ(dec_hex(1), "1");
		}
		TEST(dec_to_hex, two)
		{
			EXPECT_EQ(dec_hex(2), "2");
		}
		TEST(dec_to_hex, three)
		{
			EXPECT_EQ(dec_hex(3), "3");
		}
		TEST(dec_to_hex, four)
		{
			EXPECT_EQ(dec_hex(4), "4");
		}
		TEST(dec_to_hex, five)
		{
			EXPECT_EQ(dec_hex(5), "5");
		}
		TEST(dec_to_hex, six)
		{
			EXPECT_EQ(dec_hex(6), "6");
		}
		TEST(dec_to_hex, seven)
		{
			EXPECT_EQ(dec_hex(7), "7");
		}
		TEST(dec_to_hex, eight)
		{
			EXPECT_EQ(dec_hex(8), "8");
		}
		TEST(dec_to_hex, nine)
		{
			EXPECT_EQ(dec_hex(9), "9");
		}
		TEST(dec_to_hex, ten)
		{
			EXPECT_EQ(dec_hex(10), "a");
		}
		TEST(dec_to_hex, eleven)
		{
			EXPECT_EQ(dec_hex(11), "b");
		}
		TEST(dec_to_hex, twelve)
		{
			EXPECT_EQ(dec_hex(12), "c");
		}
		TEST(dec_to_hex, thirteen)
		{
			EXPECT_EQ(dec_hex(13), "d");
		}
		TEST(dec_to_hex, fourteen)
		{
			EXPECT_EQ(dec_hex(14), "e");
		}
		TEST(dec_to_hex, fiveteen)
		{
			EXPECT_EQ(dec_hex(15), "f");
		}
		TEST(dec_to_hex, small1)
		{
			EXPECT_EQ(dec_hex(42), "2a");
		}
		TEST(dec_to_hex, small2)
		{
			EXPECT_EQ(dec_hex(194), "c2");
		}
		TEST(dec_to_hex, big1)
		{
			EXPECT_EQ(dec_hex(154001), "25991");
		}
		TEST(dec_to_hex, big2)
		{
			EXPECT_EQ(dec_hex(654098), "9fb12");
		}
		TEST(dec_to_hex, huge1)
		{
			EXPECT_EQ(dec_hex(2564999787), "98e2ca6b");
		}
		TEST(dec_to_hex, huge2)
		{
			EXPECT_EQ(dec_hex(192564999787), "2cd5c4b66b");
		}
	}

	namespace from_bin
	{

	}
}