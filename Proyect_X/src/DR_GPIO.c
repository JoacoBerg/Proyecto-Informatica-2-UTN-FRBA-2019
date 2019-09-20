#include <DR_GPIO.h>


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-------------------------         FUNCIONES  GPIO         -------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------


void GPIO_Pinsel(uint32_t Puerto, uint32_t Pin, uint32_t Funcion){	//tambien llamada PINSEL por el resto de la catedra

	PINSEL[(Puerto*2) + (Pin/16)]&=~(3<<((Pin%16) * 2));

	if(Funcion!=0)
		PINSEL[(Puerto*2) + (Pin/16)]|=(Funcion<<((Pin%16) * 2));
}



void GPIO_Mode(uint32_t Puerto, uint32_t Pin,uint32_t Configurar){	//pull up or pull down

	PINMODE[(Puerto*2) + (Pin/16)]&=~(3<<((Pin%16) * 2));

	if(Configurar!=0){
		PINMODE[(Puerto*2) + (Pin/16)]|=(Configurar<<((Pin%16) * 2));
	}
}



void GPIO_Dir(uint32_t Puerto, uint32_t Pin,uint32_t Dir){	//0: Entrada; 1: Salida
	
	if(Dir)
		GPIOs[Puerto].FIODIR|=(1<<Pin);
	else
		GPIOs[Puerto].FIODIR&=~(1<<Pin);
}



void GPIO_Set(uint32_t Puerto, uint32_t Pin, uint32_t Estado){	//escritura del GPIO
	
	if(1==Estado)	//Buena practica de programacion: en lugar de if(Estado==1)
		GPIOs[Puerto].FIOSET = (1<<Pin);
	else
		GPIOs[Puerto].FIOCLR = (1<<Pin);
}



uint32_t GPIO_Get(uint32_t Puerto, uint32_t Pin){	//lectura del GPIO

	if(GPIOs[Puerto].FIOPIN & (1<<Pin))	//creo q se puede volar el if y retornar directamente
		return 1;
	else
		return 0;
}

/* para gpioget
 * se puede agregar en get un flag de activo en alto o activo en bajo.
 * En caso de que sea activo en bajo se puede comparar este flag y en caso de que sea 1 0 cero invertir el resultado
 * */
