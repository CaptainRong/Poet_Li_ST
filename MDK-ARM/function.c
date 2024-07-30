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
extern uint8_t func1_part;


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
void function1(){
	//���ܽ���1
	char* menu[] = {"system of Serial Cum",
		"x w l 20221071473",
		"c r 20221071019",
		"y m 20221071345",
		"press key 1 to send",
		"pattern:"
	 };

	//sprintf(menu[5], "ģʽ%d", pattern);
	for(int i=0;i<6;i++){
		LCD_PutString(10, 10+i*(220/6), menu[i], Black, White, 0);
	}
	//printf("i's value: %d\n",(i*(220/6)));
	switch (func1_part)
	{
	case 0:
		/* code */
		LCD_PutString(80,190,"0", Black, White, 0);
		break;
	case 1:
		LCD_PutString(80,190,"1", Black, White, 0);
		printf("KEY1 Press!\nA55A 20221071473 A5A5");
		break;
	case 2:
		LCD_PutString(80,190,"2", Black, White, 0);
		printf("KEY2 Press!\nA55A 20221071019 A5A5");
		break;
	case 3:
		LCD_PutString(80,190,"3", Black, White, 0);
		printf("KEY3 Press!\nA55A 20221071345 A5A5");
		break;	
	default:
		break;
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
	

int draw_menu(int function1_p, int nuu, int pattern){
	/* 
		function1_p: 功能界面1的模式，0到3
		nuu ： 暂时用不到的变量，又不想大范围改，写完再说吧
	 */
	//ToDo 如果最后nuu用不上，就删了吧
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
	
	//printf("%d, %d\n", layer, target);
	//char* menu[] = {"Dynamic figures","Circle", "Square", "Picture", "Dot&Line"};
	char* menu[] = {"��ʾ 1","��ʾ 2","��ʾ 3","��ʾ 4", "Undisplay"};
	
	/* 应该不会有layer = 1 的情况了	
	if(layer == 0) {
		Lcd_ColorBox(8, 8+target*(300/5), 224, 22, Yellow);
		for(int i=0;i<5;i++){
			LCD_PutString(10, 10+i*(300/5), menu[i], Black, White, 0);
		}
	}
	*/  

	// if(layer == 1) {
	// 	//Lcd_ColorBox(0, 0, 240, 320, White);
	// 	switch(target){
	// 		case 0:
	// 			function1(pattern);
	// 			return 0;
	// 		case 1:
	// 			function2();
	// 			//draw_two_second_task(target);
	// 			return 1;
	// 		case 2:
	// 			function3(pattern);
	// 			return 0;
	// 		case 3:
	// 			function4(pattern);
	// 			return 1;
	// 		case 4:
	// 			return 0;
	// 		default:
	// 			break;
	// 	}
	// }
	if(pattern == 1){
		//功能界面1的展示
		function1();
	}
	return 0;
}

