//
// Created by Fedya on 19.04.2021.
//

#ifndef CODE_TEAM_PROTOCOLS_H
#define CODE_TEAM_PROTOCOLS_H
#include "Tool.h"
#include "ServerConnection.h"
#include <cassert>

struct protocol {
private:
    ServerConnection s;
public:
    protocol() {
        s.connect();
    }
    void SendTool(Tool &t) {
        s.SendString(t.tool_name());
        t.serialize(s);
    }
    void GetTool(Tool &t) {
        std::string str = s.GetString();
        assert(t.tool_name() == str);
        t.deserialize(s);
    }
    void send_string(const std::string &str) {
        s.SendString(str);
    }
    std::string get_string() {
        return s.GetString();
    }
    int get_int() {
        return s.GetInt();
    }
};
#endif  // CODE_TEAM_PROTOCOLS_H
