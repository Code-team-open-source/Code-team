//
// Created by Fedya on 19.04.2021.
//

#ifndef CODE_TEAM_PROTOCOLS_H
#define CODE_TEAM_PROTOCOLS_H
#include <cassert>
#include "ServerConnection.h"
#include "Tool.h"

struct protocol {
    ServerConnection s;
    protocol() {
        s.connect();
    }
    void SendTool(Tool &t) {
        t.serialize(s);
    }
    Tool *GetTool() {
        std::string str = s.GetString();
        Tool *t;
        if (str == "Button") {
            t = new Button("");
        }
        if (str == "Slider") {
            t = new Slider("");
        }
        t->deserialize(s);
        return t;
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
    void send_int(int x) {
        s.SendInt(x);
    }
};
#endif  // CODE_TEAM_PROTOCOLS_H
