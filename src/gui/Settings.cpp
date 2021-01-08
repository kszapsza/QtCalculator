#include <QFile>
#include <QMessageBox>

#include "./gui/Calc.h"
#include "./gui/Settings.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	Settings.cpp
 	Settings dialog window implementation.
///////////////////////////////////////////////////////////
*/

Settings::Settings(Calc* parent)
		:
		QDialog(parent), ui(new Ui::Settings)
{
	ui->setupUi(this);

	calc_ = parent;
	unsaved_config_ = parent->core_->config;

	ui->settingsInitValue->setValue(parent->core_->config.init_value);
	ui->settingsInitMode->setCurrentIndex(static_cast<int>(parent->core_->config.init_mode));

	const QMap<char, int> disp_format_ctoi = {{ 'e', 0 }, { 'E', 1 }, { 'f', 2 }, { 'g', 3 }, { 'G', 4 }};
	const QMap<int, char> disp_format_itoc = {{ 0, 'e' }, { 1, 'E' }, { 2, 'f' }, { 3, 'g' }, { 4, 'G' }};

	ui->settingsDispFormat->setCurrentIndex(disp_format_ctoi[parent->core_->config.disp_format]);

	connect(ui->settingsInitValue, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](const double settings_init_value)
			{
			  unsaved_config_.init_value = settings_init_value;
			  changes_made_ = true;
			});

	connect(ui->settingsInitMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
			[=](const int settings_init_mode)
			{
			  unsaved_config_.init_mode = static_cast<mode>(settings_init_mode);
			  changes_made_ = true;
			});

	connect(ui->settingsDispFormat, QOverload<int>::of(&QComboBox::currentIndexChanged),
			[=](const int settings_disp_format)
			{
			  unsaved_config_.disp_format = disp_format_itoc[settings_disp_format];
			  changes_made_ = true;
			});

	connect(ui->settingsButtons, SIGNAL(accepted()),
			this, SLOT(saveConfig()));
}

Settings::~Settings()
{
	delete ui;
}

void Settings::saveConfig() const
{
	if (changes_made_)
	{
		calc_->core_->config.init_value = unsaved_config_.init_value;
		calc_->core_->config.init_mode = unsaved_config_.init_mode;
		calc_->core_->config.disp_format = unsaved_config_.disp_format;

		QFile config_file("config.dat");

		if (config_file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream config_str(&config_file);

			config_str << calc_->core_->config.init_value << '\n';
			config_str << static_cast<int>(calc_->core_->config.init_mode) << '\n';
			config_str << calc_->core_->config.disp_format << '\n';
		}

		// Clear input as operations can work bad after changing formatting.
		calc_->clearButtonPressed();

		config_file.close();
	}
}

void Settings::reject()
{
	if (changes_made_)
	{
		const auto mbox_unsaved_decision = QMessageBox::warning(
				this, "Calculator", "You have unsaved changes. Do you wish to save?",
				QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);

		if (mbox_unsaved_decision == QMessageBox::Yes)
		{
			saveConfig();
		}
		else if (mbox_unsaved_decision != QMessageBox::Cancel)
		{
			QDialog::reject();
		}
	}
	else
	{
		QDialog::reject();
	}
}