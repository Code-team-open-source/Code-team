Использующиеся структуры:
У клиента и сервера есть структура с инструментами:

class Tool {
    tool_text
    size_on_screen
};

Types of Tools:

class Button : Tool {
    position = {pushed, not_pushed};
};

class Slider : Tool { // ползунок
    position = // в каком положении ползунок
};

Типы инструментов таким образом расписываем дальше.

*На клиенте*:
class Player {
    Task
    vector<Tool>
};


class Task {
    task_text
    timer
};

*На сервере*

class Task {
    task_text
    Player // у кого сейчас это задание
    vector<{Tool, correct positions to do task}>
    time
};

class Player {
    name
    vector<Tool>
    current_task;
}

enum Game_status {
    waiting, playing, end_of_game
}

class Game {
    Game_status
    round
    time_left
    fails_left
};


map pool_connection:
    [player_id] = [Player, socket]


Передаем клиент -> серверу: 1.
Передаем сервер -> клиенту: 2.


Клиент:
main {
    player pl =  connect_to_server(*name*)
    /*
     * При подключении посылаем на сервер имя, в ответ получаем набор Tool,
     * которые будут отображаться на экране
     */
    when (game_status == playing) {
        pl.task = get_initial_task_from_server
    }
    while (game_status != end_of_game) {
        /*интеракция с пользователем*/
        send_to_server()
        /*
         * На сервер посылаем индекс измененного Tool и его новое положение
         */
    }
}

send_to_server() {
    Есть 2 вида информации, которую может отправить клиент серверу:
      -он выполнил действие с каким-либо своим инструментом
      -истекло время на выполнение его задания:
              в этом случае надо будет еще принять новое задание
}


Сервер:
    vector<int> all_tasks{...};
    start_game{
        while (game_status == waiting) {
          waiting_for_new_players() :
              add to pool_connection
        }
        get_random_tasks(n); // записываем n случайных заданий в all_tasks

    }
    vector<Task> current_tasks
    vector<int> players_to_change_task
    get_from_client(int changed_tool) {
            /*
             * Проходимся по all_tasks:
             */
            if completed_task \in current_tasks
                    players_to_change_task.push_back(...);
            else {
                    num_of_fails++
                    if (num_of_fails > ALLOWED_FAILS)
                            game_status = end_of_game;

            }
            if (current_player \in players_to_change_task)
                    new task_to_him;

            return {game_status, bool new_task, task_to_him, (num_of_fails mb)}
    }

Начало игры
1 -> готов
Сервер записывает игрока в пул
игрок после потверждения сервера меняет статус на ожидание


во время игры
1-> клиент шлет (постоянно) серверу проверку состояния.
. игрок ничего не делал
. номер сделанного задания.
2->game_status,  (смени задание на новое, время на новое задание), кол-во общих ошибок,.


1-> каждую секунду посылает серверу подтверждение ожидания,
2-> когда набирается народ посылает готовность, задания, время
клиент меняет статус.
1-> во время игры клиент посылает серверу что сделал игрок, сервер отвечает:
// .все ок, какое то задание выполнено, 
// .не ок (уменьши время у б), увеличивается колво общих ошибок.

2-> 
игрок задание 


