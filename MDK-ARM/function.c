#include "stdio.h"
#include "LCD.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>

extern const unsigned char gImage_20[12800];
extern const unsigned char gImage_xwl[12808];
extern const unsigned char gImage_cr[12648];
extern const unsigned char gImage_ym[12808];
extern char *name_li[];
extern char *number_li[];


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

;
void function1(int pattern){
	//���ܽ���1
	char* menu[] = {"����ͨ����ʾϵͳ","��ΰ�� 20221071473","���� 20221071019","�וF 20221071345","�밴��1����Ϣ��������", "default"};
	sprintf(menu[5], "ģʽ%d", pattern);
	for(int i=0;i<5;i++){
		LCD_PutString(10, 10+i*(220/6), menu[i], Black, White, 0);
	}
	
	if (pattern != 0){
		printf("KEY%d Press!", pattern);
		printf("A55A%sA5A5", number_li[pattern-1]);
	}
}

void function2(){
	LCD_PutString(40, 80, "����ͨ��ϵͳ", Black, White, 0);
	LCD_PutString(20, 100, "���ڽ��մ�������", Black, White, 0);
	return;
}


void function3(int num){
	//�ڶ���
	/*
	Ŀǰһ�ţ�xwl
			���ţ�cr
			���ţ�ym
	*/
	/*   ������ʾ��Ӧ�����ֺ�ͼƬ begin  */
	//numΪ��Ӧ����ţ�e.g.�����numΪ1 -> xwl����xwl��ͼƬ��ѧ�ţ�����
	LCD_PutString(70, 20, "�յ���ȷ����", Black, White, 0);
	LCD_PutString(100, 40, name_li[num], Black, White, 0);
	LCD_PutString(75, 60, number_li[num], Black, White, 0);
	if (num==1) LCD_Fill_Pic(80, 100, 80, 80, gImage_xwl);
	if (num==2) LCD_Fill_Pic(80, 100, 79, 80, gImage_cr);
	if (num==3) LCD_Fill_Pic(80, 100, 80, 80, gImage_ym);
}


void function4(int pattern){
	/*---------------- PUT UR CODE HERE (FUNCTION4) --------------*/
	
	return;
}
	

int draw_menu(int layer, int target, int pattern){
	/*  LOGIC:
	layer = 0:
		main menu;
	layer = 1, target = 0:
		function1
			press btn1->pattern += 1;
			press btn2->taeget += 1;
			pattern = 0: 
				show pattern 0;
			pattern	= 1:
				show pattern 1, allow strs
			pattern = 2:
				aame;
			pattern = 3:
				same;
	
	layer = 1,target = 1:
		function2
			show text, allow ports
			ports.get(number)->target += 1, ports.send(number);
			ports.get(command)->target -= 1, disable btn1;
	
	layer = 1, target = 2:
		function3
			show texts, show img, show number
			press btn3->target+=1;
	
	layer = 1, target = 3;
		function4
			press btn3->pattern += 1;
		
	
	*/
	
	printf("%d, %d\n", layer, target);
	//char* menu[] = {"Dynamic figures","Circle", "Square", "Picture", "Dot&Line"};
	char* menu[] = {"��ʾ 1","��ʾ 2","��ʾ 3","��ʾ 4", "Undisplay"};
	
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
				function1(pattern);
				return 0;
			case 1:
				function2();
				//draw_two_second_task(target);
				return 1;
			case 2:
				function3(pattern);
				return 0;
			case 3:
				function4(pattern);
				return 1;
			case 4:
				return 0;
			default:
				break;
		}
	}
	return 0;
}

