#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // 共享内存大小

int main() {
    key_t key = ftok("/root/code/12_memory/", 1);  // 创建共享内存的key
    std::cout << key  << std::endl;
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);  // 创建共享内存段

    if (shm_id == -1) {
        std::cout << "Failed to create shared memory segment." << std::endl;
        return 1;
    }

    char* shared_memory = (char*)shmat(shm_id, NULL, 0);  // 将共享内存附加到进程空间

    if (shared_memory == (char*)-1) {
        std::cout << "Failed to attach shared memory segment." << std::endl;
        return 1;
    }

    //while (true) {
        static int a = 1234560;
        std::string message = "Hello from Process A!\n";
        //std::strcpy(shared_memory, message.c_str());  // 将数据写入共享内存
        std::strcpy(shared_memory, std::to_string(a).c_str());  // 将数据写入共享内存
        a++;
        std::strcpy(shared_memory, std::to_string(a).c_str());  // 将数据写入共享内存
    //}

    shmdt(shared_memory);  // 分离共享内存

    return 0;
}
