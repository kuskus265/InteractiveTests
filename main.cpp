#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define STRING_LENGHT 100

void Shuffle(char (*answrs)[STRING_LENGHT], int size) 
{
    for (int i = 0; i < size;) 
    {
        int j = i + rand() % (size - i);
        /* Reject this shuffle if the element we're about to place
        * is the same as the previous one
        */
        if (i > 0 && strcmp(answrs[j], answrs[i-1]) == 0) i = 0;
        else 
        {
            /* Otherwise, place element i and move to the next one*/
            char t[STRING_LENGHT];
            strcpy(t,answrs[i]);
            strcpy(answrs[i],answrs[j]);
            strcpy(answrs[j],t);
            /*char t = answrs[i];
            answrs[i] = answrs[j];
            answrs[j] = t;*/
            ++i;
        
        }   
    }
}

void SimpleQuestion(const char question[], const char tAnswr[], int count,...)
{
    printf("%s\n",question);

    char answrs[count+1][STRING_LENGHT];
    strcpy(answrs[0],tAnswr);

    va_list list;
    va_start(list,count);

    for(int i = 0; i<count; i++)
    {
        strcpy(answrs[i+1],va_arg(list,const char*));
    }
    va_end(list);

    Shuffle(answrs,count+1);

    for(int i = 0; i<count+1; i++)
    {
        printf("%s\n",answrs[i]);
    }
}

int main() 
{
    srand(time(NULL));
    printf("\n");
    SimpleQuestion("Otazka?","Je to otazka",3,"Neni","Nevim","Mozna");
}
