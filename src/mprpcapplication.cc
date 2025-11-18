#include "mprpcapplication.h"
MprpcApplication &MprpcApplication::GetInsantce() {
    static MprpcApplication instance;
    return instance;
}

void MprpcApplication::Init(int argc, char **argv) {}
