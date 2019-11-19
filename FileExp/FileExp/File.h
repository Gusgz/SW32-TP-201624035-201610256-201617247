#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <string>
#include <experimental/filesystem>
#include <time.h> 
#include <sstream>
using namespace std;
using namespace std::experimental::filesystem;
typedef unsigned long ulong;
class File {
private:
	string name;
	string extension;
	ulong size;
	string date;
public:
	File(path file) { 
		if (!(file.stem().string() == ""))
			this->name = file.stem().string();
		else
			this->name = "###";

		//if (is_regular_file(file)) {
		//	this->extension = file.extension().string();
		//	this->size = file_size(file);
		//}
		//else
		//{
		//	if (is_directory(file)) {
		//		this->extension = ".dir";
		//		this->size = 0;
		//	}
		//}

		if (!is_directory(file)) {
			this->extension = file.extension().string();
			this->size = file_size(file);
		}
		else {
			this->extension = ".dir";
			this->size = 0;
		}

		auto a = last_write_time(file);
		time_t time = decltype(a)::clock::to_time_t(a);
		stringstream ss;
		ss << asctime(localtime(&time));
		this->date = ss.str();
	}
	~File() {}

	string	GetName() { return this->name; }
	string	GetExtension() { return this->extension; }
	ulong	GetSize() { return this->size; }
	string	GetDate() { return this->date; }

	void SetName(string name) { this->name = name; }
	void SetExtension(string extension) { this->extension = extension; }
	void SetSize(ulong size) { this->size = size; }
	void SetDate(string date) { this->date = date; }
};
