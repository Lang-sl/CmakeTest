//#ifndef FORM1_H
//#define FORM1_H

//=====================================================================>>>
#ifndef UNTITLEDDLL_GLOBAL_H
#define UNTITLEDDLL_GLOBAL_H

#ifdef UNTITLEDDLL_LIBRARY
#define FORM1_EXPORT  __declspec(dllexport)
#else
#define FORM1_EXPORT  __declspec(dllimport)
#endif
//=====================================================================>>>

#include <QMainWindow>

namespace Ui
{
class Form1;
}

class Form1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form1(QWidget *parent = nullptr);
    ~Form1();

private:
    Ui::Form1 *ui;
};

#endif // FORM1_H
