#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <semaphore>

// Constants
constexpr int SIZE = 25;

// Global Mutex and Semaphore
std::mutex mtx;
std::binary_semaphore sem(1);

// Function Prototypes
void writeOnes(std::ofstream &file);
void writeTwos(std::ofstream &file);
void part1();
void part2();
void part3();
void readAndPrint();

int main() {
    std::cout << "Part 1: Without Locking\n";
    part1();

    std::cout << "\nPart 2: Using Mutex Lock\n";
    part2();

    std::cout << "\nPart 3: Using Semaphore\n";
    part3();

    return 0;
}

void writeOnes(std::ofstream &file) {
    for (int i = 0; i < SIZE * SIZE; ++i) {
        file << '1';
    }
}

void writeTwos(std::ofstream &file) {
    for (int i = 0; i < SIZE * SIZE; ++i) {
        file << '2';
    }
}

void part1() {
    std::ofstream file("datafile", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error opening file for Part 1\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(writeOnes, std::ref(file));
    std::thread t2(writeTwos, std::ref(file));

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    file.close();
    std::cout << "Time taken (without locking): " << elapsed.count() << " ms\n";

    readAndPrint();
}

void part2() {
    std::ofstream file("datafile", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error opening file for Part 2\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    auto writeOnesLocked = [&file]() {
        std::lock_guard<std::mutex> lock(mtx);
        writeOnes(file);
    };

    auto writeTwosLocked = [&file]() {
        std::lock_guard<std::mutex> lock(mtx);
        writeTwos(file);
    };

    std::thread t1(writeOnesLocked);
    std::thread t2(writeTwosLocked);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    file.close();
    std::cout << "Time taken (with mutex lock): " << elapsed.count() << " ms\n";

    readAndPrint();
}

void part3() {
    std::ofstream file("datafile", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error opening file for Part 3\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    auto writeOnesSemaphore = [&file]() {
        sem.acquire();
        writeOnes(file);
        sem.release();
    };

    auto writeTwosSemaphore = [&file]() {
        sem.acquire();
        writeTwos(file);
        sem.release();
    };

    std::thread t1(writeOnesSemaphore);
    std::thread t2(writeTwosSemaphore);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    file.close();
    std::cout << "Time taken (with semaphore): " << elapsed.count() << " ms\n";

    readAndPrint();
}

void readAndPrint() {
    std::ifstream file("datafile");
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading\n";
        return;
    }

    char data[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            file >> data[i][j];
        }
    }

    file.close();

    std::cout << "Contents of the file:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}
