#include "task_sliders.h"

Task_sliders::Task_sliders(QString s) : Task(s)
{
    sl = new Sliders();
    gr->setLayout(sl->lv);
}

void Task_sliders::serialize(ServerConnection s) {
    s.SendString("Slider");
    Task::serialize(s);
    s.SendInt(available_positions);
    s.SendInt(current_state);
    s.SendInt(orientation);
}

void Task_sliders::deserialize(ServerConnection s) {
    std::string check = s.GetString();
    assert(check == "Slider");
    Task::deserialize(s);
    available_positions = s.GetInt(); // working?
    current_state = s.GetInt();
    orientation = (s.GetInt());
}
