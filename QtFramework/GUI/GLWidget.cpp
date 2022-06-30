#include "GLWidget.h"

#if !defined(__APPLE__)
#include <GL/glu.h>
#endif


using namespace std;

#include <Core/Exceptions.h>

namespace cagd
{
    //--------------------------------
    // special and default constructor

    GLWidget::GLWidget(QWidget *parent): QOpenGLWidget(parent)
    {
    }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {
        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        //glLoadIdentity();

        _aspect = static_cast<double>(width()) / static_cast<double>(height());
        _z_near = 1.0;
        _z_far  = 1000.0;
        _fovy   = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0; _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0; _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling the depth test
        glEnable(GL_DEPTH_TEST);

        // setting the background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;

        // ...

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects

            switch(_selected) {
                case 0:
            {
                if (!initalizeParametricCurves())
                {
                    throw Exception("Could not create all parametric curves!");
                }
                break;
            }
                case 1:
            {

                initializeCyclicData();
                initializeModels();
                _initializeMaterials();
                initializeProperties();
                initializeCyclicCurves();
                connect(_old_timer, SIGNAL(timeout()), this, SLOT(animate()));
                break;
            }
                case 2:
            {

                initializeParametricSurfaceData();
                _initializeMaterials();
                _initializeTextures();
                initializeParametricSurfaces();
                connect(_timer, SIGNAL(timeout()), this, SLOT(animateSurface()));
                break;
            }
                case 3:
            {
                initializeParametricSurfaceData();
                _initializeMaterials();
                _initializeTextures();
                initializeParametricSurfaces();
                connect(_timer, SIGNAL(timeout()), this, SLOT(animateSurface()));
                _initializeShaders();
                break;
            }
                case 4:
            {
                initializeHermiteArc();
                updateHermiteArc();
                break;
            }
            case 5:
            {
                _initializeShaders();
                initializeHermitePatch();
                updateHermitePatch();
                break;
            }
            case 6:
            {
                _initializeHermiteArcs();
                break;
            }
                case 7:
            {
                HCoordinate3 direction (0.0, 0.0, 5.0, 0.0);
                Color4  ambient(0.4, 0.4, 0.4, 1.0);
                Color4  diffuse(0.8, 0.8, 0.8, 1.0);
                Color4  specular(1.0, 1.0, 1.0, 1.0);
                _dl = new (nothrow) DirectionalLight(GL_LIGHT1, direction, ambient, diffuse, specular);

                _initializeMaterials();
                _initializeTextures();
                _initializeShaders();
                _initializeHermitePatches();
                break;
            }
            }

            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

            glEnable(GL_POLYGON_SMOOTH);
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
            glEnable(GL_DEPTH_TEST);


        }
        catch (Exception &e)
        {
            cout << e << endl;
        }
    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)

            switch(_selected) {
                case 0:
            {
                if (!paintParametricCurves())
                {
                    throw Exception("Could not paint all parametric curves!");
                }
                break;
            }
                case 1:
            {
                paintSelectedCyclicCurve();
                paintStaticModels();
                paintModels();
                _old_timer->start(50);
                break;
            }
                case 2:
            {
                paintSelectedSurface();
                _timer->start(50);
                break;
            }
                case 3:
            {
                _shaders[_selected_shader].Enable();
                _leMouse.Render();
                _shaders[_selected_shader].Disable();
                break;
            }
                case 4:
            {
                break;
            }
                case 5:
            {
                renderHermitePatch();
                break;
            }
                case 6:
            {
                _renderHermiteArcs();
                break;
            }
                case 7:
            {
                _renderHermitePatches();
                break;
            }
            }


        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored
        glPopMatrix();
    }

    // PROJECT ONLY

    // Hermite Arcs

    bool GLWidget::_initializeHermiteArcs() {
        ifstream fin("Hermite/HermiteArcs.txt");

        fin >> _number_of_hermite_arcs;

        _hermite_arcs.ResizeColumns(_number_of_hermite_arcs);
        _images_of_hermite_arcs.ResizeColumns(_number_of_hermite_arcs);
        _composite_arc_index_of_hermite_arcs.ResizeColumns(_number_of_hermite_arcs);

        for(GLuint i = 0 ; i < _number_of_hermite_arcs ; i++) {
            _hermite_arcs[i] = new CubicHermiteArc3();
            _images_of_hermite_arcs[i] = new GenericCurve3();
            _composite_arc_index_of_hermite_arcs[i] = -1;

            fin >> *_hermite_arcs[i];
            if( !_hermite_arcs[i]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW)) {
                for(GLuint j = 0 ; j < i ; j++) {
                    delete _hermite_arcs[j];
                    _hermite_arcs[j] = nullptr;
                    delete _images_of_hermite_arcs[j];
                    _images_of_hermite_arcs[j] = nullptr;
                }
                return false;
            }

            _images_of_hermite_arcs[i] = _hermite_arcs[i]->GenerateImage(2,100,GL_STATIC_DRAW);
            if (!_images_of_hermite_arcs[i]) {
                for(GLuint j = 0 ; j < i ; j++) {
                    delete _hermite_arcs[j];
                    _hermite_arcs[j] = nullptr;
                    delete _images_of_hermite_arcs[j];
                    _images_of_hermite_arcs[j] = nullptr;
                }
                return false;
            }

            if( !_images_of_hermite_arcs[i]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW)) {
                for(GLuint j = 0 ; j < i ; j++) {
                    delete _hermite_arcs[j];
                    _hermite_arcs[j] = nullptr;
                    delete _images_of_hermite_arcs[j];
                    _images_of_hermite_arcs[j] = nullptr;
                }
                return false;
            }
        }

        return true;
    }

    bool GLWidget::_renderHermiteArcs() {
        for(GLuint i = 0 ; i < _number_of_hermite_arcs ; i++) {
            if( _composite_arc_index_of_hermite_arcs[i] == -1) {
                glPointSize(10.0f);
                if (i == _selected_hermite_arc) {
                    glColor3f(1.0f, 0.0, 0.0);
                } else if (i == _selected_secondary_arc) {
                    glColor3f(0.0f, 0.0f, 1.0);
                } else {
                    glColor3f(0.0f, 1.0f, 0.0f);
                }

                _hermite_arcs[i]->RenderData(GL_LINE_STRIP);
                if (!_images_of_hermite_arcs[i]->RenderDerivatives(0, GL_LINE_STRIP)) {
                    return false;
                }

               if(_show_hermite_first_order && i == _selected_hermite_arc){
                     glPointSize(1.0f);
                     glColor3f(0.0f, 1.0f, 0.0f);
                     _images_of_hermite_arcs[i]->RenderDerivatives(1, GL_LINES);
               }

               if(_show_hermite_second_order && i == _selected_hermite_arc){
                    glPointSize(1.0f);
                    glColor3f(0.0f, 0.0f, 1.0f);
                    _images_of_hermite_arcs[i]->RenderDerivatives(2, GL_LINES);
               }
            }
        }

        for(GLuint i = 0 ; i < _number_of_composite_arcs ; i++) {
            _composite_hermite_arcs[i]->RenderAllArcs();
        }

        return true;
    }

    bool GLWidget::_updateSelectedHermiteArc() {

        if( !_hermite_arcs[_selected_hermite_arc]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW) || !_hermite_arcs[_selected_secondary_arc]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW)) {
            for(GLuint j = 0 ; j < _number_of_hermite_arcs ; j++) {
                delete _hermite_arcs[j];
                _hermite_arcs[j] = nullptr;
                delete _images_of_hermite_arcs[j];
                _images_of_hermite_arcs[j] = nullptr;
            }
            return false;
        }

        _images_of_hermite_arcs[_selected_hermite_arc] = _hermite_arcs[_selected_hermite_arc]->GenerateImage(2,100,GL_STATIC_DRAW);
        _images_of_hermite_arcs[_selected_secondary_arc] = _hermite_arcs[_selected_secondary_arc]->GenerateImage(2,100,GL_STATIC_DRAW);

        if (!_images_of_hermite_arcs[_selected_hermite_arc] || !_images_of_hermite_arcs[_selected_secondary_arc]) {
            for(GLuint j = 0 ; j < _number_of_hermite_arcs ; j++) {
                delete _hermite_arcs[j];
                _hermite_arcs[j] = nullptr;
                delete _images_of_hermite_arcs[j];
                _images_of_hermite_arcs[j] = nullptr;
            }
            return false;
        }

        if( !_images_of_hermite_arcs[_selected_hermite_arc]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW) || !_images_of_hermite_arcs[_selected_secondary_arc]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW)) {
            for(GLuint j = 0 ; j < _number_of_hermite_arcs ; j++) {
                delete _hermite_arcs[j];
                _hermite_arcs[j] = nullptr;
                delete _images_of_hermite_arcs[j];
                _images_of_hermite_arcs[j] = nullptr;
            }
            return false;
        }

        for(GLint i = 0 ; i < _number_of_composite_arcs ; i++) {
            if(i == _selected_composite_arc) {
                _composite_hermite_arcs[i]->updateArc(_selected_hermite_arc, _images_of_hermite_arcs[_selected_hermite_arc]);
                _composite_hermite_arcs[i]->updateArc(_selected_secondary_arc, _images_of_hermite_arcs[_selected_secondary_arc]);
            }
        }

        return true;
    }



    void GLWidget::_continueArc() {
        if(_composite_arc_index_of_hermite_arcs[_selected_hermite_arc] == -1) {
            return;
        }

        int _comp_index = _composite_arc_index_of_hermite_arcs[_selected_hermite_arc];
        CubicHermiteArc3* arc = _composite_hermite_arcs[_comp_index]->ContinueExisitingArc(_selected_hermite_arc, _primary_dir);
        if(arc == nullptr)
            return;

        _number_of_hermite_arcs += 1;
        _hermite_arcs.ResizeColumns(_number_of_hermite_arcs);
        _images_of_hermite_arcs.ResizeColumns(_number_of_hermite_arcs);
        _composite_arc_index_of_hermite_arcs.ResizeColumns(_number_of_hermite_arcs);

        _composite_arc_index_of_hermite_arcs[_number_of_hermite_arcs - 1] = _composite_arc_index_of_hermite_arcs[_selected_hermite_arc];
        _hermite_arcs[_number_of_hermite_arcs - 1] = arc;

        _hermite_arcs[_number_of_hermite_arcs - 1]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW);

        _images_of_hermite_arcs[_number_of_hermite_arcs - 1] = _hermite_arcs[_number_of_hermite_arcs - 1]->GenerateImage(2,100,GL_STATIC_DRAW);

        _images_of_hermite_arcs[_number_of_hermite_arcs - 1]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW);
        _composite_hermite_arcs[_comp_index]->InsertNewArc(_hermite_arcs[_number_of_hermite_arcs - 1], _images_of_hermite_arcs[_number_of_hermite_arcs - 1], _r, _g, _b, _number_of_hermite_arcs - 1);
        _composite_hermite_arcs[_comp_index]->addNeighbourContinue(_selected_hermite_arc, _primary_dir , _number_of_hermite_arcs - 1);
        update();
    }

    void GLWidget::_joinArc(){

        if(_composite_arc_index_of_hermite_arcs[_selected_hermite_arc] == -1) {
            return;
        }

        int _comp_index = _composite_arc_index_of_hermite_arcs[_selected_hermite_arc];
        CubicHermiteArc3* arc = _composite_hermite_arcs[_comp_index]->JoinExistingArcs(_selected_hermite_arc, _primary_dir, _selected_secondary_arc, _secondary_dir);
        if(arc == nullptr)
            return;

        _number_of_hermite_arcs += 1;
        _hermite_arcs.ResizeColumns(_number_of_hermite_arcs);
        _images_of_hermite_arcs.ResizeColumns(_number_of_hermite_arcs);
        _composite_arc_index_of_hermite_arcs.ResizeColumns(_number_of_hermite_arcs);

        _composite_arc_index_of_hermite_arcs[_number_of_hermite_arcs - 1] = _composite_arc_index_of_hermite_arcs[_selected_hermite_arc];
        _hermite_arcs[_number_of_hermite_arcs - 1] = arc;

        _hermite_arcs[_selected_hermite_arc]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW);
        _hermite_arcs[_selected_secondary_arc]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW);

        _images_of_hermite_arcs[_selected_hermite_arc] = _hermite_arcs[_selected_hermite_arc]->GenerateImage(2,100,GL_STATIC_DRAW);
        _images_of_hermite_arcs[_selected_secondary_arc] = _hermite_arcs[_selected_secondary_arc]->GenerateImage(2,100,GL_STATIC_DRAW);

        _images_of_hermite_arcs[_selected_hermite_arc]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW);
        _images_of_hermite_arcs[_selected_secondary_arc]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW);

        _hermite_arcs[_number_of_hermite_arcs - 1]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW);
        _images_of_hermite_arcs[_number_of_hermite_arcs - 1] = _hermite_arcs[_number_of_hermite_arcs - 1]->GenerateImage(2,100,GL_STATIC_DRAW);
        _images_of_hermite_arcs[_number_of_hermite_arcs - 1]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW);

        for(GLint i = 0 ; i < _number_of_composite_arcs ; i++) {
            _composite_hermite_arcs[i]->updateArc(_selected_hermite_arc, _images_of_hermite_arcs[_selected_hermite_arc]);
            _composite_hermite_arcs[i]->updateArc(_selected_secondary_arc, _images_of_hermite_arcs[_selected_secondary_arc]);
        }

        _composite_hermite_arcs[_comp_index]->InsertNewArc(_hermite_arcs[_number_of_hermite_arcs - 1], _images_of_hermite_arcs[_number_of_hermite_arcs - 1], _r, _g, _b, _number_of_hermite_arcs - 1);
        _composite_hermite_arcs[_comp_index]->addNeighbour(_selected_hermite_arc, _primary_dir, _number_of_hermite_arcs - 1, 0);
        _composite_hermite_arcs[_comp_index]->addNeighbour(_number_of_hermite_arcs - 1, 1, _selected_secondary_arc, _secondary_dir);
        update();
    }

    void GLWidget::_mergeArc(){
        if(_composite_arc_index_of_hermite_arcs[_selected_hermite_arc] == -1) {
            return;
        }

        int _comp_index = _composite_arc_index_of_hermite_arcs[_selected_hermite_arc];
        if(!_composite_hermite_arcs[_comp_index]->MergeExistingArcs(_selected_hermite_arc, _primary_dir, _selected_secondary_arc, _secondary_dir)) {
            return;
        }


        _hermite_arcs[_selected_hermite_arc]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW);
        _hermite_arcs[_selected_secondary_arc]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW);

        _images_of_hermite_arcs[_selected_hermite_arc] = _hermite_arcs[_selected_hermite_arc]->GenerateImage(2,100,GL_STATIC_DRAW);
        _images_of_hermite_arcs[_selected_secondary_arc] = _hermite_arcs[_selected_secondary_arc]->GenerateImage(2,100,GL_STATIC_DRAW);

        _images_of_hermite_arcs[_selected_hermite_arc]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW);
        _images_of_hermite_arcs[_selected_secondary_arc]->UpdateVertexBufferObjects(1, GL_STATIC_DRAW);

        for(GLint i = 0 ; i < _number_of_composite_arcs ; i++) {
            _composite_hermite_arcs[i]->updateArc(_selected_hermite_arc, _images_of_hermite_arcs[_selected_hermite_arc]);
            _composite_hermite_arcs[i]->updateArc(_selected_secondary_arc, _images_of_hermite_arcs[_selected_secondary_arc]);
        }

        _composite_hermite_arcs[_comp_index]->addNeighbour(_selected_hermite_arc, _primary_dir, _selected_secondary_arc, _secondary_dir);
        update();
    }

    void GLWidget::_addSelectedArcToSelectedCompositeArc() {
        if(_valid_selected_composite_curve) {
            _composite_hermite_arcs[_selected_composite_arc]->InsertNewArc(_hermite_arcs[_selected_hermite_arc],_images_of_hermite_arcs[_selected_hermite_arc],_r,_g,_b,_selected_hermite_arc);
            _composite_arc_index_of_hermite_arcs[_selected_hermite_arc] = _selected_composite_arc;
        }
    }

    void GLWidget::_setSelectedHermiteArc(int index) {
        if(index < _number_of_hermite_arcs) {
            _selected_hermite_arc = index;
            for(GLuint i = 0 ; i < _number_of_composite_arcs ; i++) {
                _composite_hermite_arcs[i]->setSelected(_selected_hermite_arc);
            }

            DCoordinate3& cp = (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point];
            emit xHermitePointChanged(cp[0]);
            emit yHermitePointChanged(cp[1]);
            emit zHermitePointChanged(cp[2]);

            DCoordinate3& cp2 = (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point + 2];
            emit dxHermitePointChanged(cp2[0]);
            emit dyHermitePointChanged(cp2[1]);
            emit dzHermitePointChanged(cp2[2]);
        }
        update();
    }

    void GLWidget::_setSelectedSecondaryHermiteArc(int index) {
        if(index < _number_of_hermite_arcs) {
            _selected_secondary_arc = index;
            for(GLuint i = 0 ; i < _number_of_composite_arcs ; i++) {
                _composite_hermite_arcs[i]->setSelectedSecondary(_selected_secondary_arc);
            }

        }
        update();
    }


    void GLWidget::_updateArcNeighbours(DCoordinate3 corner, DCoordinate3 tangent) {
        int index = _composite_arc_index_of_hermite_arcs[_selected_hermite_arc];
        if(index != -1) {
            _composite_hermite_arcs[index]->updateNeighbours(_selected_hermite_arc, _selected_hermite_arc_point, corner, tangent);
            for(GLuint i = 0 ; i < _number_of_hermite_arcs ; i++) {
                if(_composite_arc_index_of_hermite_arcs[i] == index) {
                    _hermite_arcs[i]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW);
                    _images_of_hermite_arcs[i] = _hermite_arcs[i]->GenerateImage(1,30,GL_STATIC_DRAW);
                    _images_of_hermite_arcs[i]->UpdateVertexBufferObjects(1,GL_STATIC_DRAW);
                    _composite_hermite_arcs[index]->updateArc(i, _images_of_hermite_arcs[i]);
                }
            }
        }
    }

    void GLWidget::_setPrimaryDirection(int index) {
        _primary_dir = index;
    }
    void GLWidget::_setSecondaryDirection(int index) {
        _secondary_dir = index;
    }
    void GLWidget::_setSecondarySelectedArc(int index) {
        _selected_secondary_arc = index;
    }

    void GLWidget::setHermitePointIndex(int value){

         _selected_hermite_arc_point = value;

         DCoordinate3& cp = (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point];
         emit xHermitePointChanged(cp[0]);
         emit yHermitePointChanged(cp[1]);
         emit zHermitePointChanged(cp[2]);

         DCoordinate3& cp2 = (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point + 2];
         emit dxHermitePointChanged(cp2[0]);
         emit dyHermitePointChanged(cp2[1]);
         emit dzHermitePointChanged(cp2[2]);

    }
    void GLWidget::setHermitePointx(double value){
        DCoordinate3 corner = _hermite_arcs[_selected_hermite_arc]->GetCorner(_selected_hermite_arc_point);
        DCoordinate3 tangent(0,0,0);
       (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point][0] = value;
        corner -= _hermite_arcs[_selected_hermite_arc]->GetCorner(_selected_hermite_arc_point);
        _updateSelectedHermiteArc();
        _updateArcNeighbours(corner, tangent);
        update();
   }

   void GLWidget::setHermitePointy(double value){
       DCoordinate3 corner = _hermite_arcs[_selected_hermite_arc]->GetCorner(_selected_hermite_arc_point);
       DCoordinate3 tangent(0,0,0);
       (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point][1] = value;
       corner -= _hermite_arcs[_selected_hermite_arc]->GetCorner(_selected_hermite_arc_point);
       _updateSelectedHermiteArc();
       _updateArcNeighbours(corner, tangent);
       update();
   }

   void GLWidget::setHermitePointz(double value){
       DCoordinate3 corner = _hermite_arcs[_selected_hermite_arc]->GetCorner(_selected_hermite_arc_point);
       DCoordinate3 tangent(0,0,0);
       (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point][2] = value;
       corner -= _hermite_arcs[_selected_hermite_arc]->GetCorner(_selected_hermite_arc_point);
       _updateSelectedHermiteArc();
       _updateArcNeighbours(corner, tangent);
       update();
   }

   void GLWidget::setHermitePointdx(double value){
       DCoordinate3 tangent = _hermite_arcs[_selected_hermite_arc]->GetTangent(_selected_hermite_arc_point);
       DCoordinate3 corner(0,0,0);
      (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point + 2][0] = value;
       tangent -= _hermite_arcs[_selected_hermite_arc]->GetTangent(_selected_hermite_arc_point);
       _updateSelectedHermiteArc();
       _updateArcNeighbours(corner, tangent);
       update();
  }

  void GLWidget::setHermitePointdy(double value){
      DCoordinate3 tangent = _hermite_arcs[_selected_hermite_arc]->GetTangent(_selected_hermite_arc_point);
      DCoordinate3 corner(0,0,0);
      (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point + 2][1] = value;
      tangent -= _hermite_arcs[_selected_hermite_arc]->GetTangent(_selected_hermite_arc_point);
      _updateSelectedHermiteArc();
      _updateArcNeighbours(corner, tangent);
      update();
  }

  void GLWidget::setHermitePointdz(double value){
      DCoordinate3 tangent = _hermite_arcs[_selected_hermite_arc]->GetTangent(_selected_hermite_arc_point);
      DCoordinate3 corner(0,0,0);
      (*_hermite_arcs[_selected_hermite_arc])[_selected_hermite_arc_point + 2][2] = value;
      tangent -= _hermite_arcs[_selected_hermite_arc]->GetTangent(_selected_hermite_arc_point);
      _updateSelectedHermiteArc();
      _updateArcNeighbours(corner, tangent);
      update();
  }

   void GLWidget::showHermiteFirstOrderDerivates(bool visibility) {
        _show_hermite_first_order = visibility;
        for(GLuint i = 0 ; i < _number_of_composite_arcs ; i++) {
            _composite_hermite_arcs[i]->setFirstOrderVisibility(_show_hermite_first_order);
        }
        update();
   }

   void GLWidget::showHermiteSecondOrderDerivates(bool visibility) {
        _show_hermite_second_order = visibility;
        for(GLuint i = 0 ; i < _number_of_composite_arcs ; i++) {
            _composite_hermite_arcs[i]->setSecondOrderVisibility(_show_hermite_second_order);
        }
        update();
   }

   void GLWidget::_createNewCompositeArc() {
       _number_of_composite_arcs += 1;
       _valid_selected_composite_curve = true;
       _composite_hermite_arcs.ResizeColumns(_number_of_hermite_arcs);
       _composite_hermite_arcs[_number_of_composite_arcs - 1] = new HermiteCompositeCurve3(_number_of_composite_arcs - 1);
       _composite_hermite_arcs[_number_of_composite_arcs - 1]->setFirstOrderVisibility(_show_hermite_first_order);
       _composite_hermite_arcs[_number_of_composite_arcs - 1]->setSecondOrderVisibility(_show_hermite_second_order);
       _composite_hermite_arcs[_number_of_composite_arcs - 1]->highlightSelectedComposite(_highlight_selected_composite_curve);
       _composite_hermite_arcs[_number_of_composite_arcs - 1]->setSelected(_selected_hermite_arc);
       _composite_hermite_arcs[_number_of_composite_arcs - 1]->setSelectedComposite(_selected_composite_arc);
       _composite_hermite_arcs[_number_of_composite_arcs - 1]->setSelectedSecondary(_selected_secondary_arc);
   }
   void GLWidget::_highlightHermiteCompositeArc(bool visibility) {
        _highlight_selected_composite_curve = visibility;
        for(GLuint i = 0 ; i < _number_of_composite_arcs ; i++) {
            _composite_hermite_arcs[i]->highlightSelectedComposite(_highlight_selected_composite_curve);
        }
        update();
   }
   void GLWidget::_setSelectedCompositeArc(int index) {
        if(index < _number_of_composite_arcs) {
            _selected_composite_arc = index;
            _valid_selected_composite_curve = true;
            for(GLuint i = 0 ; i < _number_of_composite_arcs ; i++) {
                _composite_hermite_arcs[i]->setSelectedComposite(_selected_composite_arc);
            }
        } else {
            _selected_composite_arc = index;
            _valid_selected_composite_curve = false;
        }
        update();
   }


   void GLWidget::_hermite_red(double value) {
       _r = value;
   }
   void GLWidget::_hermite_green(double value) {
       _g = value;
   }
   void GLWidget::_hermite_blue(double value) {
       _b = value;
   }


    // Hermite Patches
   void GLWidget::_continuePatch(){
        if(_composite_patch_index_of_hermite_patches[_selected_hermite_patch] == -1) {
           return;
       }

       int _comp_index = _composite_patch_index_of_hermite_patches[_selected_hermite_patch];
       BicubicHermitePatch3* patch = _composite_hermite_patches[_comp_index]->ContinueExistingPatch(_selected_hermite_patch, _primary_patch_dir);
       if(patch == nullptr)
           return;

       _number_of_hermite_patches += 1;
       _hermite_patches.ResizeColumns(_number_of_hermite_patches);
       _images_of_hermite_patches.ResizeColumns(_number_of_hermite_patches);
       _composite_patch_index_of_hermite_patches.ResizeColumns(_number_of_hermite_patches);
       _patches_u_lines.ResizeColumns(_number_of_hermite_patches);
       _patches_v_lines.ResizeColumns(_number_of_hermite_patches);

       _composite_patch_index_of_hermite_patches[_number_of_hermite_patches -1] = _composite_patch_index_of_hermite_patches[_selected_hermite_patch];
       _hermite_patches[_number_of_hermite_patches - 1] = patch;
       _hermite_patches[_number_of_hermite_patches - 1]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW);

       _images_of_hermite_patches[_number_of_hermite_patches - 1] = _hermite_patches[_number_of_hermite_patches - 1]->GenerateImage(30, 30,GL_STATIC_DRAW);
       _images_of_hermite_patches[_number_of_hermite_patches - 1]->UpdateVertexBufferObjects(GL_STATIC_DRAW);

       _u_lines = _hermite_patches[_number_of_hermite_patches - 1]->GenerateUIsoparametricLines(10, 2, 30);
       for(GLuint i = 0 ; i < _u_lines->GetColumnCount(); i++) {
           if((*_u_lines)[i]) {
               (*_u_lines)[i]->UpdateVertexBufferObjects(0.1,GL_STATIC_DRAW);
           }
       }
       _patches_u_lines[_number_of_hermite_patches - 1] = _u_lines;

       _v_lines = _hermite_patches[_number_of_hermite_patches - 1]->GenerateVIsoparametricLines(10, 2, 30);
       for(GLuint i = 0 ; i < _v_lines->GetColumnCount(); i++) {
           if((*_v_lines)[i]) {
               (*_v_lines)[i]->UpdateVertexBufferObjects(0.1,GL_STATIC_DRAW);
           }
       }
       _patches_v_lines[_number_of_hermite_patches - 1] = _v_lines;

       _composite_hermite_patches[_comp_index]->InsertNewPatch(patch,  _images_of_hermite_patches[_number_of_hermite_patches - 1], &_materials[_selected_patch_material], _texture[_selected_patch_texture], &_shaders[_selected_patch_shader], _number_of_hermite_patches - 1);
