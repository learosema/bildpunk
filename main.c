#include <stdio.h>
#include "bildpunk.h"

int main(int argc, char *argv[])
{
	int x;
	int y;
	BPCONTEXT* ctx = bp_init();
	printf("Hello World");
	fgetc(stdin);

	for (y = 0; y < 200; y++)
	{
		for (x = 0; x < 320; x++)
		{
			bp_putpixel(ctx, x, y, (BYTE)((x + y) & 255));
		}
	}
	fgetc(stdin);
	bp_clear(ctx);
	for (x = 0; x < 200; x++) {
		bp_hline(ctx, x, x, 320, (BYTE)(x & 255));
	}
	fgetc(stdin);
	bp_clear(ctx);
	for (x = 0; x < 200; x++) {
		bp_hline(ctx, -x, x, 320, (BYTE)(x & 255));
	}
	fgetc(stdin);
	bp_free(ctx);
	return 0;
}
