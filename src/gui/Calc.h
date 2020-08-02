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
 	
 	Calc.h
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
	
    [[nodiscard]] Ui::Calc* getUi() const				{ return ui; }
    [[nodiscard]] QActionGroup* getCalcModes() const	{ return calc_modes_; }
    [[nodiscard]] QLineEdit* getCurrDisplay() const		{ return curr_display_; }
	
	friend class Settings;

private:
	
	Ui::Calc *ui;
	CalcCore* core_{};
	
	QActionGroup* calc_modes_;
	QLineEdit* curr_display_;

	void unaryButtonPressed(double (*func)(double)) const;

public slots:
// basicCalc.cpp
	
	void numButtonPressed() const;
	void commaButtonPressed() const;	
	void mathButtonPressed() const;
	
	void equalButtonPressed() const;
	void percentButtonPressed() const;	

	void squareButtonPressed();
	void sqrtButtonPressed() const;

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
	void randButtonPressed() const;
	
	void logBase2ButtonPressed() const;
	void logBase10ButtonPressed() const;
	void lnButtonPressed() const;

	void factorialButtonPressed() const;	
	void expButtonPressed() const;
	void e10ToXButtonPressed() const;
	
	void absButtonPressed() const;
	void inverseButtonPressed() const;

	void sinClicked() const;
	void cosClicked() const;
	void tanClicked() const;
	void cotClicked() const;
	void secClicked() const;
	void cscClicked() const;

	void arcsinClicked() const;
	void arccosClicked() const;
	void arctanClicked() const;
	void arccotClicked() const;
	void arcsecClicked() const;
	void arccscClicked() const;

	void sinhClicked() const;
	void coshClicked() const;
	void tanhClicked() const;
	void cothClicked() const;
	void sechClicked() const;
	void cschClicked() const;

	void arsinhClicked() const;
	void arcoshClicked() const;
	void artanhClicked() const;
	void arcothClicked() const;
	void arsechClicked() const;
	void arcschClicked() const;
};