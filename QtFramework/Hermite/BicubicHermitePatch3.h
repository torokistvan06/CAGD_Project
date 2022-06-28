#ifndef BICUBICHERMITEPATCH3_H
#define BICUBICHERMITEPATCH3_H

#include "../Core/TensorProductSurfaces3.h"
#include "./BasisFunctions.h"

namespace cagd
{
    class BicubicHermitePatch3: public TensorProductSurface3
    {
    public:
        BicubicHermitePatch3();

        GLboolean UBlendingFunctionValues(GLdouble u_knot, RowMatrix<GLdouble> &blending_values) const;
        GLboolean VBlendingFunctionValues(GLdouble u_knot, RowMatrix<GLdouble> &blending_values) const;
        GLboolean CalculatePartialDerivatives(GLuint max_order_of_derivatives, GLdouble u, GLdouble v, PartialDerivatives& partial_derivatives) const;

        GLboolean SetCorner(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z);
        GLboolean SetCorner(GLuint corner_index, const DCoordinate3 &position);


        GLboolean SetUvector(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z);
        GLboolean SetUvector(GLuint corner_index, const DCoordinate3 &position);

        GLboolean SetVvector(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z);
        GLboolean SetVvector(GLuint corner_index, const DCoordinate3 &position);


        GLboolean SetTwistVector(GLuint corner_index, GLdouble t_x, GLdouble t_y, GLdouble t_z);
        GLboolean SetTwistVector(GLuint corner_index, const DCoordinate3 &tangent);

        GLboolean UpdateHermitePatch();

        GLboolean UpdateVertexBufferObjectsOfData(GLenum usage_flag=GL_LINE_STRIP);
        GLboolean RenderData(GLenum render) const;

        // in-out operators

        friend std::ostream& operator <<(std::ostream& lhs, const BicubicHermitePatch3& rhs);
        friend std::istream& operator >>(std::istream& lhs, BicubicHermitePatch3& rhs);
    };
}

#endif // BICUBICHERMITEPATCH3_H
