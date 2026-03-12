#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **optionsProcess() {
    static char *options[] = 
    {
        "code",
        "mate-terminal",
        "chrome",
        "firefox"
    };
    return options;
}

char **callLabels(int idProcess) {
    static char *labels[][3] = 
    {
        {"Editar", "Pesquisar", "Ajuda"}, // vscode
        {"Preferências", "Pesquisar", "Terminal"}, //terminal
        {"Histórico", "Guias", "Downloads"}, // browser
        {"Arquivo", "Editar", "Formato"} // caja or default
    };

    return labels[idProcess];
}

int getIdProcessInArray(char *options[], char *process, int sizeArrayOptions) {
    for(int i = 0; i < sizeArrayOptions; i++) {
        if(strcmp(process, options[i]) == 0) {
            return i;
        }
    }
    return 3; // default id
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
    int idProcess = getIdProcessInArray(optionsProcess(), process, 4);
    char **labels = callLabels(idProcess);

    printf("%s  %s  %s", labels[0], labels[1], labels[2]);
}