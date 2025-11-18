#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "user.pb.h"

#include <iostream>

int main(int argc, char **argv) {
    // 整个程序启动以后，想使用mprpc框架来使用rpc服务调用，需要先调用框架的初始化函数(只初始化一次)
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");

    // rpc方法的响应
    fixbug::LoginResponse response;

    // 调用stub类的具体的方法都会调用到RpcChannel的CallMethod方法
    // 因此在该方法执行逻辑就是根据传入的参数序列化参数并且网络传输

    // 发起rpc方法的调用，同步的rpc调用过程
    stub.Login(nullptr, &request, &response, nullptr);

    // 一次rpc调用完成，读响应
    if (0 == response.result().errcode()) {
        std::cout << "rpc login response:" << response.success() << std::endl;
    } else {
        std::cout << "rpc login response error:" << response.result().errmsg()
                  << std::endl;
    }

    return 0;
}