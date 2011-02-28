#include "intelcecursor.h"

#ifndef QT_NO_QWS_CURSOR

#define GDL_CURSOR_WIDTH 	32
#define GDL_CURSOR_HEIGHT 	32
#define CURSOR_DATA_SIZE (GDL_CURSOR_HEIGHT * GDL_CURSOR_WIDTH)
#define TRANSPARENT_COLOR_INDEX 2

/* HW Cursor Functions */
static void IntelCE_InitCursor();
static void IntelCE_CloseCursor();
static void IntelCE_SetCursor(void *cursor);
static void IntelCE_FreeCursor(void *cursor);
static void *IntelCE_CreateCursor(const QImage &image, int hot_x, int hot_y);
static void IntelCE_MoveCursor(int x, int y);

void IntelCECursor::initCursor()
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	qt_screencursor = new IntelCECursor();
	IntelCE_InitCursor();
}

IntelCECursor::IntelCECursor() 
	: m_bitmap(), m_pvCursor(NULL), m_bVisible(true)
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
}

IntelCECursor::~IntelCECursor()
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	if (m_pvCursor)
		IntelCE_FreeCursor(m_pvCursor);
	IntelCE_CloseCursor();
}

IntelCECursor* IntelCECursor::instance()
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	if (qt_screencursor == NULL) {
		initSoftwareCursor();
	}
	return (IntelCECursor*) qt_screencursor;
}

void IntelCECursor::show()
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	m_bVisible = true;
	IntelCE_SetCursor(m_pvCursor);
}

void IntelCECursor::hide()
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	m_bVisible = false;
	IntelCE_SetCursor(NULL);
}

bool IntelCECursor::isVisible() const
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	return m_bVisible;
}

bool IntelCECursor::isAccelerated() const
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	return true;
}

void IntelCECursor::move(int x, int y)
{
	if (m_bVisible) {
		//fprintf(stderr, "### IntelCECursor::%s(%d,%d)\n", __FUNCTION__, x, y);
		IntelCE_MoveCursor(x,y);
	}
}

void IntelCECursor::set(const QImage& image, int hotx, int hoty)
{
	//fprintf(stderr, "### IntelCECursor::%s(image,%d,%d)\n", __FUNCTION__,hotx,hoty);

	if ( image.isNull() ) {
		qCritical("cursor image is null\n");
		m_bitmap = QImage();
	}
	else if (image.format() != QImage::Format_Indexed8) {
		qCritical("invalid cursor image\n");
		m_bitmap = QImage();
	}
	else {
		m_bitmap = image;

		//fprintf(stderr, "cursor w=%d, h=%d, depth=%d\n",
		//		image.width(), image.height(), image.depth());

		if (m_pvCursor)
			IntelCE_FreeCursor(m_pvCursor);
		m_pvCursor = IntelCE_CreateCursor(image, hotx, hoty);
		IntelCE_SetCursor(m_pvCursor);
	}
}

QImage IntelCECursor::image() const
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	return m_bitmap;
}

QRect IntelCECursor::boundingRect() const
{
	//fprintf(stderr, "### IntelCECursor::%s\n", __FUNCTION__);
	return m_bitmap.rect();
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgdl.h"

#define CHECK_GDL_RC(rc, msg) {\
	if (rc != GDL_SUCCESS) {\
		fprintf(stderr, "GDL ERROR %d: %s (%s:%d)\n", rc, msg, __FILE__, __LINE__); \
		exit(-1); }}

/* The implementation dependent data for the window manager cursor */
typedef struct {
	int			x_hot;
	int			y_hot;
	uchar* 		pData;
} stCursor;

static gdl_surface_info_t destination_surface_info;
static gdl_uint8 *cursorPlaneBuffer;
static gdl_uint32 cursorPlanePitch;

// Initializes a plane for the graphics to be rendered to
static gdl_ret_t setup_plane(gdl_plane_id_t plane)
{
    gdl_pixel_format_t pixelFormat = GDL_PF_ARGB_8;
    gdl_color_space_t  colorSpace = GDL_COLOR_SPACE_RGB;
    gdl_color_t        gdl_color;
    gdl_palette_t      pal;
    gdl_rectangle_t srcRect;
    gdl_rectangle_t dstRect;
    gdl_ret_t rc = GDL_SUCCESS;

    dstRect.origin.x = 0;
    dstRect.origin.y = 0;
    dstRect.width = GDL_CURSOR_WIDTH;
    dstRect.height = GDL_CURSOR_HEIGHT;

    srcRect.origin.x = 0;
    srcRect.origin.y = 0;
    srcRect.width = GDL_CURSOR_WIDTH;
    srcRect.height = GDL_CURSOR_HEIGHT;

    rc = gdl_plane_reset(plane);
    if (GDL_SUCCESS == rc)
    {
        rc = gdl_plane_config_begin(plane);
    }

    if (GDL_SUCCESS == rc)
    {
        rc = gdl_plane_set_attr(GDL_PLANE_SRC_COLOR_SPACE, &colorSpace);
    }

    if (GDL_SUCCESS == rc)
    {
        rc = gdl_plane_set_attr(GDL_PLANE_PIXEL_FORMAT, &pixelFormat);
    }

    if (GDL_SUCCESS == rc)
    {
        rc = gdl_plane_set_attr(GDL_PLANE_DST_RECT, &dstRect);
    }

    if (GDL_SUCCESS == rc)
    {
        rc = gdl_plane_set_attr(GDL_PLANE_SRC_RECT, &srcRect);
    }

    if (GDL_SUCCESS == rc)
    {
        rc = gdl_plane_config_end(GDL_FALSE);
    }
    else
    {
        gdl_plane_config_end(GDL_TRUE);
    }

    if (GDL_SUCCESS != rc)
    {
        qCritical("GDL configuration failed! GDL error code is 0x%x\n", rc);
    }

    rc = gdl_alloc_surface(GDL_PF_ARGB_8,
                               GDL_CURSOR_WIDTH,
                               GDL_CURSOR_HEIGHT,
                               0,
                               &destination_surface_info);
    CHECK_GDL_RC(rc, "Failed ");

    // Black
    pal.data[0].a = 0xff;
    pal.data[0].r_y = 0x00;
    pal.data[0].g_u = 0x00;
    pal.data[0].b_v = 0x00;
    // White
    pal.data[1].a = 0xff;
    pal.data[1].r_y = 0xff;
    pal.data[1].g_u = 0xff;
    pal.data[1].b_v = 0xff;
    // Transparent background
    pal.data[2].a = 0x00;
    pal.data[2].r_y = 0x00;
    pal.data[2].g_u = 0x00;
    pal.data[2].b_v = 0x00;
    pal.length = 3;

    rc = gdl_set_palette(destination_surface_info.id, &pal);
    CHECK_GDL_RC(rc, "Failed ");

    rc = gdl_map_surface(destination_surface_info.id, &cursorPlaneBuffer, &cursorPlanePitch);
    CHECK_GDL_RC(rc, "Failed ");

    /* The CLUT index */
    gdl_color.alpha_index = 0;
    rc = gdl_clear_surface(destination_surface_info.id, &gdl_color);
    CHECK_GDL_RC(rc,"Failed ");

    rc = gdl_flip(plane,destination_surface_info.id, GDL_FLIP_ASYNC);
    CHECK_GDL_RC(rc,"Failed ");

    return rc;
}

