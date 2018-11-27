/****************************************************************************
** Meta object code from reading C++ file 'DrawingArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../inc/GUI/DrawingArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DrawingArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DrawingArea_t {
    QByteArrayData data[6];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawingArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawingArea_t qt_meta_stringdata_DrawingArea = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DrawingArea"
QT_MOC_LITERAL(1, 12, 28), // "HorizontalScrollValueChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 5), // "value"
QT_MOC_LITERAL(4, 48, 26), // "VerticalScrollValueChanged"
QT_MOC_LITERAL(5, 75, 17) // "ScaleValueChanged"

    },
    "DrawingArea\0HorizontalScrollValueChanged\0"
    "\0value\0VerticalScrollValueChanged\0"
    "ScaleValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawingArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    1,   32,    2, 0x08 /* Private */,
       5,    1,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,

       0        // eod
};

void DrawingArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DrawingArea *_t = static_cast<DrawingArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->HorizontalScrollValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->VerticalScrollValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ScaleValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DrawingArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DrawingArea.data,
      qt_meta_data_DrawingArea,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DrawingArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawingArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DrawingArea.stringdata0))
        return static_cast<void*>(const_cast< DrawingArea*>(this));
    return QWidget::qt_metacast(_clname);
}

int DrawingArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
