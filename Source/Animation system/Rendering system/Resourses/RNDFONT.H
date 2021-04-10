/* FILE NAME: RNDFONT.H
 * PROGRAMMER: ag6
 * DATE: 01.02.2019
 * PURPOSE: 
 */

#ifndef __RNDFONT_H_
#define __RNDFONT_H_

#include "def.h"
#include "rndres.h"

/***
 * BMF Font handle types
 ***/

/* Common info: 
 *   Sinature (4 bytes): "BMF\3".
 * Set of blocks: 1 byte 'block Id (1-5) plus 4 bytes block size in bytes.
 */

#pragma pack(push, 1)

/* Block type 1: info.
* This structure gives the layout of the fields. Remember that there should
 * be no padding between members. Allocate the size of the block using the
 * blockSize, as following the block comes the font name, including the
 * terminating null char. Most of the time this block can simply be ignored. */
typedef struct tagag6FNTINFO
{
  unsigned short int FontSize;  /* Base letter height value */
  unsigned char BitField;  /* Info bits -
                   *   bit 0: smooth - set to 1 if smoothing was turned on,
                   *   bit 1: unicode - set to 1 if it is the unicode charset,
                   *   bit 2: italic - the font is italic,
                   *   bit 3: bold - the font is bold,
                   *   bit 4: fixedHeigth,
                   *   bits 5-7: reserved. */
  unsigned char CharSet;   /* The name of the OEM charset used (when not unicode, e.g. RUSSIAN_CHARSET - 204). */
  unsigned short int StretchH;  /* The font height stretch in percentage. 100% means no stretch. */
  unsigned char AntiAlias; /* The supersampling level used. 1 means no supersampling was used. */
  unsigned char            /* The padding for each character (up, right, down, left). */
    PaddingUp, PaddingRight, PaddingDown, PaddingLeft;
  unsigned char            /* The spacing for each character (horizontal, vertical). */
    SpacingHoriz, SpacingVert;
  unsigned char Outline;   /* The outline thickness for the characters in pixels */
  /* char FontName[]; - String - null terminated string */
} ag6FNTINFO; /* End of 'ag6FNTINFO' structure */

/* Block type 2: common */
typedef struct tagag6FNTCOMMON
{
  unsigned short int LineHeight; /* This is the distance in pixels between each line of text. */
  unsigned short int Base;     /* The number of pixels from the absolute top of the line to the base of the characters. */
  unsigned short int ScaleW;     /* The width of the texture, normally used to scale the x pos of the character image. */
  unsigned short int ScaleH;     /* The height of the texture, normally used to scale the y pos of the character image. */
  unsigned short int Pages;      /* The number of texture pages included in the font. */
  unsigned char BitField;   /* Info bits - bits 0-6: reserved,
                    *    bit 7: packed - set to 1 if the monochrome characters have been packed into each
                    *                    of the texture channels. In this case alphaChnl describes what
                    *                    is stored in each channel. */
  unsigned char
    /* By channels info:
     *   set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds
     *   the glyph and the outline, 3 if its set to zero, and 4 if its set to one. */
    AlphaChnll, RedChnl, GreenChnl, BlueChnl;
} ag6FNTCOMMON; /* End of 'ag6FNTCOMMON' structure */

/* Block type 3: pages
 * This block gives the name of each texture file with the image 
 * data for the characters. The string pageNames holds the names
 * separated and terminated by null chars. Each filename has the
 * same length, so once you know the size of the first name, you
 * can easily determine the position of each of the names. The id
 * of each page is the zero-based index of the string name. */
typedef struct tagag6FNTPAGES
{
  unsigned char Dummy;
  /* char pageNames[]; - Strings - null terminated strings */
} ag6FNTPAGES; /* End of 'ag6FNTPAGES' structure */

/* Block type 4: chars
 * The number of characters in the file can be computed by taking the size
 * of the block and dividing with the size of the charInfo structure, i.e.:
 *   numChars = charsBlock.blockSize/20. */
typedef struct tagag6FNTCHARS
{
  unsigned long int Id;       /* The character id (character code). */
  unsigned short int X;         /* The left position of the character image in the texture. */
  unsigned short int Y;         /* The top position of the character image in the texture. */
  unsigned short int Width;     /* The width of the character image in the texture. */
  unsigned short int Height;    /* The height of the character image in the texture. */
  short int XOffset;  /* How much the current position should be offset when copying the image from the texture to the screen. */
  short int YOffset;  /* How much the current position should be offset when copying the image from the texture to the screen. */
  short int XAdvance; /* How much the current position should be advanced after drawing the character. */
  unsigned char Page;      /* The texture page where the character image is found. */
  unsigned char Chnl;      /* The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels). */
} ag6FNTCHARS; /* End of 'ag6FNTCHARS' structure */

/* Block type 5: kerning pairs
 * This block is only in the file if there are any kerning
 * pairs with amount differing from 0. */
typedef struct tagag6FNTKERNING_PAIRS
{
  unsigned long int First;  /* The first character id. */
  unsigned long int Second; /* The second character id. */
  unsigned short int Amount;  /* How much the x position should be adjusted when drawing the second character immediately following the first. */
} ag6FNTKERNING_PAIRS; /* End of 'ag6FNTKERNING_PAIRS' structure */


#pragma pack(pop)

/* Font representation type */
typedef struct tagag6FONT
{
  /* Texture file name */
  char TextureFileName[AG6_MATERIAL_NAME_SIZE];
  /* Texture resource number */
  int TexNo;
  /* Material number */
  int MtlNo;

  /* Font description */
  char FontName[AG6_MATERIAL_NAME_SIZE]; /* Font face name */
  ag6FNTINFO Info;        /* Font information */
  ag6FNTCOMMON Common;    /* Font common information */
  ag6FNTCHARS Chars[256]; /* Every character information */
} ag6FONT;


/* Font load function.
 * ARGUMENTS:
 *   - font structure pointer:
 *       ag6FONT *Fnt;
 *   - font file name:
 *       char *FileName;
 * RETURNS:
 *   (int) TRUE if success, FALSE otherwise.
 */
int AG6_RndFntLoad( ag6FONT *Fnt, char *FileName );

/* Loading primitive from font function.
 * ARGUMENTS:
 *   - PRIM struct:
 *       ag6PRIM *Pr;
 *   - FONT struct:
 *       ag6GFONT *Fnt;
 * RETURNS: None.
 */
VOID AG6_RndPrimFromFont( ag6PRIM *Pr, char *Str, ag6FONT *Fnt, FLT FontSize, VEC4 Color );

#endif /* __RNDFONT_H_ */


/* END OF 'RNDFONT.H' FILE */