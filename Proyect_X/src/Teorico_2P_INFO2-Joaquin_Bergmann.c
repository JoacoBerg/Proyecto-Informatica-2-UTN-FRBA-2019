// SEGUNDO PARCIAL INFORMATICA 2
// JOAQUIN BERGMANN
// 29/11/2019

//1)

#define	TOOGLE	((__RW uint32_t*) 0x2009C004)

void TooglePIN(uint8_t port, uint8_t pin)
{	
	TOGGLE[port*8] |= (1<<pin);
}



//2)

//Usarlo como punteros

#define SEC 		*( (__RW uint32_t  * ) 0x40024020)
#define MIN 		*( (__RW uint32_t  * ) 0x40024024)
#define HOUR  		*( (__RW uint32_t  * ) 0x40024028) 
#define DOM		*( (__RW uint32_t  * ) 0x4002402C) 
#define DOW		*( (__RW uint32_t  * ) 0x40024030) 
#define DOY		*( (__RW uint32_t  * ) 0x40024034) 
#define MONTH		*( (__RW uint32_t  * ) 0x40024038) 
#define YEAR		*( (__RW uint32_t  * ) 0x4002403C) 
#define CALIBRATION	*( (__RW uint32_t  * ) 0x40024040)



//Usarlo como estructura

#define		RTC ( (__RW rtc_t* ) 0x40024020L) //Para usar la estructura

typedef struct {
	__RW uint32_t	SEC;
	__RW  uint32_t	MIN;
	__RW uint32_t 	HOUR;
	__RW uint32_t 	DOM;
	__RW uint32_t 	DOW;
	__RW uint32_t 	DOY;
	__RW uint32_t 	MONTH;
	__RW uint32_t 	YEAR;
	__RW uint32_t 	CALIBRATION;
} rtc_t;

rtc_t *RTC = 0x40024020;

