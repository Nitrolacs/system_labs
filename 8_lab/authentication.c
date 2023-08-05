#include <security/pam_appl.h>
#include <security/pam_misc.h>

#include "authentication.h"
#include "signals.h"

// Переменная для хранения дескриптора файла журнала
extern FILE* logfd;

// Структура для хранения ответов PAM
struct pam_response* reply;

int my_conv(int num_msg, const struct pam_message** msg,
        struct pam_response** resp, void* appdata_ptr)
{
    *resp = reply;
    return PAM_SUCCESS;
}

int authenticate(const char* username, char* password)
{
    // Создаем структуру для общения с PAM
    const struct pam_conv localConversation = {my_conv, NULL};

    // Создаем дескриптор для PAM
    pam_handle_t* localAuthHandle = NULL;

    // Запускаем PAM с указанным именем пользователя и функцией общения
    int pamRet = pam_start("lpam", username,
                           &localConversation, &localAuthHandle);

    if (pamRet != PAM_SUCCESS)
    {
        fprintf(stderr, "Ошибка при запуске PAM.\n");
        writeLog("%s\n", "Ошибка при запуске PAM.");
        return -1;
    }

    // Выделяем память для ответов PAM
    reply = (struct pam_response*)malloc(sizeof(struct pam_response));

    // Получаем пароль
    reply[0].resp = password;

    // Устанавливаем код ответа PAM
    reply[0].resp_retcode = 0;

    // Проверяем аутентификацию пользователя с помощью PAM
    pamRet = pam_authenticate(localAuthHandle, 0);

    if (pamRet == PAM_SUCCESS) // Если аутентификация успешна
    {
        printf("Аутентификация прошла успешно.\n");
        writeLog("%s\n", "Аутентификация прошла успешно.");
    }
    else
    {
        // Если аутентификация не успешна
        printf("Аутентификация не прошла.\n");
        writeLog("%s\n", "Аутентификация не прошла.");
    }

    // Заканчиваем работу с PAM
    pam_end(localAuthHandle, pamRet);

    return pamRet;
}

