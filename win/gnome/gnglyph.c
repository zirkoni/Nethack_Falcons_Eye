/*	SCCS Id: @(#)gnglyph.c	3.3	2000/07/16	*/
/* Copyright (C) 1998 by Erik Andersen <andersee@debian.org> */
/* NetHack may be freely redistributed.  See license for details. */

#include "gnglyph.h"

static GHackGlyphs     ghack_glyphs;
static GdkImlibImage** ghack_tiles = NULL;

/* NAME:
 *     ghack_init_glyphs(char* xpm_file)
 *
 * ARGUMENTS:
 *     char *xpm_file -- The name of the image file.
 *                       May be any image format imlib recognizes.
 *			 Does not have to be XPM.
 *
 * RETURNS:
 *     TRUE  upon successful loading of the glyphs.
 *     FALSE upon failure.
 *
 * PURPOSE:
 *     Constructor for the Glyph object.  Well, really each glyph
 *     object is a collection of glyphs, or tiles.  This constructor
 *     takes a single argument: the name of the image file that contains
 *     the tile images.
 *
 * NOTES:
 *     The glyphs (tiles) must be in the image in a certain way: the
 *     glyphs must be stacked such that the resultant image is
 *     TILE_X wide, and TILE_Y * (number of glyphs) high.  In this
 *     sense, TILE_X == TILE_Y, and can be any reasonable integer--
 *     say, 16 <= TILE_X <= 64.  Because the glyph number is tightly
 *     coupled to the Nethack object it represents, the order of the
 *     glyphs in the image is imporant: Glyph 1 is at the top of the
 *     image, while Glyph N (the last glyph) is at the bottom.
 *
 *     What's the difference between a glyph and a tile?  Well, a
 *     tile is just an image.  A glyph is a tile that knows its
 *     place in line.
 *
 *     This initializer relies heavily on gdk_imlib.  Thanks, Rasterman.
 */

int
ghack_init_glyphs( const char *xpmFile)
{
  ghack_glyphs.im = gdk_imlib_load_image((char *) xpmFile);
  if ( ! ghack_glyphs.im )
    {
      g_error("Couldn't load required xpmFile!");
      return -1;
    }

  gdk_imlib_render(ghack_glyphs.im, ghack_glyphs.im->rgb_width,
	  ghack_glyphs.im->rgb_height);

  ghack_glyphs.count = ghack_glyphs.im->rgb_height / ghack_glyphs.im->rgb_width;
  ghack_glyphs.width  = ghack_glyphs.im->rgb_width;
  ghack_glyphs.height = ghack_glyphs.im->rgb_height / ghack_glyphs.count;


  /* Assume the tiles are stacked vertically.
   * Further, assume that the tiles are SQUARE
   */
  ghack_tiles = g_new0( GdkImlibImage*, ghack_glyphs.count );
  if (ghack_tiles == NULL)
      return -1;
  else
      return 0;
}

void
ghack_free_glyphs( )
{
    int i;
    for ( i=0 ; i<ghack_glyphs.count ; i++)
	gdk_imlib_destroy_image(ghack_tiles[i]);
    g_free( ghack_tiles);
    gdk_imlib_destroy_image(ghack_glyphs.im);
    ghack_glyphs.im=NULL;
}


/* NAME:
 *     ghack_glyph_count( )
 *
 * ARGUMENTS:
 *     None.
 *
 * RETURNS:
 *     int -- The number of glyphs in this object.
 *
 * PURPOSE:
 *     Simply reports the number of glyphs in this object.
 */

int
ghack_glyph_count( )
{
  return ghack_glyphs.count;
}


/* NAME:
 *     ghack_glyph_height()
 *
 * ARGUMENTS:
 *     None
 *
 * RETURNS:
 *     int -- The glyph height.
 *
 * PURPOSE:
 *     Returns the standard glyph height.
 */

int
ghack_glyph_height()
{
  return ghack_glyphs.height;
}


/* NAME:
 *     ghack_glyph_width()
 *
 * ARGUMENTS:
 *     None
 *
 * RETURNS:
 *     int -- The glyph width.
 *
 * PURPOSE:
 *     Returns the standard glyph width.
 */

int
ghack_glyph_width()
{
  return ghack_glyphs.width;
}


/* NAME:
 *     ghack_image_from_glyph( int glyph, gboolean force)
 *
 * ARGUMENTS:
 *     int glyph  -- The glyph number.
 *     gboolean force -- force it to re-render.
 *
 * RETURNS:
 *     GdkImlibImage* -- The glyph image, as a GdkImlibImage.
 *
 * PURPOSE:
 *     Decodes the glyph into an image suitable for manipulation
 */

GdkImlibImage*
ghack_image_from_glyph( int glyph, gboolean force )
{
  int tile = glyph2tile[glyph];

  if ( tile >= ghack_glyphs.count || tile < 0 )
    {
      g_warning("Aiiee! I've was asked for a tile outside the allowed range!\n"
	    "Email this to other-gnomehack@lists.debian.org");
      g_warning("Max tile: %d   Tile asked for: %d",
		ghack_glyphs.count, tile);
      return NULL;
    }

  if (ghack_glyphs.im == NULL)
    {
    g_warning("Aiiee! I've been asked to clone from a null image.\n"
	    "Email this to other-gnomehack@lists.debian.org");
    g_warning( "making image from tile %d, force=%s\n", tile,
	    (force==TRUE)? "TRUE": "FALSE");
    }

  if (force == TRUE)
    {
    g_warning("Aiiee! I've been asked to force rendering.\n"
	    "Email this to other-gnomehack@lists.debian.org");
    g_warning( "making image from tile %d, force=%s\n", tile,
	    (force==TRUE)? "TRUE" : "FALSE");
    }

  if (!ghack_tiles[tile] || force)
  {
#if 0
      fprintf( stderr, "crop_and_clone: glyph=%d, tile=%d, ptr=%p, x=%d, y=%d, w=%d, h=%d\n", glyph, tile,
	      (void*)&(ghack_tiles[tile]), 0,
	      tile * ghack_glyphs.width,
	      ghack_glyphs.height,
	      ghack_glyphs.width);
#endif
      if (ghack_glyphs.im->pixmap == NULL)
	  g_warning( "Aiiee!  ghack_glyphs.im->pixmap==NULL!!!!\n");
      ghack_tiles[tile] = gdk_imlib_crop_and_clone_image(ghack_glyphs.im, 0,
	      tile * ghack_glyphs.width,
	      ghack_glyphs.height,
	      ghack_glyphs.width);
  }

  if (ghack_tiles[tile] && (!ghack_tiles[tile]->pixmap || force))
  {
      if ( gdk_imlib_render(ghack_tiles[tile],
		  ghack_tiles[tile]->rgb_width,
		  ghack_tiles[tile]->rgb_height) == 0) {
	  g_error("GLYPH: couldn't create tile # %d", tile);
      }
      if ( !ghack_tiles[tile]->pixmap )
	  g_error("Strange, tile # %d didn't get rendered???", tile);
  }

  return ghack_tiles[tile];
}

