//
// Created by kszap on 18.08.2020.
//
#pragma once

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	core/enums.h
 	Enumeration typedefs.
///////////////////////////////////////////////////////////
*/

enum class operation : int
{
	none = 0, division = 1, multiplication = 2, subtraction = 3,
	addition = 4, log_base_y = 5, modulo = 6, power = 7
};

// Enum underlying indexes are connected with QStackWidget current tab indexes!
enum class mode : int
{
	basic = 0, scientific = 1, programmer = 2
};

enum class numeric_systems : int
{
	dec = 0, bin = 1, hex = 2, oct = 3
};