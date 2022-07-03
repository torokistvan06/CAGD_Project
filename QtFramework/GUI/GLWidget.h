#pragma once

#include <GL/glew.h>
#include <QOpenGLWidget>
#include <iostream>
#include <fstream>
#include "../Core/Matrices.h"
#include "../Test/TestFunctions.h"
#include "../Core/Constants.h"
#include "../Parametric/ParametricCurves3.h"
#include "../Parametric/ParametricSurfaces3.h"
#include "../Core/TriangulatedMeshes3.h"
#include "../Core/Materials.h"
#include "../Cyclic/CyclicCurves3.h"
#include "../Core/ModelProperties.h"
#include "../Core/Lights.h"
#include "../Core/ShaderPrograms.h"
#include "../Hermite/CubicHermiteArc3.h"
#include "../Hermite/BicubicHermitePatch3.h"
#include "../Hermite/HermiteCompositeCurve3.h"
#include "../Hermite/HermiteCompositeSurfaces3.h"
#include <QTimer>
#include <QOpenGLTexture>

namespace cagd
{
    class GLWidget: public QOpenGLWidget
    {
        Q_OBJECT

    private:

        // variable that defines what we see on the main window

        int _selected = 2;

        // variables defining the projection matrix

        double       _aspect;            // aspect ratio of the rendering window
        double       _fovy;              // field of view in direction y
        double       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        double       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // variables for Parametric Curves

        GLuint                          _parametric_curves_count = 8;
        RowMatrix<ParametricCurve3*>    _parametric_curves;
        RowMatrix<GenericCurve3*>       _image_of_parametric_curves;

        int                             _selected_parametric_curve = 0;
        bool                            _show_tangents = true;
        bool                            _show_acceleration_vectors = true;
        double                          _scale = 1;
        GLuint                          _div_point_count = 200;

        // functions for Parametric Curves

        bool initalizeParametricCurves();
        bool paintParametricCurves();
        void destroyParametricCurves(int _count);
        void destroyImages(int _count);

        // variables for RedBullAirAndWaterRaceScene

        RowMatrix<TriangulatedMesh3>    _dynamic_models;
        RowMatrix<TriangulatedMesh3>    _characters;
        RowMatrix<TriangulatedMesh3>    _static_models;

        RowMatrix<ModelProperties>      _static_model_properties;

        GLint                           _dynamic_model_count = 4;
        GLint                           _static_model_count = 4;

        CyclicCurve3                    *_cyclic_curves[4];
        GenericCurve3                   *_images_of_cyclic_curves[4];

        GLint                           _speed[4];

        GLdouble                        _cyclic_div_point_count = 200;
        GLdouble                        _derivatives_scale = 1;

        GLdouble                        _dynamic_model_scaling = 1;
        GLboolean                       _dynamic_scaling_up = true;

        GLuint                           _selected_cyclic_curve = 0;
        GLuint                           _selected_point = 0;

        GLboolean                       _show_cyclic_curve = false;
        GLboolean                       _show_tangent = false;
        GLboolean                       _show_acceleration_vector = false;

        RowMatrix<GLuint>               _old_time_index;
        QTimer                          *_old_timer = new QTimer();

        RowMatrix<GLdouble*>             _old_transformation;

        RowMatrix<ColumnMatrix<GLdouble>>          knot_vector;
        RowMatrix<ColumnMatrix<DCoordinate3>>      points;

        DirectionalLight                            *_dl;

        // functions for RedBullAirAndWaterRaceScene

        void initializeCyclicCurves();
        void initializeCyclicData();
        bool initializeProperties();
        bool initializeModels();

        void updateCyclicCurveImage(int);

        void destroyCyclicCurveImage(int);

        void paintSelectedCyclicCurve();
        bool paintModels();
        bool paintStaticModels();

        // variables for parametric surfaces

        ParametricSurface3*     _parametric_surfaces[6];
        TriangulatedMesh3*      _image_of_ps[6];

        ParametricCurve3*       _parametric_surfaces_curve[6];
        GenericCurve3*          _images_of_parametric_surfaces_curve[6];

        int                     _selected_parametric_surface = 0;
        int                     _selected_texture = 0;
        int                     _selected_material = 0;

        bool                    _show_texture = false;

        QTimer*                 _timer = new QTimer();
        GLdouble                _u_min[6];
        GLdouble                _u_index[6];
        GLdouble                _u_max[6];

        GLdouble                _transformation[16];

        TriangulatedMesh3       _leMouse;

        GLuint                  u_div_point_count = 200;
        GLuint                  v_div_point_count = 200;

        GLdouble                     rotate = 0;

        // functions for parametric surfaces

        void initializeParametricSurfaces();
        void initializeParametricSurfaceData();

        void paintSelectedSurface();

        // variables for shaders


        float                       _shader_scale = 0;
        float                       _shader_smoothing = 0;
        float                       _shader_shading = 0;

