#include <stdio.h>
int custom_len(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }        
    return i;
}

char* read_line_dynamic()
{
    char *string;
    fgets(string, 10000000, stdin); //rückgabe wert überpüfung fehlt 
    custom_len(string);
    *string = malloc(custom_len(string));


}
