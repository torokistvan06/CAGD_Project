#include "HermiteCompositeSurfaces3.h"

namespace cagd{
    HermiteCompositeSurface3::HermiteCompositeSurface3(){
        this->_minimal_patch_count_to_be_reserved = 3;
        this->_number_of_patches = 0;
    }

    HermiteCompositeSurface3::~HermiteCompositeSurface3(){
        this->_attributes.clear();
        this->_number_of_patches = 0;
    }

//    GLboolean HermiteCompositeSurface3::InsertNewPatch(BicubicHermitePatch3 patch) {
//        return false;
//    };

    GLboolean HermiteCompositeSurface3::DeleteExistingPatch(GLuint index) {
        return false;
    };

    GLboolean HermiteCompositeSurface3::ContinueExistingPatch(GLuint index, Direction direction) {
        return false;
    };

    GLboolean HermiteCompositeSurface3::JoinExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1) {
        return false;
    };

    GLboolean HermiteCompositeSurface3::MergeExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1) {
        return false;
    };

    GLboolean HermiteCompositeSurface3::RenderAllPatches(GLuint order, GLenum render_mode) const {
        return false;
    };

    GLboolean HermiteCompositeSurface3::RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const {
        return false;
    };
}

