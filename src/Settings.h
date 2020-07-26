#ifndef SETTINGS_H
#define SETTINGS_H

#include "./ui_Settings.h"
#include "Calc.h"

namespace Ui { class Settings; }

struct Config;
class Calc;

class Settings final : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(Calc *parent = nullptr);
    ~Settings();

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

#endif // SETTINGS_H
