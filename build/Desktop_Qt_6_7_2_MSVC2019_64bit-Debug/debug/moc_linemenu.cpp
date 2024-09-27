/****************************************************************************
** Meta object code from reading C++ file 'linemenu.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../linemenu.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'linemenu.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSLineMenuENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSLineMenuENDCLASS = QtMocHelpers::stringData(
    "LineMenu",
    "on_pushButton_saveLines_clicked",
    "",
    "on_pushButton_removeLines_clicked",
    "on_pushButton_splitz_clicked",
    "selectedRows",
    "loadLineGisData",
    "on_pushButton_loadLines_clicked",
    "on_pushButton_unloadLines_clicked",
    "on_tableWidget_line_cellDoubleClicked",
    "row",
    "column",
    "allDisconnects",
    "updateLineGisData",
    "id",
    "newName",
    "on_pushButton_deleteLines_clicked",
    "on_comboBox_loadOrder_activated",
    "index",
    "updateLineTable",
    "lineList",
    "type",
    "setWidgetState",
    "loadlineTable",
    "loadList"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLineMenuENDCLASS[] = {

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
      16,    0,  122,    2, 0x08,   15 /* Private */,
      17,    1,  123,    2, 0x08,   16 /* Private */,
      19,    2,  126,    2, 0x0a,   18 /* Public */,
      22,    1,  131,    2, 0x0a,   21 /* Public */,
      23,    1,  134,    2, 0x0a,   23 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QStringList,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::QVariant, QMetaType::QVariant,   20,   21,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::QVariant,   24,

       0        // eod
};

Q_CONSTINIT const QMetaObject LineMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSLineMenuENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLineMenuENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLineMenuENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LineMenu, std::true_type>,
        // method 'on_pushButton_saveLines_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_removeLines_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_splitz_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectedRows'
        QtPrivate::TypeAndForceComplete<QStringList, std::false_type>,
        // method 'loadLineGisData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_loadLines_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_unloadLines_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableWidget_line_cellDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'allDisconnects'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateLineGisData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_pushButton_deleteLines_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_comboBox_loadOrder_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateLineTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>,
        // method 'setWidgetState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'loadlineTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>
    >,
    nullptr
} };

void LineMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LineMenu *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_saveLines_clicked(); break;
        case 1: _t->on_pushButton_removeLines_clicked(); break;
        case 2: _t->on_pushButton_splitz_clicked(); break;
        case 3: { QStringList _r = _t->selectedRows();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->loadLineGisData(); break;
        case 5: _t->on_pushButton_loadLines_clicked(); break;
        case 6: _t->on_pushButton_unloadLines_clicked(); break;
        case 7: _t->on_tableWidget_line_cellDoubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->allDisconnects(); break;
        case 9: _t->updateLineGisData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->on_pushButton_deleteLines_clicked(); break;
        case 11: _t->on_comboBox_loadOrder_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->updateLineTable((*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2]))); break;
        case 13: _t->setWidgetState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->loadlineTable((*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *LineMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LineMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLineMenuENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LineMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
