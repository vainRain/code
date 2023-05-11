#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1])); // convert a string to an integer

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 5);

    int clnt_addr_size = 0;
    struct sockaddr_in clnt_addr;
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    printf("after accept(), clnt_addr_size = %d\n", clnt_addr_size);

    char message[] = "Hello World";
    write(clnt_sock, message, sizeof(message));
    
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
}