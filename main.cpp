/**
 * Tệp chứa hàm main của chương trình
 * TODO : clean code lại 
 */
#include "include/Imageloader.h"
#include "include/ScreenWriter.h"
#include "include/Planet.h"

using namespace solar_system_glo_var;

void setup(void);

/**
 * hàm vẽ các quỹ đạo
 */
void orbitalTrails(void);

/**
 * hàm vẽ hình ảnh slash? (giới thiệu)
 */
void drawLogoScene(void);

/**
 * hàm vẽ mô phỏng
 */
void drawScene(void);

/**
 * hàm quyết định xem sẽ hiện thị slash hay mô phỏng
 */
void drawScenesInOrder(void);

/**
 * hàm thực hiện chuyển động của các mô phỏng
 */
void animate(int n);

/// định nghĩa các hàm callback ///

/**
 * hàm callback khi cửa sổ bị thay đổi kích thước
 */
void resize(int w, int h);

/**
 * hàm callback khi thực hiện thao tác với chuột
 */
void mouseControl(int button, int state, int x, int y);

/**
 * hàm callback khi thực hiện thao tác cuộn con lăn con chuột
 */
void mouseWheel(int wheel, int direction, int x, int y);

/**
 * hàm callback khi thực hiện thao tác rê chuột
 */
void windowPmotion(int x, int y);

/**
 * hàm callback khi thực hiện các thao tác nhấn phím
 */
void keyInput(unsigned char key, int x, int y);

/**
 * hàm callback khi thực hiện chọn các lựa chọn trên menu
 */
void onMenuActive(int menu);

/// định nghĩa các biến đối tượng toàn cục ///

GLuint sunTexture, merTexture, venTexture, earTexture, marTexture, jupTexture, satTexture, uraTexture, nepTexture, pluTexture, staTexture, logTexture;
// Sun, Planets and Stars
Planet sun(5.0, 0, 0, 0, 0, 0);			  // Sun
Planet mer(1.0, 7, 0, 4.74, 02.11, 0);	  // Mercury
Planet ven(1.5, 11, 0, 3.50, 177.0, 0);	  // Venus
Planet ear(2.0, 16, 0, 2.98, 23.44, 0);	  // Earth
Planet mar(1.2, 21, 0, 2.41, 25.00, 0);	  // Mars
Planet jup(3.5, 28, 0, 1.31, 03.13, 0);	  // Jupiter
Planet sat(3.0, 37, 0, 0.97, 26.70, 0);	  // Saturn
Planet ura(2.5, 45.5, 0, 0.68, 97.77, 0); // Uranus
Planet nep(2.3, 53.6, 0, 0.54, 28.32, 0); // Neptune
Planet plu(0.3, 59, 0, 0.47, 119.6, 0);	  // Pluto
Planet lun(.40, 3, 0, 5.40, 0, 0);		  // Luna     (Earth)
Planet pho(.20, 1.8, 0, 2.30, 0, 0);	  // Phobos   (Mars)
Planet dei(.24, 2.4, 0, 3.60, 0, 0);	  // Deimos   (Mars)
Planet eur(.24, 4, 0, 4.40, 0, 0);		  // Europa   (Jupiter)
Planet gan(.24, 4.7, 0, 5.00, 0, 0);	  // Ganymede (Jupiter)
Planet cal(.24, 5.3, 0, 2.30, 0, 0);	  // Callisto (Jupiter)
Planet tit(.75, 3.7, 0, 2.40, 0, 0);	  // Titan	   (Saturn)
Planet nix(.10, 1.5, 0, 5.00, 0, 0);	  // Nix	   (Pluto)
Planet puc(.26, 2.9, 0, 7.00, 0, 0);	  // Puck	   (Uranus)
Planet tri(.36, 3.2, 0, 3.40, 0, 0);	  // Triton   (Neptune)

