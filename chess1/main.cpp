//#include "chess1.h"
#include <QtWidgets/QApplication>

#include"SingleGame.h"
#pragma execution_character_set( "utf-8" )
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//人机的
	SingleGame w;
	//人人的
	//chess1 w;


	w.show();
	return a.exec();
}
