#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "machine.h"

void app_main(void){
    static const char* TAG = "app_main";
    printf("Maquina enigma.\n");
    walze *walzes = rolInit();
    if (walzes == NULL) {
        ESP_LOGI(TAG, "Erro ao alocar memória para walzes.");
        return;
    }
    unsigned int rol[3] = {0, 4, 2};
    unsigned int seq[3] = {11, 15, 06};
    printf("Configuração diaria aplicada.\n");
    // char out = roll(walzes, rol, seq, 'J');
    // printf("Saida: %c; ASCII: %d\n", out, (int)out);
    char msg[5] = "WEPM";
    printf("Codificando: %s.\n", msg);
    // printf("Saida: ");
    for (unsigned int a = 0; a < strlen(msg); a++) {
        // Pressionando uma tecla o primeiro rotor da 1 passo
        seq[0]++;
        printf("%c\n", roll(walzes, rol, seq, msg[a]));
    }
    // printf("\n");
    free(walzes);
    printf("Fim.\n");
}
