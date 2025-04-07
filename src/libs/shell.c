#include "shell.h"

void launch_shell(int n, string name){
    string ch = (string) malloc(200);
    string defaultName = "LYRICOS";
    char currentName[50]; // Buffer para armazenar o nome do shell
    memory_copy(name, currentName, 50); // Copia o nome inicial para o buffer

    do{
        printf("%s (%d)> ", currentName, n);
        ch = keyboardcall();

        if(strEql(ch, "changename")){
            printf("\nDigite o nome do Shell: ");
            string name_shell = keyboardcall();
            clearScreen();

            if(!strEql(name_shell, "default")){
                memory_copy(name_shell, currentName, 50);
            } else {
                memory_copy(defaultName, currentName, 50);
            }

        } else if(strEql(ch, "echo")){
            echo();
        } else if(strEql(ch, "help") || strEql(ch, "")){
            help();
        } else if(strEql(ch, "getdatetime")){
            kernelGetDateApi();
        } else if(strEql(ch, "changetimezone")){
            changeTimezone();
        } else if(strEql(ch, "sum")){
            sum();
        } else if(strEql(ch, "multiply")){
            multiply();
        } else if(strEql(ch, "clear")){
            clearScreen();
        } else if(strEql(ch, "color")){
            set_background_color();
        } else if(strEql(ch, "shutdown")){
            clearScreen();
            kernelShutdownApi();
        } else if(strEql(ch, "reboot")){
            clearScreen();
            kernelRebootApi();
        } else if(strEql(ch, "exit")){
            printf("\nbye\n");
        } else {
            printf("\n Invalid command !\n");
        }

    } while (!strEql(ch, "exit"));
    
    handle_user_input();
}


void changeTimezone(){
    printf("\n");
    printf("UTC                      America/Sao_Paulo         America/Brasilia\n");
    printf("America/New_York         America/Los_Angeles       America/Chicago\n");
    printf("America/Denver           America/Mexico_City       America/Buenos_Aires\n");
    printf("America/Lima             America/Bogota            Europe/London\n");
    printf("Europe/Berlin            Europe/Paris              Europe/Madrid\n");
    printf("Europe/Rome              Europe/Moscow             Europe/Istanbul\n");
    printf("Asia/Tokyo               Asia/Shanghai             Asia/Hong_Kong\n");
    printf("Asia/Singapore           Asia/Dubai                Asia/Kolkata\n");
    printf("Asia/Jakarta             Asia/Hong_Kong            Asia/Singapore\n");
    printf("Australia/Sydney         Australia/Melbourne       Australia/Brisbane\n");
    printf("Australia/Perth          Pacific/Auckland          Africa/Johannesburg\n");
    printf("Africa/Cairo             Africa/Lagos              Antarctica/Palmer\n");
    printf("Indian/Maldives\n\n");
    printf("Digite o timezone: ");
    string str = keyboardcall(); 

    if(strEql(str, ""))
    {
        printf("\nNão pode ser vazio!\n");
        changeTimezone();
    }
    setTimezone(str);
}

void echo()
{
    printf("\nEnter text Value: ");
	string str = keyboardcall();
    if(strEql(str, ""))
    {
        printf("\nEmpty text value\n");
        echo();
    }else
    {
	    printf("\necho: %s\n", str);
    }
}

void sum()
{
    printf("\nHow many numbers: ");
	int n = str_to_int(keyboardcall());
	int i =0;
	printf("\n");
	int arr[n];
	fill_array(arr,n);
	int s = sum_array(arr,n);
	printf("Result: %s", int_to_string(s));
	printf("\n");
}

void help()
{
    printf("\nchangename            : Trocar nome do shell");
    printf("\nchangetimezone        : Mudar fuso");
    printf("\ngetdatetime           : Exibir data e hora em tempo real");
    printf("\nsum                   : Mudar Soma");
	printf("\nmultiply              : Multiplicar");
	printf("\nclear                 : Limpar tela");
    printf("\nexit                  : Sair do Shell");
    printf("\necho                  : Imprimir Texto");
    printf("\ncolor                 : trocar cor do texto e cor de fundo");
    printf("\nshutdown              : Desligar Computador");
    printf("\nreboot                : Reiniciar Computador");
    printf("\n\n");
}

int sum_array(int arr[],int n)
{
	int i = 0;
	int s = 0;
	for (i = 0;i<n;i++)
	{
		s += arr[i];
	}
	return s;
}

void multiply()
{
    printf("\nHow many numbers: ");
    int n = str_to_int(keyboardcall());
    printf("\n");
    int arr[n];
    fill_array(arr, n);
    int result = multiply_array(arr, n);
    printf("Result: %s", int_to_string(result));
    printf("\n");
}

void set_background_color()
{
    printf("\nColor codes : ");
    printf("\n0 : black");
    print_colored("\n1 : blue",1,0);   // screen.h
	print_colored("\n2 : green",2,0);
	print_colored("\n3 : cyan",3,0);
	print_colored("\n4 : red",4,0);
	print_colored("\n5 : purple",5,0);
	print_colored("\n6 : orange",6,0);
	print_colored("\n7 : grey",7,0);
	print_colored("\n8 : dark grey",8,0);
	print_colored("\n9 : blue light",9,0);
	print_colored("\n10 : green light",10,0);
	print_colored("\n11 : blue lighter",11,0);
	print_colored("\n12 : red light",12,0);
	print_colored("\n13 : rose",13,0);
	print_colored("\n14 : yellow",14,0);
	print_colored("\n15 : white",15,0);

    printf("\n\n Text color ? : ");
    int text_color = str_to_int(keyboardcall());
	printf("\n\n Background color ? : ");
	int bg_color = str_to_int(keyboardcall());
	set_screen_color(text_color,bg_color);

    clearScreen();
}

int multiply_array(int arr[], int n)
{
    int i;
    int result = 1;
    for (i = 0; i < n; i++)
    {
        result *= arr[i];
    }
    return result;
}

void fill_array(int arr[],int n)
{
	int i = 0;
	for (i = 0;i<n;i++)
	{
        printf("ARR[%s]: ", int_to_string(i));
		arr[i] = str_to_int(keyboardcall());
		printf("\n");
	}
}