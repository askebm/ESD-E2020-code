#ifndef RECEIPTPRINTERDRIVER_H
#define RECEIPTPRINTERDRIVER_H

#include <string>
#include <fstream>
#include <libusb-1.0/libusb.h>
#include <sys/types.h>
#include <chrono>

using namespace std::chrono_literals;

#define LF  (unsigned char*)0xA
#define ESC (unsigned char*)0x1B
#define AT  (unsigned char*)0x40
#define DLE (unsigned char*)0x10
#define EOT (unsigned char*)0x04
#define N   (unsigned char*)4

class ReceiptPrinterDriver
{
private:
    libusb_device_handle *m_dev_handle;
	libusb_context *m_ctx = NULL;
    u_int16_t m_vendor_id;
    u_int16_t m_product_id;
    
    void send(unsigned char* data, int length_of_data);
    void sendCommand(unsigned char* command);
    char read();

public:
    ReceiptPrinterDriver();
    ~ReceiptPrinterDriver();

    void configure(u_int16_t vendor_id, u_int16_t product_id);
    void lineFeed(int num_line_feeds);
    void printLine(std::string text);
    void initialize();
    void disable();
    bool getPaperStatus();
};

#endif /* RECEIPTPRINTERDRIVER_H */
