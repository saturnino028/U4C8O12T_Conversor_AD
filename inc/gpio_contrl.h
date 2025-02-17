/**
 * @brief cabeçalho das funções de controle de gpio e outras 
 */
#ifndef GPIO_CONTRL_H
#define GPIO_CONTRL_H

/********************* Includes *********************/

#include <stdlib.h>
#include "ssd1306.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

/********************* Defines *********************/

#define bot_A   5 //Botao A
#define bot_B   6 //Botão B

#define buz_B   10 //Buzzer B

#define LED_G   11 //Led Verde
#define LED_B   12 //Led azul
#define LED_R   13 //Led vermelho

#define bot_joy 22 //Botão do joystick
#define joyVRy  26 //Eixo y do joystick
#define joyVRx  27 //Eixo x do joystick

#define NUM_PIXELS 25 //Número de pixels/leds matriz

/********************* Variaveis Globais *********************/

extern volatile bool led_flag;
extern volatile bool flag_A;

/********************* Prototipo de Funções *********************/

void calibrar_joy(ssd1306_t *ssd, uint16_t posicoesjoy[6]);
void setup_pins_gpio();
void entrar_modo_gravacao();
void botoes_callback(uint gpio, uint32_t events);
void som_buz(uint16_t freq, uint16_t duration_ms);


#endif //GPIO_BOOT.H