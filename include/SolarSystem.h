#ifndef _SOLAR_SYSTEM_H_
#define _SOLAR_SYSTEM_H_
#include "Global.h"
#include "Planet.h"
#include "ScreenWriter.h"

/**
 * hàm vẽ trục
 */
void drawAxis();

/**
 * hàm vẽ các quỹ đạo
 */
void orbitalTrails(
    float merDis, float venDis, float earDis, float marDis, float jupDis, float satDis, float uraDis, float nepDis, float pluDis);

/**
 * hàm vẽ mặt trời
 */
void drawSun(Planet sun, GLuint sunTexture, GLUquadric *quadric);

/**
 * hàm vẽ sao thủy
 */
void drawMercury(Planet mer, GLuint merTexture, GLUquadric *quadric);

/**
 * hàm vẽ sao kim
 */
void drawVenus(Planet ven, GLuint venTexture, GLUquadric *quadric);

/**
 * hàm vẽ trái đất
 */
void drawEarth(Planet ear, Planet lun, GLuint earTexture, GLUquadric *quadric);

/**
 * hàm vẽ sao hỏa
 */
void drawMars(Planet mar, Planet pho, Planet dei, GLuint marTexture, GLUquadric *quadric);

/**
 * hàm vẽ sao mộc
 */
void drawJupiter(Planet jup, Planet eur, Planet gan, Planet cal, GLuint jupTexture, GLUquadric *quadric);

/**
 * hàm vẽ sao thổ
 */
void drawSaturn(Planet sat, Planet tit, GLuint satTexture, GLUquadric *quadric);

/**
 * hàm vẽ sao thiên vương
 */
void drawUranus(Planet ura, Planet puc, GLuint uraTexture, GLUquadric *quadric);

/**
 * hàm vẽ sao hải vương
 */
void drawNeptune(Planet nep, Planet tri, GLuint nepTexture, GLUquadric *quadric);

/**
 * hàm vẽ sao diêm vương
 */
void drawPluto(Planet plu, Planet nix, GLuint pluTexture, GLUquadric *quadric);

/**
 * hàm vẽ nền
 */
void drawBackground(GLuint staTexture);

#endif