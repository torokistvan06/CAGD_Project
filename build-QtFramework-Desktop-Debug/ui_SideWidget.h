/********************************************************************************
** Form generated from reading UI file 'SideWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEWIDGET_H
#define UI_SIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *rotate_x_slider;
    QLabel *label_2;
    QSlider *rotate_y_slider;
    QLabel *label_3;
    QSlider *rotate_z_slider;
    QLabel *label_4;
    QDoubleSpinBox *zoom_factor_spin_box;
    QLabel *label_5;
    QDoubleSpinBox *trans_x_spin_box;
    QLabel *label_6;
    QDoubleSpinBox *trans_y_spin_box;
    QLabel *label_7;
    QDoubleSpinBox *trans_z_spin_box;
    QLabel *label_10;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QLabel *label_8;
    QComboBox *Pc;
    QCheckBox *ShowTangent;
    QCheckBox *ShowAcceleration;
    QLabel *label_9;
    QDoubleSpinBox *scale_spin_box;
    QLabel *label_11;
    QSlider *_div_point_count_widget;
    QWidget *tab_4;
    QLabel *label_12;
    QComboBox *selectedCyclicCurve;
    QCheckBox *showCyclicCurves;
    QCheckBox *showTangents;
    QCheckBox *showAccelerations;
    QLabel *label_13;
    QSlider *speedOfSelectedCurve;
    QLabel *label_14;
    QComboBox *selectedPoint;
    QDoubleSpinBox *selectedX;
    QDoubleSpinBox *selectedY;
    QDoubleSpinBox *selectedZ;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QDoubleSpinBox *distance;
    QWidget *tab;
    QComboBox *selectedSurface;
    QLabel *label_19;
    QComboBox *selectedTexture;
    QComboBox *selectedMaterial;
    QLabel *label_20;
    QLabel *label_21;
    QCheckBox *showTexture;
    QWidget *Lab5;
    QLabel *label_22;
    QComboBox *selecteShader;
    QDoubleSpinBox *scale;
    QDoubleSpinBox *smoothing;
    QDoubleSpinBox *shading;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QDoubleSpinBox *red;
    QDoubleSpinBox *blue;
    QDoubleSpinBox *green;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QWidget *tab_2;
    QDoubleSpinBox *hermite_x;
    QDoubleSpinBox *hermite_y;
    QDoubleSpinBox *hermite_z;
    QSpinBox *hermite_index;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QCheckBox *show_hermite_first_order_derivates;
    QCheckBox *show_hermite_second_order_derivates;
    QLabel *label_74;
    QLabel *label_75;
    QLabel *label_76;
    QLabel *label_77;
    QDoubleSpinBox *hermite_dx;
    QDoubleSpinBox *hermite_dy;
    QDoubleSpinBox *hermite_dz;
    QPushButton *createNewCompositeCurve;
    QLabel *label_78;
    QCheckBox *highlightSelectedCompositeArc;
    QSpinBox *selectedCompositeArc;
    QPushButton *addArcToCompositeCurve;
    QDoubleSpinBox *hermite_red;
    QDoubleSpinBox *hermite_green;
    QDoubleSpinBox *hermite_blue;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_79;
    QComboBox *selectedPrimaryDirection;
    QPushButton *continueSelectedArc;
    QComboBox *selectedSecondaryDirection;
    QLabel *label_80;
    QPushButton *joinSelectedArcs;
    QPushButton *mergeSelectedArcs;
    QLabel *label_81;
    QSpinBox *selectedHermiteArc;
    QSpinBox *selectedSecondaryHermiteArc;
    QWidget *tab_6;
    QComboBox *selectedHermitePatch;
    QLabel *label_46;
    QSpinBox *hermite_patch_index;
    QLabel *label_47;
    QLabel *label_48;
    QLabel *label_63;
    QLabel *label_64;
    QDoubleSpinBox *hermite_patch_x;
    QDoubleSpinBox *hermite_patch_y;
    QDoubleSpinBox *hermite_patch_z;
    QLabel *label_65;
    QLabel *label_66;
    QLabel *label_67;
    QDoubleSpinBox *hermite_patch_ux;
    QDoubleSpinBox *hermite_patch_uy;
    QDoubleSpinBox *hermite_patch_uz;
    QLabel *label_68;
    QLabel *label_69;
    QLabel *label_70;
    QDoubleSpinBox *hermite_patch_vx;
    QDoubleSpinBox *hermite_patch_vy;
    QDoubleSpinBox *hermite_patch_vz;
    QLabel *label_71;
    QLabel *label_72;
    QLabel *label_73;
    QDoubleSpinBox *hermite_patch_tx;
    QDoubleSpinBox *hermite_patch_ty;
    QDoubleSpinBox *hermite_patch_tz;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QString::fromUtf8("SideWidget"));
        SideWidget->resize(659, 635);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 271, 231));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 21, 261, 220));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rotate_x_slider = new QSlider(layoutWidget);
        rotate_x_slider->setObjectName(QString::fromUtf8("rotate_x_slider"));
        rotate_x_slider->setMinimum(-180);
        rotate_x_slider->setMaximum(180);
        rotate_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, rotate_x_slider);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rotate_y_slider = new QSlider(layoutWidget);
        rotate_y_slider->setObjectName(QString::fromUtf8("rotate_y_slider"));
        rotate_y_slider->setMinimum(-180);
        rotate_y_slider->setMaximum(180);
        rotate_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, rotate_y_slider);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rotate_z_slider = new QSlider(layoutWidget);
        rotate_z_slider->setObjectName(QString::fromUtf8("rotate_z_slider"));
        rotate_z_slider->setMinimum(-180);
        rotate_z_slider->setMaximum(180);
        rotate_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotate_z_slider);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        zoom_factor_spin_box = new QDoubleSpinBox(layoutWidget);
        zoom_factor_spin_box->setObjectName(QString::fromUtf8("zoom_factor_spin_box"));
        zoom_factor_spin_box->setDecimals(5);
        zoom_factor_spin_box->setMinimum(0.000100000000000);
        zoom_factor_spin_box->setMaximum(10000.000000000000000);
        zoom_factor_spin_box->setSingleStep(0.100000000000000);
        zoom_factor_spin_box->setValue(1.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, zoom_factor_spin_box);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        trans_x_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_x_spin_box->setObjectName(QString::fromUtf8("trans_x_spin_box"));
        trans_x_spin_box->setMinimum(-100.000000000000000);
        trans_x_spin_box->setMaximum(100.000000000000000);
        trans_x_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(4, QFormLayout::FieldRole, trans_x_spin_box);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        trans_y_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_y_spin_box->setObjectName(QString::fromUtf8("trans_y_spin_box"));
        trans_y_spin_box->setMinimum(-100.000000000000000);
        trans_y_spin_box->setMaximum(100.000000000000000);
        trans_y_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, trans_y_spin_box);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        trans_z_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_z_spin_box->setObjectName(QString::fromUtf8("trans_z_spin_box"));
        trans_z_spin_box->setMinimum(-100.000000000000000);
        trans_z_spin_box->setMaximum(100.000000000000000);
        trans_z_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(6, QFormLayout::FieldRole, trans_z_spin_box);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(40, 390, 73, 26));
        tabWidget = new QTabWidget(SideWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 230, 631, 381));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 10, 103, 24));
        Pc = new QComboBox(tab_3);
        Pc->setObjectName(QString::fromUtf8("Pc"));
        Pc->setGeometry(QRect(120, 10, 152, 24));
        ShowTangent = new QCheckBox(tab_3);
        ShowTangent->setObjectName(QString::fromUtf8("ShowTangent"));
        ShowTangent->setGeometry(QRect(10, 40, 251, 21));
        ShowTangent->setChecked(true);
        ShowAcceleration = new QCheckBox(tab_3);
        ShowAcceleration->setObjectName(QString::fromUtf8("ShowAcceleration"));
        ShowAcceleration->setGeometry(QRect(10, 70, 231, 21));
        ShowAcceleration->setChecked(true);
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 100, 73, 26));
        scale_spin_box = new QDoubleSpinBox(tab_3);
        scale_spin_box->setObjectName(QString::fromUtf8("scale_spin_box"));
        scale_spin_box->setGeometry(QRect(120, 100, 150, 26));
        scale_spin_box->setDecimals(5);
        scale_spin_box->setMinimum(0.000100000000000);
        scale_spin_box->setMaximum(10000.000000000000000);
        scale_spin_box->setSingleStep(0.100000000000000);
        scale_spin_box->setValue(1.000000000000000);
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 130, 101, 26));
        _div_point_count_widget = new QSlider(tab_3);
        _div_point_count_widget->setObjectName(QString::fromUtf8("_div_point_count_widget"));
        _div_point_count_widget->setGeometry(QRect(120, 140, 160, 17));
        _div_point_count_widget->setMinimum(1);
        _div_point_count_widget->setMaximum(500);
        _div_point_count_widget->setValue(200);
        _div_point_count_widget->setOrientation(Qt::Horizontal);
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        label_12 = new QLabel(tab_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 10, 181, 21));
        selectedCyclicCurve = new QComboBox(tab_4);
        selectedCyclicCurve->setObjectName(QString::fromUtf8("selectedCyclicCurve"));
        selectedCyclicCurve->setGeometry(QRect(210, 10, 76, 24));
        showCyclicCurves = new QCheckBox(tab_4);
        showCyclicCurves->setObjectName(QString::fromUtf8("showCyclicCurves"));
        showCyclicCurves->setGeometry(QRect(330, 10, 191, 21));
        showTangents = new QCheckBox(tab_4);
        showTangents->setObjectName(QString::fromUtf8("showTangents"));
        showTangents->setGeometry(QRect(10, 50, 181, 21));
        showAccelerations = new QCheckBox(tab_4);
        showAccelerations->setObjectName(QString::fromUtf8("showAccelerations"));
        showAccelerations->setGeometry(QRect(200, 50, 181, 21));
        label_13 = new QLabel(tab_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 90, 221, 21));
        speedOfSelectedCurve = new QSlider(tab_4);
        speedOfSelectedCurve->setObjectName(QString::fromUtf8("speedOfSelectedCurve"));
        speedOfSelectedCurve->setGeometry(QRect(230, 90, 160, 17));
        speedOfSelectedCurve->setMaximum(5);
        speedOfSelectedCurve->setOrientation(Qt::Horizontal);
        label_14 = new QLabel(tab_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 120, 241, 21));
        selectedPoint = new QComboBox(tab_4);
        selectedPoint->setObjectName(QString::fromUtf8("selectedPoint"));
        selectedPoint->setGeometry(QRect(260, 120, 76, 24));
        selectedX = new QDoubleSpinBox(tab_4);
        selectedX->setObjectName(QString::fromUtf8("selectedX"));
        selectedX->setGeometry(QRect(40, 150, 64, 26));
        selectedX->setMinimum(-99.000000000000000);
        selectedY = new QDoubleSpinBox(tab_4);
        selectedY->setObjectName(QString::fromUtf8("selectedY"));
        selectedY->setGeometry(QRect(130, 150, 64, 26));
        selectedY->setMinimum(-99.000000000000000);
        selectedZ = new QDoubleSpinBox(tab_4);
        selectedZ->setObjectName(QString::fromUtf8("selectedZ"));
        selectedZ->setGeometry(QRect(230, 150, 64, 26));
        selectedZ->setMinimum(-99.000000000000000);
        label_15 = new QLabel(tab_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 150, 21, 21));
        label_16 = new QLabel(tab_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(110, 150, 21, 21));
        label_17 = new QLabel(tab_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(210, 150, 21, 21));
        label_18 = new QLabel(tab_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(310, 150, 81, 21));
        distance = new QDoubleSpinBox(tab_4);
        distance->setObjectName(QString::fromUtf8("distance"));
        distance->setGeometry(QRect(370, 150, 64, 26));
        distance->setMinimum(0.000000000000000);
        distance->setMaximum(1.000000000000000);
        distance->setSingleStep(0.010000000000000);
        distance->setValue(0.500000000000000);
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setFocusPolicy(Qt::WheelFocus);
        selectedSurface = new QComboBox(tab);
        selectedSurface->setObjectName(QString::fromUtf8("selectedSurface"));
        selectedSurface->setGeometry(QRect(130, 30, 141, 24));
        label_19 = new QLabel(tab);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(20, 30, 101, 21));
        selectedTexture = new QComboBox(tab);
        selectedTexture->setObjectName(QString::fromUtf8("selectedTexture"));
        selectedTexture->setGeometry(QRect(130, 70, 141, 24));
        selectedMaterial = new QComboBox(tab);
        selectedMaterial->setObjectName(QString::fromUtf8("selectedMaterial"));
        selectedMaterial->setGeometry(QRect(130, 110, 141, 24));
        label_20 = new QLabel(tab);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(20, 70, 101, 21));
        label_21 = new QLabel(tab);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(20, 110, 111, 21));
        showTexture = new QCheckBox(tab);
        showTexture->setObjectName(QString::fromUtf8("showTexture"));
        showTexture->setGeometry(QRect(20, 150, 161, 21));
        tabWidget->addTab(tab, QString());
        Lab5 = new QWidget();
        Lab5->setObjectName(QString::fromUtf8("Lab5"));
        label_22 = new QLabel(Lab5);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(20, 20, 111, 16));
        selecteShader = new QComboBox(Lab5);
        selecteShader->setObjectName(QString::fromUtf8("selecteShader"));
        selecteShader->setGeometry(QRect(130, 20, 191, 24));
        scale = new QDoubleSpinBox(Lab5);
        scale->setObjectName(QString::fromUtf8("scale"));
        scale->setGeometry(QRect(130, 50, 64, 26));
        scale->setMaximum(1.000000000000000);
        scale->setSingleStep(0.050000000000000);
        smoothing = new QDoubleSpinBox(Lab5);
        smoothing->setObjectName(QString::fromUtf8("smoothing"));
        smoothing->setGeometry(QRect(130, 90, 64, 26));
        smoothing->setMaximum(1.000000000000000);
        smoothing->setSingleStep(0.050000000000000);
        shading = new QDoubleSpinBox(Lab5);
        shading->setObjectName(QString::fromUtf8("shading"));
        shading->setGeometry(QRect(130, 130, 64, 26));
        shading->setMaximum(1.000000000000000);
        shading->setSingleStep(0.050000000000000);
        label_23 = new QLabel(Lab5);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(50, 60, 71, 16));
        label_24 = new QLabel(Lab5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(50, 100, 71, 16));
        label_25 = new QLabel(Lab5);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(70, 140, 61, 16));
        red = new QDoubleSpinBox(Lab5);
        red->setObjectName(QString::fromUtf8("red"));
        red->setGeometry(QRect(270, 50, 64, 26));
        red->setMaximum(1.000000000000000);
        red->setSingleStep(0.050000000000000);
        blue = new QDoubleSpinBox(Lab5);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setGeometry(QRect(270, 90, 64, 26));
        blue->setMaximum(1.000000000000000);
        blue->setSingleStep(0.050000000000000);
        green = new QDoubleSpinBox(Lab5);
        green->setObjectName(QString::fromUtf8("green"));
        green->setGeometry(QRect(270, 130, 64, 26));
        green->setMaximum(1.000000000000000);
        green->setSingleStep(0.050000000000000);
        label_26 = new QLabel(Lab5);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(210, 50, 71, 16));
        label_27 = new QLabel(Lab5);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(210, 100, 71, 16));
        label_28 = new QLabel(Lab5);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(200, 140, 61, 16));
        tabWidget->addTab(Lab5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        hermite_x = new QDoubleSpinBox(tab_2);
        hermite_x->setObjectName(QString::fromUtf8("hermite_x"));
        hermite_x->setGeometry(QRect(40, 90, 64, 26));
        hermite_x->setMinimum(-99.000000000000000);
        hermite_y = new QDoubleSpinBox(tab_2);
        hermite_y->setObjectName(QString::fromUtf8("hermite_y"));
        hermite_y->setGeometry(QRect(40, 120, 64, 26));
        hermite_y->setMinimum(-99.000000000000000);
        hermite_z = new QDoubleSpinBox(tab_2);
        hermite_z->setObjectName(QString::fromUtf8("hermite_z"));
        hermite_z->setGeometry(QRect(40, 150, 64, 26));
        hermite_z->setMinimum(-99.000000000000000);
        hermite_index = new QSpinBox(tab_2);
        hermite_index->setObjectName(QString::fromUtf8("hermite_index"));
        hermite_index->setGeometry(QRect(120, 50, 46, 26));
        hermite_index->setMaximum(1);
        label_29 = new QLabel(tab_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(10, 50, 91, 21));
        label_30 = new QLabel(tab_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(20, 90, 16, 21));
        label_31 = new QLabel(tab_2);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(20, 120, 16, 21));
        label_32 = new QLabel(tab_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(20, 150, 16, 21));
        show_hermite_first_order_derivates = new QCheckBox(tab_2);
        show_hermite_first_order_derivates->setObjectName(QString::fromUtf8("show_hermite_first_order_derivates"));
        show_hermite_first_order_derivates->setGeometry(QRect(10, 190, 201, 21));
        show_hermite_second_order_derivates = new QCheckBox(tab_2);
        show_hermite_second_order_derivates->setObjectName(QString::fromUtf8("show_hermite_second_order_derivates"));
        show_hermite_second_order_derivates->setGeometry(QRect(10, 220, 221, 21));
        label_74 = new QLabel(tab_2);
        label_74->setObjectName(QString::fromUtf8("label_74"));
        label_74->setGeometry(QRect(10, 20, 81, 21));
        label_75 = new QLabel(tab_2);
        label_75->setObjectName(QString::fromUtf8("label_75"));
        label_75->setGeometry(QRect(120, 90, 16, 21));
        label_76 = new QLabel(tab_2);
        label_76->setObjectName(QString::fromUtf8("label_76"));
        label_76->setGeometry(QRect(120, 120, 16, 21));
        label_77 = new QLabel(tab_2);
        label_77->setObjectName(QString::fromUtf8("label_77"));
        label_77->setGeometry(QRect(120, 150, 16, 21));
        hermite_dx = new QDoubleSpinBox(tab_2);
        hermite_dx->setObjectName(QString::fromUtf8("hermite_dx"));
        hermite_dx->setGeometry(QRect(150, 90, 64, 26));
        hermite_dx->setMinimum(-99.000000000000000);
        hermite_dy = new QDoubleSpinBox(tab_2);
        hermite_dy->setObjectName(QString::fromUtf8("hermite_dy"));
        hermite_dy->setGeometry(QRect(150, 120, 64, 26));
        hermite_dy->setMinimum(-99.000000000000000);
        hermite_dz = new QDoubleSpinBox(tab_2);
        hermite_dz->setObjectName(QString::fromUtf8("hermite_dz"));
        hermite_dz->setGeometry(QRect(150, 150, 64, 26));
        hermite_dz->setMinimum(-99.000000000000000);
        createNewCompositeCurve = new QPushButton(tab_2);
        createNewCompositeCurve->setObjectName(QString::fromUtf8("createNewCompositeCurve"));
        createNewCompositeCurve->setGeometry(QRect(230, 20, 291, 28));
        label_78 = new QLabel(tab_2);
        label_78->setObjectName(QString::fromUtf8("label_78"));
        label_78->setGeometry(QRect(250, 70, 161, 21));
        highlightSelectedCompositeArc = new QCheckBox(tab_2);
        highlightSelectedCompositeArc->setObjectName(QString::fromUtf8("highlightSelectedCompositeArc"));
        highlightSelectedCompositeArc->setGeometry(QRect(270, 110, 231, 21));
        selectedCompositeArc = new QSpinBox(tab_2);
        selectedCompositeArc->setObjectName(QString::fromUtf8("selectedCompositeArc"));
        selectedCompositeArc->setGeometry(QRect(420, 70, 81, 26));
        selectedCompositeArc->setMaximum(10);
        addArcToCompositeCurve = new QPushButton(tab_2);
        addArcToCompositeCurve->setObjectName(QString::fromUtf8("addArcToCompositeCurve"));
        addArcToCompositeCurve->setGeometry(QRect(240, 150, 291, 28));
        hermite_red = new QDoubleSpinBox(tab_2);
        hermite_red->setObjectName(QString::fromUtf8("hermite_red"));
        hermite_red->setGeometry(QRect(260, 190, 64, 26));
        hermite_red->setMinimum(0.000000000000000);
        hermite_red->setMaximum(1.000000000000000);
        hermite_red->setSingleStep(0.010000000000000);
        hermite_red->setValue(0.500000000000000);
        hermite_green = new QDoubleSpinBox(tab_2);
        hermite_green->setObjectName(QString::fromUtf8("hermite_green"));
        hermite_green->setGeometry(QRect(360, 190, 64, 26));
        hermite_green->setMinimum(0.000000000000000);
        hermite_green->setMaximum(1.000000000000000);
        hermite_green->setSingleStep(0.010000000000000);
        hermite_green->setValue(0.500000000000000);
        hermite_blue = new QDoubleSpinBox(tab_2);
        hermite_blue->setObjectName(QString::fromUtf8("hermite_blue"));
        hermite_blue->setGeometry(QRect(450, 190, 64, 26));
        hermite_blue->setMinimum(0.000000000000000);
        hermite_blue->setMaximum(1.000000000000000);
        hermite_blue->setSingleStep(0.010000000000000);
        hermite_blue->setValue(0.500000000000000);
        label_33 = new QLabel(tab_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(250, 190, 21, 21));
        label_34 = new QLabel(tab_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(340, 190, 16, 21));
        label_35 = new QLabel(tab_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(440, 190, 16, 21));
        label_79 = new QLabel(tab_2);
        label_79->setObjectName(QString::fromUtf8("label_79"));
        label_79->setGeometry(QRect(260, 230, 161, 21));
        selectedPrimaryDirection = new QComboBox(tab_2);
        selectedPrimaryDirection->setObjectName(QString::fromUtf8("selectedPrimaryDirection"));
        selectedPrimaryDirection->setGeometry(QRect(440, 230, 76, 24));
        continueSelectedArc = new QPushButton(tab_2);
        continueSelectedArc->setObjectName(QString::fromUtf8("continueSelectedArc"));
        continueSelectedArc->setGeometry(QRect(10, 250, 241, 28));
        selectedSecondaryDirection = new QComboBox(tab_2);
        selectedSecondaryDirection->setObjectName(QString::fromUtf8("selectedSecondaryDirection"));
        selectedSecondaryDirection->setGeometry(QRect(440, 260, 76, 24));
        label_80 = new QLabel(tab_2);
        label_80->setObjectName(QString::fromUtf8("label_80"));
        label_80->setGeometry(QRect(260, 260, 171, 21));
        joinSelectedArcs = new QPushButton(tab_2);
        joinSelectedArcs->setObjectName(QString::fromUtf8("joinSelectedArcs"));
        joinSelectedArcs->setGeometry(QRect(10, 280, 241, 28));
        mergeSelectedArcs = new QPushButton(tab_2);
        mergeSelectedArcs->setObjectName(QString::fromUtf8("mergeSelectedArcs"));
        mergeSelectedArcs->setGeometry(QRect(10, 310, 241, 28));
        label_81 = new QLabel(tab_2);
        label_81->setObjectName(QString::fromUtf8("label_81"));
        label_81->setGeometry(QRect(260, 290, 141, 21));
        selectedHermiteArc = new QSpinBox(tab_2);
        selectedHermiteArc->setObjectName(QString::fromUtf8("selectedHermiteArc"));
        selectedHermiteArc->setGeometry(QRect(120, 20, 46, 26));
        selectedHermiteArc->setMaximum(100);
        selectedSecondaryHermiteArc = new QSpinBox(tab_2);
        selectedSecondaryHermiteArc->setObjectName(QString::fromUtf8("selectedSecondaryHermiteArc"));
        selectedSecondaryHermiteArc->setGeometry(QRect(440, 290, 61, 26));
        selectedSecondaryHermiteArc->setMaximum(100);
        tabWidget->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        selectedHermitePatch = new QComboBox(tab_6);
        selectedHermitePatch->setObjectName(QString::fromUtf8("selectedHermitePatch"));
        selectedHermitePatch->setGeometry(QRect(100, 10, 76, 24));
        label_46 = new QLabel(tab_6);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setGeometry(QRect(10, 10, 91, 21));
        hermite_patch_index = new QSpinBox(tab_6);
        hermite_patch_index->setObjectName(QString::fromUtf8("hermite_patch_index"));
        hermite_patch_index->setGeometry(QRect(100, 40, 46, 26));
        hermite_patch_index->setMaximum(3);
        label_47 = new QLabel(tab_6);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setGeometry(QRect(10, 40, 91, 21));
        label_48 = new QLabel(tab_6);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setGeometry(QRect(20, 70, 16, 21));
        label_63 = new QLabel(tab_6);
        label_63->setObjectName(QString::fromUtf8("label_63"));
        label_63->setGeometry(QRect(20, 100, 16, 21));
        label_64 = new QLabel(tab_6);
        label_64->setObjectName(QString::fromUtf8("label_64"));
        label_64->setGeometry(QRect(20, 130, 16, 21));
        hermite_patch_x = new QDoubleSpinBox(tab_6);
        hermite_patch_x->setObjectName(QString::fromUtf8("hermite_patch_x"));
        hermite_patch_x->setGeometry(QRect(30, 70, 64, 26));
        hermite_patch_x->setMinimum(-99.000000000000000);
        hermite_patch_y = new QDoubleSpinBox(tab_6);
        hermite_patch_y->setObjectName(QString::fromUtf8("hermite_patch_y"));
        hermite_patch_y->setGeometry(QRect(33, 100, 61, 26));
        hermite_patch_y->setMinimum(-99.000000000000000);
        hermite_patch_z = new QDoubleSpinBox(tab_6);
        hermite_patch_z->setObjectName(QString::fromUtf8("hermite_patch_z"));
        hermite_patch_z->setGeometry(QRect(30, 130, 64, 26));
        hermite_patch_z->setMinimum(-99.000000000000000);
        label_65 = new QLabel(tab_6);
        label_65->setObjectName(QString::fromUtf8("label_65"));
        label_65->setGeometry(QRect(110, 70, 21, 21));
        label_66 = new QLabel(tab_6);
        label_66->setObjectName(QString::fromUtf8("label_66"));
        label_66->setGeometry(QRect(110, 100, 21, 21));
        label_67 = new QLabel(tab_6);
        label_67->setObjectName(QString::fromUtf8("label_67"));
        label_67->setGeometry(QRect(110, 130, 21, 21));
        hermite_patch_ux = new QDoubleSpinBox(tab_6);
        hermite_patch_ux->setObjectName(QString::fromUtf8("hermite_patch_ux"));
        hermite_patch_ux->setGeometry(QRect(130, 70, 64, 26));
        hermite_patch_ux->setMinimum(-99.000000000000000);
        hermite_patch_uy = new QDoubleSpinBox(tab_6);
        hermite_patch_uy->setObjectName(QString::fromUtf8("hermite_patch_uy"));
        hermite_patch_uy->setGeometry(QRect(130, 100, 64, 26));
        hermite_patch_uy->setMinimum(-99.000000000000000);
        hermite_patch_uz = new QDoubleSpinBox(tab_6);
        hermite_patch_uz->setObjectName(QString::fromUtf8("hermite_patch_uz"));
        hermite_patch_uz->setGeometry(QRect(130, 130, 64, 26));
        hermite_patch_uz->setMinimum(-99.000000000000000);
        label_68 = new QLabel(tab_6);
        label_68->setObjectName(QString::fromUtf8("label_68"));
        label_68->setGeometry(QRect(210, 70, 21, 21));
        label_69 = new QLabel(tab_6);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setGeometry(QRect(210, 100, 21, 21));
        label_70 = new QLabel(tab_6);
        label_70->setObjectName(QString::fromUtf8("label_70"));
        label_70->setGeometry(QRect(210, 130, 21, 21));
        hermite_patch_vx = new QDoubleSpinBox(tab_6);
        hermite_patch_vx->setObjectName(QString::fromUtf8("hermite_patch_vx"));
        hermite_patch_vx->setGeometry(QRect(230, 70, 64, 26));
        hermite_patch_vx->setMinimum(-99.000000000000000);
        hermite_patch_vy = new QDoubleSpinBox(tab_6);
        hermite_patch_vy->setObjectName(QString::fromUtf8("hermite_patch_vy"));
        hermite_patch_vy->setGeometry(QRect(230, 100, 64, 26));
        hermite_patch_vy->setMinimum(-99.000000000000000);
        hermite_patch_vz = new QDoubleSpinBox(tab_6);
        hermite_patch_vz->setObjectName(QString::fromUtf8("hermite_patch_vz"));
        hermite_patch_vz->setGeometry(QRect(230, 130, 64, 26));
        hermite_patch_vz->setMinimum(-99.000000000000000);
        label_71 = new QLabel(tab_6);
        label_71->setObjectName(QString::fromUtf8("label_71"));
        label_71->setGeometry(QRect(310, 70, 21, 21));
        label_72 = new QLabel(tab_6);
        label_72->setObjectName(QString::fromUtf8("label_72"));
        label_72->setGeometry(QRect(310, 130, 21, 21));
        label_73 = new QLabel(tab_6);
        label_73->setObjectName(QString::fromUtf8("label_73"));
        label_73->setGeometry(QRect(310, 100, 21, 21));
        hermite_patch_tx = new QDoubleSpinBox(tab_6);
        hermite_patch_tx->setObjectName(QString::fromUtf8("hermite_patch_tx"));
        hermite_patch_tx->setGeometry(QRect(330, 70, 64, 26));
        hermite_patch_tx->setMinimum(-99.000000000000000);
        hermite_patch_ty = new QDoubleSpinBox(tab_6);
        hermite_patch_ty->setObjectName(QString::fromUtf8("hermite_patch_ty"));
        hermite_patch_ty->setGeometry(QRect(330, 100, 64, 26));
        hermite_patch_ty->setMinimum(-99.000000000000000);
        hermite_patch_tz = new QDoubleSpinBox(tab_6);
        hermite_patch_tz->setObjectName(QString::fromUtf8("hermite_patch_tz"));
        hermite_patch_tz->setGeometry(QRect(330, 130, 64, 26));
        hermite_patch_tz->setMinimum(-99.000000000000000);
        tabWidget->addTab(tab_6, QString());
#if QT_CONFIG(shortcut)
        label->setBuddy(rotate_x_slider);
        label_2->setBuddy(rotate_y_slider);
        label_3->setBuddy(rotate_z_slider);
        label_4->setBuddy(zoom_factor_spin_box);
        label_5->setBuddy(trans_x_spin_box);
        label_6->setBuddy(trans_y_spin_box);
        label_7->setBuddy(trans_z_spin_box);
        label_10->setBuddy(zoom_factor_spin_box);
        label_8->setBuddy(trans_y_spin_box);
        label_9->setBuddy(zoom_factor_spin_box);
        label_11->setBuddy(zoom_factor_spin_box);
#endif // QT_CONFIG(shortcut)

        retranslateUi(SideWidget);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(SideWidget);
    } // setupUi

    void retranslateUi(QWidget *SideWidget)
    {
        SideWidget->setWindowTitle(QCoreApplication::translate("SideWidget", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SideWidget", "Transformations", nullptr));
        label->setText(QCoreApplication::translate("SideWidget", "Rotate around x", nullptr));
        label_2->setText(QCoreApplication::translate("SideWidget", "Rotate around y", nullptr));
        label_3->setText(QCoreApplication::translate("SideWidget", "Rotate around z", nullptr));
        label_4->setText(QCoreApplication::translate("SideWidget", "Zoom factor", nullptr));
#if QT_CONFIG(tooltip)
        zoom_factor_spin_box->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("SideWidget", "Translate along x", nullptr));
        label_6->setText(QCoreApplication::translate("SideWidget", "Translate along y", nullptr));
        label_7->setText(QCoreApplication::translate("SideWidget", "Translate along z", nullptr));
        label_10->setText(QCoreApplication::translate("SideWidget", "Scaling", nullptr));
        label_8->setText(QCoreApplication::translate("SideWidget", "Parametric curve:", nullptr));
        ShowTangent->setText(QCoreApplication::translate("SideWidget", "Show Tangent", nullptr));
        ShowAcceleration->setText(QCoreApplication::translate("SideWidget", "Show Acceleration", nullptr));
        label_9->setText(QCoreApplication::translate("SideWidget", "Scaling", nullptr));
#if QT_CONFIG(tooltip)
        scale_spin_box->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_11->setText(QCoreApplication::translate("SideWidget", "Div Point Count", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("SideWidget", "Lab2", nullptr));
        label_12->setText(QCoreApplication::translate("SideWidget", "Selected cyclic curve:", nullptr));
        showCyclicCurves->setText(QCoreApplication::translate("SideWidget", "Show interpolating curves", nullptr));
        showTangents->setText(QCoreApplication::translate("SideWidget", "Show tangents", nullptr));
        showAccelerations->setText(QCoreApplication::translate("SideWidget", "Show acceleration", nullptr));
        label_13->setText(QCoreApplication::translate("SideWidget", "Speed of object on selected curve", nullptr));
        label_14->setText(QCoreApplication::translate("SideWidget", "Selected point on selected cyclic curve", nullptr));
        label_15->setText(QCoreApplication::translate("SideWidget", "X:", nullptr));
        label_16->setText(QCoreApplication::translate("SideWidget", "Y:", nullptr));
        label_17->setText(QCoreApplication::translate("SideWidget", "Z:", nullptr));
        label_18->setText(QCoreApplication::translate("SideWidget", "Distance:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("SideWidget", "Lab3", nullptr));
        label_19->setText(QCoreApplication::translate("SideWidget", "Selected surface", nullptr));
        label_20->setText(QCoreApplication::translate("SideWidget", "Selected texture", nullptr));
        label_21->setText(QCoreApplication::translate("SideWidget", "Selected material", nullptr));
        showTexture->setText(QCoreApplication::translate("SideWidget", "Show texture", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SideWidget", "Lab4", nullptr));
        label_22->setText(QCoreApplication::translate("SideWidget", "Selected shader:", nullptr));
        label_23->setText(QCoreApplication::translate("SideWidget", "Scale factor", nullptr));
        label_24->setText(QCoreApplication::translate("SideWidget", "Smoothing", nullptr));
        label_25->setText(QCoreApplication::translate("SideWidget", "Shading", nullptr));
        label_26->setText(QCoreApplication::translate("SideWidget", "Red:", nullptr));
        label_27->setText(QCoreApplication::translate("SideWidget", "Blue", nullptr));
        label_28->setText(QCoreApplication::translate("SideWidget", "Green", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Lab5), QCoreApplication::translate("SideWidget", "Lab5", nullptr));
        label_29->setText(QCoreApplication::translate("SideWidget", "Selected point", nullptr));
        label_30->setText(QCoreApplication::translate("SideWidget", "x", nullptr));
        label_31->setText(QCoreApplication::translate("SideWidget", "y", nullptr));
        label_32->setText(QCoreApplication::translate("SideWidget", "z", nullptr));
        show_hermite_first_order_derivates->setText(QCoreApplication::translate("SideWidget", "Show First Order Derivatives", nullptr));
        show_hermite_second_order_derivates->setText(QCoreApplication::translate("SideWidget", "Show Second Order Derivatives", nullptr));
        label_74->setText(QCoreApplication::translate("SideWidget", "Selected arc", nullptr));
        label_75->setText(QCoreApplication::translate("SideWidget", "dx", nullptr));
        label_76->setText(QCoreApplication::translate("SideWidget", "dy", nullptr));
        label_77->setText(QCoreApplication::translate("SideWidget", "dz", nullptr));
        createNewCompositeCurve->setText(QCoreApplication::translate("SideWidget", "Create New Composite Curve", nullptr));
        label_78->setText(QCoreApplication::translate("SideWidget", "Selected composite curve:", nullptr));
        highlightSelectedCompositeArc->setText(QCoreApplication::translate("SideWidget", "Highlight selected composite arc", nullptr));
        addArcToCompositeCurve->setText(QCoreApplication::translate("SideWidget", "Add selected arc to selected composite curve", nullptr));
        label_33->setText(QCoreApplication::translate("SideWidget", "r", nullptr));
        label_34->setText(QCoreApplication::translate("SideWidget", "g", nullptr));
        label_35->setText(QCoreApplication::translate("SideWidget", "b", nullptr));
        label_79->setText(QCoreApplication::translate("SideWidget", "Selected primary direction", nullptr));
        continueSelectedArc->setText(QCoreApplication::translate("SideWidget", "Continue Selected Arc (Primary Dir)", nullptr));
        label_80->setText(QCoreApplication::translate("SideWidget", "Selected secondary direction", nullptr));
        joinSelectedArcs->setText(QCoreApplication::translate("SideWidget", "Join Selected Arcs", nullptr));
        mergeSelectedArcs->setText(QCoreApplication::translate("SideWidget", "Merge Selected Arcs", nullptr));
        label_81->setText(QCoreApplication::translate("SideWidget", "Selected secondary arc", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SideWidget", "Hermite Arcs", nullptr));
        label_46->setText(QCoreApplication::translate("SideWidget", "Selected patch", nullptr));
        label_47->setText(QCoreApplication::translate("SideWidget", "Selected point", nullptr));
        label_48->setText(QCoreApplication::translate("SideWidget", "x", nullptr));
        label_63->setText(QCoreApplication::translate("SideWidget", "y", nullptr));
        label_64->setText(QCoreApplication::translate("SideWidget", "z", nullptr));
        label_65->setText(QCoreApplication::translate("SideWidget", "ux", nullptr));
        label_66->setText(QCoreApplication::translate("SideWidget", "uy", nullptr));
        label_67->setText(QCoreApplication::translate("SideWidget", "uz", nullptr));
        label_68->setText(QCoreApplication::translate("SideWidget", "vx", nullptr));
        label_69->setText(QCoreApplication::translate("SideWidget", "vy", nullptr));
        label_70->setText(QCoreApplication::translate("SideWidget", "vz", nullptr));
        label_71->setText(QCoreApplication::translate("SideWidget", "tx", nullptr));
        label_72->setText(QCoreApplication::translate("SideWidget", "tz", nullptr));
        label_73->setText(QCoreApplication::translate("SideWidget", "ty", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("SideWidget", "Hermite Patches", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
