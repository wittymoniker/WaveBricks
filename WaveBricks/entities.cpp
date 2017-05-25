//entities

#include <cmath>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
static int slices = 128;//if needed
static int stacks = 128;//if needed
class instrument{
    public:
        float yRes, xRes, siz, x,y,z, r,g,b, rx,rrx,ry,rry,rz,rrz, fade;
        bool gravity, collide;
        string type;
};
std::vector<instrument> objList;

