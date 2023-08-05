/*! Функции интерфейса CLI */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "interface.h"
#include "filesystem.h"

void PrintClientHelp(void)
{
    printf("Использование: ./client [опции] коэффициенты\n");
    printf("Опции:\n");
    printf("-h \t\tВывести эту справку и выйти\n");
    printf("-l logFile\tЗадать имя файла для логирования\n");
    printf("-t timeout\tЗадать таймаут для ожидания ответа\n");
    printf("-f filesystem\tПроверка заполнения \"дисков\", на которых"
           " хранятся log-файлы\n");
    printf("Коэффициенты:\n");
    printf("a b c\t\tКоэффициенты квадратного уравнения\n");
    printf("a b c d\t\tКоэффициенты кубического уравнения\n");
}

void PrintServerHelp(void)
{
    printf("Использование: ./server [опции]\n");
    printf("Опции:\n");
    printf("-h \t\tВывести эту справку и выйти\n");
    printf("-l logFile\tЗадать имя файла для логирования\n");
    printf("-t timeout\tЗадать таймаут для ожидания ответа\n");
    printf("-f filesystem\tПроверка заполнения \"дисков\", на которых"
           " хранятся log-файлы\n");
}

// Функция для обработки аргументов из командной строки для клиента
int
ParseArgsClient(int argc, char *argv[], char **logFile, int *timeout,
                double *a,
                double *b, double *c,
                double *d)
                {

    // Проверяем, что стандартный ввод и вывод являются терминалами
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
    {
        fprintf(stderr, "Перенаправление стандартных потоков запрещено.\n");
        return -1;
    }
    
    // Объявляем переменную для хранения кода возврата функции getopt
    int opt;

    // Проверяем количество аргументов командной строки

    if (argc == 1)
    {
        PrintClientHelp();
        exit(0);
    }

    // Объявляем указатели на конец чисел
    char* endptrA;
    char* endptrB;
    char* endptrC;
    char* endptrD;

    // Объявляем переменные-флаги для проверки повторения опций
    int aFlag = 0;
    int bFlag = 0;
    int cFlag = 0;
    int dFlag = 0;
    int lFlag = 0;
    int tFlag = 0;
    int hFlag = 0;
    int fFlag = 0;

    // Используем цикл while для анализа аргументов командной строки
    //  strtod() преобразует строку в число с плавающей точкой и возвращает
    //  указатель на первый символ, который не является частью числа.
    //  Если этот символ не равен нулевому символу ‘\0’, то это означает,
    //  что строка содержит неверный формат числа.
    while ((opt = getopt(argc, argv, "a:b:c:d:t:l:hf")) != -1)
    {
        switch (opt)
        {
            case 'l':
                // Проверяем флаг l
                if (lFlag == 1)
                {
                    // Опция l повторяется
                    fprintf(stderr,
                            "Опция -l не может быть указана более одного раза.\n");
                    return -1;
                }
                else
                {
                    // Опция l встречается в первый раз
                    lFlag = 1; // Устанавливаем флаг a в 1
                }
                // Имя файла журнала
                *logFile = optarg;
                break;
            case 't':
                // Проверяем флаг t
                if (tFlag == 1)
                {
                    // Опция t повторяется
                    fprintf(stderr,
                            "Опция -t не может быть указана более одного раза.\n");
                    return -1;
                }
                else
                {
                    // Опция t встречается в первый раз
                    tFlag = 1; // Устанавливаем флаг t в 1
                }
                // Время ожидания ввода пользователя
                *timeout = atoi(optarg);
                break;
            case 'h':
                // Проверяем флаг h
                if (hFlag == 1)
                {
                    // Опция a повторяется
                    fprintf(stderr,
                            "Опция -h не может быть указана более одного раза.\n");
                    return -1;
                }
                else
                {
                    // Опция h встречается в первый раз
                    hFlag = 1; // Устанавливаем флаг h в 1
                }
                PrintClientHelp();
                break;
            case 'f':
                // Проверяем флаг f
                if (fFlag == 1)
                {
                    // Опция a повторяется
                    fprintf(stderr,
                            "Опция -f не может быть указана более одного раза.\n");
                    return -1;
                }
                else
                {
                    // Опция f встречается в первый раз
                    fFlag = 1; // Устанавливаем флаг f в 1
                }
                CheckDiskFull();
                break;
            case 'a':
                // Проверяем флаг a
                if (aFlag == 1)
                {
                    // Опция a повторяется
                    fprintf(stderr,
                            "Опция -a не может быть указана более одного раза.\n");
                    return -1;
                }
                else
                {
                    // Опция a встречается в первый раз
                    aFlag = 1; // Устанавливаем флаг a в 1
                }
                // Преобразуем строку в число с плавающей точкой и сохраняем в указателе a
                *a = strtod(optarg,
                            &endptrA); // Присваиваем значение и адрес конца числа
                if (*endptrA !=
                    '\0')
                {
                    // Проверяем, что строка заканчивается нулевым символом
                    fprintf(stderr, "Неверный формат числа для опции -a.\n");
                    return -1;
                }
                break;
            case 'b':
                // Проверяем флаг b
                if (bFlag == 1)
                {
                    // Опция b повторяется
                    fprintf(stderr,
                            "Опция -b не может быть указана более одного раза.\n");
                    return -1;
                }
                else
                {
                    // Опция b встречается в первый раз
                    bFlag = 1; // Устанавливаем флаг b в 1
                }
                // Преобразуем строку в число с плавающей точкой и сохраняем в указателе b

                *b = strtod(optarg,
                            &endptrB); // Присваиваем значение и адрес конца числа
                if (*endptrB !=
                    '\0')
                {
                    // Проверяем, что строка заканчивается нулевым символом
                    fprintf(stderr, "Неверный формат числа для опции -b.\n");
                    return -1;
                }
                break;
            case 'c':
                // Проверяем флаг c
                if (cFlag == 1)
                {
                    // Опция c повторяется
                    fprintf(stderr,
                            "Опция -c не может быть указана более одного раза.\n");
                    return -1;
                }
                else
                {
                    // Опция c встречается в первый раз
                    cFlag = 1; // Устанавливаем флаг c в 1
                }
                // Преобразуем строку в число с плавающей точкой и сохраняем в указателе c

                *c = strtod(optarg,
                            &endptrC); // Присваиваем значение и адрес конца числа
                if (*endptrC !=
                    '\0')
                {
                    // Проверяем, что строка заканчивается нулевым символом
                    fprintf(stderr, "Неверный формат числа для опции -c.\n");
                    return -1;
                }
                break;
            case 'd': // Добавляем опцию -d для четвертого коэффициента
                // Проверяем флаг d
                if (dFlag == 1)
                {
                    // Опция d повторяется
                    fprintf(stderr,
                            "Опция -d не может быть указана более одного раза.\n");
                    return -1;
                }
                else
                {
                    // Опция d встречается в первый раз
                    dFlag = 1; // Устанавливаем флаг d в 1
                }
                // Преобразуем строку в число с плавающей точкой и сохраняем в указателе d
                *d = strtod(optarg,
                            &endptrD); // Присваиваем значение и адрес конца числа
                if (*endptrD !=
                    '\0')
                {
                    // Проверяем, что строка заканчивается нулевым символом
                    fprintf(stderr,
                            "Неверный формат числа для опции -d.\n");
                    return -1;
                }
                break;
            default:
                fprintf(stderr,
                        "Использование: ./client [-l logFile] "
                        "[-t timeout] -a a -b b -c c [-d d]\n");
                return -1;
        }
    }

    // Проверяем, что коэффициенты уравнения не равны нулю или единице
    if (*a == 0 || *a == 1 || *b == 0 || *b == 1 || *c == 0 || *c == 1)
    {
        fprintf(stderr, "Неверные коэффициенты.\n");
        return -1;
    }

    // Возвращаем код успеха
    return 0;
}

// Функция для разбора аргументов командной строки сервера
void parseArgsServer(int argc, char* argv[], char** logFile, int* timeout)
{
    // Проверяем, что стандартный ввод и вывод являются терминалами
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
    {
        fprintf(stderr, "Перенаправление стандартных потоков запрещено.\n");
        exit(1);
    }

    int opt;

    // Опции для getopt
    const char* optstring = "l:t:hf";
    // Парсим аргументы с помощью getopt
    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch (opt) {
            case 'l': // имя файла журнала
                *logFile = optarg;
                break;
            case 't': // время ожидания сообщений от клиента
                *timeout = atoi(optarg);
                break;
            case 'h':
                PrintServerHelp();
                break;
            case 'f':
                CheckDiskFull();
                break;
            default: // неверный аргумент
                fprintf(stderr,
                        "Использование: %s [-l logFile] [-t timeout]\n", argv[0]);
                exit(1);
        }
    }
}