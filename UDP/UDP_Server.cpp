#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

void error_handler(char *message)
{
    fputs("[E] ", stderr);
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[]) //need port argument
{

    if(argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    char buf[100];
    // socket
    int h_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(h_sock == -1) error_handler("sock() error");

    // bind
    sockaddr_in my_addr, clnt_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port = htons(stoi(argv[1]));
    if(bind(h_sock, (struct sockaddr*) &my_addr, sizeof(my_addr)) == -1)
    {
        error_handler("bind() error");
    }

    while(1)
    {
        cout << "loop start" << endl;

        memset(&buf ,0, sizeof(buf));
        // recvfrom
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        int str_len = recvfrom(h_sock, buf, sizeof(buf), 0, (struct sockaddr*) &clnt_addr, &clnt_addr_size);

        cout << "get message: " << buf << endl;

        sendto(h_sock, buf, str_len, 0, (struct sockaddr*) &clnt_addr, clnt_addr_size);

        cout << "loop fin" << endl;
    }

    close(h_sock);
    return 0;
}