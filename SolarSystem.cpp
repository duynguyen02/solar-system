#include "include/SolarSystem.h"

void drawAxis()
{
    // vẽ trục 3 chiều
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3d(axisLength, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, axisLength, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, axisLength);
    glEnd();
    // gán nhãn cho từng trục
    glRasterPos3d(axisLength, 0, 0);
    print("X");
    glRasterPos3d(0, axisLength, 0);
    print("Y");
    glRasterPos3d(0, 0, axisLength);
    print("Z");
    glPopMatrix();
}

void orbitalTrails(float merDis, float venDis, float earDis, float marDis, float jupDis, float satDis, float uraDis, float nepDis, float pluDis)
{
    // đặt tọa độ hiện tại vào stack
    glPushMatrix();
    // đặt màu
    glColor3ub(255, 255, 255);

    // dịch tọa độ tâm về tọa độ (0,0,0) để xác định tâm theo tọa độ trục
    glTranslatef(0.0, 0.0, 0.0);

    // xoay theo hướng 90 ở trục x
    glRotatef(90.0, 1.0, 0.0, 0.0);

    // vẽ các hình vòng xuyến dựa theo khoảng cách từ tâm đến các vị trí ohành tinh
    // glutWireTorus vẽ một đường đa giác với việc tăng n đa giác lên sẽ khiến đa giác thành một vòng tròn
    // tham khảo: https://linux.die.net/man/3/glutwiretorus
    // minh chứng: https://youtu.be/x3rEQ-YiTrA?t=110
    // bán kính của ống // bán kính của vòng xuyến // số cạnh của ống // số cạnh của vòng xuyến
    glutWireTorus(0.001, merDis, 100.0, 100.0);
    glutWireTorus(0.001, venDis, 100.0, 100.0);
    glutWireTorus(0.001, earDis, 100.0, 100.0);
    glutWireTorus(0.001, marDis, 100.0, 100.0);
    glutWireTorus(0.001, jupDis, 100.0, 100.0);
    glutWireTorus(0.001, satDis, 100.0, 100.0);
    glutWireTorus(0.001, uraDis, 100.0, 100.0);
    glutWireTorus(0.001, nepDis, 100.0, 100.0);
    glutWireTorus(0.001, pluDis, 100.0, 100.0);

    // lấy tọa độ đã đặt vào stack ra lại
    glPopMatrix();
}

