/****************************************************************************
** Meta object code from reading C++ file 'xmppclient.h'
**
** Created: Mon 27. Feb 21:13:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xmppclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xmppclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_xmppClient[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      28,   22,   11,   11, 0x05,
      73,   58,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     108,   11,   11,   11, 0x0a,
     134,  126,   11,   11, 0x0a,
     177,  160,   11,   11, 0x0a,
     219,  210,   11,   11, 0x0a,
     267,  251,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_xmppClient[] = {
    "xmppClient\0\0refresh()\0point\0"
    "sendPointFromCentral(QString)\0"
    "jid,coordinate\0updateUser(QString,QGeoCoordinate)\0"
    "clientConnected()\0message\0"
    "messageRecv(QXmppMessage)\0bareJid,resource\0"
    "presenceChanged(QString,QString)\0"
    "presence\0presenceReceived(QXmppPresence)\0"
    "jid,lat,lon,acc\0"
    "getNewCoords(QString,QString,QString,QString)\0"
};

const QMetaObject xmppClient::staticMetaObject = {
    { &QXmppClient::staticMetaObject, qt_meta_stringdata_xmppClient,
      qt_meta_data_xmppClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &xmppClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *xmppClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *xmppClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_xmppClient))
        return static_cast<void*>(const_cast< xmppClient*>(this));
    return QXmppClient::qt_metacast(_clname);
}

int xmppClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QXmppClient::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refresh(); break;
        case 1: sendPointFromCentral((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: updateUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 3: clientConnected(); break;
        case 4: messageRecv((*reinterpret_cast< const QXmppMessage(*)>(_a[1]))); break;
        case 5: presenceChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: presenceReceived((*reinterpret_cast< const QXmppPresence(*)>(_a[1]))); break;
        case 7: getNewCoords((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void xmppClient::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void xmppClient::sendPointFromCentral(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void xmppClient::updateUser(QString _t1, QGeoCoordinate _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
