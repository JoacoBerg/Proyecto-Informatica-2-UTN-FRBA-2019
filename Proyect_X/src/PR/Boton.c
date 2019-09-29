#include "Boton.h"
#include "DR_GPIO.h"
void Boton_init()
{
	SetPinsel( BOTON_PORT, BOTON_PIN, PINSEL_GPIO);  //funcion GPIO configurada en pin
	SetPinMode( BOTON_PORT, BOTON_PIN, PINMODE_PULLDOWN); //pull up
	SetPinDir( BOTON_PORT, BOTON_PIN, INPUT); // input
}




