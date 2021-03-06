/*==================================================================================
    Copyright (c) 2008, DAVA Consulting, LLC
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    * Neither the name of the DAVA Consulting, LLC nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE DAVA CONSULTING, LLC AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL DAVA CONSULTING, LLC BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Revision History:
        * Created by Vitaliy Borodovsky 
=====================================================================================*/
#ifndef __DAVAENGINE_RENDER_BASE_H__
#define __DAVAENGINE_RENDER_BASE_H__

#include "Base/BaseTypes.h"
#include "DAVAConfig.h"

/**
	\defgroup render Rendering abstraction
	\defgroup render_2d 2D Rendering
	\defgroup render_3d 3D Rendering
*/

/*
 Boroda: Я не знаю почему но <glew/gl.h> при включение из .mm файлов выдает ошибку как будто кто-то уже подключил 
 стандартный GL хотя в проекте нигде нет на него упоминаний. Есть подозрение что какой-то конфликт с внутренностями ObjC
 Как обойти пока непонятно - я сделал этот хедер чтобы включать его только там где это реально надо. 
 
 Раньше это лежало в BaseTypes.h
 */

#ifdef __DAVAENGINE_IPHONE__
	#define __DAVAENGINE_OPENGL__
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>
    #import <OpenGLES/ES2/gl.h>
    #import <OpenGLES/ES2/glext.h>
#elif defined(__DAVAENGINE_MACOS__)
	#define __DAVAENGINE_OPENGL__
	//	#include <GL/glew.h>
	#include <OpenGL/OpenGL.h>
	//	#include <GLUT/glut.h>
#elif defined(__DAVAENGINE_WIN32__)
 	#if defined(__DAVAENGINE_RENDER_AUTOCONFIG__)
 	#define __DAVAENGINE_DIRECTX9__
//	#define __DAVAENGINE_OPENGL__
 	#endif 

	#if defined(__DAVAENGINE_OPENGL__)
		#include <GL/glew.h>
		#include <direct.h>
	#elif defined(__DAVAENGINE_DIRECTX9__)
		// TODO: right now Sprite code do not compiles without GL types. Fix that. 
		#include <GL/gl.h>
		// #include <direct.h>
		
		#define D3D_DEBUG_INFO
		#include <d3d9.h>
		#include <dxerr.h>
#endif 

#endif 


#if defined(__DAVAENGINE_OPENGL__)
#include "Render/OGLHelpers.h"
#elif defined(__DAVAENGINE_DIRECTX9__)
#include "Render/D3D9Helpers.h"
#endif 


namespace DAVA
{

enum eBlendMode
{
	BLEND_NONE = 0,				// blend mode not defined
	BLEND_ZERO,
	BLEND_ONE,
	BLEND_DST_COLOR,
	BLEND_ONE_MINUS_DST_COLOR,
	BLEND_SRC_ALPHA,
	BLEND_ONE_MINUS_SRC_ALPHA,
	BLEND_DST_ALPHA,
	BLEND_ONE_MINUS_DST_ALPHA,
	BLEND_SRC_ALPHA_SATURATE,

	BLEND_MODE_COUNT,
};

#if defined(__DAVAENGINE_OPENGL__)
static const GLint BLEND_MODE_MAP[BLEND_MODE_COUNT] = 
{
    0,	// not a valid blend mode
    GL_ZERO,
    GL_ONE,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_SRC_ALPHA_SATURATE,
};
#elif defined(__DAVAENGINE_DIRECTX9__)
static const GLint BLEND_MODE_MAP[BLEND_MODE_COUNT] = 
{
    0,	// not a valid blend mode
    D3DBLEND_ZERO,
    D3DBLEND_ONE,
    D3DBLEND_DESTCOLOR,
    D3DBLEND_INVDESTCOLOR,
    D3DBLEND_SRCALPHA,
    D3DBLEND_INVSRCALPHA,
    D3DBLEND_DESTALPHA,
    D3DBLEND_INVDESTALPHA,
    D3DBLEND_SRCALPHASAT,
};
#endif
  
enum eCmpFunc
{
    CMP_NEVER = 0,   // Never passes.
    CMP_LESS,    // Passes if the incoming alpha value is less than the reference value.
    CMP_EQUAL,   // Passes if the incoming alpha value is equal to the reference value.
    CMP_LEQUAL,  // Passes if the incoming alpha value is less than or equal to the reference value.
    CMP_GREATER, // Passes if the incoming alpha value is greater than the reference value.
    CMP_NOTEQUAL, // Passes if the incoming alpha value is not equal to the reference value.
    CMP_GEQUAL,   // Passes if the incoming alpha value is greater than or equal to the reference value.
    CMP_ALWAYS,
    CMP_TEST_MODE_COUNT, 
};
    
#if defined(__DAVAENGINE_OPENGL__)
static const GLint ALPHA_TEST_MODE_MAP[CMP_TEST_MODE_COUNT] = 
{
    GL_NEVER,
    GL_LESS,
    GL_EQUAL,
    GL_LEQUAL,
    GL_GREATER,
    GL_NOTEQUAL,
    GL_GEQUAL,
    GL_ALWAYS,
};
#elif defined(__DAVAENGINE_DIRECTX9__)  
static const GLint ALPHA_TEST_MODE_MAP[CMP_TEST_MODE_COUNT] = 
{
    D3DCMP_NEVER,
    D3DCMP_LESS,
    D3DCMP_EQUAL,
    D3DCMP_LESSEQUAL,
    D3DCMP_GREATER,
    D3DCMP_NOTEQUAL,
    D3DCMP_GREATEREQUAL,
    D3DCMP_ALWAYS,
};  
#endif
    
enum eVertexDataType
{
	TYPE_FLOAT = 0,
	//TYPE_FIXED,

