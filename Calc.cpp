#include "Calc.h"
#include "./ui_Calc.h"

#include <QPushButton>
#include <QtMath>
#include <map>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
///////////////////////////////////////////////////////////
*/

Calc::Calc(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::Calc)
{
	// UI initialization.
    ui->setupUi(this);

    // Initialize display with init value.
    ui->display->setText(QString::number(Data::init_calc_value));

    // Initialize number buttons.
    QPushButton *number_buttons[10]{ nullptr };
    for (size_t i = 0; i < 10; ++i)
	{
    	QString button_name = "button_" + QString::number(i);
    	number_buttons[i] = Calc::findChild<QPushButton*>(button_name);
    	connect(number_buttons[i], SIGNAL(released()),
    		this, SLOT(numButtonPressed()));
	}

	// Initialize [.] comma button.
	connect(ui->button_comma, SIGNAL(released()),
		this, SLOT(commaButtonPressed()));

    // Initialize math operations buttons.
    connect(ui->button_div, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));
	connect(ui->button_mul, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));
	connect(ui->button_sub, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));
	connect(ui->button_add, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));

	// Initialize [x²] and [√‾] buttons.
	connect(ui->button_square, SIGNAL(released()),
		this, SLOT(squareButtonPressed()));
	connect(ui->button_sqrt, SIGNAL(released()),
		this, SLOT(sqrtButtonPressed()));

	// Initialize result buttons: [=] and [%].
	connect(ui->button_equal, SIGNAL(released()),
		this, SLOT(equalButtonPressed()));
	connect(ui->button_percent, SIGNAL(released()),
		this, SLOT(percentButtonPressed()));

    // Initialize [C] button.
    connect(ui->button_C, SIGNAL(released()),
		this, SLOT(clearButtonPressed()));

    // Initialize [±] button.
    connect(ui->button_sign, SIGNAL(released()),
		this, SLOT(signButtonPressed()));

	// Initialize [MRC], [M+], [M−] buttons.
	connect(ui->button_mem, SIGNAL(released()),
		this, SLOT(memButtonPressed()));
	connect(ui->button_mem_add, SIGNAL(released()),
		this, SLOT(memAddButtonPressed()));
	connect(ui->button_mem_sub, SIGNAL(released()),
		this, SLOT(memSubButtonPressed()));

    // Initialize [OFF] button.
    connect(ui->button_off, SIGNAL(released()),
		this, SLOT(offButtonPressed()));
}

Calc::~Calc()
{
    delete ui;
}

///////////////////////////////////////////////////////////
//	INPUT												 //
///////////////////////////////////////////////////////////

// Putting numbers in using [0~9] buttons.
void Calc::numButtonPressed() const
{
	// Establish pointer to the button pressed.
	const auto *button = dynamic_cast<QPushButton*>(sender());
	const QString button_value = button->text();
	const QString display_value = ui->display->text();

	if (display_value == QString::number(data.lhs)
		|| display_value == "0" )
	{
		ui->display->setText(button_value);
	}
	else
	{
		const QString new_value = display_value + button_value;
		ui->display->setText(new_value);
	}
}

void Calc::commaButtonPressed() const
{
	const QString display_value = ui->display->text();
	const QString new_value = display_value + '.';
	ui->display->setText(new_value);
}

///////////////////////////////////////////////////////////
//	TWO-ARGUMENT OPERATIONS								 //
///////////////////////////////////////////////////////////

// Core function performing operation stored in buffer.
// Used both by [=] button and math buttons.
QString Calc::performOperation() const
{
	// Result string.
	QString str_result{};

	switch (data.op_decision)
	{
	case Operation::NONE:
		str_result = ui->display->text();
		break;
	case Operation::DIV:
		if (data.rhs == 0)
		{
			ui->statusbar->showMessage("Cannot divide by zero!", 2000);
			str_result = "Err";
		}
		else str_result = QString::number(data.lhs / data.rhs);
		break;
	case Operation::MUL:
		str_result = QString::number(data.lhs * data.rhs);
		break;
	case Operation::SUB:
		str_result = QString::number(data.lhs - data.rhs);
		break;
	case Operation::ADD:
		str_result = QString::number(data.lhs + data.rhs);
		break;
	}

	return str_result;
}

