#include <bits/stdc++.h>
#include <thread>
#include <cstdlib>
#include <time.h>

class threadInfo
{
public:
    int tid;
    time_t *request_time;
    time_t *entry_time;
    bool isWaiting;
    double total_thread_wait_time;
    double worst_wait_time;
};

int n, k;
double l1, l2;
std::atomic_int lock(0);
threadInfo **data;
std::ifstream fin("inp-params.txt");
std::ofstream fout("CAS_bounded_output.txt");

int compare_and_swap(std::atomic<int> *val, int expected, int new_val)
{
	return std::atomic_exchange_explicit(val, new_val, std::memory_order_acquire);
}

void testCS(int tid)
{
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::exponential_distribution<double> dist1(1.0 / l1), dist2(1.0 / l2);

    for(int i = 0; i < k; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::time_t time_counter = time(NULL);
        std::string reqEnterTime = ctime(&time_counter);
        data[tid - 1]->request_time[i] = time_counter;
        fout << i + 1 << "th CS Request by thread " << data[tid - 1]->tid << " at " << reqEnterTime;

        data[tid - 1]->isWaiting = true;
        int len = 1;
        while (data[tid-1]->isWaiting == true && len == 1)
        {
            len = compare_and_swap(&lock, 0, 1);
        }
        data[tid - 1]->isWaiting = false;

        auto stop= std::chrono::high_resolution_clock::now();
        auto time_diff = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

        time_counter = std::time(NULL);
        std::string actEnterTime = ctime(&time_counter);
        data[tid - 1]->entry_time[i] = time_counter;
        fout << i + 1 << "th CS Entry by thread " << data[tid -1]->tid << " at " << actEnterTime;

        double wait = (double)(time_diff.count());
        data[tid - 1]->total_thread_wait_time += wait;

        if (wait > data[tid - 1]->worst_wait_time)
        {
            data[tid - 1]->worst_wait_time = wait;
        }

        double l = dist1(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds((int(l))));
        time_counter = std::time(NULL);
        std::string exitTime = ctime(&time_counter);
        fout << i + 1 << "th CS Exit by thread " << data[tid - 1]->tid << " at " << exitTime;

        int j = (tid) % n;
        while ((j != tid-1) && data[j]->isWaiting == false)
        {
            j = (j + 1) % n;
            // fout<<"Loop exit"<<std::endl;
        }

        if (j == tid-1) // when no process waits and j remains tid
        {
            std::atomic_store_explicit(&lock, false, std::memory_order_release);
        }

        else
        {
            data[j]->isWaiting = false;
        }

        double m = dist2(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)m));
    }
}

int main()
{
    fin >> n >> k >> l1 >> l2;
    fin.close();

    fout << "Bounded CAS ME Output:\n";

    std::thread threads[n];

    double total_wait_time = 0;
    double total_worst_wait_time = 0;

    data = (threadInfo **)malloc(sizeof(threadInfo *) * n);

    for(int i = 0; i < n; i++)
    {
        data[i] = (threadInfo *)malloc(sizeof(threadInfo));
        data[i]->entry_time = (time_t *)malloc(sizeof(time_t) * k);
        data[i]->request_time = (time_t *)malloc(sizeof(time_t) * k);
        data[i]->tid = i + 1;
        data[i]->total_thread_wait_time = 0;
        threads[i] = std::thread(&testCS, i+1);
    }

    for(int i = 0; i < n; i++)
    {
        threads[i].join();
    }

    for(int i = 0; i < n; i++)
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
        free(data[i]->request_time);
        free(data[i]);
    }

    free(data);

    return 0;
}