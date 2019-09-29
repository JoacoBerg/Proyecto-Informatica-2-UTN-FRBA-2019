#include <DR_PINSEL.h>


void SetPinsel(uint32_t Puerto, uint32_t Pin, uint32_t Funcion){	//tambien llamada PINSEL por el resto de la catedra

	PINSEL[(Puerto*2) + (Pin/16)]&=~(3<<((Pin%16) * 2));

	if(Funcion!=0)
		PINSEL[(Puerto*2) + (Pin/16)]|=(Funcion<<((Pin%16) * 2));
}
