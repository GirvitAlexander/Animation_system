/* FILE NAME: RNDRES.H
 * PROGRAMMER: AG6
 * DATE: 23.01.2019
 * PURPOSE:.
 */

#include "def.h"
#include "rnd.h"

/* Maximum material name size */
#define AG6_MATERIAL_NAME_SIZE  300

/* Maximum resource tables size */
#define AG6_RESOURCE_TABLE_SIZE 3000

/* Rendering resource initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AG6_RndResInit( VOID );

/* Rendering resource deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AG6_RndResClose( VOID );

/***
 * Shader handle function group
 ***/

/* Shader store representation type */
typedef struct tagag6SHADER
{
  char Name[AG6_MATERIAL_NAME_SIZE]; /* Shader path prefix name */
  UINT PrgNo;                        /* OpenGL shader program Id */
} ag6SHADER;

/* Shader resource table and size */
extern ag6SHADER AG6_RndShaders[AG6_RESOURCE_TABLE_SIZE];
extern int AG6_RndShadersSize;

/* Load shader program function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       char *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT AG6_RndShaderLoad( char *FileNamePrefix );

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program Id:
 *       UINT Prg;
 * RETURNS: None.
 */
VOID AG6_RndShaderFree( UINT Prg );

/* Add shader program from file function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       char *FileNamePrefix;
 * RETURNS:
 *   (int) shader table index or -1 if error is occured.
 */
int AG6_RndShaderAdd( char *FileNamePrefix );

/* Update all shaders from store table function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AG6_RndShadersUpdate( VOID );

/* Remove shader program from resource table function.
 * ARGUMENTS:
 *   - shader table index:
 *       int ShdNo;
 * RETURNS: None.
 */
VOID AG6_RndShaderDelete( int ShdNo );

/***
 * Texture handle function group
 ***/

/* Texture store representation type */
typedef struct tagag6TEXTURE
{
  char Name[AG6_MATERIAL_NAME_SIZE]; /* Image file name */
  int W, H;                          /* Texture size in pixels */
  UINT TexId;                        /* OpenGL texture Id */
} ag6TEXTURE;

/* Texture resource table and size */
extern ag6TEXTURE AG6_RndTextures[AG6_RESOURCE_TABLE_SIZE];
extern int AG6_RndTexturesSize;

/* Add texture image from file function.
 * ARGUMENTS:
 *   - texture image file name:
 *       char *FileName;
 * RETURNS:
 *   (int) texture table index or -1 if error is occured.
 */
int AG6_RndTextureAddFromFile( char *FileName );

/* Add texture image from file function.
 * ARGUMENTS:
 *   - texture image file name:
 *       char *FileName;
 * RETURNS:
 *   (int) texture table index or -1 if error is occured.
 */
int AG6_RndTextureAddFromFileg24( char *FileName );

/* Add texture image by image data function.
 * ARGUMENTS:
 *   - texture name:
 *       char *Name;
 *   - texture image size:
 *       int W, H;
 *   - texture image pixel color data (unsigned long int colors):
 *       VOID *ImageData;
 * RETURNS:
 *   (int) texture table index or -1 if error is occured.
 */
int AG6_RndTextureAdd( char *Name, int W, int H, VOID *ImageData );

/* Remove texture from resource table function.
 * ARGUMENTS:
 *   - texture table index:
 *       int TexNo;
 * RETURNS: None.
 */
VOID AG6_RndTextureDelete( int TexNo );

/***
 * Material handle function group
 ***/

/* Material store representation type */
typedef struct tagag6MATERIAL
{
  char Name[AG6_MATERIAL_NAME_SIZE]; /* Material name */

  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;                    /* Ambient, diffuse, specular coefficients */
  FLT Ph;                            /* Phong power coefficient */
  FLT Trans;                         /* Transparency factor */
  int Tex[8];                        /* Texture references from texture table */
  int ShdNo;                         /* Shader reference in shader table */
} ag6MATERIAL;

/* Material resource table and size */
extern ag6MATERIAL AG6_RndMaterials[AG6_RESOURCE_TABLE_SIZE];
extern int AG6_RndMaterialsSize;

/* Add material function.
 * ARGUMENTS:
 *   - material data structure pointer:
 *       ag6MATERIAL *Mtl;
 * RETURNS:
 *   (int) material table index or -1 if error is occured.
 */
int AG6_RndMaterialAdd( ag6MATERIAL *Mtl );

/* Material apply function.
 * ARGUMENTS:
 *   - material table index:
 *       int MtlNo;
 * RETURNS:
 *   (UINT) apply result shader program identifier.
 */
UINT AG6_RndMaterialApply( int MtlNo );

/***
 * Object (primitive collection) handle
 ***/

/* Object representation type */
typedef struct tagag6OBJ
{
  ag6PRIM *Prims; /* Primitive array */
  int NumOfPrims; /* Number of object primitives */
  MATR Trans;
} ag6OBJ;

/* Create object function.
 * ARGUMENTS:
 *   - object structure:
 *       ag6OBJ *Obj;
 *   - primitives count:
 *       int NumOfPrims;
 * RETUNRS:
 *   (int) TRUE if successful, FALSE otherwise.
 */
int AG6_RndObjCreate( ag6OBJ *Obj, int NumOfPrims );

/* Free object function.
 * ARGUMENTS:
 *   - object structure:
 *       ag6OBJ *Obj;
 * RETUNRS: None.
 */
VOID AG6_RndObjFree( ag6OBJ *Obj );

/* Load object from CGSG '.G3DM' file function.
 * ARGUMENTS:
 *   - object structure:
 *       ag6OBJ *Obj;
 *   - file name:
 *       char *FileName;
 * RETUNRS:
 *   (int) TRUE if successful, FALSE otherwise.
 */
int AG6_RndObjLoad( ag6OBJ *Obj, char *FileName );

/* Draw object function.
 * ARGUMENTS:
 *   - object structure:
 *       ag6OBJ *Obj;
 *   - object all primitives transformation matrix:
 *       MATR World;
 * RETUNRS: None.
 */
VOID AG6_RndObjDraw( ag6OBJ *Obj, MATR World );

/***
 * GRID handle function group
 ***/

typedef struct tagag6GRID
{
  int W, H;
  ag6VERTEX *V;
} ag6GRID;

/* Image representation type */
typedef struct tagag6IMAGE
{
  int W, H;             /* Image size in pixels */
  unsigned long int *Pixels;        /* All image pixels array */
  unsigned long int **Rows;         /* All image pixels rows */
  unsigned char (**RowsARGB)[4]; /* All image pixels rows with BGRA color component access */
} ag6IMAGE;

VOID AG6_RndGridFree( ag6GRID *G );
int AG6_RndGridCreate( ag6GRID *G, int W, int H );
VOID AG6_RndPrimFromGrid( ag6PRIM *Pr, ag6GRID *G );
VOID AG6_RndGridEvalNormals( ag6GRID *G );
int AG6_RndGridCreateSphere( ag6GRID * G, int W, int H, VEC C, FLT R, FLT R2 );

/* END OF 'RNDRES.H' FILE */