//       _composite_hermite_patches[_comp_index]->addNeighbourContinue();
       update();

        return;
   }
   void GLWidget::_joinPatch(){
        return;
   }
   void GLWidget::_mergePatch(){
        return;
   }



    bool GLWidget::_initializeHermitePatches() {
        ifstream fin("Hermite/HermitePatches.txt");

        fin >> _number_of_hermite_patches;
        _hermite_patches.ResizeColumns(_number_of_hermite_patches);
        _images_of_hermite_patches.ResizeColumns(_number_of_hermite_patches);
        _composite_patch_index_of_hermite_patches.ResizeColumns(_number_of_hermite_patches);
        _patches_u_lines.ResizeColumns(_number_of_hermite_patches);
        _patches_v_lines.ResizeColumns(_number_of_hermite_patches);

        for(GLuint i = 0 ; i < _number_of_hermite_patches ; i++) {
            _hermite_patches[i] = new BicubicHermitePatch3();
            _images_of_hermite_patches[i] = new TriangulatedMesh3();
            _composite_patch_index_of_hermite_patches[i] = -1;
            fin >> *_hermite_patches[i];

            if ( !_hermite_patches[i]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW)) {
                for (GLuint j = 0 ; j < i ; j++) {
                    delete _hermite_patches[j];
                    _hermite_patches[j] = nullptr;
                    delete _images_of_hermite_patches[j];
                    _images_of_hermite_patches[j] = nullptr;
                }
                return false;
            }

            _images_of_hermite_patches[i] = _hermite_patches[i]->GenerateImage(30, 30, GL_STATIC_DRAW);
            if ( !_images_of_hermite_patches[i]) {
                for (GLuint j = 0 ; j < i ; j++) {
                    delete _hermite_patches[j];
                    _hermite_patches[j] = nullptr;
                    delete _images_of_hermite_patches[j];
                    _images_of_hermite_patches[j] = nullptr;
                }
                return false;
            }

            if (!_images_of_hermite_patches[i]->UpdateVertexBufferObjects(GL_STATIC_DRAW)) {
                for (GLuint j = 0 ; j < i ; j++) {
                    delete _hermite_patches[j];
                    _hermite_patches[j] = nullptr;
                    delete _images_of_hermite_patches[j];
                    _images_of_hermite_patches[j] = nullptr;
                }
                return false;
            }

            _u_lines = _hermite_patches[i]->GenerateUIsoparametricLines(10, 2, 30);
            for(GLuint i = 0 ; i < _u_lines->GetColumnCount(); i++) {
                if((*_u_lines)[i]) {
                    (*_u_lines)[i]->UpdateVertexBufferObjects(0.1,GL_STATIC_DRAW);
                }
            }
            _patches_u_lines[i] = _u_lines;

            _v_lines = _hermite_patches[i]->GenerateVIsoparametricLines(10, 2, 30);
            for(GLuint i = 0 ; i < _v_lines->GetColumnCount(); i++) {
                if((*_v_lines)[i]) {
                    (*_v_lines)[i]->UpdateVertexBufferObjects(0.1,GL_STATIC_DRAW);
                }
            }
            _patches_v_lines[i] = _v_lines;
        }

        return true;
    }

    bool GLWidget::_renderHermitePatches() {
        _dl->Enable();
            glEnable(GL_LIGHTING);
            glEnable(GL_NORMALIZE);
            glEnable(GL_TEXTURE_2D);

                for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
                    _composite_hermite_patches[i]->RenderAllPatches();
                }

                _materials[0].Apply();
                for(GLuint i = 0 ; i < _number_of_hermite_patches ; i++) {
                    if(_composite_patch_index_of_hermite_patches[i] == -1)
                    {

                        _images_of_hermite_patches[i]->Render();

                        if (_show_u_lines && _selected_hermite_patch == i) {
                            for(GLuint j = 0; j < _patches_u_lines[i]->GetColumnCount(); j++)
                            {
                                if((*_patches_u_lines[i])[j])
                                {
                                    (*_patches_u_lines[i])[j]->RenderDerivatives(0, GL_LINE_STRIP);
                                }
                            }
                        }

                        if (_show_v_lines && _selected_hermite_patch == i) {
                            for(GLuint j = 0; j < _patches_v_lines[i]->GetColumnCount(); j++)
                            {
                                if((*_patches_v_lines[i])[j])
                                {
                                    (*_patches_v_lines[i])[j]->RenderDerivatives(0, GL_LINE_STRIP);
                                }
                            }
                        }

                        if(_show_first_order_derivates && _selected_hermite_patch == i){
                           glColor3f(0.0f, 1.0f, 0.0f);
                           for(GLuint j = 0; j < _patches_u_lines[i]->GetColumnCount(); j++)
                           {
                               glPointSize(1.0f);
                               glColor3f(0.0f, 1.0f, 0.0f);

                               if((*_patches_u_lines[i])[j])
                               {
                                   (*_patches_u_lines[i])[j]->RenderDerivatives(1, GL_POINTS);
                                   (*_patches_u_lines[i])[j]->RenderDerivatives(1, GL_LINES);
                               }
                           }

                           for(GLuint j = 0; j < _patches_v_lines[i]->GetColumnCount(); j++)
                           {
                               glPointSize(1.0f);
                               glColor3f(0.0f, 1.0f, 0.0f);

                               if((*_patches_v_lines[i])[j])
                               {
                                   (*_patches_v_lines[i])[j]->RenderDerivatives(1, GL_POINTS);
                                   (*_patches_v_lines[i])[j]->RenderDerivatives(1, GL_LINES);
                               }
                           }
                       }

                        if(_show_second_order_derivates && _selected_hermite_patch == i){
                           glColor3f(0.0f, 1.0f, 0.0f);
                           for(GLuint j = 0; j < _patches_u_lines[i]->GetColumnCount(); j++)
                           {
                               glPointSize(1.0f);
                               glColor3f(0.0f, 1.0f, 0.0f);

                               if((*_patches_u_lines[i])[j])
                               {
                                   (*_patches_u_lines[i])[j]->RenderDerivatives(2, GL_POINTS);
                                   (*_patches_u_lines[i])[j]->RenderDerivatives(2, GL_LINES);
                               }
                           }

                           for(GLuint j = 0; j < _patches_v_lines[i]->GetColumnCount(); j++)
                           {
                               glPointSize(1.0f);
                               glColor3f(0.0f, 1.0f, 0.0f);

                               if((*_patches_v_lines[i])[j])
                               {
                                   (*_patches_v_lines[i])[j]->RenderDerivatives(2, GL_POINTS);
                                   (*_patches_v_lines[i])[j]->RenderDerivatives(2, GL_LINES);
                               }
                           }
                       }
                    }
                }


            glDisable(GL_TEXTURE_2D);
            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHTING);
        _dl->Disable();
        return true;
    }

    bool GLWidget::_updateSelectedHermitePatch() {
        if ( !_hermite_patches[_selected_hermite_patch]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW)) {
            for (GLuint j = 0 ; j < _number_of_hermite_patches ; j++) {
                delete _hermite_patches[j];
                _hermite_patches[j] = nullptr;
                delete _images_of_hermite_patches[j];
                _images_of_hermite_patches[j] = nullptr;
            }
            return false;
        }

        _images_of_hermite_patches[_selected_hermite_patch] = _hermite_patches[_selected_hermite_patch]->GenerateImage(30, 30, GL_STATIC_DRAW);
        if ( !_images_of_hermite_patches[_selected_hermite_patch]) {
            for (GLuint j = 0 ; j < _number_of_hermite_patches ; j++) {
                delete _hermite_patches[j];
                _hermite_patches[j] = nullptr;
                delete _images_of_hermite_patches[j];
                _images_of_hermite_patches[j] = nullptr;
            }
            return false;
        }

        if (!_images_of_hermite_patches[_selected_hermite_patch]->UpdateVertexBufferObjects(GL_STATIC_DRAW)) {
            for (GLuint j = 0 ; j < _number_of_hermite_patches ; j++) {
                delete _hermite_patches[j];
                _hermite_patches[j] = nullptr;
                delete _images_of_hermite_patches[j];
                _images_of_hermite_patches[j] = nullptr;
            }
            return false;
        }

        _u_lines = _hermite_patches[_selected_hermite_patch]->GenerateUIsoparametricLines(10, 2, 30);
        for(GLuint i = 0 ; i < _u_lines->GetColumnCount(); i++) {
            if((*_u_lines)[i]) {
                (*_u_lines)[i]->UpdateVertexBufferObjects(0.1,GL_STATIC_DRAW);
            }
        }
        _patches_u_lines[_selected_hermite_patch] = _u_lines;

        _v_lines = _hermite_patches[_selected_hermite_patch]->GenerateVIsoparametricLines(10, 2, 30);
        for(GLuint i = 0 ; i < _v_lines->GetColumnCount(); i++) {
            if((*_v_lines)[i]) {
                (*_v_lines)[i]->UpdateVertexBufferObjects(0.1,GL_STATIC_DRAW);
            }
        }
        _patches_v_lines[_selected_hermite_patch] = _v_lines;

        for(GLint i = 0 ; i < _number_of_composite_patches ; i++) {
            if(i == _selected_composite_patch) {
                _composite_hermite_patches[i]->updatePatch(_selected_hermite_patch, _images_of_hermite_patches[_selected_hermite_patch]);
                _composite_hermite_patches[i]->updatePatch(_selected_secondary_patch, _images_of_hermite_patches[_selected_secondary_patch]);
            }
        }
        return true;
    }

    void GLWidget::_createNewCompositePatch() {
        _number_of_composite_patches += 1;
        _valid_selected_composite_patch = true;
        _composite_hermite_patches.ResizeColumns(_number_of_composite_patches);
        HermiteCompositeSurface3* surface = new HermiteCompositeSurface3(_number_of_composite_patches - 1);
        surface->setSelectedPatch(_selected_hermite_patch);
        surface->setSelectedCompositePatch(_selected_composite_patch);
        surface->showFirstOrder(_show_first_order_derivates);
        surface->showSecondOrder(_show_second_order_derivates);
        surface->showShaders(_use_shaders);
        surface->showTextures(_use_textures);
        surface->showULines(_show_u_lines);
        surface->showVLines(_show_v_lines);
        surface->hightlightSelected(_highlight_selected_composite_patch);
        _composite_hermite_patches[_number_of_composite_patches - 1] = surface;
    }

    void GLWidget::_addSelectedPatchToSelectedCompositePatch() {
        if(_valid_selected_composite_patch) {
            Material* mat = &_materials[_selected_patch_material];
            QOpenGLTexture* texture = _texture[_selected_patch_texture];
            ShaderProgram* shader = &_shaders[_selected_patch_shader];
            BicubicHermitePatch3* patch = _hermite_patches[_selected_hermite_patch];
            TriangulatedMesh3* image = _images_of_hermite_patches[_selected_hermite_patch];
            _composite_hermite_patches[_selected_composite_patch]->InsertNewPatch(patch, image, mat, texture, shader, _selected_hermite_patch);
            _composite_patch_index_of_hermite_patches[_selected_hermite_patch] = _selected_composite_patch;
        }
    }

    void GLWidget::_setHermitePatchMaterial(int index){
         _selected_patch_material = index;
    }

    void GLWidget::_setHermitePatchTexture(int index){
         _selected_patch_texture = index;
    }

    void GLWidget::_setHermitePatchShader(int index){
         _selected_patch_shader = index;
    }

    void GLWidget::_showHermitePatchTextures(bool visibility){
         _use_textures = visibility;
         for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
            _composite_hermite_patches[i]->showTextures(visibility);
         }
         update();
    }

    void GLWidget::_showHermitePatchShaders(bool visibility){
         _use_shaders = visibility;
         for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
            _composite_hermite_patches[i]->showShaders(visibility);
         }
         update();
    }

    void GLWidget::_setSelectedSecondaryHermitePatch(int index) {
        if (index < _number_of_hermite_patches) {
            _selected_secondary_patch = index;
        }
        update();
    }

    void GLWidget::_setVisibilityOfULines(bool visibility) {
        _show_u_lines = visibility;
        for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
           _composite_hermite_patches[i]->showULines(visibility);
        }
        update();
    }

    void GLWidget::_setVisibilityOfVLines(bool visibility) {
        _show_v_lines = visibility;
        for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
           _composite_hermite_patches[i]->showVLines(visibility);
        }
        update();
    }

    void GLWidget::_highlightSelectedCompositePatch(bool visibility) {
        _highlight_selected_composite_patch = visibility;
        for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
           _composite_hermite_patches[i]->hightlightSelected(visibility);
        }
        update();
    }

    void GLWidget::_setVisibilityOfFirstOrderDerivatives(bool visibility) {
        _show_first_order_derivates = visibility;
        for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
           _composite_hermite_patches[i]->showFirstOrder(visibility);
        }
        update();
    }

    void GLWidget::_setVisibilityOfSecondOrderDerivatives(bool visibility){
        _show_second_order_derivates = visibility;
        for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
           _composite_hermite_patches[i]->showSecondOrder(visibility);
        }
        update();
    }

    void GLWidget::_setSelectedHermitePatch(int index) {
        if(index < _number_of_hermite_patches) {
            _selected_hermite_patch = index;
            for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
                _composite_hermite_patches[i]->setSelectedPatch(index);
             }

            switch(_selected_hermite_patch_point)
            {
                 case 0:
                {
                    emit HermitePatchPointChangeX((*_hermite_patches[_selected_hermite_patch])(0,0).x());
                    emit HermitePatchPointChangeY((*_hermite_patches[_selected_hermite_patch])(0,0).y());
                    emit HermitePatchPointChangeZ((*_hermite_patches[_selected_hermite_patch])(0,0).z());

                    emit HermitePatchPointChangeVX((*_hermite_patches[_selected_hermite_patch])(2,0).x());
                    emit HermitePatchPointChangeVY((*_hermite_patches[_selected_hermite_patch])(2,0).y());
                    emit HermitePatchPointChangeVZ((*_hermite_patches[_selected_hermite_patch])(2,0).z());

                    emit HermitePatchPointChangeUX((*_hermite_patches[_selected_hermite_patch])(0,2).x());
                    emit HermitePatchPointChangeUY((*_hermite_patches[_selected_hermite_patch])(0,2).y());
                    emit HermitePatchPointChangeUZ((*_hermite_patches[_selected_hermite_patch])(0,2).z());

                    emit HermitePatchPointChangeTX((*_hermite_patches[_selected_hermite_patch])(2,2).x());
                    emit HermitePatchPointChangeTY((*_hermite_patches[_selected_hermite_patch])(2,2).y());
                    emit HermitePatchPointChangeTZ((*_hermite_patches[_selected_hermite_patch])(2,2).z());
                    break;
                }
                 case 1:
                {

                    emit HermitePatchPointChangeX((*_hermite_patches[_selected_hermite_patch])(0,1).x());
                    emit HermitePatchPointChangeY((*_hermite_patches[_selected_hermite_patch])(0,1).y());
                    emit HermitePatchPointChangeZ((*_hermite_patches[_selected_hermite_patch])(0,1).z());

                    emit HermitePatchPointChangeVX((*_hermite_patches[_selected_hermite_patch])(2,1).x());
                    emit HermitePatchPointChangeVY((*_hermite_patches[_selected_hermite_patch])(2,1).y());
                    emit HermitePatchPointChangeVZ((*_hermite_patches[_selected_hermite_patch])(2,1).z());

                    emit HermitePatchPointChangeUX((*_hermite_patches[_selected_hermite_patch])(0,3).x());
                    emit HermitePatchPointChangeUY((*_hermite_patches[_selected_hermite_patch])(0,3).y());
                    emit HermitePatchPointChangeUZ((*_hermite_patches[_selected_hermite_patch])(0,3).z());

                    emit HermitePatchPointChangeTX((*_hermite_patches[_selected_hermite_patch])(2,3).x());
                    emit HermitePatchPointChangeTY((*_hermite_patches[_selected_hermite_patch])(2,3).y());
                    emit HermitePatchPointChangeTZ((*_hermite_patches[_selected_hermite_patch])(2,3).z());
                    break;
                }

                case 2:
               {

                   emit HermitePatchPointChangeX((*_hermite_patches[_selected_hermite_patch])(1,0).x());
                   emit HermitePatchPointChangeY((*_hermite_patches[_selected_hermite_patch])(1,0).y());
                   emit HermitePatchPointChangeZ((*_hermite_patches[_selected_hermite_patch])(1,0).z());

                   emit HermitePatchPointChangeVX((*_hermite_patches[_selected_hermite_patch])(3,0).x());
                   emit HermitePatchPointChangeVY((*_hermite_patches[_selected_hermite_patch])(3,0).y());
                   emit HermitePatchPointChangeVZ((*_hermite_patches[_selected_hermite_patch])(3,0).z());

                   emit HermitePatchPointChangeUX((*_hermite_patches[_selected_hermite_patch])(1,2).x());
                   emit HermitePatchPointChangeUY((*_hermite_patches[_selected_hermite_patch])(1,2).y());
                   emit HermitePatchPointChangeUZ((*_hermite_patches[_selected_hermite_patch])(1,2).z());

                   emit HermitePatchPointChangeTX((*_hermite_patches[_selected_hermite_patch])(3,2).x());
                   emit HermitePatchPointChangeTY((*_hermite_patches[_selected_hermite_patch])(3,2).y());
                   emit HermitePatchPointChangeTZ((*_hermite_patches[_selected_hermite_patch])(3,2).z());
                   break;
               }

                case 3:
               {

                   emit HermitePatchPointChangeX((*_hermite_patches[_selected_hermite_patch])(1,1).x());
                   emit HermitePatchPointChangeY((*_hermite_patches[_selected_hermite_patch])(1,1).y());
                   emit HermitePatchPointChangeZ((*_hermite_patches[_selected_hermite_patch])(1,1).z());

                   emit HermitePatchPointChangeVX((*_hermite_patches[_selected_hermite_patch])(3,1).x());
                   emit HermitePatchPointChangeVY((*_hermite_patches[_selected_hermite_patch])(3,1).y());
                   emit HermitePatchPointChangeVZ((*_hermite_patches[_selected_hermite_patch])(3,1).z());

                   emit HermitePatchPointChangeUX((*_hermite_patches[_selected_hermite_patch])(1,3).x());
                   emit HermitePatchPointChangeUY((*_hermite_patches[_selected_hermite_patch])(1,3).y());
                   emit HermitePatchPointChangeUZ((*_hermite_patches[_selected_hermite_patch])(1,3).z());

                   emit HermitePatchPointChangeTX((*_hermite_patches[_selected_hermite_patch])(3,3).x());
                   emit HermitePatchPointChangeTY((*_hermite_patches[_selected_hermite_patch])(3,3).y());
                   emit HermitePatchPointChangeTZ((*_hermite_patches[_selected_hermite_patch])(3,3).z());
                   break;
               }
            }
        }


        update();
    }


    void GLWidget::_selectCompositePatch(int index) {
        if(index < _number_of_composite_patches) {
            _selected_composite_patch = index;
            for(GLuint i = 0 ; i < _number_of_composite_patches ; i++) {
                _composite_hermite_patches[i]->setSelectedCompositePatch(index);
             }
            _valid_selected_composite_patch = true;
        } else {
            _valid_selected_composite_patch = false;
        }
    }

    void GLWidget::_setSelectedHermitePatchPoint(int index) {
        _selected_hermite_patch_point = index;

        switch(_selected_hermite_patch_point)
        {
             case 0:
            {
                emit HermitePatchPointChangeX((*_hermite_patches[_selected_hermite_patch])(0,0).x());
                emit HermitePatchPointChangeY((*_hermite_patches[_selected_hermite_patch])(0,0).y());
                emit HermitePatchPointChangeZ((*_hermite_patches[_selected_hermite_patch])(0,0).z());

                emit HermitePatchPointChangeUX((*_hermite_patches[_selected_hermite_patch])(2,0).x());
                emit HermitePatchPointChangeUY((*_hermite_patches[_selected_hermite_patch])(2,0).y());
                emit HermitePatchPointChangeUZ((*_hermite_patches[_selected_hermite_patch])(2,0).z());

                emit HermitePatchPointChangeVX((*_hermite_patches[_selected_hermite_patch])(0,2).x());
                emit HermitePatchPointChangeVY((*_hermite_patches[_selected_hermite_patch])(0,2).y());
                emit HermitePatchPointChangeVZ((*_hermite_patches[_selected_hermite_patch])(0,2).z());

                emit HermitePatchPointChangeTX((*_hermite_patches[_selected_hermite_patch])(2,2).x());
                emit HermitePatchPointChangeTY((*_hermite_patches[_selected_hermite_patch])(2,2).y());
                emit HermitePatchPointChangeTZ((*_hermite_patches[_selected_hermite_patch])(2,2).z());
                break;
            }
             case 1:
            {

                emit HermitePatchPointChangeX((*_hermite_patches[_selected_hermite_patch])(0,1).x());
                emit HermitePatchPointChangeY((*_hermite_patches[_selected_hermite_patch])(0,1).y());
                emit HermitePatchPointChangeZ((*_hermite_patches[_selected_hermite_patch])(0,1).z());

                emit HermitePatchPointChangeUX((*_hermite_patches[_selected_hermite_patch])(2,1).x());
                emit HermitePatchPointChangeUY((*_hermite_patches[_selected_hermite_patch])(2,1).y());
                emit HermitePatchPointChangeUZ((*_hermite_patches[_selected_hermite_patch])(2,1).z());

                emit HermitePatchPointChangeVX((*_hermite_patches[_selected_hermite_patch])(0,3).x());
                emit HermitePatchPointChangeVY((*_hermite_patches[_selected_hermite_patch])(0,3).y());
                emit HermitePatchPointChangeVZ((*_hermite_patches[_selected_hermite_patch])(0,3).z());

                emit HermitePatchPointChangeTX((*_hermite_patches[_selected_hermite_patch])(2,3).x());
                emit HermitePatchPointChangeTY((*_hermite_patches[_selected_hermite_patch])(2,3).y());
                emit HermitePatchPointChangeTZ((*_hermite_patches[_selected_hermite_patch])(2,3).z());
                break;
            }

            case 2:
           {

               emit HermitePatchPointChangeX((*_hermite_patches[_selected_hermite_patch])(1,0).x());
               emit HermitePatchPointChangeY((*_hermite_patches[_selected_hermite_patch])(1,0).y());
               emit HermitePatchPointChangeZ((*_hermite_patches[_selected_hermite_patch])(1,0).z());

               emit HermitePatchPointChangeUX((*_hermite_patches[_selected_hermite_patch])(3,0).x());
               emit HermitePatchPointChangeUY((*_hermite_patches[_selected_hermite_patch])(3,0).y());
               emit HermitePatchPointChangeUZ((*_hermite_patches[_selected_hermite_patch])(3,0).z());

               emit HermitePatchPointChangeVX((*_hermite_patches[_selected_hermite_patch])(1,2).x());
               emit HermitePatchPointChangeVY((*_hermite_patches[_selected_hermite_patch])(1,2).y());
               emit HermitePatchPointChangeVZ((*_hermite_patches[_selected_hermite_patch])(1,2).z());

               emit HermitePatchPointChangeTX((*_hermite_patches[_selected_hermite_patch])(3,2).x());
               emit HermitePatchPointChangeTY((*_hermite_patches[_selected_hermite_patch])(3,2).y());
               emit HermitePatchPointChangeTZ((*_hermite_patches[_selected_hermite_patch])(3,2).z());
               break;
           }

            case 3:
           {

               emit HermitePatchPointChangeX((*_hermite_patches[_selected_hermite_patch])(1,1).x());
               emit HermitePatchPointChangeY((*_hermite_patches[_selected_hermite_patch])(1,1).y());
               emit HermitePatchPointChangeZ((*_hermite_patches[_selected_hermite_patch])(1,1).z());

               emit HermitePatchPointChangeUX((*_hermite_patches[_selected_hermite_patch])(3,1).x());
               emit HermitePatchPointChangeUY((*_hermite_patches[_selected_hermite_patch])(3,1).y());
               emit HermitePatchPointChangeUZ((*_hermite_patches[_selected_hermite_patch])(3,1).z());

               emit HermitePatchPointChangeVX((*_hermite_patches[_selected_hermite_patch])(1,3).x());
               emit HermitePatchPointChangeVY((*_hermite_patches[_selected_hermite_patch])(1,3).y());
               emit HermitePatchPointChangeVZ((*_hermite_patches[_selected_hermite_patch])(1,3).z());

               emit HermitePatchPointChangeTX((*_hermite_patches[_selected_hermite_patch])(3,3).x());
               emit HermitePatchPointChangeTY((*_hermite_patches[_selected_hermite_patch])(3,3).y());
               emit HermitePatchPointChangeTZ((*_hermite_patches[_selected_hermite_patch])(3,3).z());
               break;
           }
        }
    }

    void GLWidget::setHermitePatchPointX(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,0)[0] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,1)[0] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,0)[0] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,1)[0] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointY(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,0)[1] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,1)[1] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,0)[1] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,1)[1] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointZ(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,0)[2] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,1)[2] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,0)[2] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,1)[2] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }


    void GLWidget::setHermitePatchPointUX(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,0)[0] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,1)[0] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,0)[0] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,1)[0] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointUY(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,0)[1] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,1)[1] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,0)[1] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,1)[1] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointUZ(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,0)[2] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,1)[2] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,0)[2] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,1)[2] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }


    void GLWidget::setHermitePatchPointVX(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,2)[0] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,3)[0] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,2)[0] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,3)[0] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointVY(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,2)[1] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,3)[1] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,2)[1] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,3)[1] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointVZ(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,2)[2] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(0,3)[2] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,2)[2] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(1,3)[2] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointTX(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,2)[0] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,3)[0] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,2)[0] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,3)[0] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointTY(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,2)[1] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,3)[1] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,2)[1] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,3)[1] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }

    void GLWidget::setHermitePatchPointTZ(double value) {
         switch(_selected_hermite_patch_point) {
         case 0:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,2)[2] = value;
             break;
         }
         case 1:
         {
             (*_hermite_patches[_selected_hermite_patch])(2,3)[2] = value;
             break;
         }
         case 2:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,2)[2] = value;
             break;
         }
         case 3:
         {
             (*_hermite_patches[_selected_hermite_patch])(3,3)[2] = value;
             break;
         }
     }
         _updateSelectedHermitePatch();
         update();
    }
    // PROJECT ONLY

    void GLWidget::updateHermitePatch() {
        GLenum usage_flag = GL_STATIC_DRAW;

        ColumnMatrix<GLdouble> v_knot_vector;
        RowMatrix<GLdouble>  u_knot_vector;

        _bicubic_hermite_patch3->UpdateVertexBufferObjectsOfData();
        _before_interpolation = nullptr;

        _before_interpolation = _bicubic_hermite_patch3->GenerateImage(30, 30, GL_STATIC_DRAW);
        if(!_before_interpolation) {
            throw Exception("Couldn't update image of bicubic hermite patch");
        }
        if(!_before_interpolation->UpdateVertexBufferObjects()) {
            throw Exception("Couldn't update vbo of image of bicubic hermite patch");
        }

        for(GLuint i = 0 ; i < _u_lines->GetColumnCount(); i++) {
            if((*_u_lines)[i]) {
                (*_u_lines)[i] = nullptr;
            }
        }
        _u_lines = _bicubic_hermite_patch3->GenerateUIsoparametricLines(4, 2, 30);
        for(GLuint i = 0 ; i < _u_lines->GetColumnCount(); i++) {
            if((*_u_lines)[i]) {
                (*_u_lines)[i]->UpdateVertexBufferObjects(0.5,GL_STATIC_DRAW);
            }
        }

        for(GLuint i = 0 ; i < _v_lines->GetColumnCount(); i++) {
            if((*_v_lines)[i]) {
                (*_v_lines)[i] = nullptr;
            }
        }
        _v_lines = _bicubic_hermite_patch3->GenerateVIsoparametricLines(4, 2, 30);
        for(GLuint i = 0 ; i < _v_lines->GetColumnCount(); i++) {
            if((*_v_lines)[i]) {
                (*_v_lines)[i]->UpdateVertexBufferObjects(0.5,GL_STATIC_DRAW);
            }
        }

        Matrix<DCoordinate3> _data_points_to_interpolate;

        u_knot_vector.ResizeColumns(4);
        v_knot_vector.ResizeRows(4);

        GLdouble pointValue = 0;
        GLdouble step = 1.0 / 3.0;

        for (GLuint i = 0 ; i <= 3; i++) {
            u_knot_vector[i] = pointValue;
            v_knot_vector[i] = pointValue;
            pointValue += step;
        }

        GLdouble x_min = -2.0, x_max = 2.0;
        GLdouble y_min = -3.0, y_max = 3.0;

        GLdouble dx = (x_max - x_min) / 3.0;
        GLdouble dy = (y_max - y_min) / 3.0;

        _data_points_to_interpolate.ResizeRows(4);
        _data_points_to_interpolate.ResizeColumns(4);


        for (GLuint i = 0; i <= 3; i++)
        {
            GLdouble x = x_min + i * dx;
            for (GLuint j = 0; j <= 3; j++)
                {
                    GLdouble y = y_min + j * dy;
                    DCoordinate3 &dp = _data_points_to_interpolate(i, j);
                    dp[0] = x;
                    dp[1] = y;
                    dp[2] = -2.0 + 4.0 * static_cast<GLdouble>(rand()) / RAND_MAX;
                }
        }

        BicubicHermitePatch3 tmp = (*_bicubic_hermite_patch3);

        if(!tmp.UpdateVertexBufferObjectsOfData(usage_flag)) {
            throw Exception("Couldn't update vbo of tmp");
        }

        if(!tmp.UpdateDataForInterpolation(u_knot_vector,v_knot_vector,_data_points_to_interpolate)) {
            throw Exception("Couldn't update data for interpolation for tmp");
        }

        if(!tmp.UpdateVertexBufferObjectsOfData(usage_flag)) {
            throw Exception("Couldn't update vbo of tmp");
        }

        _after_interpolation = tmp.GenerateImage(30, 30, GL_STATIC_DRAW);
        if(!_after_interpolation) {
            throw Exception("Couldn't create image of interpolating patch");
        }

        if(!_after_interpolation->UpdateVertexBufferObjects()) {
            throw Exception("Couldn't update vbo of image of interpolating patch");
        }
    }

    bool GLWidget::initializeHermitePatch() {

        _bicubic_hermite_patch3 = new BicubicHermitePatch3();
        _u_lines = new RowMatrix<GenericCurve3*>(10);
        _v_lines = new RowMatrix<GenericCurve3*>(10);

        //set points
        _bicubic_hermite_patch3->SetCorner(0,0,0,-3);
        _bicubic_hermite_patch3->SetCorner(1,5,0,0);
        _bicubic_hermite_patch3->SetCorner(2,0,5,2);
        _bicubic_hermite_patch3->SetCorner(3,5,5,0);

        _bicubic_hermite_patch3->SetUvector(0,0,4,4);
        _bicubic_hermite_patch3->SetUvector(1,0,2,0);
        _bicubic_hermite_patch3->SetUvector(2,0,0,2);
        _bicubic_hermite_patch3->SetUvector(3,2,2,2);

        _bicubic_hermite_patch3->SetVvector(0,0,0,0);
        _bicubic_hermite_patch3->SetVvector(1,2,2,0);
        _bicubic_hermite_patch3->SetVvector(2,0,2,2);
        _bicubic_hermite_patch3->SetVvector(3,2,0,2);

        _bicubic_hermite_patch3->SetTwistVector(0,0,0,0);
        _bicubic_hermite_patch3->SetTwistVector(1,1,3,2);
        _bicubic_hermite_patch3->SetTwistVector(2,3,2,1);
        _bicubic_hermite_patch3->SetTwistVector(3,1,2,3);

        _u_lines = _bicubic_hermite_patch3->GenerateUIsoparametricLines(10, 2, 30);
        for(GLuint i = 0 ; i < _u_lines->GetColumnCount(); i++) {
            if((*_u_lines)[i]) {
                (*_u_lines)[i]->UpdateVertexBufferObjects(1,GL_STATIC_DRAW);
            }
        }

        _v_lines = _bicubic_hermite_patch3->GenerateVIsoparametricLines(10, 2, 30);

        for(GLuint i = 0 ; i < _v_lines->GetColumnCount(); i++) {
            if((*_v_lines)[i]) {
                (*_v_lines)[i]->UpdateVertexBufferObjects(1,GL_STATIC_DRAW);
            }
        }


         _bicubic_hermite_patch3->UpdateVertexBufferObjectsOfData();

        // generate the mesh of the surface patch
        _before_interpolation = _bicubic_hermite_patch3->GenerateImage(30, 30, GL_STATIC_DRAW);
        _before_interpolation->UpdateVertexBufferObjects();



        return true;
    }

    bool GLWidget::renderHermitePatch() {
            glColor3f(0.0f, 1.0f, 0.0f);
            for(GLuint i = 0; i < _u_lines->GetColumnCount(); i++)
            {
                if((*_u_lines)[i])
                {
                    (*_u_lines)[i]->RenderDerivatives(0, GL_LINE_STRIP);
                }
            }


            glColor3f(1.0f, 1.0f, 0);
            for(GLuint i = 0; i < _v_lines->GetColumnCount(); i++)
            {
                if((*_v_lines)[i])
                {
                    (*_v_lines)[i]->RenderDerivatives(0, GL_LINE_STRIP);
                }
            }

            if(_show_hermite_patch_first_derivatives){
               glColor3f(0.0f, 1.0f, 0.0f);
               for(GLuint i = 0; i < _u_lines->GetColumnCount(); i++)
               {
                   glPointSize(1.0f);
                   glColor3f(0.0f, 1.0f, 0.0f);

                   if((*_u_lines)[i])
                   {
                       (*_u_lines)[i]->RenderDerivatives(1, GL_POINTS);
                       (*_u_lines)[i]->RenderDerivatives(1, GL_LINES);
                   }
               }

               for(GLuint i = 0; i < _v_lines->GetColumnCount(); i++)
               {
                   glPointSize(1.0f);
                   glColor3f(0.0f, 1.0f, 0.0f);

                   if((*_v_lines)[i])
                   {
                       (*_v_lines)[i]->RenderDerivatives(1, GL_POINTS);
                       (*_v_lines)[i]->RenderDerivatives(1, GL_LINES);
                   }
               }
           }

           if(_show_hermite_patch_second_derivatives){
               glColor3f(0.0f, 1.0f, 0.0f);
               for(GLuint i = 0; i < _u_lines->GetColumnCount(); i++)
               {
                   glPointSize(10.0f);
                   glColor3f(0.0f, 1.0f, 0.0f);

                   if((*_u_lines)[i])
                   {
                       (*_u_lines)[i]->RenderDerivatives(2, GL_POINTS);
                       (*_u_lines)[i]->RenderDerivatives(2, GL_LINES);
                   }
               }

               for(GLuint i = 0; i < _v_lines->GetColumnCount(); i++)
               {
                   glPointSize(10.0f);
                   glColor3f(0.0f, 1.0f, 0.0f);

                   if((*_v_lines)[i])
                   {
                       (*_v_lines)[i]->RenderDerivatives(2, GL_POINTS);
                       (*_v_lines)[i]->RenderDerivatives(2, GL_LINES);
                   }
               }
           }

            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);

            MatFBRuby.Apply();
            _before_interpolation->Render();

            glEnable(GL_BLEND);
            glDepthMask(GL_FALSE);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            //MatFBTurquoise.Apply();
            //_after_interpolation->Render();
            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);

            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHTING);


            return true;
    }

