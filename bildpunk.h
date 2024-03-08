#pragma once
#include <stddef.h>
#define BYTE unsigned char
#define UINT unsigned int
#define VIDEO_RAM (BYTE* )0xa0000

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define CLAMP(x, a, b) MIN(MAX((x), (a)), (b))

typedef struct {
	size_t width;
	size_t height;
	BYTE* buffer;
} BPCONTEXT;

typedef struct {
	BYTE r;
	BYTE g;
	BYTE b;
} RGB;

BPCONTEXT* bp_init();
void bp_free(BPCONTEXT* ctx);
void bp_putpixel(BPCONTEXT* ctx, int x, int y, BYTE color);

void bp_clear(BPCONTEXT* ctx);
void bp_hline(BPCONTEXT* ctx, int x, int y, size_t width, BYTE color);
void bp_fillrect(BPCONTEXT* ctx, int x, int y, size_t width, size_t height, BYTE color);

