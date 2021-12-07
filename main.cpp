#include <sys/time.h>
#include "Questions.h"

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
    printf("Address is: %s\n", testAddr);

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
    printf("%s:\n",name);
    printf("\nTime: %.3f s\n", timeTaken);
    printf("Score: %d out of %d\n",score,numOfQuestions);

    fprintf(output,"%s:\n",name);
    fprintf(output,"Time: %.3f s\n", timeTaken);
    fprintf(output,"Score: %d out of %d\n",score,numOfQuestions);

    fclose(output);

    printf("Press ENTER to go to the menu!\n");
    getchar();
    system("@cls||clear"); //vymazání konzole
    goto categoryMenu; // návrat do menu
    
    /*int poc = 3;
    char spatneOdp[poc][STRING_LENGHT] = {"jedna","DVA","3"};
    SimpleTestQuestion("Test","Spravna",poc,spatneOdp);*/
    /*int pocT = 2; int pocF = 3;
    char odpovedi[pocT+pocF][STRING_LENGHT] = {"Spravna1","Spravna 2","SpOdp","SpatnODp","Nope"};
    MultAnswrTestQuestion("Test Mult.",pocT,pocF,odpovedi);*/
    /*int poc = 3;
    char odpovedi[poc][STRING_LENGHT] = {"Spravne","správně","spravne"};
    TextQuestion("Spravne?",poc,odpovedi);*/

    /*printf("\n");
    SimpleTestQuestion("Otazka?","Je to otazka",3,"Neni","Nevim","Mozna");
    SimpleTestQuestion("Find the impostor","000O000000",9,"0000000000","0000000000","0000000000"
    ,"0000000000","0000000000","0000000000","0000000000","0000000000","0000000000");
    SimpleTestQuestion("Jsem dobrej?","Ano",1,"Ne");
    MultAnswrTestQuestion("Ovoce?",3,4,"Jablko","Boruvka","Malina","Meloun","Okurka","Brambora","Chleba");
    MultAnswrTestQuestion("Never gonna...",2,2,"give you up","let you down","say hello","make you smile");
    TextQuestion("x/8 = 1\nx = ?",3,"8","osm","eight"); //pro výpočty to bude chtít vlastní typ otázky možná
    TextQuestion("Běží ovce běží,\nu nohou jim sněží\na pod nohou jehňata,\nsvítí jako ze zlata.",
    4,"kameny a oblazky v rece","kameny a oblázky v řece","kameny a kaminky v rece","kameny a kamínky v řece");*/
}
