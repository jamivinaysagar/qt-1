#ifndef PluginEventsSDL_h
#define PluginEventsSDL_h


typedef enum PluginEventType_e
{
	PluginMouseEventType,
	PluginKeyEventType,
	PluginPaintEventType
}PluginEventType;

typedef enum PluginMouseState_e
{
	PluginMouseButtonDown,
	PluginMouseButtonUp,
	PluginMouseButtonMove
}PluginMouseState;

typedef enum PluginMouseButton_e
{
	PluginMouseButtonLeft,
	PluginMouseButtonCenter,
	PluginMouseButtonRight,
	PluginMouseButtonWheelUp,
	PluginMouseButtonWheelDown
}PluginMouseButton;

typedef enum PluginKeyState_e
{
	PluginKeyDown,
	PluginKeyUp
}PluginKeyState;

typedef enum PluginModifierKey_e
{
	PluginAltKey 		= 1 << 0,
	PluginCtrlKey 		= 1 << 1,
	PluginMetaKey 		= 1 << 2,
	PluginShiftKey 		= 1 << 3,
}PluginModifierKey;


typedef struct PluginRect_s
{
    int16_t		top;
    int16_t		left;
    int16_t		bottom;
    int16_t		right;
} PluginRect;

typedef struct
{
	uint8_t 			type;
	uint8_t 			state;
	uint16_t 			x;
	uint16_t			y;
	int16_t 			xrel;
	int16_t				yrel;
	uint8_t 			which;
	uint8_t 			button;
} PluginMouseEvent;

typedef struct
{
	uint8_t 			type;
	uint8_t 			state;
	uint8_t 			scancode;
	uint16_t 			sym;
	uint16_t 			mod;
	uint16_t 			unicode;
} PluginKeyEvent;

typedef struct
{
	uint8_t 			type;
	uint8_t				bUseAccelBlit;
	PluginRect 			inval;
	uint16_t 			w;
	uint16_t			h;
	uint16_t 			xoffset;
	uint16_t			yoffset;
	uint16_t 			pitch;
	uint8_t 			depth;
	uint8_t* 			pixels;
} PluginPaintEvent;

typedef union
{
	uint8_t				type;
	PluginMouseEvent	mouse;
	PluginKeyEvent		key;
	PluginPaintEvent	paint;
} PluginEvent;


// Extend the NPNVariable enumeration
#define NPPVpluginDrawingFunctions	9999

typedef void* 	(*CREATE_SURFACE_FUNC)		(int width, int height, int depth_in_bits);
typedef bool 	(*FREE_SURFACE_FUNC)		(void * pSurface);
typedef bool 	(*LOCK_SURFACE_FUNC)		(void * pSurface);
typedef bool 	(*UNLOCK_SURFACE_FUNC)		(void * pSurface);
typedef void* 	(*GET_PIXELS_FUNC)			(void * pSurface);
typedef int 	(*GET_PITCH_FUNC)			(void * pSurface);
typedef bool 	(*DRAW_RECT_FUNC)			(void * pSurface, uint32_t color, const PluginRect* rect);
typedef bool 	(*BLIT_FUNC)				(void * pSurface, void* pTargetSurface, const int nTargetPitch, const PluginRect* src_rect,
											 const PluginRect* dest_rect, bool bSourceAlpha);

typedef struct GL_FuncTable_s
{
	CREATE_SURFACE_FUNC		pfCreateSurface;
	FREE_SURFACE_FUNC		pfFreeSurface;
	LOCK_SURFACE_FUNC		pfLockSurface;
	UNLOCK_SURFACE_FUNC		pfUnlockSurface;
	GET_PIXELS_FUNC			pfGetPixels;
	GET_PITCH_FUNC			pfGetPitch;
	DRAW_RECT_FUNC			pfDrawRect;
	BLIT_FUNC				pfBlit;
} GL_FuncTable;




#endif // PluginEventsSDL_h
