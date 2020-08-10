#pragma once

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 	
 	core/utility.h
///////////////////////////////////////////////////////////
*/

namespace core
{
	/// UTILITY FUNCTIONS ///
	
	// Compares if two floats (a, b) are nearly equal with precision of epsilon
	// multiplied by custom factor (eps_factor). Useful, if either a or b
	// precision is already result of some previous operation, consider:
	// 
	//	a = std::sin(x), then epsilon factor might be set to std::fabs(x), or e.g.:
	//	b = std::fmod(x, y), then std::max(std::fabs(x), std::fabs(y)) may be used
	//	as a coefficient.
	//
	// Gives satisfying results indepentently of order of magnitude of pair (a, b),
	// but may work unexpectedly if their *individual* order of magnitude differs strongly.

	template<typename Float>
	bool nearly_equal(const Float a, const Float b, const Float eps_factor)
		requires std::is_floating_point_v<Float>
	{
		const auto abs_a = std::abs(a);
		const auto abs_b = std::abs(b);

		const auto epsilon = std::numeric_limits<Float>::epsilon() * eps_factor;
		
		return std::fabs(abs_a - abs_b) <= epsilon;
	}

	double square(double r) noexcept;
	double rand();
	double log2(double r) noexcept;
	double real_fact(double r);
	double exp(double r) noexcept;
	double _10_to_x(double r) noexcept;
	double inv(double r);
	
	double tan(double r);
	double cot(double r);
	double sec(double r);
	double csc(double r);
	
	double asin(double r);
	double acos(double r);
	double acot(double r) noexcept;
	double asec(double r);
	double acsc(double r);
	
	double coth(double r);
	double sech(double r) noexcept;
	double csch(double r);
	
	double acosh(double r);
	double atanh(double r);
	double acoth(double r);
	double asech(double r);
	double acsch(double r);
} // namespace core