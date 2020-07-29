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
typedef double (*dbl_ptr)(double);

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

	// Higher precision doesn't make sense for doubles,
	// lower precision causes severe problems with functions.
	static constexpr int display_prec{ 18 };
};

struct Data
{
	// Allows to perform sequential operations such as 2*2*2 = 8
	bool sequential_operation{ false };
	
	// Allows to perform sequential operations such as 2*3[=][=][=] = 54.
	uint8_t subsequent_equal_presses{ 0 };

	double last_result{ 0.0 };

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

	[[nodiscard]] QString performBinaryOperation();
	void performUnaryOperation(dbl_ptr func);

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

	void piButtonPressed() const;
	void eButtonPressed() const;
	void randButtonPressed();
	
	void logBase2ButtonPressed();
	void logBase10ButtonPressed();
	void lnButtonPressed();

	void factorialButtonPressed();	
	void expButtonPressed();
	void e10ToXButtonPressed();
	
	void absButtonPressed();
	void inverseButtonPressed();

	void sinClicked();
	void cosClicked();
	void tanClicked();
	void cotClicked();
	void secClicked();
	void cscClicked();

	void arcsinClicked();
	void arccosClicked();
	void arctanClicked();
	void arccotClicked();
	void arcsecClicked();
	void arccscClicked();

	void sinhClicked();
	void coshClicked();
	void tanhClicked();
	void cothClicked();
	void sechClicked();
	void cschClicked();

	void arsinhClicked();
	void arcoshClicked();
	void artanhClicked();
	void arcothClicked();
	void arsechClicked();
	void arcschClicked();
};
#endif // CALC_H