#include "Boton.h"

void Boton_init()
{
	GPIO_Pinsel( BOTON_PORT, BOTON_PIN, PINSEL_GPIO);  //funcion GPIO configurada en pin
	GPIO_Mode( BOTON_PORT, BOTON_PIN, PINMODE_PULLDOWN); //pull up
	GPIO_Dir( BOTON_PORT, BOTON_PIN, INPUT); // input
}




