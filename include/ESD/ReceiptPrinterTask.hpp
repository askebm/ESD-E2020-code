#ifndef RECEIPTPRINTERTASK_H
#define RECEIPTPRINTERTASK_H

//#include <ESD/ReceiptFormatter.hpp>
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
        RECEIVED_RECEIPT = 1,
        RECIEPT_PRINTER_NO_PAPER = 2
    };
    ReceiptPrinterTask() = delete;
    ~ReceiptPrinterTask();
    
    virtual bool init() override;
    virtual void run() override;

    void printReceipt(std::vector<std::string> formatted_receipt);
    
protected:
    ReceiptPrinterDriver m_printer;        
    ReceiptItems m_receiptItems;

};

class ReceiptFormatter
{
private:
    void addHeading(std::string heading);
    void addItemLine(std::string item, std::string qty, std::string price, std::string line_sum);
    void addSum(std::string receipt_sum);
    void addReceiptId(std::string receipt_id); 
    void addEmptyLines(int number_of_lines);

    ReceiptPrinterTask::ReceiptItems m_receipt;
    std::vector<std::string> m_formatted_receipt;

public:
    ReceiptFormatter(ReceiptPrinterTask::ReceiptItems receipt);
    ~ReceiptFormatter();

    std::vector<std::string> formatReceipt();
};

#endif /* RECEIPTPRINTERTASK_H */
