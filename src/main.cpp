#include "gui/Calc.h"
#include "core/core.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 ///////////////////////////////////////////////////////////
*/

int main(int argc, char *argv[])
{ 
	CalcCore calc_core{};

	QApplication a(argc, argv);
    Calc w(&calc_core, nullptr);
	
    w.show();
    return QApplication::exec();
}
