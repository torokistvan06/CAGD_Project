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

        int ind;

        for(GLuint i = 0 ; i < _number_of_patches ; i++) {
            if(_attributes[i].index == index) {
               ind = i;
            }
        }

        //hibakezelesek hogy ne legyen mar ott szomszed

        BicubicHermitePatch3 *patch = new BicubicHermitePatch3();
        GLdouble x, y, z;

        //current patch corner points
        _attributes[ind].patch->GetData(0, 0, x, y, z);
        DCoordinate3 leftUpper(x, y, z);

        _attributes[ind].patch->GetData(0, 1, x, y, z);
        DCoordinate3 leftLower(x, y, z);

        _attributes[ind].patch->GetData(1, 0, x, y, z);
        DCoordinate3 rightUpper(x, y, z);

        _attributes[ind].patch->GetData(1, 1, x, y, z);
        DCoordinate3 rightLower(x, y, z);

        //current patch first order partial derivatives in u direction at the corner
        _attributes[ind].patch->GetData(0, 2, x, y, z);
        DCoordinate3 leftUpperU(x, y, z);

        _attributes[ind].patch->GetData(0, 3, x, y, z);
        DCoordinate3 leftLowerU(x, y, z);

        _attributes[ind].patch->GetData(1, 2, x, y, z);
        DCoordinate3 rightUpperU(x, y, z);

        _attributes[ind].patch->GetData(1, 3, x, y, z);
        DCoordinate3 rightLowerU(x, y, z);

        //current patch first order partial derivatives in v direction at the corner
        _attributes[ind].patch->GetData(2, 0, x, y, z);
        DCoordinate3 leftUpperV(x, y, z);

        _attributes[ind].patch->GetData(2, 1, x, y, z);
        DCoordinate3 leftLowerV(x, y, z);

        _attributes[ind].patch->GetData(3, 0, x, y, z);
        DCoordinate3 rightUpperV(x, y, z);

        _attributes[ind].patch->GetData(3, 1, x, y, z);
        DCoordinate3 rightLowerV(x, y, z);

        //current twist vectors
        _attributes[ind].patch->GetData(2, 2, x, y, z);
        DCoordinate3 leftUpperT(x, y, z);

        _attributes[ind].patch->GetData(2, 3, x, y, z);
        DCoordinate3 leftLowerT(x, y, z);

        _attributes[ind].patch->GetData(3, 2, x, y, z);
        DCoordinate3 rightUpperT(x, y, z);

        _attributes[ind].patch->GetData(3, 3, x, y, z);
        DCoordinate3 rightLowerT(x, y, z);

        //esetekre bontani hogy merre kell continue
        //megvan minden pont es vector -> distanceokat kiszamolni, uj arcok es az uj acrokbol 1 uj patch

        //NORTH -> szukseg van leftUpper, righUpper stb..
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

            patch->SetCorner(0, leftUpper + distance1);
            patch->SetCorner(1, leftUpper);
            patch->SetCorner(2, rightUpper + distance2);
            patch->SetCorner(3, rightUpper);

            patch->SetUvector(0, leftUpperU);
            patch->SetUvector(1, leftUpperU);
            patch->SetUvector(2, rightUpperU);
            patch->SetUvector(3, rightUpperU);

            patch->SetVvector(0, leftUpperV);
            patch->SetVvector(1, leftUpperV);
            patch->SetVvector(2, rightUpperV);
            patch->SetVvector(3, rightUpperV);

            patch->SetTwistVector(0, leftUpperT);
            patch->SetTwistVector(1, leftUpperT);
            patch->SetTwistVector(2, rightUpperT);
            patch->SetTwistVector(3, rightUpperT);
        }

        return patch;
    };

    GLboolean HermiteCompositeSurface3::JoinExistingPatches(GLuint index_0, int direction_0, GLuint index_1, int direction_1) {
        return false;
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
}

