#ifndef BASISFUNCTIONS_H
#define BASISFUNCTIONS_H

#include <GL/glew.h>

namespace cagd
{
    // zeroth-order derivatives
    GLdouble F0(GLdouble u){
        return 2*u*u*u - 3*u*u + 1;
    }

    GLdouble F1(GLdouble u){
        return -2*u*u*u + 3*u*u;
    }

    GLdouble F2(GLdouble u){
        return u*u*u - 2*u*u + u;
    }

    GLdouble F3(GLdouble u){
        return u*u*u - u*u;
    }

    // first derivatives
    GLdouble d1F0(GLdouble u){
        return 6*(u-1) * u;
    }

    GLdouble d1F1(GLdouble u){
        return -6*(u-1) * u;
    }

    GLdouble d1F2(GLdouble u){
        return 3*u*u - 4*u*u + 1;
    }

    GLdouble d1F3(GLdouble u){
        return 3*u*u - 2*u;
    }

    // second derivatives
    GLdouble d2F0(GLdouble u){
        return 12*u -6;
    }

    GLdouble d2F1(GLdouble u){
        return 6-12*u;
    }

    GLdouble d2F2(GLdouble u){
        return 6*u - 4;
    }

    GLdouble d2F3(GLdouble u){
        return 6*u - 2;
    }
}

#endif // BASISFUNCTIONS_H
