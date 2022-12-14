#include "include/ScreenWriter.h"

void printv(va_list args, const char *format)
{
	char buf[LEN];
	char *ch = buf;
	vsnprintf(buf, LEN, format, args);
	while (*ch)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *ch++);
}

void print(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	printv(args, format);
	va_end(args);
}

#ifdef __unix__
void printAt(int x, int y, const char *format, ...)
{
	va_list args;
	glWindowPos2i(x, y);
	va_start(args, format);
	printv(args, format);
	va_end(args);
}
#endif


void writeBitmapString(void *font, char string[])
{
	char *c;
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}