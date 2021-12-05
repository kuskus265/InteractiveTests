#include <time.h>
#include "Questions.h"

int main() 
{
    srand(time(NULL));

    printf("\n");

    FILE* header = fopen("headers.txt","r"); //načtení hlavičkového souboru
    int numOfTests = getc(header)-'0'; //pocet testů celkem
    getc(header); //cteni konce radku
    struct testHeader testHeaders[numOfTests];
    for(int i = 0; i < numOfTests; i++) //načtení hlaviček testů do pole
    {
        char temp[STRING_LENGHT]; //temporary string pro hodnotu kategorie
        fgets(testHeaders[i].name, STRING_LENGHT, header);
        testHeaders[i].name[strcspn(testHeaders[i].name, "\n")] = 0; //odstranění end of line
        fgets(temp, STRING_LENGHT, header);
        testHeaders[i].category = atoi(temp); //převod ze string na int
    }
    fclose(header);

    categoryMenu: //návrat na výběr kategorie
    int numOfCat = sizeof(categoriesN) / sizeof(categoriesN[0]); //počet kategorií
    for(int i = 0; i < numOfCat;i++)
    {
        printf("%d) %s\n",i+1,categoriesN[i]); //tisk kategorií
    }

    unsigned int chosenCategory; //vybraná kategorie
    do
    {
        printf("Choose category: ");
        scanf("%d", &chosenCategory);
        chosenCategory == 0 ? chosenCategory = numOfCat + 1 : chosenCategory=chosenCategory; //znemožnění nuly
        if(chosenCategory > numOfCat) printf("Not defined category!\n");
    } while (chosenCategory > numOfCat);

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
