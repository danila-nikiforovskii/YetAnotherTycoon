#include "dmainscreen.h"
#include "math.h"
#define PI 3.14159f
#include <QDateTime>
#include <QApplication>
#include <QQueue>
#include <QDebug>


DMainScreen::DMainScreen(QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    Q_UNUSED(parent);
    waterframe = 0;
    seed = QDateTime::currentMSecsSinceEpoch()%ULONG_MAX;
    cursor_x = -1; cursor_y = -1;
    setMouseTracking(true);
    setFocusPolicy(Qt::ClickFocus);

    //    for (int i=0;i<WIDTH;i++)
    //        for(int j=-HEIGHT2;j<=HEIGHT2;j++)
    //        {
    //            map[i][j+HEIGHT2] = 0;
    //            GameMap[i][j+HEIGHT2].baseterain = 1;
    //            GameMap[i][j+HEIGHT2].forest = 0;

    //            for (int tre=0;tre<61;tre++)
    //                GameMap[i][j+HEIGHT2].tree[tre] = 0;
    //        }
    viewport_width = 128;
    viewport_height = 128;
    fbo = nullptr;
    mousemapfbo = nullptr;
    //
    GAMEPLAY_MAIN_MAPINIT();

    LastHoverID = -1;

    //--------------------------------
    maintimer = this->startTimer(33,Qt::PreciseTimer);

    NetworkList = new DNetworkList;
}

void DMainScreen::GAMEPLAY_MAIN_MAPINIT()
{

    // init height map

    for (uint ii01 = 0; ii01 <= WIDTH; ii01++)
        for (uint jj01 = 0; jj01 <= HEIGHT; jj01++)
            {
                map[ii01][jj01]=0;
            }

    map[5][5]=2;
    map[4][5]=2;
    map[5][4]=2;
    map[4][4]=2;


    for (int jj = 1; jj<=4;jj++)
        {
            map[8][2+jj]=jj;
            map[9][2+jj]=jj;


            map[8][15-jj]=jj;
            map[9][15-jj]=jj;

        }

    map[9][6]=8;
    map[8][6]=8;

    map[10][7]=-5;

    RENDER_BASIC_CALCULATE_NORMALS();

    // init mapcells

    for (uint i=0;i<WIDTH;i++)
        for (uint j=0;j<HEIGHT;j++)
            {
                cells[i][j].setX(i);
                cells[i][j].setX(j);

                cells[i][j].type = TERRAIN_TYPES_GRASS_GREEN;
                cells[i][j].variety = ((i*DRandom()+j*DRandom())*DRandom())%8;

                cells[i][j].seavariety = ((i*DRandom()+j*DRandom())*DRandom())%32;
                cells[i][j].nextvariety = ((i*DRandom()+j*DRandom())*DRandom())%32;
                cells[i][j].seaphase = ((i*DRandom()+j*DRandom())*DRandom())%64;
            }

  for (int i=0;i<WIDTH;i++)
      for(int j=0;j<WIDTH;j++)
          {
                obstructions[i][j].u= nullptr;
                obstructions[i][j].d= nullptr;
                obstructions[i][j].l= nullptr;
                obstructions[i][j].r= nullptr;
          }

  for (int i=0;i<=WIDTH;i++)
      for(int j=0;j<=HEIGHT;j++)
          {
                CornerNodes[i][j].i = i;
                CornerNodes[i][j].j = j;
          }


  for (int i=0;i<WIDTH;i++)
      for(int j=0;j<=HEIGHT;j++)
          {
                HorizontalSideNodes[i][j].i = i;
                HorizontalSideNodes[i][j].j = j;
          }


  for (int i=0;i<=WIDTH;i++)
      for(int j=0;j<HEIGHT;j++)
          {
                VerticalSideNodes[i][j].i = i;
                VerticalSideNodes[i][j].j = j;               
          }






}


void DMainScreen::RENDER_BASIC_CALCULATE_NORMALS()
{

    for (int x = 1; x<WIDTH; x++)
        for (int y = 1; y< HEIGHT; y++)
            {

                GLfloat scale = 0.25f;

                GLfloat z0 = static_cast<GLfloat>(map[x][y])*scale;
                GLfloat zup = static_cast<GLfloat>(map[x][y-1])*scale; ;
                GLfloat zdown =  static_cast<GLfloat>(map[x][y+1])*scale; ;
                GLfloat zleft =  static_cast<GLfloat>(map[x-1][y])*scale;  ;
                GLfloat zright =  static_cast<GLfloat>(map[x+1][y])*scale; ;

                GLfloat zul =  static_cast<GLfloat>(map[x-1][y-1])*scale;  ;
                GLfloat zur =  static_cast<GLfloat>(map[x+1][y-1])*scale; ;
                GLfloat zdr =  static_cast<GLfloat>(map[x+1][y+1])*scale; ;
                GLfloat zdl =  static_cast<GLfloat>(map[x-1][y+1])*scale; ;

                /* normals[x][y].x = +++;
            normals[x][y].y = crossy(1,0,zright-z0,0,1,zup-z0)+crossy(0,1,zup-z0,-1,0,zleft-z0)+crossy(-1,0,zleft-z0,0,-1,zdown-z0)+crossy(0,-1,zdown-z0,1,0,zright-z0);
            normals[x][y].z = crossz(1,0,zright-z0,0,1,zup-z0)+crossz(0,1,zup-z0,-1,0,zleft-z0)+crossz(-1,0,zleft-z0,0,-1,zdown-z0)+crossz(0,-1,zdown-z0,1,0,zright-z0);
           */
                //cross products are normalized

                normals[x][y].x = 0;
                normals[x][y].y = 0;
                normals[x][y].z = 0;

                if (abs(zul+z0)<abs(zleft+zup))
                    {
                        normals[x][y].x += 0.5*(crossx(0,1,zup-z0,-1,1,zul-z0)+crossx(-1,1,zul-z0,-1,0,zleft-z0));
                        normals[x][y].y += 0.5*(crossy(0,1,zup-z0,-1,1,zul-z0)+crossy(-1,1,zul-z0,-1,0,zleft-z0));
                        normals[x][y].z += 0.5*(crossz(0,1,zup-z0,-1,1,zul-z0)+crossz(-1,1,zul-z0,-1,0,zleft-z0));
                    }
                else
                    {
                        normals[x][y].x += crossx(0,1,zup-z0,-1,0,zleft-z0);
                        normals[x][y].y += crossy(0,1,zup-z0,-1,0,zleft-z0);
                        normals[x][y].z += crossz(0,1,zup-z0,-1,0,zleft-z0);
                    }

                if (abs(zur+z0)<abs(zright+zup))
                    {
                        normals[x][y].x += 0.5*(crossx(1,0,zright-z0,1,1,zur-z0)+crossx(1,1,zur-z0,0,1,zup-z0));
                        normals[x][y].y += 0.5*(crossy(1,0,zright-z0,1,1,zur-z0)+crossy(1,1,zur-z0,0,1,zup-z0));
                        normals[x][y].z += 0.5*(crossz(1,0,zright-z0,1,1,zur-z0)+crossz(1,1,zur-z0,0,1,zup-z0));
                    }
                else
                    {
                        normals[x][y].x += crossx(1,0,zright-z0,0,1,zup-z0);
                        normals[x][y].y += crossy(1,0,zright-z0,0,1,zup-z0);
                        normals[x][y].z += crossz(1,0,zright-z0,0,1,zup-z0);
                    }


                if (abs(zdl+z0)<abs(zleft+zdown))
                    {
                        normals[x][y].x += 0.5*(crossx(-1,0,zleft-z0,-1,-1,zdl-z0)+crossx(-1,-1,zdl-z0,0,-1,zdown-z0));
                        normals[x][y].y += 0.5*(crossy(-1,0,zleft-z0,-1,-1,zdl-z0)+crossy(-1,-1,zdl-z0,0,-1,zdown-z0));
                        normals[x][y].z += 0.5*(crossz(-1,0,zleft-z0,-1,-1,zdl-z0)+crossz(-1,-1,zdl-z0,0,-1,zdown-z0));

                    }
                else
                    {
                        normals[x][y].x += crossx(-1,0,zleft-z0,0,-1,zdown-z0);
                        normals[x][y].y += crossy(-1,0,zleft-z0,0,-1,zdown-z0);
                        normals[x][y].z += crossz(-1,0,zleft-z0,0,-1,zdown-z0);

                    }

                if (abs(zdr+z0)<abs(zright+zdown))
                    {
                        normals[x][y].x += 0.5*(crossx(0,-1,zdown-z0,1,-1,zdr-z0)+crossx(1,-1,zdr-z0,1,0,zright-z0));
                        normals[x][y].y += 0.5*(crossy(0,-1,zdown-z0,1,-1,zdr-z0)+crossy(1,-1,zdr-z0,1,0,zright-z0));
                        normals[x][y].z += 0.5*(crossz(0,-1,zdown-z0,1,-1,zdr-z0)+crossz(1,-1,zdr-z0,1,0,zright-z0));
                    }
                else
                    {
                        normals[x][y].x += crossx(0,-1,zdown-z0,1,0,zright-z0);
                        normals[x][y].y += crossy(0,-1,zdown-z0,1,0,zright-z0);
                        normals[x][y].z += crossz(0,-1,zdown-z0,1,0,zright-z0);
                    }


                // normals[x][y].x = normals[x][y].x*0.25;
                // normals[x][y].y = normals[x][y].y*0.25;
                // normals[x][y].z = normals[x][y].z*0.25;

            }


    for (int x = 0;x<=WIDTH;x++)
        {
            normals[x][0]=normals[x][1];
            normals[x][HEIGHT]=normals[x][HEIGHT-1];
        }

    for (int y=0;y<=WIDTH;y++)
        {
            normals[0][y] = normals[0][y+1];
            normals[WIDTH][y] = normals[WIDTH-1][y+1];
        }


}


void DMainScreen::timerEvent(QTimerEvent *event)
{

    if (!READY) READY = true;
    if (event->timerId() == maintimer)
        {
            waterframe = (waterframe+1)%(32*16);


            for (int i=0;i<WIDTH;i++)
                for (int j=0;j<HEIGHT;j++)
                    {
                        cells[i][j].seaphase =  (cells[i][j].seaphase +1)%(64);

                        if (cells[i][j].seaphase == 0)
                            {
                                cells[i][j].seavariety = cells[i][j].nextvariety;
                                cells[i][j].nextvariety = (cells[i][j].nextvariety + 1 + DRandom()%15)%16;
                            }
                    }
            if ( ( waterframe%2) == 0)
                test_deg = (test_deg + 90/6)%360;


            updateGL();
        }

}

unsigned long long DMainScreen::DRandom()
{
    seed = (seed*25214903917 + 11)%281474976710656;
    return seed;
}

float DMainScreen::DFloatRandom()
{
    seed = (seed*25214903917 + 11)%281474976710656;;
    return seed*1.0f/static_cast<float>(281474976710656);
}

void DMainScreen::draw()
{

}

void DMainScreen::initializeGL()
{
    textureID[0]=bindTexture(QPixmap(QString(GAME_ROOT_DIR).append("atlas.bmp")), GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    textureID[1]=bindTexture(QPixmap(QString(GAME_ROOT_DIR).append("trees.bmp")), GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    textureID[2]=bindTexture(QPixmap(QString(GAME_ROOT_DIR).append("rivers.bmp")), GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    textureID[7]=bindTexture(QPixmap(QString(GAME_ROOT_DIR).append("blank.bmp")), GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_2D);

    shader = new QOpenGLShaderProgram();
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,QString(GAME_ROOT_DIR).append("vertex.txt"));
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(GAME_ROOT_DIR).append("frag.txt"));
    shader->link();
    /* shader->bind();
    VertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    VertexBuffer->create();
    VertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    VertexBuffer->bind();
    VertexBuffer->allocate(vertices,sizeof(vertices[0])*91*dataXsize*dataYsize);

    vao = new QOpenGLVertexArrayObject( this );
    vao->create();
    vao->bind();

    watershader->enableAttributeArray("vv");
    watershader->enableAttributeArray("MTX");

    watershader->setAttributeBuffer("vv", GL_FLOAT, 0, 3, 5*sizeof(float));
    watershader->setAttributeBuffer("MTX", GL_FLOAT, 3*sizeof(float), 2, 5*sizeof(float));


    vao->release();
    shader->release();
  */

    simpleshader = new QOpenGLShaderProgram();
    simpleshader->addShaderFromSourceFile(QOpenGLShader::Vertex,QString(GAME_ROOT_DIR).append("vertex.txt"));
    simpleshader->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(GAME_ROOT_DIR).append("frag_simple.txt"));
    simpleshader->link();

    uishader = new QOpenGLShaderProgram();
    uishader->addShaderFromSourceFile(QOpenGLShader::Vertex,QString(GAME_ROOT_DIR).append("vertex_ui.txt"));
    uishader->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(GAME_ROOT_DIR).append("frag_ui.txt"));
    uishader->link();

    uimousemapshader = new QOpenGLShaderProgram();
    uimousemapshader->addShaderFromSourceFile(QOpenGLShader::Vertex,QString(GAME_ROOT_DIR).append("vertex_ui.txt"));
    uimousemapshader->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(GAME_ROOT_DIR).append("frag_ui_mm.txt"));
    uimousemapshader->link();



    treeshader = new QOpenGLShaderProgram();
    treeshader->addShaderFromSourceFile(QOpenGLShader::Vertex,QString(GAME_ROOT_DIR).append("vertex.txt"));
    treeshader->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(GAME_ROOT_DIR).append("frag_tree.txt"));
    treeshader->link();

    flatshader = new QOpenGLShaderProgram();
    flatshader->addShaderFromSourceFile(QOpenGLShader::Vertex,QString(GAME_ROOT_DIR).append("vertex.txt"));
    flatshader->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(GAME_ROOT_DIR).append("frag_flat.txt"));
    flatshader->link();

    rivershader = new QOpenGLShaderProgram();
    rivershader->addShaderFromSourceFile(QOpenGLShader::Vertex,QString(GAME_ROOT_DIR).append("vertex.txt"));
    rivershader->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(GAME_ROOT_DIR).append("frag_rivers.txt"));
    rivershader->link();

    cliffshader = new QOpenGLShaderProgram();
    cliffshader->addShaderFromSourceFile(QOpenGLShader::Vertex,QString(GAME_ROOT_DIR).append("vertex.txt"));
    cliffshader->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(GAME_ROOT_DIR).append("frag_cliff.txt"));
    cliffshader->link();

    simpleshader->bind();
    simpleshader->setUniformValue(simpleshader->uniformLocation("texture"), 6);
    simpleshader->release();


    initializeGLFunctions();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureID[2]);

    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, textureID[7]);

    shader->bind();
    shader->setUniformValue(shader->uniformLocation("texture"), 0);
    shader->setUniformValue(shader->uniformLocation("atlasx"), 0);
    shader->setUniformValue(shader->uniformLocation("atlasy"), 0);
    shader->setUniformValue(shader->uniformLocation("atlasx2"), 0);
    shader->setUniformValue(shader->uniformLocation("atlasy2"), 0);
    shader->release();

    treeshader->bind();
    treeshader->setUniformValue(treeshader->uniformLocation("texture"), 1);
    treeshader->setUniformValue(treeshader->uniformLocation("atlasx"), 0);
    treeshader->setUniformValue(treeshader->uniformLocation("atlasy"), 0);
    treeshader->release();

    simpleshader->bind();
    simpleshader->setUniformValue(simpleshader->uniformLocation("texture"), 6);
    simpleshader->release();

    flatshader->bind();
    flatshader->setUniformValue(flatshader->uniformLocation("col"),1.0f,1.0f,1.0f);
    flatshader->release();

    rivershader->bind();
    rivershader->setUniformValue(rivershader->uniformLocation("texture"), 2);
    rivershader->setUniformValue(rivershader->uniformLocation("atlasx"), 0);
    rivershader->setUniformValue(rivershader->uniformLocation("atlasy"), 0);
    rivershader->release();

    cliffshader->bind();
    cliffshader->setUniformValue(cliffshader->uniformLocation("texture"), 0);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx"), 0);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy"), 0);

    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_red"), 0);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_red"), 0);

    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_yellow"), 0);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_yellow"), 0);

    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_green"), 0);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_green"), 0);

    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_cyan"), 0);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_cyan"), 0);

    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_blue"), 0);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_blue"), 0);

    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_black"), 0);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_black"), 0);
    cliffshader->release();


    fbo = new QOpenGLFramebufferObject(QSize(viewport_width,viewport_height));
    mousemapfbo = new QOpenGLFramebufferObject(QSize(viewport_width,viewport_height));

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, fbo->texture());


    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);


    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    OpenGL_INIT = true;
}


