#pragma once
#include <USBDriver/USBDriver.hpp>
#include <Task/Task.hpp>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>

class CardScannerTask : public Task
{
public:

    // Types.
    using Task::Task;
    using DATA = std::array<char,4>;

    enum Command
    {
        GET_CARD_NUMBER = 1,
    };

    // Messages.
    struct Msg
    {
        DATA data;
        int length;
    };

    // Methods.
    CardScannerTask() = delete;
    ~CardScannerTask();

    virtual void run() override;
    virtual bool init() override;

protected:

    // Attributes.
    USBDriver       USBd;
    DATA         data;
    std::string device_path = "/dev/input/event1";
};


