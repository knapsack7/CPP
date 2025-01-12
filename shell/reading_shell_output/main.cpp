#include<stdio.h>
#include<iostream>
#include<string>

int main(){
	const char * command = "df -h";
	char buffer[128];
	std::string result;
	
	//open a pipe to run the command
	FILE* pipe = popen(command, "r");
	if(!pipe){
		std::cerr<<"Failed to run a command.\n";
		return 1;
	}
	// Read the command ouput
	while(fgets(buffer, sizeof(buffer), pipe) != nullptr){
		result += buffer;
	}

	pclose(pipe);

	std::cout<<"Command Output:\n"<< result<<std::endl;

	return 0;

}
