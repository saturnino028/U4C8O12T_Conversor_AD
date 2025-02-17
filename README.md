# Controle de Joystick e Display SSD1306 no RP2040

## Descrição do Projeto
Este projeto tem como objetivo explorar o uso de conversores analógico-digitais (ADC) no RP2040 e integrar funcionalidades com um joystick, LEDs RGB e um display OLED SSD1306 via I2C.

## Funcionalidades Implementadas
- **Controle de LEDs RGB via PWM:**
  - LED Azul ajusta o brilho conforme o eixo Y do joystick.
  - LED Vermelho ajusta o brilho conforme o eixo X do joystick.
  - LEDs controlados via PWM para variação suave de intensidade.
- **Exibição Gráfica no SSD1306:**
  - Um quadrado de 8x8 pixels representa a posição do joystick na tela.
  - O botão do joystick altera a borda do display ao ser pressionado.
- **Funções Adicionais:**
  - **Calibração do Joystick:** Ajusta automaticamente os valores máximos, mínimos e centrais do eixo X e Y.
  - **Modo de Gravação:** Reinicia o RP2040 no modo de boot para gravação de firmware.

## Hardware Utilizado
- Placa de desenvolvimento **BitDogLab** com RP2040
- **Joystick** conectado aos GPIOs 26 (Y) e 27 (X)
- **LED RGB** conectado aos GPIOs 11, 12 e 13
- **Botão do Joystick** conectado ao GPIO 22
- **Botão A** conectado ao GPIO 5
- **Display SSD1306** conectado via I2C (GPIO 14 e 15)

## Requisitos do Projeto
1. **Uso de interrupções:** Implementação via IRQ para os botões.
2. **Debouncing:** Tratamento via software para evitar leituras erradas.
3. **Utilização do Display 128x64:** Controle via I2C para exibição gráfica.
4. **Organização do Código:** Estruturado e comentado para facilitar manutenção.

## Instalação e Execução
1. Clone o repositório:
   ```sh
   git clone https://github.com/saturnino028/U4C8O12T_Conversor_AD.git
   ```
2. Compile e carregue o firmware na placa RP2040.
3. Execute o programa e siga as instruções no display para calibração do joystick.

## Estrutura do Código
- **`main.c`**: Contém a lógica principal do projeto.
- **`fonte.h`**: Fontes display SSD1306.
- **`gpio_contrl.c` e `gpio_contrl.h`**: Funções de controle de gpio, joystick, interrupção e modo gravação.
- **`pwm_contrl.c` e `pwm_contrl.h`**: Gerencia as funções PWM que controlam o brilho dos LEDs.
- **`ssd1306.c` e `ssd1306.h`**: Controle do display SSD1306.

## Demonstração
<--to do-->
- Um vídeo demonstrativo do funcionamento do projeto pode ser acessado em: [](url).

## Considerações Finais
Este projeto é uma excelente oportunidade para consolidar conhecimentos em eletrônica embarcada, ADCs, PWM e comunicação I2C.

---
Desenvolvido para a capacitação em Sistemas Embarcados oferecida pela CEPEDI utilizando o Raspberry Pi Pico W, o Pico SDK e o kit de desenvolvimento BitDogLab.
