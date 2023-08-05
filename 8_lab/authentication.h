/*!
 * \file authentication.h
 * \brief Заголовочный файл с описанием функций
 *
 * Данный файл содержит в себе определение основных
 * функций, используемых для работы с PAM.
*/

#ifndef INC_6_LAB_AUTHENTICATION_H
#define INC_6_LAB_AUTHENTICATION_H

/*!
 * \brief Функция общения с PAM. Эта функция используется для передачи ответов от приложения к модулю PAM.
 * \param[in] num_msg Количество сообщений, переданных модулем PAM.
 * \param[in] num_msg Количество сообщений, переданных модулем PAM.
 * \param[in] msg Указатель на массив указателей на структуры pam_message, содержащие сообщения от модуля PAM.
 * \param[in] resp Указатель на указатель на массив структур pam_response, в котором функция должна выделить память и сохранить ответы от приложения.
 * \param[in] appdata_ptr Указатель на данные, переданные приложением через структуру pam_conv. В данном случае он не используется и равен NULL.
 * \return Код возврата PAM. В данном случае всегда возвращает PAM_SUCCESS.
 */
int my_conv(int num_msg, const struct pam_message** msg,
        struct pam_response** resp, void* appdata_ptr);

/*!
 * \brief Функция аутентификации с PAM. Эта функция используется для проверки имени пользователя и пароля с помощью модуля PAM.
 * \param[in] username Указатель на строку, содержащую имя пользователя.
 * \param[in] password Указатель на строку, содержащую пароль пользователя.
 * \return Код возврата PAM. Возвращает PAM_SUCCESS, если аутентификация успешна, иначе возвращает другой код ошибки PAM.
 */
int authenticate(const char* username, char* password);

#endif //INC_6_LAB_AUTHENTICATION_H
