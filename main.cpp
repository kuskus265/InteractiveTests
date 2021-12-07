#include <sys/time.h>
#include "Questions.h"
#include <unistd.h>

int main() 
{
    srand(time(NULL));

    printf("\n");

    char name[STRING_LENGHT];
    printf("Please enter your name: ");
    scanf("%s",&name[0]);

    char temp[STRING_LENGHT]; //temporary string pro int a chvilkové věci xD
    FILE* header = fopen("headers.txt","r"); //načtení hlavičkového souboru
    int numOfTests = atoi(fgets(temp, STRING_LENGHT, header)); //pocet testů celkem
    struct testHeader testHeaders[numOfTests];
    for(int i = 0; i < numOfTests; i++) //načtení hlaviček testů do pole
    {
        fgets(testHeaders[i].name, STRING_LENGHT, header);
        testHeaders[i].name[strcspn(testHeaders[i].name, "\n")] = 0; //odstranění end of line
        fgets(temp, STRING_LENGHT, header);
        testHeaders[i].category = atoi(temp); //převod ze string na int
    }
    fclose(header);

    categoryMenu: //návrat na výběr kategorie - ano, je tady goto, ale je jen jedno místo, kam se program vrací :D
    int numOfCat = sizeof(categoriesN) / sizeof(categoriesN[0]); //počet kategorií
    for(int i = 0; i < numOfCat;i++)
    {
        printf("%d) %s\n",i+1,categoriesN[i]); //tisk kategorií
    }
    printf("%d) Exit program\n",numOfCat+1); //konec programu

    unsigned int chosenCategory; //vybraná kategorie
    do
    {
        printf("Choose category: ");
        scanf("%d", &chosenCategory);
        if(chosenCategory==numOfCat+1) return 0; //ukončí program
        chosenCategory == 0 ? chosenCategory = numOfCat + 10 : chosenCategory=chosenCategory; //znemožnění nuly
        if(chosenCategory > numOfCat) printf("Not defined category!\n");
    } while (chosenCategory > numOfCat);
    system("@cls||clear"); //vymazání konzole

    unsigned short int position = 1; //pozice v tisknutém seznamu
    for(int i = 0; i < numOfTests; i++)
    {
        if(testHeaders[i].category == chosenCategory) //projde pole testů a vypíše jen vybranou kategorii
        {
            testHeaders[i].position = position;
            printf("%d) %s\n",position,testHeaders[i].name);
            position++; //navýšení pozice
        }
        else testHeaders[i].position = 0; //nulování pozice testu - podle toho se bude hledat vybraný test
    }
    printf("%d) Back\n",position); //vytištění možnosti zpět

    unsigned int chosenTestPosition; //vybraný test (pozice v menu = tesHeaders.position)
    do
    {
        printf("Choose test: ");
        scanf("%d", &chosenTestPosition);
        if(chosenTestPosition > position || chosenTestPosition == 0) printf("Not defined test!\n");
    } while (chosenTestPosition > position || chosenTestPosition == 0);
    if(chosenTestPosition == position)
    {
        system("@cls||clear"); //vymazání konzole
        goto categoryMenu; //pokud zvolena možnost zpět, jdi na začítek menu kategorií
    }

    struct testHeader chosenTest;
    for(int i = 0; i < numOfTests; i++) //hledání vybraného testu
    {
        if(testHeaders[i].position == chosenTestPosition)
        {
            chosenTest = testHeaders[i];
            break;
        }
    }
    printf("\nYou have chosen test: %s\n", chosenTest.name);

    char testAddr[STRING_LENGHT] = "tests/"; //adresa testu
    strcat(testAddr,chosenTest.name);
    strcat(testAddr,".txt");
    //printf("Address is: %s\n", testAddr);

    while (getchar() != '\n'); //vyprazdneni bufferu
    printf("Press ENTER to start test!\n");
    getchar();
    system("@cls||clear"); //vymazání konzole

    int numOfQuestions; //počet otázek
    int score = 0;

    FILE* output = fopen("output.txt","w");
    fprintf(output,"%s\n",chosenTest.name);

    FILE* testf = fopen(testAddr,"r"); //otevři test
    numOfQuestions = atoi(fgets(temp, STRING_LENGHT, testf)); //převod počtu otázek na int

    struct timeval begin, end; //structy pro začátek a konec testu (čas)
    gettimeofday(&begin, 0); //čas začátku
    
    for(int i = 0; i < numOfQuestions; i++) //opakuj podle počtu otázek v testu
    {
        char question[STRING_LENGHT];
        switch (atoi(fgets(temp, STRING_LENGHT, testf))) //větvení podle typu otázky
        {
            case 1: //jedna správná odpověď
            {
                fgets(question, STRING_LENGHT, testf); //otázka
                question[strcspn(question, "\n")] = 0; //odstranění end of line
                while(strcspn(question, "\\")!=strlen(question))question[strcspn(question, "\\")] = '\n'; // znak \ v souboru znamená \n
                int count = atoi(fgets(temp, STRING_LENGHT, testf)); //počet špatných odpovědí v int
                char tAnswr[STRING_LENGHT];
                char list[count][STRING_LENGHT];
                fgets(tAnswr, STRING_LENGHT, testf); //správná odpoěď
                tAnswr[strcspn(tAnswr, "\n")] = 0; //odstranění end of line
                for (int i = 0; i < count; i++) //čtení špatých odpovědí
                {
                    fgets(list[i], STRING_LENGHT, testf);
                    list[i][strcspn(list[i], "\n")] = 0; //odstranění end of line
                }

                score = score + SimpleTestQuestion(question,tAnswr,count,list,output); //volání funkce otázky s přečtenými daty
                
                break;
            }
            case 2: //více správných odpovědí
            {
                fgets(question, STRING_LENGHT, testf); //otázka
                question[strcspn(question, "\n")] = 0; //odstranění end of line
                while(strcspn(question, "\\")!=strlen(question))question[strcspn(question, "\\")] = '\n'; // znak \ v souboru znamená \n
                int countT = atoi(fgets(temp, STRING_LENGHT, testf)); //počet správných odpovědí v int
                int countF = atoi(fgets(temp, STRING_LENGHT, testf)); //počet špatných odpovědí v int
                char list[countT+countF][STRING_LENGHT];
                for (int i = 0; i < countT+countF; i++) //čtení správných a špatných odpovědí
                {
                    fgets(list[i], STRING_LENGHT, testf);
                    list[i][strcspn(list[i], "\n")] = 0; //odstranění end of line
                }

                score = score + MultAnswrTestQuestion(question,countT,countF,list,output); //volání funkce otázky s přečtenými daty

                break;
            }
            case 3: //textová odpověď
            {
                fgets(question, STRING_LENGHT, testf); //otázka
                question[strcspn(question, "\n")] = 0; //odstranění end of line
                while(strcspn(question, "\\")!=strlen(question))question[strcspn(question, "\\")] = '\n'; // znak \ v souboru znamená \n
                int count = atoi(fgets(temp, STRING_LENGHT, testf)); //počet správných odpovědí v int
                char list[count][STRING_LENGHT];
                for (int i = 0; i < count; i++) //čtení správných odpovědí
                {
                    fgets(list[i], STRING_LENGHT, testf);
                    list[i][strcspn(list[i], "\n")] = 0; //odstranění end of line
                }

                score = score + TextQuestion(question,count,list,output); //volání funkce otázky s přečtenými daty

                break;
            }
        }
        fgets(temp, STRING_LENGHT, testf); //čtení oddělovače otázek - ?!!**
        temp[strcspn(temp, "\n")] = 0; //odstranění end of line - kdyby bylo potřeba s tím pracovat
    }
    fclose(testf);

    gettimeofday(&end, 0); //čas konce
    double timeTaken = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6; //výpočet času

    char statsAddr[STRING_LENGHT] = "stats/"; //adresa statistik testu
    strcat(statsAddr,chosenTest.name);
    strcat(statsAddr,"_stats.txt");
    printf("Address is: %s\n", statsAddr);
    FILE* stats = fopen(statsAddr,"r");
    /*if( access( statsAddr, F_OK ) == 0 ) {
        printf("File exists\n");
    } else {
        printf("File not exists\n");
    }*/
    if(stats == NULL)
    {
        stats = fopen(statsAddr,"w");
        fprintf(stats,"1\n%s\n0\n0\n0",name);
        fclose(stats);
        stats = fopen(statsAddr,"r");
    }

    int numOfUsers = atoi(fgets(temp, STRING_LENGHT, stats));
    printf("%d - int\n",numOfUsers);
    struct testStat testStats[numOfUsers+1];
    struct testStat statsOfUser;
    for(int i = 0; i < numOfUsers; i++)
    {
        printf("test\n");
        fgets(testStats[i].userName, STRING_LENGHT, stats);
        testStats[i].userName[strcspn(testStats[i].userName, "\n")] = 0; //odstranění end of line
        fscanf(stats,"%f",&testStats[i].avgScore);
        fgetc(stats);
        //testStats[i].avgScore = atoi(fgets(temp, STRING_LENGHT, stats));
        fscanf(stats,"%f",&testStats[i].avgTime);
        fgetc(stats);
        //testStats[i].avgTime = atoi(fgets(temp, STRING_LENGHT, stats));
        testStats[i].numOfAttempts = atoi(fgets(temp, STRING_LENGHT, stats));
    }
    fclose(stats);

    printf("test1\n");

    short int isNew = 1;
    for(int i = 0; i < numOfUsers+1; i++)
    {
        printf("test2\n");
        if(testStats[i].userName == name)
        {
            isNew = 0;
            testStats[i].numOfAttempts++;
            testStats[i].avgScore = (testStats[i].avgScore + score)/testStats[i].numOfAttempts;
            testStats[i].avgTime = (testStats[i].avgTime + timeTaken)/testStats[i].numOfAttempts;
            statsOfUser = testStats[i];
        }
    }
    if(isNew)
    {
        int i = numOfUsers+1;
        testStats[i].userName == name;
        testStats[i].numOfAttempts++;
        testStats[i].avgScore = (testStats[i].avgScore + score)/testStats[i].numOfAttempts;
        testStats[i].avgTime = (testStats[i].avgTime + timeTaken)/testStats[i].numOfAttempts;
        statsOfUser = testStats[i];
    }

    printf("\n%s:\n",name);
    printf("\nTime: %.3f s\n", timeTaken);
    printf("Average time: %.3f s\n",statsOfUser.avgTime);
    printf("\nScore: %d out of %d\n",score,numOfQuestions);
    printf("Average score: %f\n",statsOfUser.avgScore);
    printf("Number of attempts: %d",statsOfUser.numOfAttempts);

    fprintf(output,"%s:\n",name);
    fprintf(output,"\nTime: %.3f s\n", timeTaken);
    fprintf(output,"Average time: %.3f s\n",statsOfUser.avgTime);
    fprintf(output,"\nScore: %d out of %d\n",score,numOfQuestions);
    fprintf(output,"Average score: %f\n",statsOfUser.avgScore);
    fprintf(output,"Number of attempts: %d\n",statsOfUser.numOfAttempts);

    fclose(output);

    stats = fopen(statsAddr,"w");
    fprintf(stats,"%d",numOfUsers+1);
    for(int i = 0; i < numOfUsers+1; i++)
    {
        fprintf(stats,"%s\n%f\n%f\n%d",testStats[i].userName,testStats[i].avgScore,testStats[i].avgTime,testStats[i].numOfAttempts);
    }
    fclose(stats);

    printf("Press ENTER to go to the menu!\n");
    getchar();
    system("@cls||clear"); //vymazání konzole
    goto categoryMenu; // návrat do menu
}
