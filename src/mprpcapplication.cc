#include <iostream>
#include <unistd.h>

#include "mprpcapplication.h"

void ShowArgsHelp() {
    std::cout << "format: command -i <configfiel>" << std::endl;
}

MprpcApplication &MprpcApplication::GetInsantce() {
    static MprpcApplication instance;
    return instance;
}

void MprpcApplication::Init(int argc, char **argv) {
    if (argc < 2) {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while ((c = getopt(argc, argv, "i:")) != -1) {
        switch (c) {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            std::cout << "invalid args!" << std::endl;
            exit(EXIT_FAILURE);
            break;
        case ':':
            std::cout << "need <configfile>" << std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    // 开始加载配置文件 rpcserver_ip rpcserver_port zookerper_ip zookeeper_port
}