int main(int argc, char **argv)
{
	// khởi tạo glut
	glutInit(&argc, argv);
	// khởi tạo các thông số cơ bản
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutCreateWindow(APP_NAME);

	// hàm hiển thị đồ họa
	glutDisplayFunc(drawScenesInOrder);
	// hàm bắt sự kiện thay đổi kích thướt màn hình
	glutReshapeFunc(resize);
	// hàm bắt sự kiện chuột
	glutMouseFunc(mouseControl);
	// hàm bắt sự kiện phím
	glutKeyboardFunc(keyInput);
	// hàm bắt sự kiện con lăn chuột
	glutMouseWheelFunc(mouseWheel);
	// hàm bắt sự kiện rê chuột
	glutPassiveMotionFunc(windowPmotion);

	// tạo popup menu
	glutCreateMenu(onMenuActive);
	glutAddMenuEntry("Chay/dung mo phong [SPACE]", 32);
	glutAddMenuEntry("An/hien quy dao hanh tinh [O]", 79);
	glutAddMenuEntry("An/hien quy dao ve tinh [o]", 111);
	glutAddMenuEntry("An/hien cac ve tinh [M]", 77);
	glutAddMenuEntry("An/hien cac nhan [L]", 76);
	glutAddMenuEntry("Goc nhin cheo [1]", 49);
	glutAddMenuEntry("Goc nhin ngang [2]", 50);
	glutAddMenuEntry("Goc nhin doc [3]", 51);
	glutAddMenuEntry("Huong dan [H]", 72);
	glutAddMenuEntry("Lam chu server Mat Troi", 122);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// gọi hàm các setup
	setup();

	glutMainLoop();
}

void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// kích hoạt chế độ trong việc vẽ các đối tượng theo 3 chiều
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	// tải hình ảnh từ các file và chuyển thành texture
	Image *sta = loadBMP("img/stars.bmp");
	staTexture = loadTexture(sta);
	delete sta;
	Image *sun = loadBMP("img/sun.bmp");
	sunTexture = loadTexture(sun);
	delete sun;
	Image *mer = loadBMP("img/mercury.bmp");
	merTexture = loadTexture(mer);
	delete mer;
	Image *ven = loadBMP("img/venus.bmp");
	venTexture = loadTexture(ven);
	delete ven;
	Image *ear = loadBMP("img/earth.bmp");
	earTexture = loadTexture(ear);
	delete ear;
	Image *mar = loadBMP("img/mars.bmp");
	marTexture = loadTexture(mar);
	delete mar;
	Image *jup = loadBMP("img/jupiter.bmp");
	jupTexture = loadTexture(jup);
	delete jup;
	Image *sat = loadBMP("img/saturn.bmp");
	satTexture = loadTexture(sat);
	delete sat;
	Image *ura = loadBMP("img/uranus.bmp");
	uraTexture = loadTexture(ura);
	delete ura;
	Image *nep = loadBMP("img/neptune.bmp");
	nepTexture = loadTexture(nep);
	delete nep;
	Image *plu = loadBMP("img/pluto.bmp");
	pluTexture = loadTexture(plu);
	delete plu;
	Image *log = loadBMP("img/logo.bmp");
	logTexture = loadTexture(log);
	delete log;

	// thiết đặt đổ bóng
	glEnable(GL_LIGHTING);
	float lightAmb[] = {0.0, 0.0, 0.0, 1.0};
	float lightDifAndSpec[] = {1.0, 1.0, 1.0, 1.0};
	float globAmb[] = {0.5, 0.5, 0.5, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
}

void orbitalTrails(void)
{
	// đặt tọa độ hiện tại vào stack
	glPushMatrix();
	// đặt màu
	glColor3ub(255, 255, 255);

	// dịch tọa độ tâm
	glTranslatef(0.0, 0.0, 0.0);

	// xoay theo hướng 90 ở trục x
	glRotatef(90.0, 1.0, 0.0, 0.0);

	// vẽ các hình vòng xuyến dựa theo khoảng cách từ tâm đến các vị trí hành tinh
	glutWireTorus(0.001, mer.distance, 100.0, 100.0);
	glutWireTorus(0.001, ven.distance, 100.0, 100.0);
	glutWireTorus(0.001, ear.distance, 100.0, 100.0);
	glutWireTorus(0.001, mar.distance, 100.0, 100.0);
	glutWireTorus(0.001, jup.distance, 100.0, 100.0);
	glutWireTorus(0.001, sat.distance, 100.0, 100.0);
	glutWireTorus(0.001, ura.distance, 100.0, 100.0);
	glutWireTorus(0.001, nep.distance, 100.0, 100.0);
	glutWireTorus(0.001, plu.distance, 100.0, 100.0);

	// lấy tọa độ đã đặt vào stack ra lại
	glPopMatrix();


	// vẽ trục 3 chiều để thuận tiện trong việc hình dung các vị trí mô phỏng
	glPushMatrix();
	double len = 20.0; // độ dài của trục
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(len, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, len, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, len);
	glEnd();
	// gán nhãn cho từng trục
	glRasterPos3d(len, 0, 0);
	print("X");
	glRasterPos3d(0, len, 0);
	print("Y");
	glRasterPos3d(0, 0, len);
	print("Z");
	glPopMatrix();
}

void drawLogoScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, logTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-100, -100, -100);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(100, -100, -100);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(100, 100, -100);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-100, 100, -100);
	glEnd();

	glutSwapBuffers();
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


#ifdef _WIN32
#elif __MINGW32__
#elif __unix__
	// vì trong hàm printAt chứa hàm glWindowPos2i thuộc thư viện opengl của các HĐH thuộc unix
	// nên chỉ có các HĐH thuộc unix mới có thể gọi hàm này
	if (instructionState)
	{
		printAt(5, 680, "Nhan phim SPACE/LEFT_MOUSE de chay/dung mo phong");
		printAt(5, 655, "Nhan phim O de an/hien quy dao hanh tinh");
		printAt(5, 630, "Nhan phim o de an/hien quy dao ve tinh");
		printAt(5, 605, "Nhan phim M/m de an/hien cac ve tinh");
		printAt(5, 580, "Nhan phim L/l de an/hien cac nhan");
		printAt(5, 555, "Nhan phim 1/2/3 de thay doi goc nhin");
		printAt(5, 530, "Cuon chuot de phong to/thu nho (voi HDH Windows)");
		printAt(5, 505, "Nhan phim >/< de phong to/thu nho (voi HDH Linux)");
		printAt(5, 480, "Nhan phim H/h de an/hien huong dan");
		printAt(5, 455, "Nhan phim +/- de tang/giam toc do quay");
		printAt(5, 430, "Nhan phim D/d de thiet lap lai gia tri mac dinh");
		printAt(5, 405, "Nhan phim ESC de ket thuc gia lap");
	}