bool DMainScreen::CornerLimits(int i,int j)

    {

        return (i>=0)&&(i<=WIDTH)&&(j>0)&&(j<=HEIGHT);

    }
bool DMainScreen::HorLimits(int i,int j)
    {
        return (i>=0)&&(i<WIDTH)&&(j>0)&&(j<=HEIGHT);

    }

bool DMainScreen::VertLimits(int i,int j)
    {
        return (i>=0)&&(i<=WIDTH)&&(j>0)&&(j<HEIGHT);
    }


void DMainScreen::resizeGL(int width, int height)
{
    /*glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //#ifdef QT_OPENGL_ES_1
    //glOrthof(-5, +5, -5, +5, 0.5, 45.0);
    //#else
        glOrtho(0.0,this->viewport_width,this->viewport_height,0.0,-1.0,1.0);
    //#endif
    glMatrixMode(GL_MODELVIEW);
*/

    Q_UNUSED(width);
    Q_UNUSED(height);

    this->viewport_height = 720;// height;
    this->viewport_width =1280;// width;

    if (fbo!=nullptr){
            delete fbo;

            glActiveTexture(GL_TEXTURE6);
            fbo = new QOpenGLFramebufferObject(QSize(viewport_width,viewport_height));
            //fbo = new QOpenGLFramebufferObject(QSize(this->width(),this->height()));
            glBindTexture(GL_TEXTURE_2D, fbo->texture());
        }


    if (mousemapfbo!=nullptr)
        {

            delete mousemapfbo;

            //  glActiveTexture(GL_TEXTURE6);
            glActiveTexture(GL_TEXTURE8);
            //mousemapfbo = new QOpenGLFramebufferObject(QSize(viewport_width,viewport_height));
            mousemapfbo = new QOpenGLFramebufferObject(QSize(this->width(),this->height()));
            glBindTexture(GL_TEXTURE_2D, mousemapfbo->texture());
            // JUST FOR TESTING
            //glActiveTexture(GL_TEXTURE6);
            // glBindTexture(GL_TEXTURE_2D, mousemapfbo->texture());

        }

}

void DMainScreen::drawhex_multi(float centerx, float centery, float width, int index, int index_red,  int index_yellow, int index_green, int index_cyan, int index_blue, int index_black)
{
    glColor3f(1.0,1.0,1.0);


    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx"), index%16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy"), index/16);

    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_red"), index_red%16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_red"), index_red/16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_green"), index_green%16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_green"), index_green/16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_yellow"), index_yellow%16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_yellow"), index_yellow/16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_cyan"), index_cyan%16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_cyan"), index_cyan/16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_blue"), index_blue%16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_blue"), index_blue/16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasx_black"), index_black%16);
    cliffshader->setUniformValue(cliffshader->uniformLocation("atlasy_black"), index_black/16);


    glBegin(GL_TRIANGLES);

    float margin = 0.000f;
    glTexCoord2f(0.0f+margin,0.5f);glVertex3f(centerx-width/2,centery,1);
    glTexCoord2f(0.25f,1.0f-margin);glVertex3f(centerx-width/4,centery-width/4,1);
    glTexCoord2f(0.25f,0.0f+margin);glVertex3f(centerx-width/4,centery+width/4,1);

    glTexCoord2f(0.25f,1.0f-margin);glVertex3f(centerx-width/4,centery-width/4,1);
    glTexCoord2f(0.75f,1.0f-margin);glVertex3f(centerx+width/4,centery-width/4,1);
    glTexCoord2f(0.75f,0.0f+margin);glVertex3f(centerx+width/4,centery+width/4,1);


    glTexCoord2f(0.25f,1.0f-margin);glVertex3f(centerx-width/4,centery-width/4,1);
    glTexCoord2f(0.75f,0.0f+margin);glVertex3f(centerx+width/4,centery+width/4,1);
    glTexCoord2f(0.25f,0.0f+margin);glVertex3f(centerx-width/4,centery+width/4,1);


    glTexCoord2f(0.75f,1.0f-margin);glVertex3f(centerx+width/4,centery-width/4,1);
    glTexCoord2f(1.0f-margin,0.5f);glVertex3f(centerx+width/2,centery,1);
    glTexCoord2f(0.75f,0.0f+margin);glVertex3f(centerx+width/4,centery+width/4,1);
    glEnd();
}

void DMainScreen::drawhex(float centerx, float centery, float width, int index, int index2)
{

    glColor3f(1.0,1.0,1.0);


    shader->setUniformValue(shader->uniformLocation("atlasx"), index%16);
    shader->setUniformValue(shader->uniformLocation("atlasy"), index/16);
    shader->setUniformValue(shader->uniformLocation("atlasx2"), index2%16);
    shader->setUniformValue(shader->uniformLocation("atlasy2"), index2/16);

    glBegin(GL_TRIANGLES);

    float margin = 0.000f;
    glTexCoord2f(0.0f+margin,0.5f);glVertex3f(centerx-width/2,centery,1);
    glTexCoord2f(0.25f,1.0f-margin);glVertex3f(centerx-width/4,centery-width/4,1);
    glTexCoord2f(0.25f,0.0f+margin);glVertex3f(centerx-width/4,centery+width/4,1);

    glTexCoord2f(0.25f,1.0f-margin);glVertex3f(centerx-width/4,centery-width/4,1);
    glTexCoord2f(0.75f,1.0f-margin);glVertex3f(centerx+width/4,centery-width/4,1);
    glTexCoord2f(0.75f,0.0f+margin);glVertex3f(centerx+width/4,centery+width/4,1);


    glTexCoord2f(0.25f,1.0f-margin);glVertex3f(centerx-width/4,centery-width/4,1);
    glTexCoord2f(0.75f,0.0f+margin);glVertex3f(centerx+width/4,centery+width/4,1);
    glTexCoord2f(0.25f,0.0f+margin);glVertex3f(centerx-width/4,centery+width/4,1);


    glTexCoord2f(0.75f,1.0f-margin);glVertex3f(centerx+width/4,centery-width/4,1);
    glTexCoord2f(1.0f-margin,0.5f);glVertex3f(centerx+width/2,centery,1);
    glTexCoord2f(0.75f,0.0f+margin);glVertex3f(centerx+width/4,centery+width/4,1);
    glEnd();
}

void DMainScreen::drawedgequadA(float centerx, float centery, float width, int variety, int config,  bool ismouth)
{

    glColor3f(1.0,1.0,1.0);


    rivershader->setUniformValue(rivershader->uniformLocation("atlasx"), config);

    if ((config==1)||(config==2)||(config==4))

        rivershader->setUniformValue(rivershader->uniformLocation("atlasy"), variety%4 + (ismouth?4:0));
    else
        rivershader->setUniformValue(rivershader->uniformLocation("atlasy"), variety);


    glBegin(GL_TRIANGLES);

    glTexCoord2f(0.0f,1.0f);      glVertex3f(centerx-width/2,centery,1);
    glTexCoord2f(1.0f,1.0f);      glVertex3f(centerx,centery,1);
    glTexCoord2f(1.0f,0.0f);      glVertex3f(centerx,centery+width/2,1);

    glTexCoord2f(0.0f,1.0f);      glVertex3f(centerx-width/2,centery,1);
    glTexCoord2f(1.0f,0.0f);      glVertex3f(centerx,centery+width/2,1);
    glTexCoord2f(0.0f,0.0f);      glVertex3f(centerx-width/2,centery+width/2,1);

    glEnd();
}


void DMainScreen::drawedgequadB(float centerx, float centery, float width, int variety, int config,  bool ismouth)
{

    glColor3f(1.0,1.0,1.0);


    rivershader->setUniformValue(rivershader->uniformLocation("atlasx"), config);

    if ((config==1)||(config==2)||(config==4))
        rivershader->setUniformValue(rivershader->uniformLocation("atlasy"), variety%4 + (ismouth?4:0));
    else
        rivershader->setUniformValue(rivershader->uniformLocation("atlasy"), variety);


    glBegin(GL_TRIANGLES);

    glTexCoord2f(1.0f,1.0f);      glVertex3f(centerx,centery,1);
    glTexCoord2f(0.0f,1.0f);      glVertex3f(centerx+width/2,centery,1);
    glTexCoord2f(0.0f,0.0f);      glVertex3f(centerx+width/2,centery+width/2,1);

    glTexCoord2f(1.0f,1.0f);      glVertex3f(centerx,centery,1);
    glTexCoord2f(0.0f,0.0f);      glVertex3f(centerx+width/2,centery+width/2,1);
    glTexCoord2f(1.0f,0.0f);      glVertex3f(centerx,centery+width/2,1);

    glEnd();
}

bool DMainScreen::terrain_precedence(int t1, int t2)
{
    return (t1>t2);
}

void DMainScreen::RENDER_BASIC_multiquad(int x_ul, int y_ul, int tx_ul, int ty_ul, int tx_dr, int ty_dr, texture_rotation rot )
{

    int ixstep,iystep;
    int jxstep,jystep;
    int xstart,ystart;
    int wid,hei;

    switch (rot)
        {
        case d0:
            {
                wid = (tx_dr-tx_ul)+1;
                hei = (ty_dr-ty_ul)+1;
                ixstep = 1;
                iystep = 0;
                jxstep = 0;
                jystep = 1;
                xstart = tx_ul;
                ystart = ty_ul;
                break;
            }

        case d90:
            {
                hei = (tx_dr-tx_ul)+1;
                wid = (ty_dr-ty_ul)+1;
                xstart = tx_ul;
                ystart = ty_dr;
                ixstep = 0;
                iystep = -1;
                jxstep = 1;
                jystep = 0;
                break;
            }

        case d180:
            {
                wid = (tx_dr-tx_ul)+1;
                hei = (ty_dr-ty_ul)+1;
                xstart = tx_dr;
                ystart = ty_dr;
                ixstep = -1;
                iystep = 0;
                jxstep = 0;
                jystep = -1;
                break;
            }

        case d270:
            {
                hei = (tx_dr-tx_ul)+1;
                wid = (ty_dr-ty_ul)+1;
                xstart = tx_dr;
                ystart = ty_ul;
                ixstep = 0;
                iystep = 1;
                jxstep = -1;
                jystep = 0;
                break;
            }

        case m0:
            {
                wid = (tx_dr-tx_ul)+1;
                hei = (ty_dr-ty_ul)+1;
                xstart = tx_dr;
                ystart = ty_ul;
                ixstep = -1;
                iystep = 0;
                jxstep = 0;
                jystep = 1;
                break;
            }
        case m90:
            {
                hei = (tx_dr-tx_ul)+1;
                wid = (ty_dr-ty_ul)+1;
                xstart = tx_dr;
                ystart = ty_dr;
                ixstep = 0;
                iystep = -1;
                jxstep = -1;
                jystep = 0;

                break;
            }
        case m180:
            {
                wid = (tx_dr-tx_ul)+1;
                hei = (ty_dr-ty_ul)+1;

                xstart = tx_ul;
                ystart = ty_dr;
                ixstep = 1;
                iystep = 0;
                jxstep = 0;
                jystep = -1;
                break;
            }
        case m270:
            {
                hei = (tx_dr-tx_ul)+1;
                wid = (ty_dr-ty_ul)+1;
                xstart = tx_ul;
                ystart = ty_ul;
                ixstep = 0;
                iystep = 1;
                jxstep = 1;
                jystep = 0;
                break;
            }

        }


    for (int ii01 = 0; ii01 < wid; ii01++)
        {
            for (int jj01 = 0; jj01 < hei; jj01++)
                {

                    shader->setUniformValue(shader->uniformLocation("atlasy"), ystart);
                    shader->setUniformValue(shader->uniformLocation("atlasx"), xstart);
                    //  shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_TERRAIN_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                    int i2 = ii01 + x_ul;
                    int j2 = jj01 + y_ul;
                    RENDER_BASIC_terrainquad(i2,j2,map[i2][j2],map[i2+1][j2],map[i2][j2+1],map[i2+1][j2+1],rot);

                    xstart = xstart + jxstep;
                    ystart = ystart + jystep;
                }

            xstart = xstart + ixstep - jxstep*hei;
            ystart = ystart + iystep - jystep*hei;
        }
}


void DMainScreen::RENDER_GRID()
{
    for (uint ii01 = 0; ii01 < HORIZONTAL_TO_DRAW; ii01++)
        for (uint jj01 = 0; jj01 < VERTICAL_TO_DRAW; jj01++)
            {
                shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                shader->setUniformValue(shader->uniformLocation("atlasx"), 9);
                RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
            }
}

