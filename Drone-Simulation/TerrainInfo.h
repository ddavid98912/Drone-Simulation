#pragma once
#include <stdlib.h>
class TerrainInfo {
public:
	int totalWidth = 1000;
	int totalHeight = 1000;
	int offset = 500;

	int renderWidth = 11;
	int renderHeight = 31;

	float scale = 5;

	float* heightMap;

	void generateTerrain() {
		heightMap = new float[totalWidth * totalHeight];
		for (int i = 0;i < totalHeight * totalWidth; i++) {
			heightMap[i] = (((float)(rand() % 10)) / 10 + 3) * scale;
		}
	}
};




