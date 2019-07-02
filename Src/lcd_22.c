 /*
*========================================================================================================
*
* File                : lcd_22.C
* Hardware Environment:
* Build Environment   : MPLAB IDE
* Version             : V8.76
* By                  : Zhou Jie
*
*                                  (c) Copyright 2011-2016, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*========================================================================================================
*/

#include "lcd_22.h"
#include "asciihex8X16.h"

extern SPI_HandleTypeDef hspi1;

volatile xy_t touch_xy_buffer[TOUCH_MAX_CACHE];
volatile u8 touch_wr_index;
volatile u8 touch_rd_index;
volatile u8 touch_counter;


const u16 colorfol[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};
void init_lcd_spi(void)
{
	/*TRISC=0X10;
    
     SSPSTAT=0X80;
     SSPCON=0X30;
    INTCON=0X00;
     PIR1=0X00;*/



    /*SPI_CR1&=(~0x38); 
	SPI_CR1|=0x03;   
	
	//SPI_CR2|=0xc0;   
	SPI_CR2|=0x03;   
	SPI_CR1|=0x04;   
	SPI_CR1|=0x40;   */

}

void init_touch_spi(void)
{
		/*TRISC=0X10;
     SSPSTAT=0X80;
     SSPCON=0X30;
    INTCON=0X00;
     PIR1=0X00;*/
}

#if defined(LCD22_SPI)
void post_data(u16 data)
{
	/*
	//u8 tmp;
	//while(!SSPIF);
	SSPBUF=(u8)(data>>8);
	while(!SSPIF);
	SSPIF=0;
	//tmp=SSPBUF;
	
    //while(!SSPIF);
	SSPBUF=(u8)(data);
	while(!SSPIF);
	SSPIF=0;
	//tmp=SSPBUF;
	*/
	uint8_t buff[2] = {data>>8, (uint8_t)data};
	HAL_SPI_Transmit(&hspi1, (uint8_t *)buff, 2, 0xFF);
}


#endif

void lcd_rst(void) 
{
	reset_clr;
	HAL_Delay(1);
	reset_set;
	HAL_Delay(1);
}

void post_cmd(u16 index, u16 cmd)
{
	en_lcd_index();
	post_data(index);
	en_lcd_data();
	post_data(cmd);
}

void init_lcd(void)
{
	/*u16 x, y;
	touch_counter = 0;
	touch_wr_index = 0;
	touch_rd_index = 0;*/

	init_lcd_spi();
	en_lcd();
	lcd_rst();

	post_cmd( 0x000, 0x0001 ); /* oschilliation start */
	HAL_Delay( 10 );
	/* Power settings */  	
	post_cmd( 0x100, 0x0000 ); /*power supply setup*/	
	post_cmd( 0x101, 0x0000 ); 
	post_cmd( 0x102, 0x3110 ); 
	post_cmd( 0x103, 0xe200 ); 
	post_cmd( 0x110, 0x009d ); 
	post_cmd( 0x111, 0x0022 ); 
	post_cmd( 0x100, 0x0120 ); 
	HAL_Delay( 20 );

	post_cmd( 0x100, 0x3120 );
	HAL_Delay( 80 );
	/* Display control */   
	post_cmd( 0x001, 0x0100 );
	post_cmd( 0x002, 0x0000 );
	post_cmd( 0x003, 0x1230 );
	post_cmd( 0x006, 0x0000 );
	post_cmd( 0x007, 0x0101 );
	post_cmd( 0x008, 0x0808 );
	post_cmd( 0x009, 0x0000 );
	post_cmd( 0x00b, 0x0000 );
	post_cmd( 0x00c, 0x0000 );
	post_cmd( 0x00d, 0x0018 );
	/* LTPS control settings */   
	post_cmd( 0x012, 0x0000 );
	post_cmd( 0x013, 0x0000 );
	post_cmd( 0x018, 0x0000 );
	post_cmd( 0x019, 0x0000 );

	post_cmd( 0x203, 0x0000 );
	post_cmd( 0x204, 0x0000 );

	post_cmd( 0x210, 0x0000 );
	post_cmd( 0x211, 0x00ef );
	post_cmd( 0x212, 0x0000 );
	post_cmd( 0x213, 0x013f );
	post_cmd( 0x214, 0x0000 );
	post_cmd( 0x215, 0x0000 );
	post_cmd( 0x216, 0x0000 );
	post_cmd( 0x217, 0x0000 );

	// Gray scale settings
	post_cmd( 0x300, 0x5343);
	post_cmd( 0x301, 0x1021);
	post_cmd( 0x302, 0x0003);
	post_cmd( 0x303, 0x0011);
	post_cmd( 0x304, 0x050a);
	post_cmd( 0x305, 0x4342);
	post_cmd( 0x306, 0x1100);
	post_cmd( 0x307, 0x0003);
	post_cmd( 0x308, 0x1201);
	post_cmd( 0x309, 0x050a);

	/* RAM access settings */ 
	post_cmd( 0x400, 0x4027 );
	post_cmd( 0x401, 0x0000 );
	post_cmd( 0x402, 0x0000 );	/* First screen drive position (1) */   	
	post_cmd( 0x403, 0x013f );	/* First screen drive position (2) */   	
	post_cmd( 0x404, 0x0000 );

	post_cmd( 0x200, 0x0000 );
	post_cmd( 0x201, 0x0000 );
	
	post_cmd( 0x100, 0x7120 );
	post_cmd( 0x007, 0x0103 );
	HAL_Delay( 10 );
	post_cmd( 0x007, 0x0113 );

	dis_lcd();
}
void LCD_test(void)
{
	u16  temp,num;
	u8 n;//i;

	en_lcd();	

	post_cmd(0x210,0x00);
	post_cmd(0x212,0x0000);
	post_cmd(0x211,0xEF);
	post_cmd(0x213,0x013F);
	
	post_cmd(0x200,0x0000);
	post_cmd(0x201,0x0000);

	en_lcd_index();
	post_data(0x202);
	en_lcd_data();
	for(n=0;n<8;n++)
	{
	    temp=colorfol[n];
		for(num=40*240;num>0;num--)
		{
			post_data(temp);
		}
	}
	HAL_Delay(500);
/*	for(n=0;n<1;n++)
	{
		post_cmd(0x210,0x00);
		post_cmd(0x212,0x0000);
		post_cmd(0x211,0xEF);
		post_cmd(0x213,0x013F);

		post_cmd(0x200,0x0000);
		post_cmd(0x201,0x0000);
		
		en_lcd_index();
		post_data(0x202);
		en_lcd_data();
	    temp=colorfol[n];
		for(i=0;i<240;i++)
		{
			for(num=0;num<320;num++)
			{
		  		post_data(temp);
			}
		}
	//	HAL_Delay(50);
	}*/
	dis_lcd();
}


