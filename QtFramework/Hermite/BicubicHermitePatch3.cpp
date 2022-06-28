#include "BicubicHermitePatch3.h"

namespace cagd {

BicubicHermitePatch3::BicubicHermitePatch3():TensorProductSurface3(0,1,0,1,4,4)
{
}


GLboolean BicubicHermitePatch3::UBlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const{
    values.ResizeColumns(4);

    values[0] = cagd::F0(u);
    values[1] = cagd::F1(u);
    values[2] = cagd::F2(u);
    values[3] = cagd::F3(u);

    return GL_TRUE;
}


GLboolean BicubicHermitePatch3::VBlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const{
    values.ResizeColumns(4);

    values[0] = cagd::F0(u);
    values[1] = cagd::F1(u);
    values[2] = cagd::F2(u);
    values[3] = cagd::F3(u);

    return GL_TRUE;

}

GLboolean BicubicHermitePatch3::CalculatePartialDerivatives(GLuint max_order_of_derivatives, GLdouble u, GLdouble v, PartialDerivatives &d) const{

    d.ResizeRows(max_order_of_derivatives + 1);
    d.LoadNullVectors();

    RowMatrix<GLdouble> u_values_d0(4),u_values_d1(4),u_values_d2(4);
    RowMatrix<GLdouble> v_values_d0(4),v_values_d1(4),v_values_d2(4);

    u_values_d0(0)=cagd::F0(u);
    u_values_d0(1)=cagd::F1(u);
    u_values_d0(2)=cagd::F2(u);
    u_values_d0(3)=cagd::F3(u);

    u_values_d1(0)=cagd::d1F0(u);
    u_values_d1(1)=cagd::d1F1(u);
    u_values_d1(2)=cagd::d1F2(u);
    u_values_d1(3)=cagd::d1F3(u);

    u_values_d2(0)=cagd::d2F0(u);
    u_values_d2(1)=cagd::d2F1(u);
    u_values_d2(2)=cagd::d2F2(u);
    u_values_d2(3)=cagd::d2F3(u);

    v_values_d0(0)=cagd::F0(v);
    v_values_d0(1)=cagd::F1(v);
    v_values_d0(2)=cagd::F2(v);
    v_values_d0(3)=cagd::F3(v);

    v_values_d1(0)=cagd::d1F0(v);
    v_values_d1(1)=cagd::d1F1(v);
    v_values_d1(2)=cagd::d1F2(v);
    v_values_d1(3)=cagd::d1F3(v);

    v_values_d2(0)=cagd::d2F0(v);
    v_values_d2(1)=cagd::d2F1(v);
    v_values_d2(2)=cagd::d2F2(v);
    v_values_d2(3)=cagd::d2F3(v);


    for(GLuint row = 0; row < 4; ++row)
    {
        DCoordinate3 temp_d0_v, temp_d1_v, temp_d2_v;;
        for(GLuint column = 0; column < 4; ++column)
        {
            temp_d0_v += _data(row, column) * v_values_d0(column);
            temp_d1_v += _data(row, column) * v_values_d1(column);
            temp_d2_v += _data(row, column) * v_values_d2(column);
        }
        d(0, 0) += temp_d0_v * u_values_d0(row);

        d(1, 0) += temp_d0_v * u_values_d1(row);
        d(1, 1) += temp_d1_v * u_values_d0(row);

        d(2, 0) += temp_d0_v * u_values_d2(row);
        d(2, 1) += temp_d1_v * u_values_d1(row);
        d(2, 2) += temp_d2_v * u_values_d0(row);
    }

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::SetCorner(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z){
   if (corner_index==0){
         this->SetData(0,0,x,y,z);
   }else{
       if (corner_index==1){
            this->SetData(0,1,x,y,z);
       }else{
           if (corner_index==2){
                 this->SetData(1,0,x,y,z);
           }else{
                   if(corner_index==3){
                        this->SetData(1,1,x,y,z);
                   }else return GL_FALSE;

               }
           }
       }
   return GL_TRUE;

}

GLboolean BicubicHermitePatch3::SetCorner(GLuint corner_index, const DCoordinate3 &position){
    if (corner_index==0){
          this->SetData(0,0,position);
    }else{
        if (corner_index==1){
             this->SetData(0,1,position);
        }else{
            if (corner_index==2){
                  this->SetData(1,0,position);
            }else{
                    if(corner_index==3){
                         this->SetData(1,1,position);
                    }else return GL_FALSE;

                }
            }
        }
    return GL_TRUE;

}

GLboolean BicubicHermitePatch3::SetUvector(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z){
    if (corner_index==0){
          this->SetData(2,0,x,y,z);
    }else{
        if (corner_index==1){
             this->SetData(2,1,x,y,z);
        }else{
            if (corner_index==2){
                  this->SetData(3,0,x,y,z);
            }else{
                    if(corner_index==3){
                         this->SetData(3,1,x,y,z);
                    }else return GL_FALSE;

                }
            }
        }
    return GL_TRUE;

}
GLboolean BicubicHermitePatch3::SetUvector(GLuint corner_index, const DCoordinate3 &position){
    if (corner_index==0){
          this->SetData(2,0,position);
    }else{
        if (corner_index==1){
             this->SetData(2,1,position);
        }else{
            if (corner_index==2){
                  this->SetData(3,0,position);
            }else{
                    if(corner_index==3){
                         this->SetData(3,1,position);
                    }else return GL_FALSE;

                }
            }
        }
    return GL_TRUE;

}
GLboolean BicubicHermitePatch3::SetVvector(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z){
    if (corner_index==0){
          this->SetData(0,2,x,y,z);
    }else{
        if (corner_index==1){
             this->SetData(0,3,x,y,z);
        }else{
            if (corner_index==2){
                  this->SetData(1,2,x,y,z);
            }else{
                    if(corner_index==3){
                         this->SetData(1,3,x,y,z);
                    }else return GL_FALSE;

                }
            }
        }
    return GL_TRUE;

}
GLboolean BicubicHermitePatch3::SetVvector(GLuint corner_index, const DCoordinate3 &position){
    if (corner_index==0){
          this->SetData(0,2,position);
    }else{
        if (corner_index==1){
             this->SetData(0,3,position);
        }else{
            if (corner_index==2){
                  this->SetData(1,2,position);
            }else{
                    if(corner_index==3){
                         this->SetData(1,3,position);
                    }else return GL_FALSE;

                }
            }
        }
    return GL_TRUE;

}


GLboolean BicubicHermitePatch3::SetTwistVector(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z)
{
    if (corner_index==0){
        this->SetData(2,2,x,y,z);
  }else{
      if (corner_index==1){
           this->SetData(2,3,x,y,z);
      }else{
          if (corner_index==2){
                this->SetData(3,2,x,y,z);
          }else{
                  if(corner_index==3){
                       this->SetData(3,3,x,y,z);
                  }else return GL_FALSE;

              }
          }
      }
    return GL_TRUE;

}
GLboolean BicubicHermitePatch3::SetTwistVector(GLuint corner_index, const DCoordinate3 &position){
    if (corner_index==0){
          this->SetData(2,2,position);
    }else{
        if (corner_index==1){
             this->SetData(2,3,position);
        }else{
            if (corner_index==2){
                  this->SetData(3,2,position);
            }else{
                    if(corner_index==3){
                         this->SetData(3,3,position);
                    }else return GL_FALSE;

                }
            }
        }
    return GL_TRUE;

}


GLboolean BicubicHermitePatch3::UpdateVertexBufferObjectsOfData(GLenum usage_flag)
{
    GLuint data_count = _data.GetRowCount();
    if (!data_count)
        return GL_FALSE;

    if (usage_flag != GL_STREAM_DRAW  && usage_flag != GL_STREAM_READ  && usage_flag != GL_STREAM_COPY
        && usage_flag != GL_DYNAMIC_DRAW && usage_flag != GL_DYNAMIC_READ && usage_flag != GL_DYNAMIC_COPY
        && usage_flag != GL_STATIC_DRAW  && usage_flag != GL_STATIC_READ  && usage_flag != GL_STATIC_COPY)
        return GL_FALSE;

    GLenum _data_usage_flag = usage_flag;

    DeleteVertexBufferObjectsOfData();

    glGenBuffers(1, &_vbo_data);
    if (!_vbo_data)
        return GL_FALSE;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_data);
    glBufferData(GL_ARRAY_BUFFER, 84 * sizeof(GLfloat), 0, _data_usage_flag);

    GLfloat *coordinate = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (!coordinate)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        DeleteVertexBufferObjectsOfData();
        return GL_FALSE;
    }

