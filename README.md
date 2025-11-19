**mpRpc 概览**
- **简介**: mpRpc 是一个基于 Protobuf 与 Muduo 的轻量级 C++ RPC 框架，提供 `RpcProvider`（服务端）、`MprpcChannel`（客户端通信通道）、`MprpcController`（错误控制）、`MprpcApplication`（应用配置/初始化）等组件。支持通过 ZooKeeper 进行服务注册/发现（示例工程已包含 `zookeeperutil.*`）。
- **协议**: `4 字节 header_size(网络序)` + `RpcHeader(service_name, method_name, args_size)` + `args(payload)`。
- **示例**: `example/` 提供了 `UserService`、`FriendService` 的 Provider 与 Consumer 调用示例，`proto` 位于 `example/*.proto` 与 `src/rpcheader.proto`。

**目录结构**
- `src/`: 框架代码
	- `mprpcapplication.*`: 参数解析与配置加载（`-i <config>`）
	- `mprpcchannel.*`: 客户端打包与发送 RPC 请求
	- `mprpccontroller.*`: 调用错误状态管理
	- `rpcprovider.*`: 基于 Muduo 的服务端，接收并分发请求
	- `logger.*`、`include/logger.h`: 简单日志设施（`LOG_INFO/LOG_ERR`）
	- `zookeeperutil.*`: ZooKeeper 工具封装
	- `rpcheader.proto/.pb.*`: RPC 头的 protobuf 定义
- `example/`: 示例工程
	- `callee/`: `userservice.cc`、`friendservice.cc` 服务实现并发布
	- `caller/`: `calluserservice.cc`、`callfriendservice.cc` 客户端调用
	- `*.proto`: 示例服务的 Protobuf 定义
- `bin/`: 可执行文件与示例配置（构建后生成 `provider`、`consumer`）
- `CMakeLists.txt`: 根构建脚本（`src/` 与 `example/` 均为子工程）

**依赖要求**
- 必需
	- CMake
	- g++ (支持 C++11)
	- Protobuf & protoc（建议系统包：`protobuf-compiler`、`libprotobuf-dev`）
	- Muduo 网络库（编译安装，并保证可被 `find`/`link`）
	- ZooKeeper 客户端库（如 `libzookeeper_mt`），用于服务发现

```bash
sudo apt update
sudo apt install -y build-essential cmake protobuf-compiler libprotobuf-dev zlib1g-dev
```

Muduo 与 ZooKeeper 的安装请参考各自官方文档（或现有环境预装的版本）。

**构建步骤**
```bash
protoc src/rpcheader.proto --cpp_out=./
chmod +x autobuild.sh
./autobuild.sh
```

构建完成后，可执行文件输出到 `bin/` 目录，例如 `bin/provider`、`bin/consumer`。

**配置文件**
- 放置在 `bin/` 下（示例：`test.conf`）。
- 建议内容示例（注意使用 ASCII 的点号 `.`）：
```properties
rpcserverip=127.0.0.1
rpcserverport=8000
zookeeperip=127.0.0.1
zookeeperport=2181
```

**运行示例**
1) 启动 ZooKeeper（如需服务注册/发现）：
```bash
# 参考你的安装路径
${ZK_HOME}/bin/zkServer.sh start
${ZK_HOME}/bin/zkServer.sh status
```

2) 启动 Provider（服务端）：
```bash
./provider -i test.conf
```
- 典型启动日志会包含：
	- `service_name:UserServiceRpc` / `method_name:Login` 等已发布方法
	- `RpcProvider start service at ip:... port:...`

3) 启动 Consumer（客户端）：
```bash
./consumer -i test.conf
```
- 典型输出会打印序列化的请求头、参数，以及服务端响应结果。

提示：Provider 与 Consumer 在不同终端运行，先启动 Provider 再启动 Consumer。确保 `test.conf` 的 `rpcserverip` 与 `rpcserverport` 与 Provider 一致。

**生成/更新 Protobuf**

- 示例 `.proto` 位于 `example/`：
```bash
protoc user.proto --cpp_out=./
protoc friend.proto --cpp_out=./
```
- 框架 RPC 头位于 `src/rpcheader.proto`，通常无需修改；若修改请同步重新生成。

**技术要点**
- `MprpcChannel::CallMethod`: 负责将 `service_name/method_name/args` 打包发送
- `RpcProvider::onMessage`: 读取 4 字节长度（网络序）后，解析 `RpcHeader` 并分发调用
- `MprpcController`: 承载错误码与错误文本（如 socket 连接失败、反序列化失败）
- `Logger`: 简易日志系统（异步队列）
- `ZooKeeper`: 可用于注册与发现服务地址

