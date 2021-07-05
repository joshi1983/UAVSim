class I2C:
	def __init__(self, scl, sda):
		self.scl = scl
		self.sda = sda

	def __hex__(self):
		return hex(self.scl) + hex(self.sda)

class Pin:
	def __init__(self, pin):
		self.pin = pin

	def __hex__(self):
		return hex(self.pin)
