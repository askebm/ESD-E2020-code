#pragma once
#include <USBDriver/USBDriver.hpp>
#include <Task/Task.hpp>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>

class BarCodeScannerTask : public Task
{
public:

    // Types.
    using Task::Task;
    using DATA = std::array<char,4>;

    enum Command
    {
        GET_BARCODE = 1,
    };

    // Messages.
    struct Msg
    {
        DATA data;
        int length;
    };

    // Methods.
    BarCodeScannerTask() = delete;
    ~BarCodeScannerTask();

    virtual void run() override;
    virtual bool init() override;

protected:

    // Attributes.
    USBDriver       USBd;
    DATA         data;
    std::string device_path = "/dev/input/event0";
};