    //insert points
    for (GLuint i = 0; i < 2; ++i)
    {
        for (GLuint j = 0; j < 2; ++j)
        {
            for (GLuint k = 0; k < 3; ++k)
            {
                *coordinate = (GLfloat)_data(i,j)[k];
                ++coordinate;
            }
        }
    }


    //insert pv
    for (GLuint i = 0; i < 2; ++i)
    {
        for (GLuint j = 0; j < 2; ++j)
        {
            for (GLuint k = 0; k < 3; ++k)
            {
                *coordinate = (GLfloat)_data(j, i)[k];
                ++coordinate;
            }
            for (GLuint k = 0; k < 3; ++k)
            {
                *coordinate = (GLfloat) (_data(i,j)[k] + _data(i,j+2)[k]);
                ++coordinate;
            }

        }
    }


    //insert pu
    for (GLuint i = 0; i < 2; ++i)
    {
        for (GLuint j = 0; j < 2; ++j)
        {
            for (GLuint k = 0; k < 3; ++k)
            {
                *coordinate = (GLfloat)_data(j, i)[k];
                ++coordinate;
            }
            for (GLuint k = 0; k < 3; ++k)
            {
                *coordinate = (GLfloat) (_data(i,j)[k] + _data(i+2,j)[k]);
                ++coordinate;
            }

        }
    }

    //insert t
    for (GLuint i = 0; i < 2; ++i)
    {
        for (GLuint j = 0; j < 2; ++j)
        {
            for (GLuint k = 0; k < 3; ++k)
            {
                *coordinate = (GLfloat)_data(j, i)[k];
                ++coordinate;
            }
            for (GLuint k = 0; k < 3; ++k)
            {
                *coordinate = (GLfloat) (_data(i,j)[k] + _data(i+2,j+2)[k]);
                ++coordinate;
            }

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

GLboolean BicubicHermitePatch3::RenderData(GLenum render) const{
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

}

std::istream& cagd::operator >>(std::istream& lhs, BicubicHermitePatch3& rhs) {
    DCoordinate3 tmp;
    for(GLuint m = 0 ; m < 4 ; m++) {
        for(GLuint n = 0 ; n < 4 ; n++) {
           lhs >> tmp;
           rhs.SetData(n,m,tmp);
        }
    }
    return lhs;
}

std::ostream& cagd::operator <<(std::ostream& lhs, const BicubicHermitePatch3& rhs) {
    DCoordinate3 tmp;
    for(GLuint m = 0 ; m < 4 ; m++) {
        for(GLuint n = 0 ; n < 4 ; n++) {
            rhs.GetData(m,n,tmp);
            lhs << tmp;
        }
    }
    return lhs;
}




