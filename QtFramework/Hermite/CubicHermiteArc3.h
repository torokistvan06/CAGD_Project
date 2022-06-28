#ifndef CUBICHERMITEARC3_H
#define CUBICHERMITEARC3_H

#include "../Core/LinearCombination3.h"
#include "../Core/Constants.h"
#include "../Core/GenericCurves3.h"

namespace cagd
{

    class CubicHermiteArc3: public LinearCombination3
    {
    private:

    public:

        // default constructor
        CubicHermiteArc3(GLenum data_usage_flag = GL_STATIC_DRAW);

        // setters for corners
        GLboolean SetCorner(GLuint corner_index, const DCoordinate3 &position);
        GLboolean SetCorner(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z);

        // setter for tangents
        GLboolean SetTangent(GLuint corner_index, const DCoordinate3 &tangent);
        GLboolean SetTangent(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z);

        // virtual functions inherited from LinearCombination3
        GLboolean BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const override;
        GLboolean CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives& d) const override;

        // function that have to be overriden from LinearCombination3
        GLboolean UpdateVertexBufferObjectsOfData(GLenum usage_flag = GL_STATIC_DRAW) override;
        GLboolean RenderData(GLenum render_mode = GL_LINE_STRIP) const override;

        // in-out operators

        friend std::ostream& operator <<(std::ostream& lhs, const CubicHermiteArc3& rhs);
        friend std::istream& operator >>(std::istream& lhs, CubicHermiteArc3& rhs);

        DCoordinate3 GetDistance();
        DCoordinate3 GetContraryDistance();

        DCoordinate3 GetCorner(int);
        DCoordinate3 GetTangent(int);


    };

}

#endif // CUBICHERMITEARC3_H
