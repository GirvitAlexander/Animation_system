/* FILE NAME: RNDSHD.C
 * PROGRAMMER: AG6
 * DATE: 01.03.2019
 * PURPOSE: FBO.
 */

#include "rnd.h"
#include "rndres.h"
#include "anim.h"

#define AG6_RND_TRG_NUM_OF_ATTACHMENTS 3

static UINT AG6_RndTrgFBO;
static UINT AG6_RndTrgTexAttachment[AG6_RND_TRG_NUM_OF_ATTACHMENTS];
static UINT AG6_RndTrgRBuf;
static ag6PRIM AG6_RndTrgPrim;

/* Inite function
 * ARGUMENTS:
 *  None.
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgInit( VOID )
{
  int i;
  ag6VERTEX V = {{0}};
  int I;
  ag6MATERIAL mtl =
  {
    "Target material",
    {0.1, 0.1, 0.1}, {1, 1, 1}, {0, 0, 0}, 1,
    1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };
  
  AG6_RndPrimCreate(&AG6_RndTrgPrim, AG6_PRIM_POINTS, &V, 1, NULL, 0);

  for (i = 0; i < AG6_RND_TRG_NUM_OF_ATTACHMENTS; i++)
  {
    unsigned long int Dummy;

    AG6_RndTrgTexAttachment[i] = AG6_RndTextureAdd("Target", 1, 1, &Dummy);
    mtl.Tex[i] = AG6_RndTrgTexAttachment[i];
  }
  AG6_RndTrgCreate(AG6_RndFrameW, AG6_RndFrameH);
  mtl.ShdNo = AG6_RndShaderAdd("RENDER_TARGET_END");
  AG6_RndTrgPrim.MtNo = AG6_RndMaterialAdd(&mtl);
} /* End of 'AG6_RndTrgInit' function */

/* Resize init function
 * ARGUMENTS:
 *   - window
 *     HWND hWnd;
 *   - 
 *   LONG loWord;
 *   - 
 *   LONG hiWord;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgResize( int W, int H )
{
  AG6_RndTrgFree();
  AG6_RndTrgCreate(W, H);
} /* End of 'AG6_RndTrgResize' function */

/* Start function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgStart( VOID )
{
  glBindFramebuffer(GL_FRAMEBUFFER, AG6_RndTrgFBO);
  glClearColor(0.3, 0.5, 0.7, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'AG6_RndTrgStart' function */

/* Create function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgCreate( int W, int H )
{
  int i, w, h;
  UINT DrawBuffers[AG6_RND_TRG_NUM_OF_ATTACHMENTS];

  glGenFramebuffers(1, &AG6_RndTrgFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, AG6_RndTrgFBO);

  for (i = 0; i < AG6_RND_TRG_NUM_OF_ATTACHMENTS; i++)
  {
    int no = AG6_RndTrgTexAttachment[i];

    DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    if (AG6_RndTextures[no].TexId != 0)
      glDeleteTextures(1, &AG6_RndTextures[no].TexId);
    glGenTextures(1, &AG6_RndTextures[no].TexId);
    glBindTexture(GL_TEXTURE_2D, AG6_RndTextures[no].TexId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, W, H);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
      GL_TEXTURE_2D, AG6_RndTextures[no].TexId, 0);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);   
  }
  glDrawBuffers(AG6_RND_TRG_NUM_OF_ATTACHMENTS, DrawBuffers);

  glGenRenderbuffers(1, &AG6_RndTrgRBuf);
  glBindRenderbuffer(GL_RENDERBUFFER, AG6_RndTrgRBuf);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, W, H);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, AG6_RndTrgRBuf);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
} /* End of 'AG6_RndTrgCreate' function */

/* End function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgEnd( VOID )
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(0.3, 0.5, 0.7, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (AG6_Anim.IsWireFrame)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  AG6_RndPrimDraw(&AG6_RndTrgPrim, MatrIdentity());
  if (AG6_Anim.IsWireFrame)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glFinish();
} /* End of 'AG6_RndTrgEnd' function */

/* Closing function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgClose( VOID )
{
  AG6_RndPrimFree(&AG6_RndTrgPrim);
  AG6_RndTrgFree();
} /* End of 'AG6_RndTrgClose' function */

/* Free function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgFree( VOID )
{
  int i;

  glBindFramebuffer(GL_FRAMEBUFFER, AG6_RndTrgFBO);
  for (i = 0; i < AG6_RND_TRG_NUM_OF_ATTACHMENTS; i++)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, 0, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
  glDeleteRenderbuffers(1, &AG6_RndTrgRBuf);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDeleteFramebuffers(1, &AG6_RndTrgFBO);
} /* End of 'AG6_RndTrgFree' function */


/* END OF 'RNDTRG.C' FILE */