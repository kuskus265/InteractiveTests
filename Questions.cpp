#include "Questions.h"
//#include <stdio.h>

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

int SimpleTestQuestion(const char question[], const char tAnswr[], int count, char (*list)[STRING_LENGHT],FILE* output) //otázka, správná odpověď, počet špatných, špatné odpovědi
{
    char tAnswrCh; //písmneko správné odpovědi
    char userAnswr; //udpověď uživatele
    char answrs[count+1][STRING_LENGHT]; //pole všech odpovědí včetně správné
    int score = 0;

    printf("%s\n",question); //otázka
    fprintf(output,"\n%s\n",question);

    strcpy(answrs[0],tAnswr); //kopírování správné odpovědi do pole všech

    /*va_list list;
    va_start(list,count);

    for(int i = 0; i<count; i++) //kopírování špatných odpovědí z listu do pole všech
    {
        strcpy(answrs[i+1],va_arg(list,const char*));
    }
    va_end(list);*/

    for(int i = 0; i<count; i++) //kopírování špatných odpovědí z listu do pole všech
    {
        strcpy(answrs[i+1],list[i]);
    }

    Shuffle(answrs,count+1); //zamíchání

    for(int i = 0; i<count+1; i++) //projít odpovědi, připsat písmenko, najít správnou, uložit její písmenko
    {
        char answrChar = ASCII_a+i; //momentální písmenko otázky
        if(!strcmp(answrs[i],tAnswr)) //je tato odpověd správná?
        {
            tAnswrCh = answrChar; //pokud ano, ulož její písmenko
        }
        printf("%c) %s\n",answrChar,answrs[i]); //vypiš odpověď
        fprintf(output,"%c) %s\n",answrChar,answrs[i]);
    }

    do //cyklus pro zadání uživatelské odpovědi
    {
        printf("Answer: ");
        scanf(" %c",&userAnswr); //zadání odpovědi
        while (getchar() != '\n'); //vyprazdneni bufferu - přečte se jen první znak z několika zadaných a zbatek se smaže
        if(userAnswr > ASCII_a+count||userAnswr < ASCII_a) //pokud odpověď neopdovídá intervalu možností otázky
        {
            printf("Not defined answer: %c!\n",userAnswr);
        }
    } while (userAnswr > ASCII_a+count||userAnswr < ASCII_a); //opakuj, dokud není odpověď z intervalu
    
    fprintf(output,"Answer: %c\n",userAnswr);

    if(userAnswr == tAnswrCh)
    {
        printf("Correct! :)\n"); //pokud odpověď stejná jako správná odpověď
        fprintf(output,"Correct! :)\n");
        score = 1;
    }
    else 
    {
        printf("Wrong! :(\n");
        fprintf(output,"Wrong! :(\n");
    }
    /*printf("UA: %c\n",userAnswr);
    printf("TA: %c\n",tAnswrCh);*/
    printf("Press ENTER to continue!\n");
    getchar();
    system("@cls||clear"); //vymazání konzole

    if(score>0) return 1;
    else return 0;
}

