#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


/*  a portion of init() */
tobj = gluNewTess();
gluTessCallback(tobj, GLU_TESS_VERTEX,
                   (GLvoid (*) ()) &glVertex3dv);
gluTessCallback(tobj, GLU_TESS_BEGIN,
                   (GLvoid (*) ()) &beginCallback);
gluTessCallback(tobj, GLU_TESS_END,
                   (GLvoid (*) ()) &endCallback);
gluTessCallback(tobj, GLU_TESS_ERROR,
                   (GLvoid (*) ()) &errorCallback);

/*  the callback routines registered by gluTessCallback() */

void beginCallback(GLenum which)
{
   glBegin(which);
}

void endCallback(void)
{
   glEnd();
}

void errorCallback(GLenum errorCode)
{
   const GLubyte *estring;

   estring = gluErrorString(errorCode);
   fprintf (stderr, "Tessellation Error: %s\n", estring);
   exit (0);
}
