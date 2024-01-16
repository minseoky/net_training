#include <iostream>
#include <sys/socket.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

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
    if(argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    char buf[100] = {};

    //socket
    int h_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(h_socket == -1) error_handler("socket() error");

    //bind
    sockaddr_in serv_addr, clnt_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(stoi(argv[1]));
    if(bind(h_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handler("bind() error");
    }

    //listen
    if(listen(h_socket, 10) == -1)
    {
        error_handler("listen() error");
    }
    cout << "listening..." << endl;

    while(1)
    {
        //accept
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        int clnt_sock = accept(h_socket, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
        cout << "accepted" << endl;
        int str_len = 0;

        memset(&buf, 0, sizeof(buf));

        str_len = read(clnt_sock, buf, sizeof(buf));

        write(clnt_sock, buf, str_len);
        cout << "send to clnt: " << buf << endl;
        close(clnt_sock);
    }

    return 0;
}