/****************************************************************************
** Meta object code from reading C++ file 'amc4030.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../amc4030.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amc4030.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AMC4030_t {
    QByteArrayData data[13];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AMC4030_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AMC4030_t qt_meta_stringdata_AMC4030 = {
    {
QT_MOC_LITERAL(0, 0, 7), // "AMC4030"
QT_MOC_LITERAL(1, 8, 32), // "on_Btn_ConnectController_clicked"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 12), // "ParameterSet"
QT_MOC_LITERAL(4, 55, 13), // "ManualOperate"
QT_MOC_LITERAL(5, 69, 12), // "ProgramEdite"
QT_MOC_LITERAL(6, 82, 21), // "ChooseChineseLanguage"
QT_MOC_LITERAL(7, 104, 21), // "ChooseEnglishLanguage"
QT_MOC_LITERAL(8, 126, 24), // "WriteUserSettingsCfgFile"
QT_MOC_LITERAL(9, 151, 23), // "ReadUserSettingsCfgFile"
QT_MOC_LITERAL(10, 175, 20), // "on_Btn_About_clicked"
QT_MOC_LITERAL(11, 196, 17), // "ReadMachineStatus"
QT_MOC_LITERAL(12, 214, 3) // "get"

    },
    "AMC4030\0on_Btn_ConnectController_clicked\0"
    "\0ParameterSet\0ManualOperate\0ProgramEdite\0"
    "ChooseChineseLanguage\0ChooseEnglishLanguage\0"
    "WriteUserSettingsCfgFile\0"
    "ReadUserSettingsCfgFile\0on_Btn_About_clicked\0"
    "ReadMachineStatus\0get"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AMC4030[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void AMC4030::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AMC4030 *_t = static_cast<AMC4030 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Btn_ConnectController_clicked(); break;
        case 1: _t->ParameterSet(); break;
        case 2: _t->ManualOperate(); break;
        case 3: _t->ProgramEdite(); break;
        case 4: _t->ChooseChineseLanguage(); break;
        case 5: _t->ChooseEnglishLanguage(); break;
        case 6: _t->WriteUserSettingsCfgFile(); break;
        case 7: _t->ReadUserSettingsCfgFile(); break;
        case 8: _t->on_Btn_About_clicked(); break;
        case 9: _t->ReadMachineStatus(); break;
        case 10: _t->get((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AMC4030::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AMC4030.data,
      qt_meta_data_AMC4030,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AMC4030::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AMC4030::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AMC4030.stringdata0))
        return static_cast<void*>(const_cast< AMC4030*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AMC4030::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
