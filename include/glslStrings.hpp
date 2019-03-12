#define GLEW_STATIC
#include "glew.h"

#ifndef GLSL_STRINGS
#define GLSL_STRINGS

namespace vertexShaderStrings
{
	const GLchar* vertSrcLine[] = {
    "#version 330 core\n"
	""
    "in vec2 inPoint;"
    "in vec4 inVertexColor;"
    "out vec4 outVertexColor;"
    ""
	"void main(void)"
	"{"
	"	gl_Position = vec4( inPoint[ 0 ] , inPoint[ 1 ] , 0.5 , 1.0 );"
	"	outVertexColor = inVertexColor;"
	"}"
    };
}

namespace fragmentShaderStrings
{
	const GLchar* fragSrcLine[] = {
    "#version 330 core\n"
    ""
    "in vec4 outVertexColor;"
	"out vec4 color;"
	""
	"void main(void)"
	"{"
	"	color = outVertexColor;"
	"}"
    };
};

#endif
