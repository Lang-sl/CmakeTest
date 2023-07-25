/****************************************************************************
** Meta object code from reading C++ file 'CmakeTest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/CmakeTest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CmakeTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CmakeTest_t {
    QByteArrayData data[12];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CmakeTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CmakeTest_t qt_meta_stringdata_CmakeTest = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CmakeTest"
QT_MOC_LITERAL(1, 10, 24), // "onToolBarActionTriggered"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "QAction*"
QT_MOC_LITERAL(4, 45, 6), // "action"
QT_MOC_LITERAL(5, 52, 10), // "updateTime"
QT_MOC_LITERAL(6, 63, 4), // "time"
QT_MOC_LITERAL(7, 68, 16), // "authRemindWindow"
QT_MOC_LITERAL(8, 85, 17), // "authSuccessWindow"
QT_MOC_LITERAL(9, 103, 4), // "auth"
QT_MOC_LITERAL(10, 108, 4), // "quit"
QT_MOC_LITERAL(11, 113, 6) // "cancel"

    },
    "CmakeTest\0onToolBarActionTriggered\0\0"
    "QAction*\0action\0updateTime\0time\0"
    "authRemindWindow\0authSuccessWindow\0"
    "auth\0quit\0cancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CmakeTest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       5,    1,   52,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,
      10,    0,   58,    2, 0x08 /* Private */,
      11,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CmakeTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CmakeTest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onToolBarActionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->updateTime((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->authRemindWindow(); break;
        case 3: _t->authSuccessWindow(); break;
        case 4: _t->auth(); break;
        case 5: _t->quit(); break;
        case 6: _t->cancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CmakeTest::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CmakeTest.data,
    qt_meta_data_CmakeTest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CmakeTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CmakeTest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CmakeTest.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CmakeTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
