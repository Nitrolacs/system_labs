/*!
 * \file child.h
 * \brief Заголовочный файл с описанием функций
 *
 * Данный файл содержит в себе определения основных
 * функций, используемых в программе.
*/

#ifndef INC_1_LAB_CHILD_H
#define INC_1_LAB_CHILD_H
#include "structure.h"

/*!
 * \brief Функция ввода строки
 * \param[out] stringSize Полученная длина строки
 * \return Введённая пользователем строка
 */
char* StringInput(int* stringSize);

/*!
 * \brief Объединяет три строки в одну
 * \param[in] firstStr Первая строка
 * \param[in] secondStr Вторая строка
 * \param[in] thirdStr Третья строка
 * \return Строка, составленная из трёх строк
 */
char* concatenate(const char* firstStr, const char* secondStr,
                  const char* thirdStr);

/*!
 * \brief Ввод комплексного числа
 * \param[out] userStr Считанная строка
 * \param[out] strSize Размер считанной строки
 * \param[out] cmpNumber Полученное комплексное число
 */
void ComplexNumberInput(char** userStr, int* strSize, complex* cmpNumber);

/*!
 * \brief Получает операнд
 * \param[out] userStr Считанная строка
 * \param[in] userChoice Выбор пользователя
 */
void CheckOperation(char* userStr, int userChoice);

/*!
 * \brief Заполненяет строки
 * \param[out] firstUserStr Первая считанная строка
 * \param[out] firstStrSize Размер первой строки
 * \param[out] secondUserStr Вторая считанная строка
 * \param[out] thirdUserStr Третья считанная строка
 * \param[out] thirdStrSize Размер третьей строки
 * \param[in] userChoice Выбор пользователя
 * \param[out] firstNumber Первое комплексное число
 * \param[out] secondNumber Второе комплексное число
 */
void RowFilling(char** firstUserStr, int* firstStrSize, char* secondUserStr,
                char** thirdUserStr, int* thirdStrSize,  int userChoice,
                complex* firstNumber, complex* secondNumber);

/*!
 * \brief Операции с тремя строками
 * \param[in] firstNumber Первое комплексное число
 * \param[in] operation Операнд
 * \param[in] secondNumber Второе комплексное число
 */
void ThreeStringOperation(complex firstNumber, char operation,
                          complex secondNumber, complex* result);

/*!
 * \brief Операции с двумя строками
 * \param[in] number Комплексное число
 * \param[in] operation Операнд
 */
void TwoStringOperation(complex number, char operation, complex* result);

/*!
 * \brief Считывает из консоли одно целое число
 * \param[in] message Выводимое сообщение
 * \param[in] lowerBound Нижняя граница чисел
 * \param[in] count Верхняя граница чисел
 * \return Считанное число
 */
int CheckingInput(const char message[], int lowerBound, int count);

/*!
 * \brief Выводит меню программы
 */
void PrintMenu(void);

/*!
 * \brief Точка входа в программу
 * \return Код завершения
 */
int main(void);

#endif //INC_1_LAB_CHILD_H