        float                       _red = 50.0f;
        float                       _green = 50.0f;
        float                       _blue = 50.0f;


        int                         _selected_shader = 1;

        // functions for shaders


        // Hermite Arc

        CubicHermiteArc3           *_cubic_hermite_arc3 = nullptr;
        GenericCurve3              *_image_of_cubic_hermite_arc3;
        GenericCurve3              *_image_of_interpolating_cubic_hermite_arc3 = nullptr;

        bool                        initializeHermiteArc();
        bool                        renderHermiteArc();
        void                        updateHermiteArc();

        // Hermite patch

        BicubicHermitePatch3        *_bicubic_hermite_patch3 = nullptr;
        TriangulatedMesh3           *_before_interpolation;
        TriangulatedMesh3           *_after_interpolation;
        RowMatrix<GenericCurve3*>   *_u_lines;
        RowMatrix<GenericCurve3*>   *_v_lines;


        bool                        _show_hermite_patch_first_derivatives = false;
        bool                        _show_hermite_patch_second_derivatives = false;

        bool                        initializeHermitePatch();
        bool                        renderHermitePatch();
        void                        updateHermitePatch();

        // Project - Hermite Arcs

        GLuint                                      _selected_hermite_arc = 0;
        GLuint                                      _number_of_hermite_arcs = 9;
        GLuint                                      _selected_hermite_arc_point = 0;
        GLuint                                      _selected_composite_arc = 0;
        GLuint                                      _number_of_composite_arcs = 0;
        GLuint                                      _primary_dir = 0, _secondary_dir = 0; // 0 - Left, 1 - Right
        GLuint                                      _selected_secondary_arc = 0;

        GLfloat                                     _r = 0.5, _g = 0.5, _b = 0.5;

        RowMatrix<CubicHermiteArc3*>                _hermite_arcs;
        RowMatrix<GenericCurve3*>                   _images_of_hermite_arcs;
        RowMatrix<GLint>                            _composite_arc_index_of_hermite_arcs;
        RowMatrix<HermiteCompositeCurve3*>          _composite_hermite_arcs;

        bool                                        _show_hermite_first_order = false;
        bool                                        _show_hermite_second_order = false;
        bool                                        _highlight_selected_composite_curve = false;
        bool                                        _valid_selected_composite_curve = false;

        bool                                        _initializeHermiteArcs();
        bool                                        _renderHermiteArcs();
        bool                                        _updateSelectedHermiteArc();


        // Project - Hermite Patches;

        GLuint                                      _selected_hermite_patch = 0;
        GLuint                                      _number_of_hermite_patches = 9;
        GLuint                                      _selected_hermite_patch_point = 0;
        GLuint                                      _selected_composite_patch = 0;
        GLuint                                      _number_of_composite_patches = 0;
        GLuint                                      _primary_patch_dir = 0, _secondary_patch_dir = 0;
        GLuint                                      _selected_secondary_patch = 0;

        GLuint                                      _selected_patch_material = 0;
        GLuint                                      _selected_patch_texture = 0;
        GLuint                                      _selected_patch_shader = 0;

        RowMatrix<BicubicHermitePatch3*>            _hermite_patches;
        RowMatrix<TriangulatedMesh3*>               _images_of_hermite_patches;
        RowMatrix<GLint>                            _composite_patch_index_of_hermite_patches;
        RowMatrix<HermiteCompositeSurface3*>        _composite_hermite_patches;
        RowMatrix<RowMatrix<GenericCurve3*>*>       _patches_u_lines, _patches_v_lines;

        RowMatrix<ShaderProgram>                    _shaders;
        RowMatrix<Material>                         _materials;
        QOpenGLTexture*                             _texture[14];

        bool                                        _valid_selected_composite_patch;

        bool                                        _show_u_lines = false;
        bool                                        _show_v_lines = false;
        bool                                        _show_first_order_derivates = false;
        bool                                        _show_second_order_derivates = false;
        bool                                        _highlight_selected_composite_patch = false;

        bool                                        _use_textures = false;
        bool                                        _use_shaders = false;

        bool                                        _initializeHermitePatches();
        bool                                        _renderHermitePatches();
        bool                                        _updateSelectedHermitePatch();
        void                                        _updatePatchNeighbours(DCoordinate3, DCoordinate3, DCoordinate3, DCoordinate3);
        void                                        _initializeTextures();
        void                                        _initializeShaders();
        bool                                        _initializeMaterials();


    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);
        virtual ~GLWidget();


    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        void set_tab(int value);
        // Slots for parametric curves

        void set_scale(double scale);
        void set_div_point_count(int div_point_count);

        void setParametricCurveIndex(int index);
        void setVisibilityOfTangents(bool visibility);
        void setVisibilityOfAccelerationVectors(bool visibility);

        // Slots for RedBullAirAndWaterRaceScene

