/**
 * @brief código principal
 * @author Marco A J Saturnino
 */
#include "main.h"

int main()
{
    ssd1306_t ssd; // Inicializa a estrutura do display
    bool cor = true; //Cor do display
    uint16_t passadoX, passadoY; //Armazena o valor antigo de X e Y
    uint16_t joy_pos[6] = {2047,4095,0,2047,4095,0}; /*
    * é um vetor com as posições de calibração do joystick, nas três primeiras posições
    * estão armazenados os valores de referencia de X - X0, Xmax, Xmin. Nas três últimas, estão os valores
    * de referencia de y - y0, ymax, ymin.
    */
    uint16_t adc_value_x, adc_value_y; //Auxiliar para leitura ADC
    uint8_t adc_lef_ret = 100, adc_top_ret = 46;
    char str_x[5];  // Buffer para armazenar a string
    char str_y[5];  // Buffer para armazenar a string
    uint8_t aux = 0.0;

    stdio_init_all();
    setup_pins_gpio();
    setup_pwm();

    adc_init();
    adc_gpio_init(joyVRx); //Inicia pino ADC eixo x
    adc_gpio_init(joyVRy); //Inicia pino ADC eixo y
    
    config_i2c_display(&ssd); //Configura o I2C para o diplay

    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 30); // Desenha uma string
    ssd1306_draw_string(&ssd, "BEM VINDO", 24, 48); // Desenha uma string      
    ssd1306_send_data(&ssd); // Atualiza o display
    sleep_ms(3000);

    gpio_set_irq_enabled_with_callback(bot_B, GPIO_IRQ_EDGE_FALL, true, botoes_callback);

    calibrar_joy(&ssd, joy_pos);

    gpio_set_irq_enabled_with_callback(bot_A, GPIO_IRQ_EDGE_FALL, true, botoes_callback);
    gpio_set_irq_enabled_with_callback(bot_joy, GPIO_IRQ_EDGE_FALL, true, botoes_callback);

    passadoX = joy_pos[0]; //Valor de referência X
    sprintf(str_x, "%d", passadoX);  // Converte o inteiro em string 
    passadoY = joy_pos[3]; //Valor de referência Y
    sprintf(str_y, "%d", passadoY);  // Converte o inteiro em string

    while (true)
    {
        adc_select_input(0); // Seleciona o ADC para eixo Y. O pino 26 como entrada analógica
        adc_value_y = adc_read();
        adc_select_input(1); // Seleciona o ADC para eixo X. O pino 27 como entrada analógica
        adc_value_x = adc_read();    

        // Atualiza o conteúdo do display com animações
        ssd1306_fill(&ssd, !cor); // Limpa o display
        if(!led_flag)
            ssd1306_rect(&ssd, 3, 3, 122, 60, cor, !cor); // Desenha um retângulo
        if(led_flag)
            ssd1306_rect(&ssd, 3, 3, 122, 60, !cor, cor); // Desenha um retângulo
        ssd1306_line(&ssd, 3, 25, 123, 25, cor); // Desenha uma linha
        ssd1306_line(&ssd, 3, 37, 123, 37, cor); // Desenha uma linha   
        ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 6); // Desenha uma string
        ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 16); // Desenha uma string
        ssd1306_draw_string(&ssd, "ADC   JOYSTICK", 10, 28); // Desenha uma string 
        ssd1306_draw_string(&ssd, "X    Y    ", 20, 41); // Desenha uma string
        ssd1306_line(&ssd, 44, 37, 44, 60, cor); // Desenha uma linha vertical     
        ssd1306_draw_string(&ssd, str_x, 8, 52); // Desenha uma string  
        ssd1306_line(&ssd, 84, 37, 84, 60, cor); // Desenha uma linha vertical 
        ssd1306_draw_string(&ssd, str_y, 49, 52); // Desenha uma string
        
        ssd1306_rect(&ssd, adc_top_ret, adc_lef_ret,8,8,cor,cor); //Desenha retângulo 8x8
        
        //Verifica se houve alteração significativa no eixo X (>5%)
        if(abs(passadoX - adc_value_x)> (passadoX*0.05) ) 
        {
            passadoX = adc_value_x; //Atualiza variavel de controle
            sprintf(str_x, "%d", adc_value_x);  // Converte o inteiro em string

            if(joy_pos[0] != 0)
            {   
                aux = 0.0;
                if(adc_value_x < joy_pos[0])//Se estiver indo para esquerda
                {
                    aux = ((joy_pos[0] - adc_value_x) * 100) / (joy_pos[0] - joy_pos[2]);//Logica PWM
                    adc_lef_ret = 100 - ((joy_pos[0]-adc_value_x)*16)/(joy_pos[0]-joy_pos[2]);//Logica Ret
                }
                else if(adc_value_x > joy_pos[0])//Se estiver indo para a direita
                {
                    aux = ((adc_value_x - joy_pos[0]) * 100) / (joy_pos[1] - joy_pos[0]);//Logica PWM
                    adc_lef_ret = 100 + ((adc_value_x-joy_pos[0])*16)/(joy_pos[1]-joy_pos[0]);//Logica Ret
                }
                else
                {
                    aux = 0;
                    adc_lef_ret = 100;
                }
                if(aux<10)
                    duty_cicle(0, slice_ledR, LED_R);
                else
                    duty_cicle(aux, slice_ledR, LED_R);
            }
            printf("Valor PWM1: %d\n", aux);
            printf("adc_lef_ret: %d\n", adc_lef_ret);
        }

        //Verifica se houve alteração significativa no eixo Y (>5%)
        if(abs(passadoY - adc_value_y) > (passadoY*0.05))
        {
            passadoY = adc_value_y;
            sprintf(str_y, "%d", adc_value_y);  // Converte o inteiro em string

            if(joy_pos[3] != 0) //Evitar erros
            {
                //Logica PWM
                aux = 0.0;
                if(adc_value_y < joy_pos[3])//Se estiver indo para baixo
                {
                    aux = ((joy_pos[3] - adc_value_y) * 100) / (joy_pos[3] - joy_pos[5]);//Logica PWM
                    adc_top_ret = 46 + ((joy_pos[3] - adc_value_y)*9)/(joy_pos[3] - joy_pos[5]);//Logica Ret
                }
                else if(adc_value_y > joy_pos[3])//Se estiver indo para cima
                {
                    aux = ((adc_value_y - joy_pos[3]) * 100) / (joy_pos[4] - joy_pos[3]);//Logica PWM
                    adc_top_ret = 46 - ((adc_value_y-joy_pos[3])*9)/(joy_pos[4]-joy_pos[3]);//Logica Ret
                }
                else
                {
                    aux = 0;
                    adc_top_ret = 46;
                }
                if(aux<10)
                    duty_cicle(0, slice_ledB, LED_B);
                else
                    duty_cicle(aux, slice_ledB, LED_B);
            }
            printf("Valor PWM2: %d\n", aux);
            printf("adc_top_ret: %d\n", adc_top_ret);
        }
              
        ssd1306_send_data(&ssd); // Atualiza o display    
        sleep_ms(100);
    }
    
}