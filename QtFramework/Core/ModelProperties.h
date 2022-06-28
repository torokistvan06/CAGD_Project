#pragma once

#include <Core/DCoordinates3.h>
#include <Core/Materials.h>
#include <iostream>

using namespace cagd;
using namespace std;

class ModelProperties
{
public:
    int          id;
    DCoordinate3 position;  // new position of the middle point of the model's bounding box
    GLdouble     angle[3];  // rotational angles
    GLdouble     scale[3];  // scaling parameters

    // other attributes, e.g., materials or material-ids
    int          materialID;

};

inline istream& operator >>(istream& lhs, ModelProperties& rhs)
{
    lhs >> rhs.id;
    lhs >> rhs.position;
    for(GLint i = 0; i < 3; i++){
        lhs >> rhs.angle[i];
    }
    for(GLint i = 0; i < 3; i++){
        lhs >> rhs.scale[i];
    }
    lhs >> rhs.materialID;
    return lhs;
}

inline ostream& operator <<(ostream& lhs, const ModelProperties& rhs)
{
    lhs << rhs.id << endl;
    lhs << rhs.position << endl;
    for(GLint i = 0; i < 3; i++){
        lhs << rhs.angle[i] << " ";
    }
    lhs << endl;
    for(GLint i = 0; i < 3; i++){
        lhs << rhs.scale[i] << " ";
    }
    lhs << endl;
    return lhs;
}
