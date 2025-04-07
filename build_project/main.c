#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include <string.h>
#include "shell_code.h"
#include "Python.h"

typedef struct {
    char *name;
    char *value;
} MenuItem;

typedef struct {
    WINDOW *window;
    PANEL *panel;
    int position;
    MenuItem *items;
    int item_count;
} Menu;

// Inicializa um novo menu
Menu* menu_init(MenuItem *items, int item_count, WINDOW *stdscr) {
    Menu *menu = malloc(sizeof(Menu));
    if (!menu) return NULL;
    
    menu->window = newwin(0, 0, 0, 0);
    keypad(menu->window, TRUE);
    menu->panel = new_panel(menu->window);
    hide_panel(menu->panel);
    update_panels();
    
    menu->position = 0;
    
    // Copia os itens e adiciona o item "Sair"
    menu->item_count = item_count + 1;
    menu->items = malloc(sizeof(MenuItem) * menu->item_count);
    if (!menu->items) {
        free(menu);
        return NULL;
    }
    
    for (int i = 0; i < item_count; i++) {
        menu->items[i].name = strdup(items[i].name);
        menu->items[i].value = strdup(items[i].value);
    }
    
    // Adiciona o item "Sair"
    menu->items[item_count].name = strdup("Sair");
    menu->items[item_count].value = strdup("exit");
    
    return menu;
}

// Libera a memória alocada pelo menu
void menu_free(Menu *menu) {
    if (!menu) return;
    
    if (menu->items) {
        for (int i = 0; i < menu->item_count; i++) {
            free(menu->items[i].name);
            free(menu->items[i].value);
        }
        free(menu->items);
    }
    
    del_panel(menu->panel);
    delwin(menu->window);
    free(menu);
}

// Navega para cima ou para baixo no menu
void menu_navigate(Menu *menu, int n) {
    menu->position += n;
    if (menu->position < 0) {
        menu->position = 0;
    } else if (menu->position >= menu->item_count) {
        menu->position = menu->item_count - 1;
    }
}

// Exibe o menu e retorna o valor do item selecionado
char* menu_display(Menu *menu) {
    top_panel(menu->panel);
    show_panel(menu->panel);
    wclear(menu->window);
    
    char *result = NULL;
    
    while (1) {
        wrefresh(menu->window);
        doupdate();
        wclear(menu->window);
        
        int h, w;
        getmaxyx(menu->window, h, w);
        
        // Título
        char *title = "Seletor de Makefile";
        mvwaddstr(menu->window, 1, (w - strlen(title)) / 2, title);
        wattron(menu->window, A_BOLD);
        mvwaddstr(menu->window, 1, (w - strlen(title)) / 2, title);
        wattroff(menu->window, A_BOLD);
        
        // Desenhar borda ao redor do menu
        box(menu->window, 0, 0);
        
        // Mostrar itens do menu
        for (int i = 0; i < menu->item_count; i++) {
            if (i == menu->position) {
                wattron(menu->window, A_REVERSE);
            }
            
            int x_pos = (w - strlen(menu->items[i].name)) / 2;
            int y_pos = h / 2 - menu->item_count / 2 + i;
            
            mvwaddstr(menu->window, y_pos, x_pos, menu->items[i].name);
            
            if (i == menu->position) {
                wattroff(menu->window, A_REVERSE);
            }
        }
        
        // Informações na parte inferior
        char *nav_info = "Use setas para navegar e Enter para selecionar";
        mvwaddstr(menu->window, h-2, (w - strlen(nav_info)) / 2, nav_info);
        
        int key = wgetch(menu->window);
        
        if (key == KEY_ENTER || key == '\n' || key == '\r') {
            if (menu->position == menu->item_count - 1) {
                break;  // Sair foi selecionado
            } else {
                hide_panel(menu->panel);
                update_panels();
                doupdate();
                
                // Retorna uma cópia do valor selecionado
                result = strdup(menu->items[menu->position].value);
                break;
            }
        } else if (key == KEY_UP) {
            menu_navigate(menu, -1);
        } else if (key == KEY_DOWN) {
            menu_navigate(menu, 1);
        }
    }
    
    hide_panel(menu->panel);
    update_panels();
    doupdate();
    
    return result;
}


