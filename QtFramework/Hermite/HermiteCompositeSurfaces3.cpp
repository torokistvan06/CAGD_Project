#include "HermiteCompositeSurfaces3.h"

namespace cagd{
    HermiteCompositeSurface3::HermiteCompositeSurface3(GLuint index){
        this->_number_of_patches = 0;
        this->_composite_index = index;
    }

    HermiteCompositeSurface3::~HermiteCompositeSurface3(){
        this->_attributes.clear();
        this->_number_of_patches = 0;
    }

    GLboolean HermiteCompositeSurface3::updatePatch(GLuint index, TriangulatedMesh3* image) {
        for(GLuint i = 0 ; i < _number_of_patches ; i++) {
            if (_attributes[i].index == index) {
                _attributes[i].image = image;
            }
        }
        return true;
    }

    GLboolean HermiteCompositeSurface3::InsertNewPatch(BicubicHermitePatch3* patch, TriangulatedMesh3* image, Material* mat, QOpenGLTexture* texture, ShaderProgram* shader, int index) {
       PatchAttributes element;

       element.patch = patch;
       element.image = image;
       element.material = mat;
       element.texture = texture;
       element.shader = shader;
       element.index = index;

       for( GLuint i = 0 ; i < 8 ; i++) {
           element.neighbours[i] = nullptr;
       }

       _number_of_patches += 1;
       this->_attributes.push_back(element);

       return true;
    };

    GLboolean HermiteCompositeSurface3::DeleteExistingPatch(GLuint index) {
        return false;
    };

