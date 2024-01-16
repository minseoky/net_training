#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
using namespace std;

void error_handler(char *message)
{
    fputs("[E] ", stderr);
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    char buf[100] = {};
    char read_buf[100] = {};

    // socket
    int h_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(h_sock == -1) error_handler("socket() error");

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(stoi("12345"));

    //connect
    if(connect(h_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handler("connect() error");
    }

    cout << "message to server: ";
    cin >> buf;

    write(h_sock, buf, strlen(buf));

    shutdown(h_sock, SHUT_WR);


    memset(read_buf, 0, sizeof(read_buf));
    read(h_sock, read_buf, sizeof(read_buf));
    cout << "echo from server: " << read_buf << endl;

    close(h_sock);

    return 0;
}