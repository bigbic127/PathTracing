#version 430 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexcoord;
layout(location = 3) in vec3 vTangent;
layout(location = 4) in vec3 vBitangent;
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

void main()
{
    gl_Position = mProjection * mView * mModel * vec4(vPosition, 1.0f);
}