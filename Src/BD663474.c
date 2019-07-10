/*
*========================================================================================================
*
* File                : BD663474.C
* Hardware Environment: STM32F446
* Build Environment   : Keil uVision 5
* Version             : 1.0
* By                  : Victor Nikitchuk & WaveShare Indian programmers
*
*	Основано на примере для Open16F877A. https://www.waveshare.com/wiki/File:Open16F877A-Demo.7z
*
*========================================================================================================
*/

#include "BD663474.h"
#include <stdlib.h>

/* Глобальные переменные */
//Интерфейс SPI для коммуникации с дисплеем
#ifndef TFT_SOFTSPI
SPI_HandleTypeDef *_displaySPI;
#endif
//Размеры дисплея по горизонтали и вертикали (меняются при изменении ориентации экрана)
uint16_t TFT_Width, TFT_Height;
//Текущая ориентация
uint8_t TFT_currentOrientation;
//Текущий цвет кисти
uint16_t currentColor;

//Аппаратная перезагрузка дисплея
void TFT_reset(void) {
	TFT_RESET_Reset;
	delay_ms(1);
	TFT_RESET_Set;
	delay_ms(1);
}
//Инициализация дисплея
#ifndef TFT_SOFTSPI
void TFT_init(uint8_t orientation, SPI_HandleTypeDef *displaySPI) {
	_displaySPI = displaySPI;
#endif
#ifdef TFT_SOFTSPI
void TFT_init(uint8_t orientation) {
#endif
	//Общение на шине именно с дисплеем
	TFT_CS_Reset;
	//Аппаратная перезагрузка дисплея
	TFT_reset();
	
	TFT_sendCmd(0x000,0x0001); //Запуск осциллятора
	delay_ms(10);
	/* Настройки питания */  	
	TFT_sendCmd(0x100, 0x0000);		//Дисплей выключен
	TFT_sendCmd(0x101, 0x0000);		//Тактирование выключено 
	TFT_sendCmd(0x102, 0x3100); 	//Настройка частот преобразователей
	TFT_sendCmd(0x103, 0xe200); 	//Настройка напряжений
	TFT_sendCmd(0x110, 0x009d);		//Настройка апмлитуд переменного напряжения матрицы 
	TFT_sendCmd(0x111, 0x0022);		//Настройка тока 
	TFT_sendCmd(0x100, 0x0120);		//Включение операционных усилителей и запуск генератора градационного напряжения
	delay_ms(20);
	TFT_sendCmd(0x100, 0x3120);		//Включение питания матрицы и всего остального
	delay_ms(80);
	/* Управление дисплеем */   
	TFT_sendCmd(0x001, 0x0100); 	//Ориентация дисплея: 0x0100 - сверху вниз, 0x0000 - снизу вверх. Можно отзеркалить изображение 	
	TFT_sendCmd(0x002, 0x0000);		//Установка формы сигнала драйвера
	TFT_sendCmd(0x003, 0x1230);		//Режим ввода
	//TODO: Команду установки ориентации дисплея
	//0xXXX0 - ввод по короткой стороне (по ширине), 0xXXX8 - по длинной (по длине)
	//0xXXnX - инкремент/декремент по длине и ширине
	TFT_sendCmd(0x006, 0x0000);		//Контроль движения изображения
	TFT_sendCmd(0x007, 0x0101);		//Выключение дисплея как такогого
	TFT_sendCmd(0x008, 0x0808);		//Настройка рамок (?)
	TFT_sendCmd(0x009, 0x0000);		//Настройка сканирования (?)
	TFT_sendCmd(0x00b, 0x0000);		//Настройка количества цветов дисплея. Переключение между 8 цветами и 262k
	TFT_sendCmd(0x00c, 0x0000);		//Настройка интерфейса RGB 
	TFT_sendCmd(0x00d, 0x0010);		//Настройка частоты обновления кадров. 0xXX10 - максимальная, 0xXX1F - минимальная частота
	/* LTPS control settings */   
	TFT_sendCmd(0x012, 0x0000);
	TFT_sendCmd(0x013, 0x0000);	
	TFT_sendCmd(0x018, 0x0000);
	TFT_sendCmd(0x019, 0x0000);

	TFT_sendCmd(0x203, 0x0000);		//Маска записи в GRAM
	TFT_sendCmd(0x204, 0x0000);		//Маска записи в GRAM
	/* Выделение активной области дисплея, в которую будут отправляться данные */
	TFT_sendCmd(0x210, 0x0000);		//Начало по горизонтали
	TFT_sendCmd(0x211, 0x00ef);		//Конец по горизонтали
	TFT_sendCmd(0x212, 0x0000);		//Начало по вертикали
	TFT_sendCmd(0x213, 0x013f);		//Конец по вертикали
	/* Выделение активной области дисплея для движущегося изображения */
	TFT_sendCmd(0x214, 0x0000);		//Начало по горизонтали
	TFT_sendCmd(0x215, 0x0000);		//Конец по горизонтали
	TFT_sendCmd(0x216, 0x0000);		//Начало по вертикали
	TFT_sendCmd(0x217, 0x0000);		//Конец по вертикали
	/* Настройка градации серого */
	TFT_sendCmd(0x300, 0x5343);
	TFT_sendCmd(0x301, 0x1021);
	TFT_sendCmd(0x302, 0x0003);
	TFT_sendCmd(0x303, 0x0011);
	TFT_sendCmd(0x304, 0x050a);
	TFT_sendCmd(0x305, 0x4342);
	TFT_sendCmd(0x306, 0x1100);
	TFT_sendCmd(0x307, 0x0003);
	TFT_sendCmd(0x308, 0x1201);
	TFT_sendCmd(0x309, 0x050a);
	/* Настройка доступа к RAM */ 
	TFT_sendCmd(0x400, 0x4027);
	TFT_sendCmd(0x401, 0x0000);
	TFT_sendCmd(0x402, 0x0000);		/* First screen drive position (1) */   	
	TFT_sendCmd(0x403, 0x013f);		/* First screen drive position (2) */   	
	TFT_sendCmd(0x404, 0x0000);
	//Установка ориентации дисплея
	TFT_setOrientation(orientation);
	/* Установка текущего пикселя */
	TFT_sendCmd(0x200, 0x0000);		//По горизонтали
	TFT_sendCmd(0x201, 0x0000);		//По вертикали
	
	TFT_sendCmd(0x100, 0x7120);		//Включение питания дисплея
	TFT_sendCmd(0x007, 0x0103);		//Разрешение изображения
	delay_ms(10);
	TFT_sendCmd(0x007, 0x0113);		//Включение ключей

	TFT_CS_Set; //Поднятие CS, т.к. общение с дисплеем закончено
}
//Залитие дисплея указанным цветом
void TFT_fillDisplay(uint16_t color) {
	TFT_CS_Reset;	//Общение на шине именно с дисплеем
	
	TFT_setWindow(0,0, TFT_Width-1, TFT_Height-1);
	
	TFT_sendCmd(0x200,0x0000);
	TFT_sendCmd(0x201,0x0000);

	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	
	for (uint32_t i = TFT_Width*TFT_Height; i != 0; i--) {
		TFT_sendData(color);
	}
	TFT_CS_Set; //Поднятие CS, т.к. общение с дисплеем закончено
}

//Функция отправки 16 бит данных
void TFT_sendData(uint16_t data) {
	//Отправка данных по SPI
	#ifndef TFT_SOFTSPI
	//Буффер данных для отправки
	uint8_t buff[2] = {data>>8, (uint8_t)data};
	HAL_SPI_Transmit(_displaySPI, (uint8_t *)buff, 2, 0xFF);
	#endif
	#ifdef TFT_SOFTSPI
	uint16_t mask = 32768;
	for (uint8_t i = 0; i < 16; i++) {
		(data & (mask)) ? TFT_MOSI_Set : TFT_MOSI_Reset;
		TFT_SCK_Set;
		TFT_SCK_Reset;
		mask >>= 1;
	}
	#endif
	
}
//Функция отправки команды
void TFT_sendCmd(uint16_t cmd, uint16_t data) {
	//Установка RS в режим отправки команд
	TFT_index;
	//Отправка команды
	TFT_sendData(cmd);
	//Установка RS в режим отправки данных
	TFT_data;
	//Отправка данных
	TFT_sendData(data);
}

//Установка текущей ориентации
void TFT_setOrientation(uint8_t orientation) {
	TFT_currentOrientation = orientation;
	switch(orientation) {
		//Портретная ориентация (верх со стороны 1-го пина)
		case 0:
			TFT_sendCmd(0x003, 0x10A0);
			TFT_Width = 240;
			TFT_Height = 320;
			break;
		//Альбомная ориентация (левый верхний угол со стороны шлейфа тачскрина)
		case 1:
			TFT_sendCmd(0x003, 0x1098);
			TFT_Width = 320;
			TFT_Height = 240;
			break;
		//Портретная ориентация (верх со стороны 40-го пина)
		case 2:
			TFT_sendCmd(0x003, 0x1080);
			TFT_Width = 240;
			TFT_Height = 320;
			break;
		//Альбомная ориентация (левый верхний угол со стороны вывода №1)
		case 3:
			TFT_sendCmd(0x003, 0x10A8);
			TFT_Width = 320;
			TFT_Height = 240;
			break;
	}
}

//Выключить дисплей
void TFT_Off(void) {
	/*//Display OFF
	TFT_sendCmd(0x007, 0x0112); //D[1:0] = 0b10
	delay_ms(1);
	TFT_sendCmd(0x007, 0x0102);	//DTE = 0
	TFT_sendCmd(0x100, 0x3120); //GON = 0
	//LCD power supply OFF
	TFT_sendCmd(0x100, 0x0000); //SAP = 0, AP[1:0] = 0b00, PON = 1, COM = 0, GON = 0
	delay_ms(1);
	TFT_sendCmd(0x100, 0x0000); //PON = 0
	//Deep standby set
	TFT_sendCmd(0x100, 0x0004);*/
	TFT_RESET_Reset; //Просто сброс дисплея
}
//Включить дисплей
void TFT_On(void) {
	TFT_init(TFT_currentOrientation, _displaySPI);
}
//Установить рабочую область от точки (x0,y0) до (x1, y1)
void TFT_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	uint16_t x0a, x1a, y0a, y1a;

	switch(TFT_currentOrientation) {
		case 1:
			x0a = x0;
			x1a = x1;
			y0a = y0;
			y1a = y1;

			x0 = y0a;
			x1 = y1a;
			y0 = TFT_Width - 1 - x1a;
			y1 = TFT_Width - 1 - x0a;
			break;
		case 2:
			x0a = x0;
			x1a = x1;
			y0a = y0;
			y1a = y1;

			x0 = TFT_Width - 1 - x1a;
			x1 = TFT_Width - 1 - x0a;
			y0 = TFT_Height - 1 - y1a;
			y1 = TFT_Height - 1 - y0a;
			break;
		case 3:
			x0a = x0;
			x1a = x1;
			y0a = y0;
			y1a = y1;

			x0 = TFT_Height - 1 - y1a;
			x1 = TFT_Height - 1 - y0a;
			y0 = x0a;
			y1 = x1a;
			break;
	}
	TFT_sendCmd(0x0210, x0);
	TFT_sendCmd(0x0211, x1);
	TFT_sendCmd(0x0212, y0);
	TFT_sendCmd(0x0213, y1);
	TFT_sendCmd(0x0200, x0);
	TFT_sendCmd(0x0201, y0);
}
//Установить текущий цвет кисти
void TFT_setColor(uint16_t color) {
	currentColor = color;
}
//Получить текущий цвет кисти
uint16_t TFT_getColor(void) {
	return currentColor;
}