//    bool GLWidget::renderHermiteArc(){

//              if(_selected_hermite_point < 2) {
//                  glPointSize(10.0f);
//                  glBegin(GL_POINTS);
//                  glColor3f(0.0, 1.0f, 1.0f);
//                  glVertex3f((*_cubic_hermite_arc3)[_selected_hermite_point][0], (*_cubic_hermite_arc3)[_selected_hermite_point][1], (*_cubic_hermite_arc3)[_selected_hermite_point][2]);
//                  glEnd();
//              }
//              glPointSize(2);

//              glPointSize(10.0f);
//              glColor3f(1.0f, 0.5f, 0.0f);
//              _cubic_hermite_arc3->RenderData(GL_LINE_STRIP);
//              if (!_image_of_cubic_hermite_arc3->RenderDerivatives(0, GL_LINE_STRIP)) {
//               return false;
//              }

//             if(_show_hermite_interpolating_curve){
//                  glColor3f(1.0, 0.0, 1.0);
//                  _image_of_interpolating_cubic_hermite_arc3->RenderDerivatives(0, GL_LINE_STRIP);
//              }

//             if(_show_hermite_first_order){
//                   glPointSize(1.0f);
//                   glColor3f(0.0f, 1.0f, 0.0f);
//                   _image_of_cubic_hermite_arc3->RenderDerivatives(1, GL_LINES);
//             }

