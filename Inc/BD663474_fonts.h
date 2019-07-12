#ifndef BD663474_FONTS
#define BD663474_FONTS

//Структура шрифта
typedef struct {
	const unsigned char width; 		//Длина
	const unsigned char height;		//Высота
	const unsigned char distance;   //Дистанция между символами
	const unsigned char *bitmap;	//Ссылка на массив
} TFT_font;

static const unsigned char mono5x8_bitmap[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,            // Code for char  
	0x00, 0x00, 0x4F, 0x00, 0x00,            // Code for char !
	0x00, 0x03, 0x00, 0x03, 0x00,            // Code for char "
	0x14, 0x7F, 0x14, 0x7F, 0x14,            // Code for char #
	0x24, 0x2A, 0x7F, 0x2A, 0x12,            // Code for char $
	0x23, 0x13, 0x08, 0x64, 0x62,            // Code for char %
	0x36, 0x49, 0x55, 0x22, 0x50,            // Code for char &
	0x00, 0x05, 0x03, 0x00, 0x00,            // Code for char '
	0x00, 0x1C, 0x22, 0x41, 0x00,            // Code for char (
	0x00, 0x41, 0x22, 0x1C, 0x00,            // Code for char )
	0x14, 0x08, 0x3E, 0x08, 0x14,            // Code for char *
	0x08, 0x08, 0x3E, 0x08, 0x08,            // Code for char +
	0x00, 0x50, 0x30, 0x00, 0x00,            // Code for char ,
	0x08, 0x08, 0x08, 0x08, 0x08,            // Code for char -
	0x00, 0x30, 0x30, 0x00, 0x00,            // Code for char .
	0x00, 0x60, 0x1C, 0x03, 0x00,            // Code for char /
	0x3E, 0x51, 0x49, 0x45, 0x3E,            // Code for char 0
	0x00, 0x42, 0x7F, 0x40, 0x00,            // Code for char 1
	0x42, 0x61, 0x51, 0x49, 0x46,            // Code for char 2
	0x21, 0x41, 0x45, 0x4B, 0x31,            // Code for char 3
	0x18, 0x14, 0x12, 0x7F, 0x10,            // Code for char 4
	0x4F, 0x49, 0x49, 0x49, 0x31,            // Code for char 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,            // Code for char 6
	0x01, 0x71, 0x09, 0x05, 0x03,            // Code for char 7
	0x36, 0x49, 0x49, 0x49, 0x36,            // Code for char 8
	0x06, 0x49, 0x49, 0x29, 0x1E,            // Code for char 9
	0x00, 0x36, 0x36, 0x00, 0x00,            // Code for char :
	0x00, 0xB6, 0x76, 0x00, 0x00,            // Code for char ;
	0x08, 0x14, 0x22, 0x41, 0x00,            // Code for char <
	0x14, 0x14, 0x14, 0x14, 0x14,            // Code for char =
	0x00, 0x41, 0x22, 0x14, 0x08,            // Code for char >
	0x02, 0x01, 0x51, 0x09, 0x06,            // Code for char ?
	0x32, 0x49, 0x79, 0x41, 0x3E,            // Code for char @
	0x7E, 0x11, 0x11, 0x11, 0x7E,            // Code for char A
	0x7F, 0x49, 0x49, 0x49, 0x36,            // Code for char B
	0x3E, 0x41, 0x41, 0x41, 0x22,            // Code for char C
	0x7F, 0x41, 0x41, 0x22, 0x1C,            // Code for char D
	0x7F, 0x49, 0x49, 0x49, 0x41,            // Code for char E
	0x7F, 0x09, 0x09, 0x09, 0x01,            // Code for char F
	0x3E, 0x41, 0x49, 0x49, 0x7A,            // Code for char G
	0x7F, 0x08, 0x08, 0x08, 0x7F,            // Code for char H
	0x00, 0x41, 0x7F, 0x41, 0x00,            // Code for char I
	0x20, 0x40, 0x41, 0x3F, 0x01,            // Code for char J
	0x7F, 0x08, 0x14, 0x22, 0x41,            // Code for char K
	0x7F, 0x40, 0x40, 0x40, 0x60,            // Code for char L
	0x7F, 0x02, 0x0C, 0x02, 0x7F,            // Code for char M
	0x7F, 0x04, 0x08, 0x10, 0x7F,            // Code for char N
	0x3E, 0x41, 0x41, 0x41, 0x3E,            // Code for char O
	0x7F, 0x09, 0x09, 0x09, 0x06,            // Code for char P
	0x3E, 0x41, 0x51, 0x21, 0x5E,            // Code for char Q
	0x7F, 0x09, 0x19, 0x29, 0x46,            // Code for char R
	0x46, 0x49, 0x49, 0x49, 0x31,            // Code for char S
	0x01, 0x01, 0x7F, 0x01, 0x01,            // Code for char T
	0x3F, 0x40, 0x40, 0x40, 0x3F,            // Code for char U
	0x1F, 0x20, 0x40, 0x20, 0x1F,            // Code for char V
	0x3F, 0x40, 0x38, 0x40, 0x3F,            // Code for char W
	0x63, 0x14, 0x08, 0x14, 0x63,            // Code for char X
	0x07, 0x08, 0x70, 0x08, 0x07,            // Code for char Y
	0x61, 0x51, 0x49, 0x45, 0x43,            // Code for char Z
	0x00, 0x7F, 0x41, 0x41, 0x00,            // Code for char [
	0x00, 0x03, 0x1C, 0x60, 0x00,            // Code for char BackSlash 
	0x00, 0x41, 0x41, 0x7F, 0x00,            // Code for char ]
	0x04, 0x02, 0x01, 0x02, 0x04,            // Code for char ^
	0x40, 0x40, 0x40, 0x40, 0x40,            // Code for char _
	0x00, 0x01, 0x02, 0x00, 0x00,            // Code for char `
	0x20, 0x54, 0x54, 0x54, 0x78,            // Code for char a
	0x7F, 0x48, 0x44, 0x44, 0x38,            // Code for char b
	0x38, 0x44, 0x44, 0x44, 0x28,            // Code for char c
	0x38, 0x44, 0x44, 0x48, 0x7F,            // Code for char d
	0x38, 0x54, 0x54, 0x54, 0x18,            // Code for char e
	0x08, 0x7E, 0x09, 0x01, 0x02,            // Code for char f
	0x08, 0x54, 0x54, 0x54, 0x3C,            // Code for char g
	0x7F, 0x10, 0x08, 0x08, 0x70,            // Code for char h
	0x00, 0x44, 0x7D, 0x40, 0x00,            // Code for char i
	0x20, 0x40, 0x44, 0x3D, 0x00,            // Code for char j
	0x7F, 0x10, 0x28, 0x44, 0x00,            // Code for char k
	0x00, 0x41, 0x7F, 0x40, 0x00,            // Code for char l
	0x7C, 0x04, 0x18, 0x04, 0x78,            // Code for char m
	0x7C, 0x08, 0x04, 0x04, 0x78,            // Code for char n
	0x38, 0x44, 0x44, 0x44, 0x38,            // Code for char o
	0x7C, 0x14, 0x14, 0x14, 0x08,            // Code for char p
	0x08, 0x14, 0x14, 0x14, 0x7C,            // Code for char q
	0x7C, 0x08, 0x04, 0x04, 0x08,            // Code for char r
	0x48, 0x54, 0x54, 0x54, 0x20,            // Code for char s
	0x04, 0x3F, 0x44, 0x40, 0x20,            // Code for char t
	0x3C, 0x40, 0x40, 0x20, 0x7C,            // Code for char u
	0x1C, 0x20, 0x40, 0x20, 0x1C,            // Code for char v
	0x3C, 0x40, 0x30, 0x40, 0x3C,            // Code for char w
	0x44, 0x28, 0x10, 0x28, 0x44,            // Code for char x
	0x0C, 0x50, 0x50, 0x50, 0x3C,            // Code for char y
	0x44, 0x64, 0x54, 0x4C, 0x44,            // Code for char z
	0x08, 0x36, 0x41, 0x41, 0x00,            // Code for char {
	0x00, 0x00, 0x7F, 0x00, 0x00,            // Code for char |
	0x00, 0x41, 0x41, 0x36, 0x08,            // Code for char }
	0x10, 0x08, 0x10, 0x10, 0x08,            // Code for char ~
	0x00, 0x7F, 0x41, 0x7F, 0x00,            // Code for char 
	//Кириллица
	//192
	0x7E, 0x11, 0x11, 0x11, 0x7E,            // Code for char А
	0x7F, 0x49, 0x49, 0x49, 0x31,            // Code for char Б
	0x7F, 0x49, 0x49, 0x49, 0x36,            // Code for char В
	0x7F, 0x01, 0x01, 0x01, 0x03,            // Code for char Г
	0x70, 0x29, 0x27, 0x21, 0x7F,            // Code for char Д
	0x7F, 0x49, 0x49, 0x49, 0x00,            // Code for char Е
	0x77, 0x08, 0x7F, 0x08, 0x77,            // Code for char Ж
	0x22, 0x41, 0x49, 0x49, 0x36,            // Code for char З
	0x7F, 0x10, 0x08, 0x04, 0x7F,            // Code for char И
	0x7E, 0x21, 0x12, 0x09, 0x7E,            // Code for char Й
	0x7F, 0x08, 0x14, 0x22, 0x41,            // Code for char К
	0x20, 0x41, 0x3F, 0x01, 0x7F,            // Code for char Л
	0x7F, 0x02, 0x0C, 0x02, 0x7F,            // Code for char М
	0x7F, 0x08, 0x08, 0x08, 0x7F,            // Code for char Н
	0x3E, 0x41, 0x41, 0x41, 0x3E,            // Code for char О
	0x7F, 0x01, 0x01, 0x01, 0x7F,            // Code for char П
	0x7F, 0x09, 0x09, 0x09, 0x06,            // Code for char Р
	0x3E, 0x41, 0x41, 0x41, 0x22,            // Code for char С
	0x01, 0x01, 0x7F, 0x01, 0x01,            // Code for char Т
	0x47, 0x28, 0x10, 0x08, 0x07,            // Code for char У
	0x1C, 0x22, 0x7F, 0x22, 0x1C,            // Code for char Ф
	0x63, 0x14, 0x08, 0x14, 0x63,            // Code for char Х
	0x3F, 0x20, 0x20, 0x3F, 0x60,            // Code for char Ц
	0x07, 0x08, 0x08, 0x08, 0x7F,            // Code for char Ч
	0x7F, 0x40, 0x7E, 0x40, 0x7F,            // Code for char Ш
	0x7F, 0x40, 0x7E, 0x40, 0xFF,            // Code for char Щ
	0x01, 0x7F, 0x48, 0x48, 0x30,            // Code for char Ъ
	0x7F, 0x48, 0x30, 0x00, 0x7F,            // Code for char Ы
	0x00, 0x7F, 0x48, 0x48, 0x30,            // Code for char Ъ
	0x22, 0x41, 0x49, 0x49, 0x3E,            // Code for char Э
	0x7F, 0x08, 0x3E, 0x41, 0x3E,            // Code for char Ю
	0x46, 0x29, 0x19, 0x09, 0x7F,            // Code for char Я
	0x20, 0x54, 0x54, 0x54, 0x78,            // Code for char а
	0x3C, 0x4A, 0x4A, 0x49, 0x31,            // Code for char б
	0x7C, 0x54, 0x54, 0x54, 0x28,            // Code for char в
	0x7C, 0x04, 0x04, 0x04, 0x0C,            // Code for char г
	0xE0, 0x54, 0x4C, 0x44, 0xFC,            // Code for char д
	0x38, 0x54, 0x54, 0x54, 0x18,            // Code for char е
	0x6C, 0x10, 0x7C, 0x10, 0x6C,            // Code for char ж
	0x44, 0x54, 0x54, 0x54, 0x28,            // Code for char з
	0x7C, 0x20, 0x10, 0x08, 0x7C,            // Code for char и
	0x7C, 0x21, 0x12, 0x09, 0x7C,            // Code for char й
	0x7C, 0x10, 0x28, 0x44, 0x00,            // Code for char к
	0x20, 0x44, 0x3C, 0x04, 0x7C,            // Code for char л
	0x7C, 0x08, 0x10, 0x08, 0x7C,            // Code for char м
	0x7C, 0x10, 0x10, 0x10, 0x7C,            // Code for char н
	0x38, 0x44, 0x44, 0x44, 0x38,            // Code for char о
	0x7C, 0x04, 0x04, 0x04, 0x7C,            // Code for char п
	0x7C, 0x14, 0x14, 0x14, 0x08,            // Code for char р
	0x38, 0x44, 0x44, 0x44, 0x20,            // Code for char с
	0x04, 0x04, 0x7C, 0x04, 0x04,            // Code for char т
	0x4C, 0x50, 0x50, 0x50, 0x3C,            // Code for char у
	0x18, 0x24, 0x7C, 0x24, 0x18,            // Code for char ф
	0x44, 0x28, 0x10, 0x28, 0x44,            // Code for char х
	0x3C, 0x20, 0x20, 0x3C, 0x60,            // Code for char ц
	0x0C, 0x10, 0x10, 0x10, 0x7C,            // Code for char ч
	0x7C, 0x40, 0x70, 0x40, 0x7C,            // Code for char ш
	0x7C, 0x40, 0x7C, 0x40, 0xFC,            // Code for char щ
	0x04, 0x7C, 0x50, 0x50, 0x20,            // Code for char ъ
	0x7C, 0x50, 0x20, 0x00, 0x7C,            // Code for char ы
	0x00, 0x7C, 0x50, 0x50, 0x20,            // Code for char ь
	0x28, 0x44, 0x54, 0x54, 0x38,            // Code for char э
	0x7C, 0x10, 0x38, 0x44, 0x38,            // Code for char ю
	0x48, 0x34, 0x14, 0x14, 0x7C,            // Code for char я
};

static TFT_font mono5x8 = {5,8,1,mono5x8_bitmap};

#endif
