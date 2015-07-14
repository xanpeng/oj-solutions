// ZOJ后台是C++程序，前台是Java，前后台通过socket通信
// 前台响应网页提交和点击，并有很多管理Submission的逻辑，不便简化，偷懒跳过
// 后台的主要逻辑简化如下
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;

//
// util functions
//
int writen(int fd, const void* buffer, size_t count) {
    const char* p = (const char*)buffer;
    while (count > 0) {
        int num = write(fd, p, count);
        if (num == -1) {
            cerr << "Failed to write to fd" << endl;
            return -1;
        }
        p += num;
        count -= num;
    }
    return 0;
}

static inline int write_uint32(int fd, uint32_t value) {
    value = htonl(value);
    return writen(fd, &value, sizeof(value));
}

//
// Runner system
//
class Runner {
public:
    Runner(int sock) : sock_(sock) {}
    virtual ~Runner();
    int run();
protected:
    virtual void internal_run() = 0;
    int send_running_message();
    int sock_;
    int result_;
    int time_limit_, memory_limit_;
    int time_consumption_, memory_consumption_;
    pid_t pid_;
};
Runner::~Runner() {
    killpg(pid_, SIGTERM);
}
int Runner::run() {
    cout << "Running" << endl;
    internal_run();
    write_uint32(sock_, result_);
    return result_;
}

class NativeRunner : public Runner {
public:
    NativeRunner(int sock) : Runner(sock) {}
    virtual void internal_run();
};
void NativeRunner::internal_run() {
    pid_ = fork();
    if (pid_ == -1) {
        cerr << "Failed to execute" << endl;
        result_ = -1;
        return;
    }
    // trace pid_, fake here
    time_consumption_ = 100;
    memory_consumption_ = 100;
    write_uint32(sock_, time_consumption_);
    write_uint32(sock_, memory_consumption_);
}
// class JavaRunner : public Runner {};

//
// socket utility
//
int create_server_socket(int* port) {
    int sock = socket(PF_INET, SOCK_STREAM, 6);
    if (sock == -1) {
        cerr << "Failed to create socket" << endl;
        return -1;
    }

    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = 0;
    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) == -1) {
        cerr << "Failed to bind" << endl;
        close(sock);
        return -1;
    }
    if (listen(sock, 32) == -1) {
        cerr << "Failed to listen" << endl;
        close(sock);
        return -1;
    }
    socklen_t len = sizeof(address);
    if (getsockname(sock, (struct sockaddr*)&address, &len) == -1) {
        cerr << "Failed to get socket port" << endl;
        close(sock);
        return -1;
    }
    *port = ntohs(address.sin_port);
    return sock;
}

//
// judger
// 
int exec_testcase_command(int sock) {
    Runner* runner = new NativeRunner(sock);
    int result = runner->run();
    delete runner;
    return result == -1 ? -1 : 0;
}

int judge_main(int sock) {
    int ret;
    if (exec_testcase_command(sock) == -1) {
        ret = -1;
    }
    close(sock);
    return ret;
}

//
// server entry
//
int main() {
    int port;
    int server_sock = create_server_socket(&port);
    if (server_sock < 0) {
        return EXIT_FAILURE;
    }
    cout << "Listening on port" << endl;

    sockaddr_in addr;
    socklen_t len = sizeof(sockaddr_in);
    int sock = accept(server_sock, (struct sockaddr*)&addr, &len);
    if (sock == -1) {
        cerr << "Failed to accept" << endl;
        return EXIT_FAILURE;
    }

    exit(judge_main(sock));
}