static void IntelCE_InitCursor()
{
	/* Initialize the gdl layer */
	gdl_plane_id_t plane = GDL_PLANE_ID_IAP_B;
    gdl_init(0);
    setup_plane(plane);
	return;
}

static void IntelCE_CloseCursor()
{
    gdl_unmap_surface(destination_surface_info.id);
	gdl_close();
}

static void IntelCE_SetCursor(void *pvCursor)
{
	stCursor* cursor = (stCursor*)pvCursor;
	// Copy the cursor onto the plane
	for (int currentRow = 0; currentRow < GDL_CURSOR_HEIGHT; currentRow++) {
		memcpy(cursorPlaneBuffer+(currentRow*cursorPlanePitch),
			   cursor->pData+(currentRow*GDL_CURSOR_WIDTH), 
			   GDL_CURSOR_WIDTH);
	}
	gdl_flip(GDL_PLANE_ID_IAP_B,destination_surface_info.id, GDL_FLIP_ASYNC);
}

static void IntelCE_FreeCursor(void* pvCursor)
{
	stCursor *cursor = (stCursor*)pvCursor;
    if (cursor->pData) free(cursor->pData);
	free(cursor);
}

static void *IntelCE_CreateCursor(const QImage &image, int hot_x, int hot_y)
{
	stCursor *cursor;

	cursor = (stCursor*)malloc(sizeof(stCursor));
	if(cursor) {
		cursor->x_hot 	= hot_x;
		cursor->y_hot 	= hot_y;

		cursor->pData = (uchar*)malloc(CURSOR_DATA_SIZE);
		memset(cursor->pData, TRANSPARENT_COLOR_INDEX, CURSOR_DATA_SIZE);

		const uchar *pBase = image.bits();
		const uchar *pPixel;
		uchar *pData;

		for (int i = 0; i < GDL_CURSOR_HEIGHT && i < image.height(); i++) {
			pPixel = pBase + (i * image.bytesPerLine());
			pData  = cursor->pData + (i * GDL_CURSOR_WIDTH);
			
			// Semi-cheesy - assume the image uses a color table that
			// matches ours.  Seems to work, so we're good to go...
			for (int j = 0; j < GDL_CURSOR_WIDTH && j < image.width(); j++) {
				*pData++ = *pPixel++;
			}
		}
	}

	return((void*)cursor);
}

static void IntelCE_MoveCursor(int x, int y)
{
	gdl_plane_id_t 	plane 		= GDL_PLANE_ID_IAP_B; 
	gdl_ret_t 		rc 			= GDL_SUCCESS;
    gdl_rectangle_t srcRect, dstRect;

	int maxX = 1280, maxY = 720;
	
    dstRect.origin.x 	= x;
    dstRect.origin.y 	= y;
    dstRect.width 		= (x + GDL_CURSOR_WIDTH > maxX) ? (maxX - x) : GDL_CURSOR_WIDTH;
    dstRect.height 		= (y + GDL_CURSOR_HEIGHT > maxY) ? (maxY - y) : GDL_CURSOR_HEIGHT;

    srcRect.origin.x	= 0;
    srcRect.origin.y	= 0;
    srcRect.width		= dstRect.width;
    srcRect.height		= dstRect.height;

    /* Move the GDL plane to the new location */
    rc = gdl_plane_config_begin(plane);

    if (dstRect.width >= 16 && dstRect.height > 1) {
		if (GDL_SUCCESS == rc)
		{
			rc = gdl_plane_set_attr(GDL_PLANE_SRC_RECT, &srcRect);
		}

		if (GDL_SUCCESS == rc) {
			rc = gdl_plane_set_attr(GDL_PLANE_DST_RECT, &dstRect);
		}

		if (GDL_SUCCESS == rc) {
			rc = gdl_plane_config_end(GDL_FALSE);
		}
		else {
			gdl_plane_config_end(GDL_TRUE);
		}

		if (GDL_SUCCESS != rc)
		{
			qCritical("Failed to position mouse pointer.  GDL error code is 0x%x\n", rc);
		}
    }
}

#endif
