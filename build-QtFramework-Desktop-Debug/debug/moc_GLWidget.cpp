/****************************************************************************
** Meta object code from reading C++ file 'GLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QtFramework/GUI/GLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cagd__GLWidget_t {
    const uint offsetsAndSize[242];
    char stringdata0[2490];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_cagd__GLWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_cagd__GLWidget_t qt_meta_stringdata_cagd__GLWidget = {
    {
QT_MOC_LITERAL(0, 14), // "cagd::GLWidget"
QT_MOC_LITERAL(15, 12), // "setSelectedX"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 5), // "value"
QT_MOC_LITERAL(35, 12), // "setSelectedY"
QT_MOC_LITERAL(48, 12), // "setSelectedZ"
QT_MOC_LITERAL(61, 14), // "distanceSignal"
QT_MOC_LITERAL(76, 18), // "newHermiteArcAdded"
QT_MOC_LITERAL(95, 20), // "xHermitePointChanged"
QT_MOC_LITERAL(116, 20), // "yHermitePointChanged"
QT_MOC_LITERAL(137, 20), // "zHermitePointChanged"
QT_MOC_LITERAL(158, 21), // "dxHermitePointChanged"
QT_MOC_LITERAL(180, 21), // "dyHermitePointChanged"
QT_MOC_LITERAL(202, 21), // "dzHermitePointChanged"
QT_MOC_LITERAL(224, 24), // "HermitePatchPointChangeX"
QT_MOC_LITERAL(249, 24), // "HermitePatchPointChangeY"
QT_MOC_LITERAL(274, 24), // "HermitePatchPointChangeZ"
QT_MOC_LITERAL(299, 25), // "HermitePatchPointChangeUX"
QT_MOC_LITERAL(325, 25), // "HermitePatchPointChangeUY"
QT_MOC_LITERAL(351, 25), // "HermitePatchPointChangeUZ"
QT_MOC_LITERAL(377, 25), // "HermitePatchPointChangeVX"
QT_MOC_LITERAL(403, 25), // "HermitePatchPointChangeVY"
QT_MOC_LITERAL(429, 25), // "HermitePatchPointChangeVZ"
QT_MOC_LITERAL(455, 25), // "HermitePatchPointChangeTX"
QT_MOC_LITERAL(481, 25), // "HermitePatchPointChangeTY"
QT_MOC_LITERAL(507, 25), // "HermitePatchPointChangeTZ"
QT_MOC_LITERAL(533, 11), // "set_angle_x"
QT_MOC_LITERAL(545, 11), // "set_angle_y"
QT_MOC_LITERAL(557, 11), // "set_angle_z"
QT_MOC_LITERAL(569, 15), // "set_zoom_factor"
QT_MOC_LITERAL(585, 11), // "set_trans_x"
QT_MOC_LITERAL(597, 11), // "set_trans_y"
QT_MOC_LITERAL(609, 11), // "set_trans_z"
QT_MOC_LITERAL(621, 9), // "set_scale"
QT_MOC_LITERAL(631, 5), // "scale"
QT_MOC_LITERAL(637, 19), // "set_div_point_count"
QT_MOC_LITERAL(657, 15), // "div_point_count"
QT_MOC_LITERAL(673, 23), // "setParametricCurveIndex"
QT_MOC_LITERAL(697, 5), // "index"
QT_MOC_LITERAL(703, 23), // "setVisibilityOfTangents"
QT_MOC_LITERAL(727, 10), // "visibility"
QT_MOC_LITERAL(738, 34), // "setVisibilityOfAccelerationVe..."
QT_MOC_LITERAL(773, 7), // "animate"
QT_MOC_LITERAL(781, 22), // "setSelectedCyclicCurve"
QT_MOC_LITERAL(804, 16), // "setSelectedPoint"
QT_MOC_LITERAL(821, 26), // "setVisibilityOfCyclicCurve"
QT_MOC_LITERAL(848, 22), // "setVisibilityOfTangent"
QT_MOC_LITERAL(871, 32), // "setVisiblityOfAccelerationVector"
QT_MOC_LITERAL(904, 11), // "visiblility"
QT_MOC_LITERAL(916, 23), // "setSpeedOfSelectedCurve"
QT_MOC_LITERAL(940, 16), // "setSelectedXSlot"
QT_MOC_LITERAL(957, 16), // "setSelectedYSlot"
QT_MOC_LITERAL(974, 16), // "setSelectedZSlot"
QT_MOC_LITERAL(991, 12), // "distanceSlot"
QT_MOC_LITERAL(1004, 18), // "setSelectedSurface"
QT_MOC_LITERAL(1023, 19), // "setSelectedMaterial"
QT_MOC_LITERAL(1043, 18), // "setSelectedTexture"
QT_MOC_LITERAL(1062, 22), // "setVisibilityOfTexture"
QT_MOC_LITERAL(1085, 14), // "animateSurface"
QT_MOC_LITERAL(1100, 17), // "setSelectedShader"
QT_MOC_LITERAL(1118, 14), // "setShaderScale"
QT_MOC_LITERAL(1133, 12), // "setSmoothing"
QT_MOC_LITERAL(1146, 10), // "setShading"
QT_MOC_LITERAL(1157, 6), // "setRed"
QT_MOC_LITERAL(1164, 7), // "setBlue"
QT_MOC_LITERAL(1172, 8), // "setGreen"
QT_MOC_LITERAL(1181, 26), // "showHermitePatchFirstOrder"
QT_MOC_LITERAL(1208, 27), // "showHermitePatchSecondOrder"
QT_MOC_LITERAL(1236, 22), // "_createNewCompositeArc"
QT_MOC_LITERAL(1259, 29), // "_highlightHermiteCompositeArc"
QT_MOC_LITERAL(1289, 24), // "_setSelectedCompositeArc"
QT_MOC_LITERAL(1314, 37), // "_addSelectedArcToSelectedComp..."
QT_MOC_LITERAL(1352, 22), // "_setSelectedHermiteArc"
QT_MOC_LITERAL(1375, 20), // "setHermitePointIndex"
QT_MOC_LITERAL(1396, 31), // "_setSelectedSecondaryHermiteArc"
QT_MOC_LITERAL(1428, 12), // "_hermite_red"
QT_MOC_LITERAL(1441, 14), // "_hermite_green"
QT_MOC_LITERAL(1456, 13), // "_hermite_blue"
QT_MOC_LITERAL(1470, 20), // "_setPrimaryDirection"
QT_MOC_LITERAL(1491, 22), // "_setSecondaryDirection"
QT_MOC_LITERAL(1514, 24), // "_setSecondarySelectedArc"
QT_MOC_LITERAL(1539, 12), // "_continueArc"
QT_MOC_LITERAL(1552, 8), // "_joinArc"
QT_MOC_LITERAL(1561, 9), // "_mergeArc"
QT_MOC_LITERAL(1571, 16), // "setHermitePointx"
QT_MOC_LITERAL(1588, 16), // "setHermitePointy"
QT_MOC_LITERAL(1605, 16), // "setHermitePointz"
QT_MOC_LITERAL(1622, 17), // "setHermitePointdx"
QT_MOC_LITERAL(1640, 17), // "setHermitePointdy"
QT_MOC_LITERAL(1658, 17), // "setHermitePointdz"
QT_MOC_LITERAL(1676, 30), // "showHermiteFirstOrderDerivates"
QT_MOC_LITERAL(1707, 31), // "showHermiteSecondOrderDerivates"
QT_MOC_LITERAL(1739, 25), // "_showHermitePatchTextures"
QT_MOC_LITERAL(1765, 24), // "_showHermitePatchShaders"
QT_MOC_LITERAL(1790, 24), // "_setHermitePatchMaterial"
QT_MOC_LITERAL(1815, 23), // "_setHermitePatchTexture"
QT_MOC_LITERAL(1839, 22), // "_setHermitePatchShader"
QT_MOC_LITERAL(1862, 24), // "_setSelectedHermitePatch"
QT_MOC_LITERAL(1887, 29), // "_setSelectedHermitePatchPoint"
QT_MOC_LITERAL(1917, 33), // "_setSelectedSecondaryHermiteP..."
QT_MOC_LITERAL(1951, 22), // "_setVisibilityOfULines"
QT_MOC_LITERAL(1974, 22), // "_setVisibilityOfVLines"
QT_MOC_LITERAL(1997, 32), // "_highlightSelectedCompositePatch"
QT_MOC_LITERAL(2030, 37), // "_setVisibilityOfFirstOrderDer..."
QT_MOC_LITERAL(2068, 38), // "_setVisibilityOfSecondOrderDe..."
QT_MOC_LITERAL(2107, 21), // "_selectCompositePatch"
QT_MOC_LITERAL(2129, 24), // "_createNewCompositePatch"
QT_MOC_LITERAL(2154, 41), // "_addSelectedPatchToSelectedCo..."
QT_MOC_LITERAL(2196, 20), // "setHermitePatchIndex"
QT_MOC_LITERAL(2217, 21), // "setHermitePatchPointX"
QT_MOC_LITERAL(2239, 21), // "setHermitePatchPointY"
QT_MOC_LITERAL(2261, 21), // "setHermitePatchPointZ"
QT_MOC_LITERAL(2283, 22), // "setHermitePatchPointUX"
QT_MOC_LITERAL(2306, 22), // "setHermitePatchPointUY"
QT_MOC_LITERAL(2329, 22), // "setHermitePatchPointUZ"
QT_MOC_LITERAL(2352, 22), // "setHermitePatchPointVX"
QT_MOC_LITERAL(2375, 22), // "setHermitePatchPointVY"
QT_MOC_LITERAL(2398, 22), // "setHermitePatchPointVZ"
QT_MOC_LITERAL(2421, 22), // "setHermitePatchPointTX"
QT_MOC_LITERAL(2444, 22), // "setHermitePatchPointTY"
QT_MOC_LITERAL(2467, 22) // "setHermitePatchPointTZ"

    },
    "cagd::GLWidget\0setSelectedX\0\0value\0"
    "setSelectedY\0setSelectedZ\0distanceSignal\0"
    "newHermiteArcAdded\0xHermitePointChanged\0"
    "yHermitePointChanged\0zHermitePointChanged\0"
    "dxHermitePointChanged\0dyHermitePointChanged\0"
    "dzHermitePointChanged\0HermitePatchPointChangeX\0"
    "HermitePatchPointChangeY\0"
    "HermitePatchPointChangeZ\0"
    "HermitePatchPointChangeUX\0"
    "HermitePatchPointChangeUY\0"
    "HermitePatchPointChangeUZ\0"
    "HermitePatchPointChangeVX\0"
    "HermitePatchPointChangeVY\0"
    "HermitePatchPointChangeVZ\0"
    "HermitePatchPointChangeTX\0"
    "HermitePatchPointChangeTY\0"
    "HermitePatchPointChangeTZ\0set_angle_x\0"
    "set_angle_y\0set_angle_z\0set_zoom_factor\0"
    "set_trans_x\0set_trans_y\0set_trans_z\0"
    "set_scale\0scale\0set_div_point_count\0"
    "div_point_count\0setParametricCurveIndex\0"
    "index\0setVisibilityOfTangents\0visibility\0"
    "setVisibilityOfAccelerationVectors\0"
    "animate\0setSelectedCyclicCurve\0"
    "setSelectedPoint\0setVisibilityOfCyclicCurve\0"
    "setVisibilityOfTangent\0"
    "setVisiblityOfAccelerationVector\0"
    "visiblility\0setSpeedOfSelectedCurve\0"
    "setSelectedXSlot\0setSelectedYSlot\0"
    "setSelectedZSlot\0distanceSlot\0"
    "setSelectedSurface\0setSelectedMaterial\0"
    "setSelectedTexture\0setVisibilityOfTexture\0"
    "animateSurface\0setSelectedShader\0"
    "setShaderScale\0setSmoothing\0setShading\0"
    "setRed\0setBlue\0setGreen\0"
    "showHermitePatchFirstOrder\0"
    "showHermitePatchSecondOrder\0"
    "_createNewCompositeArc\0"
    "_highlightHermiteCompositeArc\0"
    "_setSelectedCompositeArc\0"
    "_addSelectedArcToSelectedCompositeArc\0"
    "_setSelectedHermiteArc\0setHermitePointIndex\0"
    "_setSelectedSecondaryHermiteArc\0"
    "_hermite_red\0_hermite_green\0_hermite_blue\0"
    "_setPrimaryDirection\0_setSecondaryDirection\0"
    "_setSecondarySelectedArc\0_continueArc\0"
    "_joinArc\0_mergeArc\0setHermitePointx\0"
    "setHermitePointy\0setHermitePointz\0"
    "setHermitePointdx\0setHermitePointdy\0"
    "setHermitePointdz\0showHermiteFirstOrderDerivates\0"
    "showHermiteSecondOrderDerivates\0"
    "_showHermitePatchTextures\0"
    "_showHermitePatchShaders\0"
    "_setHermitePatchMaterial\0"
    "_setHermitePatchTexture\0_setHermitePatchShader\0"
    "_setSelectedHermitePatch\0"
    "_setSelectedHermitePatchPoint\0"
    "_setSelectedSecondaryHermitePatch\0"
    "_setVisibilityOfULines\0_setVisibilityOfVLines\0"
    "_highlightSelectedCompositePatch\0"
    "_setVisibilityOfFirstOrderDerivatives\0"
    "_setVisibilityOfSecondOrderDerivatives\0"
    "_selectCompositePatch\0_createNewCompositePatch\0"
    "_addSelectedPatchToSelectedCompositePatch\0"
    "setHermitePatchIndex\0setHermitePatchPointX\0"
    "setHermitePatchPointY\0setHermitePatchPointZ\0"
    "setHermitePatchPointUX\0setHermitePatchPointUY\0"
    "setHermitePatchPointUZ\0setHermitePatchPointVX\0"
    "setHermitePatchPointVY\0setHermitePatchPointVZ\0"
    "setHermitePatchPointTX\0setHermitePatchPointTY\0"
    "setHermitePatchPointTZ"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cagd__GLWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
     113,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      23,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  692,    2, 0x06,    1 /* Public */,
       4,    1,  695,    2, 0x06,    3 /* Public */,
       5,    1,  698,    2, 0x06,    5 /* Public */,
       6,    1,  701,    2, 0x06,    7 /* Public */,
       7,    1,  704,    2, 0x06,    9 /* Public */,
       8,    1,  707,    2, 0x06,   11 /* Public */,
       9,    1,  710,    2, 0x06,   13 /* Public */,
      10,    1,  713,    2, 0x06,   15 /* Public */,
      11,    1,  716,    2, 0x06,   17 /* Public */,
      12,    1,  719,    2, 0x06,   19 /* Public */,
      13,    1,  722,    2, 0x06,   21 /* Public */,
      14,    1,  725,    2, 0x06,   23 /* Public */,
      15,    1,  728,    2, 0x06,   25 /* Public */,
      16,    1,  731,    2, 0x06,   27 /* Public */,
      17,    1,  734,    2, 0x06,   29 /* Public */,
      18,    1,  737,    2, 0x06,   31 /* Public */,
      19,    1,  740,    2, 0x06,   33 /* Public */,
      20,    1,  743,    2, 0x06,   35 /* Public */,
      21,    1,  746,    2, 0x06,   37 /* Public */,
      22,    1,  749,    2, 0x06,   39 /* Public */,
      23,    1,  752,    2, 0x06,   41 /* Public */,
      24,    1,  755,    2, 0x06,   43 /* Public */,
      25,    1,  758,    2, 0x06,   45 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      26,    1,  761,    2, 0x0a,   47 /* Public */,
      27,    1,  764,    2, 0x0a,   49 /* Public */,
      28,    1,  767,    2, 0x0a,   51 /* Public */,
      29,    1,  770,    2, 0x0a,   53 /* Public */,
      30,    1,  773,    2, 0x0a,   55 /* Public */,
      31,    1,  776,    2, 0x0a,   57 /* Public */,
      32,    1,  779,    2, 0x0a,   59 /* Public */,
      33,    1,  782,    2, 0x0a,   61 /* Public */,
      35,    1,  785,    2, 0x0a,   63 /* Public */,
      37,    1,  788,    2, 0x0a,   65 /* Public */,
      39,    1,  791,    2, 0x0a,   67 /* Public */,
      41,    1,  794,    2, 0x0a,   69 /* Public */,
      42,    0,  797,    2, 0x0a,   71 /* Public */,
      43,    1,  798,    2, 0x0a,   72 /* Public */,
      44,    1,  801,    2, 0x0a,   74 /* Public */,
      45,    1,  804,    2, 0x0a,   76 /* Public */,
      46,    1,  807,    2, 0x0a,   78 /* Public */,
      47,    1,  810,    2, 0x0a,   80 /* Public */,
      49,    1,  813,    2, 0x0a,   82 /* Public */,
      50,    1,  816,    2, 0x0a,   84 /* Public */,
      51,    1,  819,    2, 0x0a,   86 /* Public */,
      52,    1,  822,    2, 0x0a,   88 /* Public */,
      53,    1,  825,    2, 0x0a,   90 /* Public */,
      54,    1,  828,    2, 0x0a,   92 /* Public */,
      55,    1,  831,    2, 0x0a,   94 /* Public */,
      56,    1,  834,    2, 0x0a,   96 /* Public */,
      57,    1,  837,    2, 0x0a,   98 /* Public */,
      58,    0,  840,    2, 0x0a,  100 /* Public */,
      59,    1,  841,    2, 0x0a,  101 /* Public */,
      60,    1,  844,    2, 0x0a,  103 /* Public */,
      61,    1,  847,    2, 0x0a,  105 /* Public */,
      62,    1,  850,    2, 0x0a,  107 /* Public */,
      63,    1,  853,    2, 0x0a,  109 /* Public */,
      64,    1,  856,    2, 0x0a,  111 /* Public */,
      65,    1,  859,    2, 0x0a,  113 /* Public */,
      66,    1,  862,    2, 0x0a,  115 /* Public */,
      67,    1,  865,    2, 0x0a,  117 /* Public */,
      68,    0,  868,    2, 0x0a,  119 /* Public */,
      69,    1,  869,    2, 0x0a,  120 /* Public */,
      70,    1,  872,    2, 0x0a,  122 /* Public */,
      71,    0,  875,    2, 0x0a,  124 /* Public */,
      72,    1,  876,    2, 0x0a,  125 /* Public */,
      73,    1,  879,    2, 0x0a,  127 /* Public */,
      74,    1,  882,    2, 0x0a,  129 /* Public */,
      75,    1,  885,    2, 0x0a,  131 /* Public */,
      76,    1,  888,    2, 0x0a,  133 /* Public */,
      77,    1,  891,    2, 0x0a,  135 /* Public */,
      78,    1,  894,    2, 0x0a,  137 /* Public */,
      79,    1,  897,    2, 0x0a,  139 /* Public */,
      80,    1,  900,    2, 0x0a,  141 /* Public */,
      81,    0,  903,    2, 0x0a,  143 /* Public */,
      82,    0,  904,    2, 0x0a,  144 /* Public */,
      83,    0,  905,    2, 0x0a,  145 /* Public */,
      84,    1,  906,    2, 0x0a,  146 /* Public */,
      85,    1,  909,    2, 0x0a,  148 /* Public */,
      86,    1,  912,    2, 0x0a,  150 /* Public */,
      87,    1,  915,    2, 0x0a,  152 /* Public */,
      88,    1,  918,    2, 0x0a,  154 /* Public */,
      89,    1,  921,    2, 0x0a,  156 /* Public */,
      90,    1,  924,    2, 0x0a,  158 /* Public */,
      91,    1,  927,    2, 0x0a,  160 /* Public */,
      92,    1,  930,    2, 0x0a,  162 /* Public */,
      93,    1,  933,    2, 0x0a,  164 /* Public */,
      94,    1,  936,    2, 0x0a,  166 /* Public */,
      95,    1,  939,    2, 0x0a,  168 /* Public */,
      96,    1,  942,    2, 0x0a,  170 /* Public */,
      97,    1,  945,    2, 0x0a,  172 /* Public */,
      98,    1,  948,    2, 0x0a,  174 /* Public */,
      99,    1,  951,    2, 0x0a,  176 /* Public */,
     100,    1,  954,    2, 0x0a,  178 /* Public */,
     101,    1,  957,    2, 0x0a,  180 /* Public */,
     102,    1,  960,    2, 0x0a,  182 /* Public */,
     103,    1,  963,    2, 0x0a,  184 /* Public */,
     104,    1,  966,    2, 0x0a,  186 /* Public */,
     105,    1,  969,    2, 0x0a,  188 /* Public */,
     106,    0,  972,    2, 0x0a,  190 /* Public */,
     107,    0,  973,    2, 0x0a,  191 /* Public */,
     108,    1,  974,    2, 0x0a,  192 /* Public */,
     109,    1,  977,    2, 0x0a,  194 /* Public */,
     110,    1,  980,    2, 0x0a,  196 /* Public */,
     111,    1,  983,    2, 0x0a,  198 /* Public */,
     112,    1,  986,    2, 0x0a,  200 /* Public */,
     113,    1,  989,    2, 0x0a,  202 /* Public */,
     114,    1,  992,    2, 0x0a,  204 /* Public */,
     115,    1,  995,    2, 0x0a,  206 /* Public */,
     116,    1,  998,    2, 0x0a,  208 /* Public */,
     117,    1, 1001,    2, 0x0a,  210 /* Public */,
     118,    1, 1004,    2, 0x0a,  212 /* Public */,
     119,    1, 1007,    2, 0x0a,  214 /* Public */,
     120,    1, 1010,    2, 0x0a,  216 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,   34,
    QMetaType::Void, QMetaType::Int,   36,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

       0        // eod
};