//             if(_show_hermite_second_order){
//                  glColor3f(0.0f, 0.0f, 1.0f);
//                  _image_of_cubic_hermite_arc3->RenderDerivatives(2, GL_LINES);
//                  glPointSize(1.0f);
//             }
//              return true;
//        }

    bool GLWidget::initializeHermiteArc(){
       GLenum usage_flag=GL_STATIC_DRAW;
       _cubic_hermite_arc3 = new CubicHermiteArc3();

        if(!_cubic_hermite_arc3){
           return false;
       }

       //points
       _cubic_hermite_arc3->SetCorner(0, -2.0, 0.0, 0.0);
       _cubic_hermite_arc3->SetCorner(1, +1.0, 0.0, 0.0);

       //tangents
       _cubic_hermite_arc3->SetTangent(0, 0.0, 1.0, 0.0);
       _cubic_hermite_arc3->SetTangent(1, 1.0, 1.0, 0.0);


      _cubic_hermite_arc3->UpdateVertexBufferObjectsOfData();

      _image_of_cubic_hermite_arc3 = _cubic_hermite_arc3->GenerateImage(2, 100);
       if (!_image_of_cubic_hermite_arc3) {
            return false;
        }
        if (!_image_of_cubic_hermite_arc3->UpdateVertexBufferObjects(1,usage_flag)) {
          return false;
        }

        return true;
    }

    void GLWidget::updateHermiteArc(){
        GLenum usage_flag=GL_STATIC_DRAW;
        ColumnMatrix<double> knot_vector;
        knot_vector.ResizeRows(4);

        _cubic_hermite_arc3->UpdateVertexBufferObjectsOfData();
        CubicHermiteArc3 temp = *_cubic_hermite_arc3;
        temp.UpdateVertexBufferObjectsOfData();

         GLdouble pointValue = 0;

          GLdouble step = TWO_PI / (4);
         for (GLuint i = 0; i < 4; i++) {
           knot_vector(i) = pointValue;
           pointValue += step;
         }

        ColumnMatrix<DCoordinate3> _dataPointsToInterpolate(4);


        for (GLuint i = 0; i < 4; i++) {
          _dataPointsToInterpolate(i) = temp[i];
        }


        temp.UpdateDataForInterpolation(knot_vector, _dataPointsToInterpolate);
         if(_image_of_interpolating_cubic_hermite_arc3){

              _image_of_interpolating_cubic_hermite_arc3->DeleteVertexBufferObjects();
         }

        _image_of_interpolating_cubic_hermite_arc3 = temp.GenerateImage(2, 100);
        _image_of_interpolating_cubic_hermite_arc3->UpdateVertexBufferObjects(1, usage_flag);

       _image_of_cubic_hermite_arc3->DeleteVertexBufferObjects();
       _image_of_cubic_hermite_arc3 = _cubic_hermite_arc3->GenerateImage(2, 100);
       _image_of_cubic_hermite_arc3->UpdateVertexBufferObjects(1, usage_flag);


     update();
    }

    void GLWidget::_initializeShaders()
    {
        try {
            _shaders.ResizeColumns(4);
            if (!_shaders[0].InstallShaders("Shaders/directional_light.vert","Shaders/directional_light.frag"))
            {
                throw Exception("Directional light creation error");
            }

            if (!_shaders[1].InstallShaders("Shaders/two_sided_lighting.vert","Shaders/two_sided_lighting.frag"))
            {
                throw Exception("Two sided lighting creation error");
            }

            if (!_shaders[2].InstallShaders("Shaders/toon.vert","Shaders/toon.frag"))
            {
                throw Exception("Toon creation error.");
            } else {
                _shaders[2].Enable();
                _shaders[2].SetUniformVariable4f("default_outline_color", 60.0f, 160.0f, 60.0f, 1.0f);
                _shaders[2].Disable();
            }

            if (!_shaders[3].InstallShaders("Shaders/reflection_lines.vert","Shaders/reflection_lines.frag"))
            {
                throw Exception("Reflection lines creation error");
            } else {
                _shaders[3].Enable();
                _shaders[3].SetUniformVariable1f("scale_factor", _shader_scale);
                _shaders[3].SetUniformVariable1f("smoothing", _shader_smoothing);
                _shaders[3].SetUniformVariable1f("shading", _shader_shading);
                _shaders[3].Disable();
            }

        } catch (Exception& e) {
            std::cout << e << endl;
        }
    }

    void GLWidget::initializeParametricSurfaceData() {

        HCoordinate3 direction (0.0, 0.0, 1.0, 0.0);
        Color4  ambient(0.4, 0.4, 0.4, 1.0);
        Color4  diffuse(0.8, 0.8, 0.8, 1.0);
        Color4  specular(1.0, 1.0, 1.0, 1.0);
        _dl = new (nothrow) DirectionalLight(GL_LIGHT1, direction, ambient, diffuse, specular);

        _leMouse.LoadFromOFF("Models/Characters/mouse.off", GL_TRUE);
        _leMouse.UpdateVertexBufferObjects(GL_STATIC_DRAW);

        _parametric_curves.ResizeColumns(3);
        _image_of_parametric_curves.ResizeColumns(3);

        _u_min[0] = surface_torus::u_min;
        _u_min[1] = surface_sphere::u_min;
        _u_min[2] = surface_cylindre::u_min;
        _u_min[5] = surface_helicoid::u_min;

        _u_index[0] = surface_torus::u_min;
        _u_index[1] = surface_sphere::u_min;
        _u_index[2] = surface_cylindre::u_min;
        _u_index[5] = surface_helicoid::u_min;

        _u_max[0] = surface_torus::u_max;
        _u_max[1] = surface_sphere::u_max;
        _u_max[2] = surface_cylindre::u_max;
        _u_max[5] = surface_helicoid::u_max;

    }

    void GLWidget::initializeParametricSurfaces() {
        GLenum usage_flag = GL_STATIC_DRAW;


        TriangularMatrix<ParametricSurface3::PartialDerivative> p_derivative(3);
        p_derivative(0, 0) = surface_torus::d00;
        p_derivative(1, 0) = surface_torus::d10;
        p_derivative(1, 1) = surface_torus::d01;
        _parametric_surfaces[0] = nullptr;
        _image_of_ps[0] = nullptr;

        _parametric_surfaces[0] = new (nothrow) ParametricSurface3(p_derivative, surface_torus::u_min, surface_torus::u_max, surface_torus::v_min,surface_torus::v_max);

        if(!_parametric_surfaces[0])
        {
             cout << "Couldn't create parametric surface";
        }

         _image_of_ps[0] = _parametric_surfaces[0]->GenerateImage(u_div_point_count, v_div_point_count, usage_flag);

        if(!_image_of_ps[0]->UpdateVertexBufferObjects(usage_flag))
        {
            cout << "Could_not_create_the_vertex_buffer_object_of_the_parametric_surface!" << endl;
        }


        RowMatrix<ParametricCurve3::Derivative> curve_derivates(3);
        curve_derivates[0] = curve_on_surface_torus::d0;
        curve_derivates[1] = curve_on_surface_torus::d1;
        curve_derivates[2] = curve_on_surface_torus::d2;

        _parametric_surfaces_curve[0] = nullptr;
        _parametric_surfaces_curve[0] = new (nothrow) ParametricCurve3(curve_derivates, curve_on_surface_torus::u_min, curve_on_surface_torus::u_max);

        _images_of_parametric_surfaces_curve[0] = _parametric_surfaces_curve[0]->GenerateImage(_div_point_count, GL_STATIC_DRAW);
        _images_of_parametric_surfaces_curve[0]->UpdateVertexBufferObjects(_scale, GL_STATIC_DRAW);

        p_derivative(0, 0) = surface_sphere::d00;
        p_derivative(1, 0) = surface_sphere::d10;
        p_derivative(1, 1) = surface_sphere::d01;
        _parametric_surfaces[1] = nullptr;
        _image_of_ps[1] = nullptr;

        _parametric_surfaces[1] = new (nothrow) ParametricSurface3(p_derivative, surface_sphere::u_min, surface_sphere::u_max, surface_sphere::v_min,surface_sphere::v_max);

        if(!_parametric_surfaces[1])
        {
             cout << "Couldn't create parametric surface";
        }

         _image_of_ps[1] = _parametric_surfaces[1]->GenerateImage(u_div_point_count, v_div_point_count, usage_flag);

        if(!_image_of_ps[1]->UpdateVertexBufferObjects(usage_flag))
        {
            cout << "Could_not_create_the_vertex_buffer_object_of_the_parametric_surface!" << endl;
        }

        curve_derivates[0] = curve_on_surface_sphere::d0;
        curve_derivates[1] = curve_on_surface_sphere::d1;
        curve_derivates[2] = curve_on_surface_sphere::d2;

        _parametric_surfaces_curve[1] = nullptr;
        _parametric_surfaces_curve[1] = new (nothrow) ParametricCurve3(curve_derivates, curve_on_surface_sphere::u_min, curve_on_surface_sphere::u_max);

        _images_of_parametric_surfaces_curve[1] = _parametric_surfaces_curve[1]->GenerateImage(_div_point_count, GL_STATIC_DRAW);
        _images_of_parametric_surfaces_curve[1]->UpdateVertexBufferObjects(_scale, GL_STATIC_DRAW);

        p_derivative(0, 0) = surface_cylindre::d00;
        p_derivative(1, 0) = surface_cylindre::d10;
        p_derivative(1, 1) = surface_cylindre::d01;
        _parametric_surfaces[2] = nullptr;
        _image_of_ps[2] = nullptr;

        _parametric_surfaces[2] = new (nothrow) ParametricSurface3(p_derivative, surface_cylindre::u_min, surface_cylindre::u_max, surface_cylindre::v_min,surface_cylindre::v_max);

        if(!_parametric_surfaces[2])
        {
             cout << "Couldn't create parametric surface";
        }

         _image_of_ps[2] = _parametric_surfaces[2]->GenerateImage(u_div_point_count, v_div_point_count, usage_flag);

        if(!_image_of_ps[2]->UpdateVertexBufferObjects(usage_flag))
        {
            cout << "Could_not_create_the_vertex_buffer_object_of_the_parametric_surface!" << endl;
        }

        curve_derivates[0] = curve_on_surface_cylindre::d0;
        curve_derivates[1] = curve_on_surface_cylindre::d1;
        curve_derivates[2] = curve_on_surface_cylindre::d2;

        _parametric_surfaces_curve[2] = nullptr;
        _parametric_surfaces_curve[2] = new (nothrow) ParametricCurve3(curve_derivates, curve_on_surface_cylindre::u_min, curve_on_surface_cylindre::u_max);

        _images_of_parametric_surfaces_curve[2] = _parametric_surfaces_curve[2]->GenerateImage(_div_point_count, GL_STATIC_DRAW);
        _images_of_parametric_surfaces_curve[2]->UpdateVertexBufferObjects(_scale, GL_STATIC_DRAW);

        p_derivative(0, 0) = surface_bohemian_dome::d00;
        p_derivative(1, 0) = surface_bohemian_dome::d10;
        p_derivative(1, 1) = surface_bohemian_dome::d01;
        _parametric_surfaces[3] = nullptr;
        _image_of_ps[3] = nullptr;

        _parametric_surfaces[3] = new (nothrow) ParametricSurface3(p_derivative, surface_bohemian_dome::u_min, surface_bohemian_dome::u_max, surface_bohemian_dome::v_min,surface_bohemian_dome::v_max);

        if(!_parametric_surfaces[3])
        {
             cout << "Couldn't create parametric surface";
        }

         _image_of_ps[3] = _parametric_surfaces[3]->GenerateImage(u_div_point_count, v_div_point_count, usage_flag);

        if(!_image_of_ps[3]->UpdateVertexBufferObjects(usage_flag))
        {
            cout << "Could_not_create_the_vertex_buffer_object_of_the_parametric_surface!" << endl;
        }

        p_derivative(0, 0) = surface_cone_sinusoid::d00;
        p_derivative(1, 0) = surface_cone_sinusoid::d10;
        p_derivative(1, 1) = surface_cone_sinusoid::d01;
        _parametric_surfaces[4] = nullptr;
        _image_of_ps[4] = nullptr;

        _parametric_surfaces[4] = new (nothrow) ParametricSurface3(p_derivative, surface_cone_sinusoid::u_min, surface_cone_sinusoid::u_max, surface_cone_sinusoid::v_min,surface_cone_sinusoid::v_max);

        if(!_parametric_surfaces[4])
        {
             cout << "Couldn't create parametric surface";
        }

         _image_of_ps[4] = _parametric_surfaces[4]->GenerateImage(u_div_point_count, v_div_point_count, usage_flag);

        if(!_image_of_ps[4]->UpdateVertexBufferObjects(usage_flag))
        {
            cout << "Could_not_create_the_vertex_buffer_object_of_the_parametric_surface!" << endl;
        }

        p_derivative(0, 0) = surface_helicoid::d00;
        p_derivative(1, 0) = surface_helicoid::d10;
        p_derivative(1, 1) = surface_helicoid::d01;
        _parametric_surfaces[5] = nullptr;
        _image_of_ps[5] = nullptr;

        _parametric_surfaces[5] = new (nothrow) ParametricSurface3(p_derivative, surface_helicoid::u_min, surface_helicoid::u_max, surface_helicoid::v_min, surface_helicoid::v_max);

        if(!_parametric_surfaces[5])
        {
             cout << "Couldn't create parametric surface";
        }

         _image_of_ps[5] = _parametric_surfaces[5]->GenerateImage(u_div_point_count, v_div_point_count, usage_flag);

        if(!_image_of_ps[5]->UpdateVertexBufferObjects(usage_flag))
        {
            cout << "Could_not_create_the_vertex_buffer_object_of_the_parametric_surface!" << endl;
        }

        curve_derivates[0] = curve_on_surface_helicoid::d0;
        curve_derivates[1] = curve_on_surface_helicoid::d1;
        curve_derivates[2] = curve_on_surface_helicoid::d2;

        _parametric_surfaces_curve[5] = nullptr;
        _parametric_surfaces_curve[5] = new (nothrow) ParametricCurve3(curve_derivates, curve_on_surface_helicoid::u_min, curve_on_surface_helicoid::u_max);

        _images_of_parametric_surfaces_curve[5] = _parametric_surfaces_curve[5]->GenerateImage(_div_point_count, GL_STATIC_DRAW);
        _images_of_parametric_surfaces_curve[5]->UpdateVertexBufferObjects(_scale, GL_STATIC_DRAW);
    }

    void GLWidget::paintSelectedSurface() {
        if (_dl)
        {
            glPushMatrix();
            glRotated(rotate, 1, 1/2, 3/4);
            _dl->Enable();
                glEnable(GL_LIGHTING);
                glEnable(GL_NORMALIZE);
                glEnable(GL_TEXTURE_2D);
                glPushMatrix();
                    _materials[_selected_material].Apply();
                    if (_show_texture)
                        _texture[_selected_texture]->bind();
                    else
                        _texture[_selected_texture]->release();

                    _image_of_ps[_selected_parametric_surface]->Render();
                glPopMatrix();
            if(_selected_parametric_surface == 1 || _selected_parametric_surface == 2 || _selected_parametric_surface == 5) {
                glPushMatrix();
                    glColor3f(1,0,0);
                    _images_of_parametric_surfaces_curve[_selected_parametric_surface]->RenderDerivatives(0,GL_LINE_STRIP);
                    glMultMatrixd(_transformation);
                    glPushMatrix();
                        _materials[_selected_material].Apply();
                        glTranslated(0,-0.45,0);
                        if(_selected_parametric_surface == 5) {
                            glRotated(180,1,0,0);
                        }

                        if(_selected_parametric_surface == 1) {
                            glRotated(180,1,0,0);
                        }

                        if(_selected_parametric_surface == 2) {
                            glRotated(180,0,0,1);
                        }
                        _leMouse.Render();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                    glDisable(GL_LIGHTING);
                    glDisable(GL_NORMALIZE);
                _dl->Disable();
                glPopMatrix();
            }
            glPopMatrix();


        }
    }
    void GLWidget::animateSurface() {
        if(_selected_parametric_surface < 3 || _selected_parametric_surface == 5) {

            rotate += 2;

            DCoordinate3 point, diff_u, diff_v;
            GLdouble u = _u_index[_selected_parametric_surface], v;

            switch(_selected_parametric_surface){

            case 0:
            {
                v = 2 * u;
                point = surface_torus::d00(u,v);
                diff_u = surface_torus::d01(u,v);
                diff_v = surface_torus::d10(u,v);
                break;
            }
            case 1:
            {
                v = 3 * u / 4;
                point = surface_sphere::d00(u, v);
                diff_u = surface_sphere::d01(u, v);
                diff_v = surface_sphere::d10(u, v);
                break;
            }
            case 2:
            {
                v = sin(u);
                point = surface_cylindre::d00(u, v);
                diff_u = surface_cylindre::d01(u, v);
                diff_v = surface_cylindre::d10(u, v);
                break;
            }

            case 5:
            {
                v = 2 * u;
                point = surface_helicoid::d00(u,v);
                diff_u = surface_helicoid::d01(u,v);
                diff_v = surface_helicoid::d10(u,v);
                break;
            }
            }

            DCoordinate3 normal = diff_u ^ diff_v;
            DCoordinate3 normal_diff_u = normal ^ diff_u;

            normal.normalize();
            diff_u.normalize();
            normal_diff_u.normalize();

            _transformation[0] = diff_u[0];
            _transformation[1] = diff_u[1];
            _transformation[2] = diff_u[2];
            _transformation[3] = 0;

            _transformation[4] = normal[0];
            _transformation[5] = normal[1];
            _transformation[6] = normal[2];
            _transformation[7] = 0;

            _transformation[8] = normal_diff_u[0];
            _transformation[9] = normal_diff_u[1];
            _transformation[10] = normal_diff_u[2];
            _transformation[11] = 0;

            _transformation[12] = point[0];
            _transformation[13] = point[1];
            _transformation[14] = point[2];
            _transformation[15] = 1;


            _u_index[_selected_parametric_surface] += DEG_TO_RADIAN;
            if(_u_index[_selected_parametric_surface] >= _u_max[_selected_parametric_surface]) {
                _u_index[_selected_parametric_surface] = _u_min[_selected_parametric_surface];
            }

            update();
        }
    }

    void GLWidget::_initializeTextures() {

        _texture[0] = new QOpenGLTexture(QImage("Textures/texture_01.jpg").mirrored());
        _texture[0]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[0]->setMagnificationFilter(QOpenGLTexture::Linear);


        _texture[1] = new QOpenGLTexture(QImage("Textures/texture_02.jpg").mirrored());
        _texture[1]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[1]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[2] = new QOpenGLTexture(QImage("Textures/texture_03.jpg").mirrored());
        _texture[2]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[2]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[3] = new QOpenGLTexture(QImage("Textures/texture_04.jpg").mirrored());
        _texture[3]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[3]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[4] = new QOpenGLTexture(QImage("Textures/texture_05.jpg").mirrored());
        _texture[4]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[4]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[5] = new QOpenGLTexture(QImage("Textures/texture_06.jpg").mirrored());
        _texture[5]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[5]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[6] = new QOpenGLTexture(QImage("Textures/texture_07.jpg").mirrored());
        _texture[6]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[6]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[7] = new QOpenGLTexture(QImage("Textures/texture_08.jpg").mirrored());
        _texture[7]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[7]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[8] = new QOpenGLTexture(QImage("Textures/texture_09.jpg").mirrored());
        _texture[8]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[8]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[9] = new QOpenGLTexture(QImage("Textures/texture_10.jpg").mirrored());
        _texture[9]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[9]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[10] = new QOpenGLTexture(QImage("Textures/texture_11.jpg").mirrored());
        _texture[10]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[10]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[11] = new QOpenGLTexture(QImage("Textures/texture_12.jpg").mirrored());
        _texture[11]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[11]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[12] = new QOpenGLTexture(QImage("Textures/texture_13.jpg").mirrored());
        _texture[12]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[12]->setMagnificationFilter(QOpenGLTexture::Linear);

        _texture[13] = new QOpenGLTexture(QImage("Textures/texture_14.jpg").mirrored());
        _texture[13]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _texture[13]->setMagnificationFilter(QOpenGLTexture::Linear);
    }

    void GLWidget::animate() {

        for (GLint i = 0 ; i < _dynamic_model_count ; ++i) {

            DCoordinate3 _t;
            DCoordinate3 der1;
            DCoordinate3 der2;

            _old_time_index[i] += _speed[i];
            if(_old_time_index[i] >= _cyclic_div_point_count) {
                _old_time_index[i] = 0;
            }
            if(!_images_of_cyclic_curves[i]->GetDerivative(0, _old_time_index[i], _t))
            {
                throw Exception("Exception: Could not get derivate");
            }

            if(!_images_of_cyclic_curves[i]->GetDerivative(1, _old_time_index[i], der1))
            {
                throw Exception("Exception: Could not get derivate");
            }

            if(!_images_of_cyclic_curves[i]->GetDerivative(2, _old_time_index[i], der2))
            {
                throw Exception("Exception: Could not get derivate");
            }


            DCoordinate3 _j_prime = der1;
            DCoordinate3 orange = der1 ^ der2;
            DCoordinate3 purple = der1 ^ orange;
            DCoordinate3 _i_prime = orange;
            DCoordinate3 _k_prime = purple;

            _i_prime.normalize();
            _j_prime.normalize();
            _k_prime.normalize();

            _old_transformation[i][0] = _k_prime[0];
            _old_transformation[i][1] = _k_prime[1];
            _old_transformation[i][2] = _k_prime[2];
            _old_transformation[i][3] = 0;

            _old_transformation[i][4] = _i_prime[0];
            _old_transformation[i][5] = _i_prime[1];
            _old_transformation[i][6] = _i_prime[2];
            _old_transformation[i][7] = 0;

            _old_transformation[i][8] = _j_prime[0];
            _old_transformation[i][9] = _j_prime[1];
            _old_transformation[i][10] = _j_prime[2];
            _old_transformation[i][11] = 0;

            _old_transformation[i][12] = _t[0];
            _old_transformation[i][13] = _t[1];
            _old_transformation[i][14] = _t[2];
            _old_transformation[i][15] = 1;
        }


        if(_dynamic_scaling_up) {
            _dynamic_model_scaling += 0.05;
            if(_dynamic_model_scaling >= 3) {
                _dynamic_scaling_up = false;
            }
        } else {
            _dynamic_model_scaling -= 0.05;
            if(_dynamic_model_scaling <= 1) {
                _dynamic_scaling_up = true;
            }
        }

        update();
    }

    void GLWidget::initializeCyclicData() {
        _old_time_index.ResizeColumns(_dynamic_model_count);
        _old_time_index[0] = 0;
        _old_time_index[1] = 50;
        _old_time_index[2] = 100;
        _old_time_index[3] = 150;

        _old_transformation.ResizeColumns(_dynamic_model_count);
        for (GLint i = 0 ; i < _dynamic_model_count; i++)
        {
            _old_transformation[i] = new GLdouble[16];
            _speed[i] = 0;
        }

        knot_vector.ResizeColumns(_dynamic_model_count);
        points.ResizeColumns(_dynamic_model_count);

        HCoordinate3 direction (0.0, 0.0, 1.0, 0.0);
        Color4  ambient(0.4, 0.4, 0.4, 1.0);
        Color4  diffuse(0.8, 0.8, 0.8, 1.0);
        Color4  specular(1.0, 1.0, 1.0, 1.0);
        _dl = new (nothrow) DirectionalLight(GL_LIGHT1, direction, ambient, diffuse, specular);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
    }

    bool GLWidget::initializeProperties(){
        ifstream fin("StaticScene/StaticScene.txt");
        GLint n;
        fin >> n;
        _static_model_properties.ResizeColumns(n);
        for(GLint i = 0; i < n; i++){
            fin >> _static_model_properties[i];
        }
        fin.close();
        return true;
    }

    bool GLWidget::_initializeMaterials() {
        _materials.ResizeColumns(7);
        _materials[0] = MatFBBrass;
        _materials[1] = MatFBGold;
        _materials[2] = MatFBSilver;
        _materials[3] = MatFBEmerald;
        _materials[4] = MatFBPearl;
        _materials[5] = MatFBRuby;
        _materials[6] = MatFBTurquoise;
        return true;
    }

    bool GLWidget::initializeModels() {
        _dynamic_models.ResizeColumns(_dynamic_model_count);
        _characters.ResizeColumns(_dynamic_model_count);
        _static_models.ResizeColumns(_static_model_count);

        if(_dynamic_models[0].LoadFromOFF("Models/Flying objects/Airplanes/airplane_01.off", GL_TRUE)) {
            if(!_dynamic_models[0].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                return false;
            }
        }
        if(_dynamic_models[1].LoadFromOFF("Models/Flying objects/Airplanes/airplane_02.off", GL_TRUE)) {
            if(!_dynamic_models[1].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                return false;
            }
        }

        if(_dynamic_models[2].LoadFromOFF("Models/Boats/boat_01.off", GL_TRUE)) {
            if(!_dynamic_models[2].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                return false;
            }
        }

        if(_dynamic_models[3].LoadFromOFF("Models/Boats/boat_02.off", GL_TRUE)) {
            if(!_dynamic_models[3].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                return false;
            }
        }

        if(_characters[0].LoadFromOFF("Models/Characters/elephant.off", GL_TRUE)) {
            if(!_characters[0].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                return false;
            }
        }

        if(_characters[1].LoadFromOFF("Models/Characters/gangster.off", GL_TRUE)) {
            if(!_characters[1].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                return false;
            }
        }


        if(_characters[2].LoadFromOFF("Models/Characters/mouse.off", GL_TRUE)) {
            if(!_characters[2].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                return false;
            }
        }


        if(_characters[3].LoadFromOFF("Models/Characters/pig.off", GL_TRUE)) {
            if(!_characters[3].UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                return false;
            }
        }

        if(_static_models[0].LoadFromOFF("Models/Building blocks/Primitives/cube.off", GL_TRUE)) {
            if(!_static_models[0].UpdateVertexBufferObjects(GL_STATIC_DRAW)) {
                return false;
            }
        }

        if(_static_models[1].LoadFromOFF("Models/Building blocks/Primitives/prism.off", GL_TRUE)) {
            if(!_static_models[1].UpdateVertexBufferObjects(GL_STATIC_DRAW)) {
                return false;
            }
        }

        if(_static_models[2].LoadFromOFF("Models/Building blocks/Buildings/building_01.off", GL_TRUE)) {
            if(!_static_models[2].UpdateVertexBufferObjects(GL_STATIC_DRAW)) {
                return false;
            }
        }


        if(_static_models[3].LoadFromOFF("Models/Building blocks/Buildings/building_02.off", GL_TRUE)) {
            if(!_static_models[3].UpdateVertexBufferObjects(GL_STATIC_DRAW)) {
                return false;
            }
        }

        return true;
    }

    bool GLWidget::paintModels() {

        for(int i = 0; i < _dynamic_model_count ; i++) {
            glPushMatrix();

                if(i < 2) {
                    glTranslated(0, 4, 0);
                }
                if(i == 3) {
                    glTranslated(-7, 0, -3);
                }

                if(i == 0) {
                    _materials[3].Apply();
                } else if(i == 2) {
                    _materials[1].Apply();
                } else {
                    _materials[2].Apply();
                }

                glMultMatrixd(_old_transformation[i]);
                glPushMatrix();
                    glScaled(_dynamic_model_scaling,_dynamic_model_scaling,_dynamic_model_scaling);
                    if(i == 3) {
                        glRotated(270,1,0,0);
                        glRotated(270,0,0,1);
                    }
                    if(i == 1) {
                        glRotated(180,1,0,0);
                    }
                    _dynamic_models[i].Render();
                glPopMatrix();

                glPushMatrix();
                    glScaled(0.5,0.5,0.5);
                    glTranslated(0,1,0);
                    if(i == 0) {
                        glRotated(90,0,1,0);
                    }
                    _characters[i].Render();
                glPopMatrix();
            glPopMatrix();

        }

        return true;
    }

    bool GLWidget::paintStaticModels() {

        for(GLuint i = 0 ; i < _static_model_properties.GetColumnCount() ; i++) {
            const ModelProperties& mp = _static_model_properties[i];
            glPushMatrix();

                glRotated(mp.angle[0], 1.0, 0.0, 0.0);
                glRotated(mp.angle[1], 0.0, 1.0, 0.0);
                glRotated(mp.angle[2], 0.0, 0.0, 1.0);

                glTranslated(mp.position[0], mp.position[1], mp.position[2]);
                glScaled(mp.scale[0], mp.scale[1], mp.scale[2]);

                _materials[mp.materialID].Apply();
                _static_models[mp.id].Render();
            glPopMatrix();
        }
        return true;
    }

    void GLWidget::initializeCyclicCurves(){

        GLenum usage_flag = GL_STATIC_DRAW;
        GLdouble step;

        // Interpolating curves

        GLint nknot = 5;
        knot_vector[0].ResizeRows(nknot);
        points[0].ResizeRows(nknot);
        points[0][0] = DCoordinate3(0, 0, 0);
        points[0][1] = DCoordinate3(-12, 0, -4);
        points[0][2] = DCoordinate3(-12, 4, 4);
        points[0][3] = DCoordinate3(8, 2, 4);
        points[0][4] = DCoordinate3(14, 0, 18);

        step = TWO_PI / nknot;
        for(int i = 0; i < nknot; i++)
        {
            knot_vector[0][i] = i*step;
        }

        // 0, TWOPI/ nknot , 2 * TWO
        _cyclic_curves[0] = nullptr;
        _images_of_cyclic_curves[0] = nullptr;

        _cyclic_curves[0] = new (nothrow) CyclicCurve3(2, usage_flag);

        if(!_cyclic_curves[0])
        {
            cout << "Couldn't generate CyclicCurve" << endl;
            return;
        }

        if(!_cyclic_curves[0]->UpdateDataForInterpolation(knot_vector[0], points[0]))
        {
            cout << "The update was unsuccessful" << std::endl;
            return;
        }

        if(!_cyclic_curves[0]->UpdateVertexBufferObjectsOfData(usage_flag))
        {
            cout << "The update was unsuccessful" << std::endl;
            return;
        }
        _images_of_cyclic_curves[0] = _cyclic_curves[0]->GenerateImage(2, 200, usage_flag);

        if(!_images_of_cyclic_curves[0])
        {
            cout << "Couldn't generate CyclicCurve" << endl;
            return;
        }

        if(!_images_of_cyclic_curves[0]->UpdateVertexBufferObjects(_derivatives_scale, usage_flag))
        {
             cout << "Could_not_create_the_vertex_buffer_object_of_the_cyclic_curve!" << endl;
        }

        nknot = 5;
        knot_vector[1].ResizeRows(nknot);
        points[1].ResizeRows(nknot);
        points[1][0] = DCoordinate3(0, 0, 0);
        points[1][1] = DCoordinate3(12, 0, 4);
        points[1][2] = DCoordinate3(12, 4, -4);
        points[1][3] = DCoordinate3(-8, 0, -4);
        points[1][4] = DCoordinate3(-14, 0, -18);

        step = TWO_PI / nknot;
        for(int i = 0; i < nknot; i++)
        {
            knot_vector[1][i] = i*step;
        }
        _cyclic_curves[1] = nullptr;
        _images_of_cyclic_curves[1] = nullptr;

        _cyclic_curves[1] = new (nothrow) CyclicCurve3(2, usage_flag);

        if(!_cyclic_curves[1]->UpdateDataForInterpolation(knot_vector[1], points[1]))
        {
            cout << "The update was unsuccessful" << std::endl;
            return;
        }

        if(!_cyclic_curves[1]->UpdateVertexBufferObjectsOfData(usage_flag))
        {
            cout << "The update was unsuccessful" << std::endl;
            return;
        }
        _images_of_cyclic_curves[1] = _cyclic_curves[1]->GenerateImage(2, 200, usage_flag);

        if(!_images_of_cyclic_curves[1])
        {
            cout << "Couldn't generate CyclicCurve" << endl;
            return;
        }

        if(!_images_of_cyclic_curves[1]->UpdateVertexBufferObjects(_derivatives_scale, usage_flag))
        {
             cout << "Could_not_create_the_vertex_buffer_object_of_the_cyclic_curve!" << endl;
        }

        nknot = 5;
        knot_vector[2].ResizeRows(nknot);
        points[2].ResizeRows(nknot);
        points[2][0] = DCoordinate3(0, 0, 0);
        points[2][1] = DCoordinate3(-10, 0, -30);
        points[2][2] = DCoordinate3(-20, 0, 20);
        points[2][3] = DCoordinate3(20, 0, 20);
        points[2][4] = DCoordinate3(10, 0, -30);
        step = TWO_PI / nknot;
        for(int i = 0; i < nknot; i++)
        {
            knot_vector[2][i] = i*step;
        }
        _cyclic_curves[2] = nullptr;
        _images_of_cyclic_curves[2] = nullptr;

        _cyclic_curves[2] = new (nothrow) CyclicCurve3(2, usage_flag);

        if(!_cyclic_curves[2]->UpdateDataForInterpolation(knot_vector[2], points[2]))
        {
            cout << "The update was unsuccessful" << std::endl;
            return;
        }

        if(!_cyclic_curves[2]->UpdateVertexBufferObjectsOfData(usage_flag))
        {
            cout << "The update was unsuccessful" << std::endl;
            return;
        }
        _images_of_cyclic_curves[2] = _cyclic_curves[2]->GenerateImage(2, 200, usage_flag);

        if(!_images_of_cyclic_curves[2])
        {
            cout << "Couldn't generate CyclicCurve" << endl;
            return;
        }

        if(!_images_of_cyclic_curves[2]->UpdateVertexBufferObjects(_derivatives_scale, usage_flag))
        {
             cout << "Could_not_create_the_vertex_buffer_object_of_the_cyclic_curve!" << endl;
        }

        // Approximation curves
        step = TWO_PI / (5);

        _cyclic_curves[3] = nullptr;
        _images_of_cyclic_curves[3] = nullptr;

        _cyclic_curves[3] = new (nothrow) CyclicCurve3(2, usage_flag);

        if(!_cyclic_curves[3])
        {
            cout << "Couldn't generate CyclicCurve" << endl;
            return;
        }

        CyclicCurve3& curve= *_cyclic_curves[3];

        points[3].ResizeRows(5);
        for(GLuint i = 0; i < 5; i++)
        {
            DCoordinate3 &cp = curve[i];
            int t = i * step;

            points[3][i] = DCoordinate3(sin(t) * 50, 0, cos(t) * 50);
            cp[0] = points[3][i].x();
            cp[1] = points[3][i].y();
            cp[2] = points[3][i].z();
        }

        if(!_cyclic_curves[3]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW))
        {
            cout << "Could_not_create_the_vertex_buffer_object_of_the_cyclic_curve!" << endl;
        }

        _images_of_cyclic_curves[3] = _cyclic_curves[3]->GenerateImage(2, _cyclic_div_point_count, usage_flag);

        if(!_images_of_cyclic_curves[3])
        {
            cout << "Couldn't generate CyclicCurve" << endl;
            return;
        }

        if(!_images_of_cyclic_curves[3]->UpdateVertexBufferObjects(_derivatives_scale, usage_flag))
        {
             cout << "Could_not_create_the_vertex_buffer_object_of_the_cyclic_curve!" << endl;
             return;
        }

    }

    void GLWidget::paintSelectedCyclicCurve() {

        if(_show_cyclic_curve) {

            glPushMatrix();
            glColor3f(1.0f, 0.0f, 0.0f);

            if(_selected_cyclic_curve == 3) {
                glTranslated(-7,0,-3);
            }

            if(_selected_cyclic_curve < 2) {
                glTranslated(0,4,0);
            }

            _images_of_cyclic_curves[_selected_cyclic_curve]->RenderDerivatives(0, GL_LINE_STRIP);
            if(_selected_cyclic_curve < 3) {
                glBegin(GL_POINTS);
                glColor3f(0.0f ,0.0f, 1.0f);
                for(GLuint i = 0 ; i < points[_selected_cyclic_curve].GetRowCount() ; i++)
                   glVertex3d(points[_selected_cyclic_curve][i].x(),points[_selected_cyclic_curve][i].y(),points[_selected_cyclic_curve][i].z());
                glEnd();

            } else {
                _cyclic_curves[_selected_cyclic_curve]->RenderData(GL_POINTS);
                _cyclic_curves[_selected_cyclic_curve]->RenderData();
            }

            glPointSize(5.0f);
            if (_show_tangent) {
                glColor3f(0.0f, 0.5f, 0.0f);
                _images_of_cyclic_curves[_selected_cyclic_curve]->RenderDerivatives(1, GL_LINES);
                _images_of_cyclic_curves[_selected_cyclic_curve]->RenderDerivatives(1, GL_POINTS);
            }

            if (_show_acceleration_vector) {
                glColor3f(1.0f, 0.5f, 0.9f);
                _images_of_cyclic_curves[_selected_cyclic_curve]->RenderDerivatives(2, GL_LINES);
                _images_of_cyclic_curves[_selected_cyclic_curve]->RenderDerivatives(2, GL_POINTS);
            }

            glPopMatrix();
        }
}

    bool GLWidget::initalizeParametricCurves()
    {
        _parametric_curves.ResizeColumns(_parametric_curves_count);

        RowMatrix<ParametricCurve3::Derivative> spiral_on_cone_derivatives(3);
        spiral_on_cone_derivatives[0] = spiral_on_cone::d0;
        spiral_on_cone_derivatives[1] = spiral_on_cone::d1;
        spiral_on_cone_derivatives[2] = spiral_on_cone::d2;

        _parametric_curves[0] = nullptr;
        _parametric_curves[0] = new (nothrow) ParametricCurve3(spiral_on_cone_derivatives, spiral_on_cone::u_min, spiral_on_cone::u_max);

        if (!_parametric_curves[0])
        {
           destroyParametricCurves(0);
           return false;
        }

        RowMatrix<ParametricCurve3::Derivative> circular_helix_derivatives(3);
        circular_helix_derivatives[0] = circular_helix::d0;
        circular_helix_derivatives[1] = circular_helix::d1;
        circular_helix_derivatives[2] = circular_helix::d2;

        _parametric_curves[1] = nullptr;
        _parametric_curves[1] = new (nothrow) ParametricCurve3(circular_helix_derivatives, circular_helix::u_min, circular_helix::u_max);

        if (!_parametric_curves[1])
        {
           destroyParametricCurves(1);
           return false;
        }


        RowMatrix<ParametricCurve3::Derivative> rose_derivatives(3);
        rose_derivatives[0] = rose::d0;
        rose_derivatives[1] = rose::d1;
        rose_derivatives[2] = rose::d2;

        _parametric_curves[2] = nullptr;
        _parametric_curves[2] = new (nothrow) ParametricCurve3(rose_derivatives, rose::u_min, rose::u_max);

        if (!_parametric_curves[2])
        {
           destroyParametricCurves(2);
           return false;
        }


        RowMatrix<ParametricCurve3::Derivative> torus_knot_derivatives(3);
        torus_knot_derivatives[0] = torus_knot::d0;
        torus_knot_derivatives[1] = torus_knot::d1;
        torus_knot_derivatives[2] = torus_knot::d2;

        _parametric_curves[3] = nullptr;
        _parametric_curves[3] = new (nothrow) ParametricCurve3(torus_knot_derivatives, torus_knot::u_min, torus_knot::u_max);

        if (!_parametric_curves[3])
        {
           destroyParametricCurves(3);
           return false;
        }

        RowMatrix<ParametricCurve3::Derivative> cyclo_derivates(3);
        cyclo_derivates[0] = cyclo::d0;
        cyclo_derivates[1] = cyclo::d1;
        cyclo_derivates[2] = cyclo::d2;

        _parametric_curves[4] = nullptr;
        _parametric_curves[4] = new (nothrow) ParametricCurve3(cyclo_derivates, cyclo::u_min, cyclo::u_max);

        if (!_parametric_curves[4])
        {
           destroyParametricCurves(4);
           return false;
        }

        RowMatrix<ParametricCurve3::Derivative> spherical_sinusoid_derivatives(3);
        spherical_sinusoid_derivatives[0] = spherical_sinusoid::d0;
        spherical_sinusoid_derivatives[1] = spherical_sinusoid::d1;
        spherical_sinusoid_derivatives[2] = spherical_sinusoid::d2;

        _parametric_curves[5] = nullptr;
        _parametric_curves[5] = new (nothrow) ParametricCurve3(spherical_sinusoid_derivatives, spherical_sinusoid::u_min, spherical_sinusoid::u_max);

        if (!_parametric_curves[5])
        {
           destroyParametricCurves(5);
           return false;
        }

        RowMatrix<ParametricCurve3::Derivative> clelia_derivatives(3);
        clelia_derivatives[0] = clelia::d0;
        clelia_derivatives[1] = clelia::d1;
        clelia_derivatives[2] = clelia::d2;

        _parametric_curves[6] = nullptr;
        _parametric_curves[6] = new (nothrow) ParametricCurve3(clelia_derivatives, clelia::u_min, clelia::u_max);

        if (!_parametric_curves[6])
        {
           destroyParametricCurves(6);
           return false;
        }

        RowMatrix<ParametricCurve3::Derivative> basin_derivatives(3);
        basin_derivatives[0] = basin::d0;
        basin_derivatives[1] = basin::d1;
        basin_derivatives[2] = basin::d2;

        _parametric_curves[7] = nullptr;
        _parametric_curves[7] = new (nothrow) ParametricCurve3(basin_derivatives, basin::u_min, basin::u_max);

        if (!_parametric_curves[7])
        {
           destroyParametricCurves(7);
           return false;
        }

        GLenum usage_flag = GL_STATIC_DRAW;

        _image_of_parametric_curves.ResizeColumns(_parametric_curves_count);
        for (GLuint i = 0; i < _parametric_curves_count; i++)
        {
            _image_of_parametric_curves[i] = _parametric_curves[i]->GenerateImage(_div_point_count, usage_flag);

            if (!_image_of_parametric_curves[i] || !_image_of_parametric_curves[i]->UpdateVertexBufferObjects(_scale, usage_flag))
            {
                destroyParametricCurves(_parametric_curves_count);
                destroyImages(i);
                return false;
            }
        }

        return true;
    }

    bool GLWidget::paintParametricCurves()
    {
        if (!_image_of_parametric_curves[_selected_parametric_curve])
        {
             return false;
        }

        glColor3f(1.0f, 0.0f, 0.0f);
        _image_of_parametric_curves[_selected_parametric_curve]->RenderDerivatives(0, GL_LINE_STRIP);
        glPointSize(5.0f);


        if (_show_tangents)
        {
             glColor3f(0.0f, 0.5f, 0.0f);
             _image_of_parametric_curves[_selected_parametric_curve]->RenderDerivatives(1, GL_LINES);
             _image_of_parametric_curves[_selected_parametric_curve]->RenderDerivatives(1, GL_POINTS);

        }

        if (_show_acceleration_vectors)
        {
             glColor3f(0.1f, 0.5f, 0.9f);
            _image_of_parametric_curves[_selected_parametric_curve]->RenderDerivatives(2, GL_LINES);
            _image_of_parametric_curves[_selected_parametric_curve]->RenderDerivatives(2, GL_POINTS);

        }
        glPointSize(1.0f);
        return true;
    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(w) / static_cast<double>(h);

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        update();
    }
    //--------------------------------
    GLWidget::~GLWidget(){

    }
    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            update();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            update();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            update();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            update();
        }
    }

    void GLWidget::set_trans_x(double value)
    {

        if (_trans_x != value)
        {
            _trans_x = value;
            update();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            update();
        };
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            update();
        }
    }

    void GLWidget::setParametricCurveIndex(int index)
    {
        _selected_parametric_curve = index;
        update();
    }

    void GLWidget::setSelectedCyclicCurve(int index)
    {
        _selected_cyclic_curve = index;
        emit setSelectedX(points[_selected_cyclic_curve][_selected_point].x());
        emit setSelectedY(points[_selected_cyclic_curve][_selected_point].y());
        emit setSelectedZ(points[_selected_cyclic_curve][_selected_point].z());
        if(_selected_cyclic_curve < 3) {
            emit distanceSignal(0.5);
        }
        update();
    }

    void GLWidget::set_scale(double scale)
    {
        GLenum usage_flag = GL_STATIC_DRAW;
        _scale = scale;
        for(GLuint i = 0 ; i < _parametric_curves_count; i++) {
            _image_of_parametric_curves[i]->UpdateVertexBufferObjects(_scale, usage_flag);
            if (!_image_of_parametric_curves[i] || !_image_of_parametric_curves[i]->UpdateVertexBufferObjects(_scale, usage_flag))
            {
                destroyImages(_parametric_curves_count);
                throw Exception("Couldn't update div_point_count");
            }
        }
        update();
    }

    void GLWidget::set_div_point_count(int div_point_count)
    {
        GLenum usage_flag = GL_STATIC_DRAW;
        _div_point_count = div_point_count;
        destroyImages(_parametric_curves_count);
        for (GLuint i = 0; i < _parametric_curves_count; i++)
        {
            _image_of_parametric_curves[i] = _parametric_curves[i]->GenerateImage(_div_point_count, usage_flag);
            if (!_image_of_parametric_curves[i] || !_image_of_parametric_curves[i]->UpdateVertexBufferObjects(_scale, usage_flag))
            {
                destroyImages(_parametric_curves_count);
                throw Exception("Couldn't update div_point_count");
            }
        }
        update();
    }

    void GLWidget::setVisibilityOfTangents(bool visibility)
    {
        _show_tangents = visibility;
         update();
    }

    void GLWidget::setVisibilityOfAccelerationVectors(bool visibility)
    {
        _show_acceleration_vectors = visibility;
         update();
    }

    void GLWidget::setVisibilityOfTangent(bool visibility)
    {
        _show_tangent = visibility;
         update();
    }

    void GLWidget::setVisiblityOfAccelerationVector(bool visibility)
    {
        _show_acceleration_vector = visibility;
         update();
    }

    void GLWidget::setVisibilityOfCyclicCurve(bool visibility)
    {
        _show_cyclic_curve = visibility;
         update();
    }

    void GLWidget::setSpeedOfSelectedCurve(int value) {
        _speed[_selected_cyclic_curve] = value;
        update();
    }


    void GLWidget::setSelectedPoint(int index) {
        _selected_point = index;
        emit setSelectedX(points[_selected_cyclic_curve][_selected_point].x());
        emit setSelectedY(points[_selected_cyclic_curve][_selected_point].y());
        emit setSelectedZ(points[_selected_cyclic_curve][_selected_point].z());
        if(_selected_cyclic_curve < 3) {
            emit distanceSignal(0.5);
        }
    }

    void GLWidget::setSelectedXSlot(double value) {
        points[_selected_cyclic_curve][_selected_point].x() = value;
        destroyCyclicCurveImage(_selected_cyclic_curve);
        updateCyclicCurveImage(_selected_cyclic_curve);
        update();
    }
    void GLWidget::setSelectedYSlot(double value) {
        points[_selected_cyclic_curve][_selected_point].y() = value;
        destroyCyclicCurveImage(_selected_cyclic_curve);
        updateCyclicCurveImage(_selected_cyclic_curve);
        update();
    }

    void GLWidget::setSelectedZSlot(double value) {
        points[_selected_cyclic_curve][_selected_point].z() = value;
        destroyCyclicCurveImage(_selected_cyclic_curve);
        updateCyclicCurveImage(_selected_cyclic_curve);
        update();
    }

    void GLWidget::distanceSlot(double value) {
        if(_selected_point != 0 && _selected_point != 4) {
            knot_vector[_selected_cyclic_curve][_selected_point] = (1 - value) * knot_vector[_selected_cyclic_curve][_selected_point - 1] + value * knot_vector[_selected_cyclic_curve][_selected_point + 1];
        }
        destroyCyclicCurveImage(_selected_cyclic_curve);
        updateCyclicCurveImage(_selected_cyclic_curve);
        update();
    }

    void GLWidget::destroyCyclicCurveImage(int index) {
        delete _images_of_cyclic_curves[index];
        _images_of_cyclic_curves[index] = nullptr;
    }



    void GLWidget::setSelectedSurface(int index) {
        _selected_parametric_surface = index;
        update();
    }

    void GLWidget::setSelectedMaterial(int index) {
        _selected_material = index;
        update();
    }

    void GLWidget::setSelectedTexture(int index) {
        _selected_texture = index;
        update();
    }

    void GLWidget::setVisibilityOfTexture(bool visibility) {
        _show_texture = visibility;
        update();
    }

    void GLWidget::setSelectedShader(int index) {
        _selected_shader = index;
        update();
    }

    void GLWidget::setShaderScale(double value) {
        if(value != _shader_scale) {
            _shader_scale = value;

            _shaders[_selected_shader].Enable();

            _shaders[3].SetUniformVariable1f("scale_factor", _shader_scale);
            _shaders[3].SetUniformVariable1f("smoothing", _shader_shading);
            _shaders[3].SetUniformVariable1f("shading", _shader_smoothing);

             _shaders[_selected_shader].Disable();
             update();
        }
    }

    void GLWidget::setSmoothing(double value) {
        if(value != _shader_smoothing) {
            _shader_smoothing = value;

            _shaders[_selected_shader].Enable();

            _shaders[3].SetUniformVariable1f("scale_factor", _shader_scale);
            _shaders[3].SetUniformVariable1f("smoothing", _shader_shading);
            _shaders[3].SetUniformVariable1f("shading", _shader_smoothing);

             _shaders[_selected_shader].Disable();
             update();
        }
    }

    void GLWidget::setShading(double value) {
        if(value != _shader_shading) {
            _shader_shading = value;

            _shaders[_selected_shader].Enable();

            _shaders[3].SetUniformVariable1f("scale_factor", _shader_scale);
            _shaders[3].SetUniformVariable1f("smoothing", _shader_shading);
            _shaders[3].SetUniformVariable1f("shading", _shader_smoothing);

             _shaders[_selected_shader].Disable();
             update();
        }
    }

    void GLWidget::setRed(double value) {
        if(value != _red)
        {
            _shaders[_selected_shader].Enable();
            _red = value;
            _shaders[2].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            _shaders[_selected_shader].Disable();
            update();
        }
    }

    void GLWidget::setBlue(double value) {
        if(value != _blue)
        {
            _shaders[_selected_shader].Enable();
            _blue = value;
            _shaders[2].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            _shaders[_selected_shader].Disable();
            update();
        }

    }void GLWidget::setGreen(double value) {
        if(value != _green)
        {
            _shaders[_selected_shader].Enable();
            _green = value;
            _shaders[2].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            _shaders[_selected_shader].Disable();
            update();
        }
    }

   void GLWidget::setHermitePatchIndex(int index) {
       _selected_hermite_patch_point = index;

       switch(index)
       {
            case 0:
           {
               emit HermitePatchPointChangeX((*_bicubic_hermite_patch3)(0,0).x());
               emit HermitePatchPointChangeY((*_bicubic_hermite_patch3)(0,0).y());
               emit HermitePatchPointChangeZ((*_bicubic_hermite_patch3)(0,0).z());

               emit HermitePatchPointChangeUX((*_bicubic_hermite_patch3)(2,0).x());
               emit HermitePatchPointChangeUY((*_bicubic_hermite_patch3)(2,0).y());
               emit HermitePatchPointChangeUZ((*_bicubic_hermite_patch3)(2,0).z());

               emit HermitePatchPointChangeVX((*_bicubic_hermite_patch3)(0,2).x());
               emit HermitePatchPointChangeVY((*_bicubic_hermite_patch3)(0,2).y());
               emit HermitePatchPointChangeVZ((*_bicubic_hermite_patch3)(0,2).z());

               emit HermitePatchPointChangeTX((*_bicubic_hermite_patch3)(2,2).x());
               emit HermitePatchPointChangeTY((*_bicubic_hermite_patch3)(2,2).y());
               emit HermitePatchPointChangeTZ((*_bicubic_hermite_patch3)(2,2).z());
               break;
           }
            case 1:
           {

               emit HermitePatchPointChangeX((*_bicubic_hermite_patch3)(0,1).x());
               emit HermitePatchPointChangeY((*_bicubic_hermite_patch3)(0,1).y());
               emit HermitePatchPointChangeZ((*_bicubic_hermite_patch3)(0,1).z());

               emit HermitePatchPointChangeUX((*_bicubic_hermite_patch3)(2,1).x());
               emit HermitePatchPointChangeUY((*_bicubic_hermite_patch3)(2,1).y());
               emit HermitePatchPointChangeUZ((*_bicubic_hermite_patch3)(2,1).z());

               emit HermitePatchPointChangeVX((*_bicubic_hermite_patch3)(0,3).x());
               emit HermitePatchPointChangeVY((*_bicubic_hermite_patch3)(0,3).y());
               emit HermitePatchPointChangeVZ((*_bicubic_hermite_patch3)(0,3).z());

               emit HermitePatchPointChangeTX((*_bicubic_hermite_patch3)(2,3).x());
               emit HermitePatchPointChangeTY((*_bicubic_hermite_patch3)(2,3).y());
               emit HermitePatchPointChangeTZ((*_bicubic_hermite_patch3)(2,3).z());
               break;
           }

               case 2:
              {

                  emit HermitePatchPointChangeX((*_bicubic_hermite_patch3)(1,0).x());
                  emit HermitePatchPointChangeY((*_bicubic_hermite_patch3)(1,0).y());
                  emit HermitePatchPointChangeZ((*_bicubic_hermite_patch3)(1,0).z());

                  emit HermitePatchPointChangeUX((*_bicubic_hermite_patch3)(3,0).x());
                  emit HermitePatchPointChangeUY((*_bicubic_hermite_patch3)(3,0).y());
                  emit HermitePatchPointChangeUZ((*_bicubic_hermite_patch3)(3,0).z());

                  emit HermitePatchPointChangeVX((*_bicubic_hermite_patch3)(1,2).x());
                  emit HermitePatchPointChangeVY((*_bicubic_hermite_patch3)(1,2).y());
                  emit HermitePatchPointChangeVZ((*_bicubic_hermite_patch3)(1,2).z());

                  emit HermitePatchPointChangeTX((*_bicubic_hermite_patch3)(3,2).x());
                  emit HermitePatchPointChangeTY((*_bicubic_hermite_patch3)(3,2).y());
                  emit HermitePatchPointChangeTZ((*_bicubic_hermite_patch3)(3,2).z());
                  break;
              }

               case 3:
              {

                  emit HermitePatchPointChangeX((*_bicubic_hermite_patch3)(1,1).x());
                  emit HermitePatchPointChangeY((*_bicubic_hermite_patch3)(1,1).y());
                  emit HermitePatchPointChangeZ((*_bicubic_hermite_patch3)(1,1).z());

                  emit HermitePatchPointChangeUX((*_bicubic_hermite_patch3)(3,1).x());
                  emit HermitePatchPointChangeUY((*_bicubic_hermite_patch3)(3,1).y());
                  emit HermitePatchPointChangeUZ((*_bicubic_hermite_patch3)(3,1).z());

                  emit HermitePatchPointChangeVX((*_bicubic_hermite_patch3)(1,3).x());
                  emit HermitePatchPointChangeVY((*_bicubic_hermite_patch3)(1,3).y());
                  emit HermitePatchPointChangeVZ((*_bicubic_hermite_patch3)(1,3).z());

                  emit HermitePatchPointChangeTX((*_bicubic_hermite_patch3)(3,3).x());
                  emit HermitePatchPointChangeTY((*_bicubic_hermite_patch3)(3,3).y());
                  emit HermitePatchPointChangeTZ((*_bicubic_hermite_patch3)(3,3).z());
                  break;
              }
       }
   }

   void GLWidget::showHermitePatchFirstOrder(bool visibility) {
        _show_hermite_patch_first_derivatives = visibility;
        update();
   }

   void GLWidget::showHermitePatchSecondOrder(bool visibility) {
        _show_hermite_patch_second_derivatives = visibility;
        update();
   }

    void GLWidget::updateCyclicCurveImage(int index) {

        GLenum usage_flag = GL_STATIC_DRAW;
        if(index < 3) {

            if(!_cyclic_curves[index]->UpdateDataForInterpolation(knot_vector[index], points[index]))
            {
                cout << "The update was unsuccessful" << std::endl;
                return;
            }

            if(!_cyclic_curves[index]->UpdateVertexBufferObjectsOfData(usage_flag))
            {
                cout << "The update was unsuccessful" << std::endl;
                return;
            }
            _images_of_cyclic_curves[index] = _cyclic_curves[index]->GenerateImage(2, 200, usage_flag);

            if(!_images_of_cyclic_curves[index])
            {
                cout << "Couldn't generate CyclicCurve" << endl;
                return;
            }

            if(!_images_of_cyclic_curves[index]->UpdateVertexBufferObjects(_derivatives_scale, usage_flag))
            {
                 cout << "Could_not_create_the_vertex_buffer_object_of_the_cyclic_curve!" << endl;
            }
        } else {
            CyclicCurve3& curve= *_cyclic_curves[index];

            for(GLuint i = 0; i < 5; i++)
            {
                DCoordinate3 &cp = curve[i];

                cp[0] = points[3][i].x();
                cp[1] = points[3][i].y();
                cp[2] = points[3][i].z();
            }

            if(!_cyclic_curves[index]->UpdateVertexBufferObjectsOfData(GL_STATIC_DRAW))
            {
                cout << "Could_not_create_the_vertex_buffer_object_of_the_cyclic_curve!" << endl;
            }

            _images_of_cyclic_curves[index] = _cyclic_curves[3]->GenerateImage(2, _cyclic_div_point_count, usage_flag);

            if(!_images_of_cyclic_curves[index])
            {
                cout << "Couldn't generate CyclicCurve" << endl;
                return;
            }

            if(!_images_of_cyclic_curves[index]->UpdateVertexBufferObjects(_derivatives_scale, usage_flag))
            {
                 cout << "Could_not_create_the_vertex_buffer_object_of_the_cyclic_curve!" << endl;
                 return;
            }

        }
    }

    void GLWidget::destroyParametricCurves(int _count)
    {
        for (int i = 0; i < _count; i++)
        {
             if (_parametric_curves[i])
             {
                 delete _parametric_curves[i];
                 _parametric_curves[i] = nullptr;
             }
        }
    }

    void GLWidget::destroyImages(int _count)
    {
        for(int i = 0 ; i < _count ; i++)
        {
            if (_image_of_parametric_curves[i])
            {
                delete _image_of_parametric_curves [i];
                _image_of_parametric_curves[i] = nullptr;
            }
        }
    }

}
