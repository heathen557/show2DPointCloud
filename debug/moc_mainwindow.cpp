/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "createDirSignal"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "writeLogSignal"
QT_MOC_LITERAL(4, 43, 15), // "seriOpen_signal"
QT_MOC_LITERAL(5, 59, 16), // "sendSerialSignal"
QT_MOC_LITERAL(6, 76, 17), // "showSettingDialog"
QT_MOC_LITERAL(7, 94, 13), // "seriOpen_slot"
QT_MOC_LITERAL(8, 108, 12), // "closeConnect"
QT_MOC_LITERAL(9, 121, 14), // "transCheckSlot"
QT_MOC_LITERAL(10, 136, 18), // "showSaveFileDialog"
QT_MOC_LITERAL(11, 155, 14), // "saveSubmitSlot"
QT_MOC_LITERAL(12, 170, 6), // "isSave"
QT_MOC_LITERAL(13, 177, 9), // "circleNum"
QT_MOC_LITERAL(14, 187, 11), // "radiusMeter"
QT_MOC_LITERAL(15, 199, 20), // "sendRotateSpeed_slot"
QT_MOC_LITERAL(16, 220, 19), // "returnLinkInfo_slot"
QT_MOC_LITERAL(17, 240, 33) // "on_startRotate_pushButton_cli..."

    },
    "MainWindow\0createDirSignal\0\0writeLogSignal\0"
    "seriOpen_signal\0sendSerialSignal\0"
    "showSettingDialog\0seriOpen_slot\0"
    "closeConnect\0transCheckSlot\0"
    "showSaveFileDialog\0saveSubmitSlot\0"
    "isSave\0circleNum\0radiusMeter\0"
    "sendRotateSpeed_slot\0returnLinkInfo_slot\0"
    "on_startRotate_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       3,    2,   82,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       5,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   93,    2, 0x0a /* Public */,
       7,    1,   94,    2, 0x0a /* Public */,
       8,    0,   97,    2, 0x0a /* Public */,
       9,    0,   98,    2, 0x0a /* Public */,
      10,    0,   99,    2, 0x0a /* Public */,
      11,    3,  100,    2, 0x0a /* Public */,
      15,    2,  107,    2, 0x0a /* Public */,
      16,    2,  112,    2, 0x0a /* Public */,
      17,    0,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createDirSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->writeLogSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->seriOpen_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sendSerialSignal((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->showSettingDialog(); break;
        case 5: _t->seriOpen_slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->closeConnect(); break;
        case 7: _t->transCheckSlot(); break;
        case 8: _t->showSaveFileDialog(); break;
        case 9: _t->saveSubmitSlot((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->sendRotateSpeed_slot((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->returnLinkInfo_slot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->on_startRotate_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::createDirSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::writeLogSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::seriOpen_signal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendSerialSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
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

// SIGNAL 0
void MainWindow::createDirSignal(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::writeLogSignal(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::seriOpen_signal(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::sendSerialSignal(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
