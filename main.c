#include "matrix.h"

Matrix** matrix;

int main()
{
    system("chcp 1251");
    system("cls");
    mem_createMatrices();
    menu();
    mem_clearMatrices();
    return 0;
}

/*
 *  Memory Managment Functions
 */
void mem_createMatrices()
{
    matrix = (Matrix**)malloc(sizeof(Matrix*) * 3);
    for (int i = 0; i < 3; i++)
        matrix[i] = (Matrix*)malloc(sizeof(Matrix));
}

void mem_clearMatrices()
{
    for (int i = 0; i < 3; i++)
        free(matrix[i]);
    free(matrix);
}

void mem_allocateMatrix(Matrix* mtr, int rows, int �olumns)
{
    mtr->�olumns = �olumns;
    mtr->rows = rows;
    mtr->elements = (int***)calloc(rows, sizeof(int**));
    for (int i = 0; i < rows; i++)
    {
        mtr->elements[i] = (int**)calloc(�olumns, sizeof(int*));
        for (int j = 0; j < �olumns; j++)
        {
            mtr->elements[i][j] = (int*)calloc(2, sizeof(int));
            mtr->elements[i][j][1] = 1;
        }
    }
}

void mem_deallocateMatrix(Matrix* mtr)
{
    if (mtr->elements != NULL)
    {
        for (int i = mtr->rows - 1; i > 0; --i)
        {
            for (int j = mtr->�olumns - 1; j > 0; --j)
            {
                free(mtr->elements[i][j]);
                mtr->elements[i][j] = NULL;
            }
            free(mtr->elements[i]);
            mtr->elements[i] = NULL;
        }
        free(mtr->elements);
        mtr->elements = NULL;
        mtr->�olumns = 0;
        mtr->rows = 0;
    }

}

void mem_buffer_clear(void* buffer, int size)
{
    memset(buffer, 0, size);
}

/*
 *  Menu Functions
 */
void menu()
{
    int option = 0;
    int choice = 0;
    int back = 0;
    char flag = 0;
    do
    {
    loop:
        system("cls");
        printf("�������� ��� ���������\n\n");
        printf("1. �����������\n");
        printf("2. ����������\n");
        printf("3. ���������� ��� ����������\n");
        printf("0. �����\n");
        printf("\n��� ������� �� ����������� ������ ����, ������ ���� �����.\n\n");

        option = scanfInt();
        system("cls");
        switch (option)
        {
        case 1:
            do
            {
                printf("�����������\n\n������� ���� �� ��������� �������:\n");
                printf("1. ��������� �������\n");
                printf("2. ³������� �������\n");
                printf("3. �������� ������� �� �����\n");
                printf("4. �������� �������\n");
                printf("5. �������������� �������\n");
                printf("0. ����������� �� ��������� ����\n\n");
                choice = scanfInt();
                switch (choice)
                {
                case 1:
                    addition();
                    break;
                case 2:
                    subtraction();
                    break;
                case 3:
                    scalarMultiplication();
                    break;
                case 4:
                    multiplication();
                    break;
                case 5:
                    transposition();
                    break;
                case 0:
                    system("cls");
                    goto loop;
                    break;
                default:
                    printf("\n������ ��������� ���.\t������ ����� (1-5)\n\n");
                }
            } while (!flag);
            break;
        case 2:
            instruction();
            do
            {
                printf("������ 0, ��� ����������� �� ��������� ����.\n");
                back = scanfInt();
            } while (back != 0);
            goto loop;
            break;
        case 3:
            info();
            do
            {
                printf("������ 0, ��� ����������� �� ��������� ����.\n");
                back = scanfInt();
            } while (back != 0);
            goto loop;
            break;
        case 0:
            flag = 1;
            break;
        default:
            printf("\n������ ��������� ���.\t������ ����� (1-5)\n\n");
        }

    } while (!flag);
}

void info() {
    printf("�������� ��������: \n������� 3 �����, \n������������ \"������� � ������ �������� ���������\",\n���� \"�ϲ ���� ����� ѳ���������\",\n���������� ³���� �����������\n\n");
}

