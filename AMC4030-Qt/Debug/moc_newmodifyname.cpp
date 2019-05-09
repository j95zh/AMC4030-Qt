/****************************************************************************
** Meta object code from reading C++ file 'newmodifyname.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../newmodifyname.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newmodifyname.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_newModifyName_t {
    QByteArrayData data[6];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_newModifyName_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_newModifyName_t qt_meta_stringdata_newModifyName = {
    {
QT_MOC_LITERAL(0, 0, 13), // "newModifyName"
QT_MOC_LITERAL(1, 14, 11), // "changeEvent"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "QEvent*"
QT_MOC_LITERAL(4, 35, 1), // "e"
QT_MOC_LITERAL(5, 37, 21) // "on_pushButton_clicked"

    },
    "newModifyName\0changeEvent\0\0QEvent*\0e\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_newModifyName[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       5,    0,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void newModifyName::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        newModifyName *_t = static_cast<newModifyName *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject newModifyName::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_newModifyName.data,
      qt_meta_data_newModifyName,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *newModifyName::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *newModifyName::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_newModifyName.stringdata0))
        return static_cast<void*>(const_cast< newModifyName*>(this));
    return QDialog::qt_metacast(_clname);
}

int newModifyName::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
