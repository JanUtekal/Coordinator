/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created: Fri 13. Apr 12:09:02 2012
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
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      22,   11,   11,   11, 0x05,
      52,   42,   11,   11, 0x05,
      92,   82,   11,   11, 0x05,
     118,   11,   11,   11, 0x05,
     151,  133,   11,   11, 0x05,
     210,  200,   11,   11, 0x05,
     250,  238,   11,   11, 0x05,
     284,  279,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     312,   11,   11,   11, 0x0a,
     336,  328,   11,   11, 0x0a,
     395,  368,   11,   11, 0x0a,
     449,  368,   11,   11, 0x0a,
     502,  368,   11,   11, 0x0a,
     563,  558,   11,   11, 0x0a,
     592,  577,   11,   11, 0x0a,
     634,  619,   11,   11, 0x0a,
     681,  677,   11,   11, 0x0a,
     713,  705,   11,   11, 0x0a,

 // methods: signature, parameters, type, tag, flags
     745,   11,  741,   11, 0x02,
     769,  767,  759,   11, 0x02,
     790,  767,  784,   11, 0x02,
     805,  767,  784,   11, 0x02,
     820,   11,  784,   11, 0x02,
     834,   11,  784,   11, 0x02,
     850,  848,   11,   11, 0x02,
     880,  767,  871,   11, 0x02,
     900,   11,  741,   11, 0x02,
     917,   11,   11,   11, 0x02,
     935,  930,  741,   11, 0x02,
     980,  973,  966,   11, 0x02,
    1016,  973,  966,   11, 0x02,
    1052,  930,  741,   11, 0x02,
    1086,  973,  966,   11, 0x02,
    1125,  973,  966,   11, 0x02,
    1200, 1164,   11,   11, 0x02,
    1255,  930,  871,   11, 0x02,
    1294, 1286,   11,   11, 0x02,
    1330,  705,   11,   11, 0x02,
    1357,   11,  759,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Controller[] = {
    "Controller\0\0refresh()\0refreshMyPosition()\0"
    "name,note\0changeNoteOf(QString,QString)\0"
    "mapObject\0displayNoteText(QVariant)\0"
    "hideNoteText()\0userPoint,lat,lon\0"
    "updatePositionForMapUser(QVariant,double,double)\0"
    "userPoint\0setMapUserOffline(QVariant)\0"
    "jid,message\0sendMessage(QString,QString)\0"
    "line\0newMessageFromUser(QString)\0"
    "refreshPoints()\0lon,lat\0"
    "updateMyPosition(double,double)\0"
    "coordList,mapObjectId,data\0"
    "getPointFromCentral(QVector<QPointF>,QString,QString)\0"
    "getLineFromCentral(QVector<QPointF>,QString,QString)\0"
    "getPolygonFromCentral(QVector<QPointF>,QString,QString)\0"
    "note\0getNote(Note)\0negativeObject\0"
    "getNegativeObject(QString)\0jid,coordinate\0"
    "updateUserPosition(QString,QGeoCoordinate)\0"
    "jid\0setUserOffline(QString)\0message\0"
    "getReceivedMessage(Message)\0int\0"
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
    "sendMessageToUser(QString)\0"
    "getCurrentDateTime()\0"
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
        case 7: sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: newMessageFromUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: refreshPoints(); break;
        case 10: updateMyPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 11: getPointFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 12: getLineFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 13: getPolygonFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 14: getNote((*reinterpret_cast< Note(*)>(_a[1]))); break;
        case 15: getNegativeObject((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: updateUserPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 17: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: getReceivedMessage((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 19: { int _r = getPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: { QString _r = getJidFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 21: { float _r = getLatFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 22: { float _r = getLonFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 23: { float _r = getLatForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 24: { float _r = getLonForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 25: setToVlist((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 26: { QVariant _r = getFromVlistAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 27: { int _r = getMapPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 28: clearVlist(); break;
        case 29: { int _r = getLineCoordinatesNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 30: { double _r = getLineCoordinateLatAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 31: { double _r = getLineCoordinateLonAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 32: { int _r = getPolygonCoordinatesNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 33: { double _r = getPolygonCoordinateLatAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 34: { double _r = getPolygonCoordinateLonAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 35: createMapObjectReference((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 36: { QVariant _r = getMapObjectReference((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 37: getObjectUnderCursor((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 38: sendMessageToUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 39: { QString _r = getCurrentDateTime();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 40;
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

// SIGNAL 7
void Controller::sendMessage(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Controller::newMessageFromUser(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
