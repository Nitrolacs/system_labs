#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <unistd.h>

// Файл с информацией о смонтированных файловых системах
#define MOUNT_FILE "/proc/mounts"
#define THRESHOLD 90 // Порог заполнения диска в процентах

int CheckDiskFull()
{
    FILE *fp; // Указатель на файл
    char line[256]; // Буфер для чтения строки из файла
    char device[256]; // Буфер для хранения имени устройства
    char mountPoint[256]; // Буфер для хранения точки монтирования
    struct statvfs buf; // Структура для хранения данных о файловой системе
    unsigned long freeSpace; // Свободное пространство на диске в байтах
    unsigned long totalSpace; // Общее пространство на диске в байтах
    int usage; // Процент заполнения диска

    char buffer[256]; // Буфер для хранения пути к текущей директории
    char* directory; // Указатель для хранения результата функции getcwd()

    directory = getcwd(buffer, sizeof(buffer));
    if (directory == NULL)
    {
        perror("getcwd");
        return 1;
    }
    printf("Текущая директория: %s\n", buffer);

    // Открываем файл с информацией о смонтированных файловых системах
    fp = fopen(MOUNT_FILE, "r");

    if (fp == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Читаем файл построчно
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Разбиваем строку на токены по пробелам и получаем имя устройства и
        // точку монтирования
        sscanf(line, "%s %s", device, mountPoint);

        // Проверяем, совпадает ли точка монтирования с директорией с log
        // файлами или ее родителем
        if (strcmp(mountPoint, directory) == 0 || strcmp(mountPoint, "/") == 0)
        {
            // Закрываем файл
            fclose(fp);

            // Получаем данные о файловой системе по точке монтирования
            if (statvfs(mountPoint, &buf) == -1)
            {
                perror("Ошибка получения данных о файловой системе");
                return 1;
            }

            // Вычисляем свободное и общее пространство на диске в байтах
            freeSpace = buf.f_bsize * buf.f_bavail;
            totalSpace = buf.f_bsize * buf.f_blocks;

            // Вычисляем процент заполнения диска
            usage = 100 * (totalSpace - freeSpace) / totalSpace;

            // Выводим информацию о диске и его заполнении
            printf("Устройство: %s\n", device);
            printf("Точка монтирования: %s\n", mountPoint);
            printf("Свободное пространство: %lu байт\n", freeSpace);
            printf("Общее пространство: %lu байт\n", totalSpace);
            printf("Процент заполнения: %d%%\n", usage);

            // Проверяем, превышает ли заполнение порог
            if (usage > THRESHOLD)
            {
                printf("Предупреждение: диск заполнен более чем "
                       "на %d%%\n", THRESHOLD);
            }

            return 0;
        }
    }

    // Если не нашли нужный диск, выводим сообщение об ошибке
    printf("Не найден диск с log файлами\n");
    return 1;
}


