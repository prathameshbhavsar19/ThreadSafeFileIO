# Thread-Safe File I/O

## Project Overview
This project demonstrates a **thread-safe file I/O system** in C++, ensuring safe concurrent read and write operations using **mutex synchronization**. The goal is to prevent race conditions and data corruption when multiple threads access the same file.

## Features
- **Thread-safe file writing** using `std::mutex`
- **Concurrent file reading** while maintaining data integrity
- **Performance benchmarking** with multiple threads
- **Error handling and logging**

## Technologies Used
- **C++ (C++11 and later)**
- **Standard Library (std::thread, std::mutex, fstream)**
- **Xcode (MacBook Pro)** or any C++ compiler

## Prerequisites
- C++ compiler (GCC/Clang/MSVC)
- Basic understanding of multithreading

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/prathameshbhavsar19/threadsafe-fileio.git
   cd threadsafe-fileio
   ```
2. Compile the program:
   ```bash
   g++ -std=c++11 -pthread threadsafe_fileio.cpp -o threadsafe_fileio
   ```
3. Run the executable:
   ```bash
   ./threadsafe_fileio
   ```

## Usage
1. Start multiple threads for reading and writing.
2. Observe synchronized operations preventing data corruption.
3. Analyze execution logs for race condition prevention.

## Sample Output
```
Writing to file: Thread 1
Writing to file: Thread 2
Reading from file: Thread 3
Completed File Operations Safely.
```

## Future Enhancements
- Implement **asynchronous file I/O** for better efficiency.
- Use **read-write locks** to optimize performance.
- Extend support for **binary file operations**.

## Author
**Prathamesh Bhavsar**

## License
This project is open-source and available under the MIT License.

