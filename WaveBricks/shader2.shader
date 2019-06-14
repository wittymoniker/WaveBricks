
#version 420
#GL_ARB_separate_shader_objects : enable

uniform vec3 initialUniform = vec3(1.0, 0.0, 0.0);

layout (triangles, equal_spacing, ccw) uniform initialUniform in;

out vec4 color;
void main()
{
    float u=gl_TessCoord.x;
    float omu= 1-u;
    float v = gl_TessCoord.y;
    float omv = 1-v;
    float m = gl_TessCoord.z;
    float omm = 1-m;

    color = gl_TessCoord;

    gl_Position =
    omu * omv  * gl_in[0].gl_Position +
    u* omv * gl_in[1].gl_Position +
    u*v*gl_in[2].gl_Position+
    omu*v*gl_in[3].gl_Position;
}
in gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[]
} gl_in[gl_PatchVerticesIn];

out gl_PerVertex
{
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[]
};
