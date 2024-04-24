// UDP Client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;
    sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Message from server: ");
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    close(sockfd);
    return 0;
}
