/****************************************************************************
** Meta object code from reading C++ file 'dialogdata.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogdata.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogData[] = {

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
      12,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      85,   11,   11,   11, 0x08,
     112,   11,   11,   11, 0x08,
     140,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogData[] = {
    "DialogData\0\0on_buttonBox_accepted()\0"
    "on_buttonBox_rejected()\0"
    "on_toolBtn_DEM_clicked()\0"
    "on_toolBtn_slope_clicked()\0"
    "on_toolBtn_aspect_clicked()\0"
    "on_toolBtn_fuel_clicked()\0"
};

void DialogData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DialogData *_t = static_cast<DialogData *>(_o);
        switch (_id) {
        case 0: _t->on_buttonBox_accepted(); break;
        case 1: _t->on_buttonBox_rejected(); break;
        case 2: _t->on_toolBtn_DEM_clicked(); break;
        case 3: _t->on_toolBtn_slope_clicked(); break;
        case 4: _t->on_toolBtn_aspect_clicked(); break;
        case 5: _t->on_toolBtn_fuel_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DialogData::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DialogData::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogData,
      qt_meta_data_DialogData, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogData))
        return static_cast<void*>(const_cast< DialogData*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