void DisplayChar(u8 casc,u8 postion_x,u8 postion_y)
{
	u8 i,j,b;
	u8 *p;
	
	en_lcd();
	post_cmd(0x210,postion_x*8); 	//x start point
	post_cmd(0x212,postion_y*16); 	//y start point
	post_cmd(0x211,postion_x*8+7);	//x end point
	post_cmd(0x213,postion_y*16+15);	//y end point
	post_cmd(0x200,postion_x*8);	
	post_cmd(0x201,postion_y*16);
	
	en_lcd_index();
	post_data(0x202);
	en_lcd_data();
	p=ascii;
	p+=casc*16;
	for(j=0;j<16;j++)
	{
		b=*(p+j);
		for(i=0;i<8;i++)
		{
			if(b&0x80)
			{
				post_data(COLOR_BLACK);
			}
			else
			{
				post_data(COLOR_YELLOW);
			}
			b=b<<1;
			
		}	
	}
	dis_lcd();
}

void DisplayChar_Reverse(u8 casc,u8 postion_x,u8 postion_y)
{
	u8 i,j,b;
	u8 *p;
	
	en_lcd();
	post_cmd(0x210,postion_x*8); 	//x start point
	post_cmd(0x212,postion_y*16); 	//y start point
	post_cmd(0x211,postion_x*8+7);	//x end point
	post_cmd(0x213,postion_y*16+15);	//y end point

	post_cmd(0x200,postion_x*8);	
	post_cmd(0x201,postion_y*16);
	
	en_lcd_index();
	post_data(0x202);
	en_lcd_data();
	p=ascii;
	p+=casc*16;
	for(j=16;j>0;j--)
	{
		b=*(p+j-1);
		for(i=0;i<8;i++)
		{
			if(b&0x01)
			{
				post_data(COLOR_BLACK);
			}
			else
			{
				post_data(COLOR_YELLOW);
			}
			b=b>>1;
			
		}	
	}
	dis_lcd();
}

u8* swap(u8 *s,u8 sz)
{
    u8 i=0;
    static u8 b[10]={0};
    s+=sz-2;
    for(i=0;i<sz-1;i++)
    {
        b[i]=*s;
        s--;
    }
    s=b;
    return s;
}

