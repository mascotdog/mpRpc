#ifndef __MPRPCAPPLICATION_H__
#define __MPRPCAPPLICATION_H__

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

// mprpc框架的基础类 负责框架的一些初始化操作
class MprpcApplication {
public:
    static MprpcApplication &GetInstance();

    static void Init(int argc, char **argv);
    static MprpcConfig& GetConfig();

private:
    static MprpcConfig m_config;

    MprpcApplication(){};
    MprpcApplication(const MprpcApplication &) = delete;
    MprpcApplication(MprpcApplication &&) = delete;
};

#endif // __MPRPCAPPLICATION_H__