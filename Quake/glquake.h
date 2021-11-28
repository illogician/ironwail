/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2007-2008 Kristian Duske
Copyright (C) 2010-2014 QuakeSpasm developers

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef GLQUAKE_H
#define GLQUAKE_H

void GL_BeginRendering (int *x, int *y, int *width, int *height);
void GL_EndRendering (void);
void GL_Set2D (void);

extern	int glx, gly, glwidth, glheight;

#define	GL_UNUSED_TEXTURE	(~(GLuint)0)

// r_local.h -- private refresh defs

#define ALIAS_BASE_SIZE_RATIO		(1.0 / 11.0)
					// normalizing factor so player model works out to about
					//  1 pixel per triangle
#define	MAX_LBM_HEIGHT		480

#define BACKFACE_EPSILON	0.01

void R_TimeRefresh_f (void);
void R_ReadPointFile_f (void);
texture_t *R_TextureAnimation (texture_t *base, int frame);

typedef enum {
	pt_static, pt_grav, pt_slowgrav, pt_fire, pt_explode, pt_explode2, pt_blob, pt_blob2
} ptype_t;

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
typedef struct particle_s
{
// driver-usable fields
	vec3_t		org;
	float		color;
// drivers never touch the following fields
	struct particle_s	*next;
	vec3_t		vel;
	float		ramp;
	float		die;
	ptype_t		type;
} particle_t;


//====================================================

extern	qboolean	r_cache_thrash;		// compatability
extern	vec3_t		modelorg, r_entorigin;
extern	int		r_visframecount;	// ??? what difs?
extern	int		r_framecount;
extern	mplane_t	frustum[4];

extern	qboolean use_simd;

//
// view origin
//
extern	vec3_t	vup;
extern	vec3_t	vpn;
extern	vec3_t	vright;
extern	vec3_t	r_origin;

//
// screen size info
//
extern	refdef_t	r_refdef;
extern	mleaf_t		*r_viewleaf, *r_oldviewleaf;
extern	int		d_lightstylevalue[256];	// 8.8 fraction of base light value

extern	cvar_t	r_norefresh;
extern	cvar_t	r_drawentities;
extern	cvar_t	r_drawworld;
extern	cvar_t	r_drawviewmodel;
extern	cvar_t	r_speeds;
extern	cvar_t	r_pos;
extern	cvar_t	r_waterwarp;
extern	cvar_t	r_fullbright;
extern	cvar_t	r_lightmap;
extern	cvar_t	r_shadows;
extern	cvar_t	r_wateralpha;
extern	cvar_t	r_lavaalpha;
extern	cvar_t	r_telealpha;
extern	cvar_t	r_slimealpha;
extern	cvar_t	r_dynamic;
extern	cvar_t	r_novis;
extern	cvar_t	r_scale;

extern	cvar_t	gl_clear;
extern	cvar_t	gl_polyblend;
extern	cvar_t	gl_nocolors;

extern	cvar_t	gl_playermip;

extern int		gl_stencilbits;
extern	qboolean	gl_bindless_able;
extern	qboolean	gl_clipcontrol_able;

//==============================================================================

