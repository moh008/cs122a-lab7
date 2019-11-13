import spidev
import time

def createSPI(device):
	# Create the SPI object
	spi = spidev.SpiDev()
	# Open the SPI object on bus 0 for the specified device(CE)
	spi.open(0, device)
	# Set the max speed to 1 MHz
	spi.max_speed_hz = 1000000
	# Set the mode to 0
	spi.mode = 0
	return spi

def WelfordsAlgorithm(newLightValue):
	global _numValues
	global _mean
	global _s
	_numValues = 0
	_mean = 0
	_s = 0

	_numValues += 1
	if _numValues == 1:
		_mean = newLightValue
		_s = 0
	else:
		_oldMean = _mean
		_mean = _oldMean + (newLightValue-_oldMean) / _numValues
		_s = _s + ((newLightValue-_oldMean) * (newLightValue-_mean))
	return _mean

if __name__ == '__main__':
	try:
		spi0 = createSPI(0)
		spi1 = createSPI(1)

		average = [0]

		while True:
			# Receive data from microcontroller 1
			#newLightValue = spi0.xfer([0x10])
			newLightValue = spi0.readbytes(1)
			# Calculate running average using Welford's algorithm
			average[0] = int(WelfordsAlgorithm(newLightValue[0]))

			# Send new average to microcontroller 2
			#spi1.writebytes([0x40])
			spi1.writebytes(average)
			# Delay for 1 second
			time.sleep(0.5)

			#Send cur light value to microcontroller 2
			#spi1.writebytes([0x20])
			#spi1.writebytes(newLightValue)
			print("average:")
			print(average)
			#print("Cur_value:")
			#print(newLightValue)
			#time.sleep(1)

	except KeyboardInterrupt:
		# Close all open SPI (spi.close())
		spi0.close()	#close first MicroCon
		spi1.close()	#close second MicroCon
		exit()
