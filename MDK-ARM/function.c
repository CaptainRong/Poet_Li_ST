#include "stdio.h"
#include "LCD.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>

extern const unsigned char gImage_20[12800];
void draw_circle(int x, int y ,int r, int color, int fill){
	//DrawPixel(x, y, color);
	if (!fill){
		for (int angle = 0; angle < 360; angle++) {
        double radian = angle * 3.14159 / 180.0;
        int x_point = x + r * cos(radian);
        int y_point = y + r * sin(radian);
				DrawPixel(x_point, y_point, color);
		}
	}
	if(fill){
		for(int radious=0;radious<=r;radious++){
			draw_circle(x, y, radious, color, 0);
		}
	}
}

void draw_frame(int x1, int y1, int x2, int y2, int color){
	for(int i=0;i<x2-x1;i++) DrawPixel(x1+i, y1, color);
	for(int j=0;j<y2-y1;j++) DrawPixel(x1, y1+j, color);
	for(int j=0;j<y2-y1;j++) DrawPixel(x2, y1+j, color);
	for(int i=0;i<x2-x1;i++) DrawPixel(x1+i, y2, color);
}
	

int draw_menu(int layer, int target){
	printf("%d, %d\n", layer, target);
	char* menu[] = {"Dynamic figures","Circle", "Square", "Picture", "Dot&Line"};
	if(layer == 0) {
		Lcd_ColorBox(8, 8+target*(300/5), 224, 22, Yellow);
		for(int i=0;i<5;i++){
			LCD_PutString(10, 10+i*(300/5), menu[i], Black, White, 0);
		}
	}
	if(layer == 1) {
		//Lcd_ColorBox(0, 0, 240, 320, White);
		switch(target){
			case 0:
				return 1;
			case 1:
				draw_circle(80, 160, 32, Red, 0);
				draw_circle(160, 160, 32, Blue, 1);
				break;
			case 2:
				Lcd_ColorBox(40, 120, 80, 80, Yellow);
				break;
			case 3:
				LCD_Fill_Pic(50, 130, 80, 80, gImage_20);
				break;
			case 4:
				for(int i=0;i<80;i++) DrawPixel(80+i, 120, Black);
				draw_frame(80, 180, 160, 220, Blue2);
				for (int i = 0; i < 40; i++) {
					int x = rand() % (160 - 80 + 1) + 80;
					int y = rand() % (220 - 180 + 1) + 180;
					DrawPixel(x, y, Cyan);
				}
				break;
			default:
				break;
			}
		}
		return 0;
}

