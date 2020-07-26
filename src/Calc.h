#ifndef CALC_H
#define CALC_H

#include "./ui_Calc.h"

#include <QMainWindow>
#include <QActionGroup>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 	
 	Calc.h
 	Calc class main header.
///////////////////////////////////////////////////////////
*/

QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

#define CONSTANT static constexpr double

typedef long double ldbl;
typedef long double (*ldbl_ptr)(long double);

/// CONSTANTS ///

struct Constants
{	
	CONSTANT pi        = 3.141592653589793238463;
	CONSTANT pi_2      = 1.570796326794896619231;
	CONSTANT pi_4      = 0.785398163397448309616;
	CONSTANT _1_pi     = 0.318309886183790671538;
	CONSTANT _2_pi     = 0.636619772367581343076;
	CONSTANT _2_sqrtpi = 1.128379167095512573896;
	CONSTANT sqrt2     = 1.414213562373095048802;
	CONSTANT _1_sqrt2  = 0.707106781186547524401;
	CONSTANT sqrt3     = 1.732050807568877293527;
	CONSTANT e         = 2.718281828459045235360;
	CONSTANT log2_e    = 1.442695040888963407360;
	CONSTANT log10_e   = 0.434294481903251827651;
	CONSTANT ln2       = 0.693147180559945309417;
	CONSTANT ln10      = 2.302585092994045684018;
};

enum class operation : int
{
	none = 0, division = 1, multiplication = 2, subtraction = 3,
	addition = 4, log_base_y = 5, modulo = 6, power = 7
};

enum class mode : int
{
	basic = 0, scientific = 1
};

struct Config
{
	double init_value{ 0.0 };
	mode init_mode{ mode::scientific };
	char disp_format{ 'g' };
	int display_prec{ 15 };	
};

struct Data
{
	// Allows to perform sequential operations such as 2*2*2 = 8
	bool sequential_operation{ false };
	
	// Allows to perform sequential operations such as 2*3[=][=][=] = 54.
	uint8_t subsequent_equal_presses{ false };

	// Buffer for operations.
	double lhs{ 0.0 };
	double rhs{ 1.0 };
	double unary{ 0.0 };

	// Data::memory for [MRC], [M+], [M−] buttons.
	double memory{ 0.0 };

	// Operation decision memory for two-argument operations.
	operation op_decision{ operation::none };
};

class Calc final : public QMainWindow
{
    Q_OBJECT

public:
	explicit Calc(QWidget *parent = nullptr);
    ~Calc() override;
	
private:
    Ui::Calc *ui;
	
	Config config_{};
	Data data_;
	
	QActionGroup* calc_modes_;
	QLineEdit* curr_display_;

	void loadConfig();

	[[nodiscard]] QString performBinaryOperation() const;
	void performUnaryOperation(ldbl_ptr func);

	friend class Settings;

private slots:
	
// basicCalc.cpp
	
	void numButtonPressed();
	void commaButtonPressed();	
	void mathButtonPressed();
	
	void equalButtonPressed();
	void percentButtonPressed();	

	void squareButtonPressed();
	void sqrtButtonPressed();

	void backspaceButtonPressed() const;
	void clearButtonPressed();
	void signButtonPressed();

	void memButtonPressed();
	void memAddButtonPressed();
	void memSubButtonPressed();

	void menuFileOptions();
	void menuViewBasicTriggered();
	void menuViewScientificTriggered();

// scientificCalc.cpp

	void piButtonPressed();
	void eButtonPressed();
	void randButtonPressed();
	
	void logBase2ButtonPressed();
	void logBase10ButtonPressed();
	void lnButtonPressed();

	void factorialButtonPressed();	
	void expButtonPressed();
	void e10ToXButtonPressed();
	
	void absButtonPressed();
	void inverseButtonPressed();	
};
#endif // CALC_H