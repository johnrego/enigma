#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "machine.h"

walze *rolInit() {
    static const char* TAG = "rolInit";
    walze *w = malloc(8 * sizeof(walze));
    if (w == NULL) {
        ESP_LOGI(TAG, "Erro ao alocar memória para walzes.");
        return NULL;
    }
    (w+0)->number = 0;
    strcpy((w+0)->ran, "EKMFLGDQVZNTOWYHXUSPAIBRCJ");
    (w+0)->pos = 0;
    (w+1)->number = 1;
    strcpy((w+1)->ran, "AJDKSIRUXBLHWTMCQGZNPYFVOE");
    (w+1)->pos = 0;
    (w+2)->number = 2;
    strcpy((w+2)->ran, "BDFHJLCPRTXVZNYEIWGAKMUSQO");
    (w+2)->pos = 0;
    (w+3)->number = 3;
    strcpy((w+3)->ran, "ESOVPZJAYQUIRHXLNFTGKDCMWB");
    (w+3)->pos = 0;
    (w+4)->number = 4;
    strcpy((w+4)->ran, "VZBRGITYUPSDNHLXAWMJQOFECK");
    (w+4)->pos = 0;
    // (w+5)->number = 5;
    // strcpy((w+5)->ran, "JPGVOUMFYQBENHZRDKASXLICTW");
    // (w+5)->pos = 0;
    // (w+6)->number = 6;
    // strcpy((w+6)->ran, "NZJHGRCXMYSWBOUFAIVLPEKQDT");
    // (w+6)->pos = 0;
    // (w+7)->number = 7;
    // strcpy((w+7)->ran, "FKQHTLXOCBJSPDZRAMEWNIUYGV");
    // (w+7)->pos = 0;
    return w;
}

char roll(walze *w, unsigned int rol[3], unsigned int seq[3], char let) {
    static const char* TAG = "roll";
    // Define o número de cada rotor
    for (unsigned int a = 0; a < 3; a++) {
        if (seq[a] > 25) {
            (w+rol[a])->pos = seq[a] % 26;
        }
        else {
            (w+rol[a])->pos = seq[a];
        }
    }
    // Pressionando uma tecla o primeiro rotor da 1 passo
    ESP_LOGI(TAG, "r%d pos %d", (w+rol[0])->number, (w+rol[0])->pos++);
    // Embaralhamento pelas tomadas
    let = socket(let);
    // Embaralhamento pelos rotores em ordem crescente
    for (unsigned int a = 0; a < 3; a++) {
        // Giro dos rotores
        if ((w+rol[0])->pos > 25) {
            (w+rol[0])->pos = 0;
            (w+rol[1])->pos++;
            if ((w+rol[1])->pos > 25) {
                (w+rol[1])->pos = 0;
                (w+rol[2])->pos++;
                if ((w+rol[2])->pos > 25) (w+rol[2])->pos = 0;
            }
        }
        ESP_LOGI(TAG, "%c -> r%d -> %c", let, (w+a)->number, (w+a)->ran[(w+a)->pos]);
        let = (w+rol[a])->ran[(w+rol[a])->pos];
    }
    // Embaralhamento pelo refletor
    let = reflect(let);
    // Embaralhamento pelos rotores em ordem decrescente
    for (int a = 2; a > -1; a--) {
        ESP_LOGI(TAG, "%c -> r%d -> %c", let, (w+a)->number, (w+a)->ran[(w+a)->pos]);
        let = (w+rol[a])->ran[(w+rol[a])->pos];
    }
    // Embaralhamento pelas tomadas
    let = socket(let);
    return let;
}

char reflect(char let) {
    static const char* TAG = "reflect";
    char seq[26] = "LEYJVCNIXWPBQMDRTAKZGFUHOS";
    char *in = strchr(seq, let);
    if (in != NULL) {
        unsigned int pos = in - seq;
        if (pos % 2 == 0) {
            ESP_LOGI(TAG, "%c -> rf -> %c", let, seq[pos+1]);
            return seq[pos+1];
        }
        ESP_LOGI(TAG, "%c -> rf -> %c", let, seq[pos-1]);
        return seq[pos-1];
    }
    ESP_LOGI(TAG, "%c -> rf -> %c", let, let);
    return let;
}

char socket(char let) {
    static const char* TAG = "socket";
    // Dia 1
    // char seq[20] = "NPJVLYIXKQAODZCRFTEM";
    // Dia 22
    char seq[20] = "EYJLAKNVFZCTHPMXBQGS";
    char *in = strchr(seq, let);
    if (in != NULL) {
        unsigned int pos = in - seq;
        // ESP_LOGI(TAG, "%c na posicao %d", let, pos);
        if (pos % 2 == 0) {
            ESP_LOGI(TAG, "%c -> s%c -> %c", let, let, seq[pos+1]);
            return seq[pos+1];
        }
        ESP_LOGI(TAG, "%c -> s%c -> %c", let, let, seq[pos-1]);
        return seq[pos-1];
    }
    ESP_LOGI(TAG, "%c -> s%c -> %c", let, let, let);
    return let;
}