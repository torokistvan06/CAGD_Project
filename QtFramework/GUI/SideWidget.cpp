#include "SideWidget.h"

namespace cagd
{
    SideWidget::SideWidget(QWidget *parent): QWidget(parent)
    {
        setupUi(this);

        QPalette p = rotate_x_slider->palette();

        p.setColor(QPalette::Highlight, QColor(255,50,10).lighter());

        rotate_x_slider->setPalette(p);

        p = rotate_y_slider->palette();

        p.setColor(QPalette::Highlight, QColor(50,255,10).lighter());

        rotate_y_slider->setPalette(p);

        // Lab2

        this->Pc->addItem("Spiral on cone");
        this->Pc->addItem("Circular Helix");
        this->Pc->addItem("Rose");
        this->Pc->addItem("Torus Knot");
        this->Pc->addItem("Cyclo");
        this->Pc->addItem("Spherical sinusoid");
        this->Pc->addItem("Clelia");
        this->Pc->addItem("Basin");

        // Lab3

        this->selectedCyclicCurve->addItem("Interp1");
        this->selectedCyclicCurve->addItem("Interp2");
        this->selectedCyclicCurve->addItem("Interp3");
        this->selectedCyclicCurve->addItem("Approx");

        this->selectedPoint->addItem("0");
        this->selectedPoint->addItem("1");
        this->selectedPoint->addItem("2");
        this->selectedPoint->addItem("3");
        this->selectedPoint->addItem("4");

        // Lab4

        this->selectedSurface->addItem("Torus");
        this->selectedSurface->addItem("Sphere");
        this->selectedSurface->addItem("Cylindre");
        this->selectedSurface->addItem("Bohemian Dome");
        this->selectedSurface->addItem("Cone sinusoid");
        this->selectedSurface->addItem("Helicoid");

        this->selectedTexture->addItem("1");
        this->selectedTexture->addItem("2");
        this->selectedTexture->addItem("3");
        this->selectedTexture->addItem("4");
        this->selectedTexture->addItem("5");
        this->selectedTexture->addItem("6");
        this->selectedTexture->addItem("7");
        this->selectedTexture->addItem("8");
        this->selectedTexture->addItem("9");
        this->selectedTexture->addItem("10");
        this->selectedTexture->addItem("11");
        this->selectedTexture->addItem("12");
        this->selectedTexture->addItem("13");
        this->selectedTexture->addItem("14");

        this->selectedMaterial->addItem("Brass");
        this->selectedMaterial->addItem("Gold");
        this->selectedMaterial->addItem("Silver");
        this->selectedMaterial->addItem("Emerald");
        this->selectedMaterial->addItem("Pearl");
        this->selectedMaterial->addItem("Ruby");
        this->selectedMaterial->addItem("Turquoise");


        // Lab5

        this->selecteShader->addItem("Directional Light");
        this->selecteShader->addItem("Two Sided Light");
        this->selecteShader->addItem("Toon");
        this->selecteShader->addItem("Reflection Lines");

        // Project - Hermite Arc

        this->selectedPrimaryDirection->addItem("Left");
        this->selectedPrimaryDirection->addItem("Right");

        this->selectedSecondaryDirection->addItem("Left");
        this->selectedSecondaryDirection->addItem("Right");

        // Project - Hermite Patches:

        this->selectedPatchPrimaryDirection->addItem("North");
        this->selectedPatchPrimaryDirection->addItem("East");
        this->selectedPatchPrimaryDirection->addItem("West");
        this->selectedPatchPrimaryDirection->addItem("South");

        this->selectedPatchSecondaryDirection->addItem("North");
        this->selectedPatchSecondaryDirection->addItem("East");
        this->selectedPatchSecondaryDirection->addItem("West");
        this->selectedPatchSecondaryDirection->addItem("South");

        this->selectedPatchTexture->addItem("1");
        this->selectedPatchTexture->addItem("2");
        this->selectedPatchTexture->addItem("3");
        this->selectedPatchTexture->addItem("4");
        this->selectedPatchTexture->addItem("5");
        this->selectedPatchTexture->addItem("6");
        this->selectedPatchTexture->addItem("7");
        this->selectedPatchTexture->addItem("8");
        this->selectedPatchTexture->addItem("9");
        this->selectedPatchTexture->addItem("10");
        this->selectedPatchTexture->addItem("11");
        this->selectedPatchTexture->addItem("12");
        this->selectedPatchTexture->addItem("13");
        this->selectedPatchTexture->addItem("14");

        this->selectedPatchMaterial->addItem("Brass");
        this->selectedPatchMaterial->addItem("Gold");
        this->selectedPatchMaterial->addItem("Silver");
        this->selectedPatchMaterial->addItem("Emerald");
        this->selectedPatchMaterial->addItem("Pearl");
        this->selectedPatchMaterial->addItem("Ruby");
        this->selectedPatchMaterial->addItem("Turquoise");

        this->selectedPatchShader->addItem("Directional Light");
        this->selectedPatchShader->addItem("Two Sided Light");
        this->selectedPatchShader->addItem("Toon");
        this->selectedPatchShader->addItem("Reflection Lines");

    }

}
