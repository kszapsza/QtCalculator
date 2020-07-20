#ifndef CALC_H
#define CALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

enum class Operation : uint8_t { NONE = 0, DIV, MUL, SUB, ADD };

struct Data
{
	// Initial display value.
	static constexpr double init_calc_value{ 0.0 };

	// True since first operation, until [=] or [%] is pressed. Allows to perform sequential operations
	// such as 2*2*2 = 8 (first operation can be evaluated and treated as lhs for the following one).
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

	Data data{};

private:
    Ui::Calc *ui;

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

	static void offButtonPressed();
};
#endif // CALC_H
