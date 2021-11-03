#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define STRING_LENGHT 1000
#define ASCII_a 97

void Shuffle(char (*answrs)[STRING_LENGHT], int size) 
{
    for (unsigned int i = 0; i < size;) 
    {
        unsigned int j = i + rand() % (size - i);
        
        /* Reject this shuffle if the element we're about to place
        * is the same as the previous one
        */
        /*if (i > 0 && strcmp(answrs[j], answrs[i-1]) == 0) i = 0;
        else 
        {*/
            /* Otherwise, place element i and move to the next one*/
            char t[STRING_LENGHT];
            strcpy(t,answrs[i]);
            strcpy(answrs[i],answrs[j]);
            strcpy(answrs[j],t);
            /*char t = answrs[i];
            answrs[i] = answrs[j];
            answrs[j] = t;*/
            ++i;
        
        //}   
    }
}

void SimpleTestQuestion(const char question[], const char tAnswr[], int count,...)
{
    char tAnswrCh;
    char userAnswr;
    char answrs[count+1][STRING_LENGHT];

    printf("%s\n",question);

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
        char answrChar = ASCII_a+i;
        if(!strcmp(answrs[i],tAnswr))
        {
            tAnswrCh = answrChar;
        }
        printf("%c) %s\n",answrChar,answrs[i]);
    }

    do
    {
        printf("Answer: ");
        scanf(" %c",&userAnswr);
        if(userAnswr > ASCII_a+count||userAnswr < ASCII_a)
        {
            printf("Not defined answer!\n");
        }
    } while (userAnswr > ASCII_a+count||userAnswr < ASCII_a);
    
    if(userAnswr == tAnswrCh) printf("Correct! :)\n");
    else printf("Wrong! :(\n");
    /*printf("UA: %c\n",userAnswr);
    printf("TA: %c\n",tAnswrCh);*/
    printf("\n");
}

int main() 
{
    srand(time(NULL));
    printf("\n");
    SimpleTestQuestion("Otazka?","Je to otazka",3,"Neni","Nevim","Mozna");
    SimpleTestQuestion("Find the impostor","000O000000",9,"0000000000","0000000000","0000000000"
    ,"0000000000","0000000000","0000000000","0000000000","0000000000","0000000000");
    SimpleTestQuestion("Jsem dobrej?","Ano",1,"Ne");
}
