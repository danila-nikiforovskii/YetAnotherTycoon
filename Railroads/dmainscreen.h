#ifndef DMAINSCREEN_H
#define DMAINSCREEN_H
#include <QGLWidget>
#include <QGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QOpenGLFramebufferObject>
#include <QOpenGLVertexArrayObject>
#include <defines.h>
#include <dterraincell.h>
#include <dnetworknode.h>
#include <drailfragment.h>
#include <dnetworklist.h>
#include <dloco.h>
#include <dpath.h>

struct vec3 { GLfloat x; GLfloat y; GLfloat z;};



struct DSprite
{
    bool enabled = false;
    int atlas_i = 0;
    int atlas_j = 0;
    texture_rotation rotation = d0;
};

struct NodeID
{
    int i;
    int j;
    NetworkNodeTypes type;
};


struct DMagnet
{
        NodeID address;
        DNetworkListElement * newelement = nullptr;
        bool valid = false;
        DMagnet* prev = nullptr;
};

struct ObstructionPointerTile
{
    DNetworkListElement * u = nullptr;
    DNetworkListElement * r = nullptr;
    DNetworkListElement * l = nullptr;
    DNetworkListElement * d = nullptr;
};

class DMainScreen : public QGLWidget,   protected QGLFunctions
{
public:
    DMainScreen(QWidget *parent);
    void draw();
    int viewport_width;
    int viewport_height;

    QPoint coord00 (texture_rotation rot);
    QPoint coord01 (texture_rotation rot);
    QPoint coord10 (texture_rotation rot);
    QPoint coord11 (texture_rotation rot);

    void drawhex(float centerx, float centery, float width, int index, int index2);
    void drawhex_multi(float centerx, float centery, float width, int index, int index_red,  int index_yellow, int index_green, int index_cyan, int index_blue, int index_black);
    void drawedgequadA(float centerx, float centery, float width, int variety, int config, bool ismouth);
    void drawedgequadB(float centerx, float centery, float width, int variety, int config, bool ismouth);

    //void RENDER_BASIC_drawsprite();
    void RENDER_BASIC_terrainquad(int x, int y, int z0, int z1, int z2, int z3, texture_rotation rot);
    void RENDER_BASIC_CALCULATE_NORMALS();
    void RENDER_BASIC_multiquad(int x_ul, int y_ul, int tx_ul, int ty_ul, int tx_dr, int ty_dr, texture_rotation rot  );

    QOpenGLShaderProgram *shader, *treeshader, *flatshader, *rivershader, *cliffshader, *simpleshader ;
    QOpenGLShaderProgram *uishader, *uimousemapshader;

    bool CornerLimits(int i,int j);
    bool HorLimits(int i,int j);
    bool VertLimits(int i,int j);

    GLuint textureID[8];

    QOpenGLFramebufferObject* fbo;
    QOpenGLFramebufferObject* mousemapfbo;

    int map[WIDTH+1][HEIGHT+1]; // heightmap
    DTerrainCell cells[WIDTH][HEIGHT];

    DCornerNode CornerNodes[WIDTH+1][HEIGHT+1]; // stores the configuration of the rails connected to the node
    DHorizontalSideNode HorizontalSideNodes[WIDTH][HEIGHT+1]; // stores the configuration of the rails connected to the node
    DVerticalSideNode VerticalSideNodes[WIDTH+1][HEIGHT]; // stores the configuration of the rails connected to the node

    ObstructionPointerTile obstructions[WIDTH][HEIGHT];

    //QList<DRailFragment> railnetwork;

    DNetworkList * NetworkList;

    DNetworkList * RoadList;

    QList<DLoco> LocoList;
    vec3 normals[WIDTH+1][HEIGHT+1];

    uint LFSR[32];
    uint CAR_ARBITER[32];
    uint CAR_1[32];
    uint CAR_2[32];
    unsigned long long int seed;
    unsigned long long DRandom();
    void Randomize();
    float DFloatRandom();
    int painttimer;
    int ticktimer;



    int waterframe;






    int i_drunk,j_drunk;
    int i_check1,j_check1;
    int i_start,j_start;
    int alpha;
    int cursor_x,cursor_y;
    int mx,my;


    int w = 66;
    int sx,sy = 0;
    int edge = 0;

    bool READY = false;
    bool moving = false;
    bool zooming = false;

    int movingx = 0;
    int movingy = 0;

