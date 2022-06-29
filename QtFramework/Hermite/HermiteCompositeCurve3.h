#ifndef SOMECOMPOSITECURVE3_H
#define SOMECOMPOSITECURVE3_H

#include <Core/Colors4.h>
#include <Core/GenericCurves3.h>
#include "CubicHermiteArc3.h"

namespace cagd
{
    class HermiteCompositeCurve3
    {
    public:
        // Direction : 0 - Left, 1 - Right

        class ArcAttributes
        {
        public:
            CubicHermiteArc3        *arc;
            GenericCurve3           *image;
            Color4                  *color;           // use pointers to pre-defined colors, e.g., Color4 *color = &red;
            GLint                   index;
            // other arc attributes
            // ...

            ArcAttributes   *previous, *next; // pointers to neighboring arc attributes
            int        previous_connection_type, next_connection_type;

            // ctor, copy ctor, assignment operator, dtor (they are required by the std::vector!)
        };

        bool    _show_hermite_first_order = false;
        bool    _show_hermite_second_order = false;
        bool    _highlight_selected_composite = false;
        GLint   _selected = 0;
        GLint   _selected_composite = 0;
        GLint   _composite_index;


    protected:
        GLuint                          _number_of_arcs = 0;
        std::vector<ArcAttributes>      _attributes;          // sequence of arc attributes

    public:
        // special/default ctor
        HermiteCompositeCurve3(GLuint);

        GLboolean InsertNewArc(CubicHermiteArc3* arc, GenericCurve3* image, GLfloat r, GLfloat g, GLfloat b, GLint index);
        GLboolean DeleteExistingArc(GLuint index);
        CubicHermiteArc3* ContinueExisitingArc(GLuint index, int direction);
        GLvoid addNeighbourContinue(GLint index_0, int direction, GLint index_1);
        CubicHermiteArc3* JoinExistingArcs(GLuint index_0, int direction_0, GLuint index_1, int direction_1);
        void MergeExistingArcs(GLuint index_0, int direction_0, GLuint index_1, int direction_1);

        GLboolean RenderAllArcs() const;
        GLboolean RenderSelectedArc(GLuint index, GLuint order, GLenum render_mode) const;

        GLvoid updateArc(GLint index, GenericCurve3* image);

        void setFirstOrderVisibility(bool);
        void setSecondOrderVisibility(bool);
        void highlightSelectedComposite(bool);
        void setSelected(GLint);
        void setSelectedComposite(GLint);
    };
}

#endif // SOMECOMPOSITECURVE3_H
