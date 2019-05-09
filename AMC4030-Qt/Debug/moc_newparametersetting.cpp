/****************************************************************************
** Meta object code from reading C++ file 'newparametersetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../newparametersetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newparametersetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_newParameterSetting_t {
    QByteArrayData data[14];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_newParameterSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_newParameterSetting_t qt_meta_stringdata_newParameterSetting = {
    {
QT_MOC_LITERAL(0, 0, 19), // "newParameterSetting"
QT_MOC_LITERAL(1, 20, 29), // "on_Btn_ParameterLoade_clicked"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 28), // "on_Btn_ParameterSave_clicked"
QT_MOC_LITERAL(4, 80, 37), // "on_Btn_RestoreFactorySettings..."
QT_MOC_LITERAL(5, 118, 19), // "PulseFactor_SetText"
QT_MOC_LITERAL(6, 138, 28), // "DisplayContentsAccordingFile"
QT_MOC_LITERAL(7, 167, 14), // "ReadSysCfgFile"
QT_MOC_LITERAL(8, 182, 21), // "LoadDefaultSysCfgFile"
QT_MOC_LITERAL(9, 204, 11), // "OnSetActive"
QT_MOC_LITERAL(10, 216, 15), // "WriteSysCfgFile"
QT_MOC_LITERAL(11, 232, 11), // "changeEvent"
QT_MOC_LITERAL(12, 244, 7), // "QEvent*"
QT_MOC_LITERAL(13, 252, 1) // "e"

    },
    "newParameterSetting\0on_Btn_ParameterLoade_clicked\0"
    "\0on_Btn_ParameterSave_clicked\0"
    "on_Btn_RestoreFactorySettings_clicked\0"
    "PulseFactor_SetText\0DisplayContentsAccordingFile\0"
    "ReadSysCfgFile\0LoadDefaultSysCfgFile\0"
    "OnSetActive\0WriteSysCfgFile\0changeEvent\0"
    "QEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_newParameterSetting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,

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
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void newParameterSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        newParameterSetting *_t = static_cast<newParameterSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Btn_ParameterLoade_clicked(); break;
        case 1: _t->on_Btn_ParameterSave_clicked(); break;
        case 2: _t->on_Btn_RestoreFactorySettings_clicked(); break;
        case 3: _t->PulseFactor_SetText(); break;
        case 4: _t->DisplayContentsAccordingFile(); break;
        case 5: _t->ReadSysCfgFile(); break;
        case 6: _t->LoadDefaultSysCfgFile(); break;
        case 7: _t->OnSetActive(); break;
        case 8: _t->WriteSysCfgFile(); break;
        case 9: _t->changeEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject newParameterSetting::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_newParameterSetting.data,
      qt_meta_data_newParameterSetting,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *newParameterSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *newParameterSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_newParameterSetting.stringdata0))
        return static_cast<void*>(const_cast< newParameterSetting*>(this));
    return QDialog::qt_metacast(_clname);
}

int newParameterSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
