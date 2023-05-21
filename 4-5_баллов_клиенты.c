#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }
    //Аргументы командной строки
    const char* server_ip = argv[1];
    int server_port = atoi(argv[2]);

    // Создание сокета
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Ошибка при создании сокета");
        exit(1);
    }

    // Структура для адреса сервера
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = inet_addr(server_ip);

    // Установка соединения с сервером
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Ошибка при установлении соединения с сервером");
        exit(EXIT_FAILURE);
    }
    printf("Соединение с сервером установлено\n");

    while (1) {
        char request[] = "Запрос на просмотр картин";
        send(client_socket, request, sizeof(request), 0);
      
        // Получение ответа от сервера
        char response[256];
        int bytes_received = recv(client_socket, response, sizeof(response), 0);
        if (bytes_received > 0) {
            response[bytes_received] = '\0';
            printf("Получен ответ от сервера: %s\n", response);
            // Обработка ответа от сервера
            if (strncmp(response, "Количество посетителей превышает лимит", strlen("Количество посетителей превышает лимит")) == 0) {
                // Количество посетителей превышает лимит, ожидание
                printf("Получен ответ от сервера: %s\n", response);
                sleep(1);
                continue;
            } else if (strncmp(response, "Выход из галереи", strlen("Выход из галереи")) == 0) {
                // Выход из галереи
                printf("Получен ответ от сервера: %s\n", response);
                break;
            }
        }
    }
    char exit_request[] = "Запрос на выход из галереи";
    send(client_socket, exit_request, sizeof(exit_request), 0);

    // Закрытие клиентского сокета
    close(client_socket);

    return 0;
}
