#ifndef ICOMMANDHANDLER_H
#define ICOMMANDHANDLER_H

#include <QObject>

class ICommandHandler : public QObject
{
    Q_OBJECT
public:
    explicit ICommandHandler();
    
signals:
    
public:
    virtual QString handlerName() = 0;
    virtual void handleCommand(const QStringList &cmdDetail, int index) = 0;
    void reply(const QStringList &replyList, int index);
};

//��¼
class LoginHandler : public ICommandHandler
{
    Q_OBJECT
public:
    explicit LoginHandler(){}
public:
    QString handlerName()
    {
        return "DL";
    }

    void handleCommand(const QStringList &cmdDetail, int index);
};

//����
class OpenMachineHandler : public ICommandHandler
{
    Q_OBJECT
public:
    OpenMachineHandler(){}
public:
    QString handlerName()
    {
        return "KJ";
    }
    void handleCommand(const QStringList &cmdDetail, int index);
};

//��̨
class OpenTableHandler : public ICommandHandler
{
    Q_OBJECT
public:
    OpenTableHandler(){}
public:
    QString handlerName()
    {
        return "KT";
    }
    void handleCommand(const QStringList &cmdDetail, int index);
};

//��̨
class ChangeTableHandler : public ICommandHandler
{
    Q_OBJECT
public:
    ChangeTableHandler(){}
public:
    QString handlerName()
    {
        return "HT";
    }
    void handleCommand(const QStringList &cmdDetail, int index);
};

//���
class OrderHandler : public ICommandHandler
{
    Q_OBJECT
public:
    OrderHandler(){}
public:
    QString handlerName()
    {
        return "DC";
    }
    void handleCommand(const QStringList &cmdDetail, int index);
};

//�յ�����Ϣ
class MessageHandler : public ICommandHandler
{
    Q_OBJECT
public:
    MessageHandler(){}
public:
    QString handlerName()
    {
        return "DX";
    }
    void handleCommand(const QStringList &cmdDetail, int index);
};

class BackDishHandler : public ICommandHandler
{
    Q_OBJECT
public:
    BackDishHandler(){}
public:
    QString handlerName()
    {
        return "TC";
    }
    void handleCommand(const QStringList &cmdDetail, int index);
};


#endif // ICOMMANDHANDLER_H
