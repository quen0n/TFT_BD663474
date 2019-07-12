# TFT_BD663474
Библиотека для работы с TFT-дисплеем на контроллере BD663474. 
## Оглавление
* [Общее описание](https://github.com/RainbowKiwiFOX/TFT_BD663474#общее-описание)
* [Описание функций](https://github.com/RainbowKiwiFOX/TFT_BD663474#описание-функций)
	* [Основные функции](https://github.com/RainbowKiwiFOX/TFT_BD663474#основные-функции)
	* [Работа с графикой](https://github.com/RainbowKiwiFOX/TFT_BD663474#работа-с-графикой)
	* [Текст](https://github.com/RainbowKiwiFOX/TFT_BD663474#текст)
	* [Служебные функции](https://github.com/RainbowKiwiFOX/TFT_BD663474#служебные-функции)
* [Подключение](https://github.com/RainbowKiwiFOX/TFT_BD663474#подключение)
* [Использование](https://github.com/RainbowKiwiFOX/TFT_BD663474#использование)
* [Параметры SPI](https://github.com/RainbowKiwiFOX/TFT_BD663474#параметры-spi)
* [Программный SPI](https://github.com/RainbowKiwiFOX/TFT_BD663474#программный-spi)
## Общее описание
Библиотека написана для дисплея [240х320 TFT 2.2 от WaveShare](https://www.waveshare.com/2.2inch-320x240-Touch-LCD-A.htm) на контроллере BD663474. Язык - Си, среда разработки - Keil uVision 5, генератор кода - STM32 CubeMX. В качестве железа была использована отладочная плата [STM32 NUCLEO-F446RE](https://www.st.com/en/evaluation-tools/nucleo-f446re.html) с микроконтроллером STM32F446RET6. Обмен данными организован по SPI. Есть возможность выбора работы на аппаратном или программном SPI. Имеется поддержка UTF-8 (только кириллица). 
## Описание функций
Библиотека содержит основные функции для рисования графики и вывода текста на дисплей. Подробное описание находится в ```BD663474.h```
#### Основные функции
- **```TFT_init(uint8_t orientation, SPI_HandleTypeDef *displaySPI)```** - инициализация дисплея. Во втором аргументе укажите ссылку на интерфейс SPI. В режиме программного SPI второй аргумент отсутствует.
- **```TFT_setOrientation(uint8_t orientation)```** - сменить ориентацию дисплея. Список ориентаций находится в ```BD663474.h```
- **```TFT_reset(void)```** - аппаратная перезагрузка дисплея
- **```TFT_Off(void)```** - выключить дисплей
- **```TFT_On(void)```** - включить дисплей
- **```TFT_clear(void)```** - очистить дисплей
- **```TFT_setColor(uint16_t color)```** - установить текущий цвет рисования. Подходит для текста, например. Список цветов находится в ```BD663474.h```
- **```TFT_getColor(void)```** - получить текущий цвет рисования. Можно использовать макрос ```TFT_COLOR_CURRENT```
- **```TFT_setCursor(uint16_t X, uint16_t Y)```** - установить положение курсора на экране. Подходит для текста
- **```TFT_getCursorX(void), TFT_getCursorY(void)```** - получить текущие значения положения курсора по X и Y
- **```TFT_test(void)```** - функция тестирования дисплея. В коде можно посмотреть как пользоваться теми или иными функциями
- **```TFT_RGB(uint8_t R, uint8_t G, uint8_t B)```** - преобразовать RGB в 16-ти битный формат 565
#### Работа с графикой
- **```TFT_fillDisplay(uint16_t color)```** - залить дисплей указанным цветом
- **```TFT_drawImage(uint16_t width, uint16_t height, const uint16_t *bitmap)```** - нарисовать картинку
- **```TFT_drawPixel(uint16_t x, uint16_t y, uint16_t color)```** - закрасить пиксель по координатам X,Y указанным цветом
- **```TFT_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t size, uint16_t color)```** - нарисовать линию начиная с x0,y0, заканчивая x1,y1 указанным цветом
- **```TFT_drawLineHorizontal(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color)```** - нарисовать горизонтальную линию начиная с точки (x,y) длиной len указанным цветом
- **```TFT_drawLineVertical(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color)```** - нарисовать вертикальную линию начиная с точки (x,y) длиной len указанным цветом
- **```TFT_drawCircle(uint16_t x, uint16_t y, uint16_t radius, uint8_t size, uint16_t color)```** - нарисовать окружность с центром в координате (x,y), радиусом radius и указанным цветом
- **```TFT_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint16_t color)```** - нарисовать прямоугольник начиная с точки (x,y), с указанной шириной, висотой, шириной линии и цветом
- **```TFT_drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint16_t color)```** - нарисовать треугольник по координатам вершин и указанным цветом
- **```TFT_drawQuadrant(int16_t x, int16_t y, int16_t radius, uint8_t size, uint8_t c, uint16_t color)```** - нарисовать четверть круга с центром (x,y), с указанным радиусом, фазой и цветом
- **```TFT_drawRoundRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t size, uint16_t color)```** - нарисовать прямоугольник с скруглёнными углами начиная с точки (x,y), с указанной длиной, шириной, радиусом скругления и цветом
- **```TFT_fillRectangle(uint16_t x, uint16_t y, uint16_t lenght, uint16_t width, uint16_t color)```** - залить прямоугольник начиная с точки (x,y), с указанной длиной, шириной и цветом
- **```TFT_fillCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color)```** - залить окружность с центром в координате (x,y), радиусом radius и указанным цветом
- **```TFT_fillQuadrant(int16_t x, int16_t y, int16_t radius, uint8_t c, int16_t delta, uint16_t color)```** - закрасить четверть круга с центром (x,y), с указанным радиусом, фазой и цветом
- **```TFT_fillRoundRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t color)```** - закрасить прямоугольник с скруглёнными углами начиная с точки (x,y), с указанной длиной, шириной, радиусом скругления и цветом
#### Текст
- **```TFT_setFont(TFT_font *font)```** - установить текущий шрифт текста
- **```TFT_setFontSize(uint8_t size)```** - установить размер шрифта, стандартный размер умножается на указанное число
- **```TFT_printChar(char c)```** - напечатать один символ
- **```TFT_printCharUTF8(uint16_t c)```** - напечатать двухбайтный символ
- **```TFT_print(uint8_t x, uint8_t y, char str[])```** - печать строки начиная с указанной координаты
#### Служебные функции
- **```TFT_sendData(uint16_t data)```** - отправить 2 байта данных на дисплей
- **```TFT_sendCmd(uint16_t cmd, uint16_t data)```** - отправить команду и её данные на дисплей
- **```TFT_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)```** - ограничить рабочую область от (x0,y0) до (x1,y1)

## Подключение
Для подключения используются 5 проводов:
- RESET - ножка сброса дисплея
- CS - chip select, указание контроллеру дисплея что работаем именно с ним
- RS - переключение между отправкой данных/команды
- MOSI - линия данных SPI
- SCK - линия тактирования SPI

После подключения к микроконроллеру, по необходимости, подправьте в ```BD663474.h``` макросы работы с пинами. Если вы используете CubeMX, настройте порты на выход и укажите название пинов RESET, CS и RS как на рисунке:

![](https://pp.userapi.com/c858024/v858024166/14b3b/rmpxXDAfrB4.jpg)

## Использование

Использовать библиотеку достаточно просто. Например:
```c
#include "BD663474.h"

...

int main(void) {

	...

	const unsigned short otter[] ={...};

	TFT_init(TFT_ORIENT_LANDSCAPE, &hspi1);
	TFT_setColor(TFT_COLOR_White);
	TFT_clear();
	
	TFT_setFontSize(3);
	TFT_print(10,0, "Привет, выдра! :)");
	TFT_setCursor(90,100);
	TFT_drawImage(140,105, otter);
	
    ...
}
```
![](https://pp.userapi.com/c858424/v858424412/15667/4GpL9zMbDf8.jpg)

Испытать работу дисплея можно вызвав функцию ```TFT_test(void)```. В ней же можно посмотреть примеры использования остальных функций.

## Параметры SPI
Пример показан на рисунке. Обязательно укажите длину посылки 16 бит. Дисплей прекрасно работает на частоте SPI 45 МГц и ниже, выше 45 МГц испытания не проводились. Использование DMA лишь замедляет работу из-за коротких посылок.

![](https://pp.userapi.com/c858024/v858024166/14b5a/TBG46MGEs18.jpg)

## Программный SPI
Для использования программного SPI раскомментируйте макрос ```TFT_SOFTSPI``` в ```BD663474.h``` и подкорректируйте соответствующие макросы для MOSI и SCK. На STM32 не забудьте установить максимальную частоту тактирования портов.

## FAQ
##### Q: Дисплей не стартует, хоть убейся, что делать?
A: Причин может быть несколько:
1) Плохой контакт соединительных проводов или неправильное подключение.
2) Недостаточное или зашумлённое питание. Попробуйте припаять конденсатор на 1000 мкФ по питанию прямо на гребёнку дисплея.
3) Неправильно указаны макросы для работы с портами или неправильно настроен SPI.

##### Q: Как конвертировать картинку для вывода её на дисплей?
A: Воспользуйтесь [этим](https://github.com/amperka/UTFT/blob/master/Tools/ImageConverter565.exe) конвертором.

##### Q: На дисплее вместо текста отображается ```РРРССРРР ЪУЪ СЪКА```, что делать?

A: Раскомментируйте макрос ```TFT_UTF8_SUPPORT``` в ```BD663474.h```.

##### Q: Вместо текста отображаются закрашенные прямоугольники или вовсе микроконтроллер зависает, что делать?

A: ~~удалить среду разработки~~ Попробуйте воспользоваться другим компилятором. Лично я в Keil uVision рекомендую использовать 6 версию компилятора с такими настройками:

![](https://pp.userapi.com/c849236/v849236534/1ca0a5/iLztrVCnIu8.jpg)
![](https://pp.userapi.com/c849236/v849236534/1ca0ad/bnHQ3a5MCyY.jpg)
#### Q: А как напечатать числа?

A: Вы не слышали про [sprintf](http://www.c-cpp.ru/content/sprintf)? Тогда мы идём к вам!

```c
#include <stdlib.h>
...
int number = 10;

int main(void) {
...
  char buff[5];
  sprintf(buff, "%d", number);
  TFT_print(0,0,buff);
}

```

А можно поступить ещё круче - перегрузить fpuc() и пользоваться [printf](http://www.c-cpp.ru/content/printf):
```c
#include <stdio.h>

...

int fputc(int c, FILE * stream) {
	TFT_printChar(c);
	return c; 
}

...

int main(void) {
	...
	
    float temp = getTemp();
    printf("Temp: %.1fC", temp);
}

```

#### Q: Я хочу использовать эту библиотеку на PIC, AVR, etc, что делать?

A: В ```BD663474.h``` поменяйте значения макросов для работы с портами ввода/вывода и переделайте функцию TFT_sendCmd() под ваше железо. Можно переключиться на программный SPI если хотите очень быстрее адаптироваться.
#### Q: Что с цветами? Почему цвета отображаются как-то пятнисто?
А: Скорее всего дело в скорости работы SPI или нестабильном напряжении питания. Попробуйте, понизить скорость или отключить другие устройства от шины, оставив только дисплей. Так же попробуйте припаять конденсатор на 1000 мкФ по питанию прямо на гребёнку дисплея.

#### Q: У того дисплея есть тачскрин, как его использовать?
А: Тачскрин - это совсем другая история.
## Обратная связь, нужна помощь?
Предложения или найденные баги можно сообщить в Telegram [http://t.me/rainbowkiwifox](http://t.me/rainbowkiwifox), ВКонтакте [https://vk.com/rainbowkiwifox](https://vk.com/rainbowkiwifox) или на почту [rainbowkiwifox@gmail.com](mailto:rainbowkiwifox@gmail.com)
