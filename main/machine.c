#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "machine.h"

#define LOG_LOCAL_LEVEL ESP_LOG_ERROR

walze *rolInit(unsigned int rol[2], unsigned int seq[2], unsigned int quantity) {
    static const char *TAG = "rolInit";
    walze *w = malloc(5 * sizeof(walze));
    if (w == NULL) {
        ESP_LOGI(TAG, "Erro ao alocar memória para walzes.");
        return NULL;
    }
    // Define o numero do rotor e sua sequencia de letras
    (w+0)->number = 0;
    (w+0)->inMac = false;
    strcpy((w+0)->ranChar, "ABCD");
    (w+1)->number = 1;
    (w+1)->inMac = false;
    strcpy((w+1)->ranChar, "ABCD");
    (w+2)->number = 2;
    (w+2)->inMac = false;
    strcpy((w+2)->ranChar, "ABCD");
    (w+3)->number = 3;
    (w+3)->inMac = false;
    strcpy((w+3)->ranChar, "ABCD");
    (w+4)->number = 4;
    (w+4)->inMac = false;
    strcpy((w+4)->ranChar, "ABCD");
    // Converter as letras em inteiros
    for (unsigned int a = 0; a < 5; a++) {
        (w+a)->pos = 0;
        for (unsigned int b = 0; b < quantity; b++) {
            if ((w+a)->number == rol[b]) {
                (w+a)->inMac = true;
                (w+a)->pos = seq[b];
            }
        }
        static unsigned int ascii = 65;
        for (unsigned int b = 0; b < strlen((w+a)->ranChar); b++) {
            (w+a)->ranInt[b] = (int)(w+a)->ranChar[b] - ascii;
        }
    }
    // Seleciona apenas rotores que serao usados
    walze *wUse = malloc(quantity * sizeof(walze));
    if (wUse == NULL) {
        ESP_LOGI(TAG, "Erro ao alocar memória para walzes.");
        return NULL;
    }
    for (unsigned int a = 0; a < quantity; a++) {
        for (unsigned int b = 0; b < 5; b++) {
            if ((rol[a] == (w+b)->number) && ((w+b)->inMac == true)) {
                (wUse+a)->number = (w+b)->number;
                (wUse+a)->pos = (w+b)->pos;
                (wUse+a)->inMac = (w+b)->inMac;
                strcpy((wUse+a)->ranChar, (w+b)->ranChar);
                for (unsigned int c = 0; c < 26; c++) {
                    (wUse+a)->ranInt[c] = (w+b)->ranInt[c];
                }
            }
        }
    }
    free(w);
    return wUse;
}

char rollL(walze *w, unsigned int rol, char let) {
    static const char *TAG = "rollL";
    static unsigned int ascii = 65;
    unsigned int in = (unsigned int)let - ascii;
    int aux;
    if (rol > 0){
        aux = (in + (w+rol)->pos) % 4;
    }
    else {
        aux = (in - (w+rol)->pos) % 4;
    }
    ESP_LOGI(TAG, "%c -> r%d -> %c", let, (w+rol)->number, (w+rol)->ranChar[aux]);
    let = (char)(ascii + (w+rol)->ranInt[aux]);
    return let;
}

char rollR(walze *w, unsigned int rol, char let) {
    static const char *TAG = "rollR";
    static unsigned int ascii = 65;
    char *in = strchr((w+rol)->ranChar, let);
    if (in != NULL) {
        unsigned int pos = in - (w+rol)->ranChar;
        int aux;
        if (rol > 0){
            aux = (pos - (w+rol)->pos) % 4;
        }
        else {
            aux = (pos + (w+rol)->pos) % 4;
        }
        ESP_LOGI(TAG, "%c -> r%d -> %c", let, (w+rol)->number, (char)(ascii + aux));
        let = (char)(ascii + aux);
        return let;
    }
    ESP_LOGI(TAG, "Letra nao encontrada no rotor %d", (w+rol)->number);
    return let;
}

char gear(walze *w, char let, unsigned int quantity) {
    static const char *TAG = "gear";
    turnRoll(w);
    ESP_LOGI(TAG, "Rotor %d Posicao: %d", 0, (w+0)->pos);
    ESP_LOGI(TAG, "Rotor %d Posicao: %d", 1, (w+1)->pos);
    // let = socket(let);
    for (unsigned int a = 0; a < quantity; a++) {
        let = rollL(w, a, let);
    }
    let = reflect(let);
    for (int a = quantity - 1; a > -1; a--) {
        let = rollR(w, a, let);
    }
    // let = socket(let);
    return let;
}

char reflect(char let) {
    static const char *TAG = "reflect";
    char seq[4] = "ABCD";
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
    ESP_LOGI(TAG, "Letra nao encontrada no refletor");
    return let;
}

char socket(char let) {
    static const char *TAG = "socket";
    // Dia 1
    // char seq[20] = "NPJVLYIXKQAODZCRFTEM";
    // Dia 22
    char seq[20] = "EYJLAKNVFZCTHPMXBQGS";
    char *in = strchr(seq, let);
    unsigned int pos = in - seq;
    if (pos < 20) {
        if (pos % 2 == 0) {
            ESP_LOGI(TAG, "%c -> s%c -> %c", let, let, seq[pos+1]);
            return seq[pos+1];
        }
        ESP_LOGI(TAG, "%c -> s%c -> %c", let, let, seq[pos-1]);
        return seq[pos-1];
    }
    // ESP_LOGI(TAG, "Pos %d", pos);
    ESP_LOGI(TAG, "%c -> s%c -> %c", let, let, let);
    return let;
}

void turnRoll(walze *w) {
    //Giro dos rotores
    (w+0)->pos++;
    if ((w+0)->pos > 3){
        (w+0)->pos = 0;
        (w+1)->pos++;
        if ((w+1)->pos > 3){
            (w+1)->pos = 0;
            // (w+2)->pos++;
            // if ((w+2)->pos > 3) (w+2)->pos = 0;
        }
    }
}