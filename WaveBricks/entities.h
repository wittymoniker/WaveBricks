#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED
#include<windows.h>
#include <stdlib.h>
#include<vector>
using namespace std;
template< class T >
class reference_wrapper;
class instrument{
    public:
        static double coords;
        const float PI = 3.141592653589f;
        void tick(){
            /*if(d2){
                glBegin(GL_POLYGON);
                for(int i = 0; i < verts; i++){
                    float angle = i/(float)verts * 2.f * PI;
                    glVertex2f(cos(angle) * vertAmps[i], sin(angle) * vertAmps[i]);
                }
                glEnd();
            }else{

            }*/
        }

        void render(){

        }
        float verts, scale, x,y,z, r,g,b, rx,ry,rz, cr,cb,cg;
        bool gravity, collide, d2;
        std::vector<float>vertAmps;
        std::string name;
};

#endif // ENTITIES_H_INCLUDED
