#pragma once
#include <string>

class llUtility
{
public:
	static std::string to_string(int value);
	static std::string to_string(double value,int accuracy = 4);
	static std::string to_string(const std::string& value);
};

