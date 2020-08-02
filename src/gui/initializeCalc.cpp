#include <QFile>
#include <QtMath>
#include <QMap>

#include "Calc.h"
#include "./ui_Calc.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	initializeCalc.cpp
 	Calc constructor/destructor.
///////////////////////////////////////////////////////////
*/

Calc::Calc(CalcCore* core, QWidget *parent) :
	core_(core), QMainWindow(parent), ui(new Ui::Calc)
{	
	// UI initialization.
    ui->setupUi(this);
	ui->modes->setCurrentIndex(static_cast<int>(core_->config.init_mode));

	// Set current mode based on config.
	switch(core_->config.init_mode)
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
    ui->display->setText(QString::number(core_->config.init_value));
	ui->display_sci->setText(QString::number(core_->config.init_value));

/// BASIC MODE BUTTONS INIT ///

    // Initialize number buttons.
    QPushButton *number_buttons[10]{ nullptr };
    for (size_t i = 0; i < 10; ++i)
	{
    	QString button_name = "button_" + QString::number(i);
    	number_buttons[i] = findChild<QPushButton*>(button_name);
    	connect(number_buttons[i], SIGNAL(released()), this, SLOT(numButtonPressed()));
	}

	// Initialize [.] comma button.
	connect(ui->button_comma, SIGNAL(released()), this, SLOT(commaButtonPressed()));
	ui->button_comma->setToolTip("Insert comma");

    // Initialize math operations buttons.
    connect(ui->button_div, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_div->setToolTip("Divide by...");
	
	connect(ui->button_mul, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_mul->setToolTip("Multiply by...");
	
	connect(ui->button_sub, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_sub->setToolTip("Subtract...");
	
	connect(ui->button_add, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_add->setToolTip("Add...");

	// Initialize [x²] and [√‾] buttons.
	connect(ui->button_square, SIGNAL(released()),
		this, SLOT(squareButtonPressed()));
	ui->button_square->setToolTip("Square");
	
	connect(ui->button_sqrt, SIGNAL(released()), this, SLOT(sqrtButtonPressed()));
	ui->button_sqrt->setToolTip("Square root");

	// Initialize result buttons: [=] and [%].
	connect(ui->button_equal, SIGNAL(released()),
		this, SLOT(equalButtonPressed()));
	ui->button_equal->setToolTip("Evaluate operation");
	
	connect(ui->button_percent, SIGNAL(released()), this, SLOT(percentButtonPressed()));
	ui->button_sqrt->setToolTip("Evaluate percent operation");

    // Initialize [C] button.
    connect(ui->button_C, SIGNAL(released()), this, SLOT(clearButtonPressed()));
	ui->button_C->setToolTip("Clear display");

    // Initialize [±] button.
    connect(ui->button_sign, SIGNAL(released()), this, SLOT(signButtonPressed()));
	ui->button_sign->setToolTip("Invert sign");

	// Initialize [MRC], [M+], [M−] buttons.
	connect(ui->button_mem, SIGNAL(released()), this, SLOT(memButtonPressed()));
	ui->button_mem->setToolTip("Recall/clear memory");
	
	connect(ui->button_mem_add, SIGNAL(released()), this, SLOT(memAddButtonPressed()));
	ui->button_mem_add->setToolTip("Add to memory");
	
	connect(ui->button_mem_sub, SIGNAL(released()), this, SLOT(memSubButtonPressed()));
	ui->button_mem_sub->setToolTip("Subtract from memory");

    // Initialize [Backspace] button.
    connect(ui->button_backspace, SIGNAL(released()), this, SLOT(backspaceButtonPressed()));
	ui->button_backspace->setToolTip("Backspace button");

/// SCIENTIFIC MODE BUTTONS INIT ///

	// Initialize number buttons.
    QPushButton *number_buttons_sci[10]{ nullptr };
    for (size_t i = 0; i < 10; ++i)
	{
    	QString button_name = "button_" + QString::number(i) + "_sci";
    	number_buttons_sci[i] = findChild<QPushButton*>(button_name);
    	connect(number_buttons_sci[i], SIGNAL(released()), this, SLOT(numButtonPressed()));
	}

	// Initialize [.] comma button.
	connect(ui->button_comma_sci, SIGNAL(released()), this, SLOT(commaButtonPressed()));
	ui->button_comma_sci->setToolTip("Insert comma");

    // Initialize math operations buttons.
    connect(ui->button_div_sci, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_div_sci->setToolTip("Divide by...");
	
	connect(ui->button_mul_sci, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_mul_sci->setToolTip("Multiply by...");
	
	connect(ui->button_sub_sci, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_sub_sci->setToolTip("Subtract...");
	
	connect(ui->button_add_sci, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_add_sci->setToolTip("Add...");

	// Initialize [x²] and [√‾] buttons.
	connect(ui->button_square_sci, SIGNAL(released()), this, SLOT(squareButtonPressed()));
	ui->button_square_sci->setToolTip("Square");
	
	connect(ui->button_sqrt_sci, SIGNAL(released()), this, SLOT(sqrtButtonPressed()));
	ui->button_sqrt_sci->setToolTip("Square root");

	// Initialize result buttons: [=] and [%].
	connect(ui->button_equal_sci, SIGNAL(released()), this, SLOT(equalButtonPressed()));
	ui->button_equal_sci->setToolTip("Evaluate operation");
	
	connect(ui->button_percent_sci, SIGNAL(released()), this, SLOT(percentButtonPressed()));
	ui->button_percent_sci->setToolTip("Evaluate percent operation");

    // Initialize [C] button.
    connect(ui->button_C_sci, SIGNAL(released()), this, SLOT(clearButtonPressed()));
	ui->button_C_sci->setToolTip("Clear display");

    // Initialize [±] button.
    connect(ui->button_sign_sci, SIGNAL(released()), this, SLOT(signButtonPressed()));
	ui->button_sign_sci->setToolTip("Invert sign");
	
	// Initialize constants buttons.
    connect(ui->button_pi, SIGNAL(released()), this, SLOT(piButtonPressed()));
	ui->button_pi->setToolTip("Insert pi constant");
	
	connect(ui->button_e, SIGNAL(released()), this, SLOT(eButtonPressed()));
	ui->button_e->setToolTip("Insert e constant");

	// Randomize button.
	connect(ui->button_rand, SIGNAL(released()), this, SLOT(randButtonPressed()));
	ui->button_rand->setToolTip("Generate random number from 0 to 1");

	// Logarithms buttons.
	connect(ui->button_log_basey, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_log_basey->setToolTip("y-base logarithm (argument first, base last)");
	
	connect(ui->button_log_base2, SIGNAL(released()), this, SLOT(logBase2ButtonPressed()));
	ui->button_log_base2->setToolTip("2-base logarithm");
	
	connect(ui->button_log_base10, SIGNAL(released()), this, SLOT(logBase10ButtonPressed()));
	ui->button_log_base10->setToolTip("10-base logarithm");
	
	connect(ui->button_ln, SIGNAL(released()), this, SLOT(lnButtonPressed()));
	ui->button_ln->setToolTip("Natural logarithm");

	// Factorial button.
	connect(ui->button_factorial, SIGNAL(released()), this, SLOT(factorialButtonPressed()));
	ui->button_factorial->setToolTip("Factorial");

	// Modulo button.
	connect(ui->button_modulo, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_modulo->setToolTip("Modulo operation");

	// Exponential and power functions.
	connect(ui->button_e_to_x, SIGNAL(released()), this, SLOT(expButtonPressed()));
	ui->button_e_to_x->setToolTip("Exponential function (base e)");
	
	connect(ui->button_10_to_x, SIGNAL(released()), this, SLOT(e10ToXButtonPressed()));
	ui->button_10_to_x->setToolTip("Exponential function (base 10)");
	
	connect(ui->button_x_to_y, SIGNAL(released()), this, SLOT(mathButtonPressed()));
	ui->button_x_to_y->setToolTip("Custom power (x to y)");

	// Absolute value.
	connect(ui->button_abs, SIGNAL(released()), this, SLOT(absButtonPressed()));
	ui->button_abs->setToolTip("Absolute value");

	// Inverse.
	connect(ui->button_inverse, SIGNAL(released()), this, SLOT(inverseButtonPressed()));
	ui->button_inverse->setToolTip("Invert");

	// Initialize [Backspace] button.
    connect(ui->button_backspace_sci, SIGNAL(released()), this, SLOT(backspaceButtonPressed()));
	ui->button_backspace_sci->setToolTip("Backspace");
	
/// MENU BAR INIT ///

	connect(ui->actionOptions, SIGNAL(triggered(bool)), this, SLOT(menuFileOptions()));

	// Initialize [View] menu bar tab.
	calc_modes_ = new QActionGroup(this);
	calc_modes_->addAction(ui->actionBasic);
	calc_modes_->addAction(ui->actionScientific);	
	
	// Set current mode based on config.
	switch(core_->config.init_mode)
	{
	case mode::scientific:
		ui->actionScientific->setChecked(true);
		ui->menuFunctions->menuAction()->setVisible(true);
		break;		
	default:
	case mode::basic:
		ui->actionBasic->setChecked(true);
		ui->menuFunctions->menuAction()->setVisible(false);
		break;
	}	

	connect(ui->actionBasic, SIGNAL(triggered(bool)), this, SLOT(menuViewBasicTriggered()));
	connect(ui->actionScientific, SIGNAL(triggered(bool)), this, SLOT(menuViewScientificTriggered()));

	// FUNCTIONS //

	connect(ui->actionSin, SIGNAL(triggered(bool)), this, SLOT(sinClicked()));	
	connect(ui->actionCos, SIGNAL(triggered(bool)), this, SLOT(cosClicked()));	
	connect(ui->actionTan, SIGNAL(triggered(bool)), this, SLOT(tanClicked()));	
	connect(ui->actionCot, SIGNAL(triggered(bool)), this, SLOT(cotClicked()));	
	connect(ui->actionSec, SIGNAL(triggered(bool)), this, SLOT(secClicked()));	
	connect(ui->actionCsc, SIGNAL(triggered(bool)), this, SLOT(cscClicked()));

	connect(ui->actionArcsin, SIGNAL(triggered(bool)), this, SLOT(arcsinClicked()));	
	connect(ui->actionArccos, SIGNAL(triggered(bool)), this, SLOT(arccosClicked()));	
	connect(ui->actionArctan, SIGNAL(triggered(bool)), this, SLOT(arctanClicked()));	
	connect(ui->actionArccot, SIGNAL(triggered(bool)), this, SLOT(arccotClicked()));	
	connect(ui->actionArcsec, SIGNAL(triggered(bool)), this, SLOT(arcsecClicked()));	
	connect(ui->actionArccsc, SIGNAL(triggered(bool)), this, SLOT(arccscClicked()));

	connect(ui->actionSinh, SIGNAL(triggered(bool)), this, SLOT(sinhClicked()));	
	connect(ui->actionCosh, SIGNAL(triggered(bool)), this, SLOT(coshClicked()));	
	connect(ui->actionTanh, SIGNAL(triggered(bool)), this, SLOT(tanhClicked()));	
	connect(ui->actionCoth, SIGNAL(triggered(bool)), this, SLOT(cothClicked()));	
	connect(ui->actionSech, SIGNAL(triggered(bool)), this, SLOT(sechClicked()));	
	connect(ui->actionCsch, SIGNAL(triggered(bool)), this, SLOT(cschClicked()));

	connect(ui->actionArsinh, SIGNAL(triggered(bool)), this, SLOT(arsinhClicked()));	
	connect(ui->actionArcosh, SIGNAL(triggered(bool)), this, SLOT(arcoshClicked()));	
	connect(ui->actionArtanh, SIGNAL(triggered(bool)), this, SLOT(artanhClicked()));	
	connect(ui->actionArcoth, SIGNAL(triggered(bool)), this, SLOT(arcothClicked()));	
	connect(ui->actionArsech, SIGNAL(triggered(bool)), this, SLOT(arsechClicked()));	
	connect(ui->actionArcsch, SIGNAL(triggered(bool)), this, SLOT(arcschClicked()));
}

Calc::~Calc()
{
    delete ui;
}