void instruction() {
    printf("��� ��������� ������� ��������, ��������� ������ ������������� ����� � ��������� Enter.\n\n��� �������� ������� ��������� �������� ����� ����� �� ��������� �����.\n������� ����� �����: 3, 0, -5.\n������ ����� ��������� �����  \"/\".\n������� ����� ����� ����� ��� ���� �������,\n���� ��� �� ���� ������� ���������� ���� � ������������ ���.\n������� �����: 1/2, -3/5, 7/3.\n\n");
}

/*
 *  �heck Functions
 */
int scanfInt() {
    int number;
    char symbol;
    while (1)
    {
        if (!scanf("%d", &number) || getchar() != '\n')
            while ((symbol = getchar()) != '\n' && symbol != EOF);
        else
            return number;
        printf("���������� ��������. ��������� �������� ����� ����: ");
    }
}

int checkBounds(int rows, int �olumns)
{
    if (rows <= MAX_NUMBER_ROWS && �olumns <= MAX_NUMBER_COLUMNS)
        return 1;
    else
        return 0;
}

void checkFile(void* ptr, const char* errorMessage)
{
    if (ptr == NULL)
    {
        printf("\n %s\n", errorMessage);
        exit(1);
    }
}

/*
 *  Interface Functions
 */
void addition()
{
    printf("\n��������� �������.\n");
    do
    {
        printf("\n�������. ����� ������� ������ ���� ���������� ������.\n\n");
        printf("\n������ ��� ����� �������:\n");
        io_confirmInput(matrix[0]);
        printf("\n\n������ ��� ����� �������:\n");
        io_confirmInput(matrix[1]);
        if (matrix[0]->rows != matrix[1]->rows || matrix[0]->�olumns != matrix[1]->�olumns)
            printf("\n������ ���� ������� ������ ���� ����������.");
    } while (matrix[0]->rows != matrix[1]->rows || matrix[0]->�olumns != matrix[1]->�olumns);
    mem_allocateMatrix(matrix[2], matrix[0]->rows, matrix[0]->�olumns);
    mtr_addMatrices(matrix[0], matrix[1], matrix[2]);
    printf("\n����:\n");
    io_printSaveMatrix_control(matrix[2]);
    mem_deallocateMatrix(matrix[0]);
    mem_deallocateMatrix(matrix[1]);
    mem_deallocateMatrix(matrix[2]);
}
void subtraction()
{
    printf("\n³������� �������.\n");
    do
    {
        printf("\n�������. ����� ������� ������ ���� ���������� ������.\n\n");
        printf("\n������ ��� ����� �������:\n");
        io_confirmInput(matrix[0]);
        printf("\n\n������ ��� ����� �������:\n");
        io_confirmInput(matrix[1]);
        if (matrix[0]->rows != matrix[1]->rows || matrix[0]->�olumns != matrix[1]->�olumns)
            printf("\n������ ���� ������� ������ ���� ����������.");
    } while (matrix[0]->rows != matrix[1]->rows || matrix[0]->�olumns != matrix[1]->�olumns);
    mem_allocateMatrix(matrix[2], matrix[0]->rows, matrix[0]->�olumns);
    mtr_subtractMatrices(matrix[0], matrix[1], matrix[2]);
    printf("\nг�����:\n");
    io_printSaveMatrix_control(matrix[2]);
    mem_deallocateMatrix(matrix[0]);
    mem_deallocateMatrix(matrix[1]);
    mem_deallocateMatrix(matrix[2]);
}
void scalarMultiplication()
{
    int option = 0;
    int number[2];
    io_confirmInput(matrix[0]);
    do 
    {
        printf("\n������� ��� �����, �� ��� �� ������ ��������� �������: \n1 - ֳ��\t 2 - �������\n"); 
        option = scanfInt(); 
        if (option != 1 && option != 2) 
            printf("\n������ ��������� ���. ������ ����� 1 ��� 2.\n\n");
    } while (option != 1 && option != 2); 
    printf("\n������ �����, �� ��� �� ������ ��������� �������:\n");
    switch (option)
    {
    case 1:
        number[0] = scanfInt();
        number[1] = 1; 
        break;
    case 2:
        printf("���������: "); 
        number[0] = scanfInt(); 
        printf("���������: "); 
        number[1] = scanfInt();
        break;
    }
    mtr_multiplyMatrixByNumber(matrix[0], number);
    printf("\n�������� �������:\n");
    io_printSaveMatrix_control(matrix[0]);
    mem_deallocateMatrix(matrix[0]);
}


