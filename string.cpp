#include "string.h"


/************************************************

************************************************/


String::String()
{
	data = new char[1];
	data[0] = '\0';
}

String::String(const String &copy)
{
	int length = copy.length() + 1;
	data = new char[length];
	for(int i = 0; i < length; ++i)
		*(data+i) = *(copy.data+i);
}

String::String(const char &convert)
{
	data = new char[2];
	data[0] = convert;
	data[1] = '\0';
}

String::String(const char *convert)
{
	int count = 0;
	while(*(convert+count) != '\0') ++count;
	++count; // Increments last time for proper length
	data = new char[count];
	for(int i = 0; i < count; ++i)
		*(data+i) = *(convert+i);
}

/************************************************

************************************************/


String::String(const int &convert)
{
	data = convert_from_int(convert);
}

String::String(const double &convert)
{
	int places = 0;
	double checker = convert;
	while(checker != std::trunc(checker))
	{
		checker *= 10;
		++places;
	}
	data = convert_from_int( (convert * std::pow(10, places)) );
	insert(length()-places, '.');
}

String::String(const float &convert)
{
	int places = 0;
	float checker = convert;
	while(checker != std::trunc(checker))
	{
		checker *= 10;
		++places;
	}
	data = convert_from_int( (convert * std::pow(10, places)) );
	insert(length()-places, '.');
}

String::~String()
{
	if(data) delete [] data;
}



/************************************************

************************************************/


bool String::operator==(const String &comp) const
{
	return compare(this, comp) == 0;
}

bool String::operator==(const char *comp) const
{
	return compare(comp, this) == 0;
}

bool operator==(const char *self, const String &comp)
{
	return compare(self, comp) == 0;
}

bool String::operator!=(const String &comp) const
{
	return compare(this, comp) != 0;
}

bool String::operator!=(const char *comp) const
{
	return compare(comp, this) != 0;
}

bool operator!=(const char *self, const String &comp)
{
	return compare(self, comp) != 0;
}

bool String::operator<(const String &comp) const
{
	return compare(this, comp) < 0;
}

bool String::operator<(const char *comp) const
{
	return compare(comp, this) > 0;
}

bool operator<(const char *self, const String &comp)
{
	return compare(self, comp) < 0;
}

bool String::operator<=(const String &comp) const
{
	return compare(this, comp) <= 0;
}

bool String::operator<=(const char *comp) const
{
	return compare(comp, this) >= 0;
}

bool operator<=(const char *self, const String &comp)
{
	return compare(self, comp) <= 0;
}

bool String::operator>(const String &comp) const
{
	return compare(this, comp) > 0;
}

bool String::operator>(const char *comp) const
{
	return compare(comp, this) < 0;
}

bool operator>(const char *self, const String &comp)
{
	return compare(self, comp) > 0;
}

bool String::operator>=(const String &comp) const
{
	return compare(this, comp) >= 0;
}

bool String::operator>=(const char *comp) const
{
	return compare(comp, this) <= 0;
}

bool operator>=(const char *self, const String &comp)
{
	return compare(self, comp) >= 0;
}



/************************************************

************************************************/

String& String::operator=(const String &copy)
{
	if(!copy) return &this;
	delete [] data;
	int length = copy.length();
	data = new char[length + 1];
	for(int i = 0; i <+ length; ++i)
		*(data+i) = *(copy.data+i);
	
	return &this;
}

String& String::operator=(const char *copy)
{
	delete [] data;
	int length = 0;
	while(*(copy+length) != '\0') ++length;
	data = new char[length + 1];
	for(int i = 0; i <= length; ++i)
		*(data+i) = *(copy+i);

	return &this;
}

String& String::operator+=(const String &copy)
{
	int my_length = length();
	int their_length = copy.length();
	char *temp = new char[my_length + their_length + 1];
	char *placeholder = temp;
	for(int i = 0; i < my_length; ++i)
	{
		*(temp+i) = *(data+i);
		++placeholder;
	}
	for(int i = 0; i <= their_length; ++i)
		*(placeholder+i) = *(copy.data+i);
	delete [] data;
	data = temp;

	return &this;
}

String& String::operator+=(const char *copy)
{
	int my_length = length();
	int their_length = 0;
	while(*(copy+their_length) != '\0') ++their_length;
	char *temp = new char[my_length + their_length + 1];
	char *placeholder = temp;
	for(int i = 0; i < my_length; ++i)
	{
		*(temp+i) = *(data+i);
		++placeholder;
	}
	for(int i = 0; i <= their_length; ++i)
		*(placeholder+i) = *(copy+i);
	delete [] data;
	data = temp;

	return &this;
}

