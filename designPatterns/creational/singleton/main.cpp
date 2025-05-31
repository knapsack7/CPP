#include<iostream>
#include<string>
#include<mutex>
#include<fstream> /*to read and write to the files*/

/*
Always remember:
An object is constructed in this order:
1) its virtual base gets constructed,
2) then its base,
3) then its members,
4) then the constructor body runs.
*/

class Logger{
private:
	std::ofstream logFile; /*to write data in files*/
	inline static Logger* instance = nullptr; /*used inline to intialise static var in the class itself*/
	inline static std::mutex mutex;

	// Private constructor to prevent instantiation
    Logger() {
        logFile.open("log.txt", std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Failed to open log file." << std::endl;
        }
    }

	//Deleting copy constructor, move constructor and assignment operator to prevent copying
	Logger(const Logger&) = delete; // copy constructor
	Logger& operator=(const Logger&) = delete; // assignment operator
	Logger(const Logger&&) = delete; // Move Constructor

public:
	//static method to get the singleton instance
	static Logger& getInstance() {
		std::lock_guard<std::mutex> lock(mutex);
		if(!instance)
			instance = new Logger();
		return *instance;
	}
	//Method to log messages
	void log(const std::string& msg){
		std::lock_guard<std::mutex> lock(mutex);
		if (logFile.is_open()){
			logFile << msg << std::endl;
		}	
	}
	// Destructor
	~Logger(){
		if(logFile.is_open()){
			logFile.close();
		}
	}
};


// Example usage
int main() {
    Logger& logger = Logger::getInstance();
    logger.log("This is the first log message.");
    logger.log("Singleton pattern ensures a single instance of the logger.");

    // Trying to get another instance (will return the same instance)
    Logger& anotherLogger = Logger::getInstance();
    anotherLogger.log("Another log message from the same instance.");

    std::cout << "Check the log.txt file for the logged messages." << std::endl;
    return 0;
}

/*
Key points:
1. Made the constructor private to prevent instantiation
2. Made an function static to get the instance of the class
3. Made an static data member to store the instance of the class
4. Note only static data members are initialized when the class is loaded, not when an object is created
5. Static member function can use only static data members
6. static data members are initialized before the constructor is called
7. Statid data members need to be initialized outside the class (if not using inline keyword).
8. Need to add check in the getInstance function to avoid multiple instances of the class
*/