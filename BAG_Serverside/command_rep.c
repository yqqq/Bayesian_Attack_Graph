#include<stdio.h>
#include<stdlib.h>
#include<string>

/*-----------------------------------------------------------------------------/
/   Command lines:                                                             /
/       generation  : Generation Attack Graph                                  /
/       scale       : Restrict the scale of Attack Graph                       /
/       calculation : Send into calculation of Bayesian Attack Egine           /
/                                                                              /
/-----------------------------------------------------------------------------*/

int Get_Operation(char buff[]){
    int n;
    n=sizeof(buff[]);
    char comandline[MAXSIZE];
    strncpy(comandline,buff,n);
    switch (comandline[0]) {
        case "g":
            //call generation function
            break;
        case "c":
            //call bayesian function
        default:
            break;
    }
    
    
    
    
}
