#include "MainWindow.h"

namespace cagd
{
    MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    {
        setupUi(this);

    /*

      the structure of the main window's central widget

     *---------------------------------------------------*
     |                 central widget                    |
     |                                                   |
     |  *---------------------------*-----------------*  |
     |  |     rendering context     |   scroll area   |  |
     |  |       OpenGL widget       | *-------------* |  |
     |  |                           | | side widget | |  |
     |  |                           | |             | |  |
     |  |                           | |             | |  |
     |  |                           | *-------------* |  |
     |  *---------------------------*-----------------*  |
     |                                                   |
     *---------------------------------------------------*

    */
        _side_widget = new SideWidget(this);

        _scroll_area = new QScrollArea(this);
        _scroll_area->setWidget(_side_widget);
        _scroll_area->setSizePolicy(_side_widget->sizePolicy());
        _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        _gl_widget = new GLWidget(this);

        centralWidget()->setLayout(new QHBoxLayout());
        centralWidget()->layout()->addWidget(_gl_widget);
        centralWidget()->layout()->addWidget(_scroll_area);

        // creating a signal slot mechanism between the rendering context and the side widget
        connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
        connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
        connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

        connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

        connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
        connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
        connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));

        // lab2

        connect(_side_widget->Pc, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(setParametricCurveIndex(int)));

        connect(_side_widget->ShowTangent, SIGNAL(clicked(bool)), _gl_widget, SLOT(setVisibilityOfTangents(bool)));
        connect(_side_widget->ShowAcceleration, SIGNAL(clicked(bool)), _gl_widget, SLOT(setVisibilityOfAccelerationVectors(bool)));

        connect(_side_widget->scale_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_scale(double)));
        connect(_side_widget->_div_point_count_widget, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_div_point_count(int)));

        // lab3

        connect(_side_widget->selectedCyclicCurve, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(setSelectedCyclicCurve(int)));

        connect(_side_widget->showCyclicCurves, SIGNAL(clicked(bool)), _gl_widget, SLOT(setVisibilityOfCyclicCurve(bool)));
        connect(_side_widget->showTangents, SIGNAL(clicked(bool)), _gl_widget, SLOT(setVisibilityOfTangent(bool)));
        connect(_side_widget->showAccelerations, SIGNAL(clicked(bool)), _gl_widget, SLOT(setVisiblityOfAccelerationVector(bool)));

        connect(_side_widget->speedOfSelectedCurve, SIGNAL(valueChanged(int)), _gl_widget, SLOT(setSpeedOfSelectedCurve(int)));
        connect(_side_widget->selectedPoint, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(setSelectedPoint(int)));

        connect(_gl_widget, SIGNAL(setSelectedX(double)), _side_widget->selectedX, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(setSelectedY(double)), _side_widget->selectedY, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(setSelectedZ(double)), _side_widget->selectedZ, SLOT(setValue(double)));

        connect(_side_widget->selectedX, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setSelectedXSlot(double)));
        connect(_side_widget->selectedY, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setSelectedYSlot(double)));
        connect(_side_widget->selectedZ, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setSelectedZSlot(double)));

        connect(_gl_widget, SIGNAL(distanceSignal(double)), _side_widget->distance, SLOT(setValue(double)));
        connect(_side_widget->distance, SIGNAL(valueChanged(double)), _gl_widget, SLOT(distanceSlot(double)));

        // lab4

        connect(_side_widget->selectedSurface, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(setSelectedSurface(int)));
        connect(_side_widget->selectedMaterial, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(setSelectedMaterial(int)));
        connect(_side_widget->selectedTexture, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(setSelectedTexture(int)));

        connect(_side_widget->showTexture, SIGNAL(clicked(bool)), _gl_widget, SLOT(setVisibilityOfTexture(bool)));

        // lab5

        connect(_side_widget->selecteShader, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(setSelectedShader(int)));

        connect(_side_widget->scale, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setShaderScale(double)));
        connect(_side_widget->smoothing, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setSmoothing(double)));
        connect(_side_widget->shading, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setShading(double)));


        connect(_side_widget->red, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setRed(double)));
        connect(_side_widget->blue, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setBlue(double)));
        connect(_side_widget->green, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setGreen(double)));

        // Project - Hermite arcs


        connect(_gl_widget,SIGNAL(xHermitePointChanged(double)),_side_widget->hermite_x,SLOT(setValue(double)));
        connect(_gl_widget,SIGNAL(yHermitePointChanged(double)),_side_widget->hermite_y,SLOT(setValue(double)));
        connect(_gl_widget,SIGNAL(zHermitePointChanged(double)),_side_widget->hermite_z,SLOT(setValue(double)));

        connect(_gl_widget,SIGNAL(dxHermitePointChanged(double)),_side_widget->hermite_dx,SLOT(setValue(double)));
        connect(_gl_widget,SIGNAL(dyHermitePointChanged(double)),_side_widget->hermite_dy,SLOT(setValue(double)));
        connect(_gl_widget,SIGNAL(dzHermitePointChanged(double)),_side_widget->hermite_dz,SLOT(setValue(double)));

        connect(_side_widget->selectedHermiteArc, SIGNAL(valueChanged(int)), _gl_widget, SLOT(_setSelectedHermiteArc(int)));
        connect(_side_widget->selectedSecondaryHermiteArc, SIGNAL(valueChanged(int)), _gl_widget, SLOT(_setSelectedSecondaryHermiteArc(int)));

        connect(_side_widget->hermite_index, SIGNAL(valueChanged(int)), _gl_widget, SLOT(setHermitePointIndex(int)));
        connect(_side_widget->hermite_x, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePointx(double)));
        connect(_side_widget->hermite_y, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePointy(double)));
        connect(_side_widget->hermite_z, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePointz(double)));

        connect(_side_widget->hermite_dx, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePointdx(double)));
        connect(_side_widget->hermite_dy, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePointdy(double)));
        connect(_side_widget->hermite_dz, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePointdz(double)));

        connect(_side_widget->show_hermite_first_order_derivates, SIGNAL(clicked(bool)), _gl_widget, SLOT(showHermiteFirstOrderDerivates(bool)));
        connect(_side_widget->show_hermite_second_order_derivates, SIGNAL(clicked(bool)), _gl_widget, SLOT(showHermiteSecondOrderDerivates(bool)));

        connect(_side_widget->selectedCompositeArc, SIGNAL(valueChanged(int)), _gl_widget, SLOT(_setSelectedCompositeArc(int)));
        connect(_side_widget->highlightSelectedCompositeArc, SIGNAL(clicked(bool)), _gl_widget, SLOT(_highlightHermiteCompositeArc(bool)));
        connect(_side_widget->createNewCompositeCurve, SIGNAL(pressed()), _gl_widget, SLOT(_createNewCompositeArc()));
        connect(_side_widget->addArcToCompositeCurve, SIGNAL(pressed()), _gl_widget, SLOT(_addSelectedArcToSelectedCompositeArc()));

        connect(_side_widget->hermite_red, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_hermite_red(double)));
        connect(_side_widget->hermite_green, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_hermite_green(double)));
        connect(_side_widget->hermite_blue, SIGNAL(valueChanged(double)), _gl_widget, SLOT(_hermite_blue(double)));

        connect(_side_widget->selectedPrimaryDirection, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(_setPrimaryDirection(int)));
        connect(_side_widget->selectedSecondaryDirection, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(_setSecondaryDirection(int)));


        connect(_side_widget->continueSelectedArc, SIGNAL(pressed()), _gl_widget, SLOT(_continueArc()));
        connect(_side_widget->joinSelectedArcs, SIGNAL(pressed()), _gl_widget, SLOT(_joinArc()));
        connect(_side_widget->mergeSelectedArcs, SIGNAL(pressed()), _gl_widget, SLOT(_mergeArc()));


        // Project - Hermite patch

        connect(_side_widget->selectedHermitePatch, SIGNAL(valueChanged(int)), _gl_widget, SLOT(_setSelectedHermitePatch(int)));


        connect(_gl_widget, SIGNAL(HermitePatchPointChangeX(double)), _side_widget->hermite_patch_x, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeY(double)), _side_widget->hermite_patch_y, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeZ(double)), _side_widget->hermite_patch_z, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeUX(double)), _side_widget->hermite_patch_ux, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeUY(double)), _side_widget->hermite_patch_uy, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeUZ(double)), _side_widget->hermite_patch_uz, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeVX(double)), _side_widget->hermite_patch_vx, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeVY(double)), _side_widget->hermite_patch_vy, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeVZ(double)), _side_widget->hermite_patch_vz, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeTX(double)), _side_widget->hermite_patch_tx, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeTY(double)), _side_widget->hermite_patch_ty, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeTZ(double)), _side_widget->hermite_patch_tz, SLOT(setValue(double)));

        connect(_side_widget->hermite_patch_index, SIGNAL(valueChanged(int)), _gl_widget, SLOT(_setSelectedHermitePatchPoint(int)));

        connect(_side_widget->hermite_patch_x, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointX(double)));
        connect(_side_widget->hermite_patch_y, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointY(double)));
        connect(_side_widget->hermite_patch_z, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointZ(double)));
        connect(_side_widget->hermite_patch_vx, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointVX(double)));
        connect(_side_widget->hermite_patch_vy, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointVY(double)));
        connect(_side_widget->hermite_patch_vz, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointVZ(double)));
        connect(_side_widget->hermite_patch_ux, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointUX(double)));
        connect(_side_widget->hermite_patch_uy, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointUY(double)));
        connect(_side_widget->hermite_patch_uz, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointUZ(double)));
        connect(_side_widget->hermite_patch_tx, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointTX(double)));
        connect(_side_widget->hermite_patch_ty, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointTY(double)));
        connect(_side_widget->hermite_patch_tz, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointTZ(double)));

        connect(_side_widget->selectedSecondaryHermitePatch, SIGNAL(valueChanged(int)), _gl_widget, SLOT(_setSelectedSecondaryHermitePatch(int)));
        connect(_side_widget->showULines, SIGNAL(clicked(bool)), _gl_widget, SLOT(_setVisibilityOfULines(bool)));
        connect(_side_widget->showVLines, SIGNAL(clicked(bool)), _gl_widget, SLOT(_setVisibilityOfVLines(bool)));
        connect(_side_widget->highlightSelectedCompositePatch, SIGNAL(clicked(bool)), _gl_widget, SLOT(_highlightSelectedCompositePatch(bool)));
        connect(_side_widget->showHermitePatchFirstOrder, SIGNAL(clicked(bool)), _gl_widget, SLOT(_setVisibilityOfFirstOrderDerivatives(bool)));
        connect(_side_widget->showHermitePatchSecondaryOrder, SIGNAL(clicked(bool)), _gl_widget, SLOT(_setVisibilityOfSecondOrderDerivatives(bool)));

        connect(_side_widget->useTextures, SIGNAL(clicked(bool)), _gl_widget, SLOT(_showHermitePatchTextures(bool)));
        connect(_side_widget->useShaders, SIGNAL(clicked(bool)), _gl_widget, SLOT(_showHermitePatchTextures(bool)));

        connect(_side_widget->selectedPatchMaterial, SIGNAL(currentIndexChanged(int)),_gl_widget, SLOT(_setHermitePatchMaterial(int)));
        connect(_side_widget->selectedPatchTexture, SIGNAL(currentIndexChanged(int)),_gl_widget, SLOT(_setHermitePatchTexture(int)));
        connect(_side_widget->selectedPatchShader, SIGNAL(currentIndexChanged(int)),_gl_widget, SLOT(_setHermitePatchShader(int)));

        connect(_side_widget->createNewCompositePatch, SIGNAL(pressed()), _gl_widget, SLOT(_createNewCompositePatch()));
        connect(_side_widget->addSelectedPatchToSelectedCompositePatch, SIGNAL(pressed()), _gl_widget, SLOT(_addSelectedPatchToSelectedCompositePatch()));

        connect(_side_widget->continueSelectedPatch, SIGNAL(pressed()), _gl_widget, SLOT(_continuePatch()));
        connect(_side_widget->joinSelectedPatches, SIGNAL(pressed()), _gl_widget, SLOT(_joinPatch()));
        connect(_side_widget->mergeSelectedPatches, SIGNAL(pressed()), _gl_widget, SLOT(_mergePatch()));

    }


    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
