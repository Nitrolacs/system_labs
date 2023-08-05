/*!
 * \file unit_tests.c
 * \brief Тесты для основных функций программы.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#define DOING_UNIT_TESTS
#include "child.c"
#include "structure.h"

/*!
 * \brief Первый тест
 */
void FirstTest()
{
    complex number;
    complex result;
    number.real = 2.54;
    number.imag = -34;
    TwoStringOperation(number, 'R', &result);
    bool isValid = false;

    if (number.real == result.real)
    {
        isValid = true;
    }

    CU_ASSERT_EQUAL(isValid, true)
}

/*!
 * \brief Второй тест
 */
void SecondTest()
{
    complex number;
    complex result;
    number.real = 2.54;
    number.imag = -34;
    TwoStringOperation(number, 'I', &result);
    bool isValid = false;

    if (number.imag == result.imag)
    {
        isValid = true;
    }

    CU_ASSERT_EQUAL(isValid, true)
}

/*!
 * \brief Третий тест
 */
void ThirdTest()
{
    complex number;
    complex result;
    number.real = 2.54;
    number.imag = -34;
    TwoStringOperation(number, 'S', &result);
    bool isValid = false;

    if (result.imag == -number.imag)
    {
        isValid = true;
    }

    CU_ASSERT_EQUAL(isValid, true)
}

/*!
 * \brief Четвертый тест
 */
void FourthTest()
{
    complex firstNumber, secondNumber;
    complex result;
    firstNumber.real = 2;
    firstNumber.imag = -34;
    secondNumber.real = -6;
    secondNumber.imag = 49;

    ThreeStringOperation(firstNumber, '+', secondNumber, &result);
    bool isValid = false;

    if (result.real == -4 && result.imag == 15)
    {
        isValid = true;
    }

    CU_ASSERT_EQUAL(isValid, true)
}

/*!
 * \brief Пятый тест
 */
void FifthTest()
{
    complex firstNumber, secondNumber;
    complex result;
    firstNumber.real = 2;
    firstNumber.imag = -34;
    secondNumber.real = -6;
    secondNumber.imag = 49;

    ThreeStringOperation(firstNumber, '*', secondNumber, &result);
    bool isValid = false;

    if (result.real == 1654 && result.imag == 302)
    {
        isValid = true;
    }

    CU_ASSERT_EQUAL(isValid, true)
}

/*!
 * \brief Точка входа
 */
int main()
{
    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("main_suite", NULL, NULL);
    CU_ADD_TEST(suite, FirstTest);
    CU_ADD_TEST(suite, SecondTest);
    CU_ADD_TEST(suite, ThirdTest);
    CU_ADD_TEST(suite, FourthTest);
    CU_ADD_TEST(suite, FifthTest);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
