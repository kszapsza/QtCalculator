#include "Calc.h"
#include "./ui_Calc.h"

#include <QtMath>
#include <map>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
///////////////////////////////////////////////////////////
*/

enum Operation{ NONE = 0, DIV, MUL, SUB, ADD };

namespace Data
{
	// Initial display value.
	constexpr double init_calc_value{ 0.0 };

	// Buffer for operations.
	double lhs{ 0.0 };
	double rhs{ 1.0 };
	double unary{ 0.0 };

	// Data::memory for [MRC], [M+], [M−] buttons.
	double memory{ 0.0 };

	// Operation decision Data::memory for two-argument operations.
	Operation op_decision{ NONE };
}

///////////////////////////////////////////////////////////

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

	// Initialize [x²] button.
	connect(ui->button_square, SIGNAL(released()),
		this, SLOT(squareButtonPressed()));

	// Initialize [√‾] button.
	connect(ui->button_sqrt, SIGNAL(released()),
		this, SLOT(sqrtButtonPressed()));

	// Initialize [=] button.
	connect(ui->button_equal, SIGNAL(released()),
		this, SLOT(equalButtonPressed()));

	// Initialize [%] button.
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
void Calc::numButtonPressed()
{
	// Establish pointer to the button pressed.
	const auto *button = dynamic_cast<QPushButton*>(sender());
	const QString button_value = button->text();
	const QString display_value = ui->display->text();

	if (display_value == "0")
	{
		ui->display->setText(button_value);
	}
	else
	{
		const QString new_value = display_value + button_value;
		ui->display->setText(new_value);
	}
}

void Calc::commaButtonPressed()
{
	const QString display_value = ui->display->text();
	const QString new_value = display_value + '.';
	ui->display->setText(new_value);
}

// Math two-argument operation buttons: [/], [*], [−], [+].
void Calc::mathButtonPressed()
{
	// Move lhs value to buffer.
	Data::lhs = ui->display->text().toDouble();

	std::map<QString, Operation> op_names
	{
		{"/", DIV},
		{"*", MUL},
		{"−", SUB}, // − (U+2212)!
		{"+", ADD}
	};

	Data::op_decision = NONE;

	// Establish pointer to the button pressed.
	const auto *button = dynamic_cast<QPushButton*>(sender());
	QString button_label = button->text();

	// Set op_decision basing on the label of the button pressed.
	Data::op_decision = op_names[button_label];

	ui->display->setText(QString::number(Data::init_calc_value));
}

///////////////////////////////////////////////////////////
//	TWO-ARGUMENT OPERATIONS								 //
///////////////////////////////////////////////////////////

// Procedure when pressing [=] button.
void Calc::equalButtonPressed()
{
	// Save current display state as rhs value.
	Data::rhs = ui->display->text().toDouble();

	// Result string.
	QString str_result{};

	switch (Data::op_decision)
	{
	case NONE:
		str_result = ui->display->text();
		break;
	case DIV:
		if (Data::rhs == 0)
		{
			ui->statusbar->showMessage("Cannot divide by zero!", 2000);
			str_result = "Err";
		}
		else str_result = QString::number(Data::lhs / Data::rhs);
		break;
	case MUL:
		str_result = QString::number(Data::lhs * Data::rhs);
		break;
	case SUB:
		str_result = QString::number(Data::lhs - Data::rhs);
		break;
	case ADD:
		str_result = QString::number(Data::lhs + Data::rhs);
		break;
	}

	ui->display->setText(str_result);
}

// Procedure when pressing [%] button.
void Calc::percentButtonPressed()
{
	// Save current display state as rhs value.
	Data::rhs = ui->display->text().toDouble();

	QString str_result{};
	union
	{
		double percentage_fraction{};
		double percentage_of_lhs;
	};

	switch (Data::op_decision)
	{
	case NONE:
		str_result = ui->display->text();
		break;
	case DIV:
		percentage_fraction = Data::rhs / 100;
		if (percentage_fraction == 0)
		{
			ui->statusbar->showMessage("Cannot divide by zero!", 2000);
			str_result = "Err";
		}
		else str_result = QString::number(Data::lhs / percentage_fraction);
		break;
	case MUL:
		percentage_fraction = Data::rhs / 100;
		str_result = QString::number(Data::lhs * percentage_fraction);
		break;
	case SUB:
		percentage_of_lhs = (Data::rhs / 100) * Data::lhs;
		str_result = QString::number(Data::lhs - percentage_of_lhs);
		break;
	case ADD:
		percentage_of_lhs = (Data::rhs / 100) * Data::lhs;
		str_result = QString::number(Data::lhs + percentage_of_lhs);
		break;
	}

	ui->display->setText(str_result);
}

///////////////////////////////////////////////////////////
//	SINGLE-ARGUMENT OPERATIONS							 //
///////////////////////////////////////////////////////////

// Square button [x²].
void Calc::squareButtonPressed()
{
	// Save current display state as base value.
	Data::unary = ui->display->text().toDouble();

	// Evaluate and show square.
	const QString str_result = QString::number(qPow(Data::unary, 2));
	ui->display->setText(str_result);
}

// Square root button [√‾].
void Calc::sqrtButtonPressed()
{
	// Save current display state as base value.
	Data::unary = ui->display->text().toDouble();

	// Evaluate and show square.
	const qreal sqrt_result = qSqrt(Data::unary);
	const QString str_result = QString::number(sqrt_result);
	ui->display->setText(str_result);
}

// Clearing the display with [C] button.
void Calc::clearButtonPressed()
{
	ui->display->setText(QString::number(Data::init_calc_value));
}

// Changing display value sign with [±] button.
void Calc::signButtonPressed()
{
	const QString curr_value = ui->display->text();
	const double dbl_curr_value = curr_value.toDouble();
	const double dbl_new_value = dbl_curr_value * -1;
	ui->display->setText(QString::number(dbl_new_value));
}

///////////////////////////////////////////////////////////
//	Data::memory												 //
///////////////////////////////////////////////////////////

void Calc::memButtonPressed()
{
	const QString curr_value = ui->display->text();

	if (Data::memory == curr_value.toDouble())
	{
		Data::memory = Data::init_calc_value;
		ui->statusbar->showMessage("Data::memory cleaned.", 2000);
	}
	else
	{
		ui->statusbar->showMessage("Data::memory recalled.", 2000);
	}

	ui->display->setText(QString::number(Data::memory));
}

void Calc::memAddButtonPressed()
{
	const QString curr_value = ui->display->text();
	Data::memory += curr_value.toDouble();
	ui->statusbar->showMessage("Added to Data::memory.", 2000);
}

void Calc::memSubButtonPressed()
{
	const QString curr_value = ui->display->text();
	Data::memory -= curr_value.toDouble();
	ui->statusbar->showMessage("Subtracted from Data::memory.", 2000);
}

// Quitting the app with [OFF] button.
void Calc::offButtonPressed()
{
	QApplication::quit();
}
