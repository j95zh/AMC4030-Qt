/****************************************************************************
** Meta object code from reading C++ file 'iostatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../iostatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iostatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IOStatus_t {
    QByteArrayData data[15];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IOStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IOStatus_t qt_meta_stringdata_IOStatus = {
    {
QT_MOC_LITERAL(0, 0, 8), // "IOStatus"
QT_MOC_LITERAL(1, 9, 15), // "deleteIO_Dialog"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "refreshStatus"
QT_MOC_LITERAL(4, 40, 15), // "treeItemChanged"
QT_MOC_LITERAL(5, 56, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 73, 4), // "item"
QT_MOC_LITERAL(7, 78, 15), // "treeItemClicked"
QT_MOC_LITERAL(8, 94, 20), // "on_pb_SetCur_clicked"
QT_MOC_LITERAL(9, 115, 22), // "on_pb_StartCur_clicked"
QT_MOC_LITERAL(10, 138, 21), // "on_pb_StopCur_clicked"
QT_MOC_LITERAL(11, 160, 22), // "on_pb_ResetCur_clicked"
QT_MOC_LITERAL(12, 183, 22), // "on_pb_StartAll_clicked"
QT_MOC_LITERAL(13, 206, 21), // "on_pb_StopAll_clicked"
QT_MOC_LITERAL(14, 228, 22) // "on_pb_ResetAll_clicked"

    },
    "IOStatus\0deleteIO_Dialog\0\0refreshStatus\0"
    "treeItemChanged\0QTreeWidgetItem*\0item\0"
    "treeItemClicked\0on_pb_SetCur_clicked\0"
    "on_pb_StartCur_clicked\0on_pb_StopCur_clicked\0"
    "on_pb_ResetCur_clicked\0on_pb_StartAll_clicked\0"
    "on_pb_StopAll_clicked\0on_pb_ResetAll_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IOStatus[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   70,    2, 0x08 /* Private */,
       4,    1,   71,    2, 0x08 /* Private */,
       7,    1,   74,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Int,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IOStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IOStatus *_t = static_cast<IOStatus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->deleteIO_Dialog();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->refreshStatus(); break;
        case 2: _t->treeItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->treeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->on_pb_SetCur_clicked(); break;
        case 5: _t->on_pb_StartCur_clicked(); break;
        case 6: _t->on_pb_StopCur_clicked(); break;
        case 7: _t->on_pb_ResetCur_clicked(); break;
        case 8: _t->on_pb_StartAll_clicked(); break;
        case 9: _t->on_pb_StopAll_clicked(); break;
        case 10: _t->on_pb_ResetAll_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef int (IOStatus::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IOStatus::deleteIO_Dialog)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject IOStatus::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IOStatus.data,
      qt_meta_data_IOStatus,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *IOStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IOStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_IOStatus.stringdata0))
        return static_cast<void*>(const_cast< IOStatus*>(this));
    return QDialog::qt_metacast(_clname);
}

int IOStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
int IOStatus::deleteIO_Dialog()
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
