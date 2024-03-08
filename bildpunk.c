#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#if defined(__DOS__)
#include <dos.h>
#include <conio.h>

#define PORT_DEFINE_COLOR 0x3c8
#endif

#include "bildpunk.h"

#define BP_ERR_BADCONTEXT "Bad context."

void bp_error(char* error) {
	fprintf(stderr, "[bildpunk] error: %s\n", error);
}

void bp_setmode(unsigned char mode)
{
#if defined(__DOS__)
	union REGS regs;
	regs.w.ax = (unsigned int)(mode & 255);
	#if defined(__386__)
		int386(0x10, &regs, &regs);
	#else
		int86(0x10, &regs, &regs);
	#endif
#endif
}

BPCONTEXT* bp_create_context()
{
	BPCONTEXT* ctx = malloc(sizeof(BPCONTEXT));
	ctx->buffer = VIDEO_RAM;
	ctx->width = 320;
	ctx->height = 200;
	return ctx;
}

BPCONTEXT* bp_init()
{
	bp_setmode(0x13);
	return bp_create_context();
}

void bp_free(BPCONTEXT* ctx)
{
	if (! ctx) {
		bp_error(BP_ERR_BADCONTEXT);
		return;
	}
	bp_setmode(0x03);
	free(ctx);
}

void bp_putpixel(BPCONTEXT* ctx, int x, int y, BYTE color)
{
	#if defined(__DOS__)
	BYTE* pAdr;
	if ((x < 0) || (x >= ctx->width) || (y < 0) || (y >= ctx->height)) {
		return;
	};
	pAdr = (BYTE*)(ctx->buffer + y * ctx->width + x);
	*pAdr = color;
#else

#endif
}

void bp_clear(BPCONTEXT* ctx)
{
	if (! ctx) {
		return;
	}
	memset(ctx->buffer, 0, ctx->width * ctx->height);
}

void bp_hline(BPCONTEXT* ctx, int x, int y, size_t width, BYTE color)
{
	BYTE* pAdr;
	int x1, x2;
	if ((y < 0) || (y >= ctx->height)) {
		return;
	}
	x1 = MAX(0, x);
	x2 = MIN(x + (int)width, ctx->width - 1);
	pAdr = (BYTE*)(ctx->buffer + y * ctx->width + x1);
	memset(pAdr, color, x2 - x1 + 1);
}

void bp_fillrect(BPCONTEXT* ctx, int x, int y, size_t width, size_t height, BYTE color)
{
	size_t j = 0;
	for (j = 0; j < height; j++) {
		bp_hline(ctx, x, y + j, width, color);
	}
}

void bp_set_palette(BYTE color, BYTE r, BYTE g, BYTE b) {
	#if defined(__DOS__)
	outp(PORT_DEFINE_COLOR, color);
	outp(PORT_DEFINE_COLOR + 1, r >> 2);
	outp(PORT_DEFINE_COLOR + 1, g >> 2);
	outp(PORT_DEFINE_COLOR + 1, b >> 2);
	#endif
}

RGB bp_get_palette(BYTE color) {
	RGB rgb;
	#if defined(__DOS__)
	outp(PORT_DEFINE_COLOR, color);
	rgb.r = inp(PORT_DEFINE_COLOR + 1);
	rgb.g = inp(PORT_DEFINE_COLOR + 1);
	rgb.b = inp(PORT_DEFINE_COLOR + 1);
	#else
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	#endif
	return rgb;
}
