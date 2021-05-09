//
// Created by Fedya on 19.04.2021.
//

#ifndef CODE_TEAM_PROTOCOLS_H
#define CODE_TEAM_PROTOCOLS_H
#include "task.h"
#include "task_button.h"
#include "task_sliders.h"
#include "ClientConnection.h"
#include <cassert>

struct protocol {
private:
    ClientConnection s;
public:
    protocol() {
        s.Connect();
    }

    void SendTool(Task &t) {
        s.SendString(t.GetName());
        t.serialize(s);
    }

    void GetTool(Task &t) {
        std::string str = s.GetString();
        assert(t.GetName() == str);
        t.deserialize(s);
    }
};
#endif  // CODE_TEAM_PROTOCOLS_H
