#pragma once

#ifndef CALC_TESTS
#include "./ui_Settings.h"
#else
// ?
#endif // CALC_TESTS

#include "./gui/Calc.h"
#include "./core/core.h"

namespace Ui { class Settings; }

struct Config;
class Calc;

class Settings final : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(Calc *parent = nullptr);
    ~Settings() override;

private:
    Ui::Settings *ui;
	
	Calc* calc_;
	Config unsaved_config_;

	bool changes_made_{ false };

public slots:
	void saveConfig() const;
	void reject() override;

//private slots:
	
};
