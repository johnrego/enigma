#ifndef MACHINE_H
#define MACHINE_H

typedef struct walze_ {
    unsigned int number, pos;
    char ran[27];
} walze;

walze *rolInit();
char roll(walze *w, unsigned int rol[3], unsigned int seq[3], char let);
char socket(char let);
char reflect(char let);

#endif