String& String::operator-=(const String &remove)
{
	if(!remove) return &this;
	int start = strstr(0, remove);
	if(start < 0) return &this;

	int rem_len = remove.length();
	int length = length();
	char *temp = new char[length - rem_len + 1];
	for(int i = 0; i != start; ++i)
		*(temp+i) = *(data+i);
	for(int i = start+rem_len; i <= length; ++i)
		*(temp+i) = *(data+i);
	delete [] data;
	data = temp;

	return &this;
}

String& String::operator-=(const char *remove)
{
	int start = strstr(0, remove);
	if(start < 0) return &this;

	int rem_len = 0;
	while(*(remove+rem_len) != '\0') ++rem_len;
	int length = length();
	char *temp = new char[length - rem_len + 1];
	for(int i = 0; i != start; ++i)
		*(temp+i) = *(data+i);
	for(int i = start+rem_len; i <= length; ++i)
		*(temp+i) = *(data+i);
	delete [] data;
	data = temp;

	return &this;
}



/************************************************

************************************************/

String String::operator+(const String &add)
{
	int my_len = length();
	int their_len = add.length();
	char *temp[my_len + their_len + 1];
	for(int i = 0; i < my_len; ++i)
		*(temp+i) = *(data+i);
	for(int i = 0; i <= their_len; ++i)
		*(temp+i) = *(add.data+i);
	
	return new String(temp);
}

String String::operator+(const char *add)
{
	int my_len = length();
	int their_len = 0;
	while(*(add+their_len) != '\0') ++their_len;
	char *temp[my_len + their_len + 1];

	for(int i = 0; i < my_len; ++i)
		*(temp+i) = *(data+i);
	for(int i = 0; i <= their_len; ++i)
		*(temp+i) = *(add+i);
	
	return temp;
}

String operator+(const char *add_this, const String &to_this)
{

}

