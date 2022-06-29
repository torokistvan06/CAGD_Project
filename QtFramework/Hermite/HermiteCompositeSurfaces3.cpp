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

    GLboolean HermiteCompositeSurface3::ContinueExistingPatch(GLuint index, int direction) {
        return false;
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

