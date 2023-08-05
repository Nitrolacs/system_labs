/*! Код дочернего процесса программы */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "structure.h"

#define CORRECT_INPUT 2
#define END_STRING '\n'
#define THREE_LINES 1
#define TWO_LINES  2

#define BACKSPACE_KEY 8
#define START_CHAR_RANGE 32
#define END_CHAR_RANGE 126

char* StringInput(int* stringSize)
{
    char* userStr = (char*)malloc(1 * sizeof(char));
    userStr[0] = '\0';
    char curChar = 0;
    int curSize = 1;

    printf("Введите комплексное число: ");
    while(curChar != '\n')
    {
        curChar = getchar();

        int deltaVal = 0; // Определяет, на сколько изменится длина массива
        int lengthDif = 0;

        // Если мы стираем символы, а не пишем их,
        if (curChar == BACKSPACE_KEY)
        {
            deltaVal = -1; // то будем уменьшать длину массива
            lengthDif = 1; // и копировать строку до предпоследнего символа
        }

            // Иначе проверяем, входит ли введённый символ в диапазон печатных
        else
        {
            if (curChar >= START_CHAR_RANGE && curChar <= END_CHAR_RANGE)
            {
                deltaVal = 1; // Если да, то будем увеличивать длину на 1
                lengthDif = 2; // Не заполняем последние 2 символа -
                // оставляем место для введённого символа и '\0'
            }
            else
            {
                continue; // Если это не печатный символ, то пропускаем его
            }
        }

        // Если стирать больше нечего, но пользователь
        // всё равно жмёт Backspace.
        int newSize = curSize + deltaVal;
        if (newSize == 0)
        {
            continue; // то мы переходим на следующую итерацию - ждём '\n'
        }

        char* tmpStr = (char*)malloc(newSize * sizeof(char));
        if (tmpStr) // Проверяем, выделилась ли память
        {
            // Идём до предпоследнего символа, т.к. надо в конец записать '\0'
            for (int i = 0;
                 i < newSize - lengthDif;
                 ++i)
            {
                tmpStr[i] = userStr[i];
            }

            if (curChar != BACKSPACE_KEY) // Если введён печатный символ,
            {
                tmpStr[newSize - 2] = curChar; // Добавляем его в строку
                tmpStr[newSize - 1] = '\0';
            }
            free(userStr);
            userStr = tmpStr;
            curSize = newSize;
        }
        else
        {
            printf("Не могу выделить память под обновлённую строку!");
            break;
        }
    }

    *stringSize = curSize - 1;
    return userStr;
}

char* concatenate(const char* firstStr, const char* secondStr,
                  const char* thirdStr) {
    size_t firstLength = strlen(firstStr);
    size_t secondLength = strlen(secondStr);
    size_t thirdLength = strlen(thirdStr);

    char *res = malloc(firstLength + secondLength  + thirdLength  + 1);
    if (res) {
        memcpy(res, firstStr, firstLength);
        memcpy(res + firstLength, secondStr, secondLength);
        memcpy(res + firstLength + secondLength, thirdStr,
               thirdLength + 1);
    }
    return res;
}

void ComplexNumberInput(char** userStr, int* strSize, complex* cmpNumber)
{
    char* message = "Неверный ввод. Попробуйте снова.\n";
    char* findSearch = NULL;

    bool isValid = false;

    int result = 0;

    float firstNumberF = 0.0, secondNumberF = 0.0;
    int firstNumberI = 0;

    while (!isValid)
    {
        *userStr = StringInput(strSize);

        if (strstr(*userStr, ".i") != NULL)
        {
            findSearch = ".i";
        }
        else if (strstr(*userStr, ".+i") != NULL)
        {
            findSearch = ".+i";
        }

        else if (strstr(*userStr, ".-i") != NULL)
        {
            findSearch = ".-i";
        }

        if (findSearch != NULL)
        {
            result = sscanf(*userStr,
                            concatenate("%f", findSearch,
                                        "%f"),
                            &firstNumberF, &secondNumberF);

            if (result != 2)
            {
                firstNumberF = secondNumberF = 0.0;

                result = sscanf(*userStr, concatenate("%d",
                                                      findSearch,
                                                      "%f"),
                                &firstNumberI, &secondNumberF);
            }
        }

        if (result == 2)
        {

            if (firstNumberI != 0)
            {
                cmpNumber -> real = firstNumberI;
            }
            else
            {
                cmpNumber -> real = firstNumberF;
            }

            if (findSearch[1] == '-')
            {
                cmpNumber -> imag = -secondNumberF;
            }
            else
            {
                cmpNumber -> imag = secondNumberF;
            }

            isValid = true;
        }
        else
        {
            printf("%s", message);
        }
    }
}

