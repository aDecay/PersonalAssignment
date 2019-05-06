#include <CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")

#define _CRT_SECURE_NO_WARNINGS

void drawPlane(BlockID block, int sx, int sz, int ex, int ez, int y)
{
	for (int x = sx; x <= ex; x++)
		for (int z = sz; z <= ez; z++)
			locateBlock(block, x, y, z);
}

void drawPyramid(BlockID block, int cx, int by, int cz, int d, int height)
{
	int icm = d < height ? 1 : d / height;

	for (int dy = 0; dy <= height; dy++)
		for (int dx = dy - d; dx <= d - dy; dx += icm)
			for (int dz = dy - d; dz <= d - dy; dz += icm)
				locateBlock(block, cx + dx, by + dy, cz + dz);
}

void drawCube(BlockID block, int sx, int sy, int sz, int ex, int ey, int ez)
{
	for (int x = sx; x <= ex; x++)
		for (int y = sy; y <= ey; y++)
			for (int z = sz; z <= ez; z++)
				locateBlock(block, x, y, z);
}

int main()
{
	int sx, sy, sz;
	int ex, ey, ez;
	int cx, cz, len;
	int lx, rx, by, ty, fz, bz;
	int prmd, walld;
	int wallh;
	int blankd, interv;
	BlockID groundBlock = createBlock(BLOCK_STONE);
	BlockID pyramidBlock = createBlock(BLOCK_GLASS);
	BlockID wallBlock = createBlock(BLOCK_POLISHED_GRANITE);
	BlockID airBlock = createBlock(BLOCK_AIR);

	scanf("%d %d %d", &sx, &sy, &sz);
	scanf("%d %d %d", &ex, &ey, &ez);

	cx = sx + ex / 2;
	cz = sz + ez / 2;

	lx = sx < ex ? sx : ex;
	rx = sx > ex ? sx : ex;

	by = sy < ey ? sy : ey;
	ty = sy > ey ? sy : ey;

	fz = sz < ez ? sz : ez;
	bz = sz > ez ? sz : ez;

	len = rx - lx < bz - fz ? rx - lx : bz - fz;

	prmd = len / 5;
	walld = len / 10;

	drawPlane(groundBlock, lx, fz, rx, bz, by);
	drawPyramid(pyramidBlock, cx, by, cz, prmd, ty - by);

	wallh = ty - by;
	drawCube(wallBlock, lx, by, fz, lx + walld, by + wallh, bz);
	drawCube(wallBlock, rx - walld, by, fz, rx, by + wallh, bz);
	drawCube(wallBlock, lx, by, bz - walld, rx, by + wallh, bz);

	blankd = ((rx - lx) - 2 * walld) * 3 / 13;
	interv = ((rx - lx) - 2 * walld) / 13;
	for (int i = 0, x = interv; i < 5; i++, x += interv + blankd) {
		drawCube(airBlock, lx + x, by, bz - walld, lx + x + blankd, by + wallh / 2, bz);
	}

	blankd = ((bz - fz) - walld) * 3 / 13;
	interv = ((bz - fz) - walld) / 13;
	for (int i = 0, z = interv; i < 5; i++, z += interv + blankd) {
		drawCube(airBlock, lx, by, fz + z, lx + walld, by + wallh / 2, fz + z + blankd);
		drawCube(airBlock, rx - walld, by, fz + z, rx, by + wallh / 2, fz + z + blankd);
	}
}