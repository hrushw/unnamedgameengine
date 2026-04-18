#include <math.h>

#include "main.c"

const u64 font_H = 0x424242427E424242;
const u64 font_E = 0x7E0202021E02027E;
const u64 font_L = 0x7E02020202020202;
const u64 font_O = 0x3C4242424242423C;

const u64 font_W = 0x42667E5A42424242;
const u64 font_R = 0x4262321E3E42423E;
const u64 font_D = 0x1E2242424242221E;

const u64 font_excl = 0x1818001818181818;
const u64 font_blank = 0x0000000000000000;

/* Main drawing function */
static
void draw(Fbuf fb, WinProps_X *wp) {
	Rect EyeLeft = {
		{ fb.sz.x/32, 10*fb.sz.y/48 },
		{ fb.sz.x/4, 10*fb.sz.y/48 },
	};

	Vec2 EyeRightOrigin = {
		(i32)fb.sz.x - EyeLeft.r0.x - EyeLeft.sz.x,
		EyeLeft.r0.y
	};
	Quad EyeRight = {
		EyeRightOrigin,
		{ EyeRightOrigin.x - fb.sz.x/64,   EyeRightOrigin.y + EyeLeft.sz.y },
		{ EyeRightOrigin.x + EyeLeft.sz.x, EyeRightOrigin.y + EyeLeft.sz.y - fb.sz.x/32 },
		{ EyeRightOrigin.x + EyeLeft.sz.x, EyeRightOrigin.y },
	};

	Vec2 Smilepts[] = {
		{fb.sz.x/2, fb.sz.y/2},
		{3*fb.sz.x/16, fb.sz.y/2},
		{7*fb.sz.x/32, 5*fb.sz.y/8},
		{fb.sz.x/4, 11*fb.sz.y/16},
		{5*fb.sz.x/16, 9*fb.sz.y/12},
		{13*fb.sz.x/32, 49*fb.sz.y/60},
		{15*fb.sz.x/32, 5*fb.sz.y/6},
		{17*fb.sz.x/32, 5*fb.sz.y/6},
		{19*fb.sz.x/32, 49*fb.sz.y/60},
		{11*fb.sz.x/16, 9*fb.sz.y/12},
		{3*fb.sz.x/4, 11*fb.sz.y/16},
		{25*fb.sz.x/32, 5*fb.sz.y/8},
		{13*fb.sz.x/16, fb.sz.y/2},
	};

	Vec2 Nose[] = {
		{7*fb.sz.x/16, 3*fb.sz.y/8},
		{15*fb.sz.x/32, 7*fb.sz.y/16},
		{fb.sz.x/2, fb.sz.y/3},
		{17*fb.sz.x/32, 7*fb.sz.y/16},
		{9*fb.sz.x/16, 3*fb.sz.y/8},
	};
	Vec2 Nose_origin = {fb.sz.x/2, 2*fb.sz.y/5};
	Vec2 Nose_rot[sizeof(Nose)/sizeof(Vec2)];

	Vec2 Teeth[] = {
		{ 7*fb.sz.x/32, fb.sz.y/2},
		{17*fb.sz.x/64, 5*fb.sz.y/8},
		{10*fb.sz.x/32, fb.sz.y/2},
		{23*fb.sz.x/64, 5*fb.sz.y/8},
		{13*fb.sz.x/32, fb.sz.y/2},
		{29*fb.sz.x/64, 5*fb.sz.y/8},
		{16*fb.sz.x/32, fb.sz.y/2},
		{35*fb.sz.x/64, 5*fb.sz.y/8},
		{19*fb.sz.x/32, fb.sz.y/2},
		{41*fb.sz.x/64, 5*fb.sz.y/8},
		{22*fb.sz.x/32, fb.sz.y/2},
		{47*fb.sz.x/64, 5*fb.sz.y/8},
		{25*fb.sz.x/32, fb.sz.y/2},
	};
	u32 ToothIndices[] = {
		0, 1, 2,
		2, 3, 4,
		4, 5, 6,
		6, 7, 8,
		8, 9, 10,
		10, 11, 12
	};

	Rect Goatee = {
		{ 7*fb.sz.x/16, 7*fb.sz.y/8 },
		{ fb.sz.x/8, fb.sz.y/2 }
	};

	Vec2 Brows[] = {
		{ 5*fb.sz.x/32, (i32)fb.sz.y/12 },
		{ fb.sz.x/32, - ((i32)fb.sz.y/24) },
		{ 9*fb.sz.x/32, - ((i32)fb.sz.y/24) },

		{ 27*fb.sz.x/32, (i32)fb.sz.y/12 },
		{ 31*fb.sz.x/32, - (i32)fb.sz.y/24 },
		{ 23*fb.sz.x/32, - (i32)fb.sz.y/24 },
	};

	UVec2 textr0 = { fb.sz.x/4, fb.sz.x/10};
	u64 txt[] = {
		font_H, font_E, font_L, font_L, font_O,
		font_blank,
		font_W, font_O, font_R, font_L, font_D,
		font_excl
	};

	Vec2 EyeballLeftPos = {   fb.sz.x/16, 5*fb.sz.y/16},
		EyeballRightPos = {15*fb.sz.x/16, 5*fb.sz.y/16};
	u32 EyeballRadius = fb.sz.x/32;
	i32 EyeLength = EyeLeft.sz.x - 2*EyeballRadius,
		tm = 0, posx = 0;

	enum { FRAME_NS = 16666667 };
	DrawClock clk = drawclock_init((Timespec) {0, FRAME_NS});

	while(!wp->closed) {
		fb_clear(fb, 0);

		fb_draw_rect(fb, 0x00FF00, EyeLeft.r0, EyeLeft.sz);
		fb_draw_quad(fb, 0x00CF3F, EyeRight);
		fb_draw_polygon_fan(fb, 0xFF0000, sizeof(Smilepts)/sizeof(Vec2), Smilepts);

		double x0 = Nose_origin.x, y0 = Nose_origin.y;
		for(u32 i = 0; i < sizeof(Nose)/sizeof(Vec2); ++i) {
			double x = Nose[i].x, y = Nose[i].y;
			double theta = (double)tm*M_PI_2/500.0;
			Nose_rot[i].x = x0 + (x - x0)*cos(theta) + (y - y0)*sin(theta);
			Nose_rot[i].y = y0 - (x - x0)*sin(theta) + (y - y0)*cos(theta);
		}
		fb_draw_polygon_strip(fb, 0xFFFF00, sizeof(Nose)/sizeof(Vec2), Nose_rot);

		fb_draw_triangles_indexed(fb, 0xEFEFCF, sizeof(ToothIndices)/sizeof(u32), ToothIndices, Teeth);
		fb_draw_rect(fb, 0xFF00FF, (Vec2) {-200, -300}, (UVec2) {100, 200});
		fb_draw_rect(fb, 0xFFFFFF, Goatee.r0, Goatee.sz);
		fb_draw_triangles(fb, 0x7F3F00, 6, Brows);

		fb_draw_u64_bitmaps_x(fb, 0xFF00FF, (UVec2){textr0.x - 20, textr0.y - 20}, sizeof(txt)/sizeof(u64), txt);
		fb_draw_u64_bitmaps_x_scaled(fb, 0xFF00FF, 3, textr0, sizeof(txt)/sizeof(u64), txt);

		// get time in milliseconds
		EyeballLeftPos.x = EyeLeft.r0.x + EyeballRadius + posx;
		EyeballRightPos.x = fb.sz.x - EyeballLeftPos.x;

		Pixel EyeballColor = 0x00007F;
		fb_draw_circle(fb, EyeballColor, EyeballRadius, EyeballLeftPos);
		fb_draw_circle(fb, EyeballColor, EyeballRadius, EyeballRightPos);

		wp_putimage_x(fb, wp);

		drawclock_wait(&clk);
		handle_events_x(wp);

		enum { PERIOD = 1200 };
		tm = 1000*clk.rel.tv_sec + (clk.rel.tv_nsec / 1000000);
		posx = (((i64)tm % PERIOD) * EyeLength) / PERIOD;
		if((tm % (2*PERIOD)) > PERIOD) posx = EyeLength - posx;

		// printf("%ld.%09ld : 0.%09ld s\r", clk.rel.tv_sec, clk.rel.tv_nsec, clk.diff.tv_nsec);
		// fflush(stdout);
	}
	// printf("\n");
}

int main() {
	enum win_width_e { WIDTH = 640 };
	enum win_height_e { HEIGHT = 480 };

	static Pixel fbufdata[HEIGHT*WIDTH] = {0};
	Fbuf fb = { { WIDTH, HEIGHT }, fbufdata };

	WinProps_X wp = window_init_x(fb);
	if(wp.status == ERR_SUCCESS)
		draw(fb, &wp);

	wp.img.data = NULL;
	XCloseDisplay(wp.disp);
	render_to_ppm(fopen("test01.ppm", "wb"), fb);

	return wp.status;
}

