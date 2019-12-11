#pragma once
#include <stdlib.h>
#include "PerlinNoise.h"

class TerrainInfo {
public:
	int totalWidth = 1000;
	int totalHeight = 1000;
	int offset = 500;

	int renderWidth = 31;
	int renderHeight = 51;

	float scale = 5;

	float* heightMap;

	PerlinNoise pn;

	void generateTerrain() {
		heightMap = new float[totalWidth * totalHeight];
		for (int i = 0;i < totalHeight * totalWidth; i++) {
			float n = 3.5 * pn.noise(i / totalWidth * 0.1, i % totalWidth * 0.1, 1.54);
			heightMap[i] = ((float)(n + 1.5)) * scale;
		}
	}
};




