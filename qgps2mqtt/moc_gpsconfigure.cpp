/****************************************************************************
** Meta object code from reading C++ file 'gpsconfigure.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gpsconfigure.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpsconfigure.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gpsconfigure_t {
    QByteArrayData data[9];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gpsconfigure_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gpsconfigure_t qt_meta_stringdata_gpsconfigure = {
    {
QT_MOC_LITERAL(0, 0, 12), // "gpsconfigure"
QT_MOC_LITERAL(1, 13, 40), // "callInitializeGpsSignalWhenIs..."
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 17), // "getDataGpsUpdated"
QT_MOC_LITERAL(4, 73, 16), // "QGeoPositionInfo"
QT_MOC_LITERAL(5, 90, 4), // "info"
QT_MOC_LITERAL(6, 95, 17), // "getDataGpsChanged"
QT_MOC_LITERAL(7, 113, 36), // "InitializeGpsSignalWhenIssueH..."
QT_MOC_LITERAL(8, 150, 19) // "InitializeGpsSignal"

    },
    "gpsconfigure\0callInitializeGpsSignalWhenIssueHappened\0"
    "\0getDataGpsUpdated\0QGeoPositionInfo\0"
    "info\0getDataGpsChanged\0"
    "InitializeGpsSignalWhenIssueHappened\0"
    "InitializeGpsSignal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gpsconfigure[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   43,    2, 0x0a /* Public */,
       7,    0,   44,    2, 0x08 /* Private */,
       8,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void gpsconfigure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gpsconfigure *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->callInitializeGpsSignalWhenIssueHappened(); break;
        case 1: _t->getDataGpsUpdated((*reinterpret_cast< const QGeoPositionInfo(*)>(_a[1]))); break;
        case 2: _t->getDataGpsChanged(); break;
        case 3: _t->InitializeGpsSignalWhenIssueHappened(); break;
        case 4: _t->InitializeGpsSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGeoPositionInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (gpsconfigure::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gpsconfigure::callInitializeGpsSignalWhenIssueHappened)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (gpsconfigure::*)(const QGeoPositionInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gpsconfigure::getDataGpsUpdated)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gpsconfigure::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_gpsconfigure.data,
    qt_meta_data_gpsconfigure,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gpsconfigure::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gpsconfigure::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gpsconfigure.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int gpsconfigure::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void gpsconfigure::callInitializeGpsSignalWhenIssueHappened()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void gpsconfigure::getDataGpsUpdated(const QGeoPositionInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
