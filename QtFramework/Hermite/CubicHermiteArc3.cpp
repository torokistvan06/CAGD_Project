#include "Hermite/BasisFunctions.h"
#include "Hermite/CubicHermiteArc3.h"

#include <iostream>
using namespace std;

namespace cagd
{
    CubicHermiteArc3::CubicHermiteArc3(GLenum usage_flag) :
        LinearCombination3( 0, 1 , 4, usage_flag)
    {

    }

    // inherited pure virtual methods have to be redeclared and defined
    GLboolean CubicHermiteArc3::BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const
    {
        values.ResizeColumns(4);

        values[0] = cagd::F0(u);
        values[1] = cagd::F1(u);
        values[2] = cagd::F2(u);
        values[3] = cagd::F3(u);


        return GL_TRUE;
    }

    GLboolean CubicHermiteArc3::CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives& d) const
    {
        d.ResizeRows(max_order_of_derivatives + 1);
        d.LoadNullVectors();

        d[0] = DCoordinate3(_data[0] * cagd::F0(u) + _data[1] * cagd::F1(u) + _data[2] * cagd::F2(u) + _data[3] * cagd::F3(u));

        if (max_order_of_derivatives >= 1)
        {
            d[1] = DCoordinate3(_data[0] * cagd::d1F0(u) + _data[1] * cagd::d1F1(u) + _data[2] * cagd::d1F2(u) + _data[3] * cagd::d1F3(u));
        }

        if (max_order_of_derivatives >= 2)
        {
            d[2] = DCoordinate3(_data[0] * cagd::d2F0(u) + _data[1] * cagd::d2F1(u) + _data[2] * cagd::d2F2(u) + _data[3] * cagd::d2F3(u));
        }
        return GL_TRUE;
    }


    GLboolean CubicHermiteArc3::SetCorner(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z){
        _data[corner_index]=DCoordinate3(x,y,z);
        return true;
    }
    GLboolean CubicHermiteArc3::SetCorner(GLuint corner_index, const DCoordinate3 &position){
        _data[corner_index] = position;
        return true;
    }

    GLboolean CubicHermiteArc3::SetTangent(GLuint corner_index, GLdouble t_x, GLdouble t_y, GLdouble t_z){
        _data[corner_index+2]=DCoordinate3(t_x,t_y,t_z);
        return true;
    }
    GLboolean CubicHermiteArc3::SetTangent(GLuint corner_index, const DCoordinate3 &tangent){
         _data[corner_index+2] = tangent;
         return true;
    }

    GLboolean CubicHermiteArc3::UpdateVertexBufferObjectsOfData(GLenum usage_flag){
        GLuint data_count = 4;
        if (!data_count)
            return GL_FALSE;

        if (usage_flag != GL_STREAM_DRAW  && usage_flag != GL_STREAM_READ  && usage_flag != GL_STREAM_COPY
         && usage_flag != GL_DYNAMIC_DRAW && usage_flag != GL_DYNAMIC_READ && usage_flag != GL_DYNAMIC_COPY
         && usage_flag != GL_STATIC_DRAW  && usage_flag != GL_STATIC_READ  && usage_flag != GL_STATIC_COPY)
            return GL_FALSE;

        _data_usage_flag = usage_flag;

        DeleteVertexBufferObjectsOfData();

        glGenBuffers(1, &_vbo_data);
        if (!_vbo_data)
            return GL_FALSE;

        glBindBuffer(GL_ARRAY_BUFFER, _vbo_data);
        glBufferData(GL_ARRAY_BUFFER, (data_count + 2) * 3 * sizeof(GLfloat), 0, _data_usage_flag);

        GLfloat *coordinate = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        if (!coordinate)
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            DeleteVertexBufferObjectsOfData();
            return GL_FALSE;
        }

        for (GLuint i = 0; i < 2; ++i)
        {
            for (GLuint j = 0; j < 3; ++j)
            {
                *coordinate = (GLfloat)_data[i][j];
                ++coordinate;
            }
        }

        for (GLuint i = 2; i < 4; ++i)
        {
            for (GLuint j = 0; j < 3; ++j)
            {
                *coordinate = (GLfloat)_data[i-2][j];
                ++coordinate;
            }
            for(GLuint j =0; j < 3; ++j){
                *coordinate = (GLfloat) (_data[i][j] + _data[i-2][j]);
                ++coordinate;
            }
        }


        if (!glUnmapBuffer(GL_ARRAY_BUFFER))
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            DeleteVertexBufferObjectsOfData();
            return GL_FALSE;
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return GL_TRUE;
    }

    GLboolean CubicHermiteArc3::RenderData(GLenum render) const{
        if (!_vbo_data)
            return GL_FALSE;

        if (render != GL_LINE_STRIP && render != GL_LINE_LOOP && render!= GL_POINTS && render!=GL_LINES)
            return GL_FALSE;

        glEnableClientState(GL_VERTEX_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo_data);
                glVertexPointer(3, GL_FLOAT, 0, (const GLvoid*)0);
                glDrawArrays(GL_POINTS, 0, 2);
                glDrawArrays(GL_LINES, 2, 4);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableClientState(GL_VERTEX_ARRAY);

        return GL_TRUE;
    }

    DCoordinate3 CubicHermiteArc3::GetDistance() {
        return _data[1] - _data[0];
    }


    DCoordinate3 CubicHermiteArc3::GetContraryDistance() {
        return _data[0] - _data[1];
    }

    DCoordinate3 CubicHermiteArc3::GetCorner(int index) {
        return _data[index];
    }

    DCoordinate3 CubicHermiteArc3::GetTangent(int index) {
        return _data[index + 2];
    }
}

std::istream& cagd::operator >>(std::istream& lhs, CubicHermiteArc3& rhs) {
    DCoordinate3 tmp;
    for(GLuint m = 0 ; m < 4 ; m++) {
        lhs >> tmp;
        rhs._data[m] = tmp;
    }
    return lhs;
}

std::ostream& cagd::operator <<(std::ostream& lhs, const CubicHermiteArc3& rhs) {
    DCoordinate3 tmp;
    for(GLuint m = 0 ; m < 4 ; m++) {
        lhs << rhs._data[m];
    }
    return lhs;
}

