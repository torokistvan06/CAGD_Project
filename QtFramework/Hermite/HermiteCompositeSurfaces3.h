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
        enum Direction{N, NW, W, SW, S, SE, E, NE};

        class PatchAttributes
        {
        public:
            BicubicHermitePatch3            *patch;
            TriangulatedMesh3               *image;
            Material                        *material; // use pointers to pre-defined materials
            QOpenGLTexture                  *texture;  // use pointers to pre-defined textures
            ShaderProgram                   *shader;   // use pointers to pre-defined shader programs

            // other attributes
            // ...

            PatchAttributes                 *neighbours[8];
            Direction                       connection_type[8];

            // ctor, copy ctor, assignment operator, dtor (they are required by the std::vector!)
        };

    protected:
        GLuint                          _minimal_patch_count_to_be_reserved;
        GLuint                          _number_of_patches;
        std::vector<PatchAttributes>    _attributes;

    public:
        // special/default ctor
        HermiteCompositeSurface3(/*GLdouble u_alpha = ..., GLdouble v_alpha = ..., GLuint minimial_patch_count_to_be_reserved = ...*/);
        ~HermiteCompositeSurface3();

        // operations
        GLboolean InsertNewPatch(BicubicHermitePatch3 patch, Material mat, QOpenGLTexture texture, ShaderProgram shader);
        GLboolean DeleteExistingPatch(GLuint index);
        GLboolean ContinueExistingPatch(GLuint index, Direction direction);
        GLboolean JoinExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1);
        GLboolean MergeExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1);

        GLboolean RenderAllPatches(GLuint order, GLenum render_mode) const;
        GLboolean RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const;

        // other setters and getters
        // ...
    };
}

#endif // HERMITECOMPOSITESURFACES3_H

