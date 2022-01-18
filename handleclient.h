#include "readwrite.h"

#include <chrono>
#include <csignal>

void * handleClient(void * thread_arg);

struct thread_data{
    int client_socket_fd;
    int * numOfConnectedClients;
    pthread_mutex_t * lock;
};