void DMainScreen::RENDER_DRAW_TERRAIN(int mod)
{




    for (uint ii01 = 0; ii01 < HORIZONTAL_TO_DRAW; ii01++)
        for (uint jj01 = 0; jj01 < VERTICAL_TO_DRAW; jj01++)
            {
                switch (mod)
                    {
                    case TERRAIN_MOD_MOUSEMAP:
                        {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), cells[ii01][jj01].type/4);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), (cells[ii01][jj01].type%4)*8 + cells[ii01][jj01].variety);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_TERRAIN_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }
                    case TERRAIN_MOD_NONE:
                        {
                            // render base bits for all terrains but water
                            if (cells[ii01][jj01].type<TERRAIN_TYPES_WATER)
                                {
                                    shader->setUniformValue(shader->uniformLocation("atlasy"), cells[ii01][jj01].type/4);
                                    shader->setUniformValue(shader->uniformLocation("atlasx"), (cells[ii01][jj01].type%4)*8 + cells[ii01][jj01].variety);
                                    shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_TERRAIN_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);

                                    RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                                }
                            break;
                        }
                    case TERRAIN_MOD_CORNERS_DL:
                        {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_CORNERS_DL_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }
                    case TERRAIN_MOD_CORNERS_DR:
                        {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), 2);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_CORNERS_DR_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }
                    case TERRAIN_MOD_CORNERS_UL:
                        {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), 3);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_CORNERS_UL_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }
                    case TERRAIN_MOD_CORNERS_UR:                    {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), 4);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_CORNERS_UR_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }

                    case TERRAIN_MOD_SIDES_L:
                        {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), 5);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_SIDES_L_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }

                    case TERRAIN_MOD_SIDES_R:
                        {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), 6);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_SIDES_R_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }

                    case TERRAIN_MOD_SIDES_U:
                        {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), 7);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_SIDES_U_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }

                    case TERRAIN_MOD_SIDES_D:
                        {
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9);
                            shader->setUniformValue(shader->uniformLocation("atlasx"), 8);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_SIDES_D_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            break;
                        }



                    default: break;
                    }

            }



    if (mod == TERRAIN_MOD_NONE)
        {

            for (int ii01=0;ii01<=HORIZONTAL_TO_DRAW;ii01++)
                for (int jj01=0;jj01<=VERTICAL_TO_DRAW;jj01++)
                    {
                        shader->setUniformValue(shader->uniformLocation("atlasy2"), cells[ii01][jj01].type/4);
                        shader->setUniformValue(shader->uniformLocation("atlasx2"), (cells[ii01][jj01].type%4)*8 + cells[ii01][jj01].variety);

                        if (cells[ii01][jj01].type<TERRAIN_TYPES_WATER)
                            {

                                // render transitions
                                //up
                                if ((jj01 >0) &&   terrain_precedence(cells[ii01][jj01].type,cells[ii01][jj01-1].type))
                                    {
                                        shader->setUniformValue(shader->uniformLocation("atlasy"), 5);
                                        shader->setUniformValue(shader->uniformLocation("atlasx"), 16+ 0*cells[ii01][jj01-1].variety);
                                        RENDER_BASIC_terrainquad(ii01,jj01-1,map[ii01][jj01-1],map[ii01+1][jj01-1],map[ii01][jj01],map[ii01+1][jj01],d0);
                                    }

                                //down
                                if ((jj01 < (HEIGHT-1)) &&   terrain_precedence(cells[ii01][jj01].type,cells[ii01][jj01+1].type))
                                    {
                                        shader->setUniformValue(shader->uniformLocation("atlasy"), 5);
                                        shader->setUniformValue(shader->uniformLocation("atlasx"), 0 + 0*cells[ii01][jj01+1].variety);
                                        RENDER_BASIC_terrainquad(ii01,jj01+1,map[ii01][jj01+1],map[ii01+1][jj01+1],map[ii01][jj01+2],map[ii01+1][jj01+2],d0);
                                    }

                                //left
                                if ((ii01 >0) &&   terrain_precedence(cells[ii01][jj01].type,cells[ii01-1][jj01].type))
                                    {
                                        shader->setUniformValue(shader->uniformLocation("atlasy"), 5);
                                        shader->setUniformValue(shader->uniformLocation("atlasx"), 8 + 0*cells[ii01-1][jj01].variety);
                                        RENDER_BASIC_terrainquad(ii01-1,jj01,map[ii01-1][jj01],map[ii01][jj01],map[ii01-1][jj01+1],map[ii01][jj01+1],d0);
                                    }

                                //right
                                if ((ii01 < (WIDTH-1)) &&   terrain_precedence(cells[ii01][jj01].type,cells[ii01+1][jj01].type))
                                    {
                                        shader->setUniformValue(shader->uniformLocation("atlasy"), 5);
                                        shader->setUniformValue(shader->uniformLocation("atlasx"), 24 +0* cells[ii01+1][jj01].variety);
                                        RENDER_BASIC_terrainquad(ii01+1,jj01,map[ii01+1][jj01],map[ii01+2][jj01],map[ii01+1][jj01+1],map[ii01+2][jj01+1],d0);
                                    }
                            }

                        //render diagonal transitions where needed...
                        //convinient vars for types

                        if ((jj01 >0) && (ii01>0) && (jj01<HEIGHT) && (ii01<WIDTH))
                            {
                                int ul = cells[ii01-1][jj01-1].type; int u = cells[ii01][jj01-1].type; int ur = cells[ii01+1][jj01-1].type;
                                int l = cells[ii01-1][jj01].type; int t = cells[ii01][jj01].type; int r = cells[ii01+1][jj01].type;
                                int dl = cells[ii01-1][jj01+1].type; int d = cells[ii01][jj01+1].type; int dr = cells[ii01+1][jj01+1].type;

                                //if ( (ul==l) && (ul==u) && (ul!=ur) && (ul!=r) && (ul!=dr) && (ul!=d) && (ul!= dl) && terrain_precedence(ul,t) )
                                if ( (ul==l) && (ul==u) &&  (ul!=r) && (ul!=d) && (ul!=TERRAIN_TYPES_WATER) && terrain_precedence(ul,t) )
                                    {
                                        shader->setUniformValue(shader->uniformLocation("atlasy"), 6);
                                        shader->setUniformValue(shader->uniformLocation("atlasx"), 0 +0* cells[ii01][jj01].variety);

                                        shader->setUniformValue(shader->uniformLocation("atlasy2"), ul/4);
                                        shader->setUniformValue(shader->uniformLocation("atlasx2"), (ul%4)*8 + cells[ii01][jj01].variety);
                                        RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                                    }
                                else
                                    //if ( (ur==u)&&(ur==r)&&(ur!=l) && (ur!=ul) && (ur!=dr) && (ur!=d) && (ur!= dl) && terrain_precedence(ur,t))
                                    if ( (ur==u)&&(ur==r)&&(ur!=l) && (ur!=d)&&  (ur!=TERRAIN_TYPES_WATER)&& terrain_precedence(ur,t))
                                        {
                                            shader->setUniformValue(shader->uniformLocation("atlasy"), 6);
                                            shader->setUniformValue(shader->uniformLocation("atlasx"), 8 +0* cells[ii01][jj01].variety);

                                            shader->setUniformValue(shader->uniformLocation("atlasy2"), ur/4);
                                            shader->setUniformValue(shader->uniformLocation("atlasx2"), (ur%4)*8 + cells[ii01][jj01].variety);
                                            RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                                        }
                                    else
                                        //if ((dr==d)&&(dr==r)&&(dr!=dl) && (dr!=l) && (dr!=ul) && (dr!=u) && (dr!= ur) &&terrain_precedence(dr,t))
                                        if ((dr==d)&&(dr==r) && (dr!=l)  && (dr!=u) &&  (dr!=TERRAIN_TYPES_WATER) &&terrain_precedence(dr,t))
                                            {
                                                shader->setUniformValue(shader->uniformLocation("atlasy"), 6);
                                                shader->setUniformValue(shader->uniformLocation("atlasx"), 16 +0* cells[ii01][jj01].variety);

                                                shader->setUniformValue(shader->uniformLocation("atlasy2"), dr/4);
                                                shader->setUniformValue(shader->uniformLocation("atlasx2"), (dr%4)*8 + cells[ii01][jj01].variety);
                                                RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                                            }
                                        else //if ((dl==d)&&(dl==l)&&(dl!=ul) && (dl!=u) && (dl!=ur) && (dl!=r) && (dl!= dr) &&terrain_precedence(dl,t))
                                            if ((dl==d)&&(dl==l) && (dl!=u)  && (dl!=r)&&  (dl!=TERRAIN_TYPES_WATER) &&terrain_precedence(dl,t))
                                                {
                                                    shader->setUniformValue(shader->uniformLocation("atlasy"), 6);
                                                    shader->setUniformValue(shader->uniformLocation("atlasx"), 24 +0* cells[ii01][jj01].variety);

                                                    shader->setUniformValue(shader->uniformLocation("atlasy2"), dl/4);
                                                    shader->setUniformValue(shader->uniformLocation("atlasx2"), (dl%4)*8 + cells[ii01][jj01].variety);
                                                    RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                                                }




                            }



                    }
        }


    //dedicated water drawing
    if (mod == TERRAIN_MOD_NONE)
        {

            for (int ii01=0;ii01<=HORIZONTAL_TO_DRAW;ii01++)
                for (int jj01=0;jj01<=VERTICAL_TO_DRAW;jj01++)
                    {
                        if (cells[ii01][jj01].type ==TERRAIN_TYPES_WATER)
                            {
                                shader->setUniformValue(shader->uniformLocation("atlasy"), 4);
                                shader->setUniformValue(shader->uniformLocation("atlasx"), cells[ii01][jj01].seavariety);
                                //shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_TERRAIN_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                                shader->setUniformValue(shader->uniformLocation("frame"), cells[ii01][jj01].seaphase);
                                shader->setUniformValue(shader->uniformLocation("seavar2"), cells[ii01][jj01].nextvariety);
                                RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                            }
                    }

        }

    //sea shores
    if (mod == TERRAIN_MOD_NONE)
        {

            for (int ii01=0;ii01<=HORIZONTAL_TO_DRAW;ii01++)
                for (int jj01=0;jj01<=VERTICAL_TO_DRAW;jj01++)
                    {

                        int shores = 0;
                        int corners = 0;
                        if (cells[ii01][jj01].type !=TERRAIN_TYPES_WATER)
                            {
                                if (cells[ii01][jj01-1].type ==TERRAIN_TYPES_WATER) shores = shores + 1;
                                if (cells[ii01+1][jj01].type ==TERRAIN_TYPES_WATER) shores = shores + 2;
                                if (cells[ii01][jj01+1].type ==TERRAIN_TYPES_WATER) shores = shores + 4;
                                if (cells[ii01-1][jj01].type ==TERRAIN_TYPES_WATER) shores = shores + 8;

                                if (shores>0)
                                    {
                                        shader->setUniformValue(shader->uniformLocation("atlasy"), 7);
                                        shader->setUniformValue(shader->uniformLocation("atlasx"), shores);
                                        //shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_TERRAIN_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);

                                        shader->setUniformValue(shader->uniformLocation("atlasy2"), 4);
                                        shader->setUniformValue(shader->uniformLocation("atlasx2"), cells[ii01][jj01].seavariety);

                                        shader->setUniformValue(shader->uniformLocation("frame"), cells[ii01][jj01].seaphase);
                                        shader->setUniformValue(shader->uniformLocation("seavar2"), cells[ii01][jj01].nextvariety);
                                        RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                                    }
                                shader->setUniformValue(shader->uniformLocation("atlasy2"), 0);

                                //corners
                                if ((cells[ii01-1][jj01-1].type ==TERRAIN_TYPES_WATER)&&(cells[ii01][jj01-1].type !=TERRAIN_TYPES_WATER)&&((cells[ii01-1][jj01].type !=TERRAIN_TYPES_WATER)) ) corners = corners + 1;
                                if ((cells[ii01+1][jj01-1].type ==TERRAIN_TYPES_WATER)&&(cells[ii01][jj01-1].type !=TERRAIN_TYPES_WATER)&&((cells[ii01+1][jj01].type !=TERRAIN_TYPES_WATER)) ) corners = corners + 2;
                                if ((cells[ii01+1][jj01+1].type ==TERRAIN_TYPES_WATER)&&(cells[ii01][jj01+1].type !=TERRAIN_TYPES_WATER)&&((cells[ii01+1][jj01].type !=TERRAIN_TYPES_WATER)) ) corners = corners + 4;
                                if ((cells[ii01-1][jj01+1].type ==TERRAIN_TYPES_WATER)&&(cells[ii01][jj01+1].type !=TERRAIN_TYPES_WATER)&&((cells[ii01-1][jj01].type !=TERRAIN_TYPES_WATER)) ) corners = corners + 8;
                                if (corners>0)
                                    {
                                        shader->setUniformValue(shader->uniformLocation("atlasy"), 11);
                                        shader->setUniformValue(shader->uniformLocation("atlasx"), corners);
                                        //shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_TERRAIN_BASE + ii01*MOUSEMAP_TERRAIN_STEP + jj01*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);

                                        shader->setUniformValue(shader->uniformLocation("atlasy2"), 4);
                                        shader->setUniformValue(shader->uniformLocation("atlasx2"), cells[ii01][jj01].seavariety);

                                        shader->setUniformValue(shader->uniformLocation("frame"), cells[ii01][jj01].seaphase);
                                        shader->setUniformValue(shader->uniformLocation("seavar2"), cells[ii01][jj01].nextvariety);
                                        RENDER_BASIC_terrainquad(ii01,jj01,map[ii01][jj01],map[ii01+1][jj01],map[ii01][jj01+1],map[ii01+1][jj01+1],d0);
                                    }
                                shader->setUniformValue(shader->uniformLocation("atlasy2"), 0);

                            }
                    }

        }

}

QPoint DMainScreen::GetCornerNode(unsigned long id)
{
    QPoint CornerNode;
    switch (GetCornerTypeFromID(id))
        {
        case CORNER_UL:
            {
                CornerNode.setX(GetCornerXFromID(id));
                CornerNode.setY(GetCornerYFromID(id));
                break;
            }

        case CORNER_UR:
            {
                CornerNode.setX(GetCornerXFromID(id)+1);
                CornerNode.setY(GetCornerYFromID(id));
                break;
            }
        case CORNER_DL:
            {
                CornerNode.setX(GetCornerXFromID(id));
                CornerNode.setY(GetCornerYFromID(id)+1);
                break;
            }
        case CORNER_DR:
            {
                CornerNode.setX(GetCornerXFromID(id)+1);
                CornerNode.setY(GetCornerYFromID(id)+1);
                break;
            }
        default: break;
        }

    return CornerNode;
}

