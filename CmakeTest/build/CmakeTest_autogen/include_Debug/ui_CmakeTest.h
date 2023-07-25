/********************************************************************************
** Form generated from reading UI file 'CmakeTest.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAKETEST_H
#define UI_CMAKETEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CmakeTestClass
{
public:

    void setupUi(QWidget *CmakeTestClass)
    {
        if (CmakeTestClass->objectName().isEmpty())
            CmakeTestClass->setObjectName(QString::fromUtf8("CmakeTestClass"));
        CmakeTestClass->resize(600, 400);

        retranslateUi(CmakeTestClass);

        QMetaObject::connectSlotsByName(CmakeTestClass);
    } // setupUi

    void retranslateUi(QWidget *CmakeTestClass)
    {
        CmakeTestClass->setWindowTitle(QCoreApplication::translate("CmakeTestClass", "CmakeTest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CmakeTestClass: public Ui_CmakeTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAKETEST_H