int MultAnswrTestQuestion(const char question[], int countT, int countF, char (*list)[STRING_LENGHT],FILE* output) //otázka, počet správných odpovědí, počet špatných odpovědí, list - nejprv správné odpovědi, potom špatné
{
    int count = countT+countF;
    char tAnswrs[countT][STRING_LENGHT]; //pole správných odpovědí
    char tAnswrsCh[countT]; //písmenka správných odpovědí
    char userAnswr[count+1]; //udpověď uživatele
    char answrs[count][STRING_LENGHT]; //pole všech odpovědí včetně správné
    int k = 0; //pomocná proměnná
    int score = 0;

    printf("%s\n",question); //otázka
    fprintf(output,"\n%s\n",question);

    /*va_list list;
    va_start(list,countF);

    for(int i = 0; i < countT; i++)
    {
        strcpy(tAnswrs[i],va_arg(list,const char*)); //kopírování správných odpovědí z listu do pole správných
        strcpy(answrs[i],tAnswrs[i]); //kopírování správných odpovědí do pole všech
    }

    for(int i = 0; i<countF; i++) //kopírování špatných odpovědí z listu do pole všech
    {
        strcpy(answrs[i+countT],va_arg(list,const char*));
    }
    va_end(list);*/

    for(int i = 0; i < countT; i++)
    {
        strcpy(tAnswrs[i],list[i]); //kopírování správných odpovědí z listu do pole správných
        strcpy(answrs[i],tAnswrs[i]); //kopírování správných odpovědí do pole všech
    }

    for(int i = 0; i<countF; i++) //kopírování špatných odpovědí z listu do pole všech
    {
        strcpy(answrs[i+countT],list[i+countT]);
    }

    Shuffle(answrs,count); //zamíchání

    for(int i = 0; i<count; i++) //projít odpovědi, připsat písmenko, najít správnou, uložit její písmenko
    {
        char answrChar = ASCII_a+i; //momentální písmenko otázky
        for(int j = 0; j < countT; j++)
        {
            if(!strcmp(answrs[i],tAnswrs[j])) //je tato odpověd správná?
            {
                tAnswrsCh[k] = answrChar; //pokud ano, ulož její písmenko
                k++;
            }
        }
        printf("%c) %s\n",answrChar,answrs[i]); //vypiš odpověď
        fprintf(output,"%c) %s\n",answrChar,answrs[i]);
    }

    printf("Answers: ");
    scanf(" %s",&userAnswr[0]); //zadání odpovědí
    while (getchar() != '\n'); //vyprazdneni bufferu
    //printf("%s\n", userAnswr);
    //printf("%s\n", tAnswrsCh);
    fprintf(output,"Answers: %s\n",userAnswr);
    for(int i = 0; i < strlen(userAnswr); i++) //vyhodnocení odpovědí
    {
        if(userAnswr[i] > ASCII_a+count-1||userAnswr[i] < ASCII_a-1) //pokud odpověď neopdovídá intervalu možností otázky
        {
            if(userAnswr[i]=='\0') continue; //konec uživatelských odpovědí
            printf("Not defined answer: %c!\n",userAnswr[i]);
            fprintf(output,"Not defined answer: %c!\n",userAnswr[i]);
        }
        else
        {
            short int isCorrect = 0; //proměnná pro uložení správnosti odpovědi
            for(int j = 0; j < countT; j++)
            {
                if(userAnswr[i] == tAnswrsCh[j]) //pokud odpověď stejná jako nějaká ze správných
                {
                    tAnswrsCh[j] = '0';
                    isCorrect = 1;
                }
            }
            if(isCorrect) //pokud byla odpověd správná
            {
                printf("Correct! :)\n");
                fprintf(output,"Correct! :)\n");
                score++;
            }
            else 
            {
                printf("Wrong! :(\n");
                fprintf(output,"Wrong! :(\n");
                score = INT16_MIN; //žádné body
            }
        }
    }
    k=0;
    for (int i = 0; i < countT; i++) //vyhodnocení počtu neuhodlých správných odpovědí
    {
        if(tAnswrsCh[i]!='0') k++;
    }
    if(k)
    {
        printf("There are %d correct answers left.\n", k);
        fprintf(output,"There are %d correct answers left.\n", k);
        score = INT16_MIN; //žádné body
    }

    printf("Press ENTER to continue!\n");
    getchar();
    system("@cls||clear"); //vymazání konzole
    //printf("\n");

    if(score>0) return 1;
    else return 0;
}

int TextQuestion(const char question[], int count, char (*list)[STRING_LENGHT],FILE* output)
{
    char userAnswr[STRING_LENGHT];
    char answrs[count][STRING_LENGHT];
    short int isCorrect = 0;
    int score = 0;

    printf("%s\n",question); //otázka
    fprintf(output,"\n%s\n",question);

    /*va_list list;
    va_start(list,count);

    for(int i = 0; i<count; i++) //kopírování možných odpovědí z listu do pole
    {
        strcpy(answrs[i],va_arg(list,const char*));
    }
    va_end(list);*/
    
    for(int i = 0; i<count; i++) //kopírování možných odpovědí z listu do pole
    {
        strcpy(answrs[i],list[i]);
    }

    printf("Answer: ");
    scanf(" %[^\n]", &userAnswr[0]); //cti string i s mezerami
    //gets
    while (getchar() != '\n'); //vyprazdneni bufferu
    //printf("%s\n",userAnswr);
    fprintf(output,"Answer: %s\n",userAnswr);
    for(int i = 0; i < count; i++) //porovnani odpovedi se spravnymi
    {
        if(!strcmp(userAnswr, answrs[i])) isCorrect = 1;
    }

    if(isCorrect) //pokud byla odpověd správná
    {
        printf("Correct! :)\n");
        fprintf(output,"Correct! :)\n");
        score = 1;
    }
    else 
    {
        printf("Wrong! :(\n");
        fprintf(output,"Wrong! :(\n");
    }

    printf("Press ENTER to continue!\n");
    getchar();
    system("@cls||clear"); //vymazání konzole

    if(score>0) return 1;
    else return 0;
}