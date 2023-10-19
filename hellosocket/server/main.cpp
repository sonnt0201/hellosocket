#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {

    // khởi tạo winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // khởi tạo server
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Failed to create server socket.\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345); // Port the server listens on
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Listen on all available network interfaces

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        printf("Failed to bind.\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Failed to listen.\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Server is listening on port 12345 ...\n");  

    while (1) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            printf("Failed to accept client connection.\n");
            closesocket(serverSocket);
            WSACleanup();
            return 1;       
        }

        char buffer[4096] = "minh duc";
        int bytesRead;
        while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
            printf("in server: %s \n", buffer);
            // printf("bytesRead: %d \n", bytesRead);
            send(clientSocket, buffer, bytesRead, 0);
        } // sizeof -- strlen

        closesocket(clientSocket);

    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