void multiplication()
{
    printf("\n�������� �������.\n");
    do
    {
        printf("\n�������. ʳ������ �������� ����� ������� ������� ���������� ������� ����� ����� �������.\n");
        printf("\n������ ��� ����� �������:\n");
        io_confirmInput(matrix[0]);
        printf("\n\n������ ��� ����� �������:\n");
        io_confirmInput(matrix[1]);
        if (matrix[0]->�olumns != matrix[1]->rows)
            printf("\n������ ��������� ���. ��������� �����.\n\n");
    } while (matrix[0]->�olumns != matrix[1]->rows);
    mem_allocateMatrix(matrix[2], matrix[0]->rows, matrix[1]->�olumns);
    mtr_multiplyMatrices(matrix[0], matrix[1], matrix[2]);
    printf("\n�������:\n");
    io_printSaveMatrix_control(matrix[2]);
    mem_deallocateMatrix(matrix[0]);
    mem_deallocateMatrix(matrix[1]);
    mem_deallocateMatrix(matrix[2]);
}
void transposition()
{
    printf("\n�������������� �������.\n");
    io_confirmInput(matrix[0]);
    mtr_transposeMatrix(matrix[0]);
    printf("\n������������� �������:\n");
    io_printSaveMatrix_control(matrix[0]);
    mem_deallocateMatrix(matrix[0]);
}

/*
 *   Input/Output Functions
 */
void io_confirmInput(Matrix* mtr)
{
    int option = 0;
    do
    {
        io_inputMatrix_control(mtr);
        printf("\n������� �������:\n");
        io_printMatrix(stdout, mtr);
        printf("������ 1, ��� ����������, ��� 0, ��� �������� ������ �������.\n"); 
        do {
            option = scanfInt();

            if (option != 1 && option != 0) 
                printf("������ ��������� ���. ������ ����� 1 ��� 0.\n"); 
        } while (option != 1 && option != 0);
        if (option == 0)
            mem_deallocateMatrix(mtr); 
    } while (option != 1); 

}

void io_inputMatrix_control(Matrix* mtr)
{
    int option = 0;
    char FileName[50];
    FILE* inputFile = NULL;

    do
    {
        printf("\n������ ������� ����� � �������� ������� (������������ ����� ������� %dx%d):\n", MAX_NUMBER_ROWS, MAX_NUMBER_COLUMNS);
        printf("�����: ");
        mtr->rows = scanfInt();
        printf("�������: ");
        mtr->�olumns = scanfInt();
        if (!checkBounds(mtr->rows, mtr->�olumns)) {
            printf("\n������ ��������� ���. ��������� �����\n\n");
        }
    } while (!checkBounds(mtr->rows, mtr->�olumns));
    mem_allocateMatrix(mtr, mtr->rows, mtr->�olumns); 
    do
    {
        printf("\n������� ����� �������� �������: \n1 - ���������\t 2 - ����\n");
        option = scanfInt(); 
        if (option != 1 && option != 2) 
            printf("\n������ ��������� ���. ������ ����� 1 ��� 2.\n\n"); 
    } while (option != 1 && option != 2); 
    switch (option)
    {
    case 1:
    {
        printf("\n������ �������� �������:\n\n");
        io_inputMatrixElements_readFile(stdin, mtr);   
        break;
    }
    case 2:
    {
        printf("������ ����� �����: ");
        scanf("%32s", FileName);
        checkFile((inputFile = fopen(FileName, "r")), "��������� ������� ����.\n");
        io_inputMatrixElements_readFile(inputFile, mtr);
        fclose(inputFile);
        inputFile = NULL;
        break;
    }
    }

}

