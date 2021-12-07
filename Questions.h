#pragma once

#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#define STRING_LENGHT 1000
#define ASCII_a 97

//enum categories{music,games,math};
const char categoriesN[][20] = {"music","games","math"};

struct testHeader
{
    char name[STRING_LENGHT];
    int category;
    unsigned short int position = 0;
};

void Shuffle(char (*answrs)[STRING_LENGHT], int size); //míchání otázek
int SimpleTestQuestion(const char question[], const char tAnswr[], int count, char (*list)[STRING_LENGHT],FILE* output); //jednoduchá otázka s 1 správnou odpovědí
int MultAnswrTestQuestion(const char question[], int countT, int countF, char (*list)[STRING_LENGHT],FILE* output); //více správných odpovědí
int TextQuestion(const char question[], int count, char (*list)[STRING_LENGHT],FILE* output); //textová otázka