QPoint DMainScreen::GetHorSideNode(unsigned long id)
{
    QPoint SideNode;
    switch (GetSideTypeFromID(id))
        {
        case SIDE_U:
            {
                SideNode.setX(GetSideXFromID(id));
                SideNode.setY(GetSideYFromID(id));
                break;
            }
        case SIDE_D:
            {
                SideNode.setX(GetSideXFromID(id));
                SideNode.setY(GetSideYFromID(id)+1);
                break;
            }
        default:
            {
                SideNode.setX(-1);
                SideNode.setY(-1);
                break;
            }
        }
    return SideNode;

}

QPoint DMainScreen::GetVerSideNode(unsigned long id)
{
    QPoint SideNode;
    switch (GetSideTypeFromID(id))
        {
        case SIDE_L:
            {
                SideNode.setX(GetSideXFromID(id));
                SideNode.setY(GetSideYFromID(id));
                break;
            }
        case SIDE_R:
            {
                SideNode.setX(GetSideXFromID(id)+1);
                SideNode.setY(GetSideYFromID(id));
                break;
            }
        default:
            {
                SideNode.setX(-1);
                SideNode.setY(-1);
                break;
            }
        }
    return SideNode;
}

/*QPoint DMainScreen::GetSideNode(unsigned long id)
{
    QPoint CornerNode;
    switch (GetSideTypeFromID(id))
        {
        case SIDE_L:
            {
                CornerNode = DNetworkNode::medianL(GetSideXFromID(id),GetSideYFromID(id));
                break;
            }

        case SIDE_R:
            {
                CornerNode = DNetworkNode::medianR(GetSideXFromID(id),GetSideYFromID(id));

                break;
            }
        case SIDE_U:
            {
                CornerNode = DNetworkNode::medianU(GetSideXFromID(id),GetSideYFromID(id));

                break;
            }
        case SIDE_D:
            {
                CornerNode = DNetworkNode::medianD(GetSideXFromID(id),GetSideYFromID(id));
                // CornerNode = QPoint(QNetworkNode::medianU(2,2));
                break;
            }
        default: break;
        }

    return CornerNode;
}*/


int DMainScreen::GetSideTypeFromID(unsigned long id)
{
    if (id<MOUSEMAP_SIDES_L_BASE)
        return -1;
    else
        if (id<MOUSEMAP_SIDES_R_BASE)
            return SIDE_L;
        else
            if (id<MOUSEMAP_SIDES_U_BASE)
                return SIDE_R;
            else
                if (id<MOUSEMAP_SIDES_D_BASE)
                    return SIDE_U;
                else
                    if (id<MOUSEMAP_SIDES_D_END)
                        return SIDE_D;
                    else
                        return -1;
}

int DMainScreen::GetSideXFromID(unsigned long id)
{
    int type = GetSideTypeFromID(id);
    if (type==-1)
        return -1;
    else
        {
            unsigned long int start, end;

            switch(type)
                {
                case SIDE_L:
                    start = MOUSEMAP_SIDES_L_BASE;
                    end = MOUSEMAP_SIDES_L_END;

                    break;
                case SIDE_R:
                    start = MOUSEMAP_SIDES_R_BASE;
                    end = MOUSEMAP_SIDES_R_END;
                    break;
                case SIDE_U:
                    start = MOUSEMAP_SIDES_U_BASE;
                    end = MOUSEMAP_SIDES_U_END;
                    break;
                case SIDE_D:
                    start = MOUSEMAP_SIDES_D_BASE;
                    end = MOUSEMAP_SIDES_D_END;
                    break;
                default:
                    start = -1;// irreleveant
                    end = -1;
                    break;
                }

            if ((id>=start) && (id < end))
                {

                    return ((id-(start))%(MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH))/MOUSEMAP_TERRAIN_STEP;
                }
            else
                {
                    return -1;
                }
        }
}

int DMainScreen::GetSideYFromID(unsigned long id)
{
    int type = GetSideTypeFromID(id);
    if (type==-1)
        return -1;
    else
        {
            unsigned long int start, end;

            switch(type)
                {
                case SIDE_L:
                    start = MOUSEMAP_SIDES_L_BASE;
                    end = MOUSEMAP_SIDES_L_END;
                    break;
                case SIDE_R:
                    start = MOUSEMAP_SIDES_R_BASE;
                    end = MOUSEMAP_SIDES_R_END;
                    break;
                case SIDE_U:
                    start = MOUSEMAP_SIDES_U_BASE;
                    end = MOUSEMAP_SIDES_U_END;
                    break;
                case SIDE_D:
                    start = MOUSEMAP_SIDES_D_BASE;
                    end = MOUSEMAP_SIDES_D_END;
                    break;
                default:
                    start = -1;// irreleveant
                    end = -1;
                    break;
                }

            if ((id>=start) && (id < end))
                {
                    return ((id-(start))/(MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH))/MOUSEMAP_TERRAIN_STEP;
                }
            else
                {
                    return -1;
                }
        }
}

void DMainScreen::RENDER_DRAW_UI(int mod)
{

    switch(CurrentTool)
        {

        case TOOL_CHANGE_TERRAIN:
            {
                shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                //draw yellow cursor
                //  if ((cursor_x>-1)&&(cursor_y>-1))
                if (LastHoverGroup == HOVER_GROUP_TERRAIN)
                    {
                        shader->setUniformValue(shader->uniformLocation("atlasx"),5 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"),10 );
                        RENDER_BASIC_terrainquad(cursor_x,cursor_y,map[cursor_x][cursor_y],map[cursor_x+1][cursor_y],map[cursor_x][cursor_y+1],map[cursor_x+1][cursor_y+1],d0);
                    }
                break;


            }

        case TOOL_LANDSCAPE_DOWN:
            {

                if (LastHoverGroup == HOVER_GROUP_TERRAIN)
                    {
                        //draw simple cursor
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        shader->setUniformValue(shader->uniformLocation("atlasx"),0 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"),10 );
                        RENDER_BASIC_terrainquad(cursor_x,cursor_y,map[cursor_x][cursor_y],map[cursor_x+1][cursor_y],map[cursor_x][cursor_y+1],map[cursor_x+1][cursor_y+1],d0);
                    }

                if (LastHoverGroup == HOVER_GROUP_CORNER)
                    {
                        shader->setUniformValue(shader->uniformLocation("atlasx"),1+GetCornerTypeFromID(LastHoverID) );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);

                        int cx = GetCornerXFromID(LastHoverID);
                        int cy = GetCornerYFromID(LastHoverID);

                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);
                    }



                break;
            }

        case TOOL_LANDSCAPE_UP:
            {
                if (LastHoverGroup == HOVER_GROUP_TERRAIN)
                    {
                        //draw simple cursor
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        shader->setUniformValue(shader->uniformLocation("atlasx"),0 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"),10 );
                        RENDER_BASIC_terrainquad(cursor_x,cursor_y,map[cursor_x][cursor_y],map[cursor_x+1][cursor_y],map[cursor_x][cursor_y+1],map[cursor_x+1][cursor_y+1],d0);
                    }

                if (LastHoverGroup == HOVER_GROUP_CORNER)
                    {
                        shader->setUniformValue(shader->uniformLocation("atlasx"),1+GetCornerTypeFromID(LastHoverID) );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);

                        int cx = GetCornerXFromID(LastHoverID);
                        int cy = GetCornerYFromID(LastHoverID);

                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);
                    }



                break;
            }
        case TOOL_TOGGLE_WATER:
            {
                if (LastHoverGroup == HOVER_GROUP_TERRAIN)
                    {
                        //draw simple cursor
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        shader->setUniformValue(shader->uniformLocation("atlasx"),6 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"),10 );
                        RENDER_BASIC_terrainquad(cursor_x,cursor_y,map[cursor_x][cursor_y],map[cursor_x+1][cursor_y],map[cursor_x][cursor_y+1],map[cursor_x+1][cursor_y+1],d0);
                    }
                break;

            }

        case TOOL_RAILROAD_PLACE_START:
            {

                //RENDER_GRID();

                if (LastHoverGroup == HOVER_GROUP_CORNER)
                    {


                        //first of all let's decode HoverId of the corner and bring it to the NetworkNode format

                        QPoint CornerNode = GetCornerNode(LastHoverID);

                        //now we shall paint four quads adjancent to this corner 2143


                        // ul
                        shader->setUniformValue(shader->uniformLocation("atlasx"),2 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 10 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        int cx = CornerNode.x()-1;
                        int cy = CornerNode.y()-1;
                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                        //ur
                        shader->setUniformValue(shader->uniformLocation("atlasx"),1 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 10 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        cx = CornerNode.x();
                        cy = CornerNode.y()-1;
                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                        //dl
                        shader->setUniformValue(shader->uniformLocation("atlasx"),4 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 10 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        cx = CornerNode.x()-1;
                        cy = CornerNode.y();
                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                        //dr
                        shader->setUniformValue(shader->uniformLocation("atlasx"),3 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 10 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        cx = CornerNode.x();
                        cy = CornerNode.y();
                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                    }

                if (LastHoverGroup == HOVER_GROUP_HOR_SIDE)
                    {

                        QPoint SideNode = GetHorSideNode(LastHoverID);

                        shader->setUniformValue(shader->uniformLocation("atlasx"),9 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 10 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        int cx = SideNode.x();
                        int cy = SideNode.y();
                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                        shader->setUniformValue(shader->uniformLocation("atlasx"),10 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 10 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        cx = SideNode.x();
                        cy = SideNode.y()-1;
                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);


                    }
                if (LastHoverGroup == HOVER_GROUP_VER_SIDE)
                    {

                        QPoint SideNode = GetVerSideNode(LastHoverID);

                        shader->setUniformValue(shader->uniformLocation("atlasx"),7 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 10 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        int cx = SideNode.x()-1;
                        int cy = SideNode.y();
                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                        shader->setUniformValue(shader->uniformLocation("atlasx"),8 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"), 10 );
                        shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                        cx = SideNode.x();
                        cy = SideNode.y();
                        RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);
                    }

                break;
            }

        case TOOL_RAILROAD_PLACE_END:
            {

                // RENDER_GRID();
                RENDER_DRAW_MAGNETS(false);


                RENDER_PILOT_NETWORK();//&construction_network);

                break;
            }

         case TOOL_BULLDOSE:
            {
                shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                //draw bulldose cursor
                if (LastHoverGroup == HOVER_GROUP_TERRAIN)
                    {
                        shader->setUniformValue(shader->uniformLocation("atlasx"),11 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"),10 );
                        RENDER_BASIC_terrainquad(cursor_x,cursor_y,map[cursor_x][cursor_y],map[cursor_x+1][cursor_y],map[cursor_x][cursor_y+1],map[cursor_x+1][cursor_y+1],d0);
                    }
                break;
            }


        default: // also for TOOL_POINT
            {
                shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                //draw plain cursor
                if (LastHoverGroup == HOVER_GROUP_TERRAIN)
                    {
                        shader->setUniformValue(shader->uniformLocation("atlasx"),0 );
                        shader->setUniformValue(shader->uniformLocation("atlasy"),10 );
                        RENDER_BASIC_terrainquad(cursor_x,cursor_y,map[cursor_x][cursor_y],map[cursor_x+1][cursor_y],map[cursor_x][cursor_y+1],map[cursor_x+1][cursor_y+1],d0);
                    }
                break;
            }



        }






}



void DMainScreen::RENDER_DRAW_MAGNETS(bool ifmm)
{

    //  qDebug()<<"MAGNETS SIZE "<<magnets.size();

    int mmshift = (!ifmm)?9:0;

    if (!magnets.isEmpty())
        for (QList<DMagnet*>::iterator it =magnets.begin();it!=magnets.end();it++)
            {


                switch ((*it)->address.type)
                    {
                    case NetworkNodeTypes::corner:
                        {

                            int cx = (*it)->address.i-1;
                            int cy = (*it)->address.j-1;
                            shader->setUniformValue(shader->uniformLocation("atlasx"),2+mmshift);
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_CORNERS_DR_BASE + cx*MOUSEMAP_TERRAIN_STEP + cy*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            if ((cx>=0)&&((cx+1)<=WIDTH)&&(cy>=0)&&((cy+1)<=HEIGHT))
                                RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                            cx = (*it)->address.i;
                            cy = (*it)->address.j-1;
                            shader->setUniformValue(shader->uniformLocation("atlasx"),1+mmshift );
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_CORNERS_DL_BASE + cx*MOUSEMAP_TERRAIN_STEP + cy*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            if ((cx>=0)&&((cx+1)<=WIDTH)&&(cy>=0)&&((cy+1)<=HEIGHT))
                                RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                            cx = (*it)->address.i;
                            cy = (*it)->address.j;
                            shader->setUniformValue(shader->uniformLocation("atlasx"),3+mmshift );
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_CORNERS_UL_BASE + cx*MOUSEMAP_TERRAIN_STEP + cy*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            if ((cx>=0)&&((cx+1)<=WIDTH)&&(cy>=0)&&((cy+1)<=HEIGHT))
                                RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                            cx = (*it)->address.i-1;
                            cy = (*it)->address.j;
                            shader->setUniformValue(shader->uniformLocation("atlasx"),4+mmshift );
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_CORNERS_UR_BASE + cx*MOUSEMAP_TERRAIN_STEP + cy*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);
                            if ((cx>=0)&&((cx+1)<=WIDTH)&&(cy>=0)&&((cy+1)<=HEIGHT))
                                RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);
                            break;
                        }

                    case NetworkNodeTypes::horiz:
                        {
                            int cx = (*it)->address.i;
                            int cy = (*it)->address.j;
                            shader->setUniformValue(shader->uniformLocation("atlasx"),7+mmshift );
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_SIDES_U_BASE + cx*MOUSEMAP_TERRAIN_STEP + cy*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);

                            if ((cx>=0)&&((cx+1)<=WIDTH)&&(cy>=0)&&((cy+1)<=HEIGHT))
                                RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                            cx = (*it)->address.i;
                            cy = (*it)->address.j-1;
                            shader->setUniformValue(shader->uniformLocation("atlasx"),8+mmshift );
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_SIDES_D_BASE + cx*MOUSEMAP_TERRAIN_STEP + cy*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);

                            if ((cx>=0)&&((cx+1)<=WIDTH)&&(cy>=0)&&((cy+1)<=HEIGHT))
                                RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);
                            break;
                        }

                    case NetworkNodeTypes::vert:
                        {
                            int cx = (*it)->address.i;
                            int cy = (*it)->address.j;
                            shader->setUniformValue(shader->uniformLocation("atlasx"),5+mmshift );
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_SIDES_L_BASE + cx*MOUSEMAP_TERRAIN_STEP + cy*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);

                            if ((cx>=0)&&((cx+1)<=WIDTH)&&(cy>=0)&&((cy+1)<=HEIGHT))
                                RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);

                            cx = (*it)->address.i-1;
                            cy = (*it)->address.j;
                            shader->setUniformValue(shader->uniformLocation("atlasx"),6+mmshift );
                            shader->setUniformValue(shader->uniformLocation("atlasy"), 9 );
                            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
                            shader->setUniformValue(shader->uniformLocation("mousemapid"), MOUSEMAP_SIDES_R_BASE + cx*MOUSEMAP_TERRAIN_STEP + cy*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_TERRAIN_STEP);

                            if ((cx>=0)&&((cx+1)<=WIDTH)&&(cy>=0)&&((cy+1)<=HEIGHT))
                                RENDER_BASIC_terrainquad(cx,cy,map[cx][cy],map[cx+1][cy],map[cx][cy+1],map[cx+1][cy+1],d0);
                            break;
                        }
                    }

            }






}



