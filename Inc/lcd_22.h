/*
*========================================================================================================
*
* File                : LCD_22.C
* Hardware Environment: STM32F446
* Build Environment   : Keil uVision 5
* Version             : 1.0
* By                  : Victor Nikitchuk & WaveShare Indian programmers
*
*	Основано на примере для Open16F877A. https://www.waveshare.com/wiki/File:Open16F877A-Demo.7z
*
*========================================================================================================
*/

#ifndef LCD_22_H
#define LCD_22_H

#include "main.h"
/* Макросы взаимодействия с портами ввода/вывода */
//Чтение логического уровня на пине прерывания от тачскрина
#define PENIRQ						(HAL_GPIO_ReadPin(T_IRQ_GPIO_Port, T_IRQ_Pin) == GPIO_PIN_SET)
//Опускание/поднятие логического уровня CS тачскрина
#define Touch_CS_Reset		HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_RESET)
#define Touch_CS_Set			HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_SET)
//Опускание/поднятие логического уровня ножки сброса дисплея
#define TFT_RESET_Reset		HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET)  
#define TFT_RESET_Set			HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET)
//Опускание/поднятие логического уровня CS дисплея
#define TFT_CS_Reset			HAL_GPIO_WritePin(D_CS_GPIO_Port, D_CS_Pin, GPIO_PIN_RESET)
#define TFT_CS_Set				HAL_GPIO_WritePin(D_CS_GPIO_Port, D_CS_Pin, GPIO_PIN_SET)
//Передача данных/команды в дисплей
#define TFT_data					HAL_GPIO_WritePin(D_RS_GPIO_Port, D_RS_Pin, GPIO_PIN_SET)
#define TFT_index					HAL_GPIO_WritePin(D_RS_GPIO_Port, D_RS_Pin, GPIO_PIN_RESET)

//Преобразование RGB в 16-ти битный формат 565
#define	TFT_RGB(R, G, B)	(((B >> 3)) | ((G >> 2) << 5) | ((R >> 3) << 11))
//TODO: Разобраться что за макросы
#define SAMP_COUNT				5
#define SAMP_THRESHOLD		5
#define DOT_WIDTH 4
#define TOUCH_CMD_X 		0xD0
#define TOUCH_CMD_Y 		0x90
#define TOUCH_MAX_CACHE 8

//Цвета
enum COLOR{
	TFT_COLOR_Black 					= TFT_RGB(0, 0, 0),
	TFT_COLOR_Gray						= TFT_RGB(24, 24, 24),
	TFT_COLOR_Silver					= TFT_RGB(80, 80, 80),
	TFT_COLOR_White						= TFT_RGB(255, 255, 255),
	TFT_COLOR_Fuchsia					= TFT_RGB(255, 0, 255),
	TFT_COLOR_Purple					= TFT_RGB(64, 0, 64),
	TFT_COLOR_Red							= TFT_RGB(255, 0, 0),
	TFT_COLOR_Maroon					= TFT_RGB(64, 0, 0),
	TFT_COLOR_Yellow					= TFT_RGB(255, 255, 0),
	TFT_COLOR_Orange					= TFT_RGB(128, 64, 0),
	TFT_COLOR_Lime						= TFT_RGB(0, 255, 0),
	TFT_COLOR_Green						= TFT_RGB(0, 64, 0),
	TFT_COLOR_Aqua						= TFT_RGB(0, 255, 255),
	TFT_COLOR_Teal						= TFT_RGB(0, 64, 64),
	TFT_COLOR_Blue						= TFT_RGB(0, 0, 255),
	TFT_COLOR_Navy						= TFT_RGB(0, 0, 32),
	TFT_COLOR_clear 					= TFT_COLOR_White,
};

//Структура для координат нажатия на тачскрин 
typedef struct xy {
	uint16_t x;
	uint16_t y;
} xy_t;

/* Функции работы с дисплеем */
//Аппаратная перезагрузка дисплея
void TFT_reset(void);
//Функция отправки 16 бит данных
void TFT_sendData(uint16_t data);
//Функция отправки команды
void TFT_sendCmd(uint16_t cmd, uint16_t data) ;
//Инициализация дисплея
void TFT_init(SPI_HandleTypeDef *_displaySPI);
//Залитие дисплея указанным цветом
void TFT_fill(uint16_t color);
//Очистка дисплея (залитие белым)
#define TFT_clear() TFT_fill(TFT_COLOR_clear)
/* Функции работы с тачскрином */





//Прочее говно
void post_data(uint16_t data);
void post_cmd(uint16_t index, uint16_t cmd);
/**/
uint16_t get_touch_data(uint16_t cmd);
xy_t get_touch_xy(void);
uint8_t get_point_xy(void);
uint8_t draw_lcd(void);
void init_lcd(void);

void LCD_test(void);

#endif
