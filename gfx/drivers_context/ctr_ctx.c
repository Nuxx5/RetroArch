/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *  Copyright (C) 2011-2017 - Daniel De Matteis
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

/* 3DS context. */
#include <GL/picaGL.h>
#include "../../retroarch.h"
#include "../common/ctr_common.h"
#include "../../ctr/gpu_old.h"

/* static void ctr_ctx_swap_interval(void *data, int interval) */
/* { */
/*    (void)data; */
/*    glSwapInterval(interval); */
/* } */

static void ctr_ctx_get_video_size(void *data, unsigned *width, unsigned *height)
{
   (void)data;
   *width  = CTR_TOP_FRAMEBUFFER_WIDTH;
   *height = CTR_TOP_FRAMEBUFFER_HEIGHT;
}

static void ctr_ctx_check_window(void *data, bool *quit,
      bool *resize, unsigned *width, unsigned *height, bool is_shutdown)
{
   unsigned new_width, new_height;

   ctr_ctx_get_video_size(data, &new_width, &new_height);

   if (new_width != *width || new_height != *height)
   {
      *width = new_width;
      *height = new_height;
      *resize = true;
   }

   *quit = (bool)false;
}

static void ctr_ctx_swap_buffers(void *data, void *data2)
{
   (void)data;
   
   /* GPU_Finalize(); thought I needed this to keep it from hanging */
   pglSwapBuffers();
}

static bool ctr_ctx_set_video_mode(void *data,
      video_frame_info_t *video_info,
      unsigned width, unsigned height,
      bool fullscreen)
{
   (void)data;
   (void)width;
   (void)height;
   (void)fullscreen;

   return true;
}

static void ctr_ctx_destroy(void *data)
{
   (void)data;
   pglExit();
}

static void ctr_ctx_input_driver(void *data,
      const char *name,
      input_driver_t **input, void **input_data)
{
   (void)data;
   (void)input;
   (void)input_data;
}

static bool ctr_ctx_has_focus(void *data)
{
   (void)data;
   return true;
}

static bool ctr_ctx_suppress_screensaver(void *data, bool enable)
{
   (void)data;
   (void)enable;
   return false;
}

static enum gfx_ctx_api ctr_ctx_get_api(void *data)
{
   return GFX_CTX_NONE;
}

static bool ctr_ctx_bind_api(void *data, enum gfx_ctx_api api, unsigned major, unsigned minor)
{
   (void)data;
   (void)api;
   (void)major;
   (void)minor;

   return true;
}

static void ctr_ctx_show_mouse(void *data, bool state)
{
   (void)data;
   (void)state;
}

static void ctr_ctx_bind_hw_render(void *data, bool enable)
{
   (void)data;
   (void)enable;
}

static void *ctr_ctx_init(video_frame_info_t *video_info, void *video_driver)
{
   (void)video_driver;
   pglInit();

   return (void*)"ctr";
}

static uint32_t ctr_ctx_get_flags(void *data)
{
   uint32_t flags = 0;

   return flags;
}

static void ctr_ctx_set_flags(void *data, uint32_t flags)
{
   (void)data;
}

const gfx_ctx_driver_t ctr_ctx = {
   ctr_ctx_init,
   ctr_ctx_destroy,
   ctr_ctx_get_api,
   ctr_ctx_bind_api,
   NULL, /* swap_interval, */
   ctr_ctx_set_video_mode,
   ctr_ctx_get_video_size,
   NULL, /* get_refresh_rate */
   NULL, /* get_video_output_size */
   NULL, /* get_video_output_prev */
   NULL, /* get_video_output_next */
   NULL, /* get_metrics */
   NULL,
   NULL, /* update_title */
   ctr_ctx_check_window,
   NULL, /* set_resize */
   ctr_ctx_has_focus,
   ctr_ctx_suppress_screensaver,
   false, /* has_windowed */
   ctr_ctx_swap_buffers,
   ctr_ctx_input_driver,
   NULL,
   NULL,
   NULL,
   ctr_ctx_show_mouse,
   "ctr",
   ctr_ctx_get_flags,
   ctr_ctx_set_flags,
   ctr_ctx_bind_hw_render,
   NULL,
   NULL
};
