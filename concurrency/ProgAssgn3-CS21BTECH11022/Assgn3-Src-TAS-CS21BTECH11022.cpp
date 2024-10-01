#include <bits/stdc++.h>
#include <cstdlib>
#include <thread>
#include <time.h>

int n, k;
double l1, l2;
std::atomic_flag lock = ATOMIC_FLAG_INIT;
std::ifstream fin("inp-params.txt");
std::ofstream fout("TAS_output.txt");

class threadInfo
{
public:
    int tid;
    time_t *request_times;
    time_t *entry_time;
    double total_thread_wait_time;
    double worst_wait_time;
};

bool test_and_set(std::atomic_flag *lock)
{
    return lock->test_and_set(std::memory_order_acquire);
}

void testCS(threadInfo *data)
{
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::exponential_distribution<double> dist1(1 / l1), dist2(1 / l2);

    for (int i = 0; i < k; i++)
    {   
        auto start= std::chrono::high_resolution_clock::now();

        std::time_t time_counter = time(NULL);
        std::string reqEnterTime = ctime(&time_counter);
        data->request_times[i] = time_counter;
        fout << i + 1 << "th CS Request by thread " << data->tid << " at " << reqEnterTime;

        while (test_and_set(&lock))
            ;

        auto stop= std::chrono::high_resolution_clock::now();
        auto time_diff = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        
        time_counter = std::time(NULL);
        std::string actEnterTime = ctime(&time_counter);
        data->entry_time[i] = time_counter;
        fout << i + 1 << "th CS Entry by thread " << data->tid << " at " << actEnterTime;

        double wait =  (double)(time_diff.count());
        data->total_thread_wait_time += wait;

        if (wait > data->worst_wait_time)
        {
            data->worst_wait_time = wait;
        }

        double l = dist1(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)l));
        time_counter = std::time(NULL);
        std::string exitTime = ctime(&time_counter);
        fout << i + 1 << "th CS Exit by thread " << data->tid << " at " << exitTime;
        lock.clear(std::memory_order_release);

        double m = dist2(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)m));
    }
}

int main()
{
    fin >> n >> k;
    fin >> l1 >> l2;

    fin.close();
    fout << "TAS ME output: \n";

    std::thread threads[n];
    threadInfo *data[n];

    double total_wait_time = 0;
    double total_worst_wait_time = 0;

    for (int i = 0; i < n; i++)
    {
        data[i] = (threadInfo *)malloc(sizeof(threadInfo));
        data[i]->entry_time = (time_t *)malloc(sizeof(time_t) * k);
        data[i]->request_times = (time_t *)malloc(sizeof(time_t) * k);
        data[i]->tid = i + 1;
        data[i]->total_thread_wait_time = 0;
        data[i]->worst_wait_time = 0;
        threads[i] = std::thread(&testCS, data[i]);
    }

    for (int i = 0; i < n; i++)
    {
        threads[i].join();
    }

    for (int i = 0; i < n; i++)
    {
        total_wait_time += data[i]->total_thread_wait_time;
        total_worst_wait_time += data[i]->worst_wait_time;
    }

    fout << "\n\nTotal average waiting time of all threads = " << double(total_wait_time) / (1000000 * n) << " sec\n";
    std::cout << "\n\nTotal average waiting time of all threads = " << double(total_wait_time) / (1000000 * n) << " sec\n";
    fout << "Total worst waiting time of all threads = " << (double)total_worst_wait_time / 1000000 << " sec\n";
    std::cout << "Total worst waiting time of all threads = " << (double)total_worst_wait_time / 1000000 << " sec\n";
    fout.close();

    for(int i = 0; i < n; i++)
    {
        free(data[i]->entry_time);
        free(data[i]->request_times);
        free(data[i]);
    }

    return 0;
}