int DMainScreen::GetCornerTypeFromID(unsigned long int id)
{
    if (id<MOUSEMAP_CORNERS_DL_BASE)
        return -1;
    else
        if (id<MOUSEMAP_CORNERS_DR_BASE)
            return CORNER_DL;
        else
            if (id<MOUSEMAP_CORNERS_UL_BASE)
                return CORNER_DR;
            else
                if (id<MOUSEMAP_CORNERS_UR_BASE)
                    return CORNER_UL;
                else
                    if (id<MOUSEMAP_CORNERS_END)
                        return CORNER_UR;
                    else
                        return -1;
}

int DMainScreen::GetCornerXFromID(unsigned long int id)
{
    int type = GetCornerTypeFromID(id);
    if (type==-1)
        return -1;
    else
        {
            unsigned long int start, end;

            switch(type)
                {
                case CORNER_DL:
                    start = MOUSEMAP_CORNERS_DL_BASE;
                    end = MOUSEMAP_CORNERS_DL_END;
                    break;
                case CORNER_DR:
                    start = MOUSEMAP_CORNERS_DR_BASE;
                    end = MOUSEMAP_CORNERS_DR_END;
                    break;
                case CORNER_UL:
                    start = MOUSEMAP_CORNERS_UL_BASE;
                    end = MOUSEMAP_CORNERS_UL_END;
                    break;
                case CORNER_UR:
                    start = MOUSEMAP_CORNERS_UR_BASE;
                    end = MOUSEMAP_CORNERS_UR_END;
                    break;
                default:
                    start = -1;// irreleveant
                    end = -1;
                    break;
                }

            if ((id>=start) && (id < end))
                {
                    return ((id-(start))%(MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH))/MOUSEMAP_TERRAIN_STEP;
                }
            else
                {
                    return -1;
                }
        }
}


int DMainScreen::GetCornerYFromID(unsigned long int id)
{
    int type = GetCornerTypeFromID(id);
    if (type==-1)
        return -1;
    else
        {
            unsigned long int start, end;

            switch(type)
                {
                case CORNER_DL:
                    start = MOUSEMAP_CORNERS_DL_BASE;
                    end = MOUSEMAP_CORNERS_DL_END;
                    break;
                case CORNER_DR:
                    start = MOUSEMAP_CORNERS_DR_BASE;
                    end = MOUSEMAP_CORNERS_DR_END;
                    break;
                case CORNER_UL:
                    start = MOUSEMAP_CORNERS_UL_BASE;
                    end = MOUSEMAP_CORNERS_UL_END;
                    break;
                case CORNER_UR:
                    start = MOUSEMAP_CORNERS_UR_BASE;
                    end = MOUSEMAP_CORNERS_UR_END;
                    break;
                default:
                    start = -1;// irreleveant
                    end = -1;
                    break;
                }

            if ((id>=start) && (id < end))
                {
                    return ((id-(start))/(MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH))/MOUSEMAP_TERRAIN_STEP;
                }
            else
                {
                    return -1;
                }
        }
}





void DMainScreen::paintGL()
{


    draw();

    //int index = 6784;


    shader->bind();


    int  leftcell = ( 0 + 4*(-sx)/w/3 + WIDTH)%WIDTH;
    int rightcell = (26*128/w + 4*(-sx)/w/3 + WIDTH)%WIDTH;

    int topcell= ((0 + 2*(-sy)/w)+HEIGHT)%HEIGHT;
    int bottomcell=((20*128/w + 2*(-sy)/w) + HEIGHT)%HEIGHT;


    // ======================================  MOUSE MAP DRAWING INTO MOUSE MAP FRAME BUFFER OBJECT =====================
    mousemapfbo->bind();
    glViewport(0,0, width(), height());
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable (GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,this->viewport_width,this->viewport_height,0.0,-1.0,1.0);
    //glOrtho(0.0,width(),height(),0,-1.0,1.0);

    shader->bind();
    shader->setUniformValue(shader->uniformLocation("mousemap"), 1 );
    RENDER_DRAW_TERRAIN(TERRAIN_MOD_MOUSEMAP);


    switch (CurrentTool)
        {
        case TOOL_LANDSCAPE_DOWN:
        case TOOL_LANDSCAPE_UP:
            {
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_DL);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_DR);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_UL);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_UR);
                break;
            }
        case TOOL_RAILROAD_PLACE_START:
            {

                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_DL);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_DR);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_UL);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_UR);


                RENDER_DRAW_TERRAIN(TERRAIN_MOD_SIDES_L);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_SIDES_R);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_SIDES_U);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_SIDES_D);

                break;
            }

        case TOOL_RAILROAD_PLACE_END:
            {
                RENDER_DRAW_MAGNETS(true);
                break;
            }

        default: break;
        }


    shader->release();






    mousemapfbo->release();
    mousemap = QImage(mousemapfbo->toImage());

    //  glViewport(0,0, width(), height());

    // ======================================  MAIN DRAWING INTO FRAME BUFFER OBJECT =====================

    fbo->bind();
    glViewport(0,0, viewport_width, viewport_height);
    //glClearColor(qtBG.redF(),qtBG.greenF(),qtBG.blueF(),1.0);
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable (GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(0.0f,width(), height(),0.0f,-1.0f,1.0f);
    glOrtho(0.0,this->viewport_width,this->viewport_height,0.0,-1.0,1.0);
    shader->bind();
    shader->setUniformValue(shader->uniformLocation("mousemap"), 0);
    shader->setUniformValue(shader->uniformLocation("noshade"), 0);
    RENDER_DRAW_TERRAIN(TERRAIN_MOD_NONE);

    /*
        //debug mousemap onscreen

        switch (CurrentTool)
        {
        case TOOL_LANDSCAPE_DOWN:
        case TOOL_LANDSCAPE_UP:
            {
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_DL);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_DR);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_UL);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_UR);
                break;
            }
        case TOOL_RAILROAD_PLACE_START:
            {

                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_DL);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_DR);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_UL);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_CORNERS_UR);


                RENDER_DRAW_TERRAIN(TERRAIN_MOD_SIDES_L);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_SIDES_R);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_SIDES_U);
                RENDER_DRAW_TERRAIN(TERRAIN_MOD_SIDES_D);

                break;
            }

        default: break;
        }
    */

    // RENDER_BASIC_multiquad(2,2,2,12,4,13,m270);
    RENDER_NETWORK();//&network);

    // RENDER_BASIC_multiquad(10,10,5,12,13,15);

    RENDER_DRAW_UI(UI_MOD_NONE);



    // RENDER_DRAW_3D_CAR(2,2,static_cast<GLfloat>(test_deg));

    shader->release();

    fbo->release();
    // ----------- END MAIN RENDER INTO FBO ----------------------------


    //fbo->toImage().save(QString("C:/proj%1.bmp").arg(test_deg));

    // -----------------================= RENDERING SCREEN ================---------------------
    glViewport(0,0, width(),height());
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable (GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,width(),height(),0.0,-1.0,1.0);

    simpleshader->bind();
    simpleshader->setUniformValue(simpleshader->uniformLocation("texture"),6);

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0,1.0); glVertex3f(0,0,1);
    glTexCoord2f(1.0,1.0); glVertex3f(width(),0,1);
    glTexCoord2f(1.0,0.0); glVertex3f(width(),height(),1);

    glTexCoord2f(0.0,1.0); glVertex3f(0,0,1);
    glTexCoord2f(1.0,0.0); glVertex3f(width(),height(),1);
    glTexCoord2f(0.0,0.0); glVertex3f(0,height(),1);
    glEnd();
    simpleshader->release();


    // special
    flatshader->bind();
    int mapsize = 1;


    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            {
                float aaa = (1)*0.125f;

                if (aaa==0.0f)
                    flatshader->setUniformValue(flatshader->uniformLocation("col"),0.2f,0.2f,0.8f);
                else
                    flatshader->setUniformValue(flatshader->uniformLocation("col"),1.0f,1.0f,1.0f);


                glBegin(GL_QUADS);
                glVertex3f( 10+mapsize*i,10+mapsize*j+mapsize*(i%2),1);
                glVertex3f( 10+mapsize*i+mapsize,10+mapsize*j+mapsize*(i%2),1);
                glVertex3f( 10+mapsize*i+mapsize,10+mapsize*j+mapsize*(i%2)+mapsize,1);
                glVertex3f( 10+mapsize*i,10+mapsize*j+mapsize*(i%2)+mapsize,1);
                glEnd();

            }


    flatshader->setUniformValue(flatshader->uniformLocation("col"),0.5f,0.5f,0.2f);
    glBegin(GL_LINES);

    glVertex3f( 10+mapsize*leftcell,10+mapsize*topcell+mapsize*(leftcell%2),1);     glVertex3f( 10+mapsize*rightcell,10+mapsize*topcell+mapsize*(rightcell%2),1);

    glVertex3f( 10+mapsize*rightcell,10+mapsize*topcell+mapsize*(rightcell%2),1);glVertex3f( 10+mapsize*rightcell,10+mapsize*bottomcell+mapsize*(rightcell%2),1);
    glVertex3f( 10+mapsize*rightcell,10+mapsize*bottomcell+mapsize*(rightcell%2),1);glVertex3f( 10+mapsize*leftcell,10+mapsize*bottomcell+mapsize*(rightcell%2),1);
    glVertex3f( 10+mapsize*leftcell,10+mapsize*bottomcell+mapsize*(rightcell%2),1);glVertex3f( 10+mapsize*leftcell,10+mapsize*topcell+mapsize*(leftcell%2),1);
    glEnd();
    flatshader->release();

}


void DMainScreen::PREPARE_MAGNETS_START()
{

}


void DMainScreen::RENDER_PILOT_NETWORK()
{


    if (HoverMagnet!=nullptr)
        {




            QColor color;
            color.setRedF(1.0);//r;
            color.setGreenF((HoverMagnet->valid)?1.0:0);//g;
            color.setBlueF((HoverMagnet->valid)?1.0:0);//b;

            shader->setUniformValue(shader->uniformLocation("noshade"), 1);
            shader->setUniformValue(shader->uniformLocation("tint"), color);
            shader->setUniformValue(shader->uniformLocation("allwhite"), 1);

            DMagnet* mag = HoverMagnet;

            do
                {
                RENDER_BASIC_multiquad(mag->newelement->i, mag->newelement->j, mag->newelement->ax, mag->newelement->ay, mag->newelement->bx, mag->newelement->by, mag->newelement->rot );




                mag = mag->prev;
                }
                while(mag!=nullptr);

            shader->setUniformValue(shader->uniformLocation("allwhite"), 0);
            shader->setUniformValue(shader->uniformLocation("noshade"), 0);
        }



}

bool DMainScreen::check_obstruction(DNetworkListElement * element)
{

    bool result = true;

    for ( QList<ObstructionElement>::iterator iter=element->imprint.begin(); iter!=element->imprint.end();iter++)
        {
            if  (

                 ((iter->tile.u==1)&&(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].u!=nullptr)) ||
                 ((iter->tile.d==1)&&(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].d!=nullptr)) ||
                 ((iter->tile.l==1)&&(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].l!=nullptr)) ||
                 ((iter->tile.r==1)&&(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].r!=nullptr)) )
                {
                    result =false;
                    break;
                }
        }

    return result;

}

bool DMainScreen::check_obstruction_conditional(DNetworkListElement * element,QList<DNetworkListElement*> allowed)
{

    bool result = true;

    for ( QList<ObstructionElement>::iterator iter=element->imprint.begin(); iter!=element->imprint.end();iter++)
        {
            if  ((iter->tile.u==1)&&(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].u!=nullptr))
                {
                    if (! allowed.contains(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].u))
                        {
                        result = false;
                        break;
                        }
                }

            if  ((iter->tile.d==1)&&(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].d!=nullptr))
                {
                    if (! allowed.contains(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].d))
                        {
                        result = false;
                        break;
                        }
                }

            if  ((iter->tile.l==1)&&(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].l!=nullptr))
                {
                    if (! allowed.contains(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].l))
                        {
                        result = false;
                        break;
                        }
                }

            if  ((iter->tile.r==1)&&(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].r!=nullptr))
                {
                    if (! allowed.contains(obstructions[element->i+iter->adress.x()][element->j+iter->adress.y()].r))
                        {
                        result = false;
                        break;
                        }
                }
        }

    return result;

}



void DMainScreen::DESTROY_MAGNETS()
{
for (QList<DMagnet*>::iterator it= magnets.begin();it!=magnets.end();it++)
    {
        if ((*it)!=nullptr)
            delete (*it);
    }
magnets.clear();
}

void DMainScreen::PREPARE_MAGNETS_END()
{
    // LET'S DEFINE APPROPRIATE FINAL POINTS FOR THIS FRAGMENT ("MAGNETS")

    DESTROY_MAGNETS();

    switch (RailStart.type)
        {
        case NetworkNodeTypes::corner:

            {
                PREPARE_MAGNETS_CORNERS();
                break;
            }

        case NetworkNodeTypes::vert:

            {
               PREPARE_MAGNETS_VERTICAL_SIDES();
                break;




            }
        case NetworkNodeTypes::horiz:
            {

              PREPARE_MAGNETS_HORIZONTAL_SIDES();
                break;
            }
        }
}


