#ifndef TASK_SLIDERS_H
#define TASK_SLIDERS_H
#include "task_button.h"
#include "sliders.h"
#include "ClientConnection.h"

class Task_sliders : public Task
{
public:
    int available_positions = 10;
    int current_state = 0;
    int orientation = 0;
    Sliders *sl;
    std::string GetName() override{
        return "Slider";
    }
    void serialize(ClientConnection&) override;
    void deserialize(ClientConnection&) override;
    Task_sliders(QString s = "Task", int id = 0);
    ~Task_sliders() override;
};

#endif // TASK_SLIDERS_H
