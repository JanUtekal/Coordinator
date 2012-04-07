/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created: Wed 4. Apr 18:12:29 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../controller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Controller[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      22,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   11,   11,   11, 0x0a,
      66,   58,   11,   11, 0x0a,
     108,   98,   11,   11, 0x0a,
     146,   98,   11,   11, 0x0a,
     183,   98,   11,   11, 0x0a,
     238,  223,   11,   11, 0x0a,
     285,  281,   11,   11, 0x0a,

 // methods: signature, parameters, type, tag, flags
     313,   11,  309,   11, 0x02,
     337,  335,  327,   11, 0x02,
     358,  335,  352,   11, 0x02,
     373,  335,  352,   11, 0x02,
     388,   11,  352,   11, 0x02,
     402,   11,  352,   11, 0x02,
     418,  416,   11,   11, 0x02,
     448,  335,  439,   11, 0x02,
     468,   11,  309,   11, 0x02,
     485,   11,   11,   11, 0x02,
     498,   11,  309,   11, 0x02,
     529,  335,  522,   11, 0x02,
     557,  335,  522,   11, 0x02,
     585,   11,  309,   11, 0x02,
     612,  335,  522,   11, 0x02,
     643,  335,  522,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Controller[] = {
    "Controller\0\0refresh()\0refreshMyPosition()\0"
    "refreshPoints()\0lon,lat\0"
    "updateMyPosition(double,double)\0"
    "coordList\0getPointFromCentral(QVector<QPointF>)\0"
    "getLineFromCentral(QVector<QPointF>)\0"
    "getPolygonFromCentral(QVector<QPointF>)\0"
    "jid,coordinate\0"
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
    "getPolygonCoordinatesNum()\0"
    "getPolygonCoordinateLatAt(int)\0"
    "getPolygonCoordinateLonAt(int)\0"
};

const QMetaObject Controller::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Controller,
      qt_meta_data_Controller, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Controller::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Controller))
        return static_cast<void*>(const_cast< Controller*>(this));
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 4: getPointFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1]))); break;
        case 5: getLineFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1]))); break;
        case 6: getPolygonFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1]))); break;
        case 7: updateUserPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 8: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { int _r = getPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { QString _r = getJidFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { float _r = getLatFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 12: { float _r = getLonFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 13: { float _r = getLatForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 14: { float _r = getLonForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 15: setToVlist((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 16: { QVariant _r = getFromVlistAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 17: { int _r = getMapPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: clearVlist(); break;
        case 19: { int _r = getLineCoordinatesNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: { double _r = getLineCoordinateLatAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 21: { double _r = getLineCoordinateLonAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 22: { int _r = getPolygonCoordinatesNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 23: { double _r = getPolygonCoordinateLatAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 24: { double _r = getPolygonCoordinateLonAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void Controller::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Controller::refreshMyPosition()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
