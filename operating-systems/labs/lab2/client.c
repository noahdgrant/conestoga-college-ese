/*
* Operating Systems Lab 2
* Author: Noah Grant
* Date: October 30, 2023
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void communicate(int serverID) {
    char buf[BUFSIZ];

    while (1) {
        // Send command to server
        memset(&buf, 0, sizeof(buf));
        printf("Enter a command [Who | Where | When | Help | Close | Shutdown]: ");
        fflush(stdout);
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0';
        }

        write(serverID, buf, sizeof(buf));
        
        // Read response from server
        memset(&buf, 0, sizeof(buf));
        read(serverID, buf, sizeof(buf));
        printf("[Server] %s\n", buf);

        if ((strncmp(buf, "Close", 4)) == 0) {
            printf("[Client] Closing...\n");
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    int clientSocket;
    struct sockaddr_in serverAddr;
    struct hostent *host;

    if (argc != 3) {
        printf("Usage: ./client IP PORT\n");
        return 1;
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        printf("[Client] Socket creation failed...\n");
        return 1;
    }
    else {
        printf("[Client] Socket created successfully...\n");
    }

    // Assign IP and PORT
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(atoi(argv[2]));

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0) {
        printf("[Client] Failed to connect to the server...\n");
        return 1;
    }
    else {
        printf("[Client] Connected to the server...\n");
    }

    communicate(clientSocket);

    close(clientSocket);

    return 0;
}
