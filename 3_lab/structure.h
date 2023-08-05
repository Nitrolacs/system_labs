/*!
 * \file structure.h
 * \brief Заголовочный файл с описанием структуры
 *
 * Данный файл содержит в себе определение основных
 * структур, используемых в программе.
*/

#ifndef SF_VM_EXCHANGE_STRUCTURE_H
#define SF_VM_EXCHANGE_STRUCTURE_H

typedef struct Enterprise Enterprise; //!< Структура предприятия
typedef struct Node Node; //!< Структура списка

/*!
 * \brief Предприятие-изготовитель
 */
struct Enterprise
{
    char* company; /*!< Предприятие изготовитель */
    char* type; /*!< Тип */
    float price; /*!< Цена */
    float performance; /*!< Производительность */
};

/*!
 * \brief Список
 */
struct Node
{
    Enterprise data; /*!< Данные */
    struct Node* next; /*!< Указатель на следующий элемент */
};

#endif //SF_VM_EXCHANGE_STRUCTURE_H
