#include "network.h"
#include <iostream>
#include <sys/select.h>
#include <pthread.h>
using namespace std;

#define CHECK_RET(ret) if(-1==ret)return -1;


void* read_worker(void* ptr)
{
    Network* net = (Network*)ptr;
    int ret = 0;
    size_t len = 0;
    fd_set set;
    timeval refresh_time;
    refresh_time.tv_sec = 1;
    refresh_time.tv_usec = 0;
    char buff[256];
    len = sizeof(buff);
    while(1)
    {
        memset(&buff, 0, sizeof(buff));
        FD_ZERO(&set);
        FD_SET(net->Getfd(), &set);
        int max_sock = net->Getfd() + 1; 
        ret = select(max_sock, &set, NULL, NULL, &refresh_time);

        if (0 < ret)
        {
            if (FD_ISSET(net->Getfd(), &set))
            {
                ret = net->recvMsg(buff, len);
                cout << buff << endl;
            }
        }
    }
    
}

void* send_worker(void* ptr)
{
    Network* net = (Network*)ptr;
    int ret = 0;
    char buff[256];
    while (1)
    {
        memset(&buff, 0, sizeof(buff));
        cin >> buff;
        net->sendMsg(buff, sizeof(buff));
    }
}

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

    pthread_t tid_read,tid_send;
    ret = pthread_create(&tid_send, NULL, &read_worker, (void *)&net_work);
    CHECK_RET(ret);
    ret = pthread_create(&tid_read, NULL, &send_worker, (void *)&net_work);
    CHECK_RET(ret);

    pthread_join(tid_read, NULL);
    pthread_join(tid_send, NULL);

    return 0;

}