void DMainScreen::mouseMoveEvent(QMouseEvent *event)
{
    if (READY) {

            if (moving)    {
                    sx += (event->x()-movingx);
                    sy += (event->y()-movingy);
                    update();

                    movingy = event->y();
                    movingx = event->x();
                }

            else if(zooming) {//nothing yet
                }
            else
                {
                    mx = event->x();
                    my = event->y();

                    //check mousemap

                    //LastHoverID
                    //CurrentHoverID = mousemap.pixel(mx,my); //GetIDfromRGB(mousemap.pixel(mx,my));

                    CurrentHoverID = mousemap.pixelColor(mx,my).red()+mousemap.pixelColor(mx,my).green()*256+mousemap.pixelColor(mx,my).blue()*256*256;

                    if (CurrentHoverID!=LastHoverID)
                        {
                            //event
                            LastHoverID = CurrentHoverID;

                            LastHoverGroup = HOVER_GROUP_OTHER;

                            if (LastHoverID<MOUSEMAP_TERRAIN_END)
                                {
                                    LastHoverGroup = HOVER_GROUP_TERRAIN;
                                    cursor_x = GetXfromRGB(LastHoverID);
                                    cursor_y = GetYfromRGB(LastHoverID);
                                }
                            else
                                if (LastHoverID<MOUSEMAP_CORNERS_END)
                                    {
                                        LastHoverGroup = HOVER_GROUP_CORNER;
                                    }
                                else
                                    if (LastHoverID<MOUSEMAP_VER_SIDES_END)
                                        {
                                            LastHoverGroup = HOVER_GROUP_VER_SIDE;
                                        }
                                    else
                                        {
                                            LastHoverGroup=HOVER_GROUP_HOR_SIDE;
                                        }


                            switch (CurrentTool)
                                {
                                case TOOL_RAILROAD_PLACE_END:
                                    {

                                        if (LastHoverGroup==HOVER_GROUP_CORNER)
                                            {

                                                for(QList<DMagnet*>::iterator it=magnets.begin();it!=magnets.end();it++)
                                                    {
                                                        if ( ((*it)->address.type==NetworkNodeTypes::corner) && ((*it)->address.i == GetCornerNode(LastHoverID).x()) && ((*it)->address.j == GetCornerNode(LastHoverID).y() ))
                                                            {
                                                                HoverMagnet = *it;
                                                                break;//for
                                                            }
                                                    }
                                            }

                                        if (LastHoverGroup==HOVER_GROUP_HOR_SIDE)
                                            {

                                                for(QList<DMagnet*>::iterator it=magnets.begin();it!=magnets.end();it++)
                                                    {

                                                        if ( ((*it)->address.type==NetworkNodeTypes::horiz) && ((*it)->address.i == GetHorSideNode(LastHoverID).x()) && ((*it)->address.j == GetHorSideNode(LastHoverID).y() ))
                                                            {
                                                                HoverMagnet = *it;

                                                                break;//for
                                                            }
                                                    }
                                            }

                                        if (LastHoverGroup==HOVER_GROUP_VER_SIDE)
                                            {


                                                for(QList<DMagnet*>::iterator it=magnets.begin();it!=magnets.end();it++)
                                                    {

                                                        if ( ((*it)->address.type==NetworkNodeTypes::vert) && ((*it)->address.i == GetVerSideNode(LastHoverID).x()) && ((*it)->address.j == GetVerSideNode(LastHoverID).y() ))
                                                            {
                                                                HoverMagnet = *it;

                                                                break;//for
                                                            }
                                                    }
                                            }

                                    }
                                default: break;
                                }



                            //  qDebug() << LastHoverID;
                            //  qDebug() << cursor_x << " " << cursor_y;
                            // qDebug() << mx << " " << my;

                            // mousemap.save("D:/mm.bmp");

                        }

                    update();
                }

        }
}

int DMainScreen::GetXfromRGB(long unsigned int rgb)
{
    if ((rgb>=MOUSEMAP_TERRAIN_BASE) && (rgb < MOUSEMAP_TERRAIN_END))
        {
            return ((rgb-(MOUSEMAP_TERRAIN_BASE))%(MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH))/MOUSEMAP_TERRAIN_STEP;
        }
    else
        {
            return -1;
        }
}

int DMainScreen::GetYfromRGB(long unsigned  int rgb)
{
    if ((rgb>=MOUSEMAP_TERRAIN_BASE) && (rgb < MOUSEMAP_TERRAIN_END))
        {
            return ((rgb-(MOUSEMAP_TERRAIN_BASE))/(MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH))/MOUSEMAP_TERRAIN_STEP;
        }
    else
        {
            return -1;
        }
}

void DMainScreen::mouseReleaseEvent(QMouseEvent *event)
{
    if (READY) {

            switch (event->button()){
                case Qt::RightButton: moving = false;

                    break;
                case Qt::LeftButton: zooming = false;

                    switch (CurrentTool)
                        {
                        case TOOL_RAILROAD_PLACE_END:

                            {
                                CurrentTool = TOOL_RAILROAD_PLACE_START;

                                if (HoverMagnet!=nullptr)
                                    {

                                        if (HoverMagnet->valid)
                                            {

                                                DMagnet * mag = HoverMagnet;

                                                do {
                                                        NetworkList->append(mag->newelement);

                                                        NetworkList->last->killUpgraded();
                                                        NetworkList->last->LinkNodes();

                                                        for ( QList<ObstructionElement>::iterator iter=NetworkList->last->imprint.begin(); iter!=NetworkList->last->imprint.end();iter++)
                                                            {
                                                                if (iter->tile.u==1)
                                                                    obstructions[NetworkList->last->i+iter->adress.x()][NetworkList->last->j+iter->adress.y()].u=NetworkList->last;
                                                                if (iter->tile.d==1)
                                                                    obstructions[NetworkList->last->i+iter->adress.x()][NetworkList->last->j+iter->adress.y()].d=NetworkList->last;
                                                                if (iter->tile.l==1)
                                                                    obstructions[NetworkList->last->i+iter->adress.x()][NetworkList->last->j+iter->adress.y()].l=NetworkList->last;
                                                                if (iter->tile.r==1)
                                                                    obstructions[NetworkList->last->i+iter->adress.x()][NetworkList->last->j+iter->adress.y()].r=NetworkList->last;
                                                            }

                                                        mag = mag->prev;
                                                    } while(mag!=nullptr);
                                            }

                                        DESTROY_MAGNETS();
                                    }

                            }

                        default: break;
                        }
                    break;
                default: QWidget::mouseReleaseEvent(event);
                }


            update();
        }
}


void DMainScreen::RENDER_NETWORK()//QList<DRailFragment> *network)
{
    //   if (!railnetwork.isEmpty())
    //     for (QList<DRailFragment>::iterator it = railnetwork.begin();it!=railnetwork.end();it++)
    //       {
    //         RENDER_BASIC_multiquad(it->i, it->j, it->ax, it->ay, it->bx, it->by, it->rotation );
    //    }

    if (NetworkList->first!=nullptr)
        {
            DNetworkListElement * iter = NetworkList->first;



            while (1)
                {

                    if ((CurrentTool==TOOL_BULLDOSE) && (LastHoverGroup==HOVER_GROUP_TERRAIN) && ( (obstructions[cursor_x][cursor_y].u==iter)||(obstructions[cursor_x][cursor_y].l==iter)||(obstructions[cursor_x][cursor_y].r==iter)||(obstructions[cursor_x][cursor_y].d==iter)))
                        {
                            QColor tint;tint.setRgbF(1.0,1.0,0.0);
                            shader->setUniformValue(shader->uniformLocation("tint"),tint);
                            shader->setUniformValue(shader->uniformLocation("allwhite"),1);
                            shader->setUniformValue(shader->uniformLocation("noshade"),1);
                       }

                    RENDER_BASIC_multiquad(iter->i, iter->j, iter->ax, iter->ay, iter->bx, iter->by, iter->rot );

                    shader->setUniformValue(shader->uniformLocation("allwhite"),0);
                    shader->setUniformValue(shader->uniformLocation("noshade"),0);



              //let's draw in corners of diag elements.
             // we will draw the adjanced to the LOWER port of the element.

            DCornerNode * port = nullptr;
            shader->setUniformValue(shader->uniformLocation("atlasx"),1);
            shader->setUniformValue(shader->uniformLocation("atlasy"),13);

              switch (iter->type)
                  {
                        case RailTypes::diagULDR:
                               {
                                port = static_cast<class diagULDR*>(iter)->dr;
                                if ((port->dr!=nullptr)&&(port->ul!=nullptr))
                                    {
                                        int x = port->tileUR().x();
                                        int y = port->tileUR().y();
                                         RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d270);

                                        x = port->tileDL().x();
                                        y = port->tileDL().y();
                                        RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d90);
                                    }
                      break;
                      }

                        case RailTypes::tight_UL_L:
                      {
                       port = static_cast<class tight_UL_L*>(iter)->dr;
                       if ((port->dr!=nullptr)&&(port->ul!=nullptr))
                           {
                               int x = port->tileUR().x();
                               int y = port->tileUR().y();
                                RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d270);

                               x = port->tileDL().x();
                               y = port->tileDL().y();
                               RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d90);
                           }
                      break;
                      }

                        case RailTypes::tight_UL_U:
                      {
                       port = static_cast<class tight_UL_U*>(iter)->dr;
                       if ((port->dr!=nullptr)&&(port->ul!=nullptr))
                           {
                               int x = port->tileUR().x();
                               int y = port->tileUR().y();
                                RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d270);

                               x = port->tileDL().x();
                               y = port->tileDL().y();
                               RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d90);
                           }
                      break;
                      }


                        case RailTypes::tight_UR_R:
                      {
                       port = static_cast<class tight_UR_R*>(iter)->dl;
                       if ((port->dl!=nullptr)&&(port->ur!=nullptr))
                           {
                               int x = port->tileUL().x();
                               int y = port->tileUL().y();
                                RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d180);

                               x = port->tileDR().x();
                               y = port->tileDR().y();
                               RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d0);
                           }
                      break;
                      }


                        case RailTypes::tight_UR_U:
                      {
                       port = static_cast<class tight_UR_R*>(iter)->dl;
                       if ((port->dl!=nullptr)&&(port->ur!=nullptr))
                           {
                               int x = port->tileUL().x();
                               int y = port->tileUL().y();
                                RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d180);

                               x = port->tileDR().x();
                               y = port->tileDR().y();
                               RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d0);
                           }
                       break;
                       }


                        case RailTypes::diagURDL:
                      {
                       port = static_cast<class diagURDL*>(iter)->dl;
                       if ((port->dl!=nullptr)&&(port->ur!=nullptr))
                           {
                               int x = port->tileUL().x();
                               int y = port->tileUL().y();
                                RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d180);

                               x = port->tileDR().x();
                               y = port->tileDR().y();
                               RENDER_BASIC_terrainquad(x,y,map[x][y],map[x+1][y],map[x][y+1],map[x+1][y+1],d0);
                           }
                       break;
                       }
                        default://do nothing
                                break;
                  }

              if (iter->next == nullptr) break;
              iter=iter->next;

          }



        }

}






void DMainScreen::mousePressEvent(QMouseEvent *event)
{

    if (READY)
        {

            switch (CurrentTool)
                {
                case TOOL_CHANGE_TERRAIN:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    if (LastHoverGroup==HOVER_GROUP_TERRAIN)
                                        {
                                            cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                        }
                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }
                        break;
                    }


                case TOOL_LANDSCAPE_UP:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    if (LastHoverGroup==HOVER_GROUP_TERRAIN)
                                        {
                                            //cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                            increaseHeight(cursor_x,cursor_y+1);
                                            increaseHeight(cursor_x+1,cursor_y+1);
                                            increaseHeight(cursor_x,cursor_y);
                                            increaseHeight(cursor_x+1,cursor_y);
                                            RENDER_BASIC_CALCULATE_NORMALS();
                                        }

                                    if (LastHoverGroup==HOVER_GROUP_CORNER)
                                        {
                                            //cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                            int ccx = GetCornerXFromID(LastHoverID);
                                            int ccy = GetCornerYFromID(LastHoverID);
                                            int typ = GetCornerTypeFromID(LastHoverID);

                                            switch (typ)
                                                {
                                                case CORNER_DL:
                                                    {
                                                        increaseHeight(ccx,ccy+1);
                                                        break;
                                                    }

                                                case CORNER_DR:
                                                    {
                                                        increaseHeight(ccx+1,ccy+1);
                                                        break;
                                                    }

                                                case CORNER_UL:
                                                    {
                                                        increaseHeight(ccx,ccy);
                                                        break;
                                                    }

                                                case CORNER_UR:
                                                    {
                                                        increaseHeight(ccx+1,ccy);
                                                        break;
                                                    }
                                                default: break;
                                                }
                                            RENDER_BASIC_CALCULATE_NORMALS();
                                        }



                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }
                        break;
                    }

                case TOOL_LANDSCAPE_DOWN:
                    {

                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    break;
                                }

                            case Qt::LeftButton:
                                {

                                    if (LastHoverGroup==HOVER_GROUP_TERRAIN)
                                        {
                                            //cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                            decreaseHeight(cursor_x,cursor_y+1);
                                            decreaseHeight(cursor_x+1,cursor_y+1);
                                            decreaseHeight(cursor_x,cursor_y);
                                            decreaseHeight(cursor_x+1,cursor_y);
                                            RENDER_BASIC_CALCULATE_NORMALS();
                                        }

                                    if (LastHoverGroup==HOVER_GROUP_CORNER)
                                        {
                                            //cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                            int ccx = GetCornerXFromID(LastHoverID);
                                            int ccy = GetCornerYFromID(LastHoverID);
                                            int typ = GetCornerTypeFromID(LastHoverID);

                                            switch (typ)
                                                {
                                                case CORNER_DL:
                                                    {
                                                        decreaseHeight(ccx,ccy+1);
                                                        break;
                                                    }

                                                case CORNER_DR:
                                                    {
                                                        decreaseHeight(ccx+1,ccy+1);
                                                        break;
                                                    }

                                                case CORNER_UL:
                                                    {
                                                        decreaseHeight(ccx,ccy);
                                                        break;
                                                    }

                                                case CORNER_UR:
                                                    {
                                                        decreaseHeight(ccx+1,ccy);
                                                        break;
                                                    }
                                                default: break;
                                                }
                                            RENDER_BASIC_CALCULATE_NORMALS();
                                        }

                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }

                        break;
                    }

                case TOOL_TOGGLE_WATER:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    if (LastHoverGroup==HOVER_GROUP_TERRAIN)
                                        {
                                            if (cells[cursor_x][cursor_y].type==TERRAIN_TYPES_WATER)
                                                {
                                                    cells[cursor_x][cursor_y].type=TERRAIN_TYPES_DIRT;
                                                }
                                            else
                                                {
                                                    cells[cursor_x][cursor_y].type=TERRAIN_TYPES_WATER;
                                                    map[cursor_x][cursor_y] = -1;
                                                    map[cursor_x][cursor_y+1] = -1;
                                                    map[cursor_x+1][cursor_y] = -1;
                                                    map[cursor_x+1][cursor_y+1] = -1;
                                                }
                                        }
                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }

                    }

                case TOOL_RAILROAD_PLACE_START:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    // check if we pressed the proper starting node
                                    // TODO: just check for node...

                                    bool correct = (LastHoverGroup==HOVER_GROUP_CORNER)||(LastHoverGroup==HOVER_GROUP_HOR_SIDE)||(LastHoverGroup==HOVER_GROUP_VER_SIDE);

                                    if (correct)
                                        {
                                         //   if (LastHoverGroup==HOVER_GROUP_HOR_SIDE)
                                               // correct = (HorizontalSideNodes[GetHorSideNode(LastHoverID).x()][GetHorSideNode(LastHoverID).y()].d==nullptr) || (HorizontalSideNodes[GetHorSideNode(LastHoverID).x()][GetHorSideNode(LastHoverID).y()].u==nullptr);

                                           // if (LastHoverGroup==HOVER_GROUP_VER_SIDE)
                                              //  correct = (VerticalSideNodes[GetVerSideNode(LastHoverID).x()][GetVerSideNode(LastHoverID).y()].l==nullptr) || (VerticalSideNodes[GetVerSideNode(LastHoverID).x()][GetVerSideNode(LastHoverID).y()].r==nullptr);

                                            if (LastHoverGroup==HOVER_GROUP_CORNER)
                                                {
                                                   // correct = ((CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].ul!=nullptr) && (CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].dr!=nullptr)) ||
                                                    //        ((CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].ur!=nullptr) && (CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].dl!=nullptr));
                                                    //correct =!correct;
                                                }
                                        }


                                    magnets.clear();
                                    if (correct)
                                        {
                                            HoverMagnet = nullptr;

                                            CurrentTool = TOOL_RAILROAD_PLACE_END;

                                            if (LastHoverGroup == HOVER_GROUP_CORNER)
                                                {
                                                    // RailStart = DNetworkNode(GetCornerNode(LastHoverID).x(),GetCornerNode(LastHoverID).y(),Orientations::Node);
                                                    RailStart.i=GetCornerNode(LastHoverID).x();
                                                    RailStart.j=GetCornerNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::corner;
                                                }

                                            if (LastHoverGroup == HOVER_GROUP_HOR_SIDE)
                                                {
                                                    // RailStart = DNetworkNode(GetCornerNode(LastHoverID).x(),GetCornerNode(LastHoverID).y(),Orientations::Node);
                                                    RailStart.i=GetHorSideNode(LastHoverID).x();
                                                    RailStart.j=GetHorSideNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::horiz;
                                                }

                                            if (LastHoverGroup == HOVER_GROUP_VER_SIDE)
                                                {
                                                    RailStart.i=GetVerSideNode(LastHoverID).x();
                                                    RailStart.j=GetVerSideNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::vert;
                                                }



                                            PREPARE_MAGNETS_END();

                                        }
                                    else
                                        {
                                            //error...
                                        }

                                    break;
                                }

                            default: QWidget::mousePressEvent(event);
                            }

                        break;
                    }

                case TOOL_BULLDOSE:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {

                                    if (LastHoverGroup == HOVER_GROUP_TERRAIN)
                                        {
                                            bulldose_rail(obstructions[cursor_x][cursor_y].u);
                                            bulldose_rail(obstructions[cursor_x][cursor_y].l);
                                            bulldose_rail(obstructions[cursor_x][cursor_y].d);
                                            bulldose_rail(obstructions[cursor_x][cursor_y].r);
                                           }

                                    // check if we pressed the something like UI element or active entity like train...
                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }
                        break;
                    }



                default:// also TOOL_NONE
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    // check if we pressed the something like UI element or active entity like train...
                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }
                    }

                }
        }
}


