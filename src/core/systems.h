//
// Created by kszap on 17.08.2020.
//
#pragma once
#include <string>

namespace core
{
	std::string dec_bin(std::int64_t dec);
	std::string dec_hex(std::int64_t dec);
	std::string dec_oct(std::int64_t dec);

	std::int64_t bin_dec(std::string& bin);
	std::string bin_oct(std::string& bin);
	std::string bin_hex(std::string& bin);

	std::int64_t hex_dec(std::string& hex);
	std::string hex_bin(std::string& hex);
	std::string hex_oct(std::string& hex);

	std::int64_t oct_dec(std::string& oct);
	std::string oct_bin(std::string& hex);
	std::string oct_hex(std::string& hex);
}