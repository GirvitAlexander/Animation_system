/* FILE NAME: RNDSHD.C
 * PROGRAMMER: AG6
 * DATE: 23.01.2019
 * PURPOSE:.
 */

#include <stdio.h>
#include "rndres.h"

/* Shader resource table and size */
ag6SHADER AG6_RndShaders[AG6_RESOURCE_TABLE_SIZE];
int AG6_RndShadersSize;

/* Save text to log file function.
 * ARGUMENTS:
 *   - shader file name:
 *       char *FileName;
 *   - text 1 to save:
 *       char *Stage;
 *   - text 2 to save:
 *       char *Text;
 * RETURNS: None.
 */
static VOID AG6_RndShaderLog( char *FileName, char *Stage, char *Text )
{
  FILE *F;

  if ((F = fopen("AG6{SHAD}30.LOG", "a")) != NULL)
  {
    fprintf(F, "%s\n  %s: %s\n", FileName, Stage, Text);
    fclose(F);
  }
} /* End of 'AG6_RndShaderLog' function */

/* Text file load to memory function.
 * ARGUMENTS:
 *   - file name:
 *       char *FileName;
 * RETURNS:
 *   (char *) load text or NULL if error is occured.
 */
static char * AG6_RndShaderLoadTextFile( char *FileName )
{
  FILE *F;
  int flen;
  char *text;

  if ((F = fopen(FileName, "r")) == NULL)
    return NULL;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((text = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(text, 0, flen + 1);

  /* Read text */
  fseek(F, 0, SEEK_SET);
  fread(text, 1, flen, F);

  fclose(F);
  return text;
} /* End of 'AG6_RndShaderLoadTextFile' function */

/* Load shader program function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       char *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT AG6_RndShaderLoad( char *FileNamePrefix )
{
  int
    i, res,
    shd_type[] =
    {
      GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER,
      GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
    };
  char *suff[] = {"VERT", "CTRL", "EVAL", "GEOM", "FRAG"};
  int NS = sizeof(suff) / sizeof(suff[0]);
  UINT prg = 0, shd[sizeof(suff) / sizeof(suff[0])] = {0};
  int isok = TRUE;
  char *txt;
  static char buf[500];

  /* Load shaders */
  for (i = 0; isok && i < NS; i++)
  {
    /* Load text file */
    sprintf(buf, "%s\\%s.GLSL", FileNamePrefix, suff[i]);
    if ((txt = AG6_RndShaderLoadTextFile(buf)) == NULL)
      continue;
    /* Create shader */
    if ((shd[i] = glCreateShader(shd_type[i])) == 0)
    {
      free(txt);
      AG6_RndShaderLog(FileNamePrefix, suff[i], "Error create shader");
      isok = FALSE;
      break;
    }
    /* Attach text to shader  */
    glShaderSource(shd[i], 1, &txt, NULL);
    free(txt);

    /* Compile shader */
    glCompileShader(shd[i]);
    glGetShaderiv(shd[i], GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i], sizeof(buf), &res, buf);
      AG6_RndShaderLog(FileNamePrefix, suff[i], buf);
      isok = FALSE;
      break;
    }
  }

  /* Create program */
  if (isok)
    if ((prg = glCreateProgram()) == 0)
      isok = FALSE;
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NS; i++)
        if (shd[i] != 0)
          glAttachShader(prg, shd[i]);

      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(buf), &res, buf);
        AG6_RndShaderLog(FileNamePrefix, "LINK", buf);
        isok = FALSE;
      }
    }

  /* Error handle */
  if (!isok)
  {
    for (i = 0; i < NS; i++)
      if (shd[i] != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i]);
        glDeleteShader(shd[i]);
      }
    if (prg != 0)
      glDeleteProgram(prg);
    return 0;
  }
  return prg;
} /* End of 'AG6_RndShaderLoad' function */

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program Id:
 *       UINT Prg;
 * RETURNS: None.
 */
VOID AG6_RndShaderFree( UINT Prg )
{
  UINT i, n, shds[5];

  if (Prg == 0)
    return;
  /* Obtain program shaders count */
  glGetAttachedShaders(Prg, 5, &n, shds);
  for (i = 0; i < n; i++)
  {
    glDetachShader(Prg, shds[i]);
    glDeleteShader(shds[i]);
  }
  glDeleteProgram(Prg);
} /* End of 'AG6_RndShaderFree' function */

/* Add shader program from file function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       char *FileNamePrefix;
 * RETURNS:
 *   (int) shader table index or -1 if error is occured.
 */
int AG6_RndShaderAdd( char *FileNamePrefix )
{
  int i;
  static char Buf[1000];

  /* Look for exists shader */
  for (i = 0; i < AG6_RndShadersSize; i++)
    if (strcmp(AG6_RndShaders[i].Name, FileNamePrefix) == 0)
      return i;

  if (i >= AG6_RESOURCE_TABLE_SIZE)
    return -1;

  sprintf(Buf, "BIN/SHADERS/%s", FileNamePrefix);
  AG6_RndShaders[AG6_RndShadersSize].PrgNo = AG6_RndShaderLoad(Buf);
  strncpy(AG6_RndShaders[AG6_RndShadersSize].Name, FileNamePrefix, AG6_MATERIAL_NAME_SIZE - 1);
  return AG6_RndShadersSize++;
} /* End of 'AG6_RndShaderAdd' function */

/* Update all shaders from store table function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AG6_RndShadersUpdate( VOID )
{
  int i;
  static char Buf[1000];

  for (i = 0; i < AG6_RndShadersSize; i++)
  {
    AG6_RndShaderFree(AG6_RndShaders[i].PrgNo);
    sprintf(Buf, "BIN/SHADERS/%s", AG6_RndShaders[i].Name);
    AG6_RndShaders[i].PrgNo = AG6_RndShaderLoad(Buf);
  }
} /* End of 'AG6_RndShadersUpdate' function */

/* Remove shader program from resource table function.
 * ARGUMENTS:
 *   - shader table index:
 *       int ShdNo;
 * RETURNS: None.
 */
VOID AG6_RndShaderDelete( int ShdNo )
{
  if (ShdNo < 0 || ShdNo >= AG6_RndShadersSize)
    return;
  AG6_RndShaderFree(AG6_RndShaders[ShdNo].PrgNo);
  memset(&AG6_RndShaders[ShdNo], 0, sizeof(ag6SHADER));
} /* End of 'AG6_RndShaderDelete' function */

/* END OF 'RNDSHD.C' FILE */
