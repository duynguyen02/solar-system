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

#define APP_NAME "SOLAR SYSTEM GROUP 4" // tên app
#define WINDOW_WIDTH 700                // chiều ngang cửa sổ app
#define WINDOW_HEIGHT 700               // chiều dọc cửa sổ app
#define WINDOW_POS_X -1                 // vị trí của cửa sổ app theo trục tọa độ x
#define WINDOW_POS_Y -1                 // vị trí của cửa sổ app theo trục tọa độ y

// định nghĩa các giá trị boolean mặc định của ứng dụng
#define DEFAULT_ANIMATE 0           // mô phỏng có đang chạy
#define DEFAULT_BIG_ORBIT 1         // hiển thị quỹ đạo hành tinh
#define DEFAULT_SMALL_ORBIT 1       // hiển thị quỹ đạo vệ tinh
#define DEFAULT_MOON 1              // hiển thị vệ tinh
#define DEFAULT_LABEL 1             // hiển thị các nhãn
#define DEFAULT_LOGO_SCENE 1        // hiển thị logo ngữ cảnh
#define DEFAULT_INSTRUCTION_STATE 1 // hiển thị hướng dẫn sử dụng

// định nghĩa các giá trị mặc định khác của ứng dụng
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

#endif