#define QGL_CORE_FUNCTIONS(x)\
	x(void,			DrawElementsInstanced, (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount))\
	x(void,			DrawElementsIndirect, (GLenum mode, GLenum type, const void *indirect))\
	x(void,			MultiDrawElementsIndirect, (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride))\
	x(void,			GenBuffers, (GLsizei n, GLuint *buffers))\
	x(void,			DeleteBuffers, (GLsizei n, const GLuint *buffers))\
	x(void,			BindBuffer, (GLenum target, GLuint buffer))\
	x(void,			BindBufferRange, (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size))\
	x(void,			BufferData, (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage))\
	x(void,			BufferSubData, (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data))\
	x(GLvoid*,		MapBuffer, (GLenum target, GLenum access))\
	x(GLboolean,	UnmapBuffer, (GLenum target))\
	x(void*,		MapBufferRange, (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access))\
	x(void,			FlushMappedBufferRange, (GLenum target, GLintptr offset, GLsizeiptr length))\
	x(void,			BufferStorage, (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags))\
	x(GLsync,		FenceSync, (GLenum condition, GLbitfield flags))\
	x(void,			DeleteSync, (GLsync sync))\
	x(GLenum,		ClientWaitSync, (GLsync sync, GLbitfield flags, GLuint64 timeout))\
	x(void,			WaitSync, (GLsync sync, GLbitfield flags, GLuint64 timeout))\
	x(GLuint,		CreateProgram, (void))\
	x(void,			DeleteProgram, (GLuint program))\
	x(void,			GetProgramiv, (GLuint program, GLenum pname, GLint *params))\
	x(void,			UseProgram, (GLuint program))\
	x(void,			LinkProgram, (GLuint program))\
	x(void,			GetProgramInfoLog, (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog))\
	x(GLuint,		CreateShader, (GLenum type))\
	x(void,			DeleteShader, (GLuint shader))\
	x(void,			ShaderSource, (GLuint shader, GLsizei count, const GLchar* const *string, const GLint *length))\
	x(void,			CompileShader, (GLuint shader))\
	x(void,			GetShaderInfoLog, (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog))\
	x(void,			GetShaderiv, (GLuint shader, GLenum pname, GLint *params))\
	x(void,			AttachShader, (GLuint program, GLuint shader))\
	x(void,			DetachShader, (GLuint program, GLuint shader))\
	x(void,			BindAttribLocation, (GLuint program, GLuint index, const GLchar *name))\
	x(void,			BindVertexArray, (GLuint array))\
	x(void,			GenVertexArrays, (GLsizei n, GLuint *arrays))\
	x(void,			EnableVertexAttribArray, (GLuint index))\
	x(void,			DisableVertexAttribArray, (GLuint index))\
	x(void,			VertexAttribPointer, (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer))\
	x(GLint,		GetUniformLocation, (GLuint program, const GLchar *name))\
	x(void,			GetActiveUniform, (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name))\
	x(void,			Uniform1i, (GLint location, GLint v0))\
	x(void,			Uniform1f, (GLint location, GLfloat v0))\
	x(void,			Uniform2f, (GLint location, GLfloat v0, GLfloat v1))\
	x(void,			Uniform3f, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2))\
	x(void,			Uniform4f, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3))\
	x(void,			Uniform3fv, (GLint location, GLsizei count, const GLfloat *value))\
	x(void,			Uniform4fv, (GLint location, GLsizei count, const GLfloat *value))\
	x(void,			UniformMatrix4fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))\
	x(void,			ActiveTexture, (GLenum texture))\
	x(void,			GenerateMipmap, (GLenum target))\
	x(void,			BindFramebuffer, (GLenum target, GLuint framebuffer))\
	x(void,			GenFramebuffers, (GLsizei n, GLuint *framebuffers))\
	x(void,			DeleteFramebuffers, (GLsizei n, const GLuint *framebuffers))\
	x(void,			FramebufferTexture2D, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))\
	x(GLenum,		CheckFramebufferStatus, (GLenum target))\
	x(void,			BlitFramebuffer, (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter))\
	x(void,			DebugMessageCallback, (GLDEBUGPROC callback, const void *userParam))\
	x(void,			ObjectLabel, (GLenum identifier, GLuint name, GLsizei length, const GLchar *label))\
	x(void,			PushDebugGroup, (GLenum source, GLuint id, GLsizei length, const char * message))\
	x(void,			PopDebugGroup, (void))\
	x(const GLubyte*,GetStringi, (GLenum name, GLuint index))\
	x(void,			TexStorage2D, (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height))\
	x(void,			TexStorage3D, (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth))\
	x(void,			TexStorage2DMultisample, (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations))\
	x(void,			TexImage3D, (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels))\
	x(void,			TexSubImage3D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels))\
	x(void,			BindTextures, (GLuint first, GLsizei count, const GLuint *textures))\
	x(void,			BindImageTexture, (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format))\
	x(void,			MemoryBarrier, (GLbitfield barriers))\
	x(void,			DispatchCompute, (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z))\
	x(void,			GenSamplers, (GLsizei n, GLuint *samplers))\
	x(void,			DeleteSamplers, (GLsizei n, const GLuint *samplers))\
	x(void,			SamplerParameteri, (GLuint sampler, GLenum pname, GLint param))\
	x(void,			SamplerParameterf, (GLuint sampler, GLenum pname, GLfloat param))\
	x(void,			BindSampler, (GLuint unit, GLuint sampler))\

