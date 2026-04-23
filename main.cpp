#include <di-core.hpp>

#include <iostream>
#include <string>

class Server : public Bean<Server> {
    BEAN;
    int    port;
    std::string host;
    AUTOWIRED_SETTER_QLFR(int,         port, "server.port");
    AUTOWIRED_SETTER_QLFR(std::string, host, "server.host");
public:
    DEFAULT_CONSTRUCTOR;
    Server() = default;
    void print() {
        std::cout << "host: " << host << "  port: " << port << "\n";
    }
};

int main() {
    
    Container::getInstance().initialize();

    auto& srv = *static_cast<Server*>(Container::getInstance().getInjectable(typeid(Server))->instance);
    srv.print();
}