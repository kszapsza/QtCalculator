//
// Created by kszap on 20.08.2020.
//

#include "bitwise.h"
#include <bitset>

namespace core
{
	double land(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);
		return std::bitset<64>(bit_lhs & bit_rhs).to_ullong();;
	}

	std::int64_t lor(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);
		return std::bitset<64>(bit_lhs | bit_rhs).to_ullong();
	}

	std::int64_t lnot(const std::int64_t unary)
	{
		std::bitset<64> bit_unary(unary);
		return std::bitset<64>(~bit_unary).to_ullong();
	}

	std::int64_t lnand(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);
		return std::bitset<64>(~(bit_lhs & bit_rhs)).to_ullong();
	}

	std::int64_t lnor(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);
		return std::bitset<64>(~(bit_lhs | bit_rhs)).to_ullong();
	}

	std::int64_t lxor(const std::int64_t lhs, const std::int64_t rhs)
	{
		std::bitset<64> bit_lhs(lhs);
		std::bitset<64> bit_rhs(rhs);
		return std::bitset<64>(bit_lhs ^ bit_rhs).to_ullong();
	}
}