void cagd::GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setSelectedX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setSelectedY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setSelectedZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->distanceSignal((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->newHermiteArcAdded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->xHermitePointChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->yHermitePointChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->zHermitePointChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->dxHermitePointChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->dyHermitePointChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->dzHermitePointChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->HermitePatchPointChangeX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->HermitePatchPointChangeY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->HermitePatchPointChangeZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->HermitePatchPointChangeUX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->HermitePatchPointChangeUY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->HermitePatchPointChangeUZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->HermitePatchPointChangeVX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->HermitePatchPointChangeVY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->HermitePatchPointChangeVZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->HermitePatchPointChangeTX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->HermitePatchPointChangeTY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: _t->HermitePatchPointChangeTZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->set_angle_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->set_angle_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->set_angle_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->set_zoom_factor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->set_trans_x((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 28: _t->set_trans_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->set_trans_z((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->set_scale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 31: _t->set_div_point_count((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->setParametricCurveIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->setVisibilityOfTangents((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->setVisibilityOfAccelerationVectors((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->animate(); break;
        case 36: _t->setSelectedCyclicCurve((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->setSelectedPoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->setVisibilityOfCyclicCurve((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->setVisibilityOfTangent((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->setVisiblityOfAccelerationVector((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: _t->setSpeedOfSelectedCurve((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->setSelectedXSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 43: _t->setSelectedYSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 44: _t->setSelectedZSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 45: _t->distanceSlot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 46: _t->setSelectedSurface((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 47: _t->setSelectedMaterial((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->setSelectedTexture((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->setVisibilityOfTexture((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: _t->animateSurface(); break;
        case 51: _t->setSelectedShader((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->setShaderScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 53: _t->setSmoothing((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 54: _t->setShading((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 55: _t->setRed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 56: _t->setBlue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 57: _t->setGreen((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 58: _t->showHermitePatchFirstOrder((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->showHermitePatchSecondOrder((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: _t->_createNewCompositeArc(); break;
        case 61: _t->_highlightHermiteCompositeArc((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 62: _t->_setSelectedCompositeArc((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->_addSelectedArcToSelectedCompositeArc(); break;
        case 64: _t->_setSelectedHermiteArc((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 65: _t->setHermitePointIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 66: _t->_setSelectedSecondaryHermiteArc((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: _t->_hermite_red((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 68: _t->_hermite_green((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 69: _t->_hermite_blue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 70: _t->_setPrimaryDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 71: _t->_setSecondaryDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 72: _t->_setSecondarySelectedArc((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 73: _t->_continueArc(); break;
        case 74: _t->_joinArc(); break;
        case 75: _t->_mergeArc(); break;
        case 76: _t->setHermitePointx((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 77: _t->setHermitePointy((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 78: _t->setHermitePointz((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 79: _t->setHermitePointdx((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 80: _t->setHermitePointdy((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 81: _t->setHermitePointdz((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 82: _t->showHermiteFirstOrderDerivates((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 83: _t->showHermiteSecondOrderDerivates((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 84: _t->_showHermitePatchTextures((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 85: _t->_showHermitePatchShaders((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 86: _t->_setHermitePatchMaterial((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 87: _t->_setHermitePatchTexture((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 88: _t->_setHermitePatchShader((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 89: _t->_setSelectedHermitePatch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 90: _t->_setSelectedHermitePatchPoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 91: _t->_setSelectedSecondaryHermitePatch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 92: _t->_setVisibilityOfULines((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 93: _t->_setVisibilityOfVLines((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 94: _t->_highlightSelectedCompositePatch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 95: _t->_setVisibilityOfFirstOrderDerivatives((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 96: _t->_setVisibilityOfSecondOrderDerivatives((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 97: _t->_selectCompositePatch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 98: _t->_createNewCompositePatch(); break;
        case 99: _t->_addSelectedPatchToSelectedCompositePatch(); break;
        case 100: _t->setHermitePatchIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 101: _t->setHermitePatchPointX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 102: _t->setHermitePatchPointY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 103: _t->setHermitePatchPointZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 104: _t->setHermitePatchPointUX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 105: _t->setHermitePatchPointUY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 106: _t->setHermitePatchPointUZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 107: _t->setHermitePatchPointVX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 108: _t->setHermitePatchPointVY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 109: _t->setHermitePatchPointVZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 110: _t->setHermitePatchPointTX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 111: _t->setHermitePatchPointTY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 112: _t->setHermitePatchPointTZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSelectedX)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSelectedY)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::setSelectedZ)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::distanceSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::newHermiteArcAdded)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::xHermitePointChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::yHermitePointChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::zHermitePointChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::dxHermitePointChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::dyHermitePointChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::dzHermitePointChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeX)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeY)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeZ)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeUX)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeUY)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeUZ)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeVX)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeVY)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeVZ)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeTX)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeTY)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeTZ)) {
                *result = 22;
                return;
            }
        }
    }
}

const QMetaObject cagd::GLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_cagd__GLWidget.offsetsAndSize,
    qt_meta_data_cagd__GLWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_cagd__GLWidget_t
, QtPrivate::TypeAndForceComplete<GLWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>


>,
    nullptr
} };


const QMetaObject *cagd::GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cagd::GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cagd__GLWidget.stringdata0))
        return static_cast<void*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int cagd::GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 113)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 113;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 113)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 113;
    }
    return _id;
}

// SIGNAL 0
void cagd::GLWidget::setSelectedX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cagd::GLWidget::setSelectedY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cagd::GLWidget::setSelectedZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void cagd::GLWidget::distanceSignal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void cagd::GLWidget::newHermiteArcAdded(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void cagd::GLWidget::xHermitePointChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void cagd::GLWidget::yHermitePointChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void cagd::GLWidget::zHermitePointChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void cagd::GLWidget::dxHermitePointChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void cagd::GLWidget::dyHermitePointChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void cagd::GLWidget::dzHermitePointChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void cagd::GLWidget::HermitePatchPointChangeX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void cagd::GLWidget::HermitePatchPointChangeY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void cagd::GLWidget::HermitePatchPointChangeZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void cagd::GLWidget::HermitePatchPointChangeUX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void cagd::GLWidget::HermitePatchPointChangeUY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void cagd::GLWidget::HermitePatchPointChangeUZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void cagd::GLWidget::HermitePatchPointChangeVX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void cagd::GLWidget::HermitePatchPointChangeVY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void cagd::GLWidget::HermitePatchPointChangeVZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void cagd::GLWidget::HermitePatchPointChangeTX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void cagd::GLWidget::HermitePatchPointChangeTY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void cagd::GLWidget::HermitePatchPointChangeTZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
