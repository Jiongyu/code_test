/****************************************************************************
** Meta object code from reading C++ file 'bleinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bleinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bleinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceInfo_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceInfo_t qt_meta_stringdata_DeviceInfo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DeviceInfo"
QT_MOC_LITERAL(1, 11, 13), // "deviceChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "deviceName"
QT_MOC_LITERAL(4, 37, 13) // "deviceAddress"

    },
    "DeviceInfo\0deviceChanged\0\0deviceName\0"
    "deviceAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       2,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00495001,
       4, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       0,

       0        // eod
};

void DeviceInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeviceInfo *_t = static_cast<DeviceInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deviceChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInfo::deviceChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        DeviceInfo *_t = static_cast<DeviceInfo *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getAddress(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DeviceInfo::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DeviceInfo.data,
    qt_meta_data_DeviceInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DeviceInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceInfo.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeviceInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceInfo::deviceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_BLEInterface_t {
    QByteArrayData data[47];
    char stringdata0[751];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BLEInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BLEInterface_t qt_meta_stringdata_BLEInterface = {
    {
QT_MOC_LITERAL(0, 0, 12), // "BLEInterface"
QT_MOC_LITERAL(1, 13, 20), // "currentDeviceChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 13), // "currentDevice"
QT_MOC_LITERAL(4, 49, 19), // "devicesNamesChanged"
QT_MOC_LITERAL(5, 69, 12), // "devicesNames"
QT_MOC_LITERAL(6, 82, 15), // "servicesChanged"
QT_MOC_LITERAL(7, 98, 8), // "services"
QT_MOC_LITERAL(8, 107, 17), // "statusInfoChanged"
QT_MOC_LITERAL(9, 125, 4), // "info"
QT_MOC_LITERAL(10, 130, 6), // "isGood"
QT_MOC_LITERAL(11, 137, 12), // "dataReceived"
QT_MOC_LITERAL(12, 150, 4), // "data"
QT_MOC_LITERAL(13, 155, 16), // "connectedChanged"
QT_MOC_LITERAL(14, 172, 9), // "connected"
QT_MOC_LITERAL(15, 182, 21), // "currentServiceChanged"
QT_MOC_LITERAL(16, 204, 14), // "currentService"
QT_MOC_LITERAL(17, 219, 17), // "set_currentDevice"
QT_MOC_LITERAL(18, 237, 17), // "setCurrentService"
QT_MOC_LITERAL(19, 255, 9), // "addDevice"
QT_MOC_LITERAL(20, 265, 20), // "QBluetoothDeviceInfo"
QT_MOC_LITERAL(21, 286, 14), // "onScanFinished"
QT_MOC_LITERAL(22, 301, 17), // "onDeviceScanError"
QT_MOC_LITERAL(23, 319, 37), // "QBluetoothDeviceDiscoveryAgen..."
QT_MOC_LITERAL(24, 357, 19), // "onServiceDiscovered"
QT_MOC_LITERAL(25, 377, 14), // "QBluetoothUuid"
QT_MOC_LITERAL(26, 392, 17), // "onServiceScanDone"
QT_MOC_LITERAL(27, 410, 17), // "onControllerError"
QT_MOC_LITERAL(28, 428, 27), // "QLowEnergyController::Error"
QT_MOC_LITERAL(29, 456, 17), // "onDeviceConnected"
QT_MOC_LITERAL(30, 474, 20), // "onDeviceDisconnected"
QT_MOC_LITERAL(31, 495, 21), // "onServiceStateChanged"
QT_MOC_LITERAL(32, 517, 31), // "QLowEnergyService::ServiceState"
QT_MOC_LITERAL(33, 549, 1), // "s"
QT_MOC_LITERAL(34, 551, 23), // "onCharacteristicChanged"
QT_MOC_LITERAL(35, 575, 24), // "QLowEnergyCharacteristic"
QT_MOC_LITERAL(36, 600, 1), // "c"
QT_MOC_LITERAL(37, 602, 5), // "value"
QT_MOC_LITERAL(38, 608, 12), // "serviceError"
QT_MOC_LITERAL(39, 621, 31), // "QLowEnergyService::ServiceError"
QT_MOC_LITERAL(40, 653, 1), // "e"
QT_MOC_LITERAL(41, 655, 4), // "read"
QT_MOC_LITERAL(42, 660, 20), // "onCharacteristicRead"
QT_MOC_LITERAL(43, 681, 21), // "onCharacteristicWrite"
QT_MOC_LITERAL(44, 703, 21), // "update_currentService"
QT_MOC_LITERAL(45, 725, 13), // "currentSerice"
QT_MOC_LITERAL(46, 739, 11) // "scanDevices"

    },
    "BLEInterface\0currentDeviceChanged\0\0"
    "currentDevice\0devicesNamesChanged\0"
    "devicesNames\0servicesChanged\0services\0"
    "statusInfoChanged\0info\0isGood\0"
    "dataReceived\0data\0connectedChanged\0"
    "connected\0currentServiceChanged\0"
    "currentService\0set_currentDevice\0"
    "setCurrentService\0addDevice\0"
    "QBluetoothDeviceInfo\0onScanFinished\0"
    "onDeviceScanError\0"
    "QBluetoothDeviceDiscoveryAgent::Error\0"
    "onServiceDiscovered\0QBluetoothUuid\0"
    "onServiceScanDone\0onControllerError\0"
    "QLowEnergyController::Error\0"
    "onDeviceConnected\0onDeviceDisconnected\0"
    "onServiceStateChanged\0"
    "QLowEnergyService::ServiceState\0s\0"
    "onCharacteristicChanged\0"
    "QLowEnergyCharacteristic\0c\0value\0"
    "serviceError\0QLowEnergyService::ServiceError\0"
    "e\0read\0onCharacteristicRead\0"
    "onCharacteristicWrite\0update_currentService\0"
    "currentSerice\0scanDevices"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BLEInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       5,  210, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  139,    2, 0x06 /* Public */,
       4,    1,  142,    2, 0x06 /* Public */,
       6,    1,  145,    2, 0x06 /* Public */,
       8,    2,  148,    2, 0x06 /* Public */,
      11,    1,  153,    2, 0x06 /* Public */,
      13,    1,  156,    2, 0x06 /* Public */,
      15,    1,  159,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  162,    2, 0x0a /* Public */,
      18,    1,  165,    2, 0x0a /* Public */,
      19,    1,  168,    2, 0x08 /* Private */,
      21,    0,  171,    2, 0x08 /* Private */,
      22,    1,  172,    2, 0x08 /* Private */,
      24,    1,  175,    2, 0x08 /* Private */,
      26,    0,  178,    2, 0x08 /* Private */,
      27,    1,  179,    2, 0x08 /* Private */,
      29,    0,  182,    2, 0x08 /* Private */,
      30,    0,  183,    2, 0x08 /* Private */,
      31,    1,  184,    2, 0x08 /* Private */,
      34,    2,  187,    2, 0x08 /* Private */,
      38,    1,  192,    2, 0x08 /* Private */,
      41,    0,  195,    2, 0x08 /* Private */,
      42,    2,  196,    2, 0x08 /* Private */,
      43,    2,  201,    2, 0x08 /* Private */,
      44,    1,  206,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      46,    0,  209,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QStringList,    5,
    QMetaType::Void, QMetaType::QStringList,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    9,   10,
    QMetaType::Void, QMetaType::QByteArray,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Int,   16,

 // slots: parameters
    QMetaType::Bool, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,    2,
    QMetaType::Void, 0x80000000 | 25,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, 0x80000000 | 35, QMetaType::QByteArray,   36,   37,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 35, QMetaType::QByteArray,   36,   37,
    QMetaType::Void, 0x80000000 | 35, QMetaType::QByteArray,   36,   37,
    QMetaType::Void, QMetaType::Int,   45,

 // methods: parameters
    QMetaType::Void,

 // properties: name, type, flags
      14, QMetaType::Bool, 0x00495001,
      16, QMetaType::Int, 0x00495103,
       3, QMetaType::Int, 0x00495003,
       5, QMetaType::QStringList, 0x00495001,
       7, QMetaType::QStringList, 0x00495001,

 // properties: notify_signal_id
       5,
       6,
       0,
       1,
       2,

       0        // eod
};

void BLEInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BLEInterface *_t = static_cast<BLEInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentDeviceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->devicesNamesChanged((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->servicesChanged((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->statusInfoChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->dataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 5: _t->connectedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->currentServiceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { bool _r = _t->set_currentDevice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->setCurrentService((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->addDevice((*reinterpret_cast< const QBluetoothDeviceInfo(*)>(_a[1]))); break;
        case 10: _t->onScanFinished(); break;
        case 11: _t->onDeviceScanError((*reinterpret_cast< QBluetoothDeviceDiscoveryAgent::Error(*)>(_a[1]))); break;
        case 12: _t->onServiceDiscovered((*reinterpret_cast< const QBluetoothUuid(*)>(_a[1]))); break;
        case 13: _t->onServiceScanDone(); break;
        case 14: _t->onControllerError((*reinterpret_cast< QLowEnergyController::Error(*)>(_a[1]))); break;
        case 15: _t->onDeviceConnected(); break;
        case 16: _t->onDeviceDisconnected(); break;
        case 17: _t->onServiceStateChanged((*reinterpret_cast< QLowEnergyService::ServiceState(*)>(_a[1]))); break;
        case 18: _t->onCharacteristicChanged((*reinterpret_cast< const QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 19: _t->serviceError((*reinterpret_cast< QLowEnergyService::ServiceError(*)>(_a[1]))); break;
        case 20: _t->read(); break;
        case 21: _t->onCharacteristicRead((*reinterpret_cast< const QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 22: _t->onCharacteristicWrite((*reinterpret_cast< const QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 23: _t->update_currentService((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->scanDevices(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothDeviceInfo >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothUuid >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyController::Error >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceState >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyCharacteristic >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceError >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyCharacteristic >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyCharacteristic >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BLEInterface::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::currentDeviceChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::devicesNamesChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::servicesChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::statusInfoChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::dataReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::connectedChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (BLEInterface::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLEInterface::currentServiceChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        BLEInterface *_t = static_cast<BLEInterface *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isConnected(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->currentService(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->get_currentDevice(); break;
        case 3: *reinterpret_cast< QStringList*>(_v) = _t->get_devicesNames(); break;
        case 4: *reinterpret_cast< QStringList*>(_v) = _t->get_services(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        BLEInterface *_t = static_cast<BLEInterface *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setCurrentService(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->set_currentDevice(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject BLEInterface::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_BLEInterface.data,
    qt_meta_data_BLEInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BLEInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BLEInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BLEInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BLEInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BLEInterface::currentDeviceChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BLEInterface::devicesNamesChanged(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BLEInterface::servicesChanged(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BLEInterface::statusInfoChanged(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BLEInterface::dataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BLEInterface::connectedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void BLEInterface::currentServiceChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
