#include "Calc.h"
#include <QApplication>

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
 ///////////////////////////////////////////////////////////
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calc w;
    w.show();
    return QApplication::exec();
}
