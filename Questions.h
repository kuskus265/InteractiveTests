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
void SimpleTestQuestion(const char question[], const char tAnswr[], int count,...); //jednoduchá otázka s 1 správnou odpovědí
void MultAnswrTestQuestion(const char question[], int countT, int countF,...); //více správných odpovědí
void TextQuestion(const char question[], int count,...); //textová otázka