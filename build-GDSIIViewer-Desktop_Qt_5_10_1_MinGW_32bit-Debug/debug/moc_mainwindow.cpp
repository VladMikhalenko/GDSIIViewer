/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[321];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "ZoomValueUpdated"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "CalculateScrolls"
QT_MOC_LITERAL(4, 46, 5), // "value"
QT_MOC_LITERAL(5, 52, 21), // "CalculateWindowPoints"
QT_MOC_LITERAL(6, 74, 16), // "ZoomValueChanged"
QT_MOC_LITERAL(7, 91, 17), // "LayerValueChanged"
QT_MOC_LITERAL(8, 109, 22), // "extractionLayerChanged"
QT_MOC_LITERAL(9, 132, 18), // "markerLayerChanged"
QT_MOC_LITERAL(10, 151, 10), // "BtnOkClick"
QT_MOC_LITERAL(11, 162, 13), // "BtnScannClick"
QT_MOC_LITERAL(12, 176, 14), // "btnEncodeClick"
QT_MOC_LITERAL(13, 191, 23), // "HorizontalScrollChanged"
QT_MOC_LITERAL(14, 215, 21), // "VerticalScrollChanged"
QT_MOC_LITERAL(15, 237, 15), // "RadioOneChanged"
QT_MOC_LITERAL(16, 253, 19), // "RadioSeveralChanged"
QT_MOC_LITERAL(17, 273, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(18, 297, 23) // "on_actionExit_triggered"

    },
    "MainWindow\0ZoomValueUpdated\0\0"
    "CalculateScrolls\0value\0CalculateWindowPoints\0"
    "ZoomValueChanged\0LayerValueChanged\0"
    "extractionLayerChanged\0markerLayerChanged\0"
    "BtnOkClick\0BtnScannClick\0btnEncodeClick\0"
    "HorizontalScrollChanged\0VerticalScrollChanged\0"
    "RadioOneChanged\0RadioSeveralChanged\0"
    "on_actionOpen_triggered\0on_actionExit_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   97,    2, 0x08 /* Private */,
       5,    1,  100,    2, 0x08 /* Private */,
       6,    1,  103,    2, 0x08 /* Private */,
       7,    1,  106,    2, 0x08 /* Private */,
       8,    1,  109,    2, 0x08 /* Private */,
       9,    1,  112,    2, 0x08 /* Private */,
      10,    0,  115,    2, 0x08 /* Private */,
      11,    0,  116,    2, 0x08 /* Private */,
      12,    0,  117,    2, 0x08 /* Private */,
      13,    1,  118,    2, 0x08 /* Private */,
      14,    1,  121,    2, 0x08 /* Private */,
      15,    0,  124,    2, 0x08 /* Private */,
      16,    0,  125,    2, 0x08 /* Private */,
      17,    0,  126,    2, 0x08 /* Private */,
      18,    0,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZoomValueUpdated((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->CalculateScrolls((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->CalculateWindowPoints((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->ZoomValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->LayerValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->extractionLayerChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->markerLayerChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->BtnOkClick(); break;
        case 8: _t->BtnScannClick(); break;
        case 9: _t->btnEncodeClick(); break;
        case 10: _t->HorizontalScrollChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->VerticalScrollChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->RadioOneChanged(); break;
        case 13: _t->RadioSeveralChanged(); break;
        case 14: _t->on_actionOpen_triggered(); break;
        case 15: _t->on_actionExit_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::ZoomValueUpdated)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::ZoomValueUpdated(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
