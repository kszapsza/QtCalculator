//
// Created by kszap on 20.08.2020.
//
#pragma once
#include <string>

namespace core
{
	void remove_leading_zeroes(std::string& str);

	double land(std::int64_t lhs, std::int64_t rhs);
	std::int64_t lor(std::int64_t lhs, std::int64_t rhs);
	std::int64_t lnot(std::int64_t unary);
	std::int64_t lnand(std::int64_t lhs, std::int64_t rhs);
	std::int64_t lnor(std::int64_t lhs, std::int64_t rhs);
	std::int64_t lxor(std::int64_t lhs, std::int64_t rhs);
}