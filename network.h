#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Network
{
    public:
        Network(): _socket_fd(-1)
        { 
            memset(&selfAddr, 0, sizeof(selfAddr));
            memset(&otherAddr, 0, sizeof(otherAddr));
        }

        int sendMsg(const char* buff, size_t buff_len)
        {
            return sendto(_socket_fd, buff, buff_len, 0, (struct sockaddr*)&otherAddr, sizeof(otherAddr));
        } 

        int recvMsg(char* buff, size_t& buff_len)
        {
            int len = sizeof(otherAddr);
            return recvfrom(_socket_fd, buff, buff_len, 0, (struct sockaddr*)&otherAddr, (socklen_t*)&len);

        }

        int Init(int send_port, int recv_port)
        {
            if (-1 == _init_socket(send_port, recv_port))
            {
                return -1;
            }
            return bind(_socket_fd, (struct sockaddr*)&selfAddr, sizeof(selfAddr));
        }

        int Getfd()
        {
            return _socket_fd;
        }

    private:
        int _socket_fd;
        sockaddr_in selfAddr;
        sockaddr_in otherAddr;

        int _connect()
        {
            return 0;
        }

        int _init_socket(int send_port, int recv_port)
        {
            _socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
            if (-1 == _socket_fd)
            {
                return -1;
            }

            selfAddr.sin_family = AF_INET;
            selfAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
            selfAddr.sin_port = htons(send_port);

            otherAddr.sin_family = AF_INET;
            otherAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
            otherAddr.sin_port = htons(recv_port);

            return 0;
        }

};