    BicubicHermitePatch3* HermiteCompositeSurface3::ContinueExistingPatch(GLuint index, int direction) {
        //north, east, west, south

        int ind = -1;

        for(GLuint i = 0 ; i < _number_of_patches ; i++) {
            if(_attributes[i].index == index) {
               ind = i;
            }
        }

        if(ind == -1){
            return nullptr;
        }

        //hibakezelesek hogy ne legyen mar ott szomszed

        BicubicHermitePatch3 *patch = new BicubicHermitePatch3();

        DCoordinate3 leftUpper = getCoordinates(0, ind, 'c');
        DCoordinate3 rightUpper = getCoordinates(1, ind, 'c');
        DCoordinate3 leftLower = getCoordinates(2, ind, 'c');
        DCoordinate3 rightLower = getCoordinates(3, ind, 'c');

        DCoordinate3 leftUpperV = getCoordinates(0, ind, 'v');
        DCoordinate3 rightUpperV = getCoordinates(1, ind, 'v');
        DCoordinate3 leftLowerV = getCoordinates(2, ind, 'v');
        DCoordinate3 rightLowerV = getCoordinates(3, ind, 'v');

        DCoordinate3 leftUpperU = getCoordinates(0, ind, 'u');
        DCoordinate3 rightUpperU = getCoordinates(1, ind, 'u');
        DCoordinate3 leftLowerU = getCoordinates(2, ind, 'u');
        DCoordinate3 rightLowerU = getCoordinates(3, ind, 'u');

        DCoordinate3 leftUpperT = getCoordinates(0, ind, 't');
        DCoordinate3 rightUpperT = getCoordinates(1, ind, 't');
        DCoordinate3 leftLowerT = getCoordinates(2, ind, 't');
        DCoordinate3 rightLowerT = getCoordinates(3, ind, 't');

        //esetekre bontani hogy merre kell continue
        //megvan minden pont es vector -> distanceokat kiszamolni, uj arcok es az uj acrokbol 1 uj patch

        if(direction == 0){
            DCoordinate3 distance1 = leftUpper - leftLower;
            DCoordinate3 distance2 = rightUpper - rightLower;

            if(distance1.x() < 0) {
                distance1.x() *= -1;
            }

            if(distance1.y() < 0) {
                distance1.y() *= -1;
            }

            if(distance1.z() < 0) {
                distance1.z() *= -1;
            }

            if(distance2.x() < 0) {
                distance2.x() *= -1;
            }

            if(distance2.y() < 0) {
                distance2.y() *= -1;
            }

            if(distance2.z() < 0) {
                distance2.z() *= -1;
            }

            //corners
            patch->SetData(0, 0, leftUpper + distance1);
            patch->SetData(0, 1, rightUpper + distance2);
            patch->SetData(1, 0, leftUpper);
            patch->SetData(1, 1, rightUpper);

            //u
            patch->SetData(2, 0, leftLowerU);
            patch->SetData(2, 1, rightLowerU);
            patch->SetData(3, 0, leftUpperU);
            patch->SetData(3, 1, rightUpperU);

            //v
            patch->SetData(0, 2, leftLowerV);
            patch->SetData(0, 3, rightLowerV);
            patch->SetData(1, 2, leftUpperV);
            patch->SetData(1, 3, rightUpperV);

            //t
            patch->SetData(2, 2, leftLowerT);
            patch->SetData(2, 3, rightLowerT);
            patch->SetData(3, 2, leftUpperT);
            patch->SetData(3, 3, rightUpperT);

        } //EAST
        else if (direction == 1) {
            DCoordinate3 distance1 = rightUpper - leftUpper;
            DCoordinate3 distance2 = rightLower - leftLower;

            if(distance1.x() < 0) {
                distance1.x() *= -1;
            }

            if(distance1.y() < 0) {
                distance1.y() *= -1;
            }

            if(distance1.z() < 0) {
                distance1.z() *= -1;
            }

            if(distance2.x() < 0) {
                distance2.x() *= -1;
            }

            if(distance2.y() < 0) {
                distance2.y() *= -1;
            }

            if(distance2.z() < 0) {
                distance2.z() *= -1;
            }

            //corners
            patch->SetData(0, 0, rightUpper);
            patch->SetData(0, 1, rightUpper + distance1);
            patch->SetData(1, 0, rightLower);
            patch->SetData(1, 1, rightLower + distance2);

            //u
            patch->SetData(2, 0, rightUpperU);
            patch->SetData(2, 1, leftUpperU);
            patch->SetData(3, 0, rightLowerU);
            patch->SetData(3, 1, leftLowerU);

            //v
            patch->SetData(0, 2, rightUpperV);
            patch->SetData(0, 3, leftUpperV);
            patch->SetData(1, 2, rightLowerV);
            patch->SetData(1, 3, leftLowerV);

            //t
            patch->SetData(2, 2, rightUpperT);
            patch->SetData(2, 3, leftUpperT);
            patch->SetData(3, 2, rightLowerT);
            patch->SetData(3, 3, leftLowerT);

        }
        //WEST
        else if (direction == 2) {
            DCoordinate3 distance1 = leftUpper - rightUpper;
            DCoordinate3 distance2 = leftLower - rightLower;

            if(distance1.x() < 0) {
                distance1.x() *= -1;
            }

            if(distance1.y() < 0) {
                distance1.y() *= -1;
            }

            if(distance1.z() < 0) {
                distance1.z() *= -1;
            }

            if(distance2.x() < 0) {
                distance2.x() *= -1;
            }

            if(distance2.y() < 0) {
                distance2.y() *= -1;
            }

            if(distance2.z() < 0) {
                distance2.z() *= -1;
            }

            //corners
            patch->SetData(0, 0, leftUpper - distance1);
            patch->SetData(0, 1, leftUpper);
            patch->SetData(1, 0, leftLower - distance2);
            patch->SetData(1, 1, leftLower);

            //u
            patch->SetData(2, 0, rightUpperU);
            patch->SetData(2, 1, leftUpperU);
            patch->SetData(3, 0, rightLowerU);
            patch->SetData(3, 1, leftLowerU);

            //v
            patch->SetData(0, 2, rightUpperV);
            patch->SetData(0, 3, leftUpperV);
            patch->SetData(1, 2, rightLowerV);
            patch->SetData(1, 3, leftLowerV);

            //t
            patch->SetData(2, 2, rightUpperT);
            patch->SetData(2, 3, leftUpperT);
            patch->SetData(3, 2, rightLowerT);
            patch->SetData(3, 3, leftLowerT);
        }
        //SOUTH
        else if (direction == 3) {
            DCoordinate3 distance1 = leftUpper - leftLower;
            DCoordinate3 distance2 = rightUpper - rightLower;

            if(distance1.x() < 0) {
                distance1.x() *= -1;
            }

            if(distance1.y() < 0) {
                distance1.y() *= -1;
            }

            if(distance1.z() < 0) {
                distance1.z() *= -1;
            }

            if(distance2.x() < 0) {
                distance2.x() *= -1;
            }

            if(distance2.y() < 0) {
                distance2.y() *= -1;
            }

            if(distance2.z() < 0) {
                distance2.z() *= -1;
            }

            //corners
            patch->SetData(0, 0, leftLower);
            patch->SetData(0, 1, rightLower);
            patch->SetData(1, 0, leftLower - distance1);
            patch->SetData(1, 1, rightLower - distance2);

            //u
            patch->SetData(2, 0, leftLowerU);
            patch->SetData(2, 1, rightLowerU);
            patch->SetData(3, 0, leftUpperU);
            patch->SetData(3, 1, rightUpperU);

            //v
            patch->SetData(0, 2, leftLowerV);
            patch->SetData(0, 3, rightLowerV);
            patch->SetData(1, 2, leftUpperV);
            patch->SetData(1, 3, rightUpperV);

            //t
            patch->SetData(2, 2, leftLowerT);
            patch->SetData(2, 3, rightLowerT);
            patch->SetData(3, 2, leftUpperT);
            patch->SetData(3, 3, rightUpperT);

        }

        return patch;
    };

