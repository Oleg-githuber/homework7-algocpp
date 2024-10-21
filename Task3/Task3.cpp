
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <clocale>

bool** getMatrixFromFile(std::string fileName, int& matrixSize);
void deleteMatrix(bool** matrix, int matrixSize);
bool* initArray(int matrixSize);
bool isCyclic(bool** matrix, bool* isWalked, int matrixSize);

int main()
{
    setlocale(LC_ALL, "Russian");
    std::string fileName{ "input.txt" };

    int matrixSize{};
    bool** matrix{ getMatrixFromFile(fileName, matrixSize) };
    bool* isWalked{ initArray(matrixSize) };
    std::cout << ((isCyclic(matrix, isWalked, matrixSize)) ? "В графе есть цикл\n" : "В графе нет циклов\n");

    deleteMatrix(matrix, matrixSize);
    delete[] isWalked;
    return EXIT_SUCCESS;
}

// Создание матрицы из информации, записаной в файле
bool** getMatrixFromFile(std::string fileName, int& matrixSize)
{
    std::ifstream file(fileName);
    if (file.is_open())
    {
        //int matrixSize{};
        file >> matrixSize;
        bool** matrix{ new bool* [matrixSize] };
        for (int raw{}; raw < matrixSize; ++raw)
        {
            bool* arr{ new bool[matrixSize] };
            for (int column{}; column < matrixSize; ++column)
            {
                file >> arr[column];
            }
            matrix[raw] = arr;
        }
        file.close();
        return matrix;
    }
    else
    {
        std::cout << "File is not found" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Удаление матрицы из кучи
void deleteMatrix(bool** matrix, int matrixSize)
{
    for (int i{}; i < matrixSize; ++i)
    {
        delete[] matrix[i];
    }
    delete matrix;
}

// Создание массива информации о том, пройден ли узел графа
bool* initArray(int matrixSize)
{
    bool* isWalked{ new bool[matrixSize] };
    for (int i{}; i < matrixSize; ++i)
    {
        isWalked[i] = false;
    }
    return isWalked;
}

// Обход очередного узла
bool dfs(bool** matrix, int index, bool* isWalked, int* result, int matrixSize, int prevIndex)
{
    //result[count] = index + 1;
    isWalked[index] = true;
    for (int i{}; i < matrixSize; ++i)
    {
        if (matrix[index][i])
        {
            if (!isWalked[i])
            {
                return dfs(matrix, i, isWalked, result, matrixSize, index);
            }
            else if (i != prevIndex)
            {
                return true;
            }
        }
    }
    return false;
}

// Создание массива с последовательностью обхода графа
bool isCyclic(bool** matrix, bool* isWalked, int matrixSize)
{
    int* result{ new int[matrixSize] };
    for (int i{}; i < matrixSize; ++i)
    {
        result[i] = 0;
    }

    int count{};

    for (int i{}; i < matrixSize; ++i)
    {
        if (!isWalked[i])
        {
            if (dfs(matrix, i, isWalked, result, matrixSize, -1))
            {
                return true;
            }
        }
    }
    return false;
}