void CheckOperation(char* userStr, int userChoice)
{
    const char message[] = "Введите символ операции: ";
    char inputChar = '\0';
    char* pch;
    char* symbols;

    printf("%s", message);
    int input = scanf("%c%c", &*userStr, &inputChar);

    if (userChoice == TWO_LINES)
    {
        symbols = "IRS";
    }
    else
    {
        symbols = "+-*/";
    }

    pch=strchr(symbols, *userStr);

    while (input != CORRECT_INPUT || inputChar != END_STRING ||
           pch == NULL)
    {
        if (pch == NULL && inputChar != END_STRING)
        {
            while ((inputChar = getchar()) != '\n');
        }
        *userStr = 0;
        printf("Неверный ввод. Попробуйте снова.\n%s", message);

        input = scanf("%c%c", &*userStr, &inputChar);
        pch=strchr(symbols, *userStr);
    }
}

void RowFilling(char** firstUserStr, int* firstStrSize, char* secondUserStr,
                char** thirdUserStr, int* thirdStrSize,  int userChoice,
                complex* firstNumber, complex* secondNumber)
{
    printf("--------------\n");
    printf("| Ввод строк |\n");
    printf("--------------\n");

    ComplexNumberInput(firstUserStr, firstStrSize,
                       firstNumber);

    CheckOperation(secondUserStr, userChoice);

    if (userChoice == THREE_LINES)
    {
        ComplexNumberInput(thirdUserStr, thirdStrSize,
                           secondNumber);
    }
}

void ThreeStringOperation(complex firstNumber, char operation,
                          complex secondNumber, complex* result)
{
    if (operation == '+')
    {
        result -> real = firstNumber.real + secondNumber.real;
        result -> imag = firstNumber.imag + secondNumber.imag;
        
        if (result -> imag >= 0)
        {
            printf("Сумма двух чисел: %.1f.i%.1f\n", result -> real,
                   result -> imag);
        }
        else
        {
            printf("Сумма двух чисел: %.1f.-i%.1f\n", result -> real,
                   fabsf(result -> imag));
        }
    }

    else if (operation == '-')
    {
        result -> real = firstNumber.real - secondNumber.real;
        result -> imag = firstNumber.imag - secondNumber.imag;
        
        if (result -> imag >= 0)
        {
            printf("Разность двух чисел: %.1f.i%.1f\n", result -> real,
                   result -> imag);
        }
        else
        {
            printf("Разность двух чисел: %.1f.-i%.1f\n", result -> real,
                   fabsf(result -> imag));
        }
    }

    else if (operation == '*')
    {
        result -> real = firstNumber.real * secondNumber.real -
                      firstNumber.imag * secondNumber.imag;
        result -> imag = firstNumber.imag * secondNumber.real +
                      firstNumber.real * secondNumber.imag;
        
        if (result -> imag >= 0)
        {
            printf("Произведение двух чисел: %.1f.i%.1f\n", result -> real,
                   result -> imag);
        }
        else
        {
            printf("Произведение двух чисел: %.1f.-i%.1f\n", result -> real,
                   fabsf(result -> imag));
        }
    }

    else if (operation == '/')
    {
        float x, y, z;

        if (secondNumber.real == 0 && secondNumber.imag == 0)
            printf("Деление на 0 + 0i не разрешено.");
        else
        {
            x = firstNumber.real * secondNumber.real +
                firstNumber.imag * secondNumber.imag;

            y = firstNumber.imag * secondNumber.real - 
                firstNumber.real * secondNumber.imag;

            z = secondNumber.real * secondNumber.real + 
                secondNumber.imag * secondNumber.imag;

            if (fmodf(x, z) == 0.0 && fmodf(y, z) == 0.0)
            {
                if (y/z >= 0.0)
                    printf("Деление двух чисел: %.1f.i%.1f\n",
                           x/z, y/z);
                else
                    printf("Деление двух чисел: %.1f.-i%.1f\n",
                           x/z, fabsf(y/z));
            }

            else if (fmodf(x, z) == 0.0 && fmodf(y, z) != 0.0)
            {
                if (y/z >= 0.0)
                    printf("Деление двух чисел: %.1f.i%.1f/%.1f\n",
                           x/z, y, z);
                else
                    printf("Деление двух чисел: %.1f.-i%.1f/%.1f\n",
                           x/z, fabsf(y), z);
            }

            else if (fmodf(x, z) != 0.0 && fmodf(y, z) == 0.0)
            {
                if (y/z >= 0)
                    printf("Деление двух чисел: %.1f/%.1f.i%.1f\n",
                           x, z, y/z);
                else
                    printf("Деление двух чисел: %.1f.-i%.1f/%.1f\n",
                           x, fabsf(z), y/z);
            }

            else
            {
                if (y/z >= 0)
                    printf("Деление двух чисел: %.1f/%.1f.i%.1f/%.1f\n",
                           x, z, y, z);
                else
                    printf("Деление двух чисел: %.1f/%.1f.-i%.1f/%.1f\n",
                           x, z, fabsf(y), z);
            }
        }
    }
}

