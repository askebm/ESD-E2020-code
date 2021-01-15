#ifndef RECEIPTPRINTERTASK_H
#define RECEIPTPRINTERTASK_H

#include <ESD/driver/ReceiptPrinterDriver.hpp>
#include <Task/Task.hpp>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <array>
#include <mutex>
#include <chrono>


using namespace std::chrono_literals;

class ReceiptPrinterTask final : public Task
{
public:
	using Task::Task;
    
    struct ReceiptItems
    {
        std::vector<std::string> items;
        std::vector<std::string> quantity;
        std::vector<std::string> item_price;
        std::vector<std::string> line_sum;
        std::string receipt_sum;
        std::string receipt_id;
    };

    struct Msg
    {
        ReceiptItems m_receiptItems;
    };

    enum Printer
    {
        RECEIVED_RECEIPT = 1
    };
    ReceiptPrinterTask() = delete;
    ~ReceiptPrinterTask();
    
    virtual bool init() override;
    virtual void run() override;

    void printReceipt(ReceiptItems);

    
protected:
    ReceiptPrinterDriver m_printer;        
    ReceiptItems m_receiptItems;

};

#endif /* RECEIPTPRINTERTASK_H */
