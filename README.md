# Shared Memory and Semaphore Example

This repository contains a C program that demonstrates how to use **System V Shared Memory** and **POSIX semaphores** to synchronize processes. The program simulates two processes: a **writer** process that writes to shared memory and a **reader** process that reads from it. It uses **semaphores** to control access to the shared memory and ensure mutual exclusion.

## Features
- **Shared Memory**: The program creates and attaches shared memory that is accessible by both writer and reader processes.
- **Semaphore**: A counting semaphore is used to manage the access to shared memory and ensure synchronization between processes.
- **Process Synchronization**: The writer writes to shared memory, and the reader reads from it, using semaphores to synchronize the access.

## Components
- **Shared Memory**: A memory segment shared between the writer and reader process.
- **Semaphore**: A POSIX semaphore to control access to the shared memory, ensuring that only one process can access it at a time.
- **Writer**: The process that writes a message to shared memory.
- **Reader**: The process that reads the message from shared memory.

## Prerequisites
- **C Compiler**: You need a C compiler (e.g., `gcc`).
- **POSIX Semaphores**: Your system should support POSIX semaphores.
- **Linux Environment**: This code is designed for Linux and uses Linux-specific features such as shared memory and semaphores.

## Compilation and Execution

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/shared-memory-semaphore.git
   cd shared-memory-semaphore
   ```

2. **Compile the code**:
   Use `gcc` to compile the C code. Run the following command:
   ```bash
   gcc -o shared_memory_semaphore shared_memory_semaphore.c -pthread
   ```

3. **Run the writer process**:
   You can execute the writer process by setting the `writer` flag to `1` and the `reader` flag to `0` in the code:
   ```c
   #define writer 1
   #define reader 0
   ```

4. **Run the reader process**:
   Similarly, to execute the reader process, change the flags to:
   ```c
   #define writer 0
   #define reader 1
   ```

5. **Run the compiled program**:
   ```bash
   ./shared_memory_semaphore
   ```

6. **Cleanup**:
   The program cleans up by destroying the semaphore and removing the shared memory segment after the operations are completed.

## Code Structure

- `shared_memory_semaphore.c`: Contains the main program, which demonstrates the use of shared memory and semaphores for synchronization.
- `README.md`: This file provides instructions and an overview of the project.

## Example Output

For the writer process:
```bash
Writer wrote to shared memory
```

For the reader process:
```bash
Reader read: Hello from writer process!
```

## Notes
- The program currently supports only one process at a time: either the writer or the reader. You will need to modify the code or use separate processes for real-world concurrent execution.
- The semaphore is initialized with a count of `3`, allowing multiple threads (if used in the future) to access the shared memory simultaneously.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author
Your Name  
GitHub: [https://github.com/iamvengeance018](https://github.com/iamvengeance018)

---

You can add more details, modify it according to your needs, and adjust the links to fit your repository.
