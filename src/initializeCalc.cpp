#include "Calc.h"
#include "./ui_Calc.h"

#include <QPushButton>
#include <QtMath>
#include <QMap>
#include <QStackedWidget>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	initializeCalc.cpp
 	Calc constructor/destructor.
///////////////////////////////////////////////////////////
*/

Calc::Calc(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::Calc)
{
	// UI initialization.
    ui->setupUi(this);	
	ui->modes->setCurrentIndex(static_cast<int>(config_.start_mode));

	// Set current mode based on config.
	switch(config_.start_mode)
	{
	case mode::scientific:
		curr_display_ = ui->display_sci;
		break;		
	default:
	case mode::basic:
		curr_display_ = ui->display;
		break;
	}
	
    // Initialize both displays with init value.
    ui->display->setText(QString::number(config_.init_calc_value));
	ui->display_sci->setText(QString::number(config_.init_calc_value));

/// BASIC MODE BUTTONS INIT ///

    // Initialize number buttons.
    QPushButton *number_buttons[10]{ nullptr };
    for (size_t i = 0; i < 10; ++i)
	{
    	QString button_name = "button_" + QString::number(i);
    	number_buttons[i] = findChild<QPushButton*>(button_name);
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

    // Initialize [Backspace] button.
    connect(ui->button_backspace, SIGNAL(released()),
		this, SLOT(backspaceButtonPressed()));

/// SCIENTIFIC MODE BUTTONS INIT ///

	// Initialize number buttons.
    QPushButton *number_buttons_sci[10]{ nullptr };
    for (size_t i = 0; i < 10; ++i)
	{
    	QString button_name = "button_" + QString::number(i) + "_sci";
    	number_buttons_sci[i] = findChild<QPushButton*>(button_name);
    	connect(number_buttons_sci[i], SIGNAL(released()),
    		this, SLOT(numButtonPressed()));
	}

	// Initialize [.] comma button.
	connect(ui->button_comma_sci, SIGNAL(released()),
		this, SLOT(commaButtonPressed()));

    // Initialize math operations buttons.
    connect(ui->button_div_sci, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));
	connect(ui->button_mul_sci, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));
	connect(ui->button_sub_sci, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));
	connect(ui->button_add_sci, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));

	// Initialize [x²] and [√‾] buttons.
	connect(ui->button_square_sci, SIGNAL(released()),
		this, SLOT(squareButtonPressed()));
	connect(ui->button_sqrt_sci, SIGNAL(released()),
		this, SLOT(sqrtButtonPressed()));

	// Initialize result buttons: [=] and [%].
	connect(ui->button_equal_sci, SIGNAL(released()),
		this, SLOT(equalButtonPressed()));
	connect(ui->button_percent_sci, SIGNAL(released()),
		this, SLOT(percentButtonPressed()));

    // Initialize [C] button.
    connect(ui->button_C_sci, SIGNAL(released()),
		this, SLOT(clearButtonPressed()));

    // Initialize [±] button.
    connect(ui->button_sign_sci, SIGNAL(released()),
		this, SLOT(signButtonPressed()));
	
	// Initialize constants buttons.
    connect(ui->button_pi, SIGNAL(released()),
		this, SLOT(piButtonPressed()));
	connect(ui->button_e, SIGNAL(released()),
		this, SLOT(eButtonPressed()));

	// Randomize button.
	connect(ui->button_rand, SIGNAL(released()),
		this, SLOT(randButtonPressed()));

	// Logarithms buttons.
	connect(ui->button_log_basey, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));
	connect(ui->button_log_base2, SIGNAL(released()),
		this, SLOT(logBase2ButtonPressed()));
	connect(ui->button_log_base10, SIGNAL(released()),
		this, SLOT(logBase10ButtonPressed()));
	connect(ui->button_ln, SIGNAL(released()),
		this, SLOT(lnButtonPressed()));

	// Factorial button.
	connect(ui->button_factorial, SIGNAL(released()),
		this, SLOT(factorialButtonPressed()));

	// Modulo button.
	connect(ui->button_modulo, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));

	// Exponential and power functions.
	connect(ui->button_e_to_x, SIGNAL(released()),
		this, SLOT(expButtonPressed()));
	connect(ui->button_10_to_x, SIGNAL(released()),
		this, SLOT(e10ToXButtonPressed()));
	connect(ui->button_x_to_y, SIGNAL(released()),
		this, SLOT(mathButtonPressed()));

	// Absolute value.
	connect(ui->button_abs, SIGNAL(released()),
		this, SLOT(absButtonPressed()));

	// Inverse.
	connect(ui->button_inverse, SIGNAL(released()),
		this, SLOT(inverseButtonPressed()));

	// Initialize [Backspace] button.
    connect(ui->button_backspace_sci, SIGNAL(released()),
		this, SLOT(backspaceButtonPressed()));
	
/// MENU BAR INIT ///

	// Initialize [View] menu bar tab.
	calc_modes_ = new QActionGroup(this);
	calc_modes_->addAction(ui->actionBasic);
	calc_modes_->addAction(ui->actionScientific);	
	
	// Set current mode based on config.
	switch(config_.start_mode)
	{
	case mode::scientific:
		ui->actionScientific->setChecked(true);
		break;		
	default:
	case mode::basic:
		ui->actionBasic->setChecked(true);
		break;
	}	

	connect(ui->actionBasic, SIGNAL(triggered(bool)),
		this, SLOT(menuViewBasicTriggered()));
	connect(ui->actionScientific, SIGNAL(triggered(bool)),
		this, SLOT(menuViewScientificTriggered()));
}

Calc::~Calc()
{
    delete ui;
}