void io_printSaveMatrix_control(Matrix* mtr)
{
    int option = 0;
    char FileName[50];
    FILE* outputFile = NULL;
    io_printMatrix(stdout, mtr);
    do
    {
        printf("\n�� ������ �������� ��������� � ����? \n1 - ���\t 2 - ͳ\n");
        option = scanfInt(); 
        if (option != 1 && option != 2) 
            printf("\n������ ��������� ���. ������ ����� 1 ��� 2.\n\n"); 
    } while (option != 1 && option != 2); 

    if (option == 1)
    {
        printf("������ ��'� �����: ");
        scanf("%50s", FileName);
        checkFile((outputFile = fopen(FileName, "w")), "��������� �������� ����\n");
        io_printMatrix(outputFile, mtr);
        fclose(outputFile);
        outputFile = NULL;
        printf("��������� ������ ���������.\n");
    }
}

void io_printMatrix(FILE* stream, Matrix* mtr)
{
    fprintf(stream, "\n\n");
    int length = 0;
    int spacing = str_maxLengthElement(mtr);
    for (int i = 0; i < mtr->rows; i++)
    {
        for (int j = 0; j < mtr->�olumns; j++)
        {
            if (mtr->elements[i][j][0] < 0)
                fprintf(stream, "%d", mtr->elements[i][j][0]);
            else
                fprintf(stream, " %d", mtr->elements[i][j][0]);
            length = str_lengthValue(mtr->elements[i][j]);
            if (mtr->elements[i][j][1] <= 1)
                length -= 2;
            else
                fprintf(stream, "/%d", mtr->elements[i][j][1]);
            for (; length <= spacing; length++)
                printf(" ");
        }
        for (int k = 1; k <= 2; k++)
            fprintf(stream, "\n");
    }
}

void io_inputMatrixElements_readFile(FILE* stream, Matrix* mtr)
{
    char buffer[21]; 
    int row = 0, column = 0;
    int readValue = 0;
    while ((readValue != EOF) && (column < mtr->�olumns) && (row < mtr->rows))
    {
        mem_buffer_clear(buffer, 21);
        if (stream == stdin)
            printf("����� %d\t�������� %d : ", row + 1, column + 1);
        readValue = fscanf(stream, "%21s", buffer);
        if (readValue == EOF)
            break;
        io_definitionFractions_�onvertStringToInt(mtr, buffer, row, column);
        column++;
        if (column >= mtr->�olumns)
        {
            column = 0;
            row++;
        }
    }
}

void io_definitionFractions_�onvertStringToInt(Matrix* mtr, char* buffer, int row, int column)
{
    char numerator[10], denumerator[10];
    mem_buffer_clear(numerator, 10);
    mem_buffer_clear(denumerator, 10);

    if (strchr(buffer, '/'))
    {
        str_substring(buffer, numerator, 0, (int)(strchr(buffer, '/') - buffer));
        str_substring(buffer, denumerator, (int)(strchr(buffer, '/') - buffer) + 1, strlen(buffer));
        mtr->elements[row][column][0] = atoi(numerator); 
        mtr->elements[row][column][1] = atoi(denumerator); 
        if (mtr->elements[row][column][1] == 0)
        {
            do {
                printf("��������� ����� �� ���� ���������� ����. ������ �������� �������� ����������: ");
                scanf("%d", &mtr->elements[row][column][1]);
            } while (mtr->elements[row][column][1] == 0);
        }
        fr_reduceFraction(&mtr->elements[row][column][0], &mtr->elements[row][column][1]); 
    }
    else
    {
        mtr->elements[row][column][0] = atoi(buffer); 
        mtr->elements[row][column][1] = 1; 
    }
}

/*
 *   String Functions
 */
void str_substring(char* inputString, char* outputString, int begin, int end) 
{
    for (int i = 0; i < (end - begin); i++)
        outputString[i] = inputString[begin + i];
    outputString[end] = '\0';
}

int str_maxLengthElement(Matrix* mtr)
{
    int tmp = 0, maxlen = 0;
    for (int i = 0; i < mtr->rows; i++)
        for (int j = 0; j < mtr->�olumns; j++)
        {
            tmp = str_lengthValue(mtr->elements[i][j]);
            if (maxlen < tmp)
                maxlen = tmp;
        }
    return maxlen;
}

int str_lengthValue(int* number)
{
    return (str_countDigits(number[0]) + str_countDigits(number[1]) + 1);
}

int str_countDigits(int number)
{
    int count = 0;
    if (number < 0)
        number *= -1;
    if (number != 0) 
    {
        while (number != 0)
        {
            number /= 10;
            count++;
        }
        return count;
    }
    else
        return 1;
}

