/****************************************************************************
** Meta object code from reading C++ file 'form_auto.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../projects/cnc/form_auto.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form_auto.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_form_auto_t {
    QByteArrayData data[15];
    char stringdata0[393];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_form_auto_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_form_auto_t qt_meta_stringdata_form_auto = {
    {
QT_MOC_LITERAL(0, 0, 9), // "form_auto"
QT_MOC_LITERAL(1, 10, 28), // "on_toolButton_reload_pressed"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 26), // "on_toolButton_open_pressed"
QT_MOC_LITERAL(4, 67, 54), // "on_horizontalSlider_auto_velo..."
QT_MOC_LITERAL(5, 122, 5), // "value"
QT_MOC_LITERAL(6, 128, 25), // "on_toolButton_run_pressed"
QT_MOC_LITERAL(7, 154, 27), // "on_toolButton_pause_pressed"
QT_MOC_LITERAL(8, 182, 26), // "on_toolButton_stop_pressed"
QT_MOC_LITERAL(9, 209, 44), // "on_doubleSpinBox_tooldir_fill..."
QT_MOC_LITERAL(10, 254, 4), // "arg1"
QT_MOC_LITERAL(11, 259, 39), // "on_checkBox_tangential_overri..."
QT_MOC_LITERAL(12, 299, 7), // "checked"
QT_MOC_LITERAL(13, 307, 42), // "on_doubleSpinBox_tool_angle_x..."
QT_MOC_LITERAL(14, 350, 42) // "on_doubleSpinBox_tool_angle_y..."

    },
    "form_auto\0on_toolButton_reload_pressed\0"
    "\0on_toolButton_open_pressed\0"
    "on_horizontalSlider_auto_velocity_procent_valueChanged\0"
    "value\0on_toolButton_run_pressed\0"
    "on_toolButton_pause_pressed\0"
    "on_toolButton_stop_pressed\0"
    "on_doubleSpinBox_tooldir_fillet_valueChanged\0"
    "arg1\0on_checkBox_tangential_override_toggled\0"
    "checked\0on_doubleSpinBox_tool_angle_x_valueChanged\0"
    "on_doubleSpinBox_tool_angle_y_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_form_auto[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    1,   66,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    1,   72,    2, 0x08 /* Private */,
      11,    1,   75,    2, 0x08 /* Private */,
      13,    1,   78,    2, 0x08 /* Private */,
      14,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::Double,   10,

       0        // eod
};

void form_auto::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<form_auto *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_toolButton_reload_pressed(); break;
        case 1: _t->on_toolButton_open_pressed(); break;
        case 2: _t->on_horizontalSlider_auto_velocity_procent_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_toolButton_run_pressed(); break;
        case 4: _t->on_toolButton_pause_pressed(); break;
        case 5: _t->on_toolButton_stop_pressed(); break;
        case 6: _t->on_doubleSpinBox_tooldir_fillet_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_checkBox_tangential_override_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_doubleSpinBox_tool_angle_x_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->on_doubleSpinBox_tool_angle_y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject form_auto::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_form_auto.data,
    qt_meta_data_form_auto,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *form_auto::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *form_auto::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_form_auto.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int form_auto::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
