/**
 * Tệp chứa hàm main của chương trình
 */
#include "include/Imageloader.h"
#include "include/ScreenWriter.h"
#include "include/Planet.h"
#include "include/SolarSystem.h"

using namespace std;

int isAnimate;
int bigOrbitActive;
int smallOrbitActive;
int moonsActive;
int changeCamera;
int labelsActive;
int zoom;
int logoScene;
int instructionState;
int animationRepeatTime;
char *mouseBtnPressed;
char *mouseState;
int keyPressed;
int mouseX;
int mouseY;

static float lightPos[] = {0.0, 0.0, -75.0, 1.0}; // vị trí tiêu điểm
static float spotAngle = 360;					  // góc chiếu
float spotDirection[] = {1.0, 0.0, 0.0};		  // hướng chiếu

void setup(void);

/**
 * hàm vẽ hình ảnh giới thiệu
 */
void drawLogoScene(void);

/**
 * hàm vẽ mô phỏng
 */
void drawScene(void);

/**
 * hàm quyết định xem sẽ hiện thị giới thiệu hay mô phỏng
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

/**
 * hàm hướng dẫn sử dụng
 */
void instruction(void);

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
	isAnimate = DEFAULT_ANIMATE;
	bigOrbitActive = DEFAULT_BIG_ORBIT;
	smallOrbitActive = DEFAULT_SMALL_ORBIT;
	moonsActive = DEFAULT_MOON;
	changeCamera = DEFAULT_CAMERA_VI;
	labelsActive = DEFAULT_LABEL;
	zoom = DEFAULT_ZOOM;
	logoScene = DEFAULT_LOGO_SCENE;
	instructionState = DEFAULT_INSTRUCTION_STATE;
	animationRepeatTime = DEFAULT_ANIMATION_REPEAT_TIME;
	mouseBtnPressed = DEFAULT_MOUSE_PRESS;
	mouseState = DEFAULT_MOUSE_STATE;
	keyPressed = DEFAULT_KEY_PRESS;
	mouseX = DEFAULT_MOUSE_X;
	mouseY = DEFAULT_MOUSE_Y;

	instruction();
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
	}
#elif __APPLE__
#endif

	// đặt góc nhìn camera
	if (changeCamera == 0)
		gluLookAt(0.0, zoom, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (changeCamera == 1)
		gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (changeCamera == 2)
		gluLookAt(0.0, zoom, 0.00001, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// nếu cờ lệnh vẽ quỹ đạo hành tinh bật thì vẽ
	if (bigOrbitActive == 1)
		orbitalTrails(
			mer.distance,
			ven.distance,
			ear.distance,
			mar.distance,
			jup.distance,
			sat.distance,
			ura.distance,
			nep.distance,
			plu.distance);

	GLUquadric *quadric;
	quadric = gluNewQuadric();

	drawSun(sun, sunTexture, quadric);
	drawMercury(mer, merTexture, quadric);
	drawVenus(ven, venTexture, quadric);
	drawEarth(ear, lun, earTexture, quadric);
	drawMars(mar, pho, dei, marTexture, quadric);
	drawJupiter(jup, eur, gan, cal, jupTexture, quadric);
	drawSaturn(sat, tit, satTexture, quadric);
	glColor3ub(255, 255, 255); // FIXES SHADING ISSUE
	drawUranus(ura, puc, uraTexture, quadric);
	drawNeptune(nep, tri, nepTexture, quadric);
	drawPluto(plu, nix, pluTexture, quadric);
	drawBackground(staTexture);

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

void instruction(void)
{
	cout << "Nhan phim SPACE/LEFT_MOUSE de chay/dung mo phong" << endl;
	cout << "Nhan phim O de an/hien quy dao hanh tinh" << endl;
	cout << "Nhan phim o de an/hien quy dao ve tinh" << endl;
	cout << "Nhan phim M/m de an/hien cac ve tinh" << endl;
	cout << "Nhan phim L/l de an/hien cac nhan" << endl;
	cout << "Nhan phim 1/2/3 de thay doi goc nhin" << endl;
	cout << "Cuon chuot de phong to/thu nho (voi HDH Windows)" << endl;
	cout << "Nhan phim >/< de phong to/thu nho (voi HDH Linux)" << endl;
	cout << "Nhan phim H/h de an/hien huong dan" << endl;
	cout << "Nhan phim +/- de tang/giam toc do quay" << endl;
	cout << "Nhan phim D/d de thiet lap lai gia tri mac dinh" << endl;
	cout << "Nhan phim ESC de ket thuc gia lap" << endl;
}