#ifndef MACHINE_H
#define MACHINE_H

typedef struct walze_ {
    unsigned int number, pos, ranInt[4];
    bool inMac;
    char ranChar[5];
} walze;

walze *rolInit(unsigned int rol[2], unsigned int seq[2], unsigned int quantity);
char rollL(walze *w, unsigned int rol, char let);
char rollR(walze *w, unsigned int rol, char let);
char gear(walze *w, char let, unsigned int quantity);
char socket(char let);
char reflect(char let);
void turnRoll(walze *w);

#endif
