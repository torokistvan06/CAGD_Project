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
