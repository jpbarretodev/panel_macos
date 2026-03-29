#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **optionsProcess() {
    /**
     * Retorna apenas o array para consulta. Só pode ser chamado como parâmetro para função.
     * Aqui pode ser adicionado mais opções de programas a serem abertos. Lembre de adicionar também na função callLabels o conjunto de 3 strings para ser chamado na abertura da janela.
     */
    static char *options[] =
    {
        "code",
        "mate-terminal",
        "chrome",
        "firefox",
    };
    return options;
}

char **callLabels(int idProcess) {
    /**
     * Função recebe o id do processo correspondente ao que está disposto na função optionsProcess, para saber em qual array de strings buscar. Precisa receber o inteiro.
     */
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
    /**
     * Função reponsável por pegar o NOME do processo atual, percorrer a lista de opções de processor e retornar o ID.
     */
    for(int i = 0; i < sizeArrayOptions; i++) {
        if(strcmp(process, options[i]) == 0) {
            return i;
        }
    }
    return 3; // default id (sempre o último array contendo as strings "padrão")
}

char *getWindowFocus() {
    /**
     * Retorna somente o NOME do processo atual conforme janela em foco.
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

    printf(" %s  %s  %s", labels[0], labels[1], labels[2]);
}