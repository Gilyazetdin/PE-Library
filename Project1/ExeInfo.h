#pragma once

#include <string>
#include <fstream>
#include <exception>
#include <cassert>

#include <Windows.h>

using namespace std;


namespace Info
{
	namespace Architecture
	{
		using x86 = IMAGE_NT_HEADERS32;
		using x64 = IMAGE_NT_HEADERS64;
	}
}


class ExeInfo
{
private:
	ifstream file;

	
public:	
	template <class T>
	ExeInfo(const string& path);
	~ExeInfo();

	struct FileData
	{
		unsigned short numberOfSections;
		unsigned long timeOfCreating;
		string characteristic;
		string machineName;

		struct SymbolTable
		{
			unsigned long where;
			unsigned long size;

			void init(unsigned long where, unsigned long size);
		} symbolTable;

		struct OptionalTable
		{
			unsigned short size;
		} optonalTable;

		void init(IMAGE_FILE_HEADER& header);
	} fileData;


};