//Закрасить пиксель по координатам X,Y указанным цветом
void TFT_drawPixel(uint16_t x, uint16_t y, uint16_t color) {
	TFT_CS_Reset;					//Обращение к дисплею
	TFT_setWindow(x,y,x,y);
	TFT_index;						//Отправка команды
	TFT_sendData(0x202);	//Команда, значащая что дальше начнётся запись в буфер кадра
	TFT_data;							//Отправка данных
	TFT_sendData(color);	//Указание цвета закрашивания пикселя
	TFT_CS_Set;						//Окончание общения с дисплеем
}
//Нарисовать линию начиная с x0,y0, заканчивая x1,y1 указанным цветом
void TFT_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t size, uint16_t color) {
	int16_t dx = abs(x1-x0);
	int16_t sx = x0 < x1 ? 1 : -1;
	int16_t dy = -abs(y1-y0), sy = y0 < y1 ? 1 : -1;
	int16_t err = dx+dy, e2;
	for (;;){
		TFT_fillRectangle(x0,y0,size, size, color);
		e2 = 2*err;
		if (e2 >= dy) {
			if (x0 == x1) break;
			err += dy; x0 += sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) break;
			err += dx; y0 += sy;
		}
	}
}
//Нарисовать горизонтальную линию начиная с точки (x:y) длиной len указанным цветом
void TFT_drawLineHorizontal(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color) {
	TFT_CS_Reset;							//Обращение к дисплею
	TFT_setWindow(x,y,x+len-1,y+size-1);
	TFT_index;								//Отправка команды
	TFT_sendData(0x202);			//Команда, значащая что дальше начнётся запись в буфер кадра
	TFT_data;									//Отправка данных
	for(uint16_t i = 0; i < len*size; i++) TFT_sendData(color); //Рисование линии указанным цветом
	TFT_CS_Set;								//Окончание общения с дисплеем
}
//Нарисовать вертикальную линию начиная с точки (x:y) длиной len указанным цветом
void TFT_drawLineVertical(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color) {
	TFT_CS_Reset;							//Обращение к дисплею
	TFT_setWindow(x,y,x+size-1,y+len-1);
	TFT_index;								//Отправка команды
	TFT_sendData(0x202);			//Команда, значащая что дальше начнётся запись в буфер кадра
	TFT_data;									//Отправка данных
	for(uint16_t i = 0; i < len*size; i++) TFT_sendData(color); //Рисование линии указанным цветом
	TFT_CS_Set;								//Окончание общения с дисплеем
}
//Нарисовать окружность с центром в координате (x,y), радиусом radius и указанным цветом
void TFT_drawCircle(uint16_t x, uint16_t y, uint16_t radius, uint8_t size, uint16_t color) {
	 int16_t x_ = 0;
   int16_t y_ = radius;
   int16_t delta = 1 - 2 * radius;
   int16_t error = 0;
   while (y_ >= 0) {
		 TFT_fillRectangle(x + x_-size+1, y + y_-size, size, size, color);
		 TFT_fillRectangle(x + x_-size+1, y - y_, size, size, color);
		 TFT_fillRectangle(x - x_, y + y_-size, size, size, color);
		 TFT_fillRectangle(x - x_, y - y_, size, size, color);
		 error = 2 * (delta + y_) - 1;
		 if ((delta < 0) && (error <= 0)) {
				 delta += 2 * ++x_ + 1;
				 continue;
		 }
		 if ((delta > 0) && (error > 0)) {
				 delta -= 2 * --y_ + 1;
				 continue;
		 }
		 delta += 2 * (++x_ - y_--);
	 }
}
//Нарисовать прямоугольник начиная с точки (x:y), с указанной шириной, висотой, шириной линии и цветом
void TFT_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint16_t color) {
	TFT_drawLineHorizontal(x, y, width, size, color);
	TFT_drawLineHorizontal(x, y+height-size, width, size, color);
	TFT_drawLineVertical(x, y, height, size, color);
	TFT_drawLineVertical(x+width-size, y, height, size, color);
}
//Нарисовать треугольник по координатам вершин и указанным цветом
void TFT_drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint16_t color) {
	TFT_drawLine(x0, y0, x1, y1, size, color);
	TFT_drawLine(x1, y1, x2, y2, size, color);
	TFT_drawLine(x2, y2, x0, y0, size, color);
}
//Залить прямоугольник начиная с точки (x:y), с указанной длиной, шириной и цветом
void TFT_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
	TFT_CS_Reset;									//Обращение к дисплею
	TFT_setWindow(x,y,x+width-1,y+height-1);
	TFT_index;										//Отправка команды
	TFT_sendData(0x202);					//Команда, значащая что дальше начнётся запись в буфер кадра
	TFT_data;											//Отправка данных
	//Указание цвета закрашивания пикселя	
	for (uint32_t i = width*height; i != 0; i--) {
		TFT_sendData(color);
	}					
	TFT_CS_Set;										//Окончание общения с дисплеем
}
//Залить окружность с центром в координате (x,y), радиусом radius и указанным цветом
void TFT_fillCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color) {
	 int16_t x_ = 0;
   int16_t y_ = radius;
   int16_t delta = 1 - 2 * radius;
   int16_t error = 0;
   while (y_ >= 0) {
		 TFT_drawLineVertical(x - x_, y - y_, y_*2, 1, color);
		 TFT_drawLineVertical(x + x_, y - y_, y_*2, 1, color);
		 
		 error = 2 * (delta + y_) - 1;
		 if ((delta < 0) && (error <= 0)) {
				 delta += 2 * ++x_ + 1;
				 continue;
		 }
		 if ((delta > 0) && (error > 0)) {
				 delta -= 2 * --y_ + 1;
				 continue;
		 }
		 delta += 2 * (++x_ - y_--);
	 }
}
//Функция для рисования четверти круга с центром (x:y), с указанным радиусом, фазой и цветом
void TFT_drawQuadrant(int16_t x, int16_t y, int16_t radius, uint8_t c, uint8_t size, uint16_t color) {
  int16_t f     = 1 - radius;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * radius;
  int16_t x_     = 0;
  int16_t y_     = radius;

  while (x_ < y_) {
    if (f >= 0) {
      y_--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x_++;
    ddF_x += 2;
    f     += ddF_x;
    if (c & 0x4) {
      TFT_fillRectangle(x + x_, y + y_, size, size, color);
      TFT_fillRectangle(x + y_, y + x_, size, size, color);
    }
    if (c & 0x2) {
      TFT_fillRectangle(x + x_, y - y_, size, size, color);
      TFT_fillRectangle(x + y_, y -x_, size, size, color);
    }
    if (c & 0x8) {
      TFT_fillRectangle(x - y_, y + x_, size, size, color);
      TFT_fillRectangle(x - x_, y + y_, size, size, color);
    }
    if (c & 0x1) {
      TFT_fillRectangle(x - y_, y - x_, size, size, color);
      TFT_fillRectangle(x - x_, y - y_, size, size, color);
    }
  }
}

//Нарисовать прямоугольник с скруглёнными углами начиная с точки (x:y), с указанной длиной, шириной, радиусом скругления и цветом
void TFT_drawRoundRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t size, uint16_t color) {
  TFT_drawLineHorizontal(x+radius, y, width-2*radius, size, color); // Top
  TFT_drawLineHorizontal(x+radius, y+height-size, width-2*radius, size, color); // Bottom
  TFT_drawLineVertical(x, y+radius, height-2*radius, size, color); // Left
  TFT_drawLineVertical(x+width-size, y+radius, height-2*radius, size, color); // Right

  TFT_drawQuadrant(x+radius, y+radius, radius,1, size, color);
  TFT_drawQuadrant(x+width-radius-size, y+radius, radius, 2, size, color);
  TFT_drawQuadrant(x+width-radius-size, y+height-radius-size, radius,  4, size, color);
  TFT_drawQuadrant(x+radius, y+height-radius-size, radius, 8, size, color);
}
//Функция для закрашивания четверти круга с центром (x:y), с указанным радиусом, фазой и цветом
void TFT_fillQuadrant(int16_t x, int16_t y, int16_t radius, uint8_t c, int16_t delta, uint16_t color) {
  int16_t f     	= 1 - radius;
  int16_t ddF_x 	= 1;
  int16_t ddF_y 	= -2 * radius;
  int16_t x_     	= 0;
  int16_t y_     	= radius;

  while (x_ < y_) {
    if (f >= 0) {
      y_--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x_++;
    ddF_x += 2;
    f     += ddF_x;

    if (c & 0x1) {
      TFT_drawLineVertical(x+x_, y-y_, 2*y_+1+delta, 1, color);
      TFT_drawLineVertical(x+y_, y-x_, 2*x_+1+delta, 1, color);
    }
    if (c & 0x2) {
     TFT_drawLineVertical(x-x_, y-y_, 2*y_+1+delta, 1, color);
     TFT_drawLineVertical(x-y_, y-x_, 2*x_+1+delta, 1, color);
    }
  }
}

//Закрасить прямоугольник с скруглёнными углами начиная с точки (x:y), с указанной длиной, шириной, радиусом скругления и цветом
void TFT_fillRoundRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t color) {
  TFT_fillRectangle(x+radius, y, width-2*radius, height, color);

  TFT_fillQuadrant(x+width-radius-1, y+radius, radius, 1, height-2*radius-1, color);
  TFT_fillQuadrant(x+radius, y+radius, radius, 2, height-2*radius-1, color);
}
//Функция тестирования работы дисплея
void TFT_test(void) {
	//Массив с всеми основными цветами
	const uint16_t colorfol[]={TFT_COLOR_Black,TFT_COLOR_Gray,TFT_COLOR_Silver,TFT_COLOR_White,TFT_COLOR_Fuchsia,TFT_COLOR_Purple,TFT_COLOR_Red,TFT_COLOR_Maroon,TFT_COLOR_Yellow,TFT_COLOR_Orange,TFT_COLOR_Lime,TFT_COLOR_Green,TFT_COLOR_Aqua,TFT_COLOR_Teal,TFT_COLOR_Blue,TFT_COLOR_Navy};
	//Нужно для печати информации о скорости выполнения теста
	char buff[128];
	uint32_t starttime = HAL_GetTick();
	/* Тест 0. Заливка дисплея сплошным цветом */
	TFT_clear();
	sprintf(buff, "%d", HAL_GetTick()-starttime);
	DisplayString(buff,TFT_Width-1, TFT_Height-1,0);
	HAL_Delay(1500);
	/* Тест 1. Заливка дисплея всеми основными цветами */
	TFT_clear();
	starttime = HAL_GetTick();
	TFT_CS_Reset;	

	TFT_setWindow(0,0, TFT_Width-1, TFT_Height-1);

	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	
	for(uint8_t n = 0; n < 16; n++) {
		for(uint16_t num = TFT_Width/16*TFT_Height; num > 0; num--) TFT_sendData(colorfol[n]);
	}
	TFT_CS_Set;
	sprintf(buff, "%d", HAL_GetTick()-starttime);
	DisplayString(buff,TFT_Width-1, TFT_Height-1,0);
	HAL_Delay(1500);
	/* Тест 2. Рисование лучей от точки (0,0) до противоположных сторон */
	TFT_clear();
	starttime = HAL_GetTick();
	for (uint8_t i = 0; i < 16; i++) TFT_drawLine(0,0, TFT_Width-1, TFT_Height-i*(TFT_Height/16)-1, 2, colorfol[i]);
	for (uint8_t i = 0; i < 16; i++) TFT_drawLine(0,0, TFT_Width-i*(TFT_Width/16)-1, TFT_Height-1, 2, colorfol[i]);
	sprintf(buff, "%d", HAL_GetTick()-starttime);
	DisplayString(buff,TFT_Width-1, TFT_Height-1,0);
	HAL_Delay(1500);
	/* Тест 3. Рисование окружностей разного диаметра */
	TFT_clear();
	starttime = HAL_GetTick();
	for (uint8_t i = 0; i < 16; i++) TFT_drawCircle(TFT_Width/2, TFT_Height/2, 7*i, 2, colorfol[i]);
	sprintf(buff, "%d", HAL_GetTick()-starttime);
	DisplayString(buff,TFT_Width-1, TFT_Height-1,0);
	HAL_Delay(1500);
	/* Тест 4. Рисование прямоугольников разного размера */
	TFT_clear();
	starttime = HAL_GetTick();
	for (uint8_t i = 0; i < 16; i++) TFT_drawRectangle(TFT_Width/32*i, TFT_Height/32*i, TFT_Width-TFT_Width/32*i*2, TFT_Height-TFT_Height/32*i*2, 2, colorfol[i]);  
	sprintf(buff, "%d", HAL_GetTick()-starttime);
	DisplayString(buff,TFT_Width-1, TFT_Height-1,0);
	HAL_Delay(1500);
	/* Тест 5. Рисование скруглённых прямоугольников разного размера */
	TFT_clear();
	starttime = HAL_GetTick();
	for (uint8_t i = 0; i < 16; i++) TFT_drawRoundRect(TFT_Width/32*i, TFT_Height/32*i, TFT_Width-TFT_Width/32*i*2, TFT_Height-TFT_Height/32*i*2, 7, 2, colorfol[i]);  
	sprintf(buff, "%d", HAL_GetTick()-starttime);
	DisplayString(buff,TFT_Width-1, TFT_Height-1,0);
	HAL_Delay(1500);
	/* Тест 6. Рисование треугольников разного размера */
	TFT_clear();
	starttime = HAL_GetTick();
	for (uint8_t i = 0; i < 16; i++) TFT_drawTriangle (TFT_Width/2 - TFT_Width/32*i, TFT_Height-TFT_Height/32*(16-i), TFT_Width/2 + TFT_Width/32*i, TFT_Height-TFT_Height/32*(16-i), TFT_Width/2, TFT_Height/32*(16-i), 2, colorfol[i]);  
	sprintf(buff, "%d", HAL_GetTick()-starttime);
	DisplayString(buff,TFT_Width-1, TFT_Height-1,0);
	HAL_Delay(1500);
	/* Тест 7. Рисование закрашенных геометрических фигур - круг, прямоугольника, скруглённого прямоугольника */
	TFT_clear();
	starttime = HAL_GetTick();
	TFT_fillRoundRect(0, 0, TFT_Width-1, TFT_Height-1, 25, TFT_COLOR_Navy);
	TFT_fillRectangle(TFT_Width/16, TFT_Height/16, TFT_Width/16*14, TFT_Height/16*14, TFT_COLOR_White);
	TFT_fillCircle(TFT_Width/2, TFT_Height/2, TFT_Height/4, TFT_COLOR_Red);
	sprintf(buff, "%d", HAL_GetTick()-starttime);
	DisplayString(buff,TFT_Width-1, TFT_Height-1,0);
	HAL_Delay(1500);
}



