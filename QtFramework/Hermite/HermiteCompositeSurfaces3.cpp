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
            if (_attributes[i]->index == index) {
                _attributes[i]->image = image;
            }
        }
        return true;
    }

    GLboolean HermiteCompositeSurface3::InsertNewPatch(BicubicHermitePatch3* patch, TriangulatedMesh3* image, Material* mat, QOpenGLTexture* texture, ShaderProgram* shader, int index) {
       PatchAttributes* element = new PatchAttributes();

       element->patch = patch;
       element->image = image;
       element->material = mat;
       element->texture = texture;
       element->shader = shader;
       element->index = index;

       for( GLuint i = 0 ; i < 8 ; i++) {
           element->neighbours[i] = nullptr;
           element->connection_type[i] = -1;
       }

       _number_of_patches += 1;
       this->_attributes.push_back(element);

       return true;
    };

    GLboolean HermiteCompositeSurface3::DeleteExistingPatch(GLuint index) {
        return false;
    };

    BicubicHermitePatch3* HermiteCompositeSurface3::ContinueExistingPatch(GLuint index, int direction) {
        //north, east, west, south

        int ind = -1;

        for(GLuint i = 0 ; i < _number_of_patches ; i++) {
            if(_attributes[i]->index == index) {
               ind = i;
            }
        }

        if(ind == -1){
            return nullptr;
        }

        if(_attributes[ind]->neighbours[direction] != nullptr){
            std::cout << "Patch " << _attributes[ind]->index << " already has a neighbour in direction: " << direction << "\n";
            return nullptr;
        }

        BicubicHermitePatch3 *patch = new BicubicHermitePatch3();

        DCoordinate3 leftUpper = getCoordinates(0, ind, 'c');
        DCoordinate3 rightUpper = getCoordinates(1, ind, 'c');
        DCoordinate3 leftLower = getCoordinates(2, ind, 'c');
        DCoordinate3 rightLower = getCoordinates(3, ind, 'c');

        DCoordinate3 leftUpperV = getCoordinates(0, ind, 'v');
        DCoordinate3 rightUpperV = getCoordinates(1, ind, 'v');
        DCoordinate3 leftLowerV = getCoordinates(2, ind, 'v');
        DCoordinate3 rightLowerV = getCoordinates(3, ind, 'v');

        DCoordinate3 leftUpperU = getCoordinates(0, ind, 'u');
        DCoordinate3 rightUpperU = getCoordinates(1, ind, 'u');
        DCoordinate3 leftLowerU = getCoordinates(2, ind, 'u');
        DCoordinate3 rightLowerU = getCoordinates(3, ind, 'u');

        DCoordinate3 leftUpperT = getCoordinates(0, ind, 't');
        DCoordinate3 rightUpperT = getCoordinates(1, ind, 't');
        DCoordinate3 leftLowerT = getCoordinates(2, ind, 't');
        DCoordinate3 rightLowerT = getCoordinates(3, ind, 't');

        //esetekre bontani hogy merre kell continue
        //megvan minden pont es vector -> distanceokat kiszamolni, uj arcok es az uj acrokbol 1 uj patch

        if(direction == 0){
            DCoordinate3 distance1 = leftUpper - leftLower;
            DCoordinate3 distance2 = rightUpper - rightLower;

            if(distance1.x() < 0) {
                distance1.x() *= -1;
            }

            if(distance1.y() < 0) {
                distance1.y() *= -1;
            }

            if(distance1.z() < 0) {
                distance1.z() *= -1;
            }

            if(distance2.x() < 0) {
                distance2.x() *= -1;
            }

            if(distance2.y() < 0) {
                distance2.y() *= -1;
            }

            if(distance2.z() < 0) {
                distance2.z() *= -1;
            }

            //corners
            patch->SetData(0, 0, leftUpper + distance1);
            patch->SetData(0, 1, rightUpper + distance2);
            patch->SetData(1, 0, leftUpper);
            patch->SetData(1, 1, rightUpper);

            //u
            patch->SetData(2, 0, leftLowerU);
            patch->SetData(2, 1, rightLowerU);
            patch->SetData(3, 0, leftUpperU);
            patch->SetData(3, 1, rightUpperU);

            //v
            patch->SetData(0, 2, leftLowerV);
            patch->SetData(0, 3, rightLowerV);
            patch->SetData(1, 2, leftUpperV);
            patch->SetData(1, 3, rightUpperV);

            //t
            patch->SetData(2, 2, leftLowerT);
            patch->SetData(2, 3, rightLowerT);
            patch->SetData(3, 2, leftUpperT);
            patch->SetData(3, 3, rightUpperT);

        } //EAST
        else if (direction == 1) {
            DCoordinate3 distance1 = rightUpper - leftUpper;
            DCoordinate3 distance2 = rightLower - leftLower;

            if(distance1.x() < 0) {
                distance1.x() *= -1;
            }

            if(distance1.y() < 0) {
                distance1.y() *= -1;
            }

            if(distance1.z() < 0) {
                distance1.z() *= -1;
            }

            if(distance2.x() < 0) {
                distance2.x() *= -1;
            }

            if(distance2.y() < 0) {
                distance2.y() *= -1;
            }

            if(distance2.z() < 0) {
                distance2.z() *= -1;
            }

            //corners
            patch->SetData(0, 0, rightUpper);
            patch->SetData(0, 1, rightUpper + distance1);
            patch->SetData(1, 0, rightLower);
            patch->SetData(1, 1, rightLower + distance2);

            //u
            patch->SetData(2, 0, rightUpperU);
            patch->SetData(2, 1, leftUpperU);
            patch->SetData(3, 0, rightLowerU);
            patch->SetData(3, 1, leftLowerU);

            //v
            patch->SetData(0, 2, rightUpperV);
            patch->SetData(0, 3, leftUpperV);
            patch->SetData(1, 2, rightLowerV);
            patch->SetData(1, 3, leftLowerV);

            //t
            patch->SetData(2, 2, rightUpperT);
            patch->SetData(2, 3, leftUpperT);
            patch->SetData(3, 2, rightLowerT);
            patch->SetData(3, 3, leftLowerT);

        }
        //WEST
        else if (direction == 2) {
            DCoordinate3 distance1 = leftUpper - rightUpper;
            DCoordinate3 distance2 = leftLower - rightLower;

            if(distance1.x() < 0) {
                distance1.x() *= -1;
            }

            if(distance1.y() < 0) {
                distance1.y() *= -1;
            }

            if(distance1.z() < 0) {
                distance1.z() *= -1;
            }

            if(distance2.x() < 0) {
                distance2.x() *= -1;
            }

            if(distance2.y() < 0) {
                distance2.y() *= -1;
            }

            if(distance2.z() < 0) {
                distance2.z() *= -1;
            }

            //corners
            patch->SetData(0, 0, leftUpper - distance1);
            patch->SetData(0, 1, leftUpper);
            patch->SetData(1, 0, leftLower - distance2);
            patch->SetData(1, 1, leftLower);

            //u
            patch->SetData(2, 0, rightUpperU);
            patch->SetData(2, 1, leftUpperU);
            patch->SetData(3, 0, rightLowerU);
            patch->SetData(3, 1, leftLowerU);

            //v
            patch->SetData(0, 2, rightUpperV);
            patch->SetData(0, 3, leftUpperV);
            patch->SetData(1, 2, rightLowerV);
            patch->SetData(1, 3, leftLowerV);

            //t
            patch->SetData(2, 2, rightUpperT);
            patch->SetData(2, 3, leftUpperT);
            patch->SetData(3, 2, rightLowerT);
            patch->SetData(3, 3, leftLowerT);
        }
        //SOUTH
        else if (direction == 3) {
            DCoordinate3 distance1 = leftUpper - leftLower;
            DCoordinate3 distance2 = rightUpper - rightLower;

            if(distance1.x() < 0) {
                distance1.x() *= -1;
            }

            if(distance1.y() < 0) {
                distance1.y() *= -1;
            }

            if(distance1.z() < 0) {
                distance1.z() *= -1;
            }

            if(distance2.x() < 0) {
                distance2.x() *= -1;
            }

            if(distance2.y() < 0) {
                distance2.y() *= -1;
            }

            if(distance2.z() < 0) {
                distance2.z() *= -1;
            }

            //corners
            patch->SetData(0, 0, leftLower);
            patch->SetData(0, 1, rightLower);
            patch->SetData(1, 0, leftLower - distance1);
            patch->SetData(1, 1, rightLower - distance2);

            //u
            patch->SetData(2, 0, leftLowerU);
            patch->SetData(2, 1, rightLowerU);
            patch->SetData(3, 0, leftUpperU);
            patch->SetData(3, 1, rightUpperU);

            //v
            patch->SetData(0, 2, leftLowerV);
            patch->SetData(0, 3, rightLowerV);
            patch->SetData(1, 2, leftUpperV);
            patch->SetData(1, 3, rightUpperV);

            //t
            patch->SetData(2, 2, leftLowerT);
            patch->SetData(2, 3, rightLowerT);
            patch->SetData(3, 2, leftUpperT);
            patch->SetData(3, 3, rightUpperT);

        }

        return patch;
    };

    BicubicHermitePatch3* HermiteCompositeSurface3::JoinExistingPatches(GLuint index_0, int direction_0, GLuint index_1, int direction_1) {
        int ind_primary = -1, ind_secondary = -1;

        if(index_0 == index_1){
            return nullptr;
        }

        for(GLuint i = 0 ; i < _number_of_patches ; i++) {
            if(_attributes[i]->index == index_0) {
               ind_primary = i;
            }

            if(_attributes[i]->index == index_1) {
               ind_secondary = i;
            }
        }

        if(ind_primary == -1 || ind_secondary == -1){
            return nullptr;
        }

        if(_attributes[ind_primary]->neighbours[direction_0] != nullptr){
            std::cout << "Patch " << _attributes[ind_primary]->index << " already has a neighbour in direction: " << direction_0 << "\n";
            return nullptr;
        }

        if(_attributes[ind_secondary]->neighbours[direction_1] != nullptr){
            std::cout << "Patch " << _attributes[ind_secondary]->index << " already has a neighbour in direction: " << direction_1 << "\n";
            return nullptr;
        }

        BicubicHermitePatch3 *patch = new BicubicHermitePatch3();

        //PRIMARY PATCH
        DCoordinate3 p0 = getCoordinates(0, ind_primary, 'c');
        DCoordinate3 p1 = getCoordinates(1, ind_primary, 'c');
        DCoordinate3 p2 = getCoordinates(2, ind_primary, 'c');
        DCoordinate3 p3 = getCoordinates(3, ind_primary, 'c');

        DCoordinate3 p0V = getCoordinates(0, ind_primary, 'v');
        DCoordinate3 p1V = getCoordinates(1, ind_primary, 'v');
        DCoordinate3 p2V = getCoordinates(2, ind_primary, 'v');
        DCoordinate3 p3V = getCoordinates(3, ind_primary, 'v');

        DCoordinate3 p0U = getCoordinates(0, ind_primary, 'u');
        DCoordinate3 p1U = getCoordinates(1, ind_primary, 'u');
        DCoordinate3 p2U = getCoordinates(2, ind_primary, 'u');
        DCoordinate3 p3U = getCoordinates(3, ind_primary, 'u');

        DCoordinate3 p0T = getCoordinates(0, ind_primary, 't');
        DCoordinate3 p1T = getCoordinates(1, ind_primary, 't');
        DCoordinate3 p2T = getCoordinates(2, ind_primary, 't');
        DCoordinate3 p3T = getCoordinates(3, ind_primary, 't');

        //SECONDARY PATCH
        DCoordinate3 r0 = getCoordinates(0, ind_secondary, 'c');
        DCoordinate3 r1 = getCoordinates(1, ind_secondary, 'c');
        DCoordinate3 r2 = getCoordinates(2, ind_secondary, 'c');
        DCoordinate3 r3 = getCoordinates(3, ind_secondary, 'c');

        DCoordinate3 r0V = getCoordinates(0, ind_secondary, 'v');
        DCoordinate3 r1V = getCoordinates(1, ind_secondary, 'v');
        DCoordinate3 r2V = getCoordinates(2, ind_secondary, 'v');
        DCoordinate3 r3V = getCoordinates(3, ind_secondary, 'v');

        DCoordinate3 r0U = getCoordinates(0, ind_secondary, 'u');
        DCoordinate3 r1U = getCoordinates(1, ind_secondary, 'u');
        DCoordinate3 r2U = getCoordinates(2, ind_secondary, 'u');
        DCoordinate3 r3U = getCoordinates(3, ind_secondary, 'u');

        DCoordinate3 r0T = getCoordinates(0, ind_secondary, 't');
        DCoordinate3 r1T = getCoordinates(1, ind_secondary, 't');
        DCoordinate3 r2T = getCoordinates(2, ind_secondary, 't');
        DCoordinate3 r3T = getCoordinates(3, ind_secondary, 't');

        //PRIMARY NORTH -> SOUTH SIDE OF NEW PATCH
        if(direction_0 == 0){
            //south side of new patch
            //corner
            patch->SetData(1, 0, p0);
            patch->SetData(1, 1, p1);

            //u
            patch->SetData(3, 0, p0U);
            patch->SetData(3, 1, p1U);

            //v
            patch->SetData(1, 2, p0V);
            patch->SetData(1, 3, p1V);

            //t
            patch->SetData(3, 2, p0T);
            patch->SetData(3, 3, p1T);

            //NORTH side of new patch
            //SECONDARY: north
            if(direction_1 == 0){
                patch->SetData(0, 0, r0);
                patch->SetData(0, 1, r1);

                //u
                patch->SetData(2, 0, r0U);
                patch->SetData(2, 1, r1U);

                //v
                patch->SetData(0, 2, r0V);
                patch->SetData(0, 3, r1V);

                //t
                patch->SetData(2, 2, r0T);
                patch->SetData(2, 3, r1T);
            }
            //east
            else if(direction_1 == 1){
                patch->SetData(0, 0, r1);
                patch->SetData(0, 1, r3);

                //u
                patch->SetData(2, 0, r1U);
                patch->SetData(2, 1, r3U);

                //v
                patch->SetData(0, 2, r1V);
                patch->SetData(0, 3, r3V);

                //t
                patch->SetData(2, 2, r1T);
                patch->SetData(2, 3, r3T);
            }
            //west
            else if(direction_1 == 2){
                patch->SetData(0, 0, r0);
                patch->SetData(0, 1, r2);

                //u
                patch->SetData(2, 0, r0U);
                patch->SetData(2, 1, r2U);

                //v
                patch->SetData(0, 2, r0V);
                patch->SetData(0, 3, r2V);

                //t
                patch->SetData(2, 2, r0T);
                patch->SetData(2, 3, r2T);
            }
            else if(direction_1 == 3){
                patch->SetData(0, 0, r2);
                patch->SetData(0, 1, r3);

                //u
                patch->SetData(2, 0, r2U);
                patch->SetData(2, 1, r3U);

                //v
                patch->SetData(0, 2, r2V);
                patch->SetData(0, 3, r3V);

                //t
                patch->SetData(2, 2, r2T);
                patch->SetData(2, 3, r3T);
            }
        }
        //PRIMARY EAST -> WEST SIDE OF NEW PATCH
        else if(direction_0 == 1){

            //WEST side of new patch
            patch->SetData(0, 0, p1);
            patch->SetData(1, 0, p3);

            //u
            patch->SetData(2, 0, p1U);
            patch->SetData(3, 0, p3U);

            //v
            patch->SetData(0, 2, p1V);
            patch->SetData(1, 2, p3V);

            //t
            patch->SetData(2, 2, p1T);
            patch->SetData(3, 2, p3T);

            //WEST side of new patch
            //SECONDARY: north
            if(direction_1 == 0){
                patch->SetData(0, 1, r0);
                patch->SetData(1, 1, r1);

                //u
                patch->SetData(2, 1, r0U);
                patch->SetData(3, 1, r1U);

                //v
                patch->SetData(0, 3, r0V);
                patch->SetData(1, 3, r1V);

                //t
                patch->SetData(2, 3, r0T);
                patch->SetData(3, 3, r1T);
            }
            //east
            else if(direction_1 == 1){
                patch->SetData(0, 1, r1);
                patch->SetData(1, 1, r3);

                //u
                patch->SetData(2, 1, r1U);
                patch->SetData(3, 1, r3U);

                //v
                patch->SetData(0, 3, r1V);
                patch->SetData(1, 3, r3V);

                //t
                patch->SetData(2, 3, r1T);
                patch->SetData(3, 3, r3T);
            }
            //west
            else if(direction_1 == 2){
                patch->SetData(0, 1, r0);
                patch->SetData(1, 1, r2);

                //u
                patch->SetData(2, 1, r0U);
                patch->SetData(3, 1, r2U);

                //v
                patch->SetData(0, 3, r0V);
                patch->SetData(1, 3, r2V);

                //t
                patch->SetData(2, 3, r0T);
                patch->SetData(3, 3, r2T);
            }
            else if(direction_1 == 3){
                patch->SetData(0, 1, r2);
                patch->SetData(1, 1, r3);

                //u
                patch->SetData(2, 1, r2U);
                patch->SetData(3, 1, r3U);

                //v
                patch->SetData(0, 3, r2V);
                patch->SetData(1, 3, r3V);

                //t
                patch->SetData(2, 3, r2T);
                patch->SetData(3, 3, r3T);
            }
        }
        //PRIMARY WEST -> EAST SIDE OF NEW PATCH
        else if(direction_0 == 2){
            //EAST SIDE side of new patch
            patch->SetData(0, 1, p0);
            patch->SetData(1, 1, p2);

            //u
            patch->SetData(2, 1, p0U);
            patch->SetData(3, 1, p2U);

            //v
            patch->SetData(0, 3, p0V);
            patch->SetData(1, 3, p2V);

            //t
            patch->SetData(2, 3, p0T);
            patch->SetData(3, 3, p2T);

            //WEST SIDE of new patch
            //SECONDARY direction: NORTH
            if(direction_1 == 0){
                patch->SetData(0, 0, r0);
                patch->SetData(1, 0, r1);

                //u
                patch->SetData(2, 0, r0U);
                patch->SetData(3, 0, r1U);

                //v
                patch->SetData(0, 2, r0V);
                patch->SetData(1, 2, r1V);

                //t
                patch->SetData(2, 2, r0T);
                patch->SetData(3, 2, r1T);
            }
            //east
            else if(direction_1 == 1){
                patch->SetData(0, 0, r1);
                patch->SetData(1, 0, r3);

                //u
                patch->SetData(2, 0, r1U);
                patch->SetData(3, 0, r3U);

                //v
                patch->SetData(0, 2, r1V);
                patch->SetData(1, 2, r3V);

                //t
                patch->SetData(2, 2, r1T);
                patch->SetData(3, 2, r3T);
            }
            //west
            else if(direction_1 == 2){
                patch->SetData(0, 0, r0);
                patch->SetData(1, 0, r2);

                //u
                patch->SetData(2, 0, r0U);
                patch->SetData(3, 0, r2U);

                //v
                patch->SetData(0, 2, r0V);
                patch->SetData(1, 2, r2V);

                //t
                patch->SetData(2, 2, r0T);
                patch->SetData(3, 2, r2T);
            }
            else if(direction_1 == 3){
                patch->SetData(0, 0, r2);
                patch->SetData(1, 0, r3);

                //u
                patch->SetData(2, 0, r2U);
                patch->SetData(3, 0, r3U);

                //v
                patch->SetData(0, 2, r2V);
                patch->SetData(1, 2, r3V);

                //t
                patch->SetData(2, 2, r2T);
                patch->SetData(3, 2, r3T);
            }
        }
        //PRIMARY SOUTH -> NORTH of new patch
        else if(direction_0 == 3){
            //NORTH side side of new patch
            patch->SetData(0, 0, p2);
            patch->SetData(0, 1, p3);

            //u
            patch->SetData(2, 0, p2U);
            patch->SetData(2, 1, p3U);

            //v
            patch->SetData(0, 2, p2V);
            patch->SetData(0, 3, p3V);

            //t
            patch->SetData(2, 2, p2T);
            patch->SetData(2, 3, p3T);

            //SOUTH SIDE of new patch
            //SECONDARY direction: NORTH
            if(direction_1 == 0){
                patch->SetData(1, 0, r0);
                patch->SetData(1, 1, r1);

                //u
                patch->SetData(3, 0, r0U);
                patch->SetData(3, 1, r1U);

                //v
                patch->SetData(1, 2, r0V);
                patch->SetData(1, 3, r1V);

                //t
                patch->SetData(3, 2, r0T);
                patch->SetData(3, 3, r1T);
            }
            //east
            else if(direction_1 == 1){
                patch->SetData(1, 0, r1);
                patch->SetData(1, 1, r3);

                //u
                patch->SetData(3, 0, r1U);
                patch->SetData(3, 1, r3U);

                //v
                patch->SetData(1, 2, r1V);
                patch->SetData(1, 3, r3V);

                //t
                patch->SetData(3, 2, r1T);
                patch->SetData(3, 3, r3T);
            }
            //west
            else if(direction_1 == 2){
                patch->SetData(1, 0, r0);
                patch->SetData(1, 1, r2);

                //u
                patch->SetData(3, 0, r0U);
                patch->SetData(3, 1, r2U);

                //v
                patch->SetData(1, 2, r0V);
                patch->SetData(1, 3, r2V);

                //t
                patch->SetData(3, 2, r0T);
                patch->SetData(3, 3, r2T);
            }
            else if(direction_1 == 3){
                patch->SetData(1, 0, r2);
                patch->SetData(1, 1, r3);

                //u
                patch->SetData(3, 0, r2U);
                patch->SetData(3, 1, r3U);

                //v
                patch->SetData(1, 2, r2V);
                patch->SetData(1, 3, r3V);

                //t
                patch->SetData(3, 2, r2T);
                patch->SetData(3, 3, r3T);
            }
        }
        return patch;
    };

    GLboolean HermiteCompositeSurface3::MergeExistingPatches(GLuint index_0, int direction_0, GLuint index_1, int direction_1) {
        int ind_primary = -1, ind_secondary = -1;

        if(index_0 == index_1){
            return false;
        }

        for(GLuint i = 0 ; i < _number_of_patches ; i++) {
            if(_attributes[i]->index == index_0) {
               ind_primary = i;
            }

            if(_attributes[i]->index == index_1) {
               ind_secondary = i;
            }
        }

        if(ind_primary == -1 || ind_secondary == -1){
            return false;
        }

        if(_attributes[ind_primary]->neighbours[direction_0] != nullptr){
            std::cout << "Patch " << _attributes[ind_primary]->index << " already has a neighbour in direction: " << direction_0 << "\n";
            return false;
        }

        if(_attributes[ind_secondary]->neighbours[direction_1] != nullptr){
            std::cout << "Patch " << _attributes[ind_secondary]->index << " already has a neighbour in direction: " << direction_1 << "\n";
            return false;
        }

        //PRIMARY PATCH
        DCoordinate3 p0 = getCoordinates(0, ind_primary, 'c');
        DCoordinate3 p1 = getCoordinates(1, ind_primary, 'c');
        DCoordinate3 p2 = getCoordinates(2, ind_primary, 'c');
        DCoordinate3 p3 = getCoordinates(3, ind_primary, 'c');

        DCoordinate3 p0V = getCoordinates(0, ind_primary, 'v');
        DCoordinate3 p1V = getCoordinates(1, ind_primary, 'v');
        DCoordinate3 p2V = getCoordinates(2, ind_primary, 'v');
        DCoordinate3 p3V = getCoordinates(3, ind_primary, 'v');

        DCoordinate3 p0U = getCoordinates(0, ind_primary, 'u');
        DCoordinate3 p1U = getCoordinates(1, ind_primary, 'u');
        DCoordinate3 p2U = getCoordinates(2, ind_primary, 'u');
        DCoordinate3 p3U = getCoordinates(3, ind_primary, 'u');

        DCoordinate3 p0T = getCoordinates(0, ind_primary, 't');
        DCoordinate3 p1T = getCoordinates(1, ind_primary, 't');
        DCoordinate3 p2T = getCoordinates(2, ind_primary, 't');
        DCoordinate3 p3T = getCoordinates(3, ind_primary, 't');

        //SECONDARY PATCH
        DCoordinate3 r0 = getCoordinates(0, ind_secondary, 'c');
        DCoordinate3 r1 = getCoordinates(1, ind_secondary, 'c');
        DCoordinate3 r2 = getCoordinates(2, ind_secondary, 'c');
        DCoordinate3 r3 = getCoordinates(3, ind_secondary, 'c');

        DCoordinate3 r0V = getCoordinates(0, ind_secondary, 'v');
        DCoordinate3 r1V = getCoordinates(1, ind_secondary, 'v');
        DCoordinate3 r2V = getCoordinates(2, ind_secondary, 'v');
        DCoordinate3 r3V = getCoordinates(3, ind_secondary, 'v');

        DCoordinate3 r0U = getCoordinates(0, ind_secondary, 'u');
        DCoordinate3 r1U = getCoordinates(1, ind_secondary, 'u');
        DCoordinate3 r2U = getCoordinates(2, ind_secondary, 'u');
        DCoordinate3 r3U = getCoordinates(3, ind_secondary, 'u');

        DCoordinate3 r0T = getCoordinates(0, ind_secondary, 't');
        DCoordinate3 r1T = getCoordinates(1, ind_secondary, 't');
        DCoordinate3 r2T = getCoordinates(2, ind_secondary, 't');
        DCoordinate3 r3T = getCoordinates(3, ind_secondary, 't');

        DCoordinate3 new_corner_0, new_corner_1, new_u_0, new_u_1, new_v_0, new_v_1, new_t_0, new_t_1;
        //primary: north
        if(direction_0 == 0){

            //secondary: north
            if(direction_1 == 0){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 0, (p0+r0)/2);
                _attributes[ind_primary]->patch->SetData(0, 1, (p1+r1)/2);

                _attributes[ind_secondary]->patch->SetData(0, 0, (p0+r0)/2);
                _attributes[ind_secondary]->patch->SetData(0, 1, (p1+r1)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 2, (p0V+r0V)/2);
                _attributes[ind_primary]->patch->SetData(0, 3, (p1V+r1V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 2, (p0V+r0V)/2);
                _attributes[ind_secondary]->patch->SetData(0, 3, (p1V+r1V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 0, (p0U+r0U)/2);
                _attributes[ind_primary]->patch->SetData(2, 1, (p1U+r1U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 0, (p0U+r0U)/2);
                _attributes[ind_secondary]->patch->SetData(2, 1, (p1U+r1U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 2, (p0T+r0T)/2);
                _attributes[ind_primary]->patch->SetData(2, 3, (p1T+r1T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 2, (p0T+r0T)/2);
                _attributes[ind_secondary]->patch->SetData(2, 3, (p1T+r1T)/2);


                new_corner_0 = p0 - (p0+r0)/2;
                new_corner_1 = p1 - (p1+r1)/2;
                new_u_0 = p0U - (p0U+r0U)/2;
                new_u_1 = p1U - (p1U+r1U)/2;
                new_v_0 = p0V - (p0V+r0V)/2;
                new_v_1 = p1V - (p1V+r1V)/2;
                new_t_0 = p0T - (p0T+r0T)/2;
                new_t_1 = p1T - (p1T+r1T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r0 - (p0+r0)/2;
                new_corner_1 = r1 - (p1+r1)/2;
                new_u_0 = r0U - (p0U+r0U)/2;
                new_u_1 = r1U - (p1U+r1U)/2;
                new_v_0 = r0V - (p0V+r0V)/2;
                new_v_1 = r1V - (p1V+r1V)/2;
                new_t_0 = r0T - (p0T+r0T)/2;
                new_t_1 = r1T - (p1T+r1T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

            }
            //secondary: east
            else if(direction_1 == 1){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 0, (p0+r1)/2);
                _attributes[ind_primary]->patch->SetData(0, 1, (p1+r3)/2);

                _attributes[ind_secondary]->patch->SetData(0, 1, (p0+r1)/2);
                _attributes[ind_secondary]->patch->SetData(1, 1, (p1+r3)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 2, (p0V+r1V)/2);
                _attributes[ind_primary]->patch->SetData(0, 3, (p1V+r3V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 3, (p0V+r1V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 3, (p1V+r3V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 0, (p0U+r1U)/2);
                _attributes[ind_primary]->patch->SetData(2, 1, (p1U+r3U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 1, (p0U+r1U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 1, (p1U+r3U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 2, (p0T+r1T)/2);
                _attributes[ind_primary]->patch->SetData(2, 3, (p1T+r3T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 3, (p0T+r1T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 3, (p1T+r3T)/2);


                new_corner_0 = p0 - (p0+r1)/2;
                new_corner_1 = p1 - (p1+r3)/2;
                new_u_0 = p0U - (p0U+r1U)/2;
                new_u_1 = p1U - (p1U+r3U)/2;
                new_v_0 = p0V - (p0V+r1V)/2;
                new_v_1 = p1V - (p1V+r3V)/2;
                new_t_0 = p0T - (p0T+r1T)/2;
                new_t_1 = p1T - (p1T+r3T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r1 - (p0+r1)/2;
                new_corner_1 = r3 - (p1+r3)/2;
                new_u_0 = r1U - (p0U+r1U)/2;
                new_u_1 = r3U - (p1U+r3U)/2;
                new_v_0 = r1V - (p0V+r1V)/2;
                new_v_1 = r3V - (p1V+r3V)/2;
                new_t_0 = r1T - (p0T+r1T)/2;
                new_t_1 = r3T - (p1T+r3T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: west
            else if(direction_1 == 2){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 0, (p0+r0)/2);
                _attributes[ind_primary]->patch->SetData(0, 1, (p1+r2)/2);

                _attributes[ind_secondary]->patch->SetData(0, 0, (p0+r0)/2);
                _attributes[ind_secondary]->patch->SetData(1, 0, (p1+r2)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 2, (p0V+r0V)/2);
                _attributes[ind_primary]->patch->SetData(0, 3, (p1V+r2V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 2, (p0V+r0V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 2, (p1V+r2V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 0, (p0U+r0U)/2);
                _attributes[ind_primary]->patch->SetData(2, 1, (p1U+r2U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 0, (p0U+r0U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 0, (p1U+r2U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 2, (p0T+r0T)/2);
                _attributes[ind_primary]->patch->SetData(2, 3, (p1T+r2T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 2, (p0T+r0T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 2, (p1T+r2T)/2);


                new_corner_0 = p0 - (p0+r0)/2;
                new_corner_1 = p1 - (p1+r2)/2;
                new_u_0 = p0U - (p0U+r0U)/2;
                new_u_1 = p1U - (p1U+r2U)/2;
                new_v_0 = p0V - (p0V+r0V)/2;
                new_v_1 = p1V - (p1V+r2V)/2;
                new_t_0 = p0T - (p0T+r0T)/2;
                new_t_1 = p1T - (p1T+r2T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r0 - (p0+r0)/2;
                new_corner_1 = r2 - (p1+r2)/2;
                new_u_0 = r0U - (p0U+r0U)/2;
                new_u_1 = r2U - (p1U+r2U)/2;
                new_v_0 = r0V - (p0V+r0V)/2;
                new_v_1 = r2V - (p1V+r2V)/2;
                new_t_0 = r0T - (p0T+r0T)/2;
                new_t_1 = r2T - (p1T+r2T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 2, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: south
            else if(direction_1 == 3){

                //corners
                _attributes[ind_primary]->patch->SetData(0, 0, (p0+r2)/2);
                _attributes[ind_primary]->patch->SetData(0, 1, (p1+r3)/2);

                _attributes[ind_secondary]->patch->SetData(1, 0, (p0+r2)/2);
                _attributes[ind_secondary]->patch->SetData(1, 1, (p1+r3)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 2, (p0V+r2V)/2);
                _attributes[ind_primary]->patch->SetData(0, 3, (p1V+r3V)/2);

                _attributes[ind_secondary]->patch->SetData(1, 2, (p0V+r2V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 3, (p1V+r3V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 0, (p0U+r2U)/2);
                _attributes[ind_primary]->patch->SetData(2, 1, (p1U+r3U)/2);

                _attributes[ind_secondary]->patch->SetData(3, 0, (p0U+r2U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 1, (p1U+r3U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 2, (p0T+r2T)/2);
                _attributes[ind_primary]->patch->SetData(2, 3, (p1T+r3T)/2);

                _attributes[ind_secondary]->patch->SetData(3, 2, (p0T+r2T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 3, (p1T+r3T)/2);


                new_corner_0 = p0 - (p0+r2)/2;
                new_corner_1 = p1 - (p1+r3)/2;
                new_u_0 = p0U - (p0U+r2U)/2;
                new_u_1 = p1U - (p1U+r3U)/2;
                new_v_0 = p0V - (p0V+r2V)/2;
                new_v_1 = p1V - (p1V+r3V)/2;
                new_t_0 = p0T - (p0T+r2T)/2;
                new_t_1 = p1T - (p1T+r3T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r2 - (p0+r2)/2;
                new_corner_1 = r3 - (p1+r3)/2;
                new_u_0 = r2U - (p0U+r2U)/2;
                new_u_1 = r3U - (p1U+r3U)/2;
                new_v_0 = r2V - (p0V+r2V)/2;
                new_v_1 = r3V - (p1V+r3V)/2;
                new_t_0 = r2T - (p0T+r2T)/2;
                new_t_1 = r3T - (p1T+r3T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 2, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
        }
        //primary: east
        if(direction_0 == 1){

            //secondary: north
            if(direction_1 == 0){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 1, (p1+r0)/2);
                _attributes[ind_primary]->patch->SetData(1, 1, (p3+r1)/2);

                _attributes[ind_secondary]->patch->SetData(0, 0, (p1+r0)/2);
                _attributes[ind_secondary]->patch->SetData(0, 1, (p3+r1)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 3, (p1V+r0V)/2);
                _attributes[ind_primary]->patch->SetData(1, 3, (p3V+r1V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 2, (p1V+r0V)/2);
                _attributes[ind_secondary]->patch->SetData(0, 3, (p3V+r1V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 1, (p1U+r0U)/2);
                _attributes[ind_primary]->patch->SetData(3, 1, (p3U+r1U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 0, (p1U+r0U)/2);
                _attributes[ind_secondary]->patch->SetData(2, 1, (p3U+r1U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 3, (p1T+r0T)/2);
                _attributes[ind_primary]->patch->SetData(3, 3, (p3T+r1T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 2, (p1T+r0T)/2);
                _attributes[ind_secondary]->patch->SetData(2, 3, (p3T+r1T)/2);

                new_corner_0 = p1 - (p1+r0)/2;
                new_corner_1 = p3 - (p3+r1)/2;
                new_u_0 = p1U - (p1U+r0U)/2;
                new_u_1 = p3U - (p3U+r1U)/2;
                new_v_0 = p1V - (p1V+r0V)/2;
                new_v_1 = p3V - (p3V+r1V)/2;
                new_t_0 = p1T - (p1T+r0T)/2;
                new_t_1 = p3T - (p3T+r1T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 1, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r0 - (p1+r0)/2;
                new_corner_1 = r1 - (p3+r1)/2;
                new_u_0 = r0U - (p1U+r0U)/2;
                new_u_1 = r1U - (p3U+r1U)/2;
                new_v_0 = r0V - (p1V+r0V)/2;
                new_v_1 = r1V - (p3V+r1V)/2;
                new_t_0 = r0T - (p1T+r0T)/2;
                new_t_1 = r1T - (p3T+r1T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: east
            else if(direction_1 == 1){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 1, (p1+r1)/2);
                _attributes[ind_primary]->patch->SetData(1, 1, (p3+r3)/2);

                _attributes[ind_secondary]->patch->SetData(0, 1, (p1+r1)/2);
                _attributes[ind_secondary]->patch->SetData(1, 1, (p3+r3)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 3, (p1V+r1V)/2);
                _attributes[ind_primary]->patch->SetData(1, 3, (p3V+r3V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 3, (p1V+r1V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 3, (p3V+r3V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 1, (p1U+r1U)/2);
                _attributes[ind_primary]->patch->SetData(3, 1, (p3U+r3U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 1, (p1U+r1U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 1, (p3U+r3U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 3, (p1T+r1T)/2);
                _attributes[ind_primary]->patch->SetData(3, 3, (p3T+r3T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 3, (p1T+r1T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 3, (p3T+r3T)/2);

                new_corner_0 = p1 - (p1+r1)/2;
                new_corner_1 = p3 - (p3+r3)/2;
                new_u_0 = p1U - (p1U+r1U)/2;
                new_u_1 = p3U - (p3U+r3U)/2;
                new_v_0 = p1V - (p1V+r1V)/2;
                new_v_1 = p3V - (p3V+r3V)/2;
                new_t_0 = p1T - (p1T+r1T)/2;
                new_t_1 = p3T - (p3T+r3T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 1, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r1 - (p1+r1)/2;
                new_corner_1 = r3 - (p3+r3)/2;
                new_u_0 = r1U - (p1U+r1U)/2;
                new_u_1 = r3U - (p3U+r3U)/2;
                new_v_0 = r1V - (p1V+r1V)/2;
                new_v_1 = r3V - (p3V+r3V)/2;
                new_t_0 = r1T - (p1T+r1T)/2;
                new_t_1 = r3T - (p3T+r3T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: west
            else if(direction_1 == 2){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 1, (p1+r0)/2);
                _attributes[ind_primary]->patch->SetData(1, 1, (p3+r2)/2);

                _attributes[ind_secondary]->patch->SetData(0, 0, (p1+r0)/2);
                _attributes[ind_secondary]->patch->SetData(1, 0, (p3+r2)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 3, (p1V+r0V)/2);
                _attributes[ind_primary]->patch->SetData(1, 3, (p3V+r2V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 2, (p1V+r0V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 2, (p3V+r2V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 1, (p1U+r0U)/2);
                _attributes[ind_primary]->patch->SetData(3, 1, (p3U+r2U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 0, (p1U+r0U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 0, (p3U+r2U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 3, (p1T+r0T)/2);
                _attributes[ind_primary]->patch->SetData(3, 3, (p3T+r2T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 2, (p1T+r0T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 2, (p3T+r2T)/2);

                new_corner_0 = p1 - (p1+r0)/2;
                new_corner_1 = p3 - (p3+r2)/2;
                new_u_0 = p1U - (p1U+r0U)/2;
                new_u_1 = p3U - (p3U+r2U)/2;
                new_v_0 = p1V - (p1V+r0V)/2;
                new_v_1 = p3V - (p3V+r2V)/2;
                new_t_0 = p1T - (p1T+r0T)/2;
                new_t_1 = p3T - (p3T+r2T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 1, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r0 - (p1+r0)/2;
                new_corner_1 = r2 - (p3+r2)/2;
                new_u_0 = r0U - (p1U+r0U)/2;
                new_u_1 = r2U - (p3U+r2U)/2;
                new_v_0 = r0V - (p1V+r0V)/2;
                new_v_1 = r2V - (p3V+r2V)/2;
                new_t_0 = r0T - (p1T+r0T)/2;
                new_t_1 = r2T - (p3T+r2T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 2, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: south
            else if(direction_1 == 3){

                //corners
                _attributes[ind_primary]->patch->SetData(0, 1, (p1+r2)/2);
                _attributes[ind_primary]->patch->SetData(1, 1, (p3+r3)/2);

                _attributes[ind_secondary]->patch->SetData(1, 0, (p1+r2)/2);
                _attributes[ind_secondary]->patch->SetData(1, 1, (p3+r3)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 3, (p1V+r2V)/2);
                _attributes[ind_primary]->patch->SetData(1, 3, (p3V+r3V)/2);

                _attributes[ind_secondary]->patch->SetData(1, 2, (p1V+r2V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 3, (p3V+r3V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 1, (p1U+r2U)/2);
                _attributes[ind_primary]->patch->SetData(3, 1, (p3U+r3U)/2);

                _attributes[ind_secondary]->patch->SetData(3, 0, (p1U+r2U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 1, (p3U+r3U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 3, (p1T+r2T)/2);
                _attributes[ind_primary]->patch->SetData(3, 3, (p3T+r3T)/2);

                _attributes[ind_secondary]->patch->SetData(3, 2, (p1T+r2T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 3, (p3T+r3T)/2);

                new_corner_0 = p1 - (p1+r2)/2;
                new_corner_1 = p3 - (p3+r3)/2;
                new_u_0 = p1U - (p1U+r2U)/2;
                new_u_1 = p3U - (p3U+r3U)/2;
                new_v_0 = p1V - (p1V+r2V)/2;
                new_v_1 = p3V - (p3V+r3V)/2;
                new_t_0 = p1T - (p1T+r2T)/2;
                new_t_1 = p3T - (p3T+r3T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 1, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r2 - (p1+r2)/2;
                new_corner_1 = r3 - (p3+r3)/2;
                new_u_0 = r2U - (p1U+r2U)/2;
                new_u_1 = r3U - (p3U+r3U)/2;
                new_v_0 = r2V - (p1V+r2V)/2;
                new_v_1 = r3V - (p3V+r3V)/2;
                new_t_0 = r2T - (p1T+r2T)/2;
                new_t_1 = r3T - (p3T+r3T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 2, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
        }
        //primary: west
        if(direction_0 == 2){

            //secondary: north
            if(direction_1 == 0){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 0, (p0+r0)/2);
                _attributes[ind_primary]->patch->SetData(1, 0, (p2+r1)/2);

                _attributes[ind_secondary]->patch->SetData(0, 0, (p0+r0)/2);
                _attributes[ind_secondary]->patch->SetData(0, 1, (p2+r1)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 2, (p0V+r0V)/2);
                _attributes[ind_primary]->patch->SetData(1, 2, (p2V+r1V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 2, (p0V+r0V)/2);
                _attributes[ind_secondary]->patch->SetData(0, 3, (p2V+r1V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 0, (p0U+r0U)/2);
                _attributes[ind_primary]->patch->SetData(3, 0, (p2U+r1U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 0, (p0U+r0U)/2);
                _attributes[ind_secondary]->patch->SetData(2, 1, (p2U+r1U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 2, (p0T+r0T)/2);
                _attributes[ind_primary]->patch->SetData(3, 2, (p2T+r1T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 2, (p0T+r0T)/2);
                _attributes[ind_secondary]->patch->SetData(2, 3, (p2T+r1T)/2);

                new_corner_0 = p0 - (p0+r0)/2;
                new_corner_1 = p2 - (p2+r1)/2;
                new_u_0 = p0U - (p0U+r0U)/2;
                new_u_1 = p2U - (p2U+r1U)/2;
                new_v_0 = p0V - (p0V+r0V)/2;
                new_v_1 = p2V - (p2V+r1V)/2;
                new_t_0 = p0T - (p0T+r0T)/2;
                new_t_1 = p2T - (p2T+r1T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 2, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r0 - (p0+r0)/2;
                new_corner_1 = r1 - (p2+r1)/2;
                new_u_0 = r0U - (p0U+r0U)/2;
                new_u_1 = r1U - (p2U+r1U)/2;
                new_v_0 = r0V - (p0V+r0V)/2;
                new_v_1 = r1V - (p2V+r1V)/2;
                new_t_0 = r0T - (p0T+r0T)/2;
                new_t_1 = r1T - (p2T+r1T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

            }
            //secondary: east
            else if(direction_1 == 1){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 0, (p0+r1)/2);
                _attributes[ind_primary]->patch->SetData(1, 0, (p2+r3)/2);

                _attributes[ind_secondary]->patch->SetData(0, 1, (p0+r1)/2);
                _attributes[ind_secondary]->patch->SetData(1, 1, (p2+r3)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 2, (p0V+r1V)/2);
                _attributes[ind_primary]->patch->SetData(1, 2, (p2V+r3V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 3, (p0V+r1V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 3, (p2V+r3V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 0, (p0U+r1U)/2);
                _attributes[ind_primary]->patch->SetData(3, 0, (p2U+r3U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 1, (p0U+r1U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 1, (p2U+r3U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 2, (p0T+r1T)/2);
                _attributes[ind_primary]->patch->SetData(3, 2, (p2T+r3T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 3, (p0T+r1T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 3, (p2T+r3T)/2);

                new_corner_0 = p0 - (p0+r1)/2;
                new_corner_1 = p2 - (p2+r3)/2;
                new_u_0 = p0U - (p0U+r1U)/2;
                new_u_1 = p2U - (p2U+r3U)/2;
                new_v_0 = p0V - (p0V+r1V)/2;
                new_v_1 = p2V - (p2V+r3V)/2;
                new_t_0 = p0T - (p0T+r1T)/2;
                new_t_1 = p2T - (p2T+r3T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 2, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r1 - (p0+r1)/2;
                new_corner_1 = r3 - (p2+r3)/2;
                new_u_0 = r1U - (p0U+r1U)/2;
                new_u_1 = r3U - (p2U+r3U)/2;
                new_v_0 = r1V - (p0V+r1V)/2;
                new_v_1 = r3V - (p2V+r3V)/2;
                new_t_0 = r1T - (p0T+r1T)/2;
                new_t_1 = r3T - (p2T+r3T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: west
            else if(direction_1 == 2){
                //corners
                _attributes[ind_primary]->patch->SetData(0, 0, (p0+r0)/2);
                _attributes[ind_primary]->patch->SetData(1, 0, (p2+r2)/2);

                _attributes[ind_secondary]->patch->SetData(0, 0, (p0+r0)/2);
                _attributes[ind_secondary]->patch->SetData(1, 0, (p2+r2)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 2, (p0V+r0V)/2);
                _attributes[ind_primary]->patch->SetData(1, 2, (p2V+r2V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 2, (p0V+r0V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 2, (p2V+r2V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 0, (p0U+r0U)/2);
                _attributes[ind_primary]->patch->SetData(3, 0, (p2U+r2U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 0, (p0U+r0U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 0, (p2U+r2U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 2, (p0T+r0T)/2);
                _attributes[ind_primary]->patch->SetData(3, 2, (p2T+r2T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 2, (p0T+r0T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 2, (p2T+r2T)/2);

                new_corner_0 = p0 - (p0+r0)/2;
                new_corner_1 = p2 - (p2+r2)/2;
                new_u_0 = p0U - (p0U+r0U)/2;
                new_u_1 = p2U - (p2U+r2U)/2;
                new_v_0 = p0V - (p0V+r0V)/2;
                new_v_1 = p2V - (p2V+r2V)/2;
                new_t_0 = p0T - (p0T+r0T)/2;
                new_t_1 = p2T - (p2T+r2T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 2, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r0 - (p0+r0)/2;
                new_corner_1 = r2 - (p2+r2)/2;
                new_u_0 = r0U - (p0U+r0U)/2;
                new_u_1 = r2U - (p2U+r2U)/2;
                new_v_0 = r0V - (p0V+r0V)/2;
                new_v_1 = r2V - (p2V+r2V)/2;
                new_t_0 = r0T - (p0T+r0T)/2;
                new_t_1 = r2T - (p2T+r2T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 2, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: south
            else if(direction_1 == 3){

                //corners
                _attributes[ind_primary]->patch->SetData(0, 0, (p0+r2)/2);
                _attributes[ind_primary]->patch->SetData(1, 0, (p2+r3)/2);

                _attributes[ind_secondary]->patch->SetData(1, 0, (p0+r2)/2);
                _attributes[ind_secondary]->patch->SetData(1, 1, (p2+r3)/2);

                //v
                _attributes[ind_primary]->patch->SetData(0, 2, (p0V+r2V)/2);
                _attributes[ind_primary]->patch->SetData(1, 2, (p2V+r3V)/2);

                _attributes[ind_secondary]->patch->SetData(1, 2, (p0V+r2V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 3, (p2V+r3V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(2, 0, (p0U+r2U)/2);
                _attributes[ind_primary]->patch->SetData(3, 0, (p2U+r3U)/2);

                _attributes[ind_secondary]->patch->SetData(3, 0, (p0U+r2U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 1, (p2U+r3U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(2, 2, (p0T+r2T)/2);
                _attributes[ind_primary]->patch->SetData(3, 2, (p2T+r3T)/2);

                _attributes[ind_secondary]->patch->SetData(3, 2, (p0T+r2T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 3, (p2T+r3T)/2);

                new_corner_0 = p0 - (p0+r2)/2;
                new_corner_1 = p2 - (p2+r3)/2;
                new_u_0 = p0U - (p0U+r2U)/2;
                new_u_1 = p2U - (p2U+r3U)/2;
                new_v_0 = p0V - (p0V+r2V)/2;
                new_v_1 = p2V - (p2V+r3V)/2;
                new_t_0 = p0T - (p0T+r2T)/2;
                new_t_1 = p2T - (p2T+r3T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 2, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r2 - (p0+r2)/2;
                new_corner_1 = r3 - (p2+r3)/2;
                new_u_0 = r2U - (p0U+r2U)/2;
                new_u_1 = r3U - (p2U+r3U)/2;
                new_v_0 = r2V - (p0V+r2V)/2;
                new_v_1 = r3V - (p2V+r3V)/2;
                new_t_0 = r2T - (p0T+r2T)/2;
                new_t_1 = r3T - (p2T+r3T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
        }
        //primary: south
        if(direction_0 == 3){

            //secondary: north
            if(direction_1 == 0){
                //corners
                _attributes[ind_primary]->patch->SetData(1, 0, (p2+r0)/2);
                _attributes[ind_primary]->patch->SetData(1, 1, (p3+r1)/2);

                _attributes[ind_secondary]->patch->SetData(0, 0, (p2+r0)/2);
                _attributes[ind_secondary]->patch->SetData(0, 1, (p3+r1)/2);

                //v
                _attributes[ind_primary]->patch->SetData(1, 2, (p2V+r0V)/2);
                _attributes[ind_primary]->patch->SetData(1, 3, (p3V+r1V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 2, (p2V+r0V)/2);
                _attributes[ind_secondary]->patch->SetData(0, 3, (p3V+r1V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(3, 0, (p2U+r0U)/2);
                _attributes[ind_primary]->patch->SetData(3, 1, (p3U+r1U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 0, (p2U+r0U)/2);
                _attributes[ind_secondary]->patch->SetData(2, 1, (p3U+r1U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(3, 2, (p2T+r0T)/2);
                _attributes[ind_primary]->patch->SetData(3, 3, (p3T+r1T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 2, (p2T+r0T)/2);
                _attributes[ind_secondary]->patch->SetData(2, 3, (p3T+r1T)/2);

                new_corner_0 = p2 - (p2+r0)/2;
                new_corner_1 = p3 - (p3+r1)/2;
                new_u_0 = p2U - (p2U+r0U)/2;
                new_u_1 = p3U - (p3U+r1U)/2;
                new_v_0 = p2V - (p2V+r0V)/2;
                new_v_1 = p3V - (p3V+r1V)/2;
                new_t_0 = p2T - (p2T+r0T)/2;
                new_t_1 = p3T - (p3T+r1T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 2, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r0 - (p2+r0)/2;
                new_corner_1 = r1 - (p3+r1)/2;
                new_u_0 = r0U - (p2U+r0U)/2;
                new_u_1 = r1U - (p3U+r1U)/2;
                new_v_0 = r0V - (p2V+r0V)/2;
                new_v_1 = r1V - (p3V+r1V)/2;
                new_t_0 = r0T - (p2T+r0T)/2;
                new_t_1 = r1T - (p3T+r1T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: east
            else if(direction_1 == 1){
                //corners
                _attributes[ind_primary]->patch->SetData(1, 0, (p2+r1)/2);
                _attributes[ind_primary]->patch->SetData(1, 1, (p3+r3)/2);

                _attributes[ind_secondary]->patch->SetData(0, 1, (p2+r1)/2);
                _attributes[ind_secondary]->patch->SetData(1, 1, (p3+r3)/2);

                //v
                _attributes[ind_primary]->patch->SetData(1, 2, (p2V+r1V)/2);
                _attributes[ind_primary]->patch->SetData(1, 3, (p3V+r3V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 3, (p2V+r1V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 3, (p3V+r3V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(3, 0, (p2U+r1U)/2);
                _attributes[ind_primary]->patch->SetData(3, 1, (p3U+r3U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 1, (p2U+r1U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 1, (p3U+r3U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(3, 2, (p2T+r1T)/2);
                _attributes[ind_primary]->patch->SetData(3, 3, (p3T+r3T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 3, (p2T+r1T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 3, (p3T+r3T)/2);

                new_corner_0 = p2 - (p2+r1)/2;
                new_corner_1 = p3 - (p3+r3)/2;
                new_u_0 = p2U - (p2U+r1U)/2;
                new_u_1 = p3U - (p3U+r3U)/2;
                new_v_0 = p2V - (p2V+r1V)/2;
                new_v_1 = p3V - (p3V+r3V)/2;
                new_t_0 = p2T - (p2T+r1T)/2;
                new_t_1 = p3T - (p3T+r3T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 2, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r1 - (p2+r1)/2;
                new_corner_1 = r3 - (p3+r3)/2;
                new_u_0 = r1U - (p2U+r1U)/2;
                new_u_1 = r3U - (p3U+r3U)/2;
                new_v_0 = r1V - (p2V+r1V)/2;
                new_v_1 = r3V - (p3V+r3V)/2;
                new_t_0 = r1T - (p2T+r1T)/2;
                new_t_1 = r3T - (p3T+r3T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 1, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: west
            else if(direction_1 == 2){
                //corners
                _attributes[ind_primary]->patch->SetData(1, 0, (p2+r0)/2);
                _attributes[ind_primary]->patch->SetData(1, 1, (p3+r2)/2);

                _attributes[ind_secondary]->patch->SetData(0, 0, (p2+r0)/2);
                _attributes[ind_secondary]->patch->SetData(1, 0, (p3+r2)/2);

                //v
                _attributes[ind_primary]->patch->SetData(1, 2, (p2V+r0V)/2);
                _attributes[ind_primary]->patch->SetData(1, 3, (p3V+r2V)/2);

                _attributes[ind_secondary]->patch->SetData(0, 2, (p2V+r0V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 2, (p3V+r2V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(3, 0, (p2U+r0U)/2);
                _attributes[ind_primary]->patch->SetData(3, 1, (p3U+r2U)/2);

                _attributes[ind_secondary]->patch->SetData(2, 0, (p2U+r0U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 0, (p3U+r2U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(3, 2, (p2T+r0T)/2);
                _attributes[ind_primary]->patch->SetData(3, 3, (p3T+r2T)/2);

                _attributes[ind_secondary]->patch->SetData(2, 2, (p2T+r0T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 2, (p3T+r2T)/2);

                new_corner_0 = p2 - (p2+r0)/2;
                new_corner_1 = p3 - (p3+r2)/2;
                new_u_0 = p2U - (p2U+r0U)/2;
                new_u_1 = p3U - (p3U+r2U)/2;
                new_v_0 = p2V - (p2V+r0V)/2;
                new_v_1 = p3V - (p3V+r2V)/2;
                new_t_0 = p2T - (p2T+r0T)/2;
                new_t_1 = p3T - (p3T+r2T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 2, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r0 - (p2+r0)/2;
                new_corner_1 = r2 - (p3+r2)/2;
                new_u_0 = r0U - (p2U+r0U)/2;
                new_u_1 = r2U - (p3U+r2U)/2;
                new_v_0 = r0V - (p2V+r0V)/2;
                new_v_1 = r2V - (p3V+r2V)/2;
                new_t_0 = r0T - (p2T+r0T)/2;
                new_t_1 = r2T - (p3T+r2T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 0, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 2, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
            //secondary: south
            else if(direction_1 == 3){

                //corners
                _attributes[ind_primary]->patch->SetData(1, 0, (p2+r2)/2);
                _attributes[ind_primary]->patch->SetData(1, 1, (p3+r3)/2);

                _attributes[ind_secondary]->patch->SetData(1, 0, (p2+r2)/2);
                _attributes[ind_secondary]->patch->SetData(1, 1, (p3+r3)/2);

                //v
                _attributes[ind_primary]->patch->SetData(1, 2, (p2V+r2V)/2);
                _attributes[ind_primary]->patch->SetData(1, 3, (p3V+r3V)/2);

                _attributes[ind_secondary]->patch->SetData(1, 2, (p2V+r2V)/2);
                _attributes[ind_secondary]->patch->SetData(1, 3, (p3V+r3V)/2);

                //u
                _attributes[ind_primary]->patch->SetData(3, 0, (p2U+r2U)/2);
                _attributes[ind_primary]->patch->SetData(3, 1, (p3U+r3U)/2);

                _attributes[ind_secondary]->patch->SetData(3, 0, (p2U+r2U)/2);
                _attributes[ind_secondary]->patch->SetData(3, 1, (p3U+r3U)/2);

                //t
                _attributes[ind_primary]->patch->SetData(3, 2, (p2T+r2T)/2);
                _attributes[ind_primary]->patch->SetData(3, 3, (p3T+r3T)/2);

                _attributes[ind_secondary]->patch->SetData(3, 2, (p2T+r2T)/2);
                _attributes[ind_secondary]->patch->SetData(3, 3, (p3T+r3T)/2);

                new_corner_0 = p2 - (p2+r2)/2;
                new_corner_1 = p3 - (p3+r3)/2;
                new_u_0 = p2U - (p2U+r2U)/2;
                new_u_1 = p3U - (p3U+r3U)/2;
                new_v_0 = p2V - (p2V+r2V)/2;
                new_v_1 = p3V - (p3V+r3V)/2;
                new_t_0 = p2T - (p2T+r2T)/2;
                new_t_1 = p3T - (p3T+r3T)/2;

                this->updateNeighbours(_attributes[ind_primary]->index, 2, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_primary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);

                new_corner_0 = r2 - (p2+r2)/2;
                new_corner_1 = r3 - (p3+r3)/2;
                new_u_0 = r2U - (p2U+r2U)/2;
                new_u_1 = r3U - (p3U+r3U)/2;
                new_v_0 = r2V - (p2V+r2V)/2;
                new_v_1 = r3V - (p3V+r3V)/2;
                new_t_0 = r2T - (p2T+r2T)/2;
                new_t_1 = r3T - (p3T+r3T)/2;

                this->updateNeighbours(_attributes[ind_secondary]->index, 2, -new_corner_0, -new_u_0, -new_v_0, -new_t_0);
                this->updateNeighbours(_attributes[ind_secondary]->index, 3, -new_corner_1, -new_u_1, -new_v_1, -new_t_1);
            }
        }

        return true;
    };

    GLboolean HermiteCompositeSurface3::RenderAllPatches() const {
        for(GLuint i = 0 ; i < _number_of_patches ; i++) {

            _attributes[i]->material->Apply();
            _attributes[i]->texture->bind();
            _attributes[i]->shader->Enable();
            _attributes[i]->image->Render();
            _attributes[i]->shader->Disable();
            _attributes[i]->texture->release();
        }

        return true;
    };

    GLvoid HermiteCompositeSurface3::updateNeighbours(GLint index, GLint pointIndex, DCoordinate3 corner, DCoordinate3 partial_u, DCoordinate3 partial_v, DCoordinate3 twist_vector) {
        for(GLint i = 0 ; i < _number_of_patches ; i++) {
            if(_attributes[i]->index == index) {
                updateNeighboursRecursive(_attributes[i], pointIndex, corner, partial_u, partial_v, twist_vector, nullptr);
                break;
            }
        }
    }

    GLvoid HermiteCompositeSurface3::updateNeighboursRecursive(PatchAttributes* patch, GLint pointIndex, DCoordinate3 corner, DCoordinate3 partial_u, DCoordinate3 partial_v, DCoordinate3 twist_vector, PatchAttributes* parent) {

        for(GLuint i = 0 ; i < 8 ; i++) {
            if(patch->neighbours[i] == nullptr || patch->neighbours[i] == parent) {
                continue;
            }

            PatchAttributes* neighbour = patch->neighbours[i];
            DCoordinate3 new_data;
            if(i == 0 && pointIndex == 0) { // NORTH - LEFT-UPPER CORNER
                if(patch->connection_type[i] == 0) {
                    neighbour->patch->GetData(0,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,0, new_data);

                    neighbour->patch->GetData(2,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,0, new_data);

                    neighbour->patch->GetData(0,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,2, new_data);

                    neighbour->patch->GetData(2,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 0, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 1) {
                    neighbour->patch->GetData(0,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,0, new_data);

                    neighbour->patch->GetData(2,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,0, new_data);

                    neighbour->patch->GetData(0,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,2, new_data);

                    neighbour->patch->GetData(2,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 0, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 2) {
                    neighbour->patch->GetData(0,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,1, new_data);

                    neighbour->patch->GetData(2,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,1, new_data);

                    neighbour->patch->GetData(0,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,3, new_data);

                    neighbour->patch->GetData(2,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 1, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 3) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 2, corner, partial_u, partial_v, twist_vector, patch);
                }

            } else if(i == 0 && pointIndex == 1) { // NORTH - RIGHT UPPER CORNER

                if(patch->connection_type[i] == 0) {
                    neighbour->patch->GetData(0,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,1, new_data);

                    neighbour->patch->GetData(2,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,1, new_data);

                    neighbour->patch->GetData(0,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,3, new_data);

                    neighbour->patch->GetData(2,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 1, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 1) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 2, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 2) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 2, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 3) {
                    neighbour->patch->GetData(1,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,1, new_data);

                    neighbour->patch->GetData(3,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,1, new_data);

                    neighbour->patch->GetData(1,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,3, new_data);

                    neighbour->patch->GetData(3,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 3, corner, partial_u, partial_v, twist_vector, patch);
                }
            } else if(i == 1 && pointIndex == 1) { // EAST - RIGHT-UPPER CORNER
                if(patch->connection_type[i] == 0) {
                    neighbour->patch->GetData(0,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,0, new_data);

                    neighbour->patch->GetData(2,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,0, new_data);

                    neighbour->patch->GetData(0,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,2, new_data);

                    neighbour->patch->GetData(2,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 1, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 1) {
                    neighbour->patch->GetData(0,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,1, new_data);

                    neighbour->patch->GetData(2,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,1, new_data);

                    neighbour->patch->GetData(0,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,3, new_data);

                    neighbour->patch->GetData(2,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 1, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 2) {
                    neighbour->patch->GetData(0,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,0, new_data);

                    neighbour->patch->GetData(2,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,0, new_data);

                    neighbour->patch->GetData(0,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,2, new_data);

                    neighbour->patch->GetData(2,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 0, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 3) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 2, corner, partial_u, partial_v, twist_vector, patch);
                }

            } else if(i == 1 && pointIndex == 3) { // EAST - RIGHT LOWER CORNER

                if(patch->connection_type[i] == 0) {
                    neighbour->patch->GetData(0,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,1, new_data);

                    neighbour->patch->GetData(2,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,1, new_data);

                    neighbour->patch->GetData(0,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,3, new_data);

                    neighbour->patch->GetData(2,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 0, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 1) {
                    neighbour->patch->GetData(1,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,1, new_data);

                    neighbour->patch->GetData(3,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,1, new_data);

                    neighbour->patch->GetData(1,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,3, new_data);

                    neighbour->patch->GetData(3,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 3, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 2) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 2, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 3) {
                    neighbour->patch->GetData(1,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,1, new_data);

                    neighbour->patch->GetData(3,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,1, new_data);

                    neighbour->patch->GetData(1,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,3, new_data);

                    neighbour->patch->GetData(3,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 3, corner, partial_u, partial_v, twist_vector, patch);
                }
            } else if(i == 2 && pointIndex == 0) { // WEST - LEFT-UPPER CORNER
                if(patch->connection_type[i] == 0) {
                    neighbour->patch->GetData(0,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,0, new_data);

                    neighbour->patch->GetData(2,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,0, new_data);

                    neighbour->patch->GetData(0,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,2, new_data);

                    neighbour->patch->GetData(2,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 0, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 1) {
                    neighbour->patch->GetData(0,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,1, new_data);

                    neighbour->patch->GetData(2,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,1, new_data);

                    neighbour->patch->GetData(0,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,3, new_data);

                    neighbour->patch->GetData(2,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 1, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 2) {
                    neighbour->patch->GetData(0,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,0, new_data);

                    neighbour->patch->GetData(2,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,0, new_data);

                    neighbour->patch->GetData(0,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,2, new_data);

                    neighbour->patch->GetData(2,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 0, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 3) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 3, corner, partial_u, partial_v, twist_vector, patch);
                }

            } else if(i == 2 && pointIndex == 2) { // WEST - LEFT LOWER CORNER

                if(patch->connection_type[i] == 0) {
                    neighbour->patch->GetData(0,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,1, new_data);

                    neighbour->patch->GetData(2,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,1, new_data);

                    neighbour->patch->GetData(0,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,3, new_data);

                    neighbour->patch->GetData(2,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 1, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 1) {
                    neighbour->patch->GetData(1,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,1, new_data);

                    neighbour->patch->GetData(3,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,1, new_data);

                    neighbour->patch->GetData(1,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,3, new_data);

                    neighbour->patch->GetData(3,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 3, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 2) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 2, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 3) {
                    neighbour->patch->GetData(1,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,1, new_data);

                    neighbour->patch->GetData(3,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,1, new_data);

                    neighbour->patch->GetData(1,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,3, new_data);

                    neighbour->patch->GetData(3,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 3, corner, partial_u, partial_v, twist_vector, patch);
                }
            } else if(i == 3 && pointIndex == 2) { // SOUTH - LEFT-LOWER CORNER
                if(patch->connection_type[i] == 0) {
                    neighbour->patch->GetData(0,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,0, new_data);

                    neighbour->patch->GetData(2,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,0, new_data);

                    neighbour->patch->GetData(0,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,2, new_data);

                    neighbour->patch->GetData(2,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 0, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 1) {
                    neighbour->patch->GetData(0,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,1, new_data);

                    neighbour->patch->GetData(2,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,1, new_data);

                    neighbour->patch->GetData(0,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,3, new_data);

                    neighbour->patch->GetData(2,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 1, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 2) {
                    neighbour->patch->GetData(0,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,0, new_data);

                    neighbour->patch->GetData(2,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,0, new_data);

                    neighbour->patch->GetData(0,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,2, new_data);

                    neighbour->patch->GetData(2,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 0, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 3) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 2, corner, partial_u, partial_v, twist_vector, patch);
                }

            } else if(i == 3 && pointIndex == 3) { // SOuTH - RIGHT LOWER CORNER

                if(patch->connection_type[i] == 0) {
                    neighbour->patch->GetData(0,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(0,1, new_data);

                    neighbour->patch->GetData(2,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(2,1, new_data);

                    neighbour->patch->GetData(0,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(0,3, new_data);

                    neighbour->patch->GetData(2,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(2,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 1, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 1) {
                    neighbour->patch->GetData(1,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,1, new_data);

                    neighbour->patch->GetData(3,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,1, new_data);

                    neighbour->patch->GetData(1,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,3, new_data);

                    neighbour->patch->GetData(3,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 3, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 2) {
                    neighbour->patch->GetData(1,0, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,0, new_data);

                    neighbour->patch->GetData(3,0, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,0, new_data);

                    neighbour->patch->GetData(1,2, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,2, new_data);

                    neighbour->patch->GetData(3,2, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,2, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 2, corner, partial_u, partial_v, twist_vector, patch);
                }

                if(patch->connection_type[i] == 3) {
                    neighbour->patch->GetData(1,1, new_data);
                    new_data += corner;
                    neighbour->patch->SetData(1,1, new_data);

                    neighbour->patch->GetData(3,1, new_data);
                    new_data += partial_u;
                    neighbour->patch->SetData(3,1, new_data);

                    neighbour->patch->GetData(1,3, new_data);
                    new_data += partial_v;
                    neighbour->patch->SetData(1,3, new_data);

                    neighbour->patch->GetData(3,3, new_data);
                    new_data += twist_vector;
                    neighbour->patch->SetData(3,3, new_data);
                    updateNeighboursRecursive(patch->neighbours[i], 3, corner, partial_u, partial_v, twist_vector, patch);
                }
            }
        }

    }


    GLboolean HermiteCompositeSurface3::RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const {
        return false;
    };

    GLvoid HermiteCompositeSurface3::addNeighbour(GLuint index_0, int direction_0, GLuint index_1, int direction_1) {
        int ind_primary , ind_secondary;
        for(int i = 0 ; i < _number_of_patches ; i++) {
            if( _attributes[i]->index == index_0) {
                ind_primary = i;
            }
            if(_attributes[i]->index == index_1) {
                ind_secondary = i;
            }
        }

        _attributes[ind_primary]->neighbours[direction_0] = _attributes[ind_secondary];
        _attributes[ind_primary]->connection_type[direction_0] = direction_1;

        _attributes[ind_secondary]->neighbours[direction_1] = _attributes[ind_primary];
        _attributes[ind_secondary]->connection_type[direction_1] = direction_0;

    }

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

    //vector type c - corner, u, v, t
    DCoordinate3 HermiteCompositeSurface3::getCoordinates(int pointIndex, int patchIndex, char vectorType) {

        GLdouble x, y, z;
        //left upper
        if(pointIndex == 0){
            if (vectorType == 'c'){
                _attributes[patchIndex]->patch->GetData(0, 0, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'v'){
                _attributes[patchIndex]->patch->GetData(0, 2, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'u'){
                _attributes[patchIndex]->patch->GetData(2, 0, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else {
                _attributes[patchIndex]->patch->GetData(2, 2, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            }
        }
        //right upper
        else if(pointIndex == 1){
            if (vectorType == 'c'){
                _attributes[patchIndex]->patch->GetData(0, 1, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'v'){
                _attributes[patchIndex]->patch->GetData(0, 3, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'u'){
                _attributes[patchIndex]->patch->GetData(2, 1, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else {
                _attributes[patchIndex]->patch->GetData(2, 3, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            }
        }//left lower
        else if(pointIndex == 2){
            if (vectorType == 'c'){
                _attributes[patchIndex]->patch->GetData(1, 0, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'v'){
                _attributes[patchIndex]->patch->GetData(1, 2, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'u'){
                _attributes[patchIndex]->patch->GetData(3, 0, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else {
                _attributes[patchIndex]->patch->GetData(3, 2, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            }
        }
        //right lower
        else if(pointIndex == 3){
            if (vectorType == 'c'){
                _attributes[patchIndex]->patch->GetData(1, 1, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'v'){
                _attributes[patchIndex]->patch->GetData(1, 3, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else if(vectorType == 'u'){
                _attributes[patchIndex]->patch->GetData(3, 1, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            } else {
                _attributes[patchIndex]->patch->GetData(3, 3, x, y, z);
                DCoordinate3 coord(x, y, z);
                return coord;
            }
        }
    }

}

