#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")
// client side




int main()
{

    // CREATE CONNECTION
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed.\n");
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        printf("Failed to create socket.\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);                  // Port you want to connect to (e.g., 80 for HTTP)
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server's IP address

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        printf("Failed to connect to the server.\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // MAIN PROCESS GOES HERE ...

    // message
    char message[4096] = "";
    scanf("%s", message);
    message[strlen(message)] = '\n';
    printf("from client: %s", message);
    // SEND DATA

    if (send(clientSocket, message, strlen(message), 0) == SOCKET_ERROR)
    {
        printf("Failed to send data.\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    char buffer[4096];
    int bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0)
    {
        printf("%d", bytesRead);
        fwrite(buffer, strlen(buffer), bytesRead, stdout);
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
