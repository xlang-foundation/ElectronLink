#include "smbus.h"
#if (WIN32)
namespace X
{
	namespace ElectonLink
	{
		bool SMBus::setSlaveAddress(int deviceAddress) {
			return true;
		}
		SMBus::~SMBus() {
			if (m_isOpen) {
				closeBus();
			}
		}

		bool SMBus::openBus() {
			return true;
		}

		void SMBus::closeBus() {
		}
		uint8_t SMBus::readByte(int i2c_addr, bool force) {
			return 0;
		}

		void SMBus::writeByte(int i2c_addr, uint8_t value, bool force) {
		}

		uint8_t SMBus::readByteData(int i2c_addr, uint8_t register, bool force) {
			return 0;
		}

		void SMBus::writeByteData(int i2c_addr, uint8_t register, uint8_t value, bool force) {
		}

		uint16_t SMBus::readWordData(int i2c_addr, uint8_t register, bool force) {
			return 0;
		}

		void SMBus::writeWordData(int i2c_addr, uint8_t register, uint16_t value, bool force) {
		}

		std::vector<uint8_t> SMBus::readBlockData(int i2c_addr, uint8_t register, bool force) {
			return std::vector<uint8_t>();
		}

		void SMBus::writeBlockData(int i2c_addr, uint8_t register,
			const std::vector<uint8_t>& data, bool force) {
		}
	} // namespace ElectonLink
} // namespace X
#endif