/****************************************************************************
** Meta object code from reading C++ file 'xmppclient.h'
**
** Created: Sat 24. Mar 14:42:14 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Diplomka-Central/xmppclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xmppclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XmppClient[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   12,   11,   11, 0x05,
      67,   52,   11,   11, 0x05,
     106,  102,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     130,   11,   11,   11, 0x0a,
     156,  148,   11,   11, 0x0a,
     199,  182,   11,   11, 0x0a,
     241,  232,   11,   11, 0x0a,
     276,  273,   11,   11, 0x0a,
     306,  296,   11,   11, 0x0a,
     362,  344,   11,   11, 0x0a,
     426,  410,   11,   11, 0x0a,
     472,   11,   11,   11, 0x0a,
     492,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XmppClient[] = {
    "XmppClient\0\0landmarkList\0"
    "refresh(QList<QLandmark>*)\0jid,coordinate\0"
    "updateUser(QString,QGeoCoordinate)\0"
    "jid\0setUserOffline(QString)\0"
    "clientConnected()\0message\0"
    "messageRecv(QXmppMessage)\0bareJid,resource\0"
    "presenceChanged(QString,QString)\0"
    "presence\0presenceReceived(QXmppPresence)\0"
    "iq\0iqReceived(QXmppIq)\0landmarks\0"
    "sendObjectsToUsers(QList<QLandmark>*)\0"
    "landmark,userList\0"
    "sendObjectToUsers(QLandmark,QList<TerrainUser>)\0"
    "jid,lat,lon,acc\0"
    "getNewCoords(QString,QString,QString,QString)\0"
    "subscribeLocation()\0sendMess()\0"
};

const QMetaObject XmppClient::staticMetaObject = {
    { &QXmppClient::staticMetaObject, qt_meta_stringdata_XmppClient,
      qt_meta_data_XmppClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XmppClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XmppClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XmppClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XmppClient))
        return static_cast<void*>(const_cast< XmppClient*>(this));
    return QXmppClient::qt_metacast(_clname);
}

int XmppClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QXmppClient::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refresh((*reinterpret_cast< QList<QLandmark>*(*)>(_a[1]))); break;
        case 1: updateUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 2: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: clientConnected(); break;
        case 4: messageRecv((*reinterpret_cast< const QXmppMessage(*)>(_a[1]))); break;
        case 5: presenceChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: presenceReceived((*reinterpret_cast< const QXmppPresence(*)>(_a[1]))); break;
        case 7: iqReceived((*reinterpret_cast< const QXmppIq(*)>(_a[1]))); break;
        case 8: sendObjectsToUsers((*reinterpret_cast< QList<QLandmark>*(*)>(_a[1]))); break;
        case 9: sendObjectToUsers((*reinterpret_cast< QLandmark(*)>(_a[1])),(*reinterpret_cast< QList<TerrainUser>(*)>(_a[2]))); break;
        case 10: getNewCoords((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 11: subscribeLocation(); break;
        case 12: sendMess(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void XmppClient::refresh(QList<QLandmark> * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XmppClient::updateUser(QString _t1, QGeoCoordinate _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XmppClient::setUserOffline(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
