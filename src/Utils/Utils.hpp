#ifndef UTILS_HPP
# define UTILS_HPP

#include "structs.hpp"

class Utils {
	private:
		Utils();
		Utils(const Utils& other);
		Utils& operator=(const Utils& other);
		~Utils();
	
	public:
	static void			ref_trim(std::string& str);
	static bool			has_char(const char *str, char c);
	static bool			has_char(const std::string& str, char c);
	static std::string	trim(const std::string& str);
};

#endif