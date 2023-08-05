/*!
 * \file functions.h
 * \brief Заголовочный файл с описанием функций
 *
 * Данный файл содержит в себе определения основных
 * функций, используемых в программе.
*/

#ifndef SF_VM_EXCHANGE_FUNCTIONS_H
#define SF_VM_EXCHANGE_FUNCTIONS_H
#include "structure.h"

/*!
 * \brief Выводит меню программы
 */
void PrintMenu(void);

/*!
 * \brief Выводит меню изменения параметров
 */
void PrintChangingMenu(void);

/*!
 * \brief Считывает из консоли одно целое число
 * \param[in] lowerBound Нижняя граница чисел
 * \param[in] count Верхняя граница чисел
 * \return Считанное число
 */
int CheckingInput(int lowerBound, int count);

/*!
 * \brief Функция ввода строки
 * \return Введённая пользователем строка
 */
char* StringInput(void);

/*!
 * \brief Функция ввода числа с плавающей точкой
 * \return Введённое пользователем число
 */
float FloatInput(void);

/*!
 * \brief Создание элемента
 * \param[in] data Данные для создания
 * \return Созданный элемент
 */
Node *CreateNode(Enterprise data);

/*!
 * \brief Функция добавления элемента в начало списка
 * \param[in] head Указатель на начало списка
 * \param[in] data Данные для создания
 */
void AddNode(Node** head, Enterprise data);

/*!
 * \brief Функция для модификации элемента списка
 * \param[in] head Указатель на начало списка
 * \param[in] countEnterprises Количество элементов
 */
void UpdateNode(Node* head, int countEnterprises);

/*!
 * \brief Функция для удаления элемента списка
 * \param[in] head Указатель на начало списка
 * \param[in] countEnterprises Количество элементов
 */
void DeleteNode(Node** head, int* countEnterprises);

/*!
 * \brief Функция для чтения элемента списка
 * \param[in] head Указатель на начало списка
 * \param[in] countEnterprises Количество элементов
 */
void PrintNode(Node* head, int countEnterprises);

/*!
 * \brief Функция для отображения содержимого списка
 * \param[in] head Указатель на начало списка
 * \param[in] countEnterprises Количество элементов
 */
void PrintList(Node* head, int countEnterprises);

/*!
 * \brief Функция для нахождения списка предприятий с наилучшим соотношением
 * \param[in] head Указатель на начало списка
 */
void FindBestRatio(Node* head);

/*!
 * \brief Функция для нахождения диапазона цен
 * \param[in] head Указатель на начало списка
 */
void FindPriceRange(Node* head);

/*!
 * \brief Функция для освобождения памяти списка
 * \param[in] head Указатель на начало списка
 */
void FreeList(Node** head);

#endif //SF_VM_EXCHANGE_FUNCTIONS_H
