/*
* Operating Systems Lab 2
* Author: Noah Grant
* Date: October 30, 2023
*/

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int quit;

void communicate(int clientID) {
    char buf[BUFSIZ];
    FILE *p;
    
    while (1) {
        memset(buf, 0, sizeof(buf));
        read(clientID, buf, sizeof(buf));

        // Execute command from client
        if (strncmp("Close", buf, 4) == 0) {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "Close");
            write(clientID, buf, strlen(buf));
            printf("[Server] Closing connection...\n");
            break;
        }
        else if (strncmp("Shutdown", buf, 8) == 0) {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "Shutdown");
            write(clientID, buf, strlen(buf));
            printf("[Server] Shutting down...\n");
            quit = 1;
            break;
        }
        else if (strncmp("Help", buf, 4) == 0) {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "Go ask Scott for help\n");
        }
        else if (strncmp("Who", buf, 3) == 0) {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "INFO72220\n");
        }
        else if (strncmp("When", buf, 4) == 0) {
            memset(buf, 0, sizeof(buf));
            p = popen("date", "r");
            if (p != NULL) {
                fread(buf, 1, sizeof(buf), p);
                pclose(p);
            }
            else {
                strcpy(buf, "[Server] Can't run date command...\n");
            }
        }
        else if (strncmp("Where", buf, 5) == 0) {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "Cambridge\n");
        }
        else {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "Invalid command\n");
        }
        
        write(clientID, buf, strlen(buf));
    }
}

int main(int argc, char* argv[]) {
    int serverSocket, clientSocket;
    unsigned int clientLen;
    struct sockaddr_in serverAddr, clientAddr;
    quit = 0;

    if (argc != 2) {
        printf("Usage: ./server PORT\n");
        return 1;
    }

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        printf("[Server] Socket creation failed...\n");
        return 1;
    }
    else {
        printf("[Server] Socket creation successful...\n");
    }

    // Assign IP and PORT
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(atoi(argv[1]));

    // Bind socket to IP
    if ((bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) != 0) {
        printf("[Server] Socket bind failed...\n");
        close(serverSocket);
        return 1;
    }
    else {
        printf("[Server] Socket bind successful...\n");
    }

    // Listen for client connection
    if ((listen(serverSocket, 5)) != 0) {
        printf("[Server] Server listen failed...\n");
        return 1;
    }
    else {
        printf("[Server] Server listening...\n");
    }

    clientLen = sizeof(clientAddr);

    while (quit == 1) {
        // Accept client communication
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            printf("[Server] Did not accept client...\n");
            return 1;
        }
        else {
            printf("[Server] Accepted the client...\n");
        }

        // Communicate with client
        communicate(clientSocket);
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);

    printf("[Server] Closed successfully...\n");
    return 0;
}

