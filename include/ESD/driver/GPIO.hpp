#ifndef GPIO_H
#define GPIO_H
#include <string>

class GPIO
{
	private:
		std::string pin_number;

		//Helpers
		bool isInitialised();
		bool hasValidPin();
		int writeToFile(const std::string&, const std::string&);
		int readFromFile(const std::string&, std::string&);

	public:
		GPIO();
		GPIO(const std::string&);
		~GPIO();

		// initialise
		int exportPin();

		// disbale
		int unexportPin();

		// Mutaters
    int setPinNumber(const int&);
		int setPinDirection(const std::string&);
		int setPinValue(const std::string&);
		void set(void);
		void clear(void);

		// Accessers
		int getPinValue(std::string&);

	private:
		// TODO maybe a template?
		std::string marshallPin(const int&);
};

#endif /* GPIO_H */
