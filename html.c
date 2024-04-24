#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char *html_content =  "HTTP/1.1 200 OK\r\n"
    "Connection:close\r\n"
    "Content-Type:text/html\r\n\r\n"
    "<!DOCTYPE html>\n"
    "<html>"
    "<body>"
    "<h1>Hello World!</h1>"
    "</body></html>";

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 3);

    printf("Server running on localhost:8080\n");

    while (1) {
        int client_addr_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);

        send(client_socket, html_content, strlen(html_content), 0);

        close(client_socket);
    }

    close(server_socket);

    return 0;
}
