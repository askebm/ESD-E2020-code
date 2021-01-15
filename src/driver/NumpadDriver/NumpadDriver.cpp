#include <driver/NumpadDriver/NumpadDriver.hpp>
#include <iostream>
#include <string>
#include <unistd.h>

NumpadDriver::NumpadDriver()
{
    // GPIO pin numbers 992  - 999
	//
    // cols
    int pin_it = 995;
    for (size_t i = 0; i < 4; i++)
    {
        this->cols[i] = new GPIO( std::to_string( pin_it ) );
        pin_it--;
    }

    pin_it = 999;
    for (size_t i = 0; i < 4; i++)
    {
        this->rows[i] = new GPIO( std::to_string( pin_it ) );
        pin_it--;
    }
}

NumpadDriver::~NumpadDriver() { }

bool NumpadDriver::init()
{
    for (size_t i = 0; i < 4; i++)
    {
        this->cols[i]->exportPin();
        this->rows[i]->exportPin();
    }
    return true;
}

int NumpadDriver::check()
{	
    int press_row = -1;
    int press_col = -1;
    // Phase 1: read(rows), write(cols) ////////////////////////

    for (size_t i = 0; i < 4; i++)
    {
        this->cols[i]->setPinDirection("out");
        this->cols[i]->setPinValue("0");    
        this->rows[i]->setPinDirection("in");
    }

    std::string row_val; 
    for (size_t i = 0; i < 4; i++)
    {
        this->rows[i]->getPinValue(row_val);
        // The activated row has been found.
        if (row_val == "0")
        {
            press_row = i;
            break;
        }
    }
    
    // Phase 2: read(cols), write(rows) ////////////////////////
    for (size_t i = 0; i < 4; i++)
    {
        this->rows[i]->setPinDirection("out");
        this->rows[i]->setPinValue("1");    
        this->cols[i]->setPinDirection("in");
    }
    
    std::string col_val;
    for (size_t i = 0; i < 4; i++)
    {
        this->cols[i]->getPinValue(col_val);
        // The activated row has been found.
        if (col_val == "1")
        {
            press_col = i;
            break;
        }
    }

    // When no button is pressed, return N.
    if(press_row < 0 or press_col < 0)
        return '\0';
	
	// sleep for 50ms
	usleep(50000);
    return (this->matrix_layout[press_row][press_col]);
}

int NumpadDriver::getValue()
{
	char matrixInput = check();
	char prev_matrixInput;
	// A change has happend.
	if (matrixInput != prev_matrixInput) 
	{
		prev_matrixInput = matrixInput;
		return matrixInput;
	}
	
	return NULL;
	
}



