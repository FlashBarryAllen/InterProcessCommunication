#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // 连接到服务器
    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器的 IP 地址
    serverAddr.sin_port = htons(12345); // 服务器的端口号
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // 接收数据
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Received: " << buffer << std::endl;
    
    // 关闭套接字
    close(clientSocket);
    
    return 0;
}
