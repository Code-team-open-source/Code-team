#ifndef TASK_SLIDERS_H
#define TASK_SLIDERS_H
#include "task_button.h"
#include "sliders.h"
#include "ServerConnection.h"

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
    void serialize(ServerConnection) override;
    void deserialize(ServerConnection) override;
    Task_sliders(QString s = "Task");
};

#endif // TASK_SLIDERS_H
