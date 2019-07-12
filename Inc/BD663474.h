/*
*========================================================================================================
*
* File                : BD663474.h
* Hardware Environment: STM32F446
* Build Environment   : Keil uVision 5
* Version             : 1.0
* By                  : Victor Nikitchuk & WaveShare Indian programmers
*
*	Основано на примере для Open16F877A. https://www.waveshare.com/wiki/File:Open16F877A-Demo.7z
*
*========================================================================================================
*/

#ifndef BD663474_H
#define BD663474_H

#include "main.h"
#include <stdio.h>
#include "BD663474_fonts.h"

//Макрос задержки в мс
#define delay_ms(d) HAL_Delay(d)

/* Макросы взаимодействия с портами ввода/вывода */
#define TFT_RESET_Reset		HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET)  
#define TFT_RESET_Set			HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET)
//Опускание/поднятие логического уровня CS дисплея
#define TFT_CS_Reset			HAL_GPIO_WritePin(D_CS_GPIO_Port, D_CS_Pin, GPIO_PIN_RESET)
#define TFT_CS_Set				HAL_GPIO_WritePin(D_CS_GPIO_Port, D_CS_Pin, GPIO_PIN_SET)
//Передача данных/команды в дисплей
#define TFT_data					HAL_GPIO_WritePin(D_RS_GPIO_Port, D_RS_Pin, GPIO_PIN_SET)
#define TFT_index					HAL_GPIO_WritePin(D_RS_GPIO_Port, D_RS_Pin, GPIO_PIN_RESET)

//Включение режима поддержки UTF-8 для вывода текста
#define TFT_UTF8_SUPPORT

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
	TFT_COLOR_clear 					= TFT_COLOR_Black,
};
//Текущий цвет, который установлен функцией TFT_setColor()
#define TFT_COLOR_CURRENT TFT_getColor()

//Ориентации дисплея
enum ORIENTATION {
	TFT_ORIENT_PORTRAIT,			//Портретная ориентация (верх со стороны 1-го пина)
	TFT_ORIENT_LANDSCAPE_180,	//Альбомная ориентация (левый верхний угол со стороны шлейфа тачскрина)
	TFT_ORIENT_PORTRAIT_180,	//Портретная ориентация (верх со стороны 40-го пина)
	TFT_ORIENT_LANDSCAPE, 		//Альбомная ориентация (левый верхний угол со стороны вывода №1)
};


/* Функции работы с дисплеем */
//Аппаратная перезагрузка дисплея
void TFT_reset(void);
//Функция отправки 16 бит данных
void TFT_sendData(uint16_t data);
//Функция отправки команды
void TFT_sendCmd(uint16_t cmd, uint16_t data);
//Инициализация дисплея
#ifndef TFT_SOFTSPI
void TFT_init(uint8_t orientation, SPI_HandleTypeDef *displaySPI);
#endif
#ifdef TFT_SOFTSPI
void TFT_init(uint8_t orientation);
#endif
//Залитие дисплея указанным цветом
void TFT_fillDisplay(uint16_t color);
//Очистка дисплея (залитие белым)
#define TFT_clear() TFT_fillDisplay(TFT_COLOR_clear)
//Установка текущей ориентации
void TFT_setOrientation(uint8_t orientation);


//Установить текущий шрифт написания
void TFT_setFont(TFT_font *font);
//Установить размер шрифта
void TFT_setFontSize(uint8_t size);
//Печать символа на дисплее
void TFT_printChar(char c);
//Печать двухбайтного символа
void TFT_printCharUTF8(uint16_t c);
//Печать строки на дисплее
void TFT_print(uint8_t x, uint8_t y, char str[]);
//Нарисовать картинку на дисплее
void TFT_drawImage(uint16_t width, uint16_t height, const uint16_t *bitmap);
//Выключить дисплей
void TFT_Off(void);
//Включить дисплей
void TFT_On(void);
//Установить текущий цвет кисти
void TFT_setColor(uint16_t color);
//Получить текущий цвет кисти
uint16_t TFT_getColor(void);
//Установить рабочую область от точки (x0,y0) до (x1, y1)
void TFT_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
//Установить координаты курсора по X и Y
void TFT_setCursor(uint16_t X, uint16_t Y);
//Получить текущее положение курсора по X
uint16_t TFT_getCursorX(void);
//Получить текущее положение курсора по Y
uint16_t TFT_getCursorY(void);

//Функция тестирования работы дисплея
void TFT_test(void);

//Закрасить пиксель по координатам X,Y указанным цветом
void TFT_drawPixel(uint16_t x, uint16_t y, uint16_t color);
//Нарисовать линию начиная с x0,y0, заканчивая x1,y1 указанным цветом
void TFT_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t size, uint16_t color);
//Нарисовать горизонтальную линию начиная с точки (x,y) длиной len указанным цветом
void TFT_drawLineHorizontal(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color);
//Нарисовать вертикальную линию начиная с точки (x,y) длиной len указанным цветом
void TFT_drawLineVertical(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color);
//Нарисовать окружность с центром в координате (x,y), радиусом radius и указанным цветом
void TFT_drawCircle(uint16_t x, uint16_t y, uint16_t radius, uint8_t size, uint16_t color);
//Нарисовать прямоугольник начиная с точки (x,y), с указанной шириной, висотой, шириной линии и цветом
void TFT_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint16_t color);
//Нарисовать треугольник по координатам вершин и указанным цветом
void TFT_drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint16_t color);
//Функция для рисования четверти круга с центром (x,y), с указанным радиусом, фазой и цветом
void TFT_drawQuadrant(int16_t x, int16_t y, int16_t radius, uint8_t size, uint8_t c, uint16_t color);
//Нарисовать прямоугольник с скруглёнными углами начиная с точки (x,y), с указанной длиной, шириной, радиусом скругления и цветом
void TFT_drawRoundRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t size, uint16_t color);

//Залить прямоугольник начиная с точки (x,y), с указанной длиной, шириной и цветом
void TFT_fillRectangle(uint16_t x, uint16_t y, uint16_t lenght, uint16_t width, uint16_t color);
//Залить окружность с центром в координате (x,y), радиусом radius и указанным цветом
void TFT_fillCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color);
//Функция для закрашивания четверти круга с центром (x,y), с указанным радиусом, фазой и цветом
void TFT_fillQuadrant(int16_t x, int16_t y, int16_t radius, uint8_t c, int16_t delta, uint16_t color);
//Закрасить прямоугольник с скруглёнными углами начиная с точки (x,y), с указанной длиной, шириной, радиусом скругления и цветом
void TFT_fillRoundRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t color);

/*TODO:
поддержка разных шрифтов высотой более 8 пикс
Добавить функцию рисования закрашенных треугольников
fillRectangle и clear не инкрементирует курсор
заменить табы на пробелы
*/
#endif
