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
        void tick(float, float, float, float, float, float,float,float, float,float,float, float,float,float,
                  float, bool);
        void render();
        float type, yRes, xRes, sX, sY, x,y,z, r,g,b, rx,ry,rz, rrx,rry,rrz, fade;
        bool gravity, collide, d2;
        std::string name;
};

#endif // ENTITIES_H_INCLUDED
