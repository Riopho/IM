#include <iostream>
#include "network.h"
using namespace std;
#define CHECK_RET(ret) if(-1==ret)return -1;

int main(int argc, char **argv)
{
    if (3 != argc)
    {
        return -1;
    }

    int ret = 0;
    Network net_work;
    int send_port = atoi(argv[1]);
    int recv_port = atoi(argv[2]);
    ret = net_work.Init(send_port, recv_port);
    CHECK_RET(ret);

    char sz_inputbuf[256];
    snprintf(sz_inputbuf, sizeof(sz_inputbuf), "hello UDP");
    ret = net_work.sendMsg(sz_inputbuf, sizeof(char) * 256);
    CHECK_RET(ret);

    char sz_outputbuff[256];
    size_t len;
    net_work.recvMsg(sz_outputbuff, len);
    CHECK_RET(ret);
    
    cout << sz_outputbuff << endl;
}
