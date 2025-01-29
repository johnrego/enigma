#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "machine.h"

void app_main(void){
    static const char* TAG = "app_main";
    printf("Maquina enigma.\n");
    unsigned int rol[2] = {0, 1};
    unsigned int seq[2] = {0, 0};
    walze *walzes = rolInit(rol, seq, 2);
    if (walzes == NULL) {
        ESP_LOGI(TAG, "Erro ao alocar memória para walzes.");
        return;
    }
    // printf("Configuração diaria aplicada.\n\n");
    // char out = gear(walzes, 'D', 2);
    // printf("Saida: %c; ASCII: %d\n", out, (int)out);
    char msg[] = "ABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCD";
    printf("Codificando: %s.\n", msg);
    printf("Saida: ");
    for (unsigned int a = 0; a < strlen(msg); a++) {
        printf("%c", gear(walzes, msg[a], 2));
    }
    printf("\n");
    free(walzes);
    printf("Fim.\n");
}