/// các hàm draw...() bên dưới cũng tương tự ///
void drawSun(Planet sun, GLuint sunTexture, GLUquadric *quadric)
{
    glPushMatrix();
    // vị trí góc xoay của sun theo trục y (y = 1.0) (theo mô phỏng thì mọi hành tinh đều ở góc 0)
    glRotatef(sun.orbit, 0.0, 1.0, 0.0);

    // đặt sun vào vị trí của nó trên mặt phẳng tọa độ x
    // và nó sẽ xoay theo từ khoảng cách này tới tâm (nếu có)
    glTranslatef(sun.distance, 0.0, 0.0);

    if (labelsActive == 1)
    {
        // chỉ định toa độ cho đối tượng raster và ghi nhãn vào màn hình
        glRasterPos3f(-1.2, 7.0, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mat Troi");
    }

    glPushMatrix();

    // chỉnh độ nghiêng của sun theo mặt phẳng hoàng đạo (trục tọa độ)
    glRotatef(sun.axisTilt, 0.0, 0.0, 1.0);
    // góc xoay đối với chính nó (trục tọa độ)
    glRotatef(sun.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    // bọc ảnh
    // tương tự trong hàm drawLogoScene
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sunTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    // vẽ hình cầu
    // quadrid // bán kính // số lượng kinh tuyến // số lượng vĩ tuyến
    gluSphere(quadric, sun.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glPopMatrix();
}

void drawMercury(Planet mer, GLuint merTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(mer.orbit, 0.0, 1.0, 0.0);
    glTranslatef(mer.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 3, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sao Thuy");
    }
    glPushMatrix();

    glRotatef(mer.axisTilt, 0.0, 0.0, 1.0);
    glRotatef(mer.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, merTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, mer.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();
}

void drawVenus(Planet ven, GLuint venTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(ven.orbit, 0.0, 1.0, 0.0);
    glTranslatef(ven.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 3, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sao Kim");
    }
    glPushMatrix();

    glRotatef(ven.axisTilt, 0.0, 0.0, 1.0);
    glRotatef(ven.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, venTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, ven.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();
}

void drawEarth(Planet ear, Planet lun, GLuint earTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(ear.orbit, 0.0, 1.0, 0.0);
    glTranslatef(ear.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 3, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Trai Dat");
    }
    glPushMatrix();

    // góc nghiêng trục (nghiên theo z)
    glRotatef(ear.axisTilt, 0.0, 0.0, 1.0);
    // xoay quay chính nó (xoay trục y)
    glRotatef(ear.axisAni, 0.0, 1.0, 0.0);
    // xoay để đúng chiều texture
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, earTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, ear.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1)
    {
        lun.drawSmallOrbit();
    }
    if (moonsActive == 1)
    {
        lun.drawMoon();
    }
    glPopMatrix();
}

void drawMars(Planet mar, Planet pho, Planet dei, GLuint marTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(mar.orbit, 0.0, 1.0, 0.0);
    glTranslatef(mar.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 3, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sao Hoa");
    }
    glPushMatrix();

    glRotatef(mar.axisTilt, 0.0, 0.0, 1.0);
    glRotatef(mar.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, marTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, mar.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1)
    {
        pho.drawSmallOrbit();
        dei.drawSmallOrbit();
    }
    if (moonsActive == 1)
    {
        pho.drawMoon();
        dei.drawMoon();
    }
    glPopMatrix();
}

void drawJupiter(Planet jup, Planet eur, Planet gan, Planet cal, GLuint jupTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(jup.orbit, 0.0, 1.0, 0.0);
    glTranslatef(jup.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 4.4, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sao Moc");
    }
    glPushMatrix();

    glRotatef(jup.axisTilt, 0.0, 0.0, 1.0);
    glRotatef(jup.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, jupTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, jup.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1)
    {
        eur.drawSmallOrbit();
        gan.drawSmallOrbit();
        cal.drawSmallOrbit();
    }
    if (moonsActive == 1)
    {
        eur.drawMoon();
        gan.drawMoon();
        cal.drawMoon();
    }
    glPopMatrix();
}

void drawSaturn(Planet sat, Planet tit, GLuint satTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(sat.orbit, 0.0, 1.0, 0.0);
    glTranslatef(sat.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 4.4, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sao Tho");
    }
    glPushMatrix();

    glRotatef(sat.axisTilt, 0.0, 0.0, 1.0);
    glRotatef(sat.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, satTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, sat.radius, 20.0, 20.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3ub(158, 145, 137);
    glRotatef(-63.0, 1.0, 0.0, 0.0);
    glutWireTorus(0.2, 6.0, 30.0, 30.0);
    glutWireTorus(0.4, 5.0, 30.0, 30.0);
    glPopMatrix();
    if (smallOrbitActive == 1)
    {
        tit.drawSmallOrbit();
    }
    if (moonsActive == 1)
    {
        tit.drawMoon();
    }
    glPopMatrix();
}

void drawUranus(Planet ura, Planet puc, GLuint uraTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(ura.orbit, 0.0, 1.0, 0.0);
    glTranslatef(ura.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 4.4, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sao Thien Vuong");
    }
    glPushMatrix();

    glRotatef(ura.axisTilt, 0.0, 0.0, 1.0);
    glRotatef(ura.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, uraTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, ura.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1)
    {
        puc.drawSmallOrbit();
    }
    if (moonsActive == 1)
    {
        puc.drawMoon();
    }
    glPopMatrix();
}

void drawNeptune(Planet nep, Planet tri, GLuint nepTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(nep.orbit, 0.0, 1.0, 0.0);
    glTranslatef(nep.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 4.4, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sao Hai Vuong");
    }
    glPushMatrix();

    glRotatef(nep.axisTilt, 0.0, 0.0, 1.0);
    glRotatef(nep.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, nepTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, nep.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1)
    {
        tri.drawSmallOrbit();
    }
    if (moonsActive == 1)
    {
        tri.drawMoon();
    }
    glPopMatrix();
}

void drawPluto(Planet plu, Planet nix, GLuint pluTexture, GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(plu.orbit, 0.0, 1.0, 0.0);
    glTranslatef(plu.distance, 0.0, 0.0);
    if (labelsActive == 1)
    {
        glRasterPos3f(0.0, 3.0, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sao Diem Vuong");
    }
    glPushMatrix();

    glRotatef(plu.axisTilt, 0.0, 0.0, 1.0);
    glRotatef(plu.axisAni, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, pluTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quadric, 1);
    gluSphere(quadric, plu.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1)
    {
        nix.drawSmallOrbit();
    }
    if (moonsActive == 1)
    {
        nix.drawMoon();
    }
    glPopMatrix();
}

void drawBackground(GLuint staTexture)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, staTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_POLYGON);
    glTexCoord2f(-1.0, 0.0);
    glVertex3f(-200, -200, -100);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(200, -200, -100);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(200, 200, -100);
    glTexCoord2f(-1.0, 2.0);
    glVertex3f(-200, 200, -100);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, staTexture);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-300, -83, -200);
    glTexCoord2f(8.0, 0.0);
    glVertex3f(300, -83, 200);
    glTexCoord2f(8.0, 8.0);
    glVertex3f(300, 200, -83);
    glTexCoord2f(0.0, 8.0);
    glVertex3f(-300, 83, -200);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, staTexture);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(300, -83, -200);
    glTexCoord2f(8.0, 0.0);
    glVertex3f(-300, -83, 200);
    glTexCoord2f(8.0, 8.0);
    glVertex3f(-300, 200, -83);
    glTexCoord2f(0.0, 8.0);
    glVertex3f(300, 83, -200);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, staTexture);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-200, -83, 200);
    glTexCoord2f(8.0, 0.0);
    glVertex3f(200, -83, 200);
    glTexCoord2f(8.0, 8.0);
    glVertex3f(200, -83, -200);
    glTexCoord2f(0.0, 8.0);
    glVertex3f(-200, -83, -200);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}