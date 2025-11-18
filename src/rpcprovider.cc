#include "rpcprovider.h"
#include "mprpcapplication.h"

#include <functional>
#include <string>

void RpcProvider::NotifyService(google::protobuf::Service *service) {}

void RpcProvider::Run() {

    std::string ip =
        MprpcApplication::GetInsantce().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MprpcApplication::GetInsantce()
                             .GetConfig()
                             .Load("rpcserverport")
                             .c_str());
    muduo::net::InetAddress address(ip, port);

    // 创建TcpServer对象
    muduo::net::TcpServer server(&m_eventLoop, address, "RpcProvider");
    // 绑定连接回调和消息读写回调
    server.setConnectionCallback(
        std::bind(&RpcProvider::onConnection, this, std::placeholders::_1));
    server.setMessageCallback(
        std::bind(&RpcProvider::onMessage, this, std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3));
    // 设计muduo库的线程数量
    server.setThreadNum(4);

    std::cout << "RpcProvider start service at ip:" << ip << " port:" << port
              << std::endl;

    // 启动网络服务
    server.start();
    m_eventLoop.loop();
}

void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &conn) {}

void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &conn,
                            muduo::net::Buffer *, muduo::Timestamp) {}