#define QGL_ARB_bindless_texture_FUNCTIONS(x)\
	x(GLuint64,		GetTextureHandleARB, (GLuint texture))\
	x(GLuint64,		GetTextureSamplerHandleARB, (GLuint texture, GLuint sampler))\
	x(void,			MakeTextureHandleResidentARB, (GLuint64 handle))\
	x(void,			MakeTextureHandleNonResidentARB, (GLuint64 handle))\

#define QGL_ARB_clip_control_FUNCTIONS(x)\
	x(void,			ClipControl, (GLenum origin, GLenum depth))\

#define GL_ZERO_TO_ONE		0x935F

#define QGL_ALL_FUNCTIONS(x)\
	QGL_CORE_FUNCTIONS(x)\
	QGL_ARB_bindless_texture_FUNCTIONS(x)\
	QGL_ARB_clip_control_FUNCTIONS(x)\

#define QGL_DECLARE_FUNC(ret, name, args) extern ret (APIENTRYP GL_##name##Func) args;
QGL_ALL_FUNCTIONS(QGL_DECLARE_FUNC)
#undef QGL_DECLARE_FUNC

void GL_BeginGroup (const char *name);
void GL_EndGroup (void);

//==============================================================================

typedef enum {
	GLS_NO_ZTEST		= 1 << 0,
	GLS_NO_ZWRITE		= 1 << 1,
	
	GLS_BLEND_OPAQUE	= 0 << 2,
	GLS_BLEND_ALPHA		= 1 << 2,
	GLS_BLEND_ADD		= 2 << 2,
	GLS_MASK_BLEND		= 3 << 2,

	GLS_CULL_BACK		= 0 << 4,
	GLS_CULL_NONE		= 1 << 4,
	GLS_CULL_FRONT		= 2 << 4,
	GLS_MASK_CULL		= 3 << 4,

	GLS_ATTRIB0			= 1 << 6,
	GLS_ATTRIB1			= 1 << 7,
	GLS_ATTRIB2			= 1 << 8,
	GLS_ATTRIB3			= 1 << 9,
	GLS_ATTRIB4			= 1 << 10,
	GLS_MAX_ATTRIBS		= 5,
	GLS_MASK_ATTRIBS	= ((1 << GLS_MAX_ATTRIBS) - 1) * GLS_ATTRIB0,

	GLS_DEFAULT_STATE	= GLS_BLEND_OPAQUE | GLS_CULL_BACK | GLS_ATTRIB0,
} glstatebits_t;

#define GLS_ATTRIBS(n)	(((1 << (n)) - 1) * GLS_ATTRIB0)

extern unsigned glstate;
void GL_SetState (unsigned mask);
void GL_ResetState (void);

extern GLint ssbo_align; // SSBO alignment - 1

//johnfitz -- anisotropic filtering
#define	GL_TEXTURE_MAX_ANISOTROPY_EXT		0x84FE
#define	GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT	0x84FF
extern	float		gl_max_anisotropy;
extern	qboolean	gl_anisotropy_able;

//johnfitz -- polygon offset
#define OFFSET_BMODEL 1
#define OFFSET_NONE 0
#define OFFSET_DECAL -1
#define OFFSET_FOG -2
#define OFFSET_SHOWTRIS -3
void GL_PolygonOffset (int);

typedef enum {
	ZRANGE_FULL,
	ZRANGE_VIEWMODEL,
	ZRANGE_NEAR,
} zrange_t;
void GL_DepthRange (zrange_t range);

//johnfitz -- rendering statistics
extern int rs_brushpolys, rs_aliaspolys, rs_skypolys, rs_particles, rs_fogpolys;
extern int rs_dynamiclightmaps, rs_brushpasses, rs_aliaspasses, rs_skypasses;
extern float rs_megatexels;

//johnfitz -- track developer statistics that vary every frame
extern cvar_t devstats;
typedef struct {
	int		packetsize;
	int		edicts;
	int		visedicts;
	int		efrags;
	int		tempents;
	int		beams;
	int		dlights;
} devstats_t;
extern devstats_t dev_stats, dev_peakstats;

