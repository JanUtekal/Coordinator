/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created: Sat 14. Apr 13:30:44 2012
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
      42,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

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
     330,  312,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     357,   11,   11,   11, 0x0a,
     381,  373,   11,   11, 0x0a,
     440,  413,   11,   11, 0x0a,
     494,  413,   11,   11, 0x0a,
     547,  413,   11,   11, 0x0a,
     608,  603,   11,   11, 0x0a,
     637,  622,   11,   11, 0x0a,
     679,  664,   11,   11, 0x0a,
     726,  722,   11,   11, 0x0a,
     758,  750,   11,   11, 0x0a,

 // methods: signature, parameters, type, tag, flags
     790,   11,  786,   11, 0x02,
     814,  812,  804,   11, 0x02,
     835,  812,  829,   11, 0x02,
     850,  812,  829,   11, 0x02,
     865,   11,  829,   11, 0x02,
     879,   11,  829,   11, 0x02,
     895,  893,   11,   11, 0x02,
     925,  812,  916,   11, 0x02,
     945,   11,  786,   11, 0x02,
     962,   11,   11,   11, 0x02,
     980,  975,  786,   11, 0x02,
    1025, 1018, 1011,   11, 0x02,
    1061, 1018, 1011,   11, 0x02,
    1097,  975,  786,   11, 0x02,
    1131, 1018, 1011,   11, 0x02,
    1170, 1018, 1011,   11, 0x02,
    1245, 1209,   11,   11, 0x02,
    1300,  975,  916,   11, 0x02,
    1339, 1331,   11,   11, 0x02,
    1375,  750,   11,   11, 0x02,
    1402,   11,  804,   11, 0x02,
    1423,  312,   11,   11, 0x02,

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
    "username,password\0reconnect(QString,QString)\0"
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
    "getCurrentDateTime()\0reconnectMe(QString,QString)\0"
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
        case 9: reconnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: refreshPoints(); break;
        case 11: updateMyPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 12: getPointFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 13: getLineFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 14: getPolygonFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 15: getNote((*reinterpret_cast< Note(*)>(_a[1]))); break;
        case 16: getNegativeObject((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: updateUserPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 18: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: getReceivedMessage((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 20: { int _r = getPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 21: { QString _r = getJidFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 22: { float _r = getLatFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 23: { float _r = getLonFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 24: { float _r = getLatForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 25: { float _r = getLonForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 26: setToVlist((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 27: { QVariant _r = getFromVlistAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 28: { int _r = getMapPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 29: clearVlist(); break;
        case 30: { int _r = getLineCoordinatesNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 31: { double _r = getLineCoordinateLatAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 32: { double _r = getLineCoordinateLonAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 33: { int _r = getPolygonCoordinatesNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 34: { double _r = getPolygonCoordinateLatAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 35: { double _r = getPolygonCoordinateLonAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 36: createMapObjectReference((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 37: { QVariant _r = getMapObjectReference((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 38: getObjectUnderCursor((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 39: sendMessageToUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: { QString _r = getCurrentDateTime();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 41: reconnectMe((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 42;
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

// SIGNAL 9
void Controller::reconnect(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
