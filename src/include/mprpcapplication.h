#ifndef __MPRPCAPPLICATION_H__
#define __MPRPCAPPLICATION_H__

// mprpc框架的基础类 负责框架的一些初始化操作
class MprpcApplication {
public:
    static MprpcApplication &GetInsantce();

    static void Init(int argc, char **argv);

private:
    MprpcApplication(){};
    MprpcApplication(const MprpcApplication &) = delete;
    MprpcApplication(MprpcApplication &&) = delete;
};

#endif // __MPRPCAPPLICATION_H__