#elif __APPLE__
#endif

	// trong 1s thay khung bao nhiêu lần
	printAt(5, 85, "Speed = %f", (1.0 / (animationRepeatTime / 1000.0)));
	// click chuột phải hay trái
	printAt(5, 65, "Mouse Button = %s", mouseBtnPressed);
	// nhả hay nhấn chuột
	printAt(5, 45, "Mouse State = %s", mouseState);
	// nhấn phím nào
	printAt(5, 25, "Key = %d", keyPressed);
	// tọa độ chuột
	printAt(5, 05, "Mouse x=%d, Mouse y=%d", mouseX, mouseY);

	// đặt góc nhìn camera
	if (changeCamera == 0)
		gluLookAt(0.0, zoom, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (changeCamera == 1)
		gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (changeCamera == 2)
		gluLookAt(0.0, zoom, 0.00001, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// nếu cờ lệnh vẽ quỹ đạo hành tinh bật thì vẽ
	if (bigOrbitActive == 1)
		orbitalTrails();

	GLUquadric *quadric;
	quadric = gluNewQuadric();

	// vẽ mặt trời
	glPushMatrix();
	glRotatef(sun.orbit, 0.0, 1.0, 0.0);
	glTranslatef(sun.distance, 0.0, 0.0);
	if (labelsActive == 1)
	{
		glRasterPos3f(-1.2, 7.0, 0.0);
		glColor3ub(255, 255, 255);
		writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mat Troi");
	}
	glPushMatrix();
	glRotatef(sun.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(sun.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sunTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, sun.radius, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// Mercury
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
	glRotatef(mer.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(mer.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, merTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, mer.radius, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// Venus
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
	glRotatef(ven.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(ven.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, venTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, ven.radius, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// Earth, Orbit, Moon
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
	glRotatef(ear.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(ear.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
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

	// Mars, Orbits, Moons
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
	glRotatef(mar.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(mar.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
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

	// Jupiter, Orbits, Moons
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
	glRotatef(jup.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(jup.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
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

	// Saturn, Orbit, Moon
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
	glRotatef(sat.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(sat.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
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

	glColor3ub(255, 255, 255); // FIXES SHADING ISSUE

	// Uranus, Orbit, Moon
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
	glRotatef(ura.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(ura.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
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

	// Neptune, Orbit, Moon
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
	glRotatef(nep.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(nep.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
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

	// Pluto, Orbit, Moon
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
	glRotatef(plu.axisTilt, 1.0, 0.0, 0.0);
	glRotatef(plu.axisAni, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
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

	// đặt các ngôi sao trong vũ trụ làm nền
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

	glutSwapBuffers();
}

void animate(int n)
{
	// nếu cờ lệnh hoạt động thì animation mới được phép chạy
	if (isAnimate)
	{
		// đặt giá trị quỹ đạo ví trí của các hành tinh tăng lên dựa theo tốc độ xoay
		mer.orbit += mer.orbitSpeed;
		ven.orbit += ven.orbitSpeed;
		ear.orbit += ear.orbitSpeed;
		mar.orbit += mar.orbitSpeed;
		jup.orbit += jup.orbitSpeed;
		sat.orbit += sat.orbitSpeed;
		ura.orbit += ura.orbitSpeed;
		nep.orbit += nep.orbitSpeed;
		plu.orbit += plu.orbitSpeed;
		lun.orbit += lun.orbitSpeed;
		pho.orbit += pho.orbitSpeed;
		dei.orbit += dei.orbitSpeed;
		eur.orbit += eur.orbitSpeed;
		gan.orbit += gan.orbitSpeed;
		cal.orbit += cal.orbitSpeed;
		tit.orbit += tit.orbitSpeed;
		nix.orbit += nix.orbitSpeed;
		puc.orbit += puc.orbitSpeed;
		tri.orbit += tri.orbitSpeed;

		// nếu mà góc quỹ đạo quá 360 độ thì đặt nó lại về 0 (tức nó đã quay hết 1 vòng quanh quỹ đạo)
		if (mer, ven, ear, mar, jup, sat, ura, nep, plu, lun, pho, dei, eur, gan, cal, tit, nix, puc, tri.orbit > 360.0)
		{
			mer, ven, ear, mar, jup, sat, ura, nep, plu, lun, pho, dei, eur, gan, cal, tit, nix, puc, tri.orbit -= 360.0;
		}
		// giá trị tự quay quay trục tăng lên
		mer.axisAni += 10.0;
		ven.axisAni += 10.0;
		ear.axisAni += 10.0;
		mar.axisAni += 10.0;
		jup.axisAni += 10.0;
		sat.axisAni += 10.0;
		ura.axisAni += 10.0;
		nep.axisAni += 10.0;
		plu.axisAni += 10.0;

		// nếu giá trị vượt quá 360 độ thì đặt nó lại về 0 (tức nó đã quay hết 1 vòng quanh nó)
		if (mer, ven, ear, mar, jup, sat, ura, nep, plu.axisAni > 360.0)
		{
			mer, ven, ear, mar, jup, sat, ura, nep, plu.axisAni -= 360.0;
		}

		// vẽ lại màn hình theo các giá trị đã thay đổi bên trên
		glutPostRedisplay();
		// thiết lặp thời gian để thực hiện hàm animation bằng cách đệ quy (30 mili giây sẽ lặp 1 lần)
		glutTimerFunc(animationRepeatTime, animate, 1);
	}
}

void drawScenesInOrder(void)
{
	if (logoScene == 1)
	{
		drawLogoScene();
	}
	else
	{
		drawScene();
	}
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void mouseControl(int button, int state, int x, int y)
{
	// nếu nhấn chuột trái thì màn hình slash sẽ biến mất và hiển thị các mô phỏng
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseBtnPressed = "Left";
		if (!logoScene)
		{
			if (isAnimate)
				isAnimate = 0;
			else
			{
				isAnimate = 1;
				animate(1);
			}
		}
		else
		{
			logoScene = 0;
		}
	}

	// nếu nhân chuột phải thì ...
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		mouseBtnPressed = "Right";

	if (state == GLUT_DOWN)
		mouseState = "down";
	else if (state == GLUT_UP)
		mouseState = "up";

	// vẽ lại màn hình nếu giá trị logoScene thay đổi
	glutPostRedisplay();
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	// thay đổi giá trị của zoom để zoom xa/gần các mô phỏng
	if (direction > 0 && zoom < 100)
		zoom++;
	if (direction < 0 && zoom > -75)
		zoom--;
	// vẽ lại màn hình
	glutPostRedisplay();
}

void windowPmotion(int x, int y)
{
	mouseX = x;
	mouseY = y;
	glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y)
{
	keyPressed = key;
	switch (key)
	{
	// thoát chương trình nếu nhấn esc
	case 27:
		exit(0);
		break;
	// phím cách để chạy/dừng mô phỏng
	case ' ':
		if (isAnimate)
			isAnimate = 0;
		else
		{
			isAnimate = 1;
			animate(1);
		}
		break;
	// bật/tắt hiển thị quỹ đạo của vệ tinh
	case 'o':
		if (smallOrbitActive)
			smallOrbitActive = 0;
		else
			smallOrbitActive = 1;
		break;
	// bật/tắt hiện thị quỹ đạo của hành tinh
	case 'O':
		if (bigOrbitActive)
			bigOrbitActive = 0;
		else
			bigOrbitActive = 1;
		break;
	// bật/tắt hiện thị vệ tinh
	case 'm':
		if (moonsActive)
			moonsActive = 0;
		else
			moonsActive = 1;
		break;
	case 'M':
		if (moonsActive)
			moonsActive = 0;
		else
			moonsActive = 1;
		break;
	// bật/tắt hiển thị tên các hành tinh
	case 'l':
		if (labelsActive)
			labelsActive = 0;
		else
			labelsActive = 1;
		break;
	case 'L':
		if (labelsActive)
			labelsActive = 0;
		else
			labelsActive = 1;
		break;
	// thay đổi góc nhìn camera
	case '1':
		changeCamera = 0;
		break;
	case '2':
		changeCamera = 1;
		break;
	case '3':
		changeCamera = 2;
		break;
	case 'h':
		if (instructionState)
			instructionState = 0;
		else
			instructionState = 1;
		break;
	case 'H':
		if (instructionState)
			instructionState = 0;
		else
			instructionState = 1;
		break;
	case '-':
		animationRepeatTime += 5;
		break;
	case '+':
		animationRepeatTime -= 5;
		if (animationRepeatTime <= 0)
		{
			animationRepeatTime = 5;
		}
		break;
	case 'z':
		animationRepeatTime = 0.1;
		break;
	case '<':
		if (zoom < 100)
			zoom++;
		break;
	case '>':
		if (zoom > -75)
			zoom--;
		break;
	case 'd':
		bigOrbitActive = DEFAULT_BIG_ORBIT;
		smallOrbitActive = DEFAULT_SMALL_ORBIT;
		moonsActive = DEFAULT_MOON;
		changeCamera = DEFAULT_CAMERA_VI;
		labelsActive = DEFAULT_LABEL;
		zoom = DEFAULT_ZOOM;
		instructionState = DEFAULT_INSTRUCTION_STATE;
		animationRepeatTime = DEFAULT_ANIMATION_REPEAT_TIME;
		break;
	case 'D':
		bigOrbitActive = DEFAULT_BIG_ORBIT;
		smallOrbitActive = DEFAULT_SMALL_ORBIT;
		moonsActive = DEFAULT_MOON;
		changeCamera = DEFAULT_CAMERA_VI;
		labelsActive = DEFAULT_LABEL;
		zoom = DEFAULT_ZOOM;
		instructionState = DEFAULT_INSTRUCTION_STATE;
		animationRepeatTime = DEFAULT_ANIMATION_REPEAT_TIME;
		break;
	}
	glutPostRedisplay();
}

void onMenuActive(int menu)
{
	keyInput(menu, 0, 0);
}