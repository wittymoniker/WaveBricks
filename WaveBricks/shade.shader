#version 420
#extension GL_ARB_separate_shader_objects : enable

uniform vec3 initialUniform = vec3(1.0, 0.0, 0.0);
layout(vertices = 128) uniform initialUniform out;



void main(){

    gl_out[gl_InvocationID].gl_Position= gl_in[gl_InvocationID].gl_Position;// and then set tessellation levels

}
in gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[]
} gl_in[gl_PatchVerticesIn];


