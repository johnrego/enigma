#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "machine.h"

walze *rolInit(unsigned int rol[3], unsigned int seq[3], unsigned int quantity) {
    walze *w = malloc(5 * sizeof(walze));
    if (w == NULL) {
        log_error("Erro ao alocar memória para walzes.");
        return NULL;
    }
    // Define o numero do rotor e sua sequencia de letras
    (w+0)->number = 0;
    (w+0)->inMac = false;
    strcpy((w+0)->ranChar, "EKMFLGDQVZNTOWYHXUSPAIBRCJ");
    (w+1)->number = 1;
    (w+1)->inMac = false;
    strcpy((w+1)->ranChar, "AJDKSIRUXBLHWTMCQGZNPYFVOE");
    (w+2)->number = 2;
    (w+2)->inMac = false;
    strcpy((w+2)->ranChar, "BDFHJLCPRTXVZNYEIWGAKMUSQO");
    (w+3)->number = 3;
    (w+3)->inMac = false;
    strcpy((w+3)->ranChar, "ESOVPZJAYQUIRHXLNFTGKDCMWB");
    (w+4)->number = 4;
    (w+4)->inMac = false;
    strcpy((w+4)->ranChar, "VZBRGITYUPSDNHLXAWMJQOFECK");
    // Converter as letras em inteiros
    for (unsigned int a = 0; a < 5; a++) {
        (w+a)->pos = 0;
        for (unsigned int b = 0; b < quantity; b++) {
            if ((w+a)->number == rol[b]) {
                (w+a)->inMac = true;
                (w+a)->pos = seq[b];
            }
        }
        for (unsigned int b = 0; b < strlen((w+a)->ranChar); b++) {
            (w+a)->ranInt[b] = (int)(w+a)->ranChar[b] - 'A';
        }
    }
    // Seleciona apenas rotores que serao usados
    walze *wUse = malloc(quantity * sizeof(walze));
    if (wUse == NULL) {
        log_error("Erro ao alocar memória para walzes.");
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
    unsigned int in = (unsigned int)let - 'A';
    int aux = (in + (w+rol)->pos) % 26;
    log_trace("%c -> r%d -> %c", let, (w+rol)->number, (char)('A' + (w+rol)->ranInt[aux]));
    char tmp = (char)('A' + (w+rol)->ranInt[aux]);
    if ((tmp < 65) || (tmp > 90)){
        log_warn("A letra gerada %d, em funcao de %c nao esta no escopo.", tmp, let);
    }
    return (char)('A' + (w+rol)->ranInt[aux]);
}

char rollR(walze *w, unsigned int rol, char let) {
    char *in = strchr((w+rol)->ranChar, let);
    if (in != NULL) {
        unsigned int pos = in - (w+rol)->ranChar;
        int aux = (int)(pos - (w+rol)->pos) % 26;
        if (aux < 0 ) aux = 26 + aux;
        log_trace("%c -> r%d -> %c", let, (w+rol)->number, (char)('A' + aux));
        char tmp = (char)('A' + aux);
        if ((tmp < 65) || (tmp > 90)){
            log_warn("A letra gerada %d, em funcao de %c nao esta no escopo.", tmp, let);
        }
        return (char)('A' + aux);
    }
    log_trace("Letra nao encontrada no rotor %d", (w+rol)->number);
    return let;
}

char gear(walze *w, char let, unsigned int quantity) {
    turnRoll(w);
    let = socket(let);
    for (unsigned int a = 0; a < quantity; a++) {
        let = rollL(w, a, let);
    }
    let = reflect(let);
    for (int a = quantity - 1; a > -1; a--) {
        let = rollR(w, a, let);
    }
    let = socket(let);
    return let;
}

char reflect(char let) {
    char seq[26] = "FSOKANUERHMBTIYCWLQPZXVGJD";
    char *in = strchr(seq, let);
    if (in != NULL) {
        unsigned int pos = in - seq;
        if (pos % 2 == 0) {
            log_trace("%c -> rf -> %c", let, seq[pos+1]);
            return seq[pos+1];
        }
        log_trace("%c -> rf -> %c", let, seq[pos-1]);
        return seq[pos-1];
    }
    log_trace("Letra nao encontrada no refletor");
    return let;
}

char socket(char let) {
    // Dia 1
    char seq[20] = "NPJVLYIXKQAODZCRFTEM";
    // Dia 22
    // char seq[20] = "EYJLAKNVFZCTHPMXBQGS";
    char *in = strchr(seq, let);
    unsigned int pos = in - seq;
    if (pos < 20) {
        if (pos % 2 == 0) {
            log_trace("%c -> s%c -> %c", let, let, seq[pos+1]);
            return seq[pos+1];
        }
        log_trace("%c -> s%c -> %c", let, let, seq[pos-1]);
        return seq[pos-1];
    }
    log_trace("%c -> s%c -> %c", let, let, let);
    return let;
}

void turnRoll(walze *w) {
    //Giro dos rotores
    (w+0)->pos++;
    if ((w+0)->pos > 25){
        (w+0)->pos = 0;
        (w+1)->pos++;
        if ((w+1)->pos > 25){
            (w+1)->pos = 0;
            (w+2)->pos++;
            if ((w+2)->pos > 25) (w+2)->pos = 0;
        }
    }
}