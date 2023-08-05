/*!
 * \file structure.h
 * \brief Заголовочный файл с описанием структуры
 *
 * Данный файл содержит в себе определение основной
 * структуры, используемой в программе.
*/

#ifndef INC_1_LAB_STRUCTURE_H
#define INC_1_LAB_STRUCTURE_H

typedef struct complex complex; //!< Структура комплексного числа

/*!
 * \brief Комплексное число
 */
struct complex {
    float real; /*!< Вещественная часть комплексного числа */
    float imag; /*!< Мнимая часть комплексного числа */
};

#endif //INC_1_LAB_STRUCTURE_H
