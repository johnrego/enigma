#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "machine.h"

int main() {
    log_set_level(3);
    printf("Maquina enigma.\n");
    unsigned int rol[3] = {0, 1, 2};
    unsigned int seq[3] = {0, 0, 0};
    unsigned int quantity = 3;
    walze *walzes = rolInit(rol, seq, quantity);
    if (walzes == NULL) {
        log_fatal("Erro ao alocar memória para walzes.");
        return 1;
    }
    printf("Configuração diaria aplicada.\n");
    // char out = gear(walzes, 'D', quantity);
    // printf("Saida: %c; ASCII: %d\n", out, (int)out);
    // char msg[15] = "NADA A DECLARAR";
    char msg[15] = "AFGS J MJYWUVFP";
    printf("Codificando: %s.\n", msg);
    printf("Saida: ");
    for (unsigned int a = 0; a < strlen(msg); a++) {
        // if(a == 1) log_set_level(0);
        // else log_set_level(3);
        if (msg[a] == ' '){
            printf("%c", msg[a]);
        }
        else{
            // printf("%c\n", msg[a]);
            printf("%c", gear(walzes, msg[a], quantity));
        }
    }
    printf(".\n");
    log_trace("Rotor %d Posicao: %d", 0, (walzes+0)->pos);
    log_trace("Rotor %d Posicao: %d", 1, (walzes+1)->pos);
    log_trace("Rotor %d Posicao: %d", 2, (walzes+2)->pos);
    free(walzes);
    printf("Fim.\n");
    return 0;
}
