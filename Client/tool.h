#ifndef TOOL_H
#define TOOL_H

#include <vector>
#include <QWidget>

extern std::vector<std::pair<int, std::string>> vec;
extern std::string name;
extern std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>> cr_ts;
extern std::string ip;
extern std::string for_start;

class Tool : public QWidget
{
    Q_OBJECT
public:
    explicit Tool(QWidget *parent = nullptr);

signals:

};

#endif // TOOL_H