void TwoStringOperation(complex number, char operation, complex* result)
{
    if (operation == 'S')
    {
        result -> imag = -number.imag;
        if (number.imag >= 0)
        {
            printf("Комплексно-сопряженное число: %.1f.-i%.1f\n",
                   number.real, number.imag);
        }
        else
        {
            printf("Комплексно-сопряженное число: %.1f.i%.1f\n",
                   number.real, fabsf(number.imag));
        }
    }

    else if (operation == 'R')
    {
        result -> real = number.real;
        printf("Вещественная часть: %.1f\n", number.real);
    }

    else
    {
        result -> imag = number.imag;
        printf("Мнимая часть: %.1f\n", number.imag);
    }
}

int CheckingInput(const char message[], int lowerBound, int count)
{
    int userInput = 1;
    char inputChar = '\0';

    printf("%s", message);
    int input = scanf("%d%c", &userInput, &inputChar);

    while (input != CORRECT_INPUT || inputChar != END_STRING
           || userInput < lowerBound || userInput > count)
    {
        if (userInput >= lowerBound && userInput <= count)
        {
            while ((inputChar = getchar()) != '\n');
        }
        userInput = 1;
        printf("Неверный ввод. Попробуйте снова.\n%s", message);
        input = scanf("%d%c", &userInput, &inputChar);
    }
    return userInput;
}

void PrintMenu(void)
{
    printf("---------------\n");
    printf("| Выбор ввода |\n");
    printf("---------------\n");
    printf("1 - Ввод 3 строк (комплексные числа и знак операции)\n");
    printf("2 - Ввод 2 строк (комплексное число и операция)\n");
}

#ifndef DOING_UNIT_TESTS
int main(void)
{
    printf("-----------------------------------------------\n");
    printf("| Программа для работы с комплексными числами |\n");
    printf("-----------------------------------------------\n");

    const char firstMessage[] = "Введите номер пункта: ";

    int userChoice, lowerBound = 1;
    int menuItemsCount = 2;

    char* firstUserStr = 0;
    int firstStrSize = 0;
    char secondUserStr = 0;
    char* thirdUserStr = 0;
    int thirdStrSize = 0;

    complex firstNumber;
    complex secondNumber;
    complex result;

    PrintMenu(); // выводим меню на экран

    // получаем номер выбранного пункта меню
    userChoice = CheckingInput(firstMessage, lowerBound,
                               menuItemsCount);

    RowFilling(&firstUserStr, &firstStrSize, &secondUserStr,
               &thirdUserStr, &thirdStrSize, userChoice, &firstNumber,
               &secondNumber);

    switch (userChoice)
    {

        case THREE_LINES:
            ThreeStringOperation(firstNumber, secondUserStr, 
                                 secondNumber, &result);
            break;

        case TWO_LINES:
            TwoStringOperation(firstNumber, secondUserStr,
                               &result);
            break;

        default:
            free(firstUserStr);
            free(thirdUserStr);
            printf("Выход...");
    }

    return 0;
}
#endif
