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
#include <QString>

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

    Task *GetTool() {
        std::string str = s.GetString();
//        assert(t.GetName() == str);
        //if (str == "Button") {
            std::string text = s.GetString();
            int id = s.GetInt();
            return new Task_button(QString::fromStdString(text), id);
        //}
    }

    void SendString(const std::string &str) {
        s.SendString(str);
    }

    std::string GetString() {
        return s.GetString();
    }

    int GetInt() {
        return s.GetInt();
    }
};
#endif  // CODE_TEAM_PROTOCOLS_H
