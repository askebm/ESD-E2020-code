#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

class USBDriver
{
public:
char getDatafromUSB();
int openDevice(std::string path);
~USBDriver(){close(fd);}

private:
const char *data_path;
struct input_event ev;
int shift_bool = 0;
int fd;

char getCharFromKeycode(int keycode);
char getShiftedCharFromKeycode(int keycode);
};

