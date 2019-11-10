#include "ExeInfo.h"

template <class T>
ExeInfo::ExeInfo(const string& path)
{
	static_assert(!(is_same<T, Info::Architecture::x32>::value || is_same<T, Info::Architecture::x32>::value),
		"Tempalte must be Info::Architecture type!");

	file.open(path, ios::binary);
	if (!file.is_open())
	{
		throw runtime_error("File can not be opened.");
	}

	IMAGE_DOS_HEADER dosHeader = {0};
	file.read(reinterpret_cast<char*>(&dosHeader), sizeof(IMAGE_DOS_HEADER));

	if (dosHeader.e_magic != IMAGE_DOS_SIGNATURE)
	{
		throw runtime_error("The file has not MZ signature.");
	}

	file.seekg(dosHeader.e_lfanew, ios_base::cur);

	T ntHeader = {0};
	file.read(reinterpret_cast<char*>(&ntHeader), sizeof(T));

	if (ntHeader.Signature != IMAGE_NT_SIGNATURE)
	{
		throw runtime_error("The file has not NT signature.")
	}

	fileData.numberOfSections = ntHeader.FileHeader.NumberOfSections;

	if constexpr (is_same<T, Info::Architecture::x32>::value)
	{

	}
	else if constexpr (is_same<T, Info::Architecture::x32>::value)
	{

	}
	
	
}

ExeInfo::~ExeInfo()
{
	file.close();
}

void ExeInfo::FileData::init(IMAGE_FILE_HEADER& header)
{
	numberOfSections = header.NumberOfSections;
	timeOfCreating = header.TimeDateStamp;
	characteristic = header.Characteristics;
	switch (header.Machine)
	{
	case IMAGE_FILE_MACHINE_I386:
		machineName = "x86";
		break;
	case IMAGE_FILE_MACHINE_IA64:
		machineName = "Intel Itanium";
		break;
	case IMAGE_FILE_MACHINE_AMD64:
		machineName = "x64";
		break;
	}

	symbolTable.init(header.PointerToSymbolTable, header.NumberOfSymbols);
}

void ExeInfo::FileData::SymbolTable::init(unsigned long where, unsigned long size)
{
	this->where = where;
	this->size = size;
}
