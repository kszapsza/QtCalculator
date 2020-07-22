#ifndef CALC_H
#define CALC_H

#include "./ui_Calc.h"

#include <QMainWindow>
#include <QActionGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

enum class Operation : uint8_t { NONE = 0, DIV, MUL, SUB, ADD };
enum class Mode : int { BASIC = 0, SCIENTIFIC };

struct Data
{
	// Initial display value.
	static constexpr double init_calc_value{ 0.0 };

	// True since first operation, until [=] or [%] is pressed.
	// Allows to perform sequential operations such as 2*2*2 = 8
	// (first operation can be evaluated and treated as lhs for the following one).
	bool sequential_operation{ false };

	// Buffer for operations.
	double lhs{ 0.0 };
	double rhs{ 1.0 };
	double unary{ 0.0 };

	// Data::memory for [MRC], [M+], [M−] buttons.
	double memory{ 0.0 };

	// Operation decision memory for two-argument operations.
	Operation op_decision{ Operation::NONE };
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
	void numButtonPressed() const;
	void commaButtonPressed() const;
	
	QString performOperation() const;
	void mathButtonPressed();	

	void equalButtonPressed();
	void percentButtonPressed();

	void squareButtonPressed();
	void sqrtButtonPressed();

	void clearButtonPressed();
	void signButtonPressed() const;

	void memButtonPressed();
	void memAddButtonPressed();
	void memSubButtonPressed();

	void backspaceButtonPressed() const;

	void menuViewModeChanged() const;
};
#endif // CALC_H