void TFT_printChar(uint8_t casc, uint8_t postion_x, uint8_t postion_y) {
	uint8_t i,j,b;
	uint8_t *p;
	
	TFT_CS_Reset;

	TFT_setWindow(postion_x*8,postion_y*16,postion_x*8+7,postion_y*16+15);
	
	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	p=ascii;
	p+=casc*16;
	//8
	for(j=0;j<16;j++)
	{
		b=*(p+j);
		//16
		for(i=0;i<8;i++)
		{
			if(b&0x80)
			{
				TFT_sendData(TFT_COLOR_Black);
			}
			else
			{
				TFT_sendData(TFT_COLOR_Yellow);
			}
			b=b<<1;
			
		}	
	}
	TFT_CS_Set;
}

void TFT_printChar_Reverse(uint8_t casc,uint8_t postion_x,uint8_t postion_y)
{
	uint8_t i,j,b;
	uint8_t *p;
	
	TFT_CS_Reset;
	
	TFT_setWindow(postion_x*8,postion_y*16,postion_x*8+7,postion_y*16+15);
	
	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	p=ascii;
	p+=casc*16;
	//16
	for(j=8;j>0;j--)
	{
		b=*(p+j-1);
		//8
		for(i=0;i<16;i++)
		{
			if(b&0x01)
			{
				TFT_sendData(TFT_COLOR_Black);
			}
			else
			{
				TFT_sendData(TFT_COLOR_Yellow);
			}
			b=b>>1;
			
		}	
	}
	TFT_CS_Set;
}

char* swap(char *s,uint8_t sz)
{
    uint8_t i=0;
    static char b[10]={0};
    s+=sz-2;
    for(i=0;i<sz-1;i++)
    {
        b[i]=*s;
        s--;
    }
    s=b;
    return s;
}

void DisplayString(char *s,uint8_t x,uint8_t y,uint8_t Reverse) {
	char a[10],i;
	if(Reverse)	{
		i=0;
		while(*s){a[i]=*s;s++;i++;}
		s=swap(a,sizeof(a));
	}
	while (*s) { 
		if(Reverse){
			TFT_printChar_Reverse(*s,x,y);
		} else {
			TFT_printChar(*s,x,y);
		}
		//x
		if(++y >= 30) {
			y=0;
			//y
			if(++x >= 20) x = 0;
		}
		s++;
	}
}
