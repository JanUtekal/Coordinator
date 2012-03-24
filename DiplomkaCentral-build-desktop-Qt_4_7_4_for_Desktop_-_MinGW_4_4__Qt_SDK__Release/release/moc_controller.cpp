/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created: Sat 24. Mar 15:23:59 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Diplomka-Central/controller.h"
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
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   12,   11,   11, 0x05,
      71,   53,   11,   11, 0x05,
     115,   11,   11,   11, 0x05,
     130,   11,   11,   11, 0x05,
     153,   11,   11,   11, 0x05,
     183,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     202,  190,   11,   11, 0x0a,
     249,  235,   11,   11, 0x0a,
     301,  286,   11,   11, 0x0a,
     348,  344,   11,   11, 0x0a,

 // methods: signature, parameters, type, tag, flags
     392,  372,   11,   11, 0x02,
     428,  420,   11,   11, 0x02,
     456,   11,   11,   11, 0x02,
     473,   11,   11,   11, 0x02,
     502,  495,   11,   11, 0x02,
     542,   11,  533,   11, 0x02,
     565,   11,   11,   11, 0x02,
     616,  587,   11,   11, 0x02,
     683,  678,   11,   11, 0x02,
     705,   11,   11,   11, 0x02,
     726,   11,  722,   11, 0x02,
     748,  746,  738,   11, 0x02,
     766,  746,   11,   11, 0x02,
     781,   11,   11,   11, 0x02,
     806,   11,  722,   11, 0x02,
     826,  746,  738,   11, 0x02,
     852,  746,  738,   11, 0x02,
     881,  746,   11,   11, 0x02,
     904,  746,   11,   11, 0x02,
     939,   11,  722,   11, 0x02,
     966,  746,  738,   11, 0x02,
     999,  746,  738,   11, 0x02,
    1039, 1035,   11,   11, 0x02,
    1066,  746,   11,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Controller[] = {
    "Controller\0\0landmarks\0"
    "sendObjects(QList<QLandmark>*)\0"
    "landmark,userList\0"
    "sendMapObject(QLandmark,QList<TerrainUser>)\0"
    "aclListReady()\0terrainUserListReady()\0"
    "terrainUserFromAclListReady()\0test()\0"
    "dbLandmarks\0getAllObjects(QList<QLandmark>*)\0"
    "userLandmarks\0getConnectedUsers(QList<QLandmark>*)\0"
    "jid,coordinate\0"
    "updateUserPosition(QString,QGeoCoordinate)\0"
    "jid\0setUserOffline(QString)\0"
    "lat,lon,selectedAcl\0addPoint(double,double,int)\0"
    "lat,lon\0selectObject(double,double)\0"
    "deselectObject()\0deleteCurrentObject()\0"
    "object\0setSelectedMapObject(QVariant)\0"
    "QVariant\0getSelectedMapObject()\0"
    "testButtonOperation()\0"
    "id,name,surname,jid,password\0"
    "createNewTerrainUser(QString,QString,QString,QString,QString)\0"
    "name\0createNewAcl(QString)\0prepareAclList()\0"
    "int\0getAclNum()\0QString\0i\0getAclNameAt(int)\0"
    "removeAcl(int)\0prepareTerrainUserList()\0"
    "getTerrainUserNum()\0getTerrainUserNameAt(int)\0"
    "getTerrainUserSurnameAt(int)\0"
    "removeTerrainUser(int)\0"
    "prepareTerrainUserFromAclList(int)\0"
    "getTerrainUserFromAclNum()\0"
    "getTerrainUserFromAclNameAt(int)\0"
    "getTerrainUserFromAclSurnameAt(int)\0"
    "i,j\0setTerrainUserAcl(int,int)\0"
    "unsetTerrainUserAcl(int)\0"
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
        case 0: sendObjects((*reinterpret_cast< QList<QLandmark>*(*)>(_a[1]))); break;
        case 1: sendMapObject((*reinterpret_cast< QLandmark(*)>(_a[1])),(*reinterpret_cast< QList<TerrainUser>(*)>(_a[2]))); break;
        case 2: aclListReady(); break;
        case 3: terrainUserListReady(); break;
        case 4: terrainUserFromAclListReady(); break;
        case 5: test(); break;
        case 6: getAllObjects((*reinterpret_cast< QList<QLandmark>*(*)>(_a[1]))); break;
        case 7: getConnectedUsers((*reinterpret_cast< QList<QLandmark>*(*)>(_a[1]))); break;
        case 8: updateUserPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 9: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: addPoint((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: selectObject((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 12: deselectObject(); break;
        case 13: deleteCurrentObject(); break;
        case 14: setSelectedMapObject((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 15: { QVariant _r = getSelectedMapObject();
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 16: testButtonOperation(); break;
        case 17: createNewTerrainUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 18: createNewAcl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: prepareAclList(); break;
        case 20: { int _r = getAclNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 21: { QString _r = getAclNameAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 22: removeAcl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: prepareTerrainUserList(); break;
        case 24: { int _r = getTerrainUserNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: { QString _r = getTerrainUserNameAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 26: { QString _r = getTerrainUserSurnameAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 27: removeTerrainUser((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: prepareTerrainUserFromAclList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: { int _r = getTerrainUserFromAclNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 30: { QString _r = getTerrainUserFromAclNameAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 31: { QString _r = getTerrainUserFromAclSurnameAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 32: setTerrainUserAcl((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 33: unsetTerrainUserAcl((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void Controller::sendObjects(QList<QLandmark> * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Controller::sendMapObject(QLandmark _t1, QList<TerrainUser> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Controller::aclListReady()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Controller::terrainUserListReady()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Controller::terrainUserFromAclListReady()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Controller::test()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
