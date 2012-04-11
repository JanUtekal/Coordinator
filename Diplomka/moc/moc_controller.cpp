/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created: Tue 10. Apr 11:40:42 2012
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
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      22,   11,   11,   11, 0x05,
      52,   42,   11,   11, 0x05,
      92,   82,   11,   11, 0x05,
     118,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     133,   11,   11,   11, 0x0a,
     157,  149,   11,   11, 0x0a,
     216,  189,   11,   11, 0x0a,
     270,  189,   11,   11, 0x0a,
     323,  189,   11,   11, 0x0a,
     384,  379,   11,   11, 0x0a,
     413,  398,   11,   11, 0x0a,
     455,  440,   11,   11, 0x0a,
     502,  498,   11,   11, 0x0a,

 // methods: signature, parameters, type, tag, flags
     530,   11,  526,   11, 0x02,
     554,  552,  544,   11, 0x02,
     575,  552,  569,   11, 0x02,
     590,  552,  569,   11, 0x02,
     605,   11,  569,   11, 0x02,
     619,   11,  569,   11, 0x02,
     635,  633,   11,   11, 0x02,
     665,  552,  656,   11, 0x02,
     685,   11,  526,   11, 0x02,
     702,   11,   11,   11, 0x02,
     720,  715,  526,   11, 0x02,
     765,  758,  751,   11, 0x02,
     801,  758,  751,   11, 0x02,
     837,  715,  526,   11, 0x02,
     871,  758,  751,   11, 0x02,
     910,  758,  751,   11, 0x02,
     985,  949,   11,   11, 0x02,
    1040,  715,  656,   11, 0x02,
    1079, 1071,   11,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Controller[] = {
    "Controller\0\0refresh()\0refreshMyPosition()\0"
    "name,note\0changeNoteOf(QString,QString)\0"
    "mapObject\0displayNoteText(QVariant)\0"
    "hideNoteText()\0refreshPoints()\0lon,lat\0"
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
        case 5: refreshPoints(); break;
        case 6: updateMyPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: getPointFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 8: getLineFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 9: getPolygonFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 10: getNote((*reinterpret_cast< Note(*)>(_a[1]))); break;
        case 11: getNegativeObject((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: updateUserPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 13: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: { int _r = getPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { QString _r = getJidFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { float _r = getLatFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 17: { float _r = getLonFor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 18: { float _r = getLatForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 19: { float _r = getLonForMe();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 20: setToVlist((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 21: { QVariant _r = getFromVlistAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 22: { int _r = getMapPointNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 23: clearVlist(); break;
        case 24: { int _r = getLineCoordinatesNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: { double _r = getLineCoordinateLatAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 26: { double _r = getLineCoordinateLonAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 27: { int _r = getPolygonCoordinatesNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 28: { double _r = getPolygonCoordinateLatAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 29: { double _r = getPolygonCoordinateLonAt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 30: createMapObjectReference((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 31: { QVariant _r = getMapObjectReference((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 32: getObjectUnderCursor((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 33;
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
QT_END_MOC_NAMESPACE
