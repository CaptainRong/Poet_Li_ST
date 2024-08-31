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
extern uint8_t func4_part;

extern char k1,k2,k3;
extern int func3_num;


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
	// 功能界面1
	char* menu[] = {"system of Serial Cum 1",
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
		printf("KEY1 Press!\n\rA55A 20221071473 A5A5");
		break;
	case 2:
		LCD_PutString(80,190,"2", Black, White, 0);
		printf("KEY2 Press!\n\rA55A 20221071019 A5A5");
		break;
	case 3:
		LCD_PutString(80,190,"3", Black, White, 0);
		printf("KEY3 Press!\n\rA55A 20221071345 A5A5");
		break;	
	default:
		break;
	}	

}

void function2(){
	LCD_PutString(10, 80, "system of Serial Cum 2", Black, White, 0);
	LCD_PutString(10, 100, "receiving data...", Black, White, 0);

	//按键恢复
	k1 = 1;
    k2 = 1;
    k3 = 1;
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
	LCD_PutString(10, 20, "received right data", Black, White, 0);
	LCD_PutString(100, 40, name_li[num], Black, White, 0);
	LCD_PutString(75, 60, number_li[num], Black, White, 0);
	if (num==0) LCD_Fill_Pic(80, 100, 80, 80, gImage_xwl);
	if (num==1) LCD_Fill_Pic(80, 100, 79, 80, gImage_cr);
	if (num==2) LCD_Fill_Pic(80, 100, 80, 80, gImage_ym);

	printf("k1:%d, k2:%d, k3:%d",k1, k2, k3);
}

// void func4_verify(int NumPattern){
// 	int *list1 = [2,0,2,2,1,0,7,1,0,1,9],
// 		*list2 = [2,0,2,2,1,0,7,1,0,1,9],
// 		*list3 = [2,0,2,2,1,0,7,1,0,1,9];
// 	switch (NumPattern)
// 	{
// 	case 1:
// 		printf("picture A\n")
// 		/* code */

// 		break;
	
// 	default:
// 		break;
// 	}
// }

void function4(){
	/*---------------- PUT UR CODE HERE (FUNCTION4) --------------*/
	LCD_PutString(10, 20, "func 4", Black, White, 0);
	LCD_PutString(10, 70, "receiving data...", Black, White, 0);

	LCD_PutString(10,300,"pattern", Black, White, 0);
	switch (func4_part)
	{
	case 0:
		/* code */
		printf("Null\n");
		LCD_PutString(10,100,"", Black, White, 0);
		LCD_PutString(70,300,"0", Black, White, 0);
		break;
	case 1:
		printf("picture A\n");
		LCD_PutString(80,300,"1", Black, White, 0);
		break;
	case 2:
		printf("picture B\n");
		LCD_PutString(80,300,"2", Black, White, 0);
		break;
	case 3:
		printf("picture C\n");
		LCD_PutString(80,300,"3", Black, White, 0);	
			
		break;	
	default:
		break;
	}
	return;
}
	

int draw_menu(int function1_p, int nuu, int pattern){
	/* 
		function1_p: 功能界面1的模式，0到3
		nuu ： 暂时用不到的变量，又不想大范围改，写完再说吧
	 */
	//ToDo 如果最后nuu用不上，就删了吧
		
	if(pattern == 1){
		//功能界面1的展示
		function1();
	}
	else if (pattern == 2)
	{
		function2();
	}
	else if (pattern == 3)
	{
		/* code */
		function3((func3_num - 1));
	}
	else if (pattern == 4)
	{
		function4();
	}
	
	
	return 0;
}

