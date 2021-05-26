//
// Created by Fedya on 19.04.2021.
//

#ifndef CODE_TEAM_PROTOCOLS_H
#define CODE_TEAM_PROTOCOLS_H
#include "task.h"
#include "task_button.h"
#include "task_sliders.h"
#include "task_dial.h"
#include "task_git_tool.h"
#include "task_buttons_6.h"
#include "ClientConnection.h"
#include <cassert>
#include <QString>

struct protocol {
//private:
    ClientConnection s;
public:
    protocol() {
       int res = 1;
        while (res != 0) {
        Sleep(50);
        res = s.Connect();
    }
    }

    void SendTool(Task &t) {
        s.SendString(t.GetName());
        t.serialize(s);
    }

    Task *GetTool(int i) {
        printf("In GetTool\n");
        std::string str = s.GetString();
        printf("str = %s\n", str.c_str());
        Task *t;
        if (str == "Button") {
            t = new Task_button();
            printf("button holelua");
//            system.pause(0);
        }
        else if (str == "Slider") {
            t = new Task_sliders();
        }
        else if (str == "Dial") {
            t = new Task_dial();
        }
        else if (str == "CMD") {
            t = new Task_git_tool();
        }
        else {
            printf("not button :(");
//            s.m->setText(QString::fromStdString(str + std::to_string(i)));
        }
        t->deserialize(s);
        return t;
    }

    void SendString(const std::string &str) {
        s.SendString(str);
    }
    void SendInt(const int a) {
        s.SendInt(a);
    }

    std::string GetString() {
        return s.GetString();
    }

    int GetInt() {
        return s.GetInt();
    }
};
#endif  // CODE_TEAM_PROTOCOLS_H
