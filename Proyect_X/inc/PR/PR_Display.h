#ifndef PR_PR_DISPLAY_H_
#define PR_PR_DISPLAY_H_
#include "DR_tipos.h"

void Display7seg_per_digit_BCD(uint32_t val, uint8_t digit);
void Display7seg_BCD(uint32_t val);
void Display7seg_Binary(uint32_t val);

void BarridoDisplay(void);



#endif /* PR_PR_DISPLAY_H_ */
