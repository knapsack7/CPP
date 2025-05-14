#include<iostream>
#include<string>
#include<mutex>
#include<fstream> /*to read and write to the files*/

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