// Math two-argument operation buttons: [/], [*], [−], [+].
void Calc::mathButtonPressed()
{
	// If in sequential operation, evaluate queued operation and treat its result
	// as lhs argument for the next operation now being entered.
	if (data.sequential_operation)
	{
		// The lhs is already saved, save rhs from display,
		// perform operation and put the result on screen.
		data.rhs = ui->display->text().toDouble();
		const QString prev_op_result = performOperation();
		ui->display->setText(prev_op_result);
	}

	// If first operation, lhs = previously put number,
	// if in sequence, lhs = prev result, evaluated above.
	data.lhs = ui->display->text().toDouble();

	// Operation enum mapping to key labels.
	std::map<QString, Operation> op_names
	{
		{"/", Operation::DIV},
		{"*", Operation::MUL},
		{"−", Operation::SUB}, // − (U+2212)!
		{"+", Operation::ADD}
	};

	// Establish pointer to the button pressed.
	const auto *button = dynamic_cast<QPushButton*>(sender());
	const QString button_label = button->text();

	// Set op_decision basing on the label of the button pressed.
	data.op_decision = op_names[button_label];

	// Begin (or maintain) sequential operation state until [=] is pressed.
	data.sequential_operation = true;
}

// Procedure when pressing [=] button.
void Calc::equalButtonPressed()
{
	data.rhs = ui->display->text().toDouble();
	ui->display->setText(performOperation());

	// End of sequential operation.
	data.sequential_operation = false;
}

// Procedure when pressing [%] button. The method of calculation is different than usual.
// Pressing [%] ends sequential operation the same way as [=].
void Calc::percentButtonPressed()
{
	// Save current display state as rhs value.
	data.rhs = ui->display->text().toDouble();

	QString str_result{};
	union
	{
		double percentage_fraction{};
		double percentage_of_lhs;
	};

	switch (data.op_decision)
	{
	case Operation::NONE:
		str_result = ui->display->text();
		break;
	case Operation::DIV:
		percentage_fraction = data.rhs / 100;
		if (percentage_fraction == 0)
		{
			ui->statusbar->showMessage("Cannot divide by zero!", 2000);
			str_result = "Err";
		}
		else str_result = QString::number(data.lhs / percentage_fraction);
		break;
	case Operation::MUL:
		percentage_fraction = data.rhs / 100;
		str_result = QString::number(data.lhs * percentage_fraction);
		break;
	case Operation::SUB:
		percentage_of_lhs = (data.rhs / 100) * data.lhs;
		str_result = QString::number(data.lhs - percentage_of_lhs);
		break;
	case Operation::ADD:
		percentage_of_lhs = (data.rhs / 100) * data.lhs;
		str_result = QString::number(data.lhs + percentage_of_lhs);
		break;
	}

	ui->display->setText(str_result);
	data.sequential_operation = false;
}

///////////////////////////////////////////////////////////
//	SINGLE-ARGUMENT OPERATIONS							 //
///////////////////////////////////////////////////////////

// Square button [x²].
void Calc::squareButtonPressed()
{
	// Save current display state as base value.
	data.unary = ui->display->text().toDouble();

	// Evaluate and show square.
	const QString str_result = QString::number(qPow(data.unary, 2));
	ui->display->setText(str_result);
}

// Square root button [√‾].
void Calc::sqrtButtonPressed()
{
	// Save current display state as base value.
	data.unary = ui->display->text().toDouble();

	// Evaluate and show square.
	const qreal sqrt_result = qSqrt(data.unary);
	const QString str_result = QString::number(sqrt_result);
	ui->display->setText(str_result);
}

// Clearing the display and buffer with [C] button.
void Calc::clearButtonPressed()
{
	// Clear the display.
	ui->display->setText(QString::number(Data::init_calc_value));

	// Flush the buffer.
	data.op_decision = Operation::NONE;
	data.lhs = 0.0;
	data.rhs = 1.0;
}

// Changing display value sign with [±] button.
void Calc::signButtonPressed() const
{
	const QString curr_value = ui->display->text();
	const double dbl_curr_value = curr_value.toDouble();
	const double dbl_new_value = dbl_curr_value * -1;
	ui->display->setText(QString::number(dbl_new_value));
}

///////////////////////////////////////////////////////////
//	MEMORY												 //
///////////////////////////////////////////////////////////

void Calc::memButtonPressed()
{
	const QString curr_value = ui->display->text();

	if (data.memory == curr_value.toDouble())
	{
		data.memory = Data::init_calc_value;
		ui->statusbar->showMessage("Memory cleaned.", 2000);
	}
	else
	{
		ui->statusbar->showMessage("Memory recalled.", 2000);
	}

	ui->display->setText(QString::number(data.memory));
}

void Calc::memAddButtonPressed()
{
	const QString curr_value = ui->display->text();
	data.memory += curr_value.toDouble();
	ui->statusbar->showMessage("Added to memory.", 2000);
}

void Calc::memSubButtonPressed()
{
	const QString curr_value = ui->display->text();
	data.memory -= curr_value.toDouble();
	ui->statusbar->showMessage("Subtracted from memory.", 2000);
}

// Quitting the app with [OFF] button.
void Calc::offButtonPressed()
{
	QApplication::quit();
}
