#include "mprpcconfig.h"

#include <iostream>
#include <string>

void MprpcConfig::LoadConfigFile(const char *config_file) {
    FILE *pf = fopen(config_file, "r");
    if (!pf) {
        std::cout << config_file << " is not exists" << std::endl;
        exit(EXIT_FAILURE);
    }

    char buf[512] = {0};

    while (fgets(buf, sizeof(buf), pf) != nullptr) {
        std::string src = buf;

        // 去掉前后空格
        // 去掉 '\n'
        if (!src.empty() && src.back() == '\n') {
            src.pop_back();
        }

        // 去掉前空格
        size_t start = src.find_first_not_of(" \t");
        if (start == std::string::npos)
            continue;
        src = src.substr(start);

        // 去掉后空格
        size_t end = src.find_last_not_of(" \t");
        if (end == std::string::npos)
            continue;
        src = src.substr(0, end + 1);

        // 判断注释
        if (src.empty() || src[0] == '#')
            continue;

        // 解析 key=value
        size_t idx = src.find('=');
        if (idx == std::string::npos)
            continue;

        std::string key = src.substr(0, idx);
        std::string value = src.substr(idx + 1);

        // 去掉 key/value 的前后空格
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);

        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        m_configMap[key] = value;
    }

    fclose(pf);
}

std::string MprpcConfig::Load(const std::string key) {
    auto it = m_configMap.find(key);
    if (it == m_configMap.end()) {
        return "";
    }
    return it->second;
}
