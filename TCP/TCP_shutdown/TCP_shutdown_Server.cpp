#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

using namespace std;

/*
 * 1. 클라이언트가 서버에게 메세지 전송 후 출력 스트림 shutdown
 * 2. 서버는 EOF 받으면 버퍼 내용 에코
 * 에러 처리는 생략
 */
int main(int argc, char *argv[])
{
    int h_sock = socket(PF_INET, SOCK_STREAM, 0);
    char read_buf[100] = {};
    char append_buf[100] = {};

    sockaddr_in serv_addr, clnt_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(stoi("12345"));
    bind(h_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    listen(h_sock, 5);

    while(1)
    {
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        int clnt_sock = accept(h_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
        int str_len = 0;
        int curr_len = 0;
        while((curr_len = read(clnt_sock, read_buf, sizeof(read_buf))) != 0)
        {
            cout << "we get: " << read_buf << endl;
            strcat(append_buf, read_buf);
            memset(&read_buf, 0, sizeof(read_buf));
            str_len += curr_len;
        }
        cout << "stream closed" << endl;
        cout << "total: " << append_buf << endl;
        write(clnt_sock, append_buf, str_len);
        cout << "write complete" << endl;
    }
    return 0;
}