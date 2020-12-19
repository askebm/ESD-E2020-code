#include <USBDriver/USBDriver.hpp>

int USBDriver::openDevice(std::string path)
{

    std::cout << "TEST " << path<< std::endl;
    data_path = path.c_str();
 fd;

    fd = open(data_path, O_RDONLY);
    if(fd == -1)
    std::cout <<"ERROR: Cannot open "+ std::string(data_path) << std::endl;
//    assert(("Error: Cannot open "+ std::string(data_path),fd  == -1 ));
    return 1;
}

char USBDriver::getDatafromUSB()
{
    int dummy;
    //std::cout << data_path << "hello0" << std::endl;
    ssize_t temp = read(fd, &ev, sizeof ev);
    //std::cout << data_path << "hello0.5" << std::endl;
    if (temp == (ssize_t)-1)
    {
    //std::cout << std::string(data_path) << "hello1" << std::endl;
        if (errno == EINTR)
            return NULL;

        assert(("Error: Cannot get data from device: "+ std::string(data_path),errno != EINTR));

    }
    else if (temp != sizeof ev) {
    std::cout << std::string(data_path) << "hello2" << std::endl;
        errno = EIO;
        assert(("Error: Cannot get data from device: "+ std::string(data_path),temp != sizeof ev ));
    }
    if (ev.type == EV_KEY && ev.value >= 0)
    {
    //std::cout << std::string(data_path) << "hello3" << std::endl;

        if(shift_bool == 1 && ev.value == 0 && (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT))
        {
    //std::cout << std::string(data_path) << "hello4" << std::endl;
            shift_bool = 0;
            return NULL;
        }
        if(shift_bool == 0 && ev.value == 1 && (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT))
        {
    //std::cout << std::string(data_path) << "hello5" << std::endl;
            shift_bool = 1;
            return NULL;
        }

    if( ev.value == 1)
{
    //std::cout << std::string(data_path) << "hello6" << std::endl;
        return shift_bool ? getShiftedCharFromKeycode((int)ev.code) : getCharFromKeycode((int)ev.code);}

    }
    return NULL;
}

char USBDriver::getCharFromKeycode(int keycode){
    switch(keycode){

        case KEY_1:		return '1';
        case KEY_2:		return '2';
        case KEY_3:		return '3';
        case KEY_4:		return '4';
        case KEY_5:		return '5';
        case KEY_6:		return '6';
        case KEY_7:		return '7';
        case KEY_8:		return '8';
        case KEY_9:		return '9';
        case KEY_0:		return '0';
        case KEY_MINUS:		return '-';
        case KEY_EQUAL:		return '=';

        case KEY_Q:		return 'q';
        case KEY_W:		return 'w';
        case KEY_E:		return 'e';
        case KEY_R:		return 'r';
        case KEY_T:		return 't';
        case KEY_Y:		return 'y';
        case KEY_U:		return 'u';
        case KEY_I:		return 'i';
        case KEY_O:		return 'o';
        case KEY_P:		return 'p';
        case KEY_LEFTBRACE:	return '[';
        case KEY_RIGHTBRACE:	return ']';
        case KEY_ENTER:		return '\n';

        case KEY_A:		return 'a';
        case KEY_S:		return 's';
        case KEY_D:		return 'd';
        case KEY_F:		return 'f';
        case KEY_G:		return 'g';
        case KEY_H:		return 'h';
        case KEY_J:		return 'j';
        case KEY_K:		return 'k';
        case KEY_L:		return 'l';
        case KEY_SEMICOLON:	return ';';
        case KEY_APOSTROPHE:	return '\'';
        case KEY_GRAVE:		return '`';

        case KEY_BACKSLASH:	return '\\';
        case KEY_Z:		return 'z';
        case KEY_X:		return 'x';
        case KEY_C:		return 'c';
        case KEY_V:		return 'v';
        case KEY_B:		return 'b';
        case KEY_N:		return 'n';
        case KEY_M:		return 'm';
        case KEY_COMMA:		return ',';
        case KEY_DOT:		return '.';
        case KEY_SLASH:		return '/';

        case KEY_KPASTERISK:	return '*';

        case KEY_SPACE:		return ' ';

        case KEY_KP7:		return '7';
        case KEY_KP8:		return '8';
        case KEY_KP9:		return '9';
        case KEY_KPMINUS:	return '-';
        case KEY_KP4:		return '4';
        case KEY_KP5:		return '5';
        case KEY_KP6:		return '6';
        case KEY_KPPLUS:	return '+';
        case KEY_KP1:		return '1';
        case KEY_KP2:		return '2';
        case KEY_KP3:		return '3';
        case KEY_KP0:		return '0';
        case KEY_KPDOT:		return '.';

    }
}

char USBDriver::getShiftedCharFromKeycode(int keycode){

    switch(keycode){
        case KEY_1:		return '!';
        case KEY_2:		return '@';
        case KEY_3:		return '#';
        case KEY_4:		return '$';
        case KEY_5:		return '%';
        case KEY_6:		return '^';
        case KEY_7:		return '&';
        case KEY_8:		return '*';
        case KEY_9:		return '(';
        case KEY_0:		return ')';
        case KEY_MINUS:		return '_';
        case KEY_EQUAL:		return '+';

        case KEY_Q:		return 'Q';
        case KEY_W:		return 'W';
        case KEY_E:		return 'E';
        case KEY_R:		return 'R';
        case KEY_T:		return 'T';
        case KEY_Y:		return 'Y';
        case KEY_U:		return 'U';
        case KEY_I:		return 'I';
        case KEY_O:		return 'O';
        case KEY_P:		return 'P';
        case KEY_LEFTBRACE:	return '{';
        case KEY_RIGHTBRACE:	return '}';

        case KEY_A:		return 'A';
        case KEY_S:		return 'S';
        case KEY_D:		return 'D';
        case KEY_F:		return 'F';
        case KEY_G:		return 'G';
        case KEY_H:		return 'H';
        case KEY_J:		return 'J';
        case KEY_K:		return 'K';
        case KEY_L:		return 'L';
        case KEY_SEMICOLON:	return ':';
        case KEY_APOSTROPHE:	return '\"';
        case KEY_GRAVE:		return '~';

        case KEY_BACKSLASH:	return '|';
        case KEY_Z:		return 'Z';
        case KEY_X:		return 'X';
        case KEY_C:		return 'C';
        case KEY_V:		return 'V';
        case KEY_B:		return 'B';
        case KEY_N:		return 'N';
        case KEY_M:		return 'M';
        case KEY_COMMA:		return '<';
        case KEY_DOT:		return '>';
        case KEY_SLASH:		return '\?';

    }
}

