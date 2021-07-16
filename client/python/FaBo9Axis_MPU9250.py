import helpers.config as config
from helpers.physics_repository import PhysicsRepository
from random import *

"""
Some of the noise is being simulated with help from discussion at:
https://forum.micropython.org/viewtopic.php?t=8088&p=46007

and the specification document at:
https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf
"""
class MPU9250:
	def __init__(self):
		self.bias = {}
		self.noise = {}
		self.physics_repo = PhysicsRepository.get_instance()
		sensor_config = config.client_config.get('sensors', {}).get('MPU9250', {})
		for key in ['a', 'm', 'g']:
			self.bias[key] = {}
			self.noise[key] = {}
			for coordinate in ['x', 'y', 'z']:
				self.bias[key][coordinate] = sensor_config.get(key, {}).get('bias', {}).get(coordinate, 0)
				self.noise[key][coordinate] = sensor_config.get(key, {}).get('randomTranslation', {}).get(coordinate, 0)

	def _getVector(self, vector_key, exact_offsets):
		result = {}
		for key in ['x', 'y', 'z']:
			result[key] = exact_offsets[key] + self.bias['a'][key] + (random() * 2 - 1) * self.noise['a'][key]

		return result

	def readAccel(self):
		a = self.physics_repo.repo['acceleration'].copy()
		return self._getVector('a', a)

	def readGyro(self):
		return self._getVector('g', {'x': 0, 'y': 0, 'z': 0})

	def readMagnet(self):
		return self._getVector('m', {'x': 0, 'y': 0, 'z': 0})
