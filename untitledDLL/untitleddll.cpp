#include "untitleddll.h"
#include "form1.h"

#include <QApplication>
UntitledDLL::UntitledDLL()
{
}

/**
MFC中调用界面必须要先调用此函数，因为qt界面运行必须有调用QApplication的exec 方法，这样才能产生消息循环。
*/
extern "C" UNTITLEDDLL_EXPORT int testFormUI(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Form1 f;
    f.show();
    return a.exec();
}

