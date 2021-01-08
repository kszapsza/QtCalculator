//
// Created by kszap on 19.08.2020.
//

#include <stdexcept>

#include "./gui/Calc.h"
#include "./core/bitwise.h"
#include "./core/core.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza

 	core/programmerCalc.cpp
 	Functions associated with Programmer mode.
///////////////////////////////////////////////////////////
*/

void Calc::changeNumericSystem(numeric_systems old_system, numeric_systems new_system, QString old_value)
{
	try
	{
		switch (new_system)
		{
		case numeric_systems::dec:
			// DEC
			core_->data.setNumsys(numeric_systems::dec);
			curr_display_->setText(core::converter(old_system, numeric_systems::dec, old_value));
			ui->statusbar->showMessage("Changed numeric system to Decimal.", 2000);

			enableButtons<QPushButton*>(ui->button_2_prog, ui->button_3_prog, ui->button_4_prog, ui->button_5_prog,
					ui->button_6_prog, ui->button_7_prog, ui->button_8_prog, ui->button_9_prog);
			disableButtons<QPushButton*>(ui->button_hex_A, ui->button_hex_B, ui->button_hex_C, ui->button_hex_D,
					ui->button_hex_E, ui->button_hex_F);
			break;

		case numeric_systems::bin:
			// BIN
			core_->data.setNumsys(numeric_systems::bin);
			curr_display_->setText(core::converter(old_system, numeric_systems::bin, old_value));
			ui->statusbar->showMessage("Changed numeric system to Binary.", 2000);

			disableButtons<QPushButton*>(ui->button_2_prog, ui->button_3_prog, ui->button_4_prog, ui->button_5_prog,
					ui->button_6_prog, ui->button_7_prog, ui->button_8_prog, ui->button_9_prog, ui->button_hex_A,
					ui->button_hex_B, ui->button_hex_C, ui->button_hex_D, ui->button_hex_E, ui->button_hex_F);
			break;

		case numeric_systems::hex:
			// HEX
			core_->data.setNumsys(numeric_systems::hex);
			curr_display_->setText(core::converter(old_system, numeric_systems::hex, old_value));
			ui->statusbar->showMessage("Changed numeric system to Hexadecimal.", 2000);

			enableButtons<QPushButton*>(ui->button_2_prog, ui->button_3_prog, ui->button_4_prog, ui->button_5_prog,
					ui->button_6_prog, ui->button_7_prog, ui->button_8_prog, ui->button_9_prog, ui->button_hex_A,
					ui->button_hex_B, ui->button_hex_C, ui->button_hex_D, ui->button_hex_E, ui->button_hex_F);
			break;

		case numeric_systems::oct:
			// OCT
			core_->data.setNumsys(numeric_systems::oct);
			curr_display_->setText(core::converter(old_system, numeric_systems::oct, old_value));
			ui->statusbar->showMessage("Changed numeric system to Octal.", 2000);

			enableButtons<QPushButton*>(ui->button_2_prog, ui->button_3_prog, ui->button_4_prog, ui->button_5_prog,
					ui->button_6_prog, ui->button_7_prog);
			disableButtons<QPushButton*>(ui->button_8_prog, ui->button_9_prog, ui->button_hex_A, ui->button_hex_B,
					ui->button_hex_C, ui->button_hex_D, ui->button_hex_E, ui->button_hex_F);
			break;
		}
	}
	catch (std::runtime_error& except)
	{
		clearButtonPressed();
		ui->statusbar->showMessage(except.what(), 2000);
	}
}

void Calc::numericSystemBoxChanged()
{
	const numeric_systems old_system{ core_->data.getNumsys() };
	const numeric_systems new_system{ static_cast<numeric_systems>(ui->box_numeric_system->currentIndex()) };
	QString old_value{ curr_display_->text() };

	changeNumericSystem(old_system, new_system, old_value);
}

void Calc::programmerSignButtonPressed()
{
	const auto old_val = static_cast<std::int64_t>(core_->data.inputFormatter(curr_display_));
	const std::int64_t new_val = old_val * -1;

	const QString new_val_str = core_->resultFormatter(new_val);
	curr_display_->setText(new_val_str);
}

// Performing steps manually because we don't want to create
// separate additional performUnary overload for int64_t.
void Calc::notButtonPressed()
{
	// As seen on performUnaryOperation @ core.h.
	curr_display_input_mode_ = input_mode::substitute;
	core_->data.takeUnaryFromDisp(curr_display_);
	core_->data.resetSubsequentEqualPresses();

	// noexcept
	const auto res = core::lnot(core_->data.getUnary());
	const auto res_str = core_->resultFormatter(res);

	curr_display_->setText(res_str);
	core_->data.setLastResult(res);
}