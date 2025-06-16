#include "event2/buffer.h"
#include "event2/event.h"
#include "event2/http.h"
#include <iostream>

void api_get(struct evhttp_request* req, void* arg)
{
    // 创建响应的HTTP header
    evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", "text/plain");
    // 创建响应体
    struct evbuffer* buf = evbuffer_new();
    if (!buf) {
        std::cerr << "Failed to create response buffer\n";
        return;
    }
    evbuffer_add_printf(buf, "Hello, World! This is a response from libevent HTTP server.\n");
    // 发送响应
    evhttp_send_reply(req, 200, "OK", buf);
    evbuffer_free(buf); //释放资源
}

int main(int const argc, const char* argv[])
{
    auto* event_base = event_base_new();

    if (!event_base) {
        std::cerr << "create event base failed" << std::endl;
        return -1;
    }

    auto* http_server = evhttp_new(event_base);
    if (!http_server) {
        std::cerr << "create http server failed" << std::endl;
        event_base_free(event_base);
        return -1;
    }

    auto ret = evhttp_bind_socket(http_server, "localhost", 32880);
    if (ret != 0) {
        std::cerr << "bind localhost:32880 failed." << std::endl;
        evhttp_free(http_server);
        event_base_free(event_base);
        return ret;
    }

    evhttp_set_cb(http_server, "/api/get", api_get, nullptr);
    event_base_dispatch(event_base);

    evhttp_free(http_server);
    event_base_free(event_base);
    return 0;
}