    int CurrentTool = 3;
    bool show_edge = false;
    bool OpenGL_INIT = false;

    int paint_timer_interval;
    int tick_timer_interval;


   // QList<DRailFragment> network;
  //  RailFragmentTypes newrail;

    GLfloat crossx(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);
    GLfloat crossy(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);
    GLfloat crossz(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);

    //QList<DRailFragment> construction_network;

    QImage mousemap;
    unsigned gethexindex(unsigned i, unsigned v);
    void GAMEPLAY_MAIN_MAPINIT();
    void bulldose_rail(DNetworkListElement *dead);
    void RENDER_DRAW_TERRAIN(int mod);
    void RENDER_GRID();
    void RENDER_DRAW_UI (int mod);
    void RENDER_DRAW_MAGNETS(bool ifmm);
    void RENDER_PILOT_NETWORK();

    void PREPARE_MAGNETS_START();
    void DESTROY_MAGNETS();
    void PREPARE_MAGNETS_END();
        void PREPARE_MAGNETS_CORNERS();

        void PREPARE_MAGNETS_UL();
        void PREPARE_MAGNETS_UR();
        void PREPARE_MAGNETS_DL();
        void PREPARE_MAGNETS_DR();

        void PREPARE_MAGNETS_HORIZONTAL_SIDES();

        void PREPARE_MAGNETS_U();
        void PREPARE_MAGNETS_D();

        void PREPARE_MAGNETS_VERTICAL_SIDES();

        void PREPARE_MAGNETS_L();
        void PREPARE_MAGNETS_R();

     void PREPARE_ROAD_MAGNETS_END();
     void PREPARE_ROAD_MAGNETS_CORNERS();

     void PREPARE_ROAD_MAGNETS_UL();
     void PREPARE_ROAD_MAGNETS_UR();
     void PREPARE_ROAD_MAGNETS_DL();
     void PREPARE_ROAD_MAGNETS_DR();


     void PREPARE_ROAD_MAGNETS_HORIZONTAL_SIDES();
     void PREPARE_ROAD_MAGNETS_U();
     void PREPARE_ROAD_MAGNETS_D();


     void PREPARE_ROAD_MAGNETS_VERTICAL_SIDES();

     void PREPARE_ROAD_MAGNETS_L();
     void PREPARE_ROAD_MAGNETS_R();



    bool check_obstruction(DNetworkListElement* element);
    bool check_obstruction_conditional(DNetworkListElement * element, QList<DNetworkListElement *> allowed);

    void RENDER_NETWORK();//QList<DRailFragment> *network);


    bool terrain_precedence(int t1, int t2);

    int GetCornerTypeFromID(long unsigned int id);
    int GetCornerXFromID(long unsigned int id);
    int GetCornerYFromID(long unsigned int id);

    QPoint GetCornerNode(long unsigned int id);
    QPoint GetHorSideNode(long unsigned int id);
    QPoint GetVerSideNode(long unsigned int id);

    int GetSideTypeFromID(long unsigned int id);
    int GetSideXFromID(long unsigned int id);
    int GetSideYFromID(long unsigned int id);

    int GetXfromRGB(long unsigned int rgb);
    int GetYfromRGB(long unsigned  int rgb);
    long unsigned int LastHoverID;
    long unsigned int CurrentHoverID;

    unsigned int LastHoverGroup;
    int state;

    void increaseHeight(int x, int y);
    void decreaseHeight(int x, int y);

    int test_deg = 0;

    NodeID RailStart, RailEnd;

    QList<DMagnet*> magnets;

    DMagnet * HoverMagnet = nullptr;
    GLfloat getXfrom3D (GLfloat x, GLfloat y ,GLfloat z);
    GLfloat getYfrom3D (GLfloat x, GLfloat y ,GLfloat z);
    GLfloat getXfromVec3 (vec3 vec);
    GLfloat getYfromVec3 (vec3 vec);


    void RENDER_DRAW_3D_CAR (GLfloat i, GLfloat j, GLfloat degree);

    void RENDER_STOCK();

    void RENDER_3D_QUAD (GLfloat centroid_x, GLfloat centroid_y, vec3 vert1, vec3 vert2, vec3 vert3, vec3 vert4);
    //
    //    2  4
    //    1  3
protected:
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);



    //void mouseDoubleClickEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    void initializeGL();
};

#endif // DMAINSCREEN_H