void DisplayString(u8 *s,u8 x,u8 y,u8 Reverse)
{
	u8 a[10],i;
	if(Reverse)
	{
		i=0;
		while(*s){a[i]=*s;s++;i++;}
		s=swap(a,sizeof(a));
	}
	while (*s) 
	{ 
		if(Reverse)
			{DisplayChar_Reverse(*s,x,y);}
		else
			{DisplayChar(*s,x,y);}
		if(++x>=30)
		{
			x=0;
			if(++y>=20)
			{
			  y=0;
			}
		}
		s++;
    }
}
/*
u16 get_touch_data(u16 cmd)
{
	u8 tmp;
	SSPBUF = cmd;
	while(!SSPIF);
	SSPIF=0;

	SSPBUF = 0;
	while(!SSPIF);
	SSPIF=0;

	tmp =SSPBUF;

	SSPBUF = 0;
	while(!SSPIF);
	SSPIF=0;

	return ( ((u16)tmp)<<5 | ((u16)SSPBUF)>>3);
}

xy_t get_touch_xy(void)
{
	xy_t tmp_xy;
	if(!PENIRQ){
		tmp_xy.x = get_touch_data(TOUCH_CMD_X);
	    tmp_xy.y = get_touch_data(TOUCH_CMD_Y);
	} else{
		tmp_xy.x = 0xFFFF;
	    tmp_xy.y = 0xFFFF;
	}
	return tmp_xy;
}

u8 get_point_xy(void)
{
	u8 n,m,tmp;
	xy_t tmp_xy_buf[SAMP_COUNT], tmp_xy;
	u32 tmp_x = ((u32)tmp_xy_buf[SAMP_COUNT/2].x + (u32)tmp_xy_buf[SAMP_COUNT/2-1].x)/2;
	u32 tmp_y = ((u32)tmp_xy_buf[SAMP_COUNT/2].y + (u32)tmp_xy_buf[SAMP_COUNT/2-1].y)/2;
	
	if(touch_counter>=(TOUCH_MAX_CACHE-1)){
		return 0;
	}
	init_touch_spi();
	en_touch();
	xy_t tmp_xy_buf[SAMP_COUNT], tmp_xy;
	for(n=0; n<SAMP_COUNT; n++){
		tmp_xy_buf[n] = get_touch_xy();
	}
	dis_touch();
	for(n=0; n<(SAMP_COUNT-1); n++){
		for(m=0; m<(SAMP_COUNT-n-1); m++){
			tmp = m+1;
			if((tmp_xy_buf[m].x + tmp_xy_buf[m].y) > (tmp_xy_buf[tmp].x + tmp_xy_buf[tmp].y)){
				tmp_xy = tmp_xy_buf[tmp];
				tmp_xy_buf[tmp] = tmp_xy_buf[m];
				tmp_xy_buf[m] = tmp_xy;
			}
		}
	}
	if((tmp_xy_buf[SAMP_COUNT/2].x - tmp_xy_buf[SAMP_COUNT/2-1].x > SAMP_THRESHOLD) 
		|| (tmp_xy_buf[SAMP_COUNT/2].y - tmp_xy_buf[SAMP_COUNT/2-1].y > SAMP_THRESHOLD)){
		return 0;
	}

	if(tmp_x >= 0xFFF || tmp_y >= 0xFFF){
		return 0;
	}
 	touch_xy_buffer[touch_wr_index].x = ((tmp_x * 240)>>12);
	touch_xy_buffer[touch_wr_index].y = ((tmp_y * 320)>>12);
	if(touch_wr_index < (TOUCH_MAX_CACHE-1)){
		touch_wr_index++;
	}else{
		touch_wr_index = 0;
	}
	touch_counter++;
	return 1;
}

u8 draw_lcd(void)
{
	u8 n;
	init_lcd_spi();
	en_lcd();
	if(touch_counter==0){
		return 0;
	}
	
	touch_counter--;

	post_cmd(0x210,touch_xy_buffer[touch_rd_index].x);
	post_cmd(0x212,touch_xy_buffer[touch_rd_index].y);
	post_cmd(0x211,touch_xy_buffer[touch_rd_index].x+(DOT_WIDTH-1));
	post_cmd(0x213,touch_xy_buffer[touch_rd_index].y+(DOT_WIDTH-1));
	if(touch_rd_index < (TOUCH_MAX_CACHE-1)){
		touch_rd_index++;
	}else{
		touch_rd_index = 0;
	}
	//post_cmd(0x0005,0x0010);

	en_lcd_index();
	post_data(0x202);
	en_lcd_data();
	for(n=0; n< (DOT_WIDTH*DOT_WIDTH); n++)
	{
		post_data(COLOR_BLACK);
	}
	dis_lcd();
	return 1;
}
*/
