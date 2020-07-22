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

enum class operation : uint8_t
{
	none = 0,
	division = 1,
	multiplication = 2,
	subtraction = 3,
	addition = 4
};

enum class mode : int
{
	basic = 0,
	scientific = 1
};

struct Data
{
	// Initial display value.
	static constexpr double init_calc_value{ 0.0 };

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
	Data data;
	
	QActionGroup* calc_modes_;

private slots:	
	void numButtonPressed();
	void commaButtonPressed();

	QString performOperation() const;
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

	void menuViewBasicTriggered();
	void menuViewScientificTriggered();
	
	//void menuViewModeChanged();
};
#endif // CALC_H