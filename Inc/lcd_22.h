#ifndef LCD_22_H
#define LCD_22_H

#include "main.h"

#define u16 uint16_t
#define u8 uint8_t 

#define LCD22_SPI

#define PENIRQ						(HAL_GPIO_ReadPin(T_IRQ_GPIO_Port, T_IRQ_Pin) == GPIO_PIN_SET) //RA0   //IN

#define en_touch()				HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_RESET)	//{RA4=0;}// T_CS 
#define dis_touch()				HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_SET)	//{RA4=1;}

#define reset_clr					HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET)	//{RD0=0;}//RST    
#define reset_set					HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET)	//{RD0=1;}//

#define en_lcd()					HAL_GPIO_WritePin(D_CS_GPIO_Port, D_CS_Pin, GPIO_PIN_RESET)	//{RA1=0;}// CS
#define dis_lcd()					HAL_GPIO_WritePin(D_CS_GPIO_Port, D_CS_Pin, GPIO_PIN_SET)	//{RA1=1;}//

#define en_lcd_data()			HAL_GPIO_WritePin(D_RS_GPIO_Port, D_RS_Pin, GPIO_PIN_SET)	//{RA2=1;}// RS
#define en_lcd_index()		HAL_GPIO_WritePin(D_RS_GPIO_Port, D_RS_Pin, GPIO_PIN_RESET)	//{RA2=0;}//

#define SAMP_COUNT				5
#define SAMP_THRESHOLD		5

#define TOUCH_CMD_X 		0xD0
#define TOUCH_CMD_Y 		0x90

#define COLOR_YELLOW 		0xFFE0
#define COLOR_BLACK 		0x0000
#define COLOR_WHITE 		0xFFFF
#define COLOR_INIT 			COLOR_YELLOW

#define DOT_WIDTH 4

typedef struct xy
{
	u16 x;
	u16 y;
}xy_t;

#define TOUCH_MAX_CACHE 8
/**/
void init_lcd_spi(void);
void init_touch_spi(void);
void post_data(u16 data);
void post_cmd(u16 index, u16 cmd);
/**/
u16 get_touch_data(u16 cmd);
xy_t get_touch_xy(void);
u8 get_point_xy(void);
u8 draw_lcd(void);
void init_lcd(void);

void LCD_test(void);
#endif
