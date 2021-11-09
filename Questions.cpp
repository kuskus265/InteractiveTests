#include "Questions.h"

void Shuffle(char (*answrs)[STRING_LENGHT], int size) //pole stringů, jeho velikost
{
    for (unsigned int i = 0; i < size;) //pro každou adresu
    {
        unsigned int j = i + rand() % (size - i); //random jiná adresa
        char t[STRING_LENGHT]; //temporary
        strcpy(t,answrs[i]); //prohození
        strcpy(answrs[i],answrs[j]);
        strcpy(answrs[j],t);
        ++i;
    }
}

void SimpleTestQuestion(const char question[], const char tAnswr[], int count,...) //otázka, správná odpověď, počet špatných, špatné odpovědi
{
    char tAnswrCh; //písmneko správné odpovědi
    char userAnswr; //udpověď uživatele
    char answrs[count+1][STRING_LENGHT]; //pole všech odpovědí včetně správné

    printf("%s\n",question); //otázka

    strcpy(answrs[0],tAnswr); //kopírování správné odpovědi do pole všech

    va_list list;
    va_start(list,count);

    for(int i = 0; i<count; i++) //kopírování špatných odpovědí z listu do pole všech
    {
        strcpy(answrs[i+1],va_arg(list,const char*));
    }
    va_end(list);

    Shuffle(answrs,count+1); //zamíchání

    for(int i = 0; i<count+1; i++) //projít odpovědi, připsat písmenko, najít správnou, uložit její písmenko
    {
        char answrChar = ASCII_a+i; //momentální písmenko otázky
        if(!strcmp(answrs[i],tAnswr)) //je tato odpověd správná?
        {
            tAnswrCh = answrChar; //pokud ano, ulož její písmenko
        }
        printf("%c) %s\n",answrChar,answrs[i]); //vypiš odpověď
    }

    do //cyklus pro zadání uživatelské odpovědi
    {
        printf("Answer: ");
        scanf(" %c",&userAnswr); //zadání odpovědi
        while (getchar() != '\n'); //vyprazdneni bufferu - přečte se jen první znak z několika zadaných a zbatek se smaže
        if(userAnswr > ASCII_a+count||userAnswr < ASCII_a) //pokud odpověď neopdovídá intervalu možností otázky
        {
            printf("Not defined answer!\n");
        }
    } while (userAnswr > ASCII_a+count||userAnswr < ASCII_a); //opakuj, dokud není odpověď z intervalu
    
    if(userAnswr == tAnswrCh) printf("Correct! :)\n"); //pokud odpověď stejná jako správná odpověď
    else printf("Wrong! :(\n");
    /*printf("UA: %c\n",userAnswr);
    printf("TA: %c\n",tAnswrCh);*/
    printf("\n");
}