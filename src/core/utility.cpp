#include <chrono>
#include <numbers>
#include <random>
#include <stdexcept>

#include "./core/utility.h"

namespace core
{	
	double square(const double r) noexcept
	{
		return r * r;
	}
	
	// Generates random real number between 0 and 1.
	double rand()
	{	
		const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
	    std::minstd_rand eng(seed);
		return static_cast<double>(eng()) / std::minstd_rand::max();
	}

	// Evaluates log base 2 logarithm.
	double log2(const double r) noexcept
	{
		return std::log(r) / std::log(2.0);
	}

	// Evaluates factorial for any real number.
	double real_fact(const double r)
	{
		return std::tgamma(r + 1);
	}

	// Exponential function (e base).
	double exp(const double r) noexcept
	{
		return std::pow(std::numbers::e, r);
	}

	// Exponential function (10 base).
	double _10_to_x(const double r) noexcept
	{
		return std::pow(10, r);
	}

	// Evaluates 1/x.
	double inv(const double r)
	{
		if (r == 0)
			throw std::runtime_error("Can't divide by zero!");
		
		return 1 / r;		
	}

	double tan(const double r)
	{
		if (nearly_equal(std::cos(r), 0.0, std::fabs(r) * 2))
			throw std::runtime_error("Tangent is indeterminate for multiples of pi/2!");
		
		return std::tan(r);
	}

	double cot(const double r)
	{
		if (nearly_equal(std::sin(r), 0.0, std::fabs(r) * 2))
			throw std::runtime_error("Cotangent is indeterminate for multiples of pi!");
		
		return 1 / std::tan(r);
	}

	double sec(const double r)
	{
		if (nearly_equal(std::cos(r), 0.0, std::fabs(r) * 2))
			throw std::runtime_error("Secant is indeterminate for multiples of pi/2!");
		
		return 1 / std::cos(r);
	}

	double csc(const double r)
	{
		if (nearly_equal(std::sin(r), 0.0, std::fabs(r) * 2))
			throw std::runtime_error("Cosecant is indeterminate for multiples of pi!");
		
		return 1 / std::sin(r);
	}

	double asin(const double r)
	{
		if (r < -1 || r > 1)
			throw std::runtime_error("Arcsine is is only definite in [-1, 1]!");
		
		return std::asin(r);
	}

	double acos(const double r)
	{
		if (r < -1 || r > 1)
			throw std::runtime_error("Arccosine is only definite in [-1, 1]!");
		
		return std::acos(r);
	}

	double acot(const double r) noexcept
	{		
		return std::numbers::pi / 2 - std::atan(r);
	}

	double asec(const double r)
	{		
		if (r == 0 || 1 / r <= -1 || 1 / r >= 1)
			throw std::runtime_error("Arcsecant is only definite in (-infty, -1] u [1, +infty)!");

		return std::acos(1 / r );
	}

	double acsc(const double r)
	{		
		if (r == 0 || 1 / r <= -1 || 1 / r >= 1)
			throw std::runtime_error("Arccosecant is only definite in (-infty, -1] u [1, +infty)!");

		return std::asin(1 / r );
	}

	double coth(const double r)
	{
		if (std::sinh(r) == 0)
			throw std::runtime_error("Hyperbolic cotangent is indefinite for 0!");

		return std::cosh(r) / std::sinh(r);
	}
	
	double sech(const double r) noexcept
	{		
		return 1 / std::cosh(r);
	}

	double csch(const double r)
	{
		if (std::sinh(r) == 0)
			throw std::runtime_error("Hyperbolic cosecant is indefinite for 0!");
		
		return 1.0 / std::sinh(r);
	}

	double acosh(const double r)
	{
		if (r < 1)
			throw std::runtime_error("Area hyperbolic cosinus is only definite in [1, infty]!");

		return std::acosh(r);
	}

	double atanh(const double r)
	{
		if (r <= -1 || r >= 1)
			throw std::runtime_error("Area hyperbolic tangent is only definite in (-1, 1)!");

		return std::atanh(r);
	}

	double acoth(const double r)
	{
		if (r >= -1 && r <= 1)
			throw std::runtime_error("Area hyperbolic cotangent is only definite in (-infty, -1) u (1, infty)!");
		
		return 0.5 * std::log((r+1)/(r-1));
	}

	double asech(const double r)
	{
		if (r <= 0 || r > 1)
			throw std::runtime_error("Area hyperbolic secant is only definite in (0, 1]!");
		
		return std::log(std::sqrt((1/r) - 1) * std::sqrt((1/r) + 1) + (1/r));
	}

	double acsch(const double r)
	{
		if (r == 0)
			throw std::runtime_error("Area hyperbolic cosecant is indefinite for 0!");
		
		return std::log(std::sqrt(1 + (1 / (r*r))) + (1/r));
	}
} // namespace core
