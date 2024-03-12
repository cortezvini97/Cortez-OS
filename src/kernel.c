#include "kernel.h"

void main_kernel()
{
    string ch = (string) malloc(200);
    isr_install();
    clearScreen();
	print("Welcome to Cortez OS\nPlease enter a command\n");
    /*int loop = 1;
    while (loop)
    {
        print("\nCORTEZOS> ");
        ch = readStr();
        print("\n");
        if(strEql(ch,"cmd"))
		{
		    print("\nYou are allready in cmd. A new recursive shell is opened\n");
		}else if(strEql(ch,"clear"))
		{
            clearScreen();
		}else if(strEql(ch,"exit")){
            print("bye");
            loop = 0;
        }       
    }*/
    launch_shell(0);
}

string getKernelVersion()
{
    return "v1.0.0";
}