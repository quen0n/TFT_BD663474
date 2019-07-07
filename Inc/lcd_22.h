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

//Если вы хотите использовать программный SPI, то раскомментируйте это
//#define TFT_SOFTSPI

//Если вы используете аппаратный SPI, то модифицировать не обязательно
#ifdef TFT_SOFTSPI
#define TFT_MOSI_Set		HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_SET)
#define TFT_MOSI_Reset	HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_RESET)
#define TFT_SCK_Set			HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, GPIO_PIN_SET)
#define TFT_SCK_Reset		HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, GPIO_PIN_RESET)
#endif

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

//Ориентации дисплея
enum ORIENTATION {
	TFT_ORIENT_LANDSCAPE, 		//Альбомная ориентация (левый верхний угол со стороны вывода №1)
	TFT_ORIENT_LANDSCAPE_180,	//Альбомная ориентация (левый верхний угол со стороны шлейфа тачскрина)
	TFT_ORIENT_PORTRAIT,			//Портретная ориентация (верх со стороны 1-го пина)
	TFT_ORIENT_PORTRAIT_180,	//Портретная ориентация (верх со стороны 40-го пина)
};


/* Функции работы с дисплеем */
//Аппаратная перезагрузка дисплея
void TFT_reset(void);
//Функция отправки 16 бит данных
void TFT_sendData(uint16_t data);
//Функция отправки команды
void TFT_sendCmd(uint16_t cmd, uint16_t data) ;
//Инициализация дисплея
#ifndef TFT_SOFTSPI
void TFT_init(uint8_t orientation, SPI_HandleTypeDef *displaySPI);
#endif
#ifdef TFT_SOFTSPI
void TFT_init(uint8_t orientation);
#endif
//Залитие дисплея указанным цветом
void TFT_fill(uint16_t color);
//Очистка дисплея (залитие белым)
#define TFT_clear() TFT_fill(TFT_COLOR_clear)
//Установка текущей ориентации
void TFT_setOrientation(uint8_t orientation);
//Печать символа на дисплее
void TFT_printChar(uint8_t casc, uint8_t postion_x, uint8_t postion_y);
//Выключить дисплей (отправить в глубокий сон)
void TFT_Off(void);
//Включить дисплей (вывести из глубокого сна)
void TFT_On(void);
//Ограничение рабочей области по оси X
void TFT_setColumn(uint16_t startX, uint16_t endX);
//Ограничение рабочей области по оси Y
void TFT_setPage(uint16_t startY, uint16_t endY);
//Закрасить пиксель по координатам X,Y указанным цветом
void TFT_drawPixel(uint16_t x, uint16_t y, uint16_t color);
//Нарисовать линию начиная с x0,y0, заканчивая x1,y1 указанным цветом
void TFT_drawLine(int x0, int y0, int x1, int y1, uint16_t color);
/* Функции работы с тачскрином */


/*TODO: Функции, которые нужно реализовать
+ init(orientation) - в инициализации указывать ориентацию дисплея
+ setOrientation - повернуть дисплей
on/off - включить/выключить дисплей
drawPixel - закрасить отдельный пиксель
drawLine - нарисовать линию
fillScr - залить экран цветом (перереализовать через заливку прямоугольника)
drawRect/circle/RoundRect/Triangle - нарисовать прямоугольник/круг/скруглённый прямоугольник/треугольник
fillRect/circle/RoundRect/Triangle - нарисовать залитый прямоугольник/круг/скруглённый прямоугольник/треугольник
setColor - установить цвет кисти
setXY - установить координаты курсора
setFont - установить текущий шрифт
printChar - напечатать символ
print - напечатать слово
drawBitmap - нарисовать картинку
*/


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
