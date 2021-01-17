#include <ESD/ReceiptPrinterTask.hpp>

void ReceiptFormatter::addHeading(std::string heading)
{
    m_formatted_receipt.push_back("    " + heading + "    ");
}

void ReceiptFormatter::addItemLine(std::string item, std::string qty, std::string price, std::string line_sum)
{
    std::string tmp_item;   
    
    if (item.size() > 10) 
    {
        tmp_item = item.substr(0,9);    
    }
    else
    {
        tmp_item = item; 
        //Make sure Item Length is always 10 chars long on receipt. 
        for (int i = 0; i < ( 12 - tmp_item.size() ); ++i) 
        {
            tmp_item.append(" ");
        }
    }

    m_formatted_receipt.push_back(std::string(tmp_item + "  " + qty + "   " + price + "     " + line_sum));
}

void ReceiptFormatter::addSum(std::string receipt_sum)
{
    m_formatted_receipt.push_back(std::string("Total Amount: ") + receipt_sum);
}

void ReceiptFormatter::addReceiptId(std::string receipt_id)
{
    m_formatted_receipt.push_back(std::string("Receipt ID: ") + receipt_id);
}

void ReceiptFormatter::addEmptyLines(int number_of_lines)
{
    for (int i = 0; i < number_of_lines; ++i) 
    {
        m_formatted_receipt.push_back("");
    }
}

std::vector<std::string> ReceiptFormatter::formatReceipt()
{
    addHeading(std::string("The Shop"));
    
    //Add some line breaks.
    addEmptyLines(3);

    //Add the explanation
    m_formatted_receipt.push_back(std::string(std::string("Item") + "     " + std::string("Qty") + "  " 
                                            + std::string("Price")+ "  " + std::string("Total")));    

    for (int i = 0; i < m_receipt.items.size(); ++i) 
    {
        addItemLine(m_receipt.items[i], m_receipt.quantity[i], m_receipt.item_price[i], m_receipt.line_sum[i]);    
    }

    addEmptyLines(3);

    addSum(m_receipt.receipt_sum);

    addEmptyLines(2);

    addReceiptId(m_receipt.receipt_id);
    
    addEmptyLines(5);

    return m_formatted_receipt;
}

ReceiptFormatter::ReceiptFormatter(ReceiptPrinterTask::ReceiptItems receipt)
{
    m_receipt = receipt;
}

ReceiptFormatter::~ReceiptFormatter()
{
}

