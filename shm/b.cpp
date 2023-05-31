#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // 共享内存大小

int main() {
    key_t key = ftok("/root/code/12_memory/", 1);  // 获取共享内存的key
    std::cout << key  << std::endl;
    int shm_id = shmget(key, SHM_SIZE, 0666);  // 获取共享内存段的ID

    if (shm_id == -1) {
        std::cout << "Failed to get shared memory segment." << std::endl;
        return 1;
    }

    char* shared_memory = (char*)shmat(shm_id, NULL, 0);  // 将共享内存附加到进程空间

    if (shared_memory == (char*)-1) {
        std::cout << "Failed to attach shared memory segment." << std::endl;
        return 1;
    }
    
    //while (true) {
        std::string message(shared_memory);  // 从共享内存读取数据
        std::cout << "Received message from Process A: " << message << std::endl;
    //}

    shmdt(shared_memory);  // 分离共享内存

    shmctl(shm_id, IPC_RMID, NULL);  // 删除共享内存段

    return 0;
}
