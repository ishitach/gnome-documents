/*
 * Copyright (c) 2011 Red Hat, Inc.
 *
 * Gnome Documents is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Gnome Documents is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Gnome Documents; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Author: Cosimo Cecchi <cosimoc@redhat.com>
 *
 */

#include "gd-main-icon-view.h"
#include "gd-main-view.h"
#include "gd-main-view-generic.h"
#include "gd-two-lines-renderer.h"

#include <math.h>
#include <glib/gi18n.h>

#define VIEW_ITEM_WIDTH 140
#define VIEW_ITEM_WRAP_WIDTH 128
#define VIEW_COLUMN_SPACING 20
#define VIEW_MARGIN 16

static void gd_main_view_generic_iface_init (GdMainViewGenericIface *iface);
G_DEFINE_TYPE_WITH_CODE (GdMainIconView, gd_main_icon_view, GTK_TYPE_ICON_VIEW,
                         G_IMPLEMENT_INTERFACE (GD_TYPE_MAIN_VIEW_GENERIC,
                                                gd_main_view_generic_iface_init))

static void
on_icon_selection_changed (GtkIconView *iv,
                           gpointer user_data)
{
  GdMainIconView *self = user_data;
  g_signal_emit_by_name (self, "view-selection-changed");
}

static void
gd_main_icon_view_constructed (GObject *obj)
{
  GdMainIconView *self = GD_MAIN_ICON_VIEW (obj);
  GtkCellRenderer *cell;

  G_OBJECT_CLASS (gd_main_icon_view_parent_class)->constructed (obj);

  gtk_widget_set_hexpand (GTK_WIDGET (self), TRUE);
  gtk_widget_set_vexpand (GTK_WIDGET (self), TRUE);

  g_object_set (self,
                "item-width", VIEW_ITEM_WIDTH,
                "column-spacing", VIEW_COLUMN_SPACING,
                "margin", VIEW_MARGIN,
                NULL);

  g_signal_connect (self, "selection-changed",
                    G_CALLBACK (on_icon_selection_changed), self);

  cell = gtk_cell_renderer_pixbuf_new ();
  g_object_set (cell,
                "xalign", 0.5,
                "yalign", 0.5,
                NULL);

  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (self), cell, FALSE);
  gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (self), cell,
                                 "pixbuf", GD_MAIN_COLUMN_ICON);

  cell = gd_two_lines_renderer_new ();
  g_object_set (cell,
                "alignment", PANGO_ALIGN_CENTER,
                "wrap-mode", PANGO_WRAP_WORD_CHAR,
                "wrap-width", VIEW_ITEM_WRAP_WIDTH,
                "text-lines", 3,
                NULL);
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (self), cell, FALSE);
  gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (self), cell,
                                 "text", GD_MAIN_COLUMN_TITLE);
  gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (self), cell,
                                 "line-two", GD_MAIN_COLUMN_AUTHOR);
}

static void
gd_main_icon_view_class_init (GdMainIconViewClass *klass)
{
  GObjectClass *oclass = G_OBJECT_CLASS (klass);

  oclass->constructed = gd_main_icon_view_constructed;
}

static void
gd_main_icon_view_init (GdMainIconView *self)
{
  /* nothing */
}

static GList *
gd_main_icon_view_get_selection (GdMainViewGeneric *mv)
{
  GtkIconView *iv = GTK_ICON_VIEW (mv);

  return gtk_icon_view_get_selected_items (iv);
}

static GtkTreePath *
gd_main_icon_view_get_path_at_pos (GdMainViewGeneric *mv,
                                   gint x,
                                   gint y)
{
  return gtk_icon_view_get_path_at_pos (GTK_ICON_VIEW (mv), x, y);
}

static void
gd_main_icon_view_set_selection_mode (GdMainViewGeneric *mv,
                                      GtkSelectionMode mode)
{
  gtk_icon_view_set_selection_mode (GTK_ICON_VIEW (mv), mode);
}

static void
gd_main_icon_view_scroll_to_path (GdMainViewGeneric *mv,
                                  GtkTreePath *path)
{
  gtk_icon_view_scroll_to_path (GTK_ICON_VIEW (mv), path, TRUE, 0.5, 0.5);
}

static gboolean
gd_main_icon_view_path_is_selected (GdMainViewGeneric *mv,
                                    GtkTreePath *path)
{
  return gtk_icon_view_path_is_selected (GTK_ICON_VIEW (mv), path);
}

static void
gd_main_icon_view_select_path (GdMainViewGeneric *mv,
                               GtkTreePath *path)
{
  gtk_icon_view_select_path (GTK_ICON_VIEW (mv), path);
}

static void
gd_main_icon_view_unselect_path (GdMainViewGeneric *mv,
                                 GtkTreePath *path)
{
  gtk_icon_view_unselect_path (GTK_ICON_VIEW (mv), path);
}

static void
gd_main_icon_view_set_model (GdMainViewGeneric *mv,
                             GtkTreeModel *model)
{
  gtk_icon_view_set_model (GTK_ICON_VIEW (mv), model);
}

static void
gd_main_view_generic_iface_init (GdMainViewGenericIface *iface)
{
  iface->set_model = gd_main_icon_view_set_model;
  iface->get_selection = gd_main_icon_view_get_selection;
  iface->get_path_at_pos = gd_main_icon_view_get_path_at_pos;
  iface->scroll_to_path = gd_main_icon_view_scroll_to_path;
  iface->set_selection_mode = gd_main_icon_view_set_selection_mode;
  iface->path_is_selected = gd_main_icon_view_path_is_selected;
  iface->select_path = gd_main_icon_view_select_path;
  iface->unselect_path = gd_main_icon_view_unselect_path;
}

GtkWidget *
gd_main_icon_view_new (void)
{
  return g_object_new (GD_TYPE_MAIN_ICON_VIEW, NULL);
}