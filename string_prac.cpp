#include <iostream>
using namespace std;

class String {
public:
	String();
	String(const char* str);
	~String();

	String(const String& str);

	String operator+(const String& str) const;
	bool operator==(const String& str) const;
	char& operator[](int n) const;
	size_t size() const;
	const char* c_str() const;

	String& operator=(const String& str);
	String& operator+=(const String& str);

	friend istream& operator>>(istream& is, String& str);
	friend ostream& operator<<(ostream& os, String& str);

private:
	char *data;
	size_t length;
};

String::String():length(0), data(NULL) {}

String::String(const char* str) {
	if (str == NULL) {
		length = 0;
		data = new char[1];
		*data = '\0';
	} else {
		length = strlen(str);
		data = new char[length+1];
		strcpy(data, str);
	}
}

String::~String() {
	delete []data;
	length = 0;
}

String::String(const String& str) {
	length = str.size();
	data = new char[length+1];
	strcpy(data, str.c_str());
}

String String::operator+(const String& str) const {
	String temp;
	temp.length = length+str.size();
	temp.data = new char[temp.length+1];
	strcpy(temp.data, data);
	strcat(temp.data, str.data);
	return temp;
}

bool String::operator==(const String& str) const {
	if (str.size() != length)
		return false;

	return strcmp(data, str.data) ? false : true;
}

char& String::operator[](int n) const {
	if (n >= length)
		return *(data+length-1);

	return *(data+n);
}

size_t String::size() const {
	return length;
}

const char* String::c_str() const {
	return data;
}

String& String::operator=(const String& str) {
	if (this == &str)
		return *this;

	delete []data;
	length = str.length;
	data = new char[length+1];
	strcpy(data, str.c_str());
	return *this;
}

String& String::operator+=(const String& str) {
	length += str.length;
	char* temp = new char[length+1];
	strcpy(temp, data);
	strcat(temp, str.data);
	delete[] data;
	data = temp;
	return *this;
}


istream& operator>>(istream& is, String& str) {
	char temp[1000];
	is >> temp;
	str.length = strlen(temp);
	str.data = new char[str.length+1];
	strcpy(str.data, temp);
	return is;
}

ostream& operator<<(ostream& os, String& str) {
	os << str.data;
	return os;
}

