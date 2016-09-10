#include <cmath>
#include <stdexcept>


#ifndef __STRING_
#define __STRING_


/*****************************************************************

     ------------ Kari's Most Excellent String Class ------------

		 Author: Karis Hutcheson
		 Version: 2.1
		 Date: 09-2016

		 Release Notes:
		 I set out making this class in the hopes of introducing an
		 optimized and fully-featured string class to C++. While current
		 libraries offer enough functionality to get by, my goal in this
		 project has been to offer a library worthy of a high-level programming
		 language (not just a converted C-style approach). Thus, I'm
		 including incorporated, advanced string manipulation through
		 splicing and array slices based of Python's current implementation
		 (Python 3.x). In keeping with optimization, I've kept from using
		 many external libraries except where necessary. I've extended
		 iostream and used cmath for advanced conversion but I've tried to
		 keep it minimal. Enjoy!!!

*****************************************************************/

class String
{
	public:
		// CONSTRUCTORS
		String();
		String(const String&);
		String(const char&);
		String(const char*);
		String(const int&);
		String(const double&);
		String(const float&);

		~String();

		// COMPARISON
		bool operator==(const String&) const;
		bool operator==(const char*) const;
		friend bool operator==(const char*, const String&);

		bool operator!=(const String&) const;
		bool operator!=(const char*) const;
		friend bool operator!=(const char*, const String&);

		bool operator<(const String&) const;
		bool operator<(const char*) const;
		friend bool operator<(const char*, const String&);

		bool operator<=(const String&) const;
		bool operator<=(const char*) const;
		friend bool operator<=(const char*, const String&);

		bool operator>(const String&) const;
		bool operator>(const char*) const;
		friend bool operator>(const char*, const String&);

		bool operator>=(const String&) const;
		bool operator>=(const char*) const;
		friend bool operator>=(const char*, const String&);

		// ASSIGNMENT
		String& operator=(const String&);
		String& operator=(const char*);
		String& operator+=(const String&);
		String& operator+=(const char*);
		String& operator-=(const String&);
		String& operator-=(const char*);

		// MANIPULATION OPERATIONS
		String operator+(const String&);
		String operator+(const char*);
		friend String operator+(const char*, String&);
		String operator-(const String&);
		String operator-(const char*);

		// ACCESSORS
		char* operator[](const int); // Return index
		String* operator[](const String&); // Return slices

		// PATTERN MATCHING & QUERIES
		String** explode(const char&); // Return string array
		int strstr(const int&, const String&) const;
		int strstr(const int&, const char*) const;
		int length() const;

		// MANIPULATION
		bool insert(int, String&);
		int to_int();
		double to_double();

	private:
		char *data;

		char* convert_from_int(int);
		int compare(const String&, const String&);
		int compare(const char*, const String&);
};


#endif
