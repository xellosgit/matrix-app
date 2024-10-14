#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_ROWS 20
#define MAX_NUMBER_COLUMNS 20
/*
 *  Matrix
 */
typedef struct
{
    int*** elements;
    int rows;
    int ñolumns;
}Matrix;

/*
 *  Menu Functions
 */
void menu();
void instruction();
void info();

/*
 *  Interface Functions
 */
void addition();
void subtraction();
void scalarMultiplication();
void multiplication();
void transposition();

/*
 *  Memory Managment Functions
 */
#if defined(MAX_NUMBER_COLUMNS) && defined(MAX_NUMBER_ROWS)
void mem_createMatrices();
void mem_clearMatrices();

#else
#error Undefined matrix boundaries
#endif
void mem_allocateMatrix(Matrix* mtr, int rows, int ñolumns);
void mem_deallocateMatrix(Matrix* mtr);
void mem_buffer_clear(void* buffer, int size);

/*
 *  Ñheck Functions
 */
int scanfInt();
int checkBounds(int rows, int columns); 
void checkFile(void* ptr, const char* errorMessage);

/*
 *   Input/Output Functions
 */
void io_confirmInput(Matrix* mtr); 
void io_inputMatrix_control(Matrix* mtr); 
void io_printSaveMatrix_control(Matrix* mtr); 
void io_printMatrix(FILE* stream, Matrix* mtr); 
void io_inputMatrixElements_readFile(FILE* stream, Matrix* mtr); 
void io_definitionFractions_ñonvertStringToInt(Matrix* mtr, char* buffer, int row, int column); 

/*
 *   String Functions
 */
void str_substring(char* inputString, char* outputString, int begin, int end);
int  str_maxLengthElement(Matrix* mtr); 
int str_lengthValue(int* number); 
int str_countDigits(int number);

/*
 *   Process Fractions
 */
void fr_reduceFraction(int* numerator, int* denominator);
void fr_addFractions(int* fraction1, int* fraction2, int* fraction3);
void fr_multiplyFractions(int* fraction1, int* fraction2, int* fraction3);

/*
 *   Math Functions
 */
int math_greatestCommonDivisor(int number1, int number2); 
int math_leastCommonMultiple(int number1, int number2); 

/*
 *  Matrix Service Functions
 */
void mtr_addMatrices(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3);
void mtr_subtractMatrices(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3);
void mtr_multiplyMatrixByNumber(Matrix* matrix, int* number);
void mtr_multiplyMatrices(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3);
void mtr_transposeMatrix(Matrix* matrix);
#endif