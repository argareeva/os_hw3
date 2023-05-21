#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAX_CLIENTS 50
#define MAX_PICTURES 5
#define MAX_VISITORS 10

typedef struct {
    int picture_id;
    int visitors_count;
} Picture;

void handle_client(int client_socket) {
    // Логика обработки запросов от клиента

    Picture pictures[MAX_PICTURES];
    for (int i = 0; i < MAX_PICTURES; i++) {
        pictures[i].picture_id = i + 1;
        pictures[i].visitors_count = 0;
    }

    while (1) {
        // Пример чтения данных от клиента
        char buffer[1024];
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("Получены данные от клиента: %s\n", buffer);

            // Обработка запроса от клиента
            if (strcmp(buffer, "Запрос на просмотр картин") == 0) {
                // Случайный выбор картинки
                int random_picture = rand() % MAX_PICTURES;
                // Проверка количества посетителей у картинки
                if (pictures[random_picture].visitors_count >= MAX_VISITORS) {
                    // Количество посетителей превышает лимит
                    char response[] = "Количество посетителей превышает лимит";
                    send(client_socket, response, sizeof(response), 0);
                    printf("Количество посетителей превышает лимит");
                    continue;
                }
                // Увеличение счетчика посетителей
                pictures[random_picture].visitors_count++;
                // Отправка информации о количестве посетителей
                char response[256];
                sprintf(response, "Картинка %d: %d посетителей", pictures[random_picture].picture_id, pictures[random_picture].visitors_count);
                printf("Отправка данных клиенту: Картинка %d: %d посетителей", pictures[random_picture].picture_id, pictures[random_picture].visitors_count);
                send(client_socket, response, sizeof(response), 0);
            } else if (strcmp(buffer, "Запрос на выход из галереи") == 0) {
                // Запрос на выход из галереи
                char response[] = "Выход из галереи";
                send(client_socket, response, sizeof(response), 0);
                printf("Выход из галереи");
                break;
            }
        }
    }

    // Закрытие соединения с клиентом
    close(client_socket);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }
    //Аргументы командной строки
    const char* server_ip = argv[1];
    int server_port = atoi(argv[2]);
  
    int client_socket, server_socket;
    struct sockaddr_in server_address, client_address;
    int active_clients = 0;

    // Создание сокета
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Ошибка при создании сокета");
        exit(1);
    }
  
    // Структура для адреса сервера
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = inet_addr(server_ip);

    // Привязка сокета к адресу
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Ошибка при привязке сокета");
        exit(1);
    }

    // Ожидание входящих подключений
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Ошибка при прослушивании сокета");
        exit(1);
    }

    printf("Сервер запущен. Ожидание подключений...\n");

    while (1) {
        // Принятие клиентского подключения
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &sizeof(client_address));
        if (client_socket == -1) {
            perror("Ошибка при принятии подключения");
            exit(1);
        }
        printf("Новое подключение принято\n");

        if (active_clients >= MAX_CLIENTS) {
            printf("Превышен лимит посетителей. Отклонение подключения.\n");
            close(client_socket);
            continue;
        }

        // Создание нового процесса для обработки клиента
        pid_t pid = fork();
        if (pid == -1) {
            perror("Ошибка при создании процесса");
            exit(1);
        } else if (pid == 0) {
            // Дочерний процесс
            close(server_socket); // Дочерний процесс не нуждается в серверном сокете
            handle_client(client_socket); // Обработка запросов клиента
            exit(0); // Завершение дочернего процесса
        } else {
            // Родительский процесс
            close(client_socket); // Родительский процесс не нуждается в клиентском сокете
            active_clients++;
        }
    }

    // Закрытие серверного сокета
    close(server_socket);

    return 0;
}
