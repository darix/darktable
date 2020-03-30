/*
    This file is part of darktable,
    copyright (c) 2020 Aldric Renaudin.

    darktable is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    darktable is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with darktable.  If not, see <http://www.gnu.org/licenses/>.
*/
/** a class to manage a collection of zoomable thumbnails for culling or full preview.  */
#include "dtgtk/thumbnail.h"
#include <gtk/gtk.h>

typedef enum dt_culling_mode_t
{
  DT_CULLING_MODE_CULLING = 0, // classic culling mode
  DT_CULLING_MODE_PREVIEW      // full preview mode
} dt_culling_mode_t;

typedef struct dt_culling_t
{
  dt_culling_mode_t mode;

  GtkWidget *widget; // GtkLayout -- main widget

  // list of thumbnails loaded inside main widget (dt_thumbnail_t)
  GList *list;

  // rowid of the main shown image inside 'memory.collected_images'
  int offset;
  int offset_imgid;

  int thumbs_count;            // last nb of thumb to display
  int view_width, view_height; // last main widget size
  GdkRectangle thumbs_area;    // coordinate of all the currently loaded thumbs area

  gboolean mouse_inside; // is the mouse pointer inside thumbatable widget ?

  GSList *accel_closures; // list of associated accels

  // when performing a drag, we store the list of items to drag here
  // as this can change during the drag and drop (esp. because of the image_over_id)
  GList *drag_list;

  gboolean navigate_inside_selection; // do we navigate inside selection or inside full collection
  gboolean selection_sync;            // should the selection follow current culling images

  gboolean select_desactivate;
} dt_culling_t;

dt_culling_t *dt_culling_new(dt_culling_mode_t mode);
// reload all thumbs from scratch.
void dt_culling_full_redraw(dt_culling_t *table, gboolean force);
void dt_culling_init(dt_culling_t *table);
// define if overlays should always be shown or just on mouse-over
/*void dt_culling_set_overlays(dt_culling_t *table, gboolean show);
// get/set offset (and redraw if needed)
int dt_thumbtable_get_offset(dt_culling_t *table);
gboolean dt_thumbtable_set_offset(dt_culling_t *table, int offset, gboolean redraw);
// set offset at specific imageid (and redraw if needed)
gboolean dt_thumbtable_set_offset_image(dt_culling_t *table, int imgid, gboolean redraw);

// fired when the zoom level change
void dt_thumbtable_zoom_changed(dt_culling_t *table, int oldzoom, int newzoom);

// ensure that the mentionned image is visible by moving the view if needed
gboolean dt_thumbtable_ensure_imgid_visibility(dt_culling_t *table, int imgid);

// move by key actions.
// this key accels are not managed here but inside view
gboolean dt_thumbtable_key_move(dt_thumbtable_t *table, dt_thumbtable_move_t move, gboolean select);

// ensure the first image in collection as no offset (is positionned on top-left)
gboolean dt_thumbtable_reset_first_offset(dt_thumbtable_t *table);

// scrollbar change
void dt_thumbtable_scrollbar_changed(dt_thumbtable_t *table, int x, int y);

// init all accels
void dt_thumbtable_init_accels(dt_thumbtable_t *table);
// connect all accels if thumbtable is active in the view and they are not loaded
// disconnect them if not
void dt_thumbtable_update_accels_connection(dt_thumbtable_t *table, int view);*/

// modelines: These editor modelines have been set for all relevant files by tools/update_modelines.sh
// vim: shiftwidth=2 expandtab tabstop=2 cindent
// kate: tab-indents: off; indent-width 2; replace-tabs on; indent-mode cstyle; remove-trailing-spaces modified;