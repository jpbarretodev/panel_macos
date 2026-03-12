#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int getIdProcessInArray() {
    
}



char *getWindowFocus() {
    /**
     * get name while window in focus
     */

    static char processName[256];
    const char *cmd = "xdotool getwindowfocus getwindowpid | xargs -I {} ps -p {} -o comm=";

    FILE *fp = popen(cmd, "r");
    if(!fp) {
        return NULL; // error
    }

    if(fgets(processName, sizeof(processName), fp) != NULL) {
        processName[strcspn(processName, "\n")] = 0; // remove new Line
        pclose(fp);
        return processName;
    }

    pclose(fp);
    return NULL;
}

void main() {
    char *process = getWindowFocus();
    if(process) {
        printf("%s", process);
    } else {
        printf("Error");
    }
}