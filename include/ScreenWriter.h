#ifndef SCREEN_WRITER_H_
#define SCREEN_WRITER_H_
#include "Global.h"

#define LEN 8192

/**
 * Hàm xử lý để in chữ
 */
void printv(va_list args, const char *format);

/**
 * Hàm in chữ đã được format ra màn hình
 * Hàm này không gọi glWindowPos2i như hàm printAt nên phải gọi glWindowPos2i trước khi gọi hàm này
 * glRasterPos3d nếu trong vùng 3d
 */
void print(const char *format, ...);

/**
 * Hàm in chữ theo tọa độ được thiết lập
 */
void printAt(int x, int y, const char *format, ...);

/**
 * Hàm in chữ không được format
 */
void writeBitmapString(void *font, char string[]);

#endif