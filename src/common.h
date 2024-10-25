#ifndef ___COMMON_H__
#define ___COMMON_H__

/* DEBUG */
#ifndef DEBUG
#define DEBUG 0
#endif //DEBUG

/* DEBUG message */
#define IFDEBUG(M) if(DEBUG) fprintf(stderr, "[DEBUG file:%s line:%d]: " M "\n", __FILE__, __LINE__); else {;}

/* Macros */
#define BUFFER_SIZE 256

/* Includes of standard libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

/* Includes of local libraies */
#include "bitmap.h"

/* Globals */
extern int verb;

/* Prototypes */
void help(void);
void copyr(void);

#endif //__COMMON_H__
