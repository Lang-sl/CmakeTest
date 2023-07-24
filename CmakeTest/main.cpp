#include <QtWidgets/QApplication>
#include <qresource.h>

#include "CmakeTest.h"
#include "Config.h"

//using namespace std;

int main(int argc, char *argv[])
{
	//cout << "Test Cmake Qt" << endl;
	QApplication a(argc, argv);
	//QResource::registerResource(GAME_RES_PATH);
	CmakeTest ct;
	ct.show();
	return a.exec();
}