#include "HermiteCompositeCurve3.h"

#include <iostream>
using namespace std;

namespace cagd {

    HermiteCompositeCurve3::HermiteCompositeCurve3(GLuint index) {
        this->_composite_index = index;
    }

    GLboolean HermiteCompositeCurve3::InsertNewArc(CubicHermiteArc3* arc, GenericCurve3* image, GLfloat r, GLfloat g, GLfloat b, GLint index){
        ArcAttributes element;

        element.index = index;
        element.arc = arc;
        element.image = image;
        element.next = nullptr;
        element.previous = nullptr;

        element.color = new Color4(r,g,b);
        _number_of_arcs += 1;

        this->_attributes.push_back(element);
        return GL_TRUE;
    }

    GLboolean HermiteCompositeCurve3::DeleteExistingArc(GLuint index){

        for(GLuint i = index ; i <= _number_of_arcs ; i++) {
            _attributes[i] = _attributes[i + 1];
        }

        _number_of_arcs -= 1;
        _attributes.resize(_number_of_arcs);

        return GL_TRUE;
    }

    CubicHermiteArc3* HermiteCompositeCurve3::ContinueExisitingArc(GLuint index, int direction){

        int ind;

        for(GLuint i = 0 ; i < _number_of_arcs ; i++) {
            if(_attributes[i].index == index) {
               ind = i;
            }
        }

        if( _attributes[ind].next != nullptr) {
            return nullptr;
        }

        CubicHermiteArc3 *arc = new CubicHermiteArc3();
        DCoordinate3 distance = _attributes[ind].arc->GetDistance();
        if(distance.x() < 0) {
            distance.x() = -distance.x();
        }

        if(distance.y() < 0) {
            distance.y() = -distance.y();
        }

        if(distance.z() < 0) {
            distance.z() = -distance.z();
        }

        DCoordinate3 left = _attributes[ind].arc->GetCorner(0), right = _attributes[ind].arc->GetCorner(1);
        DCoordinate3 leftTangent = _attributes[ind].arc->GetTangent(0), rightTangent = _attributes[ind].arc->GetTangent(1);

        if(left.x() > right.x()) {
            swap(left,right);
            swap(leftTangent, rightTangent);
        }

        if(direction == 0) {
            arc->SetCorner(0, left - distance);
            arc->SetCorner(1, left);
            arc->SetTangent(0,leftTangent);
            arc->SetTangent(1,leftTangent);
        } else {
            arc->SetCorner(0,right);
            arc->SetCorner(1,right + distance);
            arc->SetTangent(0,rightTangent);
            arc->SetTangent(1,rightTangent);
        }

        return arc;
    }

    GLvoid HermiteCompositeCurve3::addNeighbourContinue(GLint index_0, int direction, GLint index_1) {
        int ind_0 , ind_1;
        for(int i = 0 ; i < _number_of_arcs ; i++) {
            if( _attributes[i].index == index_0) {
                ind_0 = i;
            }
            if(_attributes[i].index == index_1) {
                ind_1 = i;
            }
        }

        _attributes[ind_0].next = &_attributes[ind_1];
        if (direction == 0)
            _attributes[ind_0].next_connection_type = 1;
        else
            _attributes[ind_0].next_connection_type = 0;


    }

