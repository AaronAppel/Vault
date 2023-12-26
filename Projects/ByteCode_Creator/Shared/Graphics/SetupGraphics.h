#ifndef __SetupGraphics_H__
#define __SetupGraphics_H__

#include "../Libraries/lodepng/lodepng.h"
#include "ImageHelpers.h"

#include "SetupLibraries.h"

// math
#include <cmath>
#include "MathHelpers.h"
#include "MathFunctions.h"
#include "Vector.h"
#include "VectorMathHelpers.h"

typedef Vector2 vec2;
typedef Vector3 vec3;
typedef Vector4 vec4;

typedef Vector2Int ivec2;
typedef Vector3Int ivec3;
typedef Vector4Int ivec4;

#include "MyQuaternion.h"
#include "MyMatrix.h"
typedef MyMatrix mat4;

typedef unsigned int uint;

// system libraries
#include <vector>
#include <string>

// graphics
#define Wind_CCW 0
enum eShaderTypes
{
    eShader_Basic2D = 0,
    eShader_Basic3D,
    eShader_LitMaterial
};

// helpers
#include "PrintFuncs.h"
#include "FileUtils.h"
#include "StringHelpers.h"
#include "OpenGLHelpers.h"

#include "Graphics\ShaderProgram\ShaderProgram.h"
#include "Graphics\ShaderProgram\ShaderFactory.h"

#include "Graphics\Mesh\VertexData.h"
#include "Graphics\Mesh\mesh.h"
#include "Graphics\Mesh\MeshFactory.h"
#include "Graphics\Mesh\MeshUtilities.h"

#include "Graphics\Sprite\Sprite.h"

#endif //__SetupGraphics_H__
