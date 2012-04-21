/****************************************************************************
** Meta object code from reading C++ file 'xmppclient.h'
**
** Created: Sat 14. Apr 13:30:40 2012
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
static const uint qt_meta_data_XmppClient[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      49,   22,   11,   11, 0x05,
     104,   22,   11,   11, 0x05,
     158,   22,   11,   11, 0x05,
     220,  215,   11,   11, 0x05,
     250,  235,   11,   11, 0x05,
     293,  278,   11,   11, 0x05,
     332,  328,   11,   11, 0x05,
     364,  356,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     393,   11,   11,   11, 0x0a,
     411,  356,   11,   11, 0x0a,
     454,  437,   11,   11, 0x0a,
     496,  487,   11,   11, 0x0a,
     544,  528,   11,   11, 0x0a,
     590,  328,   11,   11, 0x0a,
     629,  617,   11,   11, 0x0a,
     681,  663,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XmppClient[] = {
    "XmppClient\0\0refresh()\0coordList,mapObjectId,data\0"
    "sendPointFromCentral(QVector<QPointF>,QString,QString)\0"
    "sendLineFromCentral(QVector<QPointF>,QString,QString)\0"
    "sendPolygonFromCentral(QVector<QPointF>,QString,QString)\0"
    "note\0sendNote(Note)\0negativeObject\0"
    "sendNegativeObject(QString)\0jid,coordinate\0"
    "updateUser(QString,QGeoCoordinate)\0"
    "jid\0setUserOffline(QString)\0message\0"
    "sendReceivedMessage(Message)\0"
    "clientConnected()\0messageRecv(QXmppMessage)\0"
    "bareJid,resource\0presenceChanged(QString,QString)\0"
    "presence\0presenceReceived(QXmppPresence)\0"
    "jid,lat,lon,acc\0"
    "getNewCoords(QString,QString,QString,QString)\0"
    "subscribeLocation(QString)\0jid,message\0"
    "getMessageToSend(QString,QString)\0"
    "username,password\0reconnectGet(QString,QString)\0"
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
        case 0: refresh(); break;
        case 1: sendPointFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: sendLineFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: sendPolygonFromCentral((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: sendNote((*reinterpret_cast< Note(*)>(_a[1]))); break;
        case 5: sendNegativeObject((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: updateUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2]))); break;
        case 7: setUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: sendReceivedMessage((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 9: clientConnected(); break;
        case 10: messageRecv((*reinterpret_cast< const QXmppMessage(*)>(_a[1]))); break;
        case 11: presenceChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: presenceReceived((*reinterpret_cast< const QXmppPresence(*)>(_a[1]))); break;
        case 13: getNewCoords((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 14: subscribeLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: getMessageToSend((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: reconnectGet((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void XmppClient::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void XmppClient::sendPointFromCentral(QVector<QPointF> _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XmppClient::sendLineFromCentral(QVector<QPointF> _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void XmppClient::sendPolygonFromCentral(QVector<QPointF> _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void XmppClient::sendNote(Note _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void XmppClient::sendNegativeObject(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void XmppClient::updateUser(QString _t1, QGeoCoordinate _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void XmppClient::setUserOffline(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void XmppClient::sendReceivedMessage(Message _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
