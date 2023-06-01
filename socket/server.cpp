#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    // 创建套接字
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // 绑定地址和端口
    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // 监听连接
    listen(serverSocket, 1);
    
    // 接受连接
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    
    // 发送数据
    const char* message = "Hello from server!";
    send(clientSocket, message, strlen(message), 0);
    
    // 关闭套接字
    close(clientSocket);
    close(serverSocket);
    
    return 0;
}
