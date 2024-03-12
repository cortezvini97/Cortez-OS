#include "shell.h"
#include "kernel.h"

void launch_shell(int n)
{
    string ch = (string) malloc(200);

    do
    {
        print("CORTEZOS (");
		print(int_to_string(n));
		print(")> ");
        ch = readStr();
        if(strEql(ch,"cmd"))
		{
		    print("\nYou are allready in cmd. A new recursive shell is opened\n");
			launch_shell(n+1);
		}else if(strEql(ch,"clear"))
        {
            clearScreen();
        }else if(strEql(ch,"exit")){
            print("\nbye");
        }else if(strEql(ch,"kernel --version")){
            kernelinfo();
        }else if(strEql(ch,"echo"))
        {
            echo();
        }
        else if(strEql(ch,"help"))
        {
            help();
        }else if(strEql(ch, "color"))
        {
            set_background_color();
        }else if (strEql(ch,"multiply")){
            multiply();
        }else if(strEql(ch,"sum"))
		{
		    sum();
		}else
        {
            print("\nInvalid Command.\n");
        }
    } while (!strEql(ch,"exit"));
    
}

void kernelinfo()
{
    string kernel_v = getKernelVersion();
    print("\n");
    print("kernel ");
    print(kernel_v);
    print("\n");
}

void echo()
{
    print("\n");
    print("Enter text Value: ");
	string str = readStr();
	print("\n");
    if(strEql(str, ""))
    {
        print("Empty text value");
        echo();
    }else
    {
	    print(str);
    }
	print("\n");
}

void set_background_color()
{
    print("\nColor codes : ");
    print("\n0 : black");
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

    print("\n\n Text color ? : ");
    int text_color = str_to_int(readStr());
	print("\n\n Background color ? : ");
	int bg_color = str_to_int(readStr());
	set_screen_color(text_color,bg_color);

    clearScreen();
}

void multiply()
{
    print("\nNum 1: ");
	int num1 = str_to_int(readStr());
	print("\nNum 2: ");
	int num2 = str_to_int(readStr());
	print("\nResult: ");
	print(int_to_string(num1*num2));
	print("\n");
}

void sum()
{
    print("\nHow many numbers: ");
	int n = str_to_int(readStr());
	int i =0;
	print("\n");
	int arr[n];
	fill_array(arr,n);
	int s = sum_array(arr,n);
	print("Result: ");
	print(int_to_string(s));
	print("\n");
}

void help()
{
    print("\ncmd                   : Launch a new recursive Shell");
    print("\nsum                   : Computes the sum of n numbers");
	print("\nmultiply              : Computes the multiply of n numbers");
	print("\nclear                 : Clears the screen");
    print("\nexit                  : Quits the current shell");
    print("\necho                  : Reprint a given text");
    print("\ncolor                 : Changes the colors of the terminal");
    print("\nkernel --version      : Get Kernel Version");

    print("\n\n");
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

void fill_array(int arr[],int n)
{
	int i = 0;
	for (i = 0;i<n;i++)
	{
		print("ARR[");
		print(int_to_string(i));
		print("]: ");
		arr[i] = str_to_int(readStr());
		print("\n");
	}
}