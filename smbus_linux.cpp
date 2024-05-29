#include "smbus.h"
#if !(WIN32)

#include <stdexcept>
#include <iostream>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

// Define the I2C commands if not already defined
#ifndef I2C_SLAVE
#define I2C_SLAVE 0x0703
#endif

namespace X
{
    namespace ElectonLink
    {
        static bool setSlaveAddress(int deviceAddress) {
            if (ioctl(fileDescriptor, I2C_SLAVE, deviceAddress) < 0) {
                perror("Failed to set slave address");
                return false;
            }
            return true;
        }

        SMBus::~SMBus() {
            if (m_isOpen) {
                closeBus();
            }
        }

        bool SMBus::openBus() {
            std::string busPath;
            if (m_busName.IsLong()) {
                busPath = "/dev/i2c-" + std::to_string((int)m_busName);
            }
            else {
                busPath = m_busName.toString();
            }

            fileDescriptor = open(busPath.c_str(), O_RDWR);
            if (fileDescriptor < 0) {
                perror("Failed to open the bus");
                return false;
            }

            m_isOpen = true;
            return true;
        }

        void SMBus::closeBus() {
            if (fileDescriptor >= 0) {
                close(fileDescriptor);
                fileDescriptor = -1;
            }
            m_isOpen = false;
        }
        uint8_t SMBus::readByte(int i2c_addr, bool force) {
            setSlaveAddress(i2c_addr);  // Assumes setSlaveAddress always succeeds, handle exceptions or errors as necessary
            uint8_t data = 0;
            if (read(fileDescriptor, &data, 1) != 1) {
                throw std::runtime_error("Failed to read byte");
            }
            return data;
        }

        void SMBus::writeByte(int i2c_addr, uint8_t value, bool force) {
            setSlaveAddress(i2c_addr);
            if (write(fileDescriptor, &value, 1) != 1) {
                throw std::runtime_error("Failed to write byte");
            }
        }

        uint8_t SMBus::readByteData(int i2c_addr, uint8_t reg, bool force) {
            setSlaveAddress(i2c_addr);

            // Write the register address we want to read from
            if (write(fileDescriptor, &reg, 1) != 1) {
                throw std::runtime_error("Failed to write register address");
            }

            // Read the data from the register
            uint8_t data;
            if (read(fileDescriptor, &data, 1) != 1) {
                throw std::runtime_error("Failed to read byte data");
            }

            return data;
        }

        void SMBus::writeByteData(int i2c_addr, uint8_t reg, uint8_t value, bool force) {
            setSlaveAddress(i2c_addr);

            // Write the register address followed by the data
            uint8_t buffer[2] = { reg, value };
            if (write(fileDescriptor, buffer, 2) != 2) {
                throw std::runtime_error("Failed to write byte data");
            }
        }

        uint16_t SMBus::readWordData(int i2c_addr, uint8_t reg, bool force) {
            setSlaveAddress(i2c_addr);

            // Write the register address we want to read from
            if (write(fileDescriptor, &reg, 1) != 1) {
                throw std::runtime_error("Failed to write register address");
            }

            // Read the data from the register
            uint16_t data;
            if (read(fileDescriptor, &data, 2) != 2) {
                throw std::runtime_error("Failed to read word data");
            }

            return data;
        }

        void SMBus::writeWordData(int i2c_addr, uint8_t reg, uint16_t value, bool force) {
            setSlaveAddress(i2c_addr);

            // Write the register address followed by the data
            uint8_t buffer[3] = { reg, static_cast<uint8_t>(value & 0xFF), static_cast<uint8_t>((value >> 8) & 0xFF) };
            if (write(fileDescriptor, buffer, 3) != 3) {
                throw std::runtime_error("Failed to write word data");
            }
        }

        std::vector<uint8_t> SMBus::readBlockData(int i2c_addr, uint8_t reg, bool force) {
            setSlaveAddress(i2c_addr);

            // Write the register address we want to read from
            if (write(fileDescriptor, &reg, 1) != 1) {
                throw std::runtime_error("Failed to write register address");
            }

            // Read the block of data
            std::vector<uint8_t> data(32); // Assuming max block size of 32 bytes
            int length = read(fileDescriptor, data.data(), data.size());
            if (length < 0) {
                throw std::runtime_error("Failed to read block data");
            }

            data.resize(length); // Adjust the vector size to actual data length
            return data;
        }

        void SMBus::writeBlockData(int i2c_addr, uint8_t reg, const std::vector<uint8_t>& data, bool force) {
            setSlaveAddress(i2c_addr);

            // Prepare the buffer to send
            std::vector<uint8_t> buffer(1 + data.size());
            buffer[0] = reg;
            std::copy(data.begin(), data.end(), buffer.begin() + 1);

            // Write the buffer
            if (write(fileDescriptor, buffer.data(), buffer.size()) != static_cast<ssize_t>(buffer.size())) {
                throw std::runtime_error("Failed to write block data");
            }
        }
    } // namespace ElectonLink
} // namespace X

#endif
