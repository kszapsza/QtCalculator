#ifndef CALC_H
#define CALC_H

#ifndef CALC_TESTS
#include "./ui_Calc.h"
#else
// ?
#endif // CALC_TESTS

#include "log/basicCore.h"

#include <QMainWindow>
#include <QActionGroup>
#include <QLineEdit>

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

class Calc final : public QMainWindow
{
    Q_OBJECT

public:
	
	explicit Calc(CalcCore* core, QWidget *parent = nullptr);
    ~Calc() override;
	
    [[nodiscard]] Ui::Calc* getUi() const				{ return ui; }
    [[nodiscard]] QActionGroup* getCalcModes() const	{ return calc_modes_; }
    [[nodiscard]] QLineEdit* getCurrDisplay() const		{ return curr_display_; }

private:
	
	Ui::Calc *ui;
	CalcCore* core_{};
	
	QActionGroup* calc_modes_;
	QLineEdit* curr_display_;

	void loadConfig();	
	friend class Settings;

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
#endif // CALC_H