        void animate();
        void setSelectedCyclicCurve(int index);
        void setSelectedPoint(int index);
        void setVisibilityOfCyclicCurve(bool visibility);
        void setVisibilityOfTangent(bool visibility);
        void setVisiblityOfAccelerationVector(bool visiblility);
        void setSpeedOfSelectedCurve(int value);

        void setSelectedXSlot(double value);
        void setSelectedYSlot(double value);
        void setSelectedZSlot(double value);
        void distanceSlot(double value);

        // Slots for parametric surfaces

        void setSelectedSurface(int index);
        void setSelectedMaterial(int index);
        void setSelectedTexture(int index);
        void setVisibilityOfTexture(bool visibility);

        void animateSurface();

        // Slots for shaders

        void setSelectedShader(int index);

        void setShaderScale(double value);
        void setSmoothing(double value);
        void setShading(double value);

        void setRed(double value);
        void setBlue(double value);
        void setGreen(double value);

        void showHermitePatchFirstOrder(bool visibility);
        void showHermitePatchSecondOrder(bool visibility);

        // Project - Hermite arc

        void _createNewCompositeArc();
        void _highlightHermiteCompositeArc(bool visibility);
        void _setSelectedCompositeArc(int index);

        void _addSelectedArcToSelectedCompositeArc();

        void _setSelectedHermiteArc(int index);

        void setHermitePointIndex(int index);

        void _setSelectedSecondaryHermiteArc(int index);

        void _hermite_red(double value);
        void _hermite_green(double value);
        void _hermite_blue(double value);

        void _setPrimaryDirection(int index);
        void _setSecondaryDirection(int index);
        void _setSecondarySelectedArc(int index);

        void _continueArc();
        void _joinArc();
        void _mergeArc();

        void _updateArcNeighbours(DCoordinate3, DCoordinate3);

        void setHermitePointx(double value);
        void setHermitePointy(double value);
        void setHermitePointz(double value);

        void setHermitePointdx(double value);
        void setHermitePointdy(double value);
        void setHermitePointdz(double value);

        void showHermiteFirstOrderDerivates(bool visibility);
        void showHermiteSecondOrderDerivates(bool visibility);

        // Project - Hermite patch

        void _continuePatch();
        void _joinPatch();
        void _mergePatch();

        void  _deleteSelectedPatch();

        void _setPatchPrimaryDirection(int index);
        void _setPatchSecondaryDirection(int index);

        void _showHermitePatchTextures(bool visibility);
        void _showHermitePatchShaders(bool visibility);

        void _setHermitePatchMaterial(int index);
        void _setHermitePatchTexture(int index);
        void _setHermitePatchShader(int index);

        void _setSelectedHermitePatch(int index);
        void _setSelectedHermitePatchPoint(int index);

        void _setSelectedSecondaryHermitePatch(int index);
        void _setVisibilityOfULines(bool visibility);
        void _setVisibilityOfVLines(bool visibility);
        void _highlightSelectedCompositePatch(bool visibility);
        void _setVisibilityOfFirstOrderDerivatives(bool visibility);
        void _setVisibilityOfSecondOrderDerivatives(bool visibility);

        void _selectCompositePatch(int);
        void _createNewCompositePatch();
        void _addSelectedPatchToSelectedCompositePatch();

        void setHermitePatchIndex(int index);

        void setHermitePatchPointX(double value);
        void setHermitePatchPointY(double value);
        void setHermitePatchPointZ(double value);
        void setHermitePatchPointUX(double value);
        void setHermitePatchPointUY(double value);
        void setHermitePatchPointUZ(double value);
        void setHermitePatchPointVX(double value);
        void setHermitePatchPointVY(double value);
        void setHermitePatchPointVZ(double value);
        void setHermitePatchPointTX(double value);
        void setHermitePatchPointTY(double value);
        void setHermitePatchPointTZ(double value);



    signals:

        void setSelectedX(double value);
        void setSelectedY(double value);
        void setSelectedZ(double value);
        void distanceSignal(double value);

        // Project - Hermite arc

        void newHermiteArcAdded(int value);

        void xHermitePointChanged(double value);
        void yHermitePointChanged(double value);
        void zHermitePointChanged(double value);

        void dxHermitePointChanged(double value);
        void dyHermitePointChanged(double value);
        void dzHermitePointChanged(double value);

        // Hermite patch

        void HermitePatchPointChangeX(double value);
        void HermitePatchPointChangeY(double value);
        void HermitePatchPointChangeZ(double value);
        void HermitePatchPointChangeUX(double value);
        void HermitePatchPointChangeUY(double value);
        void HermitePatchPointChangeUZ(double value);
        void HermitePatchPointChangeVX(double value);
        void HermitePatchPointChangeVY(double value);
        void HermitePatchPointChangeVZ(double value);
        void HermitePatchPointChangeTX(double value);
        void HermitePatchPointChangeTY(double value);
        void HermitePatchPointChangeTZ(double value);


    };

}