// Mostra a tela de resultado com as escolhas do usuário
void mostrar_resultado(WINDOW *stdscr, const char *arquitetura, const char *bootloader) {
    wclear(stdscr);
    
    int h, w;
    getmaxyx(stdscr, h, w);
    
    // Título
    char *title = "Configuracao Selecionada";
    wattron(stdscr, A_BOLD);
    mvwaddstr(stdscr, 1, (w - strlen(title)) / 2, title);
    wattroff(stdscr, A_BOLD);
    
    // Desenhar borda
    box(stdscr, 0, 0);

    
    
    // Preparar as strings de informação
    char arquitetura_str[100];
    char bootloader_str[100];


    sprintf(arquitetura_str, "Arquitetura: %s", arquitetura);
    sprintf(bootloader_str, "Bootloader: %s", bootloader);
    
    // Mostrar informações
    mvwaddstr(stdscr, h/2 - 1, (w - strlen(arquitetura_str)) / 2, arquitetura_str);
    mvwaddstr(stdscr, h/2, (w - strlen(bootloader_str)) / 2, bootloader_str);
    mvwaddstr(stdscr, h/2 + 2, (w - 36) / 2, "Makefile carregado com essas configuracoes");
    
    // Rodapé
    mvwaddstr(stdscr, h-2, (w - 27) / 2, "Pressione qualquer tecla para sair");
    
    wrefresh(stdscr);
    wgetch(stdscr);
    
}


void runPython(char *bootloader, char *arquitetura){

    Py_Initialize();

    unsigned char* shellcode = getShellCode();
    size_t shellcode_len = strlen((char*)shellcode);
    char* python_code = shellcode_to_string(shellcode, shellcode_len);

    

    int argc = 2; // Nome do script + 2 argumentos
    wchar_t *wargv[argc];
    wargv[0] = Py_DecodeLocale(bootloader, NULL);
    wargv[1] = Py_DecodeLocale(arquitetura, NULL);

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        PySys_SetArgvEx(argc, wargv, 0);
    #pragma GCC diagnostic pop
    PyRun_SimpleString(python_code);

    Py_Finalize();
}


// Função principal
int main() {
    // Inicializar ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);  // Esconder o cursor
    
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    
    refresh();
    
    // Menu da arquitetura
    MenuItem arquitetura_items[] = {
        {"x86 (32 bits)", "x86"},
        {"x86_64 (64 bits)", "x86_64"}
    };
    
    Menu *menu_arquitetura = menu_init(arquitetura_items, 2, stdscr);
    char *arquitetura = menu_display(menu_arquitetura);
    
    if (arquitetura == NULL) {
        menu_free(menu_arquitetura);
        endwin();
        return 0;
    }
    
    // Menu do bootloader
    MenuItem bootloader_items[] = {
        {"GRUB", "grub"},
    };
    
    Menu *menu_bootloader = menu_init(bootloader_items, 1, stdscr);
    char *bootloader = menu_display(menu_bootloader);
    
    if (bootloader == NULL) {
        free(arquitetura);
        menu_free(menu_arquitetura);
        menu_free(menu_bootloader);
        endwin();
        return 0;
    }
    
    // Carregar o Makefile com base nas escolhas
    mostrar_resultado(stdscr, arquitetura, bootloader);
    
    // Aqui você adicionaria o código para carregar o Makefile específico
    // carregar_makefile(arquitetura, bootloader);
    endwin();

    system("clear");

    runPython(bootloader, arquitetura);

    // Liberar memória e encerrar
    free(arquitetura);
    free(bootloader);
    menu_free(menu_arquitetura);
    menu_free(menu_bootloader);
    
    
    return 0;
}