	TYPE_COUNT
};
    
#if defined(__DAVAENGINE_OPENGL__)
    static const GLint VERTEX_DATA_TYPE_TO_GL[TYPE_COUNT] = {GL_FLOAT};
#endif
    
enum eIndexDataType
{
    TYPE_UNSIGNED_SHORT = 0,
};

#if defined(__DAVAENGINE_OPENGL__)
    static const GLint INDEX_DATA_TYPE_TO_GL[TYPE_COUNT] = {GL_UNSIGNED_SHORT};
#endif

enum eIndexFormat
{
	EIF_16 = 0x0,
	EIF_32 = 0x1,
};
    
enum eCull
{
    CULL_FRONT = 0,
    CULL_BACK,
    CULL_FRONT_AND_BACK,
    CULL_COUNT,
};
    
#if defined(__DAVAENGINE_OPENGL__)
    static const GLint CULL_FACE_MAP[CULL_COUNT] = 
    {
        GL_FRONT,
        GL_BACK,
        GL_FRONT_AND_BACK,
    };
#elif defined(__DAVAENGINE_DIRECTX9__) 
//    static const int32 CULL_FACE_MAP[CULL_COUNT] = 
//    {
//        CULL
//    }
#endif
    
enum ePrimitiveType
{
	PRIMITIVETYPE_POINTLIST = 0,
	PRIMITIVETYPE_LINELIST,
	PRIMITIVETYPE_LINESTRIP,
	PRIMITIVETYPE_TRIANGLELIST,
	PRIMITIVETYPE_TRIANGLESTRIP,
	PRIMITIVETYPE_TRIANGLEFAN,

	PRIMITIVETYPE_COUNT
};
    
// TODO: we have same structs & functions in PolygonGroup -- we should find a right place for them
enum eVertexFormat
{
    EVF_VERTEX			= 1,
    EVF_NORMAL			= 2,
    EVF_COLOR			= 4,
    EVF_TEXCOORD0		= 8,
    EVF_TEXCOORD1		= 16,
    EVF_TEXCOORD2		= 32,
    EVF_TEXCOORD3		= 64,
    EVF_TANGENT			= 128,
    EVF_BINORMAL		= 256,
    EVF_JOINTWEIGHT		= 512,
    EVF_LOWER_BIT		= EVF_VERTEX,
    EVF_HIGHER_BIT		= EVF_JOINTWEIGHT, 
    EVF_NEXT_AFTER_HIGHER_BIT
    = (EVF_HIGHER_BIT << 1),
    EVF_FORCE_DWORD     = 0x7fffffff,
};
enum
{
    VERTEX_FORMAT_STREAM_MAX_COUNT = 10
};
    
inline int32 GetVertexSize(int32 flags)
{
    int32 size = 0;
    if (flags & EVF_VERTEX) size += 3 * sizeof(float32);
    if (flags & EVF_NORMAL) size += 3 * sizeof(float32);
    if (flags & EVF_COLOR) size += 4;
    if (flags & EVF_TEXCOORD0) size += 2 * sizeof(float32);
    if (flags & EVF_TEXCOORD1) size += 2 * sizeof(float32);
    if (flags & EVF_TEXCOORD2) size += 2 * sizeof(float32);
    if (flags & EVF_TEXCOORD3) size += 2 * sizeof(float32);
    if (flags & EVF_TANGENT) size += 3 * sizeof(float32);
    if (flags & EVF_BINORMAL) size += 3 * sizeof(float32);
    
    if (flags & EVF_JOINTWEIGHT) size += 2 * sizeof(float32); // 4 * 3 + 4 * 3= 12 + 12 
    return size;
}


class RenderGuard
{
public:	
	RenderGuard();
	~RenderGuard();
	
	void LowLevelRenderCall();
	
	bool wrongCall;
};
	
};

#if defined(__DAVAENGINE_DEBUG__)
#define RENDER_GUARD RenderGuard renderGuard;
#else
#define RENDER_GUARD
#endif




#endif // __DAVAENGINE_RENDER_BASE_H__