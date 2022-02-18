#pragma once
#include "Framework.h"
#include <guiddef.h>
#include <sstream>
#include <iomanip>

class GUIDGenerator final
{
public:
	static const std::string GeneratorToString()
	{
		GUID guid;  // ��ĥ Ȯ�� 0�� ����
		auto hr = CoCreateGuid(&guid);
		if (SUCCEEDED(hr))
		{
			// hex is 4 bit, 4 bytes = 8*4 bits, therefore 8 char is required.
			std::stringstream sstream;
			sstream << std::hex << std::uppercase
				<< std::setw(8) << std::setfill('0') << guid.Data1 << "-"
				<< std::setw(4) << std::setfill('0') << guid.Data2 << "-"
				<< std::setw(4) << std::setfill('0') << guid.Data3 << "-"
				<< std::setw(2) << std::setfill('0') << static_cast<int>(guid.Data4[0])
				<< std::setw(2) << std::setfill('0') << static_cast<int>(guid.Data4[1])
				<< std::setw(2) << std::setfill('0') << static_cast<int>(guid.Data4[2])
				<< std::setw(2) << std::setfill('0') << static_cast<int>(guid.Data4[3])
				<< std::setw(2) << std::setfill('0') << static_cast<int>(guid.Data4[4])
				<< std::setw(2) << std::setfill('0') << static_cast<int>(guid.Data4[5])
				<< std::setw(2) << std::setfill('0') << static_cast<int>(guid.Data4[6])
				<< std::setw(2) << std::setfill('0') << static_cast<int>(guid.Data4[7]);
			return sstream.str();
		}
		
		return "N\A";
	}

	static const uint Generate()
	{   
		// GUID �� string ���� �ٲ۰� �ؽ�ȭ��. ũ�Ⱑ �پ��°� ���ϵ�.
		std::hash<std::string> hasher;
		return static_cast<uint>(hasher(GeneratorToString()));
	}
};