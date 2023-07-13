#include <bits/stdc++.h>
#include <cmath>
#include <cstdlib>
#include <pthread.h>
#include <fstream>

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
        std::ifstream fin("input.tex");
        int temp1, temp2;
        fin >> temp1 >> temp2;

        arr = (int **)malloc(dim * sizeof(int *));
        column = (bool *)malloc(sizeof(bool) * dim);
        row = (bool *)malloc(sizeof(bool) * dim);
        subGrid = (bool *)malloc(sizeof(bool) * dim);

        for (int i = 0; i < dim; i++)
        {
            arr[i] = (int *)malloc(dim * sizeof(int));
        }

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

class threadInfo
{
public:
    int works;         // Gives the number of works it has to perform
    int start;         // Gives which work number it should start from
    int thread_number; // Gives the thread number it is operating
    sudokuGrid *grid;  // Pointer to grid as an arguement, not the entire grid
};

void *func(void *args)
{
    threadInfo *data = (threadInfo *)args;

    bool temp;

    for (int i = data->start; i < data->start + data->works; i++)
    {
        temp = data->grid->workAssigner(i);
    }

    return (void *)NULL;
}

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
    if (x >= 0 && x < dim)
    {
        column[x] = checkColumn(x);
        return column[x];
    }

    else if (x >= dim && x < 2 * dim)
    {
        subGrid[x - dim] = checkSubgrid(x - dim);
        return subGrid[x - dim];
    }

    else if (x >= 2 * dim && x < 3 * dim)
    {
        row[x - 2 * dim] = checkRow(x - 2 * dim);
        return row[x - 2 * dim];
    }

    else
    {
        std::cout << "Error\n";
        return false;
    }
}

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
    int l = total_works % num_of_threads;

    pthread_t threads[num_of_threads];
    threadInfo **data = (threadInfo **)malloc(sizeof(threadInfo *) * num_of_threads);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < l; i++)
    {
        data[i] = (threadInfo *)malloc(sizeof(threadInfo));
        data[i]->grid = grid;
        data[i]->works = (total_works / num_of_threads) + 1;
        data[i]->thread_number = i;
        data[i]->start = ((total_works / num_of_threads) + 1) * (i);

        pthread_create(&threads[i], NULL, &func, data[i]);
        pthread_join(threads[i], NULL);
    }

    for (int i = l; i < num_of_threads; i++)
    {
        data[i] = (threadInfo *)malloc(sizeof(threadInfo));
        data[i]->grid = grid;
        data[i]->works = (total_works / num_of_threads);
        data[i]->thread_number = i;
        data[i]->start = ((total_works / num_of_threads) + 1) * (l) + (total_works / num_of_threads) * (i - l);

        pthread_create(&threads[i], NULL, &func, data[i]);
        pthread_join(threads[i], NULL);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::ofstream resout;
    resout.open("output.txt");

    for (int i = 0; i < num_of_threads; i++)
    {
        for (int j = data[i]->start; j < data[i]->start + data[i]->works; j++)
        {
            resout << "Thread " << i + 1 << " checks ";
            if (j >= 0 && j < grid->dim)
            {
                resout << "column " << j + 1 << " is (" << grid->workAssigner(j) << ")\n";
            }

            else if (j >= grid->dim && j < 2 * grid->dim)
            {
                resout << "subgrid " << j - grid->dim + 1 << " is (" << grid->workAssigner(j) << ")\n";
            }

            else if (j >= 2 * grid->dim && j < 3 * grid->dim)
            {
                resout << "row " << j - 2 * grid->dim + 1 << " is (" << grid->workAssigner(j) << ")\n";
            }
        }
    }

    bool invalid;
    for(int i = 0; i < grid->dim; i++)
    {
        if(grid->row[i] == false || grid->column[i] == false || grid->subGrid[i] == false)
        {
            invalid = true;
            resout << "Sudoku is Invalid\n";
        }
    }

    if(invalid == false)
    {
        resout << "Sudoku is Valid\n";
    }

    resout << "Time taken: " << (double)(time.count()) << " micro sec\n";
    // std::cout << "Time taken: " << (double)(time.count()) << " micro sec\n";

    for (int i = 0; i < num_of_threads; i++)
    {
        free(data[i]);
    }
    free(data);

    grid->destruct();
    delete grid;

    return 0;
}
