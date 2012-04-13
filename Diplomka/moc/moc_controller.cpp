/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created: Wed 11. Apr 19:30:44 2012
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
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      22,   11,   11,   11, 0x05,
      52,   42,   11,   11, 0x05,
      92,   82,   11,   11, 0x05,
     118,   11,   11,   11, 0x05,
     151,  133,   11,   11, 0x05,
     210,  200,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     238,   11,   11,   11, 0x0a,
     262,  254,   11,   11, 0x0a,
     321,  294,   11,   11, 0x0a,
     375,  294,   11,   11, 0x0a,
     428,  294,   11,   11, 0x0a,
     489,  484,   11,   11, 0x0a,
     518,  503,   11,   11, 0x0a,
     560,  545,   11,   11, 0x0a,
     607,  603,   11,   11, 0x0a,

 // methods: signature, parameters, type, tag, flags
     635,   11,  631,   11, 0x02,
     659,  657,  649,   11, 0x02,
     680,  657,  674,   11, 0x02,
     695,  657,  674,   11, 0x02,
     710,   11,  674,   11, 0x02,
     724,   11,  674,   11, 0x02,
     740,  738,   11,   11, 0x02,
     770,  657,  761,   11, 0x02,
     790,   11,  631,   11, 0x02,
     807,   11,   11,   11, 0x02,
     825,  820,  631,   11, 0x02,
     870,  863,  856,   11, 0x02,
     906,  863,  856,   11, 0x02,
     942,  820,  631,   11, 0x02,
     976,  863,  856,   11, 0x02,
    1015,  863,  856,   11, 0x02,
    1090, 1054,   11,   11, 0x02,
    1145,  820,  761,   11, 0x02,
    1184, 1176,   11,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Controller[] = {
    "Controller\0\0refresh()\0refreshMyPosition()\0"
    "name,note\0changeNoteOf(QString,QString)\0"
    "mapObject\0displayNoteText(QVariant)\0"
    "hideNoteText()\0userPoint,lat,lon\0"
    "updatePositionForMapUser(QVariant,double,double)\0"
    "userPoint\0setMapUserOffline(QVariant)\0"
    "refreshPoints()\0lon,lat\0"
    "updateMyPosition(double,double)\0"
    "coordList,mapObjectId,data\0"
    "getPointFromCentral(QVector<QPointF>,QString,QString)\0"
    "getLineFromCentral(QVector<QPointF>,QString,QString)\0"
    "getPolygonFromCentral(QVector<QPointF>,QString,QString)\0"
    "note\0getNote(Note)\0negativeObject\0"
    "getNegativeObject(QString)\0jid,coordinate\0"
    "updateUserPosition(QString,QGeoCoordinate)\0"
    "jid\0setUserOffline(QString)\0int\0"
    "getPointNum()\0QString\0i\0getJidFor(int)\0"
    "float\0getLatFor(int)\0getLonFor(int)\0"
    "getLatForMe()\0getLonForMe()\0v\0"
    "setToVlist(QVariant)\0QVariant\0"
    "getFromVlistAt(int)\0getMapPointNum()\0"
    "clearVlist()\0name\0getLineCoordinatesNum(QString)\0"
    "double\0name,i\0getLineCoordinateLatAt(QString,int)\0"
    "getLineCoordinateLonAt(QString,int)\0"
    "getPolygonCoordinatesNum(QString)\0"
    "getPolygonCoordinateLatAt(QString,int)\0"
    "getPolygonCoordinateLonAt(QString,int)\0"
    "paintedObject,name,type,coordinates\0"
    "createMapObjectReference(QVariant,QString,int,QString)\0"
    "getMapObjectReference(QString)\0lat,lon\0"
    "getObjectUnderCursor(double,double)\0"
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
        case 2: changeNoteOf((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: displayNoteText((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 4: hideNoteText(); break;
        case 5: updatePositionForMapUser((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 6: setMapUserOffline((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 7: refreshPoints(); break;
        case 8: updateMyPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: getPointFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 10: getLineFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 11: getPolygonFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 12: getNote((*reinterpret_cast< Note(*)>(_a[1]))); break;
        case 13: getNegativeObject((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: updateUserPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 15: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: { int _r = getPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: { QString _r = getJidFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 18: { float _r = getLatFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 19: { float _r = getLonFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 20: { float _r = getLatForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 21: { float _r = getLonForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 22: setToVlist((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 23: { QVariant _r = getFromVlistAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 24: { int _r = getMapPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: clearVlist(); break;
        case 26: { int _r = getLineCoordinatesNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 27: { double _r = getLineCoordinateLatAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 28: { double _r = getLineCoordinateLonAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 29: { int _r = getPolygonCoordinatesNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 30: { double _r = getPolygonCoordinateLatAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 31: { double _r = getPolygonCoordinateLonAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 32: createMapObjectReference((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 33: { QVariant _r = getMapObjectReference((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 34: getObjectUnderCursor((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 35;
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

// SIGNAL 2
void Controller::changeNoteOf(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Controller::displayNoteText(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Controller::hideNoteText()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Controller::updatePositionForMapUser(QVariant _t1, double _t2, double _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Controller::setMapUserOffline(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
