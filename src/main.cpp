#include "gui/Calc.h"
#include "core/core.h"

/*
///////////////////////////////////////////////////////////
	Qt Calculator
 	2020, Karol Szapsza
///////////////////////////////////////////////////////////

	This software utilizes the Qt framework, available under
	the	GNU Lesser General Public License version 3.
	The Qt Toolkit is Copyright (C) 2018 The Qt Company Ltd.
	and other contributors.

///////////////////////////////////////////////////////////

	This software utilizes googletest library, licensed under
	BSD-3 Clause license. Copyright 2008, Google Inc.
	All rights reserved. See: /lib/googletest/LICENSE
	
 ///////////////////////////////////////////////////////////
*/

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Calc w(nullptr);

	w.show();
	return QApplication::exec();
}
