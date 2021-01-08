//
// Created by kszap on 17.08.2020.
//

#include "systems.h"

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	core/systems.cpp
 	Core implementation of number systems conversions:
 	decimal/binary/octal/hexadecimal.
///////////////////////////////////////////////////////////
*/

namespace core
{
	std::string dec_bin(std::string& dec)
	{
		const int dec_int = std::stoi(dec);
		return dec_bin(dec_int);
	}

	std::string dec_bin(std::int64_t dec)
	{
		std::string str = std::bitset<64>(dec).to_string();
		str.erase(0, std::min(str.find('1'), str.size() - 1));
		return str;
	}

	std::string dec_hex(std::string& dec)
	{
		const int dec_int = std::stoi(dec);
		return dec_hex(dec_int);
	}

	std::string dec_hex(const std::int64_t dec)
	{
		std::stringstream ss;
		ss << std::hex << dec;
		return ss.str();
	}

	std::string dec_oct(std::string& dec)
	{
		const int dec_int = std::stoi(dec);
		return dec_oct(dec_int);
	}

	std::string dec_oct(const std::int64_t dec)
	{
		std::stringstream ss;
		ss << std::oct << dec;
		return ss.str();
	}

	std::string from_dec(numeric_systems new_system, std::string& old_value)
	{
		switch (new_system)
		{
		default:
		case numeric_systems::dec:
			return old_value;
		case numeric_systems::bin:
			return dec_bin(old_value);
		case numeric_systems::hex:
			return dec_hex(old_value);
		case numeric_systems::oct:
			return dec_oct(old_value);
		}
	}

	std::int64_t bin_dec(std::string& bin)
	{
		if (bin.length() >= 2 && bin.at(0) == '0' && (bin.at(1) == 'b' || bin.at(1) == 'B'))
			bin.erase(0, 2);

		std::int64_t result = 0;
		std::int64_t power = 0;

		for (auto it = bin.rbegin(); it != bin.rend(); it++)
		{
			if (*it == '1' || *it == '0')
			{
				result += *it == '1' ? static_cast<std::int64_t>(std::pow(2, power)) : 0;
				power++;
			}
			else
			{
				throw std::runtime_error("Syntax error in binary notation: 0b" + bin + "!\n");
			}
		}

		return result;
	}

	std::string bin_oct(std::string& bin)
	{
		const std::int64_t dec = bin_dec(bin);
		return dec_oct(dec);
	}

	std::string bin_hex(std::string& bin)
	{
		const std::int64_t dec = bin_dec(bin);
		return dec_hex(dec);
	}

	std::string from_bin(numeric_systems new_system, std::string& old_value)
	{
		switch (new_system)
		{
		case numeric_systems::dec:
			return std::to_string(bin_dec(old_value));
		default:
		case numeric_systems::bin:
			return old_value;
		case numeric_systems::hex:
			return bin_hex(old_value);
		case numeric_systems::oct:
			return bin_oct(old_value);
		}
	}

	std::int64_t hex_dec(std::string& hex)
	{
		if (hex.length() >= 2 && hex.at(0) == '0' && (hex.at(1) == 'x' || hex.at(1) == 'X'))
			hex.erase(0, 2);

		std::transform(hex.begin(), hex.end(), hex.begin(), [](char c) { return std::tolower(c); });

		const std::unordered_map<char, std::size_t> mapping = {
				{ '0', 0 }, { '1', 1 }, { '2', 2 }, { '3', 3 }, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 },
				{ '8', 8 },
				{ '9', 9 }, { 'a', 10 }, { 'b', 11 }, { 'c', 12 }, { 'd', 13 }, { 'e', 14 }, { 'f', 15 }};

		std::int64_t result = 0;
		std::int64_t power = 0;

		for (auto it = hex.rbegin(); it != hex.rend(); it++)
		{
			if ((*it >= '0' && *it <= '9') || (*it >= 'a' && *it <= 'f'))
			{
				result += mapping.at(*it) * static_cast<std::int64_t>(std::pow(16, power));
				power++;
			}
			else
			{
				throw std::runtime_error("Syntax error in hexadecimal notation: 0x" + hex + "!\n");
			}
		}

		return result;
	}

	std::string hex_bin(std::string& hex)
	{
		const std::int64_t dec = hex_dec(hex);
		return dec_bin(dec);
	}

	std::string hex_oct(std::string& hex)
	{
		const std::int64_t dec = hex_dec(hex);
		return dec_oct(dec);
	}

	std::string from_hex(numeric_systems new_system, std::string& old_value)
	{
		switch (new_system)
		{
		case numeric_systems::dec:
			return std::to_string(hex_dec(old_value));
		case numeric_systems::bin:
			return hex_bin(old_value);
		default:
		case numeric_systems::hex:
			return old_value;
		case numeric_systems::oct:
			return hex_oct(old_value);
		}
	}

	std::int64_t oct_dec(std::string& oct)
	{
		std::int64_t result = 0;
		std::int64_t power = 0;

		const auto char_to_numb = [](char ch) { return ch - '0'; };

		for (auto it = oct.rbegin(); it != oct.rend(); it++)
		{
			if (*it >= '0' && *it <= '7')
			{
				result += char_to_numb(*it) * static_cast<std::int64_t>(std::pow(8, power));
				power++;
			}
			else
			{
				throw std::runtime_error("Syntax error in binary notation: 0b" + oct + "!\n");
			}
		}

		return result;
	}

	std::string oct_bin(std::string& hex)
	{
		const std::int64_t dec = oct_dec(hex);
		return dec_bin(dec);
	}

	std::string oct_hex(std::string& hex)
	{
		const std::int64_t dec = oct_dec(hex);
		return dec_hex(dec);
	}

	std::string from_oct(numeric_systems new_system, std::string& old_value)
	{
		switch (new_system)
		{
		case numeric_systems::dec:
			return std::to_string(oct_dec(old_value));
		case numeric_systems::bin:
			return oct_bin(old_value);
		case numeric_systems::hex:
			return oct_hex(old_value);
		default:
		case numeric_systems::oct:
			return old_value;
		}
	}

	QString converter(numeric_systems old_system, numeric_systems new_system, QString& old_value)
	{
		std::string old_value_std = old_value.toStdString();

		switch (old_system)
		{
		case numeric_systems::dec:
			return QString::fromStdString(from_dec(new_system, old_value_std));
		case numeric_systems::bin:
			return QString::fromStdString(from_bin(new_system, old_value_std));
		case numeric_systems::hex:
			return QString::fromStdString(from_hex(new_system, old_value_std));
		case numeric_systems::oct:
			return QString::fromStdString(from_oct(new_system, old_value_std));
		default:
			return old_value;
		}
	}
}