#include <iostream>
using namespace std;
#include "stdTcpServer.h"
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include "stdShared.h"
#include "function.h"
#include "messageHandler.h"
#include "threadpool.h"

#define __WUZIQI__DEFINE_   0

#define BUFFER_SIZE 1024

void * handleClientInfo(void * arg)
{
    /* 线程分离 */
    pthread_detach(pthread_self());

    cout << "handleClientInfo" << endl;
    StdTcpSocketPtr clientInfo = *static_cast<StdTcpSocketPtr*>(arg);

    int readBytes = 0;
    
#if __WUZIQI__DEFINE_

    
    std::string playerName = "mr_zhou";
    MessageHandler handles(clientInfo, playerName); // 传递playerName

    char buffer[256] = { 0 };

    Msg msg;
    /* 清空脏数据 */
    memset(&msg, 0, sizeof(msg));
#else

    Msg msg;
    /* 清空脏数据 */
    memset(&msg, 0, sizeof(msg));

    MessageHandler handles(clientInfo);
#endif

    
    while (1)
    {
#if __WUZIQI__DEFINE_
        readBytes = clientInfo->recvMessage(buffer, sizeof(buffer));
#else
        readBytes = clientInfo->recvMessage(&msg, sizeof(msg));
#endif
        if (readBytes <= 0)
        {
            cout << "readBytes <= 0" << " connfd:" << clientInfo->getSockAttr()->connfd << endl;
            break;
        }
        else
        {
            /* 客户端有数据过来 */
#if __WUZIQI__DEFINE_
            cout << "buffer:" << buffer << endl;
    
            handles.handleMessage(buffer);
#else
            cout << "msg.type:" << msg.type << endl;
            handles.handleMessage(msg);
#endif
        }
#if __WUZIQI__DEFINE_
        memset(buffer, 0, sizeof(buffer));
#else
        memset(&msg, 0, sizeof(msg));
#endif
    }

    /* 资源回收 */
    return NULL;
}

int main()
{
    /* 创建线程池对象 */
    ThreadPool pool(2, 5, 20);

    /* 创建服务器对象 */
    StdTcpServer server;

    /* 设置监听 */
    bool res = server.setListen(8080);
    if (res == false)
    {
        cout << "listen error" << endl;
        _exit(-1);
    }
    cout << "server listening..." << endl;

    int ret = 0;
    while (1)
    {
        StdTcpSocketPtr clientInfo = server.getClientSock();

#if 0
        pthread_t tid;
        ret = pthread_create(&tid, NULL, handleClientInfo, &clientInfo);
        if (ret != 0)
        {
            perror("thread create error:");
            _exit(-1);
        }
#else
        pool.addTask(handleClientInfo, new StdTcpSocketPtr(clientInfo));
#endif

        /* 休眠一下 */
        sleep(1);
    }
}