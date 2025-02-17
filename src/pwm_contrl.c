#include "pwm_contrl.h"

volatile uint slice_ledR;
volatile uint slice_ledB;

/**
 * @brief configura o pino PWM para uma frequencia de Fpwm = 1 KHz @F_clock at 125MHz
 * 
 */
void setup_pwm()
{
    gpio_set_function(pwm_ledR, GPIO_FUNC_PWM); //Habilita o PWM para o led vermelho
    slice_ledR = pwm_gpio_to_slice_num(pwm_ledR); //Obter o valor do slice correspondente ao pino
    pwm_set_clkdiv(slice_ledR, 125.0); //Define o divisor de clock
    pwm_set_wrap(slice_ledR, top_wrap); //Define valor do wrap
    
    gpio_set_function(pwm_ledB, GPIO_FUNC_PWM); //Habilita o PWM para o led azul
    slice_ledB = pwm_gpio_to_slice_num(pwm_ledB); //Obter o valor do slice correspondente ao pino
    pwm_set_clkdiv(slice_ledB, 125.0); //Define o divisor de clock
    pwm_set_wrap(slice_ledB, top_wrap); //Define valor do wrap
}


void duty_cicle(float _percent, uint _slice, uint8_t _pin)
{
    pwm_set_enabled(_slice, !flag_A); //Desabilita PWM
    uint16_t valor_pwm = (_percent/100)*top_wrap;
    pwm_set_gpio_level(_pin, valor_pwm);

    pwm_set_enabled(_slice, flag_A); //Habilitar PWM
}