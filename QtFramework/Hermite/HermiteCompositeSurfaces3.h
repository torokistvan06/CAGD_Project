#ifndef HERMITECOMPOSITESURFACES3_H
#define HERMITECOMPOSITESURFACES3_H

#include <Core/Materials.h>
#include <QOpenGLTexture>
#include "../Core/ShaderPrograms.h"
#include "BicubicHermitePatch3.h"

namespace cagd
{
    class HermiteCompositeSurface3
    {
    public:

        class PatchAttributes
        {
        public:
            BicubicHermitePatch3            *patch;
            TriangulatedMesh3               *image;
            Material                        *material; // use pointers to pre-defined materials
            QOpenGLTexture                  *texture;  // use pointers to pre-defined textures
            ShaderProgram                   *shader;   // use pointers to pre-defined shader programs
            GLint                           index;
            // other attributes
            // ...

            PatchAttributes                 *neighbours[8];
            GLint                           connection_type[8];

            // ctor, copy ctor, assignment operator, dtor (they are required by the std::vector!)
        };

        GLuint                           _selected_patch;
        GLuint                           _selected_composite_patch;

        GLuint                           _composite_index;
        GLuint                          _number_of_patches;

        bool                            _use_textures;
        bool                            _use_shaders;
        bool                            _show_u_lines;
        bool                            _show_v_lines;
        bool                            _show_first_order_derivates;
        bool                            _show_second_order_derivates;
        bool                            _highlight_selected_composite_patch;


    protected:
        std::vector<PatchAttributes>    _attributes;

    public:
        // special/default ctor
        HermiteCompositeSurface3(GLuint);
        ~HermiteCompositeSurface3();

        // operations
        GLboolean InsertNewPatch(BicubicHermitePatch3* patch, TriangulatedMesh3* image, Material* mat, QOpenGLTexture* texture, ShaderProgram* shader, int index);
        GLboolean DeleteExistingPatch(GLuint index);
        BicubicHermitePatch3* ContinueExistingPatch(GLuint index, int direction);
        BicubicHermitePatch3* JoinExistingPatches(GLuint index_0, int direction_0, GLuint index_1, int direction_1);
        GLboolean MergeExistingPatches(GLuint index_0, int direction_0, GLuint index_1, int direction_1);

        GLboolean RenderAllPatches() const;
        GLboolean RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const;

        GLboolean updatePatch(GLuint index, TriangulatedMesh3* image);

        void showTextures(bool);
        void showShaders(bool);
        void showULines(bool);
        void showVLines(bool);
        void showFirstOrder(bool);
        void showSecondOrder(bool);
        void hightlightSelected(bool);
        void setSelectedPatch(int);
        void setSelectedCompositePatch(int);

        // other setters and getters
        // ...

        DCoordinate3 getCoordinates(int pointIndex, int patchIndex, char vectorType);
    };
}

#endif // HERMITECOMPOSITESURFACES3_H

