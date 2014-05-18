/****************************************************************************
** Meta object code from reading C++ file 'Toravist.hpp'
**
** Created: Sun May 18 01:13:17 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/Toravist.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Toravist.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Toravist[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      30,   21,    9,    9, 0x08,
      62,   21,    9,    9, 0x08,
      89,    9,    9,    9, 0x08,
     106,    9,    9,    9, 0x08,
     118,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Toravist[] = {
    "Toravist\0\0loadData()\0newValue\0"
    "taskGranularityChanged(QString)\0"
    "taskNatureChanged(QString)\0setTaskDefault()\0"
    "taskClear()\0about()\0"
};

void Toravist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Toravist *_t = static_cast<Toravist *>(_o);
        switch (_id) {
        case 0: _t->loadData(); break;
        case 1: _t->taskGranularityChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->taskNatureChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setTaskDefault(); break;
        case 4: _t->taskClear(); break;
        case 5: _t->about(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Toravist::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Toravist::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Toravist,
      qt_meta_data_Toravist, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Toravist::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Toravist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Toravist::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Toravist))
        return static_cast<void*>(const_cast< Toravist*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Toravist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
