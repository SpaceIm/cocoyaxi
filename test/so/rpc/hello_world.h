// Autogenerated. DO NOT EDIT. All changes will be undone.

#pragma once

#include "co/so/rpc.h"

namespace xx {

class HelloWorld : public rpc::Service {
  public:
    typedef void (HelloWorld::*Fun)(const Json&, Json&);

    HelloWorld() : _name("xx.HelloWorld") {
        _methods[hash64("hello")] = &HelloWorld::hello;
        _methods[hash64("world")] = &HelloWorld::world;
    }

    virtual ~HelloWorld() {}

    virtual const char* name() const {
        return _name.c_str();
    }

    virtual void process(const Json& req, Json& res) {
        json::Value method = req["method"];
        if (!method.is_string()) {
            res.add_member("err", 400);
            res.add_member("errmsg", "req has no method");
            return;
        }

        auto it = _methods.find(hash64(method.get_string(), method.string_size()));
        if (it == _methods.end()) {
            res.add_member("err", 404);
            res.add_member("errmsg", "method not found");
            return;
        }

        (this->*(it->second))(req, res);
    }

    virtual void hello(const Json& req, Json& res) = 0;

    virtual void world(const Json& req, Json& res) = 0;

  private:
    std::unordered_map<uint64, Fun> _methods;
    fastring _name;
};

class HelloWorldClient {
  public:
    HelloWorldClient(const char* ip, int port, bool use_ssl=false)
        : _rpc_cli(ip, port, use_ssl), _serv_name("xx.HelloWorld") {
    }

    HelloWorldClient(const HelloWorldClient& c)
        : _rpc_cli(c._rpc_cli), _serv_name(c._serv_name) {
    }

    ~HelloWorldClient() {}

    void set_userpass(const char* user, const char* pass) {
        _rpc_cli.set_userpass(user, pass);
    }

    void close() {
        _rpc_cli.close();
    }

    Json make_req_hello() {
        Json req;
        req.add_member("service", _serv_name);
        req.add_member("method", "hello");
        return req;
    }

    Json make_req_world() {
        Json req;
        req.add_member("service", _serv_name);
        req.add_member("method", "world");
        return req;
    }

    Json perform(const Json& req) {
        Json res;
        _rpc_cli.call(req, res);
        return res;
    }

    void ping() {
        _rpc_cli.ping();
    }

  private:
    rpc::Client _rpc_cli;
    fastring _serv_name;
};

} // xx
