/****************************************************************************
** Meta object code from reading C++ file 'console.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scannerconsole_01/console.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'console.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Mwars_t {
    QByteArrayData data[65];
    char stringdata0[873];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mwars_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mwars_t qt_meta_stringdata_Mwars = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Mwars"
QT_MOC_LITERAL(1, 6, 14), // "connectScanner"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 15), // "sendScannerMssg"
QT_MOC_LITERAL(4, 38, 3), // "cmd"
QT_MOC_LITERAL(5, 42, 1), // "x"
QT_MOC_LITERAL(6, 44, 1), // "y"
QT_MOC_LITERAL(7, 46, 9), // "scannerOn"
QT_MOC_LITERAL(8, 56, 10), // "scannerOff"
QT_MOC_LITERAL(9, 67, 7), // "laserOn"
QT_MOC_LITERAL(10, 75, 8), // "laserOff"
QT_MOC_LITERAL(11, 84, 17), // "clientSocketState"
QT_MOC_LITERAL(12, 102, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(13, 131, 5), // "state"
QT_MOC_LITERAL(14, 137, 17), // "clientSocketError"
QT_MOC_LITERAL(15, 155, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(16, 184, 5), // "error"
QT_MOC_LITERAL(17, 190, 11), // "OnReadyRead"
QT_MOC_LITERAL(18, 202, 16), // "connectToScanner"
QT_MOC_LITERAL(19, 219, 13), // "disconnectedz"
QT_MOC_LITERAL(20, 233, 15), // "keepServerAlive"
QT_MOC_LITERAL(21, 249, 19), // "readScannerResponse"
QT_MOC_LITERAL(22, 269, 18), // "laserDisableToggle"
QT_MOC_LITERAL(23, 288, 11), // "sendScanCmd"
QT_MOC_LITERAL(24, 300, 13), // "scannerToggle"
QT_MOC_LITERAL(25, 314, 24), // "on_pbLaserToggle_clicked"
QT_MOC_LITERAL(26, 339, 12), // "resetScanner"
QT_MOC_LITERAL(27, 352, 9), // "verboseOn"
QT_MOC_LITERAL(28, 362, 10), // "verboseOff"
QT_MOC_LITERAL(29, 373, 16), // "clearStateWidets"
QT_MOC_LITERAL(30, 390, 14), // "testDataToggle"
QT_MOC_LITERAL(31, 405, 14), // "enableTestData"
QT_MOC_LITERAL(32, 420, 15), // "disableTestData"
QT_MOC_LITERAL(33, 436, 16), // "cameraDataToggle"
QT_MOC_LITERAL(34, 453, 16), // "enableCameraData"
QT_MOC_LITERAL(35, 470, 17), // "disableCameraData"
QT_MOC_LITERAL(36, 488, 14), // "disableWidgets"
QT_MOC_LITERAL(37, 503, 13), // "enableWidgets"
QT_MOC_LITERAL(38, 517, 14), // "centre_scanner"
QT_MOC_LITERAL(39, 532, 8), // "listener"
QT_MOC_LITERAL(40, 541, 15), // "calibrateToggle"
QT_MOC_LITERAL(41, 557, 11), // "calibrateOn"
QT_MOC_LITERAL(42, 569, 12), // "calibrateOff"
QT_MOC_LITERAL(43, 582, 11), // "readXMLFile"
QT_MOC_LITERAL(44, 594, 12), // "writeXMLFile"
QT_MOC_LITERAL(45, 607, 10), // "calSetULHC"
QT_MOC_LITERAL(46, 618, 10), // "calSetLRHC"
QT_MOC_LITERAL(47, 629, 15), // "ReadCamElements"
QT_MOC_LITERAL(48, 645, 12), // "calFullFrame"
QT_MOC_LITERAL(49, 658, 12), // "calHalfFrame"
QT_MOC_LITERAL(50, 671, 8), // "xCamTrim"
QT_MOC_LITERAL(51, 680, 8), // "yCamTrim"
QT_MOC_LITERAL(52, 689, 13), // "camTrimOffset"
QT_MOC_LITERAL(53, 703, 10), // "xCamOffset"
QT_MOC_LITERAL(54, 714, 10), // "yCamOffset"
QT_MOC_LITERAL(55, 725, 13), // "camScanOffset"
QT_MOC_LITERAL(56, 739, 14), // "alignBoresight"
QT_MOC_LITERAL(57, 754, 21), // "translateTargetCoords"
QT_MOC_LITERAL(58, 776, 7), // "ushort&"
QT_MOC_LITERAL(59, 784, 3), // "x_p"
QT_MOC_LITERAL(60, 788, 3), // "y_p"
QT_MOC_LITERAL(61, 792, 22), // "on_pbRectangle_clicked"
QT_MOC_LITERAL(62, 815, 17), // "rectangleFinished"
QT_MOC_LITERAL(63, 833, 13), // "stopRectangle"
QT_MOC_LITERAL(64, 847, 25) // "disableCalibrationWidgets"

    },
    "Mwars\0connectScanner\0\0sendScannerMssg\0"
    "cmd\0x\0y\0scannerOn\0scannerOff\0laserOn\0"
    "laserOff\0clientSocketState\0"
    "QAbstractSocket::SocketState\0state\0"
    "clientSocketError\0QAbstractSocket::SocketError\0"
    "error\0OnReadyRead\0connectToScanner\0"
    "disconnectedz\0keepServerAlive\0"
    "readScannerResponse\0laserDisableToggle\0"
    "sendScanCmd\0scannerToggle\0"
    "on_pbLaserToggle_clicked\0resetScanner\0"
    "verboseOn\0verboseOff\0clearStateWidets\0"
    "testDataToggle\0enableTestData\0"
    "disableTestData\0cameraDataToggle\0"
    "enableCameraData\0disableCameraData\0"
    "disableWidgets\0enableWidgets\0"
    "centre_scanner\0listener\0calibrateToggle\0"
    "calibrateOn\0calibrateOff\0readXMLFile\0"
    "writeXMLFile\0calSetULHC\0calSetLRHC\0"
    "ReadCamElements\0calFullFrame\0calHalfFrame\0"
    "xCamTrim\0yCamTrim\0camTrimOffset\0"
    "xCamOffset\0yCamOffset\0camScanOffset\0"
    "alignBoresight\0translateTargetCoords\0"
    "ushort&\0x_p\0y_p\0on_pbRectangle_clicked\0"
    "rectangleFinished\0stopRectangle\0"
    "disableCalibrationWidgets"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mwars[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  279,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,  280,    2, 0x0a /* Public */,
       7,    0,  287,    2, 0x0a /* Public */,
       8,    0,  288,    2, 0x0a /* Public */,
       9,    0,  289,    2, 0x0a /* Public */,
      10,    0,  290,    2, 0x0a /* Public */,
      11,    1,  291,    2, 0x08 /* Private */,
      14,    1,  294,    2, 0x08 /* Private */,
      17,    0,  297,    2, 0x08 /* Private */,
      18,    0,  298,    2, 0x08 /* Private */,
      19,    0,  299,    2, 0x08 /* Private */,
      20,    0,  300,    2, 0x08 /* Private */,
      21,    0,  301,    2, 0x08 /* Private */,
      22,    0,  302,    2, 0x08 /* Private */,
      23,    0,  303,    2, 0x08 /* Private */,
      24,    0,  304,    2, 0x08 /* Private */,
      25,    0,  305,    2, 0x08 /* Private */,
      26,    0,  306,    2, 0x08 /* Private */,
      27,    0,  307,    2, 0x08 /* Private */,
      28,    0,  308,    2, 0x08 /* Private */,
      29,    0,  309,    2, 0x08 /* Private */,
      30,    0,  310,    2, 0x08 /* Private */,
      31,    0,  311,    2, 0x08 /* Private */,
      32,    0,  312,    2, 0x08 /* Private */,
      33,    0,  313,    2, 0x08 /* Private */,
      34,    0,  314,    2, 0x08 /* Private */,
      35,    0,  315,    2, 0x08 /* Private */,
      36,    0,  316,    2, 0x08 /* Private */,
      37,    0,  317,    2, 0x08 /* Private */,
      38,    0,  318,    2, 0x08 /* Private */,
      39,    0,  319,    2, 0x08 /* Private */,
      40,    0,  320,    2, 0x08 /* Private */,
      41,    0,  321,    2, 0x08 /* Private */,
      42,    0,  322,    2, 0x08 /* Private */,
      43,    0,  323,    2, 0x08 /* Private */,
      44,    0,  324,    2, 0x08 /* Private */,
      45,    0,  325,    2, 0x08 /* Private */,
      46,    0,  326,    2, 0x08 /* Private */,
      47,    0,  327,    2, 0x08 /* Private */,
      48,    0,  328,    2, 0x08 /* Private */,
      49,    0,  329,    2, 0x08 /* Private */,
      50,    0,  330,    2, 0x08 /* Private */,
      51,    0,  331,    2, 0x08 /* Private */,
      52,    0,  332,    2, 0x08 /* Private */,
      53,    0,  333,    2, 0x08 /* Private */,
      54,    0,  334,    2, 0x08 /* Private */,
      55,    0,  335,    2, 0x08 /* Private */,
      56,    0,  336,    2, 0x08 /* Private */,
      57,    2,  337,    2, 0x08 /* Private */,
      61,    0,  342,    2, 0x08 /* Private */,
      62,    0,  343,    2, 0x08 /* Private */,
      63,    0,  344,    2, 0x08 /* Private */,
      64,    0,  345,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 58, 0x80000000 | 58,   59,   60,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Mwars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Mwars *_t = static_cast<Mwars *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectScanner(); break;
        case 1: _t->sendScannerMssg((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< ushort(*)>(_a[2])),(*reinterpret_cast< ushort(*)>(_a[3]))); break;
        case 2: _t->scannerOn(); break;
        case 3: _t->scannerOff(); break;
        case 4: _t->laserOn(); break;
        case 5: _t->laserOff(); break;
        case 6: _t->clientSocketState((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 7: _t->clientSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 8: _t->OnReadyRead(); break;
        case 9: _t->connectToScanner(); break;
        case 10: _t->disconnectedz(); break;
        case 11: _t->keepServerAlive(); break;
        case 12: _t->readScannerResponse(); break;
        case 13: _t->laserDisableToggle(); break;
        case 14: _t->sendScanCmd(); break;
        case 15: _t->scannerToggle(); break;
        case 16: _t->on_pbLaserToggle_clicked(); break;
        case 17: _t->resetScanner(); break;
        case 18: _t->verboseOn(); break;
        case 19: _t->verboseOff(); break;
        case 20: _t->clearStateWidets(); break;
        case 21: _t->testDataToggle(); break;
        case 22: _t->enableTestData(); break;
        case 23: _t->disableTestData(); break;
        case 24: _t->cameraDataToggle(); break;
        case 25: _t->enableCameraData(); break;
        case 26: _t->disableCameraData(); break;
        case 27: _t->disableWidgets(); break;
        case 28: _t->enableWidgets(); break;
        case 29: _t->centre_scanner(); break;
        case 30: _t->listener(); break;
        case 31: _t->calibrateToggle(); break;
        case 32: _t->calibrateOn(); break;
        case 33: _t->calibrateOff(); break;
        case 34: { int _r = _t->readXMLFile();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 35: { int _r = _t->writeXMLFile();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 36: _t->calSetULHC(); break;
        case 37: _t->calSetLRHC(); break;
        case 38: _t->ReadCamElements(); break;
        case 39: { int _r = _t->calFullFrame();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 40: { int _r = _t->calHalfFrame();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 41: _t->xCamTrim(); break;
        case 42: _t->yCamTrim(); break;
        case 43: { int _r = _t->camTrimOffset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 44: _t->xCamOffset(); break;
        case 45: _t->yCamOffset(); break;
        case 46: { int _r = _t->camScanOffset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 47: _t->alignBoresight(); break;
        case 48: _t->translateTargetCoords((*reinterpret_cast< ushort(*)>(_a[1])),(*reinterpret_cast< ushort(*)>(_a[2]))); break;
        case 49: _t->on_pbRectangle_clicked(); break;
        case 50: _t->rectangleFinished(); break;
        case 51: _t->stopRectangle(); break;
        case 52: _t->disableCalibrationWidgets(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Mwars::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mwars::connectScanner)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Mwars::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Mwars.data,
      qt_meta_data_Mwars,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Mwars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mwars::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Mwars.stringdata0))
        return static_cast<void*>(const_cast< Mwars*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Mwars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    }
    return _id;
}

// SIGNAL 0
void Mwars::connectScanner()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
