#include "main.h"

#define XSIZE_PHYS 240
#define YSIZE_PHYS 320


#define LCD_RS         	GPIO_PIN_3	//PE3������TFT --DC RS
#define LCD_CS        	GPIO_PIN_4 	//PE4������TFT --CS
#define LCD_RST     	  GPIO_PIN_1	//PE1������TFT --RST
#define LCD_SCL        	GPIO_PIN_2	//PE2������TFT --CLK
#define LCD_SDA        	GPIO_PIN_6	//PE6������TFT - SDI
#define LCD_SDO        	GPIO_PIN_5	//PE5������TFT - SDO

/***************************************************************************************
#define LCD_RS         	RS_Pin	//PE3������TFT --DC RS
#define LCD_CS        	CS_Pin 	//PE4������TFT --CS
#define LCD_RST     	  RST_Pin	//PE1������TFT --RST
#define LCD_SCL        	CLK_Pin	//PE2������TFT --CLK
#define LCD_SDA        	SDA_Pin	//PE6������TFT - SDI
#define LCD_SDO        	SDO_Pin	//PE5������TFT - SDO
*****************************************************************************************/

#define SPI_CS(a)	\
						if (a)	\
						GPIOE->BSRR=LCD_CS;	\
						else		\
						GPIOE->BRR=LCD_CS ;
#define SPI_DCLK(a)	\
						if (a)	\
						GPIOE->BSRR=LCD_SCL;	\
						else		\
						GPIOE->BRR=LCD_SCL;
#define SPI_SDA(a)	\
						if (a)	\
						GPIOE->BSRR=LCD_SDA;	\
						else		\
						GPIOE->BRR=LCD_SDA;
#define lcd_RS(a)	\
						if (a)	\
						GPIOE->BSRR=LCD_RS;\
						else		\
						GPIOE->BRR=LCD_RS;
						
#define	LCD_RST_SET  	 GPIOE->BSRR=LCD_RST
#define	LCD_RST_CLR  	 GPIOE->BRR=LCD_RST						


						

//*************  24λɫ��1600��ɫ������ *************//
//#define WHITE          0xFFFFFF
//#define BLACK          0x000000
//#define BLUE           0x0000FF
//#define BLUE2          0x3F3FFF
//#define RED            0xFF0000
//#define MAGENTA        0xFF00FF
//#define GREEN          0x00FF00
//#define CYAN           0x00FFFF
//#define YELLOW         0xFFFF00						

//*************  16λɫ���� *************//
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0
						 
						
 void LCD_GPIO_Config(void);
void LCD_Initial(void); //LCD��ʼ������
void LCD_delay(int time);
void WriteComm(unsigned char CMD);
void WriteData(unsigned int dat);
void LCD_WR_REG(unsigned int Index,unsigned int CongfigTemp);
void Lcd_ColorBox(unsigned int xStart,unsigned int yStart,unsigned int xLong,unsigned int yLong,unsigned int Color);
void DrawPixel(unsigned int x, unsigned int y, int Color);
//void SPILCD_DrawLine(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short color);
//void SPILCD_ShowChar(unsigned short x,unsigned short y,unsigned char num, unsigned int fColor, unsigned int bColor,unsigned char flag) ;
void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int fColor, unsigned int bColor,unsigned char flag);
void LCD_Fill_Pic(unsigned int x, unsigned int y,unsigned int pic_H, unsigned int pic_V, const unsigned char*  pic);

