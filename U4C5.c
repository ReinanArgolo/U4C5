#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos dos LEDs
#define LED_RED 12
#define LED_BLUE 11
#define LED_GREEN 13

// Definição do pino do botão
#define BUTTON 5

// Variáveis para controle do estado dos LEDs
bool led_active = false;

// Função de callback para desligar o LED azul após um tempo específico
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, false); // Desliga o LED azul
    gpio_put(LED_RED, true);   // Liga o LED vermelho
    return 0;                  // Retorna 0 para indicar fim da execução
}

// Função de callback para desligar o LED vermelho após um tempo específico
int64_t turn_off_callback2(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, false);  // Desliga o LED vermelho
    gpio_put(LED_GREEN, true); // Liga o LED verde
    return 0;
}

// Função de callback para desligar o LED verde após um tempo específico
int64_t turn_off_callback3(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, false); // Desliga o LED verde
    led_active = false;         // Atualiza o estado do LED
    return 0;
}

// Função de debounce para o botão
bool debounce_button() {
    static uint32_t last_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_time > 50) { // 50ms debounce time
        last_time = current_time;
        return true;
    }
    return false;
}

int main() {
    // Inicializa a comunicação serial para depuração
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configuração do botão como entrada com pull-up interno
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    while (true) {
        // Verifica se o botão foi pressionado e se os LEDs estão desligados
        if (gpio_get(BUTTON) == 0 && !led_active && debounce_button()) {
            sleep_ms(50); // Pequeno atraso para evitar bouncing

            // Confirma se o botão ainda está pressionado e se todos os LEDs estão desligados
            if (gpio_get(BUTTON) == 0 && gpio_get(LED_RED) == 0 && gpio_get(LED_BLUE) == 0 && gpio_get(LED_GREEN) == 0) {
                gpio_put(LED_BLUE, true); // Liga o LED azul
                led_active = true; // Marca os LEDs como ativos

                // Define alarmes para desligar os LEDs em tempos diferentes
                add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Desliga o LED azul e liga o LED vermelho em 3s
                add_alarm_in_ms(6000, turn_off_callback2, NULL, false); // Desliga o LED vermelho e liga o LED verde em 6s
                add_alarm_in_ms(9000, turn_off_callback3, NULL, false); // Desliga o LED verde em 9s
            }
        }

        sleep_ms(10); // Pequeno atraso para evitar uso excessivo da CPU
    }

    return 0;
}