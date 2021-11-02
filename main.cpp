#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define STRING_LENGHT 100

/*void shuffle(char arr[][STRING_LENGHT], size_t n) {
  for (size_t i = 0; i < n;) 
  {
    size_t j = i + rand() % (n - i);
    // Reject this shuffle if the element we're about to place
    // is the same as the previous one
    // 
    if (i > 0 && strcmp(arr[j], arr[i-1]) == 0) i = 0;
    else 
    {
    //   Otherwise, place element i and move to the next one
      char t[] = arr[i];
      arr[i] = arr[j];
      arr[j] = t;
      ++i;
    }
  }
}*/

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

    //shuffle(answrs,count+1);

    printf("%s\n%s\n%s\n",answrs[0],answrs[1],answrs[2]);
    
}

int main() 
{
    srand(time(NULL));
    printf("\n");
    SimpleQuestion("Otazka?","Je to otazka",2,"Neni","Nevim");
}
