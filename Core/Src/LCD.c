#include "stdio.h"					// ��׼C�⺯��ͷ�ļ� 
#include "string.h"
#include "LCD.h"
#include "ASCII.h"
#include "GB1616.h"	//16*16������ģ
#include "lcm_font.h"


/***************************************************************************************
#define LCD_RS         	GPIO_PIN_3	//PE3������TFT --DC RS
#define LCD_CS        	GPIO_PIN_4 	//PE4������TFT --CS
#define LCD_RST     	  GPIO_PIN_1	//PE1������TFT --RST
#define LCD_SCL        	GPIO_PIN_2	//PE2������TFT --CLK
#define LCD_SDA        	GPIO_PIN_6	//PE6������TFT - SDI
#define LCD_SDO        	GPIO_PIN_5	//PE5������TFT - SDO
****************************************************************************************/


void LCD_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOE_CLK_ENABLE();					//����GPIOBʱ��


	GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;		
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//�������
	GPIO_Initure.Pull=GPIO_PULLUP;         			//����
  GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//����
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_SET);

}

/****************************************************************************
* ��    �ƣ�void Lcd_Reset(void)
* ��    �ܣ�Һ��Ӳ��λ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��ǰ��ִ��һ�θ�λ����
****************************************************************************/
void Lcd_Reset(void)
{
	LCD_RST_CLR;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(50);
}

