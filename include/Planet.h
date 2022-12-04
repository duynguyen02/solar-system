#ifndef PLANET_H_
#define PLANET_H_

#include "Global.h"

class Planet
{
public:
	float radius, distance, orbit, orbitSpeed, axisTilt, axisAni;

	Planet(float _radius, float _distance, float _orbit, float _orbitSpeed, float _axisTilt, float _axisAni);

	/**
	 * Hàm vẽ quỹ đạo các vệ tinh
	 */
	void drawSmallOrbit(void);

	/**
	 * Hàm vẽ các vệ tinh
	 */
	void drawMoon(void);
};

#endif