/*
 *   Process Fractions
 */
void fr_reduceFraction(int* numerator, int* denominator)
{
    int gcd = 0;
    if (*numerator == 0)
        *denominator = 1;
    if (*numerator !=0)  
    {
        if (*denominator < 0)
        {
            *denominator *= -1;
            *numerator *= -1;
        }
        gcd = math_greatestCommonDivisor(*numerator, *denominator);
        *numerator /= gcd;
        *denominator /= gcd;
    }
}


void fr_addFractions(int* fraction1, int* fraction2, int* fraction3)
{
    int numerator = 0, denominator = 0;
    denominator = math_leastCommonMultiple(fraction1[1], fraction2[1]);
    numerator = fraction1[0] * (denominator / fraction1[1]) + fraction2[0] * (denominator / fraction2[1]);
    fraction3[0] = numerator;
    fraction3[1] = denominator;
    fr_reduceFraction(fraction3, fraction3 + 1);
}

void fr_multiplyFractions(int* fraction1, int* fraction2, int* fraction3)
{
    fraction3[0] = fraction1[0] * fraction2[0];
    fraction3[1] = fraction1[1] * fraction2[1];
    fr_reduceFraction(fraction3, fraction3 + 1);
}

/*
 *   Math Functions
 */
int math_greatestCommonDivisor(int number1, int number2)
{
    int gcd = 0;
    if (number1 < 0)
        number1 *= -1;
    for (int i = 1; i <= number1 && i <= number2; ++i)
    {
        if (number1 % i == 0 && number2 % i == 0)
            gcd = i;
    }
    return gcd;
}

int math_leastCommonMultiple(int number1, int number2)
{
    int lcm = 0;
    lcm = (number1 > number2) ? number1 : number2;
    while (1)
    {
        if ((lcm % number1 == 0) && (lcm % number2 == 0))
        {
            break;
        }
        ++lcm;
    }
    return lcm;
}

/*
 *  Matrix Service Functions
 */
void mtr_addMatrices(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3)
{
    for (int i = 0; i < matrix1->rows; i++)
        for (int j = 0; j < matrix2->�olumns; j++)
        {
            fr_addFractions(matrix1->elements[i][j], matrix2->elements[i][j], matrix3->elements[i][j]);
        }
}

void mtr_subtractMatrices(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3)
{
    for (int i = 0; i < matrix1->rows; i++)
        for (int j = 0; j < matrix2->�olumns; j++)
        {
            matrix2->elements[i][j][0] = matrix2->elements[i][j][0] * -1;
            fr_addFractions(matrix1->elements[i][j], matrix2->elements[i][j], matrix3->elements[i][j]);
        }
}

void mtr_multiplyMatrixByNumber(Matrix* matrix, int* number)
{
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->�olumns; j++)
            fr_multiplyFractions(matrix->elements[i][j], number, matrix->elements[i][j]);

}

void mtr_multiplyMatrices(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3)  
{
    int temp[2];
    for (int i = 0; i < matrix3->rows; i++)
        for (int j = 0; j < matrix3->�olumns; j++)
        {
            matrix3->elements[i][j][0] = 0;
            matrix3->elements[i][j][1] = 1;
            for (int k = 0; k < matrix1->�olumns; k++)
            {
                fr_multiplyFractions(matrix1->elements[i][k], matrix2->elements[k][j], temp);
                fr_addFractions(matrix3->elements[i][j], temp, matrix3->elements[i][j]);
            }
        }
}

void mtr_transposeMatrix(Matrix* matrix)
{
    Matrix* tmp = (Matrix*)malloc(sizeof(Matrix));
    mem_allocateMatrix(tmp, matrix->�olumns, matrix->rows);

    int i, j, k;
    for (i = 0; i < matrix->rows; i++)
        for (j = 0; j < matrix->�olumns; j++)
            for (k = 0; k < 2; k++)
                tmp->elements[j][i][k] = matrix->elements[i][j][k];

    mem_deallocateMatrix(matrix);
    matrix->�olumns = tmp->�olumns;
    matrix->rows = tmp->rows;
    matrix->elements = tmp->elements;
    free(tmp);
}