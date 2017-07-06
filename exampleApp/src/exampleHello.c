/* Example showing how to register a new command with iocsh */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <epicsExport.h>
#include <iocsh.h>

/* This is the command, which the vxWorks shell will call directly */
void hello(const char *name) {

    char *s;

    if (name) {
	printf("Hello %s, from example\n", name);
    } else {
	puts("Hello from example");
    }

    s = malloc(5* sizeof(char));
    strcpy(s, "I will write off the end.\n");
    printf(s);

    free(s);


}

/* Information needed by iocsh */
static const iocshArg     helloArg0 = {"name", iocshArgString};
static const iocshArg    *helloArgs[] = {&helloArg0};
static const iocshFuncDef helloFuncDef = {"hello", 1, helloArgs};

/* Wrapper called by iocsh, selects the argument types that hello needs */
static void helloCallFunc(const iocshArgBuf *args) {
    hello(args[0].sval);
}

/* Registration routine, runs at startup */
static void helloRegister(void) {
    iocshRegister(&helloFuncDef, helloCallFunc);
}
epicsExportRegistrar(helloRegister);
