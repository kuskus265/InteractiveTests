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
}
