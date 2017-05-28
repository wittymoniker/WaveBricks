//entities

#include <cmath>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include "GLUI/glui.h"
#else
#include <GL/glut.h>
#include "GL/glui.h"
#endif
#include "al.h"
#include "alc.h"
#include "entities.h"
using namespace std;
static int slices = 128;//if needed
static int stacks = 128;//if needed
static double coords;

void instrument::tick(float verts, float yResolution, float xResolution, float scX, float scY, float rpx,float rpy,float rpz, float cr,float cg,float cb,
                      float rox,float roy,float roz, float fader, bool dim2){

                      if(d2){
                        for (int i=0; i<verts; i++){
                            if (type >= 2){
                                //glutSolidCircle(sX+sY, rx, ry);
                                if(type = 1){
                                    //glutSolidTriangle(sX, sY, rx, ry);
                                }
                                if(type = 2){
                                    //glutSolidTeapot(sX, sY, ry, rx);
                                }
                            }else{
                                glBegin(GL_TRIANGLE_FAN);
                                glColor3f(1-cr,1-cg,1-cb);
                                glVertex2f(instrument::x + rpx, instrument::y + rpy);
                                coords = (instrument::x + rpx, instrument::y + rpy);
                                for (i=0; i<=verts;i++){


                                         glVertex2f(-0.4,0);
                                     glVertex2f(0.4,0);
                                         glColor3f(0,1,0);
                                     glVertex2f(0,-0.5);
                                     glEnd();
                                }
                            }

                        }
                      }else{
                            if (type >= 2){
                                glutSolidSphere(sX+sY, rx, ry);
                                if(type = 1){
                                    glutSolidCone(sX, sY, rx, ry);
                                }
                                if(type = 2){
                                    glutSolidTorus(sX, sY, rx, ry);
                                }
                            }else{

                            }
                      }

}

void instrument::render(){

}

