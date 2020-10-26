#include <ESD/driver/GPIO.hpp>
#include <fstream>



int GPIO::writeToFile(const std::string& file,const std::string& data) {
	std::ofstream f;
	f.open(file);
	for (const char& i : data) {
		f << i;
	}
	auto result = f.rdstate();
	f.close();
	return result;
}

int GPIO::readFromFile(const std::string& file, std::string& data) {
	std::ifstream f(file);
	data.clear();
	char c;
	while (f.get(c)) {
		if (c != '\n') {
			data += c;
		}
	}
	auto result = f.rdstate();
	f.close();
	return result;
}

int GPIO::exportPin(){
	static const std::string file = "/sys/class/gpio/export";
	if (hasValidPin()) {
		writeToFile(file,pin_number);
		return 1;
	}
	return 0;
}

int GPIO::unexportPin(){
	static const std::string file = "/sys/class/gpio/unexport";
	writeToFile(file,pin_number);
	return 0;
}

GPIO::GPIO(){
}

GPIO::GPIO(const std::string& pin) : pin_number(pin){
	exportPin();
}

GPIO::~GPIO() {
	unexportPin();
}

int GPIO::setPinNumber(const int& pin){
	if (hasValidPin()) {
		unexportPin();
	}
	pin_number = marshallPin(pin);
	return 0;
}

int GPIO::setPinDirection(const std::string& dir){
	std::string file = "/sys/class/gpio/gpio";
	file += pin_number;
	file += "/direction";
	return writeToFile(file,dir);
}

int GPIO::setPinValue(const std::string& val){
	std::string file = "/sys/class/gpio/gpio";
	file += pin_number;
	file += "/value";
	return writeToFile(file,val);
}

int GPIO::getPinValue(std::string& val){
	std::string file = "/sys/class/gpio/gpio";
	file += pin_number;
	file += "/value";
	return readFromFile(file,val);
}

void GPIO::set(void){
	setPinValue("1");
}

void GPIO::clear(void){
	setPinValue("0");
}

std::string GPIO::marshallPin(const int& in){
	return std::to_string(in);
}

bool GPIO::isInitialised(){
	auto result = hasValidPin();
	if (result) {
		std::string tmp;
		result = bool(getPinValue(tmp));
	}
	return result;
}

bool GPIO::hasValidPin() {
	bool result;
	if (pin_number.size()) {
		result = true;
		for (const auto& c : pin_number) {
			result &= ( ( '0' <= c ) && ( c <= '9' ) );
		}
	} else {
		result = false;
	}
	return result;
}
