class MPU9250:
	def __init__(self, i2c):
		self.whoami = i2c
		self.acceleration = 0
		self.gyro = 0
		self.magnetic = 0
		self.temperature = 15
