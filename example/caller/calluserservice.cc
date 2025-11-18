#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "user.pb.h"

#include <iostream>

int main(int argc, char **argv) {
    // 整个程序启动以后，想使用mprpc框架来使用rpc服务调用，需要先调用框架的初始化函数(只初始化一次)
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());

    // 调用stub类的具体的方法都会调用到RpcChannel的CallMethod方法
    // 因此在该方法执行逻辑就是根据传入的参数序列化参数并且网络传输

    return 0;
}