//ohnfitz -- reduce overflow warning spam
typedef struct {
	double	packetsize;
	double	efrags;
	double	beams;
	double	varstring;
} overflowtimes_t;
extern overflowtimes_t dev_overflows; //this stores the last time overflow messages were displayed, not the last time overflows occured
#define CONSOLE_RESPAM_TIME 3 // seconds between repeated warning messages

//johnfitz -- moved here from r_brush.c
extern int gl_lightmap_format, lightmap_bytes;

#define LMBLOCK_WIDTH	256	//FIXME: make dynamic. if we have a decent card there's no real reason not to use 4k or 16k (assuming there's no lightstyles/dynamics that need uploading...)
#define LMBLOCK_HEIGHT	256 //Alternatively, use texture arrays, which would avoid the need to switch textures as often.

typedef struct glRect_s {
	unsigned short l,t,w,h;
} glRect_t;
struct lightmap_s
{
	glpoly_t	*polys;
	int			xofs;
	int			yofs;
};
extern struct lightmap_s *lightmaps;
extern int lightmap_count;	//allocated lightmaps

extern qboolean r_fullbright_cheatsafe, r_lightmap_cheatsafe, r_drawworld_cheatsafe; //johnfitz

extern float	map_wateralpha, map_lavaalpha, map_telealpha, map_slimealpha; //ericw
extern float	map_fallbackalpha; //spike -- because we might want r_wateralpha to apply to teleporters while water itself wasn't watervised

//johnfitz -- fog functions called from outside gl_fog.c
void Fog_ParseServerMessage (void);
float *Fog_GetColor (void);
float Fog_GetDensity (void);
void Fog_EnableGFog (void);
void Fog_DisableGFog (void);
void Fog_SetupFrame (void);
void Fog_NewMap (void);
void Fog_Init (void);

extern float r_matview[16];
extern float r_matproj[16];
extern float r_matviewproj[16];

void R_NewGame (void);

#define LIGHT_TILES_X			32
#define LIGHT_TILES_Y			16
#define LIGHT_TILES_Z			32

typedef struct gpulight_s {
	float	pos[3];
	float	radius;
	float	color[3];
	float	minlight;
} gpulight_t;

typedef struct gpuframedata_s {
	struct {
		float	viewproj[16];
		float	lighstyles[MAX_LIGHTSTYLES];
		float	fogdata[4];
		vec3_t	eyepos;
		float	skyfog;
		float	time;
		float	zlogscale;
		float	zlogbias;
		int		numlights;
	} global;
	gpulight_t	lights[MAX_DLIGHTS];
} gpuframedata_t;

extern gpuframedata_t r_framedata;

void R_AnimateLight (void);
void R_MarkSurfaces (void);
qboolean R_CullBox (vec3_t emins, vec3_t emaxs);
void R_StoreEfrags (efrag_t **ppefrag);
qboolean R_CullModelForEntity (entity_t *e);
void R_EntityMatrix (float matrix[16], vec3_t origin, vec3_t angles);

void R_InitParticles (void);
void R_DrawParticles (void);
void R_DrawParticles_ShowTris (void);
void CL_RunParticles (void);
void R_ClearParticles (void);

void R_TranslatePlayerSkin (int playernum);
void R_TranslateNewPlayerSkin (int playernum); //johnfitz -- this handles cases when the actual texture changes

void R_UploadFrameData (void);

void R_DrawBrushModels (entity_t **ents, int count);
void R_DrawBrushModels_Water (entity_t **ents, int count, qboolean translucent);
void R_DrawBrushModels_SkyLayers (entity_t **ents, int count);
void R_DrawBrushModels_SkyCubemap (entity_t **ents, int count);
void R_DrawBrushModels_SkyStencil (entity_t **ents, int count);
void R_DrawAliasModels (entity_t **ents, int count);
void R_DrawSpriteModels (entity_t **ents, int count);
void R_DrawBrushModels_ShowTris (entity_t **ents, int count);
void R_DrawAliasModels_ShowTris (entity_t **ents, int count);
void R_DrawSpriteModels_ShowTris (entity_t **ents, int count);

