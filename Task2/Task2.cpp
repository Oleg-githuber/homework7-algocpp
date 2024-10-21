

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <clocale>
#include <vector>

#define DEBUG

bool** getMatrixFromFile(std::string fileName, int& matrixSize);
bool* initArray(int matrixSize);
void deleteMatrix(bool** matrix, int matrixSize);
int* bfs(bool** matrix, bool* isWalked, int matrixSize, int index);
void printArray(int* arr, int arraySize);

int main()
{
    setlocale(LC_ALL, "Russian");
    std::string fileName{ "input.txt" };

    int matrixSize{};
    bool** matrix{ getMatrixFromFile(fileName, matrixSize) };
    bool* isWalked{ initArray(matrixSize) };
    int* arr{ bfs(matrix, isWalked, matrixSize,0) };
    printArray(arr, matrixSize);

    deleteMatrix(matrix, matrixSize);
    delete[] isWalked;
    delete[] arr;
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

// Удаление матрицы из кучи
void deleteMatrix(bool** matrix, int matrixSize)
{
    for (int i{}; i < matrixSize; ++i)
    {
        delete[] matrix[i];
    }
    delete matrix;
}

// Частичный обход в ширину по индексу
void bfs(bool** matrix, bool* isWalked, int matrixSize, int index, std::vector<int> &queue, int& resCount, int* result)
{
    if (!isWalked[index])
    {
        result[resCount++] = index + 1;
        isWalked[index] = true;
    }
    for (int i{}; i < matrixSize; ++i)
    {
        if (matrix[index][i])
        {
            if (!isWalked[i])
            {
                queue.push_back(i);
                for (int k{}; k < queue.size(); ++k)
                {
                    if (!isWalked[queue.at(k)])
                    {
                        result[resCount++] = queue.at(k) + 1;
                        isWalked[queue.at(k)] = true;
                    }
                }
            }
        }
    }
}

// Обход в ширину по индексу
int* bfs(bool** matrix, bool* isWalked, int matrixSize, int index)
{
    int* result{ new int[matrixSize] };
    for (int i{}; i < matrixSize; ++i)
    {
        result[i] = 0;
    }
    std::vector<int> queue;
    int resCount{};
    bfs(matrix, isWalked, matrixSize, index, queue, resCount, result);
    for (int k{}; k < queue.size(); ++k)
    {
        bfs(matrix, isWalked, matrixSize, queue.at(k), queue, resCount, result);
    }
    for (int i{}; i < matrixSize; ++i)
    {
        bfs(matrix, isWalked, matrixSize, i, queue, resCount, result);
    }
    return result;
}

// Вывод массива на экран
void printArray(int* arr, int arraySize)
{
    std::cout << "Порядок обхода вершин: ";
    for (int i{}; i < arraySize; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}