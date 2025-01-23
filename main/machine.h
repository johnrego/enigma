#ifndef MACHINE_H
#define MACHINE_H

typedef struct walze_ {
    unsigned int number, pos, ranInt[26];
    bool inMac;
    char ranChar[27];
} walze;

walze *rolInit(unsigned int rol[3], unsigned int seq[3]);
char rollL(walze *w, unsigned int rol, char let);
char rollR(walze *w, unsigned int rol, char let);
char gear(walze *w, char let);
char socket(char let);
char reflect(char let);

#endif
