# Import the ElectronLink module
from ElectronLink import electronlink

# Create an SMBus instance for bus 1
sb = electronlink.smbus(1)

# Open the SMBus
sb.open()

# Write a byte to the device at address 0x20, register 0x00
sb.write_byte(0x20, 0x00)

# Write a byte of data to a register
sb.write_byte_data(0x20, 0x00, 0x12)

# Read a byte from the device at address 0x20, register 0x00
read_data = sb.read_byte(0x20)
print(f"Read byte: {read_data}")

# Read a byte of data from a register
read_byte_data = sb.read_byte_data(0x20, 0x00)
print(f"Read byte data: {read_byte_data}")

# Write a word of data to a register
sb.write_word_data(0x20, 0x01, 0x1234)

# Read a word of data from a register
read_word_data = sb.read_word_data(0x20, 0x01)
print(f"Read word data: {read_word_data}")

# Write a block of data to a register
block_data = [0x01, 0x02, 0x03, 0x04]
sb.write_block_data(0x20, 0x02, block_data)

# Read a block of data from a register
read_block_data = sb.read_block_data(0x20, 0x02)
print(f"Read block data: {read_block_data}")

# Close the SMBus
sb.close()
