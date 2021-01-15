#include <ESD/driver/ReceiptPrinterDriver.hpp>
#include <sys/types.h>
#include <iostream>

ReceiptPrinterDriver::ReceiptPrinterDriver()
{
}
ReceiptPrinterDriver::~ReceiptPrinterDriver()
{
    disable(); //Close all libusb connections, when destroying object.
}

void ReceiptPrinterDriver::configure(u_int16_t vendor_id, u_int16_t product_id)
{
    m_vendor_id = vendor_id;
    m_product_id = product_id;
}

void ReceiptPrinterDriver::initialize()
{
    libusb_init(&m_ctx);
    //VendorID: 1046  ProductID: 20497 For receipt printer
    m_dev_handle = libusb_open_device_with_vid_pid(m_ctx, m_vendor_id, m_product_id);

    if (m_dev_handle) {
        if(libusb_kernel_driver_active(m_dev_handle, 0) == 1) //find out if kernel driver is attached
        libusb_detach_kernel_driver(m_dev_handle, 0);
        
	    libusb_claim_interface(m_dev_handle, 0);

        //Set back to std settings
        sendCommand( ESC );
        sendCommand( AT );
    }
    else
    {
        std::cout << "Was unable to accuire USB interface for Printer." << std::endl;
    }
}


void ReceiptPrinterDriver::lineFeed(int num_line_feeds)
{
    for (int i = 0; i < num_line_feeds; ++i) {        
        sendCommand( LF ); //lineFeed
    }
}

void ReceiptPrinterDriver::printLine(std::string text)
{
    int length_of_text = text.size();
    unsigned char* string = (unsigned char*)(text.c_str());

    send(string, length_of_text);
}

void ReceiptPrinterDriver::send(unsigned char* data, int length_of_data)
{
    int actual;
    libusb_bulk_transfer(m_dev_handle, (1 | LIBUSB_ENDPOINT_OUT), data, length_of_data, &actual, 0); 
}

void ReceiptPrinterDriver::sendCommand(unsigned char* command)
{
    send(command, 1);
}

void ReceiptPrinterDriver::disable()
{
    libusb_release_interface(m_dev_handle, 0);

	libusb_close(m_dev_handle);
	libusb_exit(m_ctx);
}