void LCD_delay(int time)  //����� ��ʱ����
{
	for (volatile uint32_t i = 0; i < time; i++)
    {
        // Change the value of j to adjust different System clock terms.
        for (volatile uint32_t j = 0; j < 1000; j++)
        {
            __NOP(); // use NOP to avoid it from being optimized.
        }
    }
}
void LCD_WriteByteSPI(unsigned char byte) //SPIģ�⺯����дһ��8bit������
{
	  unsigned char buf;
    unsigned char i;
    for(i=0;i<8;i++) 
    {
        buf=(byte>>(7-i))&0x1;
				SPI_DCLK(0);
        SPI_SDA(buf);
        SPI_DCLK(1);
    }	
		
}
void LCD_WriteRegIndex(unsigned char Index) //д����Ĳ���
{
	SPI_CS(0);
	LCD_WriteByteSPI(0X70);
	LCD_WriteByteSPI(0);
	LCD_WriteByteSPI(Index);
	SPI_CS(1);
}
void LCD_WriteData(unsigned short dat) //д����
{
	SPI_CS(0);
	LCD_WriteByteSPI(0X72);
  LCD_WriteByteSPI(dat>>8);		//	start byte RS=1,RW=0----Write a GRAM data
  LCD_WriteByteSPI(dat);
	SPI_CS(1);
}
/******************************************
��������Lcdд�����
���ܣ���Lcdָ��λ��д��Ӧ�����������
��ڲ�����Index ҪѰַ�ļĴ�����ַ
          ConfigTemp д������ݻ�����ֵ
******************************************/
void LCD_WR_REG(unsigned int Index,unsigned int CongfigTemp)
{
	LCD_WriteRegIndex(Index);
	LCD_WriteData(CongfigTemp);
}
/*************************************************
��������Lcd�����㶨λ����
���ܣ�ָ��320240Һ���ϵ�һ����Ϊд���ݵ���ʼ��
��ڲ�����x ���� 0~239
          y ���� 0~319
����ֵ����
*************************************************/
void Lcd_SetCursor(unsigned short x,unsigned short y)
{ 
  LCD_WriteRegIndex(0x20);
  LCD_WriteData(x);//ˮƽ����
  LCD_WriteRegIndex(0x21);
  LCD_WriteData(y);//��ֱ���� 
} 
/**********************************************
����������������

��ڲ�����XStart x��������
          Xend   x������յ�
					YStart y��������
          Yend   y������յ�

��������������ǣ���һ�����ο򣬷����������������������
***********************************************/
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) 
{
	//ILI9328
	
	LCD_WR_REG(0x0050,Xstart);//ˮƽGRAM��ʼλ��
	LCD_WR_REG(0x0051,Xend); //ˮƽGRAM��ֹλ��
	LCD_WR_REG(0x0052,Ystart);//��ֱ GRAM��ʼλ��
	LCD_WR_REG(0x0053,Yend); //��ֱGRAM��ֹλ��
	
	Lcd_SetCursor(Xstart, Ystart);
	
  LCD_WriteRegIndex(0x022);

}
/**********************************************
��������Lcd������亯��

��ڲ�����xStart x�������ʼ��
          ySrart y�������ֹ��
          xLong Ҫѡ�����ε�x���򳤶�
          yLong  Ҫѡ�����ε�y���򳤶�
����ֵ����
***********************************************/
void Lcd_ColorBox(unsigned int xStart,unsigned int yStart,unsigned int xLong,unsigned int yLong,unsigned int Color)
{
		unsigned int temp;

	BlockWrite(xStart,xStart+xLong-1,yStart,yStart+yLong-1);
	SPI_CS(0);
	LCD_WriteByteSPI(0X72);
	for (temp=0; temp<xLong*yLong; temp++)
	{
		LCD_WriteByteSPI(Color>>8);		//	start byte RS=1,RW=0----Write a GRAM data
		LCD_WriteByteSPI(Color);
	}
	SPI_CS(1);
}
void LCD_Initial(void) //LCD��ʼ������
{
Lcd_Reset();
//************* Start Initial Sequence **********//
LCD_WR_REG(0x0001, 0x0000); // set SS and SM bit
LCD_WR_REG(0x0002, 0x0700); // set 1 line inversion
LCD_WR_REG(0x0003, 0x1030); // set GRAM write direction and BGR=1.  0001 0000 0011 0000
LCD_WR_REG(0x0004, 0x0000); // Resize register
LCD_WR_REG(0x0008, 0x0202); // set the back porch and front porch
LCD_WR_REG(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
LCD_WR_REG(0x000A, 0x0000); // FMARK function
LCD_WR_REG(0x000C, 0x0000); // RGB interface setting
LCD_WR_REG(0x000D, 0x0000); // Frame marker Position
LCD_WR_REG(0x000F, 0x0000); // RGB interface polarity
//*************Power On sequence ****************//
LCD_WR_REG(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
LCD_WR_REG(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
LCD_WR_REG(0x0012, 0x0000); // VREG1OUT voltage
LCD_WR_REG(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
LCD_WR_REG(0x0007, 0x0001);
HAL_Delay(200); // Dis-charge capacitor power voltage
LCD_WR_REG(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
LCD_WR_REG(0x0011, 0x0227); // Set DC1[2:0], DC0[2:0], VC[2:0]
HAL_Delay(50); // Delay 50ms
LCD_WR_REG(0x0012, 0x009D); // External reference voltage= Vci;
HAL_Delay(50); // Delay 50ms
LCD_WR_REG(0x0013, 0x1A00); // VDV[4:0] for VCOM amplitude
LCD_WR_REG(0x0029, 0x001D); // VCM[5:0] for VCOMH
LCD_WR_REG(0x002B, 0x000D); // Set Frame Rate
HAL_Delay(50); // Delay 50ms
LCD_WR_REG(0x0020, 0x0000); // GRAM horizontal Address
LCD_WR_REG(0x0021, 0x0000); // GRAM Vertical Address
// ----------- Adjust the Gamma Curve ----------//
LCD_WR_REG(0x0030, 0x0000);
LCD_WR_REG(0x0031, 0x0607);
LCD_WR_REG(0x0032, 0x0305);
LCD_WR_REG(0x0035, 0x0000);
LCD_WR_REG(0x0036, 0x1604);
LCD_WR_REG(0x0037, 0x0204);
LCD_WR_REG(0x0038, 0x0001);
LCD_WR_REG(0x0039, 0x0707);
LCD_WR_REG(0x003C, 0x0000);
LCD_WR_REG(0x003D, 0x000F);
//------------------ Set GRAM area ---------------//
LCD_WR_REG(0x0050, 0x0000); // Horizontal GRAM Start Address
LCD_WR_REG(0x0051, 0x00EF); // Horizontal GRAM End Address
LCD_WR_REG(0x0052, 0x0000); // Vertical GRAM Start Address
LCD_WR_REG(0x0053, 0x013F); // Vertical GRAM Start Address
LCD_WR_REG(0x0060, 0x2700); // Gate Scan Line  
LCD_WR_REG(0x0061, 0x0001); // NDL,VLE, REV

LCD_WR_REG(0x006A, 0x0000); // set scrolling line
//-------------- Partial Display Control ---------//
LCD_WR_REG(0x0080, 0x0000);
LCD_WR_REG(0x0081, 0x0000);
LCD_WR_REG(0x0082, 0x0000);
LCD_WR_REG(0x0083, 0x0000);
LCD_WR_REG(0x0084, 0x0000);
LCD_WR_REG(0x0085, 0x0000);
//-------------- Panel Control -------------------//
LCD_WR_REG(0x0090, 0x0010);
LCD_WR_REG(0x0092, 0x0600);
LCD_WR_REG(0x0007, 0x0133); // 262K color and display ON
HAL_Delay(10);

	//============���ҵ�����µ���============//
//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1008);//MX, MY, RGB mode

	//============�����Ҵ��µ���============//
//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1018);//MX, MY, RGB mode

	//============���ҵ�����ϵ���============//
//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1028);//MX, MY, RGB mode

	//============�����Ҵ��ϵ���============//
//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1038);//MX, MY, RGB mode

	
	//============�����Ҵ��ϵ���============//
//	LCD_WR_REG(0x0001, 0x0100);// set SS and SM bit
//	LCD_WR_REG(0x03,0x1030);//MX, MY, RGB mode set GRAM write direction and BGR=1.
	
//	Lcd_Light_ON;//�򿪱���

//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1008);//MX, MY, RGB mode


}
/******************************************
��������Lcdͼ�����
���ܣ���Lcdָ��λ�����ͼ��
��ڲ�����
					(x,y): ͼƬ���Ͻ���ʼ����
					(pic_H,pic_V): ͼƬ�Ŀ��
					 pic  ָ��洢ͼƬ�����ָ��
******************************************/
void LCD_Fill_Pic(unsigned int x, unsigned int y,unsigned int pic_H, unsigned int pic_V, const unsigned char*  pic)
{
	//DMA ��ʽ
//	BlockWrite(x,x+pic_H-1,y,y+pic_V-1);
//	TK80_DMA_Init((u32)pic,pic_H*pic_V);//DMA��ʼ��
//	while((DMA2->ISR & 0x20)==0);
//	DMA2->IFCR |=1<<5;
	
	//========= ��ѯ��ʽ=========//
  unsigned long i;
	unsigned long j;
	BlockWrite(x,x+pic_H-1,y,y+pic_V-1);
	j= pic_H*pic_V*2;
	SPI_CS(0);
	LCD_WriteByteSPI(0X72);
	for (i = 0; i <j; i++) 
	{
		LCD_WriteByteSPI(pic[i]);
	}
	SPI_CS(1);
}
//=============== ��x��y �����ϴ�һ����ɫΪColor�ĵ� ===============
void DrawPixel(unsigned int x, unsigned int y, int Color)
{
	BlockWrite(x,x,y,y); 
  SPI_CS(0);
	LCD_WriteByteSPI(0X72);
	LCD_WriteByteSPI(Color>>8);
	LCD_WriteByteSPI(Color);
	SPI_CS(1);
}

/**********8*16���� ASCII�� ��ʾ*************
(x,y): ��ʾ��ĸ����ʼ����
num:   Ҫ��ʾ���ַ�:" "--->"~"
fColor ǰ��ɫ
bColor ����ɫ
flag:  �б���ɫ(1)�ޱ���ɫ(0)
*********************************************/
void SPILCD_ShowChar(unsigned short x,unsigned short y,unsigned char num, unsigned int fColor, unsigned int bColor,unsigned char flag) 
{       
	unsigned char temp;
	unsigned int pos,i,j;  

	num=num-' ';//�õ�ƫ�ƺ��ֵ
	i=num*16; 	
	for(pos=0;pos<16;pos++)
		{
			temp=nAsciiDot[i+pos];	//��ͨ����ASCII����
			for(j=0;j<8;j++)
		   {                 
		        if(temp&0x80)
							DrawPixel(x+j,y,fColor);
						else 
							if(flag) DrawPixel(x+j,y,bColor); //�������ɫ��־flagΪ1
							temp<<=1; 
		    }
			 y++;
		}		 
}  

/**********дһ��16x16�ĺ���*****************
(x,y): ��ʾ���ֵ���ʼ����
c[2]:  Ҫ��ʾ�ĺ���
fColor ǰ��ɫ
bColor ����ɫ
flag:  �б���ɫ(1)�ޱ���ɫ(0)
*********************************************/
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor,unsigned char flag)
{
	unsigned int i,j,k;
	unsigned short m;
	for (k=0;k<200;k++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
	  if ((codeGB_16[k].Index[0]==c[0])&&(codeGB_16[k].Index[1]==c[1]))
			{ 
    	for(i=0;i<32;i++) 
			{
				m=codeGB_16[k].Msk[i];
				for(j=0;j<8;j++) 
				{		
					if((m&0x80)==0x80) {
						DrawPixel(x+j,y,fColor);
						}
					else {
						if(flag) DrawPixel(x+j,y,bColor);
						}
					m=m<<1;
				} 
				if(i%2){y++;x=x-8;}
				else x=x+8;
		  }
		}  
	  }	
	}
/**********��ʾһ����*****************
(x,y): �ַ�������ʼ����
*s:    Ҫ��ʾ���ַ���ָ��
fColor ǰ��ɫ
bColor ����ɫ
flag:  �б���ɫ(1)�ޱ���ɫ(0)
*********************************************/
void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int fColor, unsigned int bColor,unsigned char flag) 
	{
		unsigned char l=0;
		while(*s) 
			{
				if( (unsigned char)*s < 0x80) 
						{
							SPILCD_ShowChar(x+l*8,y,*s,fColor,bColor,flag);
							s++;l++;
						}
				else
						{
							PutGB1616(x+l*8,y,(unsigned char*)s,fColor,bColor,flag);
							s+=2;l+=2;
						}
			}
	}

