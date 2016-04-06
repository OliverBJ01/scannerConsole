/****************************************************************************
** Meta object code from reading C++ file 'scannerDraw.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scannerconsole_01/scannerDraw.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scannerDraw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScannerDraw_t {
    QByteArrayData data[15];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScannerDraw_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScannerDraw_t qt_meta_stringdata_ScannerDraw = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ScannerDraw"
QT_MOC_LITERAL(1, 12, 8), // "finished"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 15), // "sendScannerMssg"
QT_MOC_LITERAL(4, 38, 3), // "cmd"
QT_MOC_LITERAL(5, 42, 2), // "x1"
QT_MOC_LITERAL(6, 45, 2), // "y1"
QT_MOC_LITERAL(7, 48, 7), // "laserOn"
QT_MOC_LITERAL(8, 56, 8), // "laserOff"
QT_MOC_LITERAL(9, 65, 9), // "scannerOn"
QT_MOC_LITERAL(10, 75, 10), // "scannerOff"
QT_MOC_LITERAL(11, 86, 13), // "drawRectangle"
QT_MOC_LITERAL(12, 100, 9), // "Bresenham"
QT_MOC_LITERAL(13, 110, 2), // "x2"
QT_MOC_LITERAL(14, 113, 2) // "y2"

    },
    "ScannerDraw\0finished\0\0sendScannerMssg\0"
    "cmd\0x1\0y1\0laserOn\0laserOff\0scannerOn\0"
    "scannerOff\0drawRectangle\0Bresenham\0"
    "x2\0y2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScannerDraw[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    3,   55,    2, 0x06 /* Public */,
       7,    0,   62,    2, 0x06 /* Public */,
       8,    0,   63,    2, 0x06 /* Public */,
       9,    0,   64,    2, 0x06 /* Public */,
      10,    0,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   66,    2, 0x0a /* Public */,
      12,    4,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,   13,   14,

       0        // eod
};

void ScannerDraw::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScannerDraw *_t = static_cast<ScannerDraw *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->sendScannerMssg((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< ushort(*)>(_a[2])),(*reinterpret_cast< ushort(*)>(_a[3]))); break;
        case 2: _t->laserOn(); break;
        case 3: _t->laserOff(); break;
        case 4: _t->scannerOn(); break;
        case 5: _t->scannerOff(); break;
        case 6: _t->drawRectangle(); break;
        case 7: _t->Bresenham((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScannerDraw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScannerDraw::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (ScannerDraw::*_t)(ushort , ushort , ushort );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScannerDraw::sendScannerMssg)) {
                *result = 1;
            }
        }
        {
            typedef void (ScannerDraw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScannerDraw::laserOn)) {
                *result = 2;
            }
        }
        {
            typedef void (ScannerDraw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScannerDraw::laserOff)) {
                *result = 3;
            }
        }
        {
            typedef void (ScannerDraw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScannerDraw::scannerOn)) {
                *result = 4;
            }
        }
        {
            typedef void (ScannerDraw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScannerDraw::scannerOff)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject ScannerDraw::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScannerDraw.data,
      qt_meta_data_ScannerDraw,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScannerDraw::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScannerDraw::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScannerDraw.stringdata0))
        return static_cast<void*>(const_cast< ScannerDraw*>(this));
    return QObject::qt_metacast(_clname);
}

int ScannerDraw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ScannerDraw::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ScannerDraw::sendScannerMssg(ushort _t1, ushort _t2, ushort _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScannerDraw::laserOn()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ScannerDraw::laserOff()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void ScannerDraw::scannerOn()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void ScannerDraw::scannerOff()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
