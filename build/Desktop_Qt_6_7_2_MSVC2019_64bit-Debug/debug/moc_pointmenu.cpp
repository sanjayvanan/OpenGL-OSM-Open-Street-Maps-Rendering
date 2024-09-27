/****************************************************************************
** Meta object code from reading C++ file 'pointmenu.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../pointmenu.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pointmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSPointMenuENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSPointMenuENDCLASS = QtMocHelpers::stringData(
    "PointMenu",
    "on_pushButton_remove_clicked",
    "",
    "on_pushButton_savePoint_clicked",
    "on_pushButton_load_clicked",
    "loadGisData",
    "on_pushButton_unload_clicked",
    "on_pushButton_delete_clicked",
    "selectedRows",
    "updateGisData",
    "id",
    "newName",
    "allDisconnects",
    "on_tableWidget_point_cellDoubleClicked",
    "row",
    "column",
    "on_comboBox_loadOrder_activated",
    "index",
    "on_pushButton_splitz_clicked",
    "updatePointMap",
    "pointList",
    "type",
    "loadPointTable",
    "loadList",
    "setWidgetState"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPointMenuENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    1 /* Private */,
       3,    0,  105,    2, 0x08,    2 /* Private */,
       4,    0,  106,    2, 0x08,    3 /* Private */,
       5,    0,  107,    2, 0x08,    4 /* Private */,
       6,    0,  108,    2, 0x08,    5 /* Private */,
       7,    0,  109,    2, 0x08,    6 /* Private */,
       8,    0,  110,    2, 0x08,    7 /* Private */,
       9,    2,  111,    2, 0x08,    8 /* Private */,
      12,    0,  116,    2, 0x08,   11 /* Private */,
      13,    2,  117,    2, 0x08,   12 /* Private */,
      16,    1,  122,    2, 0x08,   15 /* Private */,
      18,    0,  125,    2, 0x08,   17 /* Private */,
      19,    2,  126,    2, 0x0a,   18 /* Public */,
      22,    1,  131,    2, 0x0a,   21 /* Public */,
      24,    1,  134,    2, 0x0a,   23 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QStringList,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant, QMetaType::QVariant,   20,   21,
    QMetaType::Void, QMetaType::QVariant,   23,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

Q_CONSTINIT const QMetaObject PointMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSPointMenuENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPointMenuENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPointMenuENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PointMenu, std::true_type>,
        // method 'on_pushButton_remove_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_savePoint_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_load_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadGisData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_unload_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_delete_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectedRows'
        QtPrivate::TypeAndForceComplete<QStringList, std::false_type>,
        // method 'updateGisData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'allDisconnects'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableWidget_point_cellDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_comboBox_loadOrder_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_pushButton_splitz_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updatePointMap'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>,
        // method 'loadPointTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>,
        // method 'setWidgetState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void PointMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PointMenu *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_remove_clicked(); break;
        case 1: _t->on_pushButton_savePoint_clicked(); break;
        case 2: _t->on_pushButton_load_clicked(); break;
        case 3: _t->loadGisData(); break;
        case 4: _t->on_pushButton_unload_clicked(); break;
        case 5: _t->on_pushButton_delete_clicked(); break;
        case 6: { QStringList _r = _t->selectedRows();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->updateGisData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->allDisconnects(); break;
        case 9: _t->on_tableWidget_point_cellDoubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->on_comboBox_loadOrder_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_pushButton_splitz_clicked(); break;
        case 12: _t->updatePointMap((*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2]))); break;
        case 13: _t->loadPointTable((*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[1]))); break;
        case 14: _t->setWidgetState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PointMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PointMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPointMenuENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PointMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
