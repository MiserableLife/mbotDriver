#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <string>

#define KNRM "\x1B[0m"   
#define KRED "\x1B[31m"  
#define KGRN "\x1B[32m"  
#define KYEL "\x1B[33m"  
#define KBLU "\x1B[34m"  
#define KMAG "\x1B[35m"  
#define KCYN "\x1B[36m"  
#define KWHT "\x1B[37m"  
#define RESET "\033[0m"  
                         


class Logger
{
private:
	std::ofstream out;
public:
	Logger(std::string path);

	~Logger();

	template<typename T>
	Logger& operator<<(const T&);


};

#define MBOTDRV(color,...) \
	printf("%sMBOTDRV %s:%d ] ", color, __func__ , __LINE__); \
	printf(__VA_ARGS__) ;            \
	printf("%s", RESET);

			                                                                               
#define OLEAUT_METHOD(color)                                          \        
			  printf("%sOLEAUT %s::%s called", color, typeid(*this).name(), __func__); \   
				  printf("%s\n", RESET); \                                                     
					                                                                               
				                         


#endif
