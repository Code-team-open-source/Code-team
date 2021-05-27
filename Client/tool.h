#ifndef TOOL_H
#define TOOL_H

#include <vector>
#include <QWidget>

extern std::vector<std::pair<int, std::string>> vec;

class Tool : public QWidget
{
    Q_OBJECT
public:
    explicit Tool(QWidget *parent = nullptr);

signals:

};

#endif // TOOL_H
