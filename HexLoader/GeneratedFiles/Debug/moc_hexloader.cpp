/****************************************************************************
** Meta object code from reading C++ file 'hexloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../hexloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hexloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HexLoader_t {
    QByteArrayData data[16];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HexLoader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HexLoader_t qt_meta_stringdata_HexLoader = {
    {
QT_MOC_LITERAL(0, 0, 9), // "HexLoader"
QT_MOC_LITERAL(1, 10, 14), // "slotOpenDialog"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "slotCloseProgram"
QT_MOC_LITERAL(4, 43, 12), // "slotSaveData"
QT_MOC_LITERAL(5, 56, 14), // "slotSaveAsData"
QT_MOC_LITERAL(6, 71, 8), // "slotUndo"
QT_MOC_LITERAL(7, 80, 8), // "slotRedo"
QT_MOC_LITERAL(8, 89, 8), // "slotFind"
QT_MOC_LITERAL(9, 98, 9), // "slotAbout"
QT_MOC_LITERAL(10, 108, 26), // "slotUpdationItemBackGround"
QT_MOC_LITERAL(11, 135, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(12, 153, 27), // "slotSelectionItemBackGround"
QT_MOC_LITERAL(13, 181, 10), // "slotScroll"
QT_MOC_LITERAL(14, 192, 23), // "slotFindAsciiPushButton"
QT_MOC_LITERAL(15, 216, 22) // "slotFindCharPushButton"

    },
    "HexLoader\0slotOpenDialog\0\0slotCloseProgram\0"
    "slotSaveData\0slotSaveAsData\0slotUndo\0"
    "slotRedo\0slotFind\0slotAbout\0"
    "slotUpdationItemBackGround\0QTableWidgetItem*\0"
    "slotSelectionItemBackGround\0slotScroll\0"
    "slotFindAsciiPushButton\0slotFindCharPushButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HexLoader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    1,   87,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    1,   91,    2, 0x08 /* Private */,
      14,    0,   94,    2, 0x08 /* Private */,
      15,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HexLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HexLoader *_t = static_cast<HexLoader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotOpenDialog(); break;
        case 1: _t->slotCloseProgram(); break;
        case 2: _t->slotSaveData(); break;
        case 3: _t->slotSaveAsData(); break;
        case 4: _t->slotUndo(); break;
        case 5: _t->slotRedo(); break;
        case 6: _t->slotFind(); break;
        case 7: _t->slotAbout(); break;
        case 8: _t->slotUpdationItemBackGround((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->slotSelectionItemBackGround(); break;
        case 10: _t->slotScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slotFindAsciiPushButton(); break;
        case 12: _t->slotFindCharPushButton(); break;
        default: ;
        }
    }
}

const QMetaObject HexLoader::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_HexLoader.data,
      qt_meta_data_HexLoader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HexLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HexLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HexLoader.stringdata0))
        return static_cast<void*>(const_cast< HexLoader*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int HexLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
