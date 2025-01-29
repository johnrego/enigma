#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "machine.h"

void app_main(void){
    static const char* TAG = "app_main";
    printf("Maquina enigma.\n");
    unsigned int rol[3] = {0, 1, 2};
    unsigned int seq[3] = {0, 0, 0};
    unsigned int quantity = 3;
    walze *walzes = rolInit(rol, seq, quantity);
    if (walzes == NULL) {
        ESP_LOGI(TAG, "Erro ao alocar memória para walzes.");
        return;
    }
    // printf("Configuração diaria aplicada.\n\n");
    // char out = gear(walzes, 'D', quantity);
    // printf("Saida: %c; ASCII: %d\n", out, (int)out);
    char msg[] = "DABABCDCDABABCDABCDCDABABCDCDABCDABABCDCDABABCDABCDCDABABCDCDABCDABABCDCDABABCDABCDCDABABCDC";
    printf("Codificando: %s.\n", msg);
    printf("Saida: ");
    for (unsigned int a = 0; a < strlen(msg); a++) {
        printf("%c", gear(walzes, msg[a], quantity));
    }
    printf("\n");
    ESP_LOGI(TAG, "Rotor %d Posicao: %d", 0, (walzes+0)->pos);
    ESP_LOGI(TAG, "Rotor %d Posicao: %d", 1, (walzes+1)->pos);
    ESP_LOGI(TAG, "Rotor %d Posicao: %d", 2, (walzes+2)->pos);
    free(walzes);
    printf("Fim.\n");
}
