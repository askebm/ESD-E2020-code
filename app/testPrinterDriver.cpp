#include <ESD/driver/ReceiptPrinterDriver.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    ReceiptPrinterDriver printer;

    //VendorID: 1046  ProductID: 20497 For receipt printer
    printer.configure(1046, 20497);
    printer.initialize();

    printer.printLine("Et forsøg");
    printer.printLine("Endnu et forøg er dette");
    printer.lineFeed(5);
    printer.printLine("Og jeg prøver nu igen");

    std::cout << "Paper status: " << printer.getPaperStatus() << std::endl;

    
    return 0;
}

/*
int main() {
	libusb_device_handle *dev_handle; //a device handle
	libusb_context *ctx = NULL; //a libusb session
	int r; //for return values
	
    r = libusb_init(&ctx); //initialize the library for the session we just declared
	if(r < 0) {
		cout<<"Init Error "<<r<<endl; //there was an error
		return 1;
	}

    //VendorID: 1046  ProductID: 20497
    dev_handle = libusb_open_device_with_vid_pid(ctx, 4152, 6180); //these are vendorID and productID I found for my usb device
	if(dev_handle == NULL)		
        cout<<"Cannot open device"<<endl;
	else
		cout<<"Device Opened"<<endl;
	
    //---
    int actual; //used to find out how many bytes were written
	if(libusb_kernel_driver_active(dev_handle, 0) == 1) { //find out if kernel driver is attached
		cout<<"Kernel Driver Active"<<endl;
		if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
			cout<<"Kernel Driver Detached!"<<endl;
	}
	r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
	if(r < 0) {
		cout<<"Cannot Claim Interface"<<endl;
		return 1;
	}
	cout<<"Claimed Interface"<<endl;
    
    std::string text = std::string("Test2") + (char)0xA;
    unsigned char* string = (unsigned char*)(text.c_str());

//	r = libusb_bulk_transfer(dev_handle, (1 | LIBUSB_ENDPOINT_OUT), string, 6, &actual, 0); //my device's out endpoint was 2, found with trial- the device had 2 endpoints: 2 and 129
	if(r == 0 && actual == 1) //we wrote the 4 bytes successfully
		cout<<"Writing Successful!"<<endl;
	else
		cout<<"Write Error"<<endl;
	
	r = libusb_release_interface(dev_handle, 0); //release the claimed interface
	if(r!=0) {
		cout<<"Cannot Release Interface"<<endl;
		return 1;
	}
	cout<<"Released Interface"<<endl;

	libusb_close(dev_handle); //close the device we opened
	libusb_exit(ctx); //needs to be called to end the

	return 0;
}

*/