void DMainScreen::bulldose_rail(DNetworkListElement* dead)
{

    if (dead!=nullptr)
        {

            for (QList<ObstructionElement>::iterator ir=dead->imprint.begin();ir!=dead->imprint.end();ir++)
                {
                    if (ir->tile.u==1) obstructions[dead->i+ir->adress.x()][dead->j+ir->adress.y()].u = nullptr;
                    if (ir->tile.l==1) obstructions[dead->i+ir->adress.x()][dead->j+ir->adress.y()].l = nullptr;
                    if (ir->tile.d==1) obstructions[dead->i+ir->adress.x()][dead->j+ir->adress.y()].d = nullptr;
                    if (ir->tile.r==1) obstructions[dead->i+ir->adress.x()][dead->j+ir->adress.y()].r = nullptr;
                }

               dead->kill();
        }

}

void DMainScreen::increaseHeight(int x, int y)
{

    map[x][y]++;

    if (x>0)
        {
            if ((map[x][y]-map[x-1][y])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x-1,y);
            else if ((map[x][y]-map[x-1][y])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x-1,y);

            if (y>0)
                {
                    if ((map[x][y]-map[x-1][y-1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x-1,y-1);
                    else if ((map[x][y]-map[x-1][y-1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x-1,y-1);
                }

            if (y<HEIGHT)
                {
                    if ((map[x][y]-map[x-1][y+1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x-1,y+1);
                    else if((map[x][y]-map[x-1][y+1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x-1,y+1);
                }
        }


    if (y>0)
        {
            if ((map[x][y]-map[x][y-1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x,y-1);
            else if ((map[x][y]-map[x][y-1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x,y-1);
        }

    if (y<HEIGHT)
        {
            if ((map[x][y]-map[x][y+1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x,y+1);
            else if ((map[x][y]-map[x][y+1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x,y+1);
        }

    if (x<WIDTH)
        {
            if ((map[x][y]-map[x+1][y])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x+1,y);
            else if ((map[x][y]-map[x+1][y])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x+1,y);

            if (y>0)
                {
                    if ((map[x][y]-map[x+1][y-1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x+1,y-1);
                    else if ((map[x][y]-map[x+1][y-1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x+1,y-1);
                }

            if (y<HEIGHT)
                {
                    if ((map[x][y]-map[x+1][y+1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x+1,y+1);
                    else if((map[x][y]-map[x+1][y+1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x+1,y+1);
                }
        }

}

void DMainScreen::decreaseHeight(int x, int y)
{
    map[x][y]--;

    if (x>0)
        {
            if ((map[x][y]-map[x-1][y])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x-1,y);
            else if ((map[x][y]-map[x-1][y])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x-1,y);

            if (y>0)
                {
                    if ((map[x][y]-map[x-1][y-1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x-1,y-1);
                    else if ((map[x][y]-map[x-1][y-1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x-1,y-1);
                }

            if (y<HEIGHT)
                {
                    if ((map[x][y]-map[x-1][y+1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x-1,y+1);
                    else if((map[x][y]-map[x-1][y+1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x-1,y+1);
                }
        }


    if (y>0)
        {
            if ((map[x][y]-map[x][y-1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x,y-1);
            else if ((map[x][y]-map[x][y-1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x,y-1);
        }

    if (y<HEIGHT)
        {
            if ((map[x][y]-map[x][y+1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x,y+1);
            else if ((map[x][y]-map[x][y+1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x,y+1);
        }

    if (x<WIDTH)
        {
            if ((map[x][y]-map[x+1][y])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x+1,y);
            else if ((map[x][y]-map[x+1][y])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x+1,y);

            if (y>0)
                {
                    if ((map[x][y]-map[x+1][y-1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x+1,y-1);
                    else if ((map[x][y]-map[x+1][y-1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x+1,y-1);
                }

            if (y<HEIGHT)
                {
                    if ((map[x][y]-map[x+1][y+1])>HEIGHT_DIFF_THRESHOLD) increaseHeight(x+1,y+1);
                    else if((map[x][y]-map[x+1][y+1])<-HEIGHT_DIFF_THRESHOLD) decreaseHeight(x+1,y+1);
                }
        }
}

GLfloat DMainScreen::crossx(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{

    GLfloat temp_x = y1*z2 - y2*z1;
    GLfloat temp_y = z1*x2 - x1*z2;
    GLfloat temp_z = x1*y2 - x2*y1;

    GLfloat len = sqrt(temp_x*temp_x + temp_y*temp_y + temp_z*temp_z);
    if (temp_z<0) len = len*-1;
    return temp_x/len;
}
GLfloat DMainScreen::crossy(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{
    GLfloat temp_x = y1*z2 - y2*z1;
    GLfloat temp_y = z1*x2 - x1*z2;
    GLfloat temp_z = x1*y2 - x2*y1;

    GLfloat len = sqrt(temp_x*temp_x + temp_y*temp_y + temp_z*temp_z);
    if (temp_z<0) len = len*-1;
    return temp_y/len;
}
GLfloat DMainScreen::crossz(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{
    GLfloat temp_x = y1*z2 - y2*z1;
    GLfloat temp_y = z1*x2 - x1*z2;
    GLfloat temp_z = x1*y2 - x2*y1;

    GLfloat len = sqrt(temp_x*temp_x + temp_y*temp_y + temp_z*temp_z);
    if (temp_z<0) len = len*-1;
    return temp_z/len;
}



GLfloat DMainScreen::getXfrom3D (GLfloat x, GLfloat y ,GLfloat z)
{
    Q_UNUSED(z);
    return  w/2*x -w/2*y;
}

GLfloat DMainScreen::getYfrom3D (GLfloat x, GLfloat y ,GLfloat z)
{
    return  w/4*x + w/4*y - w/4/8*z*8;
}

GLfloat DMainScreen::getYfromVec3(vec3 vec)
{
    return  getYfrom3D(vec.x,vec.y,vec.z);
}

GLfloat DMainScreen::getXfromVec3(vec3 vec)
{
    return  getXfrom3D(vec.x,vec.y,vec.z);
}

void DMainScreen::RENDER_DRAW_3D_CAR(int i, int j, GLfloat degree)
{
    glColor3f(1.0,1.0,1.0);

    // we draw the car at the center of the (i,j) terrain quad, rotated (degree) degrees along the Z axis
    // the length of the quad is equal to 1.

    // the length of the long side is equal to 1;
    // the length of hte short side is equal to 0.5;
    // the height of the quad is equal to 0.5;

    GLfloat size_y = 1;
    GLfloat size_x = 0.4;
    GLfloat size_z = 7.0/8.0;

    //  let's enumerate our vertices
    //  y x ->
    //  | low      high
    //  v  3 2      7 6
    //     .        .
    //     0 1      4 5

    vec3 vertices[8];

    vertices[0].x =-size_x*0.5;
    vertices[0].y =size_y*0.5;
    vertices[0].z =-size_z*0.5;

    vertices[1].x =+size_x*0.5;
    vertices[1].y =size_y*0.5;
    vertices[1].z =-size_z*0.5;

    vertices[2].x =+size_x*0.5;
    vertices[2].y =-size_y*0.5;
    vertices[2].z =-size_z*0.5;

    vertices[3].x =-size_x*0.5;
    vertices[3].y =-size_y*0.5;
    vertices[3].z =-size_z*0.5;

    vertices[4].x =-size_x*0.5;
    vertices[4].y =size_y*0.5;
    vertices[4].z =size_z*0.5;

    vertices[5].x =+size_x*0.5;
    vertices[5].y =size_y*0.5;
    vertices[5].z =size_z*0.5;

    vertices[6].x =+size_x*0.5;
    vertices[6].y =-size_y*0.5;
    vertices[6].z =size_z*0.5;

    vertices[7].x =-size_x*0.5;
    vertices[7].y =-size_y*0.5;
    vertices[7].z =size_z*0.5;


    //now let's convert these coordinates into rotation coordinates rho-phi-theta...
    vec3 rot[8];


    //================= LET'S REPEAT THIS TRICK BUT WITH THE ROTATION ALONG THE X AXIS.
    for (int v =0; v<8; v++)
        {
            rot[v].x = sqrt( (vertices[v].x-0)*(vertices[v].x-0)+(vertices[v].y-0)*(vertices[v].y-0)+(vertices[v].z-0)*(vertices[v].z-0));//rho
            rot[v].y = atan2(vertices[v].z,vertices[v].y);
            //phi
            if (rot[v].y<0) rot[v].y = rot[v].y+2*PI;


            // rot[v].z = atan2( sqrt((vertices[v].x-0)*(vertices[v].x-0)+(vertices[v].y-0)*(vertices[v].y-0)), vertices[v].z);
            rot[v].z = acos( vertices[v].x/rot[v].x);
        }


    //npw let's apply rotations
    for (int v =0; v<8; v++)
        {
            rot[v].y += 15/180.0*PI;
        }


    // now let's convert back to cartesian

    for (int v =0; v<8; v++)
        {
            vertices[v].y = rot[v].x*cos(rot[v].y)*sin(rot[v].z);
            vertices[v].z = rot[v].x*sin(rot[v].y)*sin(rot[v].z);
            vertices[v].x = rot[v].x*cos(rot[v].z);
        }

    //============



    for (int v= 0; v<8; v++)
        vertices[v].z += size_z*0.5;

    for (int v =0; v<8; v++)
        {
            rot[v].x = sqrt( (vertices[v].x-0)*(vertices[v].x-0)+(vertices[v].y-0)*(vertices[v].y-0)+(vertices[v].z-0)*(vertices[v].z-0));//rho
            rot[v].y = atan2(vertices[v].y,vertices[v].x);
            //phi
            if (rot[v].y<0) rot[v].y = rot[v].y+2*PI;


            // rot[v].z = atan2( sqrt((vertices[v].x-0)*(vertices[v].x-0)+(vertices[v].y-0)*(vertices[v].y-0)), vertices[v].z);
            rot[v].z = acos( vertices[v].z/rot[v].x);
        }


    //npw let's apply rotations
    for (int v =0; v<8; v++)
        {
            rot[v].y += degree/180.0*PI;
        }


    // now let's convert back to cartesian

    for (int v =0; v<8; v++)
        {
            vertices[v].x = rot[v].x*cos(rot[v].y)*sin(rot[v].z);
            vertices[v].y = rot[v].x*sin(rot[v].y)*sin(rot[v].z);
            vertices[v].z = rot[v].x*cos(rot[v].z);
        }


    //let's draw long right side
    // it's coords are 1-5-2 5-2-6


    shader->setUniformValue(shader->uniformLocation("atlasx"), 6);
    shader->setUniformValue(shader->uniformLocation("atlasy"), 12);
    shader->setUniformValue(shader->uniformLocation("noshade"), 0);


    int centroid_x = sx + w/2*i -w/2*j;
    int centroid_y = sy + w/4*i + w/4*j + w/4 +w/4;


    RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[3],vertices[1],vertices[2]);//bottom is always first

    //to define the order we should implement something like z-buffer
    //z value is a x+y of a screen coordinates

    //int z_buffer = 0;

    if ( ((degree>=0)&&(degree<45))||((degree>=360-45)&&(degree<360)) )
        {

            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[3],vertices[7],vertices[2],vertices[6]);//far
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[4],vertices[3],vertices[7]);//left
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[1],vertices[5],vertices[2],vertices[6]);//right
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[4],vertices[1],vertices[5]);//near
        }

    if ( ((degree>=45)&&(degree<135)) )
        {

            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[4],vertices[3],vertices[7]);//left
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[4],vertices[1],vertices[5]);//near
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[3],vertices[7],vertices[2],vertices[6]);//far
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[1],vertices[5],vertices[2],vertices[6]);//right
        }

    if ( ((degree>=135)&&(degree<225)) )
        {
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[4],vertices[1],vertices[5]);//near
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[1],vertices[5],vertices[2],vertices[6]);//right
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[4],vertices[3],vertices[7]);//left
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[3],vertices[7],vertices[2],vertices[6]);//far
        }

    if ( ((degree>=225)&&(degree<315)) )
        {
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[1],vertices[5],vertices[2],vertices[6]);//right
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[3],vertices[7],vertices[2],vertices[6]);//far
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[4],vertices[1],vertices[5]);//near
            RENDER_3D_QUAD(centroid_x,centroid_y,vertices[0],vertices[4],vertices[3],vertices[7]);//left
        }





    RENDER_3D_QUAD(centroid_x,centroid_y,vertices[4],vertices[7],vertices[5],vertices[6]);//top is always last




}

void DMainScreen::RENDER_3D_QUAD (GLfloat centroid_x, GLfloat centroid_y, vec3 vert1, vec3 vert2, vec3 vert3, vec3 vert4)
{

    glBegin(GL_TRIANGLES);
    //  shader->setUniformValue(shader->uniformLocation("dz2"), vertices[5].z-vertices[1].z);
    //  shader->setUniformValue(shader->uniformLocation("dz1"), vertices[2].z-vertices[1].z);

    //  shader->setUniformValue(shader->uniformLocation("dx2"), vertices[5].x-vertices[1].x);
    //  shader->setUniformValue(shader->uniformLocation("dx1"), vertices[2].x-vertices[1].x);

    //  shader->setUniformValue(shader->uniformLocation("dy2"), vertices[5].y-vertices[1].y);
    //  shader->setUniformValue(shader->uniformLocation("dy1"), vertices[2].y-vertices[1].y);

    glTexCoord2f(0.0,1.0);
    glVertex3f(centroid_x + getXfromVec3(vert1),centroid_y + getYfromVec3(vert1),1);
    glTexCoord2f(0.0,0.0);
    glVertex3f(centroid_x + getXfromVec3(vert2),centroid_y + getYfromVec3(vert2),1);
    glTexCoord2f(1.0,1.0);
    glVertex3f(centroid_x + getXfromVec3(vert3),centroid_y + getYfromVec3(vert3),1);

    glTexCoord2f(0.0,0.0);
    glVertex3f(centroid_x + getXfromVec3(vert2),centroid_y + getYfromVec3(vert2),1);
    glTexCoord2f(1.0,1.0);
    glVertex3f(centroid_x + getXfromVec3(vert3),centroid_y + getYfromVec3(vert3),1);
    glTexCoord2f(1.0,0.0);
    glVertex3f(centroid_x + getXfromVec3(vert4),centroid_y + getYfromVec3(vert4),1);
    glEnd();
}


QPoint DMainScreen::coord00(texture_rotation rot)
{
    QPoint ret;
    switch (rot)
        {
        case d0:
            {
                ret.setX(0);ret.setY(0);break;
            }
        case d90:
            {
                ret.setX(0);ret.setY(1);break;
            }
        case d180:
            {
                ret.setX(1);ret.setY(1);break;
            }
        case d270:
            {
                ret.setX(1);ret.setY(0);break;
            }

        case m0:
            {
                ret.setX(1);ret.setY(0);break;
            }
        case m90:
            {
                ret.setX(1);ret.setY(1);break;
            }
        case m180:
            {
                ret.setX(0);ret.setY(1);break;
            }
        case m270:
            {
                ret.setX(0);ret.setY(0);break;
            }

        }
    return ret;
}


QPoint DMainScreen::coord10(texture_rotation rot)
{
    QPoint ret;
    switch (rot)
        {
        case d0:
            {
                ret.setX(1);ret.setY(0);break;
            }
        case d90:
            {
                ret.setX(0);ret.setY(0);break;
            }
        case d180:
            {
                ret.setX(0);ret.setY(1);break;
            }
        case d270:
            {
                ret.setX(1);ret.setY(1);break;
            }

        case m0:
            {
                ret.setX(0);ret.setY(0);break;
            }
        case m90:
            {
                ret.setX(1);ret.setY(0);break;
            }
        case m180:
            {
                ret.setX(1);ret.setY(1);break;
            }
        case m270:
            {
                ret.setX(0);ret.setY(1);break;
            }

        }
    return ret;
}

QPoint DMainScreen::coord01(texture_rotation rot)
{
    QPoint ret;
    switch (rot)
        {
        case d0:
            {
                ret.setX(0);ret.setY(1);break;
            }
        case d90:
            {
                ret.setX(1);ret.setY(1);break;
            }
        case d180:
            {
                ret.setX(1);ret.setY(0);break;
            }
        case d270:
            {
                ret.setX(0);ret.setY(0);break;
            }

        case m0:
            {
                ret.setX(1);ret.setY(1);break;
            }
        case m90:
            {
                ret.setX(0);ret.setY(1);break;
            }
        case m180:
            {
                ret.setX(0);ret.setY(0);break;
            }
        case m270:
            {
                ret.setX(1);ret.setY(0);break;
            }

        }
    return ret;
}


QPoint DMainScreen::coord11(texture_rotation rot)
{
    QPoint ret;
    switch (rot)
        {
        case d0:
            {
                ret.setX(1);ret.setY(1);break;
            }
        case d90:
            {
                ret.setX(1);ret.setY(0);break;
            }
        case d180:
            {
                ret.setX(0);ret.setY(0);break;
            }
        case d270:
            {
                ret.setX(0);ret.setY(1);break;
            }

        case m0:
            {
                ret.setX(0);ret.setY(1);break;
            }
        case m90:
            {
                ret.setX(0);ret.setY(0);break;
            }
        case m180:
            {
                ret.setX(1);ret.setY(0);break;
            }
        case m270:
            {
                ret.setX(1);ret.setY(1);break;
            }

        }
    return ret;
}




void DMainScreen::RENDER_BASIC_terrainquad(int x, int y, int z0, int z1, int z2, int z3, texture_rotation rot)
{
    glColor3f(1.0,1.0,1.0);



    // let's draw concave surfaces only
    // for this let's check whether diagonal is on top on the center
    // to do this, let's get the average height of their vertices
    // we even don't need to divide by 2!



    if(abs(z0+z3) < abs(z1+z2) )

        {
            shader->setUniformValue(shader->uniformLocation("dz2"), static_cast<GLfloat>(z1)-static_cast<GLfloat>(z0));
            shader->setUniformValue(shader->uniformLocation("dz1"), static_cast<GLfloat>(z3)-static_cast<GLfloat>(z0));

            shader->setUniformValue(shader->uniformLocation("dx2"), 1.0f);
            shader->setUniformValue(shader->uniformLocation("dx1"), 1.0f);

            shader->setUniformValue(shader->uniformLocation("dy2"), 0.0f);
            shader->setUniformValue(shader->uniformLocation("dy1"), 1.0f);

            glBegin(GL_TRIANGLES);

            QPoint p;
            glNormal3f(normals[x][y].x,normals[x][y].y,normals[x][y].z );
            p=coord00(rot);glTexCoord2f(p.x(),p.y());//glTexCoord2f(0.0f,0.0f);
            glVertex3f(sx + w/2*x -w/2*y ,sy + w/4*x + w/4*y - w/4/8*z0,1);

            glNormal3f(normals[x+1][y].x,normals[x+1][y].y,normals[x+1][y].z );
            p=coord10(rot);glTexCoord2f(p.x(),p.y());//glTexCoord2f(1.0f,0.0f);
            glVertex3f(sx + w/2*(x+1) - w/2*y,sy+w/4*(x+1) + w/4*y- w/4/8*z1,1);

            glNormal3f(normals[x+1][y+1].x,normals[x+1][y+1].y,normals[x+1][y+1].z );
            p=coord11(rot);glTexCoord2f(p.x(),p.y());//glTexCoord2f(1.0f,1.0f);
            glVertex3f(sx + w/2*(x+1) - w/2*(y+1),sy+w/4*(x+1) + w/4*(y+1)- w/4/8*z3,1);
            glEnd();


            shader->setUniformValue(shader->uniformLocation("dz2"), static_cast<GLfloat>(z3)-static_cast<GLfloat>(z0));
            shader->setUniformValue(shader->uniformLocation("dz1"), static_cast<GLfloat>(z2)-static_cast<GLfloat>(z0));

            shader->setUniformValue(shader->uniformLocation("dx2"), 1.0f);
            shader->setUniformValue(shader->uniformLocation("dx1"), 0.0f);

            shader->setUniformValue(shader->uniformLocation("dy1"), 1.0f);
            shader->setUniformValue(shader->uniformLocation("dy2"), 1.0f);



            glBegin(GL_TRIANGLES);

            glNormal3f(normals[x][y].x,normals[x][y].y,normals[x][y].z );
            p=coord00(rot);glTexCoord2f(p.x(),p.y());//glTexCoord2f(0.0f,0.0f);
            glVertex3f(sx + w/2*x -w/2*y ,sy + w/4*x + w/4*y- w/4/8*z0 ,1);

            glNormal3f(normals[x+1][y+1].x,normals[x+1][y+1].y,normals[x+1][y+1].z );
            p=coord11(rot);glTexCoord2f(p.x(),p.y());//glTexCoord2f(1.0f,1.0f);
            glVertex3f(sx + w/2*(x+1) - w/2*(y+1),sy+w/4*(x+1) + w/4*(y+1)- w/4/8*z3,1);

            glNormal3f(normals[x][y+1].x,normals[x][y+1].y,normals[x][y+1].z );
            p=coord01(rot);glTexCoord2f(p.x(),p.y());// glTexCoord2f(0.0f,1.0f);
            glVertex3f(sx + w/2*(x) - w/2*(y+1),sy+w/4*(x) + w/4*(y+1)- w/4/8*z2,1);

            glEnd();

        }
    else
        {

            shader->setUniformValue(shader->uniformLocation("dz2"), static_cast<GLfloat>(z1)-static_cast<GLfloat>(z0));
            shader->setUniformValue(shader->uniformLocation("dz1"), static_cast<GLfloat>(z2)-static_cast<GLfloat>(z0));

            shader->setUniformValue(shader->uniformLocation("dx2"), 1.0f);
            shader->setUniformValue(shader->uniformLocation("dx1"), 0.0f);

            shader->setUniformValue(shader->uniformLocation("dy1"), 1.0f);
            shader->setUniformValue(shader->uniformLocation("dy2"), 0.0f);

            QPoint p;
            glBegin(GL_TRIANGLES);
            glNormal3f(normals[x][y].x,normals[x][y].y,normals[x][y].z );
            p=coord00(rot);glTexCoord2f(p.x(),p.y());// glTexCoord2f(0.0f,0.0f);
            glVertex3f(sx + w/2*x -w/2*y ,sy + w/4*x + w/4*y - w/4/8*z0,1);

            glNormal3f(normals[x+1][y].x,normals[x+1][y].y,normals[x+1][y].z );
            p=coord10(rot);glTexCoord2f(p.x(),p.y());// glTexCoord2f(1.0f,0.0f);
            glVertex3f(sx + w/2*(x+1) - w/2*y,sy+w/4*(x+1) + w/4*y- w/4/8*z1,1);

            glNormal3f(normals[x][y+1].x,normals[x][y+1].y,normals[x][y+1].z );
            p=coord01(rot);glTexCoord2f(p.x(),p.y());// glTexCoord2f(0.0f,1.0f);
            glVertex3f(sx + w/2*(x) - w/2*(y+1),sy+w/4*(x) + w/4*(y+1)- w/4/8*z2,1);
            glEnd();


            shader->setUniformValue(shader->uniformLocation("dz1"), static_cast<GLfloat>(z2)-static_cast<GLfloat>(z1));
            shader->setUniformValue(shader->uniformLocation("dz2"), static_cast<GLfloat>(z3)-static_cast<GLfloat>(z1));

            shader->setUniformValue(shader->uniformLocation("dx1"), -1.0f);
            shader->setUniformValue(shader->uniformLocation("dx2"), 0.0f);

            shader->setUniformValue(shader->uniformLocation("dy1"), 1.0f);
            shader->setUniformValue(shader->uniformLocation("dy2"), 1.0f);

            glBegin(GL_TRIANGLES);
            glNormal3f(normals[x+1][y].x,normals[x+1][y].y,normals[x+1][y].z );
            p=coord10(rot);glTexCoord2f(p.x(),p.y());// glTexCoord2f(1.0f,0.0f);
            glVertex3f(sx + w/2*(x+1) - w/2*y,sy+w/4*(x+1) + w/4*y- w/4/8*z1,1);

            glNormal3f(normals[x][y+1].x,normals[x][y+1].y,normals[x][y+1].z );
            p=coord01(rot);glTexCoord2f(p.x(),p.y());// glTexCoord2f(0.0f,1.0f);
            glVertex3f(sx + w/2*(x) - w/2*(y+1),sy+w/4*(x) + w/4*(y+1)- w/4/8*z2,1);

            glNormal3f(normals[x+1][y+1].x,normals[x+1][y+1].y,normals[x+1][y+1].z );
            p=coord11(rot);glTexCoord2f(p.x(),p.y());// glTexCoord2f(1.0f,1.0f);
            glVertex3f(sx + w/2*(x+1) - w/2*(y+1),sy+w/4*(x+1) + w/4*(y+1)- w/4/8*z3,1);
            glEnd();


        }




}

unsigned DMainScreen::gethexindex(unsigned i, unsigned v)
{
    if (i==0)
        return 0+7*16+v;
    else
        return (i-1)*8+v;

}

void DMainScreen::keyPressEvent(QKeyEvent *event)
{

    switch (event->key())
        {

        case Qt::Key_0:
            CurrentTool = TOOL_NONE;
            break;
        case Qt::Key_1:
            CurrentTool = TOOL_LANDSCAPE_DOWN;
            break;
        case Qt::Key_2:
            CurrentTool = TOOL_LANDSCAPE_UP;
            break;
        case Qt::Key_3:
            CurrentTool = TOOL_CHANGE_TERRAIN;
            break;
        case Qt::Key_4:
            CurrentTool = TOOL_TOGGLE_WATER;
            break;

        case Qt::Key_7:
            CurrentTool = TOOL_RAILROAD_PLACE_START;
            break;

        case Qt::Key_8:
            CurrentTool = TOOL_BULLDOSE;
            break;
        default:
            break;
        }
}
