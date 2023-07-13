#include <bits/stdc++.h>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <omp.h>

bool invalid;

class sudokuGrid
{
public:
    int dim;
    int **arr;
    bool *column;
    bool *row;
    bool *subGrid;

    void init()
    {
        int temp1, temp2;

        arr = (int **)malloc(dim * sizeof(int *));
        column = (bool *)malloc(sizeof(bool) * dim);
        row = (bool *)malloc(sizeof(bool) * dim);
        subGrid = (bool *)malloc(sizeof(bool) * dim);

        for (int i = 0; i < dim; i++)
        {
            arr[i] = (int *)malloc(dim * sizeof(int));
        }

        std::ifstream fin("input.tex");
        fin >> temp1 >> temp2;

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                fin >> arr[i][j];

                if (arr[i][j] <= 0 || arr[i][j] > dim)
                {
                    std::cout << "Number should be between 1 and " << dim << "\n";
                    return;
                }
            }
        }

        fin.close();
    }
    void destruct()
    {
        for (int i = 0; i < dim; i++)
        {
            free(arr[i]);
        }

        free(arr);
    }

    bool checkRow(int r);
    bool checkColumn(int c);
    bool checkSubgrid(int s);
    bool workAssigner(int x);
};

bool sudokuGrid ::checkColumn(int c)
{
    std::map<int, int> map;

    for (int j = 0; j < dim; j++)
    {
        map[arr[j][c]]++;

        if (map[arr[j][c]] > 1)
        {
            return false;
        }
    }

    return true;
}

bool sudokuGrid ::checkRow(int r)
{
    std::map<int, int> map;

    for (int j = 0; j < dim; j++)
    {
        map[arr[r][j]]++;

        if (map[arr[r][j]] > 1)
        {
            return false;
        }
    }

    return true;
}

bool sudokuGrid ::checkSubgrid(int s)
{
    int dim2 = sqrt(dim);
    int row_start = s % dim2 * dim2;
    int col_start = s / dim2 * dim2;

    std::map<int, int> map;

    for (int i = row_start; i < dim2; i++)
    {
        for (int j = col_start; j < dim2; j++)
        {
            map[arr[i][j]]++;
            if (map[arr[i][j]] > 1)
            {
                return false;
            }
        }
    }

    return true;
}

bool sudokuGrid ::workAssigner(int x)
{
    bool result;

    if (x >= 0 && x < dim)
    {
        column[x] = checkColumn(x);
        if (!column[x])
        {
            invalid = true;
        }
        result = column[x];
    }

    else if (x >= dim && x < 2 * dim)
    {
        subGrid[x - dim] = checkSubgrid(x - dim);
        if (!subGrid[x - dim])
        {
            invalid = true;
        }
        result = subGrid[x - dim];
    }

    else if (x >= 2 * dim && x < 3 * dim)
    {
        row[x - 2 * dim] = checkRow(x - 2 * dim);
        if (!row[x - 2 * dim])
        {
            invalid = true;
        }
        result = row[x - 2 * dim];
    }

    else
    {
        std::cout << "Error\n";
    }

    return result;
}

class thread
{
public:
    int tid;
    int work;
    bool result;
    std::string checked;
};

int main()
{
    int num_of_threads;
    int dimension;
    std::ifstream fin("input.tex");
    fin >> num_of_threads >> dimension;
    fin.close();

    if (num_of_threads > 3 * dimension)
    {
        std::cout << "threads cannot be more than 3 times dimension\n";
        return 0;
    }

    sudokuGrid *grid = new sudokuGrid;
    grid->dim = dimension;
    grid->init();

    int total_works = 3 * dimension;
    thread data[total_works];

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for num_threads(num_of_threads)
    for (int i = 0; i < 3 * dimension; i++)
    {
        data[i].tid = omp_get_thread_num();
        data[i].result = grid->workAssigner(i);

        if (i >= 0 && i < grid->dim)
        {
            data[i].checked = "Column ";
            data[i].work = i;
        }
        else if (i >= grid->dim && i < 2 * grid->dim)
        {
            data[i].checked = "Subgrid ";
            data[i].work = i - grid->dim;
        }
        else if (i >= 2 * grid->dim && i < 3 * grid->dim)
        {
            data[i].checked = "Row ";
            data[i].work = i - 2 * grid->dim;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::ofstream resout;
    resout.open("output.txt");

    for (int i = 0; i < 3 * dimension; i++)
    {
        resout << "Thread " << data[i].tid << " checked " << data[i].checked << data[i].work << " is (" << data[i].result << ")\n";
    }

    if (invalid == true)
    {
        resout << "Sudoku is invalid\n";
    }

    else
    {
        resout << "Sudoku is valid\n";
    }

    resout << "Time taken: " << (double)(time.count()) << " micro sec\n";
    // std::cout << "Time taken: " << (double)(time.count()) << " micro sec\n";

    grid->destruct();
    delete grid;

    return 0;
}