entity_t **R_GetVisEntities (modtype_t type, qboolean translucent, int *outcount);

#define MAX_BMODEL_DRAWS		4096
#define MAX_BMODEL_INSTANCES	1024

typedef struct bmodel_draw_indirect_s {
	GLuint		count;
	GLuint		instanceCount;
	GLuint		firstIndex;
	GLuint		baseVertex;
	GLuint		baseInstance;
} bmodel_draw_indirect_t;

typedef struct bmodel_gpu_leaf_s {
	float		mins[3];
	float		maxs[3];
	GLuint		firstsurf;
	GLuint		surfcountsky; // bit 0=sky; bits 1..31=surfcount
} bmodel_gpu_leaf_t;

typedef struct bmodel_gpu_surf_s {
	vec4_t		plane;
	GLuint		framecount;
	GLuint		texnum;
	GLuint		numedges;
	GLuint		firstvert;
} bmodel_gpu_surf_t;

void GL_BuildLightmaps (void);

void GL_DeleteBModelBuffers (void);
void GL_BuildBModelVertexBuffer (void);
void GL_BuildBModelMarkBuffers (void);
void GLMesh_LoadVertexBuffers (void);
void GLMesh_DeleteVertexBuffers (void);

int R_LightPoint (vec3_t p, lightcache_t *cache);


typedef struct glprogs_s {
	/* 2d */
	GLuint		gui;
	GLuint		viewblend;
	GLuint		warpscale;
	GLuint		postprocess;

	/* 3d */
	GLuint		world[2][2];	// [bindless][alpha test]
	GLuint		water[2];		// [bindless]
	GLuint		skystencil[2];	// [bindless]
	GLuint		skylayers[2];	// [bindless]
	GLuint		skycubemap[2];	// [bindless]
	GLuint		skyboxside;
	GLuint		alias[2];		// [alpha test]
	GLuint		sprites;
	GLuint		particles;

	/* compute */
	GLuint		clear_indirect;
	GLuint		gather_indirect;
	GLuint		cull_mark;
	GLuint		cluster_lights;
} glprogs_t;

extern glprogs_t glprogs;

void GL_UseProgram (GLuint program);
void GL_ClearCachedProgram (void);
void GL_CreateShaders (void);
void GL_DeleteShaders (void);

typedef struct glframebufs_s {
	GLint			max_color_tex_samples;
	GLint			max_depth_tex_samples;
	GLint			max_samples; // lowest of max_color_tex_samples/max_depth_tex_samples

	struct {
		GLint		samples;
		GLuint		color_tex;
		GLuint		depth_stencil_tex;
		GLuint		fbo;
	}				scene;

	struct {
		GLuint		color_tex;
		GLuint		fbo;
	}				resolved_scene;

	struct {
		GLuint		color_tex;
		GLuint		fbo;
	}				composite;
} glframebufs_t;

extern glframebufs_t framebufs;

void GL_CreateFrameBuffers (void);
void GL_DeleteFrameBuffers (void);

void GLWorld_CreateResources (void);
void GLLight_CreateResources (void);
void GLLight_DeleteResources (void);

void GL_MakeAliasModelDisplayLists (qmodel_t *m, aliashdr_t *hdr);

void Sky_Init (void);
void Sky_ClearAll (void);
void Sky_DrawSky (void);
void Sky_NewMap (void);
void Sky_LoadTexture (texture_t *mt);
void Sky_LoadTextureQ64 (texture_t *mt);
void Sky_LoadSkyBox (const char *name);

void GL_BindBuffer (GLenum target, GLuint buffer);
void GL_BindBufferRange (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
void GL_DeleteBuffer (GLuint buffer);
void GL_ClearBufferBindings (void);

void GL_InitDynamicBuffers (void);
void GL_Upload (GLenum target, const void *data, size_t numbytes, GLuint *outbuf, GLbyte **outofs);
void GL_DynamicBuffersBeginFrame (void);
void GL_DynamicBuffersEndFrame (void);

void GLSLGamma_GammaCorrect (void);

float GL_WaterAlphaForTextureType (textype_t type);

#endif	/* GLQUAKE_H */