    BicubicHermitePatch3* HermiteCompositeSurface3::JoinExistingPatches(GLuint index_0, int direction_0, GLuint index_1, int direction_1) {
        int ind_primary = -1, ind_secondary = -1;

        if(index_0 == index_1){
            return nullptr;
        }

        for(GLuint i = 0 ; i < _number_of_patches ; i++) {
            if(_attributes[i].index == index_0) {
               ind_primary = i;
            }

            if(_attributes[i].index == index_1) {
               ind_secondary = i;
            }
        }

        if(ind_primary == -1 || ind_secondary == -1){
            return nullptr;
        }

        //hibakezeles hogy ne lehessen hozzaadni ha van mar azon az oldalon szomszed


    };

    GLboolean HermiteCompositeSurface3::MergeExistingPatches(GLuint index_0, int direction_0, GLuint index_1, int direction_1) {
        return false;
    };

    GLboolean HermiteCompositeSurface3::RenderAllPatches() const {
        for(GLuint i = 0 ; i < _number_of_patches ; i++) {

            _attributes[i].material->Apply();
            _attributes[i].texture->bind();
            _attributes[i].shader->Enable();
            _attributes[i].image->Render();
            _attributes[i].shader->Disable();
            _attributes[i].texture->release();
        }

        return true;
    };

    GLboolean HermiteCompositeSurface3::RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const {
        return false;
    };


    void HermiteCompositeSurface3::showTextures(bool visibility) {
        _use_textures = visibility;
    }

    void HermiteCompositeSurface3::showShaders(bool visibility) {
        _use_shaders = visibility;
    }

    void HermiteCompositeSurface3::showULines(bool visibility) {
        _show_u_lines = visibility;
    }

    void HermiteCompositeSurface3::showVLines(bool visibility) {
        _show_v_lines = visibility;
    }

    void HermiteCompositeSurface3::showFirstOrder(bool visibility) {
        _show_first_order_derivates = visibility;
    }

    void HermiteCompositeSurface3::showSecondOrder(bool visibility) {
        _show_second_order_derivates = visibility;
    }

    void HermiteCompositeSurface3::hightlightSelected(bool visibility) {
        _highlight_selected_composite_patch = visibility;
    }

    void HermiteCompositeSurface3::setSelectedPatch(int index) {
        _selected_patch = index;
    }

    void HermiteCompositeSurface3::setSelectedCompositePatch(int index) {
        _selected_composite_patch = index;
    }

    //vector type c - corner, u, v, t
    DCoordinate3 HermiteCompositeSurface3::getCoordinates(int pointIndex, int patchIndex, char vectorType) {

        GLdouble x, y, z;
        //left upper
        if(pointIndex == 0){
            if (vectorType == 'c'){
                _attributes[patchIndex].patch->GetData(0, 0, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'v'){
                _attributes[patchIndex].patch->GetData(0, 2, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'u'){
                _attributes[patchIndex].patch->GetData(2, 0, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else {
                _attributes[patchIndex].patch->GetData(2, 2, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            }
        }
        //right upper
        else if(pointIndex == 1){
            if (vectorType == 'c'){
                _attributes[patchIndex].patch->GetData(0, 1, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'v'){
                _attributes[patchIndex].patch->GetData(0, 3, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'u'){
                _attributes[patchIndex].patch->GetData(2, 1, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else {
                _attributes[patchIndex].patch->GetData(2, 3, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            }
        }//left lower
        else if(pointIndex == 2){
            if (vectorType == 'c'){
                _attributes[patchIndex].patch->GetData(1, 0, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'v'){
                _attributes[patchIndex].patch->GetData(1, 2, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'u'){
                _attributes[patchIndex].patch->GetData(3, 0, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else {
                _attributes[patchIndex].patch->GetData(3, 2, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            }
        }
        //right lower
        else if(pointIndex == 3){
            if (vectorType == 'c'){
                _attributes[patchIndex].patch->GetData(1, 1, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'v'){
                _attributes[patchIndex].patch->GetData(1, 3, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'u'){
                _attributes[patchIndex].patch->GetData(3, 1, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else {
                _attributes[patchIndex].patch->GetData(3, 3, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            }
        }
    }
}

