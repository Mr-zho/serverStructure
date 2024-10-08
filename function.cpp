#include "function.h"
#include <cstring>

/* 构造函数 */
Function::Function(const StdTcpSocketPtr & clientInfo)
{
    m_clientInfo = clientInfo;
}

/* 析构函数 */
Function::~Function()
{

}

void Function::handleRegisterInfo(const Msg & msg)
{
    /* todo... */
    std::cout << "username:" << msg.name << std::endl;
    std::cout << "passwd:" << msg.passwd << std::endl;


#if 1
    ReplyMsg responseMsg;
    responseMsg.type = REGISTER;
    /* 判断用户是否存在 */
    if (userIsExist(msg.name) == true)
    {
        responseMsg.statue_code = REGISTER_USEREXIST;
    }
    else
    {
        responseMsg.statue_code = REGISTER_SUCCESS;
        /* todo... */
    }

    /* 将信息发送回客户端 */
    this->m_clientInfo->sendMessage(static_cast<const void *>(&responseMsg), sizeof(responseMsg));
#endif
}

void Function::handleLoginInfo(const Msg & msg)
{
    std::cout << "username:" << msg.name << std::endl;
    std::cout << "passwd:" << msg.passwd << std::endl;

   

    string username(msg.name);
    string passwd(msg.passwd);

    ReplyMsg responseMsg;
    /* 清除脏数据 */
    memset(&responseMsg, 0, sizeof(responseMsg));

    responseMsg.type = LOGIN;

    if (username == "zhangsan")
    {
        if (passwd == "123456")
        {
            /* 用户名和密码匹配 - 登录成功. */
            responseMsg.statue_code = LOGIN_SUCCESS;
        }
        else
        {
            /*  用户名和密码不匹配 - 登录失败 */
            responseMsg.statue_code = LOGIN_PASSWD_ERROR;
        }
    }
    else
    {
        /* 没有该用户 */
        responseMsg.statue_code = LOGIN_NOUSER;
    }

    /* 发送信息给客户端 */
    m_clientInfo->sendMessage(static_cast<const void *>(&responseMsg), sizeof(responseMsg));

#if 0
    /* 判断用户名是否已经注册 */
    if (userIsExist(username) == false)
    {
        /* 程序进入这个里面, 说明用户名不存在 */


        /* 将信息发送到客户端 */
        
    }
    else 
    {
        /* 如果用户名存在, 判断用户名和密码是否匹配 */
        userIsMatchPasswd(username, passwd);

        /* 判断用户是否已经登陆 */
        userIsOnlined(username);
    }
#endif
}


/* 判断用户名是否存在 */
bool Function::userIsExist(const char * username)
{
    /* todo... */
    return true;
}

/* 用户名和密码是否匹配 */
bool Function::userIsMatchPasswd(const char * username, const char *  passwd)
{
    /* todo... */
    return true;
}

/* 用户是否已经登陆/在线 */
bool Function::userIsOnlined(const char * username)
{
    /* todo... */
    return true;
}


void Function::handleAddFriendInfo(const Msg & msg)
{
    cout << "msg.toName" << msg.toName << endl;
}