# 기초컴퓨터프로그래밍 개인과제
## 만들고자 한 것
유리 피라미드 형태의 건물과 그를 둘러싼 조형물
## 소스코드
### 사용자 지정 함수
#### 바닥 그리기
```C
void drawPlane(BlockID block, int sx, int sz, int ex, int ez, int y)
{
	for (int x = sx; x <= ex; x++)
		for (int z = sz; z <= ez; z++)
			locateBlock(block, x, y, z);
}
```
#### 피라미드 그리기
```C
void drawPyramid(BlockID block, int cx, int by, int cz, int d, int height)
{
	int icm = d < height ? 1 : d / height;

	for (int dy = 0; dy <= height; dy++)
		for (int dx = dy - d; dx <= d - dy; dx += icm)
			for (int dz = dy - d; dz <= d - dy; dz += icm)
				locateBlock(block, cx + dx, by + dy, cz + dz);
}
```
#### 직육면체 그리기
```C
void drawCube(BlockID block, int sx, int sy, int sz, int ex, int ey, int ez)
{
	for (int x = sx; x <= ex; x++)
		for (int y = sy; y <= ey; y++)
			for (int z = sz; z <= ez; z++)
				locateBlock(block, x, y, z);
}
```
#### 메인 함수
```C
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

	//블록 생성 범위 입력
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

	//바닥 그리기 
	drawPlane(groundBlock, lx, fz, rx, bz, by);
	//피라미드 그리기 
	drawPyramid(pyramidBlock, cx, by, cz, prmd, ty - by);

	//벽 그리기 
	wallh = ty - by;
	drawCube(wallBlock, lx, by, fz, lx + walld, by + wallh, bz);
	drawCube(wallBlock, rx - walld, by, fz, rx, by + wallh, bz);
	drawCube(wallBlock, lx, by, bz - walld, rx, by + wallh, bz);

	//벽에 구멍 뚫기 
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
```