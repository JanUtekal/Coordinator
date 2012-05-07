/****************************************************************************
** Meta object code from reading C++ file 'locationwatcher.h'
**
** Created: Sat 5. May 20:45:03 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../locationwatcher.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'locationwatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocationWatcher[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   57,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LocationWatcher[] = {
    "LocationWatcher\0\0lon,lat\0"
    "updateMyLocation(double,double)\0info\0"
    "positionUpdated(QGeoPositionInfo)\0"
};

const QMetaObject LocationWatcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LocationWatcher,
      qt_meta_data_LocationWatcher, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocationWatcher::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocationWatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocationWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocationWatcher))
        return static_cast<void*>(const_cast< LocationWatcher*>(this));
    return QObject::qt_metacast(_clname);
}

int LocationWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateMyLocation((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: positionUpdated((*reinterpret_cast< const QGeoPositionInfo(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LocationWatcher::updateMyLocation(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
