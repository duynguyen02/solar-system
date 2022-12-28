/**
 * File chứa các biến toàn cục chương trình
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <iostream>
#include <stdio.h>

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLUT/freeglut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

#define MAX_OF_PLANET_MODE 10 // số chế độ tối đa
// định nghĩa các chế độ góc nhìn hành tinh
enum PLANET_MODE{
    SUN,
    MER,
    VEN,
    EAR,
    MAR,
    JUP,
    SAT,
    URA,
    NEP,
    PLU
};

#define APP_NAME "SOLAR SYSTEM GROUP 6" // tên app
#define WINDOW_WIDTH 700                // chiều ngang cửa sổ app
#define WINDOW_HEIGHT 700               // chiều dọc cửa sổ app
#define WINDOW_POS_X -1                 // vị trí của cửa sổ app theo trục tọa độ x
#define WINDOW_POS_Y -1                 // vị trí của cửa sổ app theo trục tọa độ y

// đường dẫn tới các file âm thanh
#define MAIN_SOUND "audio/dochilacaicocuaanh.mp3"
#define SUN_SOUND  "audio/sun.mp3" 
#define MER_SOUND  "audio/mercury.mp3" 
#define VEN_SOUND  "audio/venus.mp3" 
#define EAR_SOUND  "audio/earth.mp3" 
#define MAR_SOUND  "audio/mars.mp3" 
#define JUP_SOUND  "audio/jupiter.mp3" 
#define SAT_SOUND  "audio/saturn.mp3" 
#define URA_SOUND  "audio/uranus.mp3" 
#define NEP_SOUND  "audio/neptune.mp3" 
#define PLU_SOUND  "audio/pluto.mp3" 


#define SUN_DISPLAY_NAME "Sun"
#define MER_DISPLAY_NAME "Mercury"
#define VEN_DISPLAY_NAME "Venus"
#define EAR_DISPLAY_NAME "Earth"
#define MAR_DISPLAY_NAME "Mars"
#define JUP_DISPLAY_NAME "Jupiter"
#define SAT_DISPLAY_NAME "Saturn"
#define URA_DISPLAY_NAME "Uranus"
#define NEP_DISPLAY_NAME "Neptune"
#define PLU_DISPLAY_NAME "Pluto"


// định nghĩa các giá trị boolean mặc định của ứng dụng
#define DEFAULT_PLANET_MODE 0     // chế độ góc nhìn 
#define DEFAULT_ANIMATE 0           // mô phỏng có đang chạy
#define DEFAULT_BIG_ORBIT 1         // hiển thị quỹ đạo hành tinh
#define DEFAULT_SMALL_ORBIT 1       // hiển thị quỹ đạo vệ tinh
#define DEFAULT_MOON 1              // hiển thị vệ tinh
#define DEFAULT_LABEL 1             // hiển thị các nhãn
#define DEFAULT_LOGO_SCENE 1        // hiển thị logo ngữ cảnh
#define DEFAULT_INSTRUCTION_STATE 1 // hiển thị hướng dẫn sử dụng

// định nghĩa các giá trị mặc định khác của ứng dụng
#define DEFAULT_LENGTH_OF_AXIS 59.0      // độ dài của các trục tọa độ tỷ lệ 1/100.000.000
#define DEFAULT_CAMERA_VI 0              // hướng nhìn camera (0: chéo từ trên xuống 1: nằm ngang 2: từ trên xuống)
#define DEFAULT_ZOOM 50                  // độ phóng tầm nhìn
#define DEFAULT_ANIMATION_REPEAT_TIME 30 // thời gian vẽ lại khung (30ms vẽ lại khung hay 1s vẽ khoảng hơn 30 khung)
#define DEFAULT_KEY_PRESS 0              // phím đang nhấn
#define DEFAULT_MOUSE_PRESS ""           // phím chuột đang nhấn
#define DEFAULT_MOUSE_STATE ""           // trạng thái chuột (nhấn/thả)
#define DEFAULT_MOUSE_X 0                // vị trí chuột theo tọa độ x của cửa sổ app
#define DEFAULT_MOUSE_Y 0                // vị trí chuột theo tọa độ y của cửa sổ app

// các giá trị mặc định được gán vào biến toàn cục để sử dụng cho app //
extern int isAnimate;
extern int bigOrbitActive;
extern int smallOrbitActive;
extern int moonsActive;
extern int changeCamera;
extern int labelsActive;
extern int zoom;
extern int logoScene;
extern int instructionState;
extern int animationRepeatTime;
extern char *mouseBtnPressed;
extern char *mouseState;
extern int keyPressed;
extern int mouseX;
extern int mouseY;
extern float axisLength;

#endif