    CubicHermiteArc3* HermiteCompositeCurve3::JoinExistingArcs(GLuint index_0, int direction_0, GLuint index_1, int direction_1){

        int ind_primary = -1, ind_secondary = -1;

        if(index_0 == index_1){
            return nullptr;
        }

        for(GLuint i = 0 ; i < _number_of_arcs ; i++) {
            if(_attributes[i].index == index_0) {
               ind_primary = i;
            }

            if(_attributes[i].index == index_1) {
               ind_secondary = i;
            }
        }

        if(ind_primary == -1 || ind_secondary == -1){
            return nullptr;
        }

        //deciding left and right points of primary and secondary arc
        DCoordinate3 left_primary = _attributes[ind_primary].arc->GetCorner(0);
        DCoordinate3 right_primary = _attributes[ind_primary].arc->GetCorner(1);
        DCoordinate3 leftTangent_primary = _attributes[ind_primary].arc->GetTangent(0);
        DCoordinate3 rightTangent_primary = _attributes[ind_primary].arc->GetTangent(1);

        if(left_primary.x() > right_primary.x()) {
            swap(left_primary, right_primary);
            swap(leftTangent_primary, rightTangent_primary);
        }

        DCoordinate3 left_secondary = _attributes[ind_secondary].arc->GetCorner(0);
        DCoordinate3 right_secondary = _attributes[ind_secondary].arc->GetCorner(1);
        DCoordinate3 leftTangent_secondary = _attributes[ind_secondary].arc->GetTangent(0);
        DCoordinate3 rightTangent_secondary = _attributes[ind_secondary].arc->GetTangent(1);

        if(left_secondary.x() > right_secondary.x()) {
            swap(left_secondary, right_secondary);
            swap(leftTangent_secondary, rightTangent_secondary);
        }

        //deceding start and end point of new arc
        CubicHermiteArc3 *arc = new CubicHermiteArc3();

        //left left
        if(direction_0 == 0 && direction_1 == 0) {
            arc->SetCorner(0, left_primary);
            arc->SetCorner(1, left_secondary);
            arc->SetTangent(0,leftTangent_primary);
            arc->SetTangent(1,leftTangent_secondary);
        }
        //left right
        else if(direction_0 == 0 && direction_1 == 1) {
            arc->SetCorner(0, left_primary);
            arc->SetCorner(1, right_secondary);
            arc->SetTangent(0,leftTangent_primary);
            arc->SetTangent(1,rightTangent_secondary);
        }
        //right left
        else if(direction_0 == 1 && direction_1 == 0) {
            arc->SetCorner(0, right_primary);
            arc->SetCorner(1, left_secondary);
            arc->SetTangent(0,rightTangent_primary);
            arc->SetTangent(1,leftTangent_secondary);
        }
        //right right
        else {
            arc->SetCorner(0, right_primary);
            arc->SetCorner(1, right_secondary);
            arc->SetTangent(0,rightTangent_primary);
            arc->SetTangent(1,rightTangent_secondary);
        }


        return arc;
    }

