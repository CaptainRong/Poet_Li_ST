#include "stdio.h"
#include "LCD.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>
#define LENGTH 21

extern const unsigned char gImage_0[24584];
extern const unsigned char gImage_1[24584];
extern const unsigned char gImage_2[24584];
extern const unsigned char gImage_3[24584];
extern const unsigned char gImage_4[24584];
extern const unsigned char gImage_5[24584];
extern const unsigned char gImage_6[24584];
extern const unsigned char gImage_7[24584];
extern const unsigned char gImage_8[24584];
extern const unsigned char gImage_9[24584];

extern const unsigned char gImage_A[17608];
extern const unsigned char gImage_B[14364];
extern const unsigned char gImage_C[13508];

extern const unsigned char gImage_xwl[12808];
extern const unsigned char gImage_cr[12648];
extern const unsigned char gImage_ym[12808];
extern char *name_li[];
extern char *number_li[];
extern uint8_t func1_part;
extern uint8_t func4_part;
extern uint8_t uart_dma_temp_rx[LENGTH];

extern char k1,k2,k3;
extern int func3_num;
extern int func4_show;

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
	// 鍔熻兘鐣岄潰1
	char* menu[] = {"串口通信系统",
		"徐伟凌20221071473",
		"曹  荣20221071019",
		"易  旻20221071345",
		"请按键1将信息发到串口",
		"模式:"
	 };

	//sprintf(menu[5], "模式%d", pattern);
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
	LCD_PutString(10, 80, "串口通信系统", Black, White, 0);
	LCD_PutString(10, 100, "正在接收串口数据", Black, White, 0);

	//鎸夐敭鎭㈠??
	k1 = 1;
    k2 = 1;
    k3 = 1;
	return;
}


void function3(int num){
	//锟节讹拷锟斤拷
	/*
	目前一锟脚ｏ拷xwl
			锟斤拷锟脚ｏ拷cr
			锟斤拷锟脚ｏ拷ym
	*/
	/*   锟斤拷锟斤拷锟斤拷示锟斤拷应锟斤拷锟斤拷锟街猴拷图片 begin  */
	//num为锟斤拷应锟斤拷锟斤拷牛锟絜.g.锟斤拷锟斤拷锟絥um为1 -> xwl锟斤拷锟斤拷xwl锟斤拷图片锟斤拷学锟脚ｏ拷锟斤拷锟斤拷
	LCD_PutString(10, 20, "收到正确数据", Black, White, 0);
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
	LCD_PutString(10, 70, "正在接收数据...", Black, White, 0);
	
	LCD_PutString(10,300,"模式", Black, White, 0);
	
	if (func4_show == 10){
		switch (func4_part){
	case 0:
		/* code */
		LCD_PutString(10,100,"", Black, White, 0);
		LCD_PutString(70,300,"0", Black, White, 0);
		break;
	case 1:
		LCD_PutString(80,300,"1", Black, White, 0);
		LCD_Fill_Pic(80, 100, 80, 110, gImage_A);
			
		break;
	case 2:
		LCD_PutString(80,300,"2", Black, White, 0);
		LCD_Fill_Pic(83, 100, 74, 97, gImage_B);
		break;
	case 3:
		LCD_PutString(80,300,"3", Black, White, 0);	
		LCD_Fill_Pic(75, 100, 90, 75, gImage_C);
		break;	
	default:
		break;
	}
	}
	else{
		switch(func4_show)
		{
			case 0:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_0);
				break;
			case 1:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_1);
				break;
			case 2:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_2);
				break;
			case 3:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_3);
				break;
			case 4:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_4);
				break;
			case 5:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_5);
				break;
			case 6:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_6);
				break;
			case 7:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_7);
				break;
			case 8:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_8);
				break;
			case 9:
				LCD_Fill_Pic(40, 100, 128, 96, gImage_9);
				break;
			default:
				LCD_PutString(60, 100, "*oops!There's sth wrong ;)*", Black, White, 0);
				break;
		}
	}
	return;
}
	

int draw_menu(int function1_p, int nuu, int pattern){
	/* 
		function1_p: 鍔熻兘鐣岄潰1鐨勬ā寮忥紝0鍒?3
		nuu 锛? 鏆傛椂鐢ㄤ笉鍒扮殑鍙橀噺锛屽張涓嶆兂澶ц寖鍥存敼锛屽啓瀹屽啀璇村惂
	 */
	//ToDo 濡傛灉鏈�鍚巒uu鐢ㄤ笉涓婏紝灏卞垹浜嗗惂
		
	if(pattern == 1){
		//鍔熻兘鐣岄潰1鐨勫睍绀?
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

