//
// Created by kszap on 20.08.2020.
//

#include "bitwise.h"
#include <bitset>

namespace core
{
	void remove_leading_zeroes(std::string &str)
	{
		str.erase(0, std::min(str.find('1'), str.size() - 1));
	}

	std::string land(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);

		std::string result_str = std::bitset<64>(bit_lhs & bit_rhs).to_string();
		remove_leading_zeroes(result_str);

		return result_str;
	}

	std::string lor(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);

		std::string result_str = std::bitset<64>(bit_lhs | bit_rhs).to_string();
		remove_leading_zeroes(result_str);

		return result_str;
	}

	std::string lnot(const std::int64_t unary)
	{
		std::bitset<64> bit_unary(unary);

		std::string result_str = std::bitset<64>(~bit_unary).to_string();
		remove_leading_zeroes(result_str);

		return result_str;
	}

	std::string lnand(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);

		std::string result_str = std::bitset<64>(~(bit_lhs & bit_rhs)).to_string();
		remove_leading_zeroes(result_str);

		return result_str;
	}

	std::string lnor(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);

		std::string result_str = std::bitset<64>(~(bit_lhs | bit_rhs)).to_string();
		remove_leading_zeroes(result_str);

		return result_str;
	}

	std::string lxor(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);

		std::string result_str = std::bitset<64>(bit_lhs ^ bit_rhs).to_string();
		remove_leading_zeroes(result_str);

		return result_str;
	}
}