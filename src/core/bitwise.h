//
// Created by kszap on 20.08.2020.
//
#pragma once
#include <string>

namespace core
{
	void remove_leading_zeroes(std::string& str);

	std::string land(std::int64_t lhs, std::int64_t rhs);
	std::string lor(std::int64_t lhs, std::int64_t rhs);
	std::string lnot(std::int64_t unary);
	std::string lnand(std::int64_t lhs, std::int64_t rhs);
	std::string lnor(std::int64_t lhs, std::int64_t rhs);
	std::string lxor(std::int64_t lhs, std::int64_t rhs);
}