#pragma once

#ifndef CALC_TESTS
#include "./ui_Calc.h"
#else
// ?
#endif // CALC_TESTS

#include <QMainWindow>
#include <QActionGroup>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 	
 	gui/Calc.h
 	Calc class main header.
///////////////////////////////////////////////////////////
*/

QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

struct CalcCore;

class Calc final : public QMainWindow
{
    Q_OBJECT

public:
	
	explicit Calc(CalcCore* core, QWidget *parent = nullptr);
    ~Calc() override;
	
	friend class Settings;

private:
	
	Ui::Calc *ui;
	CalcCore* core_{};
	
	QActionGroup* calc_modes_;
	QLineEdit* curr_display_;
	
	enum class input_mode { concatenate = 0, substitute = 1 }
		curr_display_input_mode_ = input_mode::substitute;

	void unaryButtonPressed(double (*func)(double));

public slots:
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

	void memButtonPressed() const;
	void memAddButtonPressed() const;
	void memSubButtonPressed() const;

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