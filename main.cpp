#include <time.h>
#include "Questions.h"

int main() 
{
    srand(time(NULL));
    printf("\n");
    SimpleTestQuestion("Otazka?","Je to otazka",3,"Neni","Nevim","Mozna");
    SimpleTestQuestion("Find the impostor","000O000000",9,"0000000000","0000000000","0000000000"
    ,"0000000000","0000000000","0000000000","0000000000","0000000000","0000000000");
    SimpleTestQuestion("Jsem dobrej?","Ano",1,"Ne");
    MultAnswrTestQuestion("Ovoce?",3,4,"Jablko","Boruvka","Malina","Meloun","Okurka","Brambora","Chleba");
    MultAnswrTestQuestion("Never gonna...",2,2,"give you up","let you down","say hello","make you smile");
    TextQuestion("x/8 = 1\nx = ?",3,"8","osm","eight"); //pro výpočty to bude chtít vlastní typ otázky možná
    TextQuestion("Běží ovce běží,\nu nohou jim sněží\na pod nohou jehňata,\nsvítí jako ze zlata.",
    4,"kameny a oblazky v rece","kameny a oblázky v řece","kameny a kaminky v rece","kameny a kamínky v řece");
}
