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
	ui->modes->setCurrentIndex(static_cast<int>(mode::basic));

    // Initialize display with init value.
    ui->display->setText(QString::number(Data::init_calc_value));

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

    // Initialize [OFF] button.
    connect(ui->button_backspace, SIGNAL(released()),
		this, SLOT(backspaceButtonPressed()));

	// Initialize [View] menu bar tab.
	calc_modes_ = new QActionGroup(this);
	calc_modes_->addAction(ui->actionBasic);
	calc_modes_->addAction(ui->actionScientific);
	
	ui->actionBasic->setChecked(true);

	connect(calc_modes_, SIGNAL(triggered(QAction*)),
		this, SLOT(menuViewModeChanged()));
}

Calc::~Calc()
{
    delete ui;
}