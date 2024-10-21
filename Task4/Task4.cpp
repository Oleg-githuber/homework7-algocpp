#include <iostream>
#include <fstream>
#include <cstdlib>
#include <clocale>

bool** getMatrixFromFile(std::string fileName, int& matrixSize);
void deleteMatrix(bool** matrix, int matrixSize);
bool* initArray(int matrixSize); 
int* components(bool** matrix, bool* isWalked, int matrixSize);
void printArray(int* arr, int arrSize);

int main()
{
    setlocale(LC_ALL, "Russian");
    std::string fileName{ "input.txt" };

    int matrixSize{};
    bool** matrix{ getMatrixFromFile(fileName, matrixSize) };
    bool* isWalked{ initArray(matrixSize) };
    int* arr{ components(matrix, isWalked, matrixSize) };
    printArray(arr, matrixSize);

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
void dfs(bool** matrix, int index, int& count, bool* isWalked, int* result, int matrixSize, int cid)
{
    result[count++] = cid + 1;
    isWalked[index] = true;
    for (int i{}; i < matrixSize; ++i)
    {
        if (matrix[index][i])
        {
            if (!isWalked[i])
            {
                dfs(matrix, i, count, isWalked, result, matrixSize, cid);
            }
        }
    }
}

// Создание массива с последовательностью обхода графа
int* components(bool** matrix, bool* isWalked, int matrixSize)
{
    int* result{ new int[matrixSize] };
    for (int i{}; i < matrixSize; ++i)
    {
        result[i] = 0;
    }

    int count{};
    int cid{};

    for (int i{}; i < matrixSize; ++i)
    {
        if (!isWalked[i])
        {
            dfs(matrix, i, count, isWalked, result, matrixSize, cid++);
        }
    }
    return result;
}

int findMax(int* arr, int arrSize)
{
    int max{ arr[0] };
    for (int i{ 1 }; i < arrSize; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

void printArray(int* arr, int arrSize)
{
    std::cout << "Принадлежность вершин компонентам связности:\n";
    for (int i{}; i < arrSize; ++i)
    {
        std::cout << i + 1 << " - " << arr[i] << '\n';
    }
    std::cout << "Количество компонентов связности в графе: " << findMax(arr, arrSize) << '\n';
}