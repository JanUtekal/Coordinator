/****************************************************************************
** Meta object code from reading C++ file 'interface.h'
**
** Created: Tue 27. Mar 17:51:50 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../interface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Interface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      21,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   10,   10,   10, 0x0a,
      65,   57,   10,   10, 0x0a,
     103,   97,   10,   10, 0x0a,
     137,  132,   10,   10, 0x0a,
     180,  165,   10,   10, 0x0a,
     227,  223,   10,   10, 0x0a,

 // methods: signature, parameters, type, tag, flags
     255,   10,  251,   10, 0x02,
     279,  277,  269,   10, 0x02,
     300,  277,  294,   10, 0x02,
     315,  277,  294,   10, 0x02,
     330,   10,  294,   10, 0x02,
     344,   10,  294,   10, 0x02,
     360,  358,   10,   10, 0x02,
     390,  277,  381,   10, 0x02,
     410,   10,  251,   10, 0x02,
     427,   10,   10,   10, 0x02,
     440,   10,  251,   10, 0x02,
     471,  277,  464,   10, 0x02,
     499,  277,  464,   10, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Interface[] = {
    "Interface\0\0refresh()\0refreshMyPosition()\0"
    "refreshPoints()\0lon,lat\0"
    "updateMyPosition(double,double)\0point\0"
    "getPointFromCentral(QString)\0line\0"
    "getLineFromCentral(QString)\0jid,coordinate\0"
    "updateUserPosition(QString,QGeoCoordinate)\0"
    "jid\0setUserOffline(QString)\0int\0"
    "getPointNum()\0QString\0i\0getJidFor(int)\0"
    "float\0getLatFor(int)\0getLonFor(int)\0"
    "getLatForMe()\0getLonForMe()\0v\0"
    "setToVlist(QVariant)\0QVariant\0"
    "getFromVlistAt(int)\0getMapPointNum()\0"
    "clearVlist()\0getLineCoordinatesNum()\0"
    "double\0getLineCoordinateLatAt(int)\0"
    "getLineCoordinateLonAt(int)\0"
};

const QMetaObject Interface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Interface,
      qt_meta_data_Interface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Interface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Interface))
        return static_cast<void*>(const_cast< Interface*>(this));
    return QObject::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refresh(); break;
        case 1: refreshMyPosition(); break;
        case 2: refreshPoints(); break;
        case 3: updateMyPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 4: getPointFromCentral((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: getLineFromCentral((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: updateUserPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 7: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: { int _r = getPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { QString _r = getJidFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { float _r = getLatFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 11: { float _r = getLonFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 12: { float _r = getLatForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 13: { float _r = getLonForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 14: setToVlist((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 15: { QVariant _r = getFromVlistAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 16: { int _r = getMapPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: clearVlist(); break;
        case 18: { int _r = getLineCoordinatesNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 19: { double _r = getLineCoordinateLatAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 20: { double _r = getLineCoordinateLonAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void Interface::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Interface::refreshMyPosition()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
