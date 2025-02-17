/**
 * @brief cabeçalho controle PWM
 */

#ifndef PWM_CONTRL_H
#define PWM_CONTRL_H

/********************* Includes *********************/

#include <stdio.h>
#include "pico/stdlib.h"
#include "gpio_contrl.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

/******************* Defines e Variaveis Globais ******************/
#define top_wrap 1000 //Maior valor de wrap

#define pwm_ledB 12
#define pwm_ledR 13

extern volatile uint slice_ledR;
extern volatile uint slice_ledB;

/******************* Prototipo de Funções *************************/

void setup_pwm();
void duty_cicle(float _percent, uint _slice, uint8_t _pin);

#endif //PWM_CONTRL_H