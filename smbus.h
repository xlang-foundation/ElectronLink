#pragma once
#include "xpackage.h"
#include "xlang.h"

namespace X
{
	namespace ElectonLink
	{

		class SMBus
		{
			//if it is int, it will be "/dev/i2c-bus_id"
			//if it is string, it will be the whole string like "/dev/i2c-1"
			X::Value m_busName;
			bool m_isOpen = false;
			int fileDescriptor = -1;
		public:
			BEGIN_PACKAGE(SMBus)
				APISET().AddFunc<2>("read_byte", &SMBus::readByte);
				APISET().AddFunc<3>("write_byte", &SMBus::writeByte);
				APISET().AddFunc<3>("read_byte_data", &SMBus::readByteData);
				APISET().AddFunc<4>("write_byte_data", &SMBus::writeByteData);
				APISET().AddFunc<3>("read_word_data", &SMBus::readWordData);
				APISET().AddFunc<4>("write_word_data", &SMBus::writeWordData);
				APISET().AddFunc<3>("read_block_data", &SMBus::readBlockData_extern);
				APISET().AddFunc<4>("write_block_data", &SMBus::writeBlockData_extern);
				APISET().AddFunc<0>("open", &SMBus::openBus);
				APISET().AddFunc<0>("close", &SMBus::closeBus);
				APISET().AddFunc<0>("is_open", &SMBus::getIsOpen);
			END_PACKAGE

			SMBus(X::Value busName) : m_busName(busName) {}
			~SMBus();
			bool openBus();

			void closeBus();

			bool getIsOpen() const { return m_isOpen; }

			uint8_t readByte(int i2c_addr, bool force = false);

			void writeByte(int i2c_addr, uint8_t value, bool force = false);

			uint8_t readByteData(int i2c_addr, uint8_t reg, bool force = false);

			void writeByteData(int i2c_addr, uint8_t reg, uint8_t value, bool force = false);

			uint16_t readWordData(int i2c_addr, uint8_t reg, bool force = false);

			void writeWordData(int i2c_addr, uint8_t reg, uint16_t value, bool force = false);

			X::Value readBlockData_extern(int i2c_addr, uint8_t reg, bool force = false)
			{
				auto data = readBlockData(i2c_addr, reg, force);
				char* pData = new char[data.size()];
				memcpy(pData, data.data(), data.size());
				X::Bin bin(pData, data.size(),true);
				return bin;
			}
			std::vector<uint8_t> readBlockData(int i2c_addr, uint8_t reg, bool force = false);
			void writeBlockData_extern(int i2c_addr, uint8_t reg,
				X::Value& binData, bool force = false)
			{
				X::Bin bin(binData);
				std::vector<uint8_t> data(bin->Data(), bin->Data() + bin.Size());
				writeBlockData(i2c_addr, reg, data, force);
			}
			void writeBlockData(int i2c_addr, uint8_t reg,
				const std::vector<uint8_t>& data, bool force = false);
		};

	} // namespace ElectonLink
} // namespace X
