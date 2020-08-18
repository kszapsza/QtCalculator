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

		TEST(dec_to_bin, basic)
		{
			EXPECT_EQ(dec_bin(0), "0");
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

		TEST(dec_to_oct, basic)
		{
			EXPECT_EQ(dec_oct(0), "0");
			EXPECT_EQ(dec_oct(1), "1");
			EXPECT_EQ(dec_oct(2), "2");
			EXPECT_EQ(dec_oct(3), "3");
			EXPECT_EQ(dec_oct(4), "4");
			EXPECT_EQ(dec_oct(5), "5");
			EXPECT_EQ(dec_oct(6), "6");
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

		TEST(dec_to_hex, basic)
		{
			EXPECT_EQ(dec_hex(0), "0");
			EXPECT_EQ(dec_hex(1), "1");
			EXPECT_EQ(dec_hex(2), "2");
			EXPECT_EQ(dec_hex(3), "3");
			EXPECT_EQ(dec_hex(4), "4");
			EXPECT_EQ(dec_hex(5), "5");
			EXPECT_EQ(dec_hex(6), "6");
			EXPECT_EQ(dec_hex(7), "7");
			EXPECT_EQ(dec_hex(8), "8");
			EXPECT_EQ(dec_hex(9), "9");
			EXPECT_EQ(dec_hex(10), "a");
			EXPECT_EQ(dec_hex(11), "b");
			EXPECT_EQ(dec_hex(12), "c");
			EXPECT_EQ(dec_hex(13), "d");
			EXPECT_EQ(dec_hex(14), "e");
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
		// *** *** BIN -> DEC *** *** //

		TEST(bin_to_dec, basic)
		{
			std::string str{};
			EXPECT_EQ(bin_dec(str = "0"), 0);
			EXPECT_EQ(bin_dec(str = "1"), 1);
		}
		TEST(bin_to_dec, syntax_except1)
		{
			std::string str{"2"};
			EXPECT_ANY_THROW(bin_dec(str));
		}
		TEST(bin_to_dec, syntax_except2)
		{
			std::string str{"010102"};
			EXPECT_ANY_THROW(bin_dec(str));
		}
		TEST(bin_to_dec, syntax_except3)
		{
			std::string str{"901010"};
			EXPECT_ANY_THROW(bin_dec(str));
		}
		TEST(bin_to_dec, ignore_0b)
		{
			std::string str_pref{"0b01010"};
			std::string str{"01010"};
			EXPECT_EQ(bin_dec(str_pref), bin_dec(str));
		}
		TEST(bin_to_dec, ignore_0B)
		{
			std::string str_pref{"0B01010"};
			std::string str{"01010"};
			EXPECT_EQ(bin_dec(str_pref), bin_dec(str));
		}
		TEST(bin_to_dec, small1)
		{
			std::string str{"101010"};
			EXPECT_EQ(bin_dec(str), 42);
		}
		TEST(bin_to_dec, small2)
		{
			std::string str{"11000010"};
			EXPECT_EQ(bin_dec(str), 194);
		}
		TEST(bin_to_dec, big1)
		{
			std::string str{"100101100110010001"};
			EXPECT_EQ(bin_dec(str), 154001);
		}
		TEST(bin_to_dec, big2)
		{
			std::string str{"10011111101100010010"};
			EXPECT_EQ(bin_dec(str), 654098);
		}
		TEST(bin_to_dec, huge1)
		{
			std::string str{"10011000111000101100101001101011"};
			EXPECT_EQ(bin_dec(str), 2564999787);
		}
		TEST(bin_to_dec, huge2)
		{
			std::string str{"10110011010101110001001011011001101011"};
			EXPECT_EQ(bin_dec(str), 192564999787);
		}
	}

	namespace from_hex
	{
		TEST(hex_to_dec, basic)
		{
			std::string str{};
			EXPECT_EQ(hex_dec(str = "0"), 0);
			EXPECT_EQ(hex_dec(str = "1"), 1);
			EXPECT_EQ(hex_dec(str = "2"), 2);
			EXPECT_EQ(hex_dec(str = "3"), 3);
			EXPECT_EQ(hex_dec(str = "4"), 4);
			EXPECT_EQ(hex_dec(str = "5"), 5);
			EXPECT_EQ(hex_dec(str = "6"), 6);
			EXPECT_EQ(hex_dec(str = "7"), 7);
			EXPECT_EQ(hex_dec(str = "8"), 8);
			EXPECT_EQ(hex_dec(str = "9"), 9);
			EXPECT_EQ(hex_dec(str = "a"), 10);
			EXPECT_EQ(hex_dec(str = "b"), 11);
			EXPECT_EQ(hex_dec(str = "c"), 12);
			EXPECT_EQ(hex_dec(str = "d"), 13);
			EXPECT_EQ(hex_dec(str = "e"), 14);
			EXPECT_EQ(hex_dec(str = "f"), 15);
		}
		TEST(hex_to_dec, syntax_except1)
		{
			std::string str{"p"};
			EXPECT_ANY_THROW(hex_dec(str));
		}
		TEST(hex_to_dec, syntax_except2)
		{
			std::string str{"abxd"};
			EXPECT_ANY_THROW(hex_dec(str));
		}
		TEST(hex_to_dec, syntax_except3)
		{
			std::string str{"XFHG"};
			EXPECT_ANY_THROW(hex_dec(str));
		}
		TEST(hex_to_dec, make_lowercase)
		{
			std::string str_upper{"ABCD"};
			std::string str_lower{"abcd"};
			EXPECT_EQ(hex_dec(str_upper), hex_dec(str_lower));
		}
		TEST(hex_to_dec, ignore_0x)
		{
			std::string str_pref{"0xAB2"};
			std::string str{"AB2"};
			EXPECT_EQ(hex_dec(str_pref), hex_dec(str));
		}
		TEST(hex_to_dec, ignore_0X)
		{
			std::string str_pref{"0XAB2"};
			std::string str{"AB2"};
			EXPECT_EQ(hex_dec(str_pref), hex_dec(str));
		}
		TEST(hex_to_dec, small1)
		{
			std::string str{"2A"};
			EXPECT_EQ(hex_dec(str), 42);
		}
		TEST(hex_to_dec, small2)
		{
			std::string str{"C2"};
			EXPECT_EQ(hex_dec(str), 194);
		}
		TEST(hex_to_dec, big1)
		{
			std::string str{"25991"};
			EXPECT_EQ(hex_dec(str), 154001);
		}
		TEST(hex_to_dec, big2)
		{
			std::string str{"9FB12"};
			EXPECT_EQ(hex_dec(str), 654098);
		}
		TEST(hex_to_dec, huge1)
		{
			std::string str{"98E2CA6B"};
			EXPECT_EQ(hex_dec(str), 2564999787);
		}
		TEST(hex_to_dec, huge2)
		{
			std::string str{"2CD5C4B66B"};
			EXPECT_EQ(hex_dec(str), 192564999787);
		}
	}

	namespace from_oct
	{
		TEST(oct_to_dec, basic)
		{
			std::string str{};
			EXPECT_EQ(oct_dec(str = "0"), 0);
			EXPECT_EQ(oct_dec(str = "1"), 1);
			EXPECT_EQ(oct_dec(str = "2"), 2);
			EXPECT_EQ(oct_dec(str = "3"), 3);
			EXPECT_EQ(oct_dec(str = "4"), 4);
			EXPECT_EQ(oct_dec(str = "5"), 5);
			EXPECT_EQ(oct_dec(str = "6"), 6);
			EXPECT_EQ(oct_dec(str = "7"), 7);
		}
		TEST(oct_to_dec, syntax_except1)
		{
			std::string str{"p"};
			EXPECT_ANY_THROW(oct_dec(str));
		}
		TEST(oct_to_dec, syntax_except2)
		{
			std::string str{"01287"};
			EXPECT_ANY_THROW(oct_dec(str));
		}
		TEST(oct_to_dec, syntax_except3)
		{
			std::string str{"XFHG"};
			EXPECT_ANY_THROW(oct_dec(str));
		}
		TEST(oct_to_dec, small1)
		{
			std::string str{"17"};
			EXPECT_EQ(oct_dec(str), 15);
		}
		TEST(oct_to_dec, small2)
		{
			std::string str{"32"};
			EXPECT_EQ(oct_dec(str), 26);
		}
		TEST(oct_to_dec, big1)
		{
			std::string str{"17421"};
			EXPECT_EQ(oct_dec(str), 7953);
		}
		TEST(oct_to_dec, big2)
		{
			std::string str{"712347"};
			EXPECT_EQ(oct_dec(str), 234727);
		}
		TEST(oct_to_dec, huge1)
		{
			std::string str{"77712347"};
			EXPECT_EQ(oct_dec(str), 16749799);
		}
		TEST(oct_to_dec, huge2)
		{
			std::string str{"777771725"};
			EXPECT_EQ(oct_dec(str), 134214613);
		}
	}
}