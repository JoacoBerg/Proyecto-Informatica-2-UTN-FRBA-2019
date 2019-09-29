//STCTRL - 0xE000 E010
//STRELOAD - 0xE000 E014
//STCURR - 0xE000 E018
//diferencia 4 -->estan por bytes el hexa

#include <DR_PINSEL.h>
#include <DR_tipos.h>
#include "DR_PLL.h"

#define PWM_DIVISOR 20000// en vez de 1000 lo ponemos en 20000 para que tenga un ciclo de 20 ms para el servo

void updatePulseWidth(uint8_t num, uint32_t pulseWidth);
void PWM_Init(void);


typedef struct{
	__RW uint32_t PWM1IR;
	union{
		__RW uint32_t PWM1TCR;
		struct{
			__RW uint32_t TCR_CountENA:1;
			__RW uint32_t TCR_CountRST:1;
			__RW uint32_t RESERVED_5:1;
			__RW uint32_t TCR_PWMENA:1;
			__RW uint32_t RESERVED_6:28;
		};
	};
	__RW uint32_t PWM1TC;
	__RW uint32_t PWM1PR;			//PWMPRESCALE = 1 micro-second resolution
	__RW uint32_t PWM1PC;
	union{
		__RW uint32_t PWM1MCR;
		struct{
			__RW uint32_t PWMMR0I:1;
			__RW uint32_t PWMMR0R:1;
			__RW uint32_t PWMMR0S:1;
			__RW uint32_t PWMMR1:3; //despues mejorar y separar en 3 como arriba (PWMMR0I, PWMMR0R, PWMMR0S)
			__RW uint32_t PWMMR2:3;
			__RW uint32_t PWMMR3:3;
			__RW uint32_t PWMMR4:3;
			__RW uint32_t PWMMR5:3;
			__RW uint32_t PWMMR6:3;
			__RW uint32_t RESERVED_2:11;
		};
	};
	__RW uint32_t PWM1MR0;			//period or PWM_DIVISOR
	__RW uint32_t PWM1MR1;			//1.1 dividendo
	__RW uint32_t PWM1MR2;			//1.2 dividendo
	__RW uint32_t PWM1MR3;			//1.3 dividendo
	__RW uint32_t PWM1CCR;
	__RW uint32_t PWM1CR0;
	__RW uint32_t PWM1CR1;
	__RW uint32_t PWM1CR2;
	__RW uint32_t PWM1CR3;
	__RW uint32_t RESERVED_0;
	__RW uint32_t PWM1MR4;			//1.4 dividendo
	__RW uint32_t PWM1MR5;			//1.5 dividendo
	__RW uint32_t PWM1MR6;			//1.6 dividendo
	union{
		__RW uint32_t PWM1PCR;		// Select Single Edge PWM (= 0)
		struct{
			__RW uint32_t UNUSED_0:2;
			__RW uint32_t PWMSEL2:1;
			__RW uint32_t PWMSEL3:1;
			__RW uint32_t PWMSEL4:1;
			__RW uint32_t PWMSEL5:1;
			__RW uint32_t PWMSEL6:1;
			__RW uint32_t RESERVED_4:2;
			__RW uint32_t PWMENA1:1;
			__RW uint32_t PWMENA2:1;
			__RW uint32_t PWMENA3:1;
			__RW uint32_t PWMENA4:1;
			__RW uint32_t PWMENA5:1;
			__RW uint32_t PWMENA6:1;
			__RW uint32_t RESERVED_7:17;
		};
	};
	union{
		__RW uint32_t PWM1LER; 		//update values from MR0 to MR6
		struct{
			__RW uint32_t LER_ENA0:1;
			__RW uint32_t LER_ENA1:1;
			__RW uint32_t LER_ENA2:1;
			__RW uint32_t LER_ENA3:1;
			__RW uint32_t LER_ENA4:1;
			__RW uint32_t LER_ENA5:1;
			__RW uint32_t LER_ENA6:1;
			__RW uint32_t RESERVED_3:25;
		};
	};
	__RW uint32_t RESERVED_1[5];
	__RW uint32_t PWM1CTCR;
}pwm1_t;

#define PWM ( (__RW pwm1_t *) 0x40018000)
#define PWMPRESCALE (25-1) //25 PCLK cycles to increment TC by 1 i.e. 1 Micro-second

#define PWM1 1
#define PWM2 2
#define PWM3 3
#define PWM4 4
#define PWM5 5
#define PWM6 6


#define GPIO_PWM1 2,0
#define GPIO_PWM2 2,1
#define GPIO_PWM3 2,2
#define GPIO_PWM4 2,3
#define GPIO_PWM5 2,4
#define GPIO_PWM6 2,5