String String::operator-(const String &subtract)
{
	int start = strstr(0, subtract);

	if(start < 0) return new String(data);

	int my_len = length();
	int their_len = subtract.length();
	int new_len = my_len = their_len;
	char *temp[my_len - their_len + 1];

	for(int i = 0; i != start; ++i)
		*(temp+i) = *(data+i);
	for(int i = start + their_len; i <= new_len; ++i)
		*(temp+(i-their_len) = *(data+i);

	return new String(temp);
}

String String::operator-(const char *subtract)
{
	int start = strstr(0, subtract);

	if(start < 0) return new String(data);

	int my_len = length();
	int their_len = 0;
	while(*(subtract+their_len) != '\0') ++their_len;
	int new_len = my_len = their_len;
	char *temp[my_len - their_len + 1];

	for(int i = 0; i != start; ++i)
		*(temp+i) = *(data+i);
	for(int i = start + their_len; i <= new_len; ++i)
		*(temp+(i-their_len) = *(data+i);

	return new String(temp);
}



/************************************************

************************************************/


char* String::operator[](const int index)
{
	int len = length();
	if(index < 0) index += len;
	if(index <= len && index > -1)
		return data + index;
	return 0;
}

/************************************************

************************************************/


String String::operator[](const String &pattern)
{
	String **temp = pattern.explode(':');
	int count = 0;
	while(*(temp+count)) ++count;
	if(count < 2 || count > 3) return 0; // min of 2, max of 3 args
	
	int begin;
	int end;
	int step = 1;
	try
	{
		begin = (*temp)->to_int();
	} catch(...){ begin = strstr(0, *(*temp)); }
	try
	{
		end = (*(temp+1))->to_int();
	} catch(...){ end = strstr(begin+1, *(*(temp+1))); }
	if(count == 3)
	{
		try
		{
			step = (*(temp+2))->to_int();
		} catch(...){}
	}
	if(begin == -1 || end == -1) return (String bad);

	int length = end - begin;
	char slice[length + 1];
	for(int i = 0; i < length; i += step)
		*(slice+i) = *(data+begin+i);

	return slice;
}


/************************************************

************************************************/


String** String::explode(const char &delineator)
{
	int count = 0;
	int index = 0;
	int length = length();
	for(int i = 0; i < length; ++i)
		if(*(data+i) == delineator) ++count;
	
	String *temp[count+2]();
	for(int i = 0; i <= count; ++i)
	{
		int end = strstr(index, delineator);
		if(end == -1) end = length;
		*(temp+i) = &operator[](String(index)+String(':')+(end-1));
		*( (*(temp+i)+(end-index)) ) = '\0';
		index = end + 1;
	}

	return temp;
}

/************************************************

************************************************/


int String::strstr(const int &start_at, const String &match) const
{
	if(!match) return -1;
	int len = length();
	int mlen = match.length();
	for(int i = start_at; i < len; ++i)
	{
		if((len-i) < mlen) return -1;
		if(*(data+i) == *(match.data))
		{
			bool found = true;
			for(int x = 0; x < mlen; ++x)
			{
				if(*(data+(i+x)) != *(match.data+x))
					found = false;
			}
			if(found) return i;
		}
	}

	return -1;
}


/************************************************

************************************************/

int String::strstr(const int &start_at, const char *match) const
{
	if(!match) return -1;
	int len = length();
	int mlen = 0;
	while(*(match+mlen) != '\0') ++mlen;

	for(int i = start_at; i < len; ++i)
	{
		if((len-i) < mlen) return -1;
		if(*(data+i) == *(match))
		{
			bool found = true;
			for(int x = 0; x < mlen; ++x)
			{
				if(*(data+(i+x)) != *(match+x))
					found = false;
			}
			if(found) return i;
		}
	}

	return -1;
}

int String::length()
{
	int count = 0;
	while(*(data+count) != '\0') ++count;
	return count;
}


/************************************************

************************************************/


bool String::insert(int index, String &to_inject)
{
	if(index > length() || !to_inject) return false;
	int other_len = to_inject.length();
	int total_length = length() + other_len;
	char *temp = new char[total_length + 1];
	for(int i = 0; i != index; ++i)
		*(temp+i) = *(data+i);
	for(int i = index; i < (index+other_len); ++i)
		*(temp+i) = *(to_inject.data+(i-index));
	for(int i = index+other_len; i < (total_length+1); ++i)
		*(temp+i) = *(data+(i-other_len));
	delete [] data;
	data = temp;
	return true;
}

/************************************************

************************************************/


int String::to_int()
{
	for(int i = 0; i < length(); ++i)
	{
		if((int)(*(data+i)) < 48 || (int)(*(data+i)) > 57)
			throw std::invalid_argument("string cannot be converted to int");
	}

	int total = 0;
	for(int i = (length() - 1); i >= 0; --i)
	{
		total += ( ((int)(*(data+i))) - 48 ) * std::pow(10, (length()-1-i));
	}

	return total;
}

/************************************************

************************************************/


double String::to_double()
{
	for(int i = 0; i < length(); ++i)
	{
		if((int)(*(data+i)) < 48 || (int)(*(data+i)) > 57)
		{
			if((int)(*(data+i)) != 46)
				throw std::invalid_argument("string cannot be converted to double");
		}
	}

	int index = strstr('.');
	if(index == -1) return (double)to_int();
	double total = 0.0;
	for(int i = index - 1; i >= 0; --i)
	{
		total += ( ((int)(*(data+i))) - 48 ) * std::pow(10, (index-1-i));
	}
	for(int i = index + 1; i < length(); ++i)
	{
		total += ( ((int)(*(data+i))) - 48 ) * std::pow(10, (1/(index-i)));
	}

	return total;
}



/************************************************

************************************************/


char* String::convert_from_int(int convert)
{
	int places = std::trunc(std::log10(convert));
	int running = convert;
	char *temp = new char[places + 1];
	for(int i = 0; i < places; ++i)
	{
		int mult = std::pow(10, places-(i+1));
		int sub = std::trunc(running/mult);
		*(temp+i) = (char)(48 + sub);
		running -= sub * mult;
	}
	*(temp+places) = '\0';

	return temp;
}

int String::compare(const String &comp_this, const String &to_this)
{
	int count = 0;
	int total = 0;
	char *comp1 = comp_this.data;
	char *comp2 = to_this.data;
	while(*(comp1+count) != '\0' && *(comp2+count) != '\0')
	{
		*(comp1+count) = to_case(1, (comp1+count));
		*(comp2+count) = to_case(1, (comp2+count));
		total += *(comp1+count) - *(comp2+count);
	}

	return total;
}

int String::compare(const char *comp_this, const String &to_this)
{
	int count = 0;
	int total = 0;
	while(*(comp_this+count) != '\0' && *(to_this+count) != '\0')
	{
		total += to_case(1, *(comp_this+count)) - to_case(1, *(to_this+count));
	}

	return total;
}

char* String::to_case(int which, char *convert)
{
	if(which == 1)
	{
		if(*convert < 97) *convert += 32;
	}
	else
	{
		if(*convert > 90) *convert -= 32;
	}

	return convert;
}
