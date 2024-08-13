#include "messageHandler.h"


/* 构造函数 */
MessageHandler::MessageHandler(const StdTcpSocketPtr & client): m_bussinssFunc(client)
{
    /* 注册消息处理函数 */
    m_handles[REGISTER] = [this](const Msg& msg) { m_bussinssFunc.handleRegisterInfo(msg); };
    m_handles[LOGIN] = [this](const Msg& msg) { m_bussinssFunc.handleLoginInfo(msg); };

    /* todo... 添加更多处理函数 */
}

/* 析构函数 */
MessageHandler::~MessageHandler()
{

}


void MessageHandler::handleMessage(const Msg& msg)
{
    auto iter = m_handles.find(msg.type);
    if (iter != m_handles.end())
    {
        /* 执行回调函数 */
        iter->second(msg);
    }
    else
    {
        // 处理未知的消息类型
        std::cout << "Unknown message type: " << msg.type << std::endl;
    }
}