    void HermiteCompositeCurve3::MergeExistingArcs(GLuint index_0, int direction_0, GLuint index_1, int direction_1){

        int ind_primary = -1, ind_secondary = -1;

        for(GLuint i = 0 ; i < _number_of_arcs ; i++) {
            if(_attributes[i].index == index_0) {
               ind_primary = i;
            }

            if(_attributes[i].index == index_1) {
               ind_secondary = i;
            }
        }

        //deciding left and right points of primary and secondary arc
        DCoordinate3 left_primary = _attributes[ind_primary].arc->GetCorner(0);
        DCoordinate3 right_primary = _attributes[ind_primary].arc->GetCorner(1);
        DCoordinate3 leftTangent_primary = _attributes[ind_primary].arc->GetTangent(0);
        DCoordinate3 rightTangent_primary = _attributes[ind_primary].arc->GetTangent(1);

        if(left_primary.x() > right_primary.x()) {
            swap(left_primary, right_primary);
            swap(leftTangent_primary, rightTangent_primary);
        }

        DCoordinate3 left_secondary = _attributes[ind_secondary].arc->GetCorner(0);
        DCoordinate3 right_secondary = _attributes[ind_secondary].arc->GetCorner(1);
        DCoordinate3 leftTangent_secondary = _attributes[ind_secondary].arc->GetTangent(0);
        DCoordinate3 rightTangent_secondary = _attributes[ind_secondary].arc->GetTangent(1);

        if(left_secondary.x() > right_secondary.x()) {
            swap(left_secondary, right_secondary);
            swap(leftTangent_secondary, rightTangent_secondary);
        }

        DCoordinate3 middle_point;
        DCoordinate3 middle_tangent;

        //left left
        if(direction_0 == 0 && direction_1 == 0) {
            middle_point = (left_primary + left_secondary)/2;
            middle_tangent = (leftTangent_primary + leftTangent_secondary)/2;

            _attributes[ind_primary].arc->SetCorner(0, middle_point);
            _attributes[ind_primary].arc->SetTangent(0, middle_tangent);

            _attributes[ind_secondary].arc->SetCorner(0, middle_point);
            _attributes[ind_secondary].arc->SetTangent(0, middle_tangent);
        }


//        //left right
//        else if(direction_0 == 0 && direction_1 == 1) {
//            arc->SetCorner(0, left_primary);
//            arc->SetCorner(1, right_secondary);
//            arc->SetTangent(0,leftTangent_primary);
//            arc->SetTangent(1,rightTangent_secondary);
//        }
//        //right left
//        else if(direction_0 == 1 && direction_1 == 0) {
//            arc->SetCorner(0, right_primary);
//            arc->SetCorner(1, left_secondary);
//            arc->SetTangent(0,rightTangent_primary);
//            arc->SetTangent(1,leftTangent_secondary);
//        }
//        //right right
//        else {
//            arc->SetCorner(0, right_primary);
//            arc->SetCorner(1, right_secondary);
//            arc->SetTangent(0,rightTangent_primary);
//            arc->SetTangent(1,rightTangent_secondary);
//        }
    }

    GLboolean HermiteCompositeCurve3::RenderAllArcs() const {

        for(GLint i = 0 ; i < _number_of_arcs ; i++) {

            glPointSize(10.0f);
            if (_attributes[i].index == _selected) {
                glColor3f(1,0,0);
            } else if (_selected_composite == this->_composite_index && _highlight_selected_composite) {
                glColor3f(1,0,1);
            } else {
                glColor4f(_attributes[i].color->r(),_attributes[i].color->g(),_attributes[i].color->b(),_attributes[i].color->a());
            }
            _attributes[i].arc->RenderData(GL_LINE_STRIP);
            if (!_attributes[i].image->RenderDerivatives(0, GL_LINE_STRIP)) {
                return false;
            }

           if(_show_hermite_first_order && i == _selected){
                 glPointSize(1.0f);
                 glColor3f(0.0f, 1.0f, 0.0f);
                 _attributes[i].image->RenderDerivatives(1, GL_LINES);
           }

           if(_show_hermite_second_order && i == _selected){
                glPointSize(1.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                _attributes[i].image->RenderDerivatives(2, GL_LINES);
           }

        }
        return GL_TRUE;
    }

    void HermiteCompositeCurve3::updateArc(GLint index, GenericCurve3* image) {
        for(GLint i = 0 ; i < _number_of_arcs ; i++) {
            if(_attributes[i].index == index && _attributes[i].index) {
                _attributes[i].image = image;
            }
        }
    }

    void HermiteCompositeCurve3::setSelected(int value) {
        this->_selected = value;
    }

    void HermiteCompositeCurve3::setFirstOrderVisibility(bool visibility) {
        this->_show_hermite_first_order = visibility;
    }

    void HermiteCompositeCurve3::setSecondOrderVisibility(bool visibility) {
        this->_show_hermite_second_order = visibility;
    }

    void HermiteCompositeCurve3::highlightSelectedComposite(bool visibility) {
        this->_highlight_selected_composite = visibility;
    }

    void HermiteCompositeCurve3::setSelectedComposite(int value) {
        this->_selected_composite = value;
    }

    GLboolean HermiteCompositeCurve3::RenderSelectedArc(GLuint index, GLuint order, GLenum render_mode) const {

        return GL_TRUE;
    }
}
