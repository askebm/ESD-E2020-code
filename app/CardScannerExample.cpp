#include <cstdlib>
#include <iostream>
#include <array>
#include <mutex>
#include <chrono>

#include <CardScannerTask/CardScannerTask.hpp>

#define SAFE_COUT(x) { static std::mutex mtx_cout; mtx_cout.lock(); std::cout << x; mtx_cout.unlock(); }
using namespace std::chrono_literals;

int main(int argc, char const *argv[])
{
    // main event queue
    std::mutex mtx_events;
    std::queue<Event> events;

    // instantiate task (can be called without name)
    CardScannerTask task("MyTask", events, mtx_events);

    // start task
    if (not task.start())
    {
        std::cerr << "Could not start the " << task.name << " task." << std::endl;
        exit(-1);
    }
    auto e = Event(CardScannerTask::GET_CARD_NUMBER);
    task.sendEventToTask(e);
    // main loop
    while(true)
    {
        static size_t t = 0;

        SAFE_COUT("[main] checking for events... [" << std::to_string(++t) << "]" << std::endl);

        std::this_thread::sleep_for (std::chrono::seconds(1));
        // check for events from tasks (using helper method)
        auto event = Task::getEventFromQueue(events, mtx_events);
        if (not event)
            continue;

        SAFE_COUT("[main] Received an event..." << std::endl);
        auto dataevent= event->getData<CardScannerTask::Msg>();
        for(int i = 0; i < dataevent.length; i++)
        {
            SAFE_COUT(dataevent.data[i]);
        }
        SAFE_COUT( std::endl);

        SAFE_COUT("[main] sending event..." << std::endl);
        auto e = Event(CardScannerTask::GET_CARD_NUMBER);
        task.sendEventToTask(e);

    } // while
    // exit program
    return 0;
}
