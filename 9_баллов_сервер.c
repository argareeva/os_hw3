#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#define MAX_CLIENTS 50
#define MAX_PICTURES 5
#define MAX_VISITORS 10

typedef struct {
    int picture_id;
    int visitors_count;
} Picture;

typedef struct {
    int client_socket;
    Picture *pictures;
} Client;

void *handle_client(void *client_ptr) {
    Client *client = (Client *)client_ptr;
    int client_socket = client->client_socket;
    Picture *pictures = client->pictures;

    while (1) {
        // Чтение данных от клиента
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
                    continue;
                }
                // Увеличение счетчика посетителей
                pictures[random_picture].visitors_count++;
                // Отправка информации о количестве посетителей
                char response[256];
                sprintf(response, "Картинка %d: %d посетителей", pictures[random_picture].picture_id, pictures[random_picture].visitors_count);
                send(client_socket, response, sizeof(response), 0);
            } else if (strcmp(buffer, "Запрос на выход из галереи") == 0) {
                // Запрос на выход из галереи
                char response[] = "Выход из галереи";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
        }
    }

    // Закрытие соединения с клиентом
    close(client_socket);
    free(client);
  
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }

    const char *server_ip = argv[1];
    int server_port = atoi(argv[2]);

    // Создание серверного сокета
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Ошибка при создании серверного сокета");
        return 1;
    }

    // Настройка адреса сервера
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = inet_addr(server_ip);

    // Привязка серверного сокета к адресу
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Ошибка при привязке серверного сокета");
        return 1;
    }

    // Ожидание входящих подключений
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Ошибка при прослушивании серверного сокета");
        return 1;
    }
    printf("Сервер запущен. Ожидание подключений...\n");

    // Создание массива с информацией о картинках
    Picture pictures[MAX_PICTURES];
    for (int i = 0; i < MAX_PICTURES; i++) {
        pictures[i].picture_id = i + 1;
        pictures[i].visitors_count = 0;
    }

    // Массив для хранения идентификаторов потоков
    pthread_t threads[MAX_CLIENTS];
    int thread_count = 0;

    while (1) {
        // Принятие клиентского подключения
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            perror("Ошибка при принятии клиентского подключения");
            return 1;
        }
        printf("Новое подключение принято\n");
        if (thread_count >= MAX_CLIENTS) {
            printf("Превышен лимит клиентов. Отклонение подключения.\n");
            close(client_socket);
            continue;
        }

        // Создание структуры для передачи информации клиентскому обработчику
        Client *client = (Client *)malloc(sizeof(Client));
        client->client_socket = client_socket;
        client->pictures = pictures;

        // Создание нового потока для обработки клиента
        pthread_create(&threads[thread_count], NULL, handle_client, (void *)client);

        // Увеличение счетчика потоков
        thread_count++;
    }

    // Ожидание завершения всех потоков
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    // Закрытие серверного сокета
    close(server_socket);

    return 0;
}
