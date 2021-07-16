import unittest
from helpers.physics_repository import PhysicsRepository

class PhysicsRepositoryTest(unittest.TestCase):
	def test_safe_copy(self):
		PhysicsRepository.safe_copy(1)
		PhysicsRepository.safe_copy((1, 3))
		PhysicsRepository.safe_copy('abc')
		PhysicsRepository.safe_copy({})
		dict1 = {}
		dict2 = PhysicsRepository.safe_copy({})
		dict2['x'] = 1
		self.assertFalse('x' in dict1, 'mutating dict2 should not affect dict1')

	def test_remove_key_from_device(self):
		pr = PhysicsRepository.get_instance()
		pr.sending_repo = {
			'devices': [
				{
					'device': {
						'name': 'lift1Motor'
					},
					'bladeAngleDegrees': 1
				}
			]
		}
		pr.remove_key_from_device('lift1Motor', 'bladeAngleDegrees')
		self.assertFalse('bladeAngleDegrees' in pr.sending_repo['devices'][0])

	def remove_key_from_device(self, device_name, key):
		for device in self.sending_repo['devices']:
			if device['device']['name'] == device_name and key in device:
				del device[key]	

	def test_physical_repository(self):
		to = {}
		PhysicsRepository.merge_dict({}, to)
		to = {
			'devices': [
				{
					'device': {
						'type': 'propeller-motor',
						'name': 'blade-1'
					},
					'bladeRotationSpeedDegreesPerSecond': 0,
				},
				{
					'device': {
						'type': 'propeller-motor',
						'name': 'blade-2'
					},
					'bladeRotationSpeedDegreesPerSecond': 0,
				}
			]
		}
		from_dict = {
			'devices': [
				{
					'device': {
						'type': 'propeller-motor',
						'name': 'blade-2'
					},
					'bladeRotationSpeedDegreesPerSecond': 2
				},
				{
					'device': {
						'type': 'propeller-motor',
						'name': 'blade-1'
					},
					'bladeRotationSpeedDegreesPerSecond': 1
				}
			]
		}
		PhysicsRepository.merge_dict(from_dict, to)
		self.assertEquals(to['devices'][0]['device']['name'], 'blade-1')
		self.assertEquals(to['devices'][1]['device']['name'], 'blade-2')
		self.assertEquals(to['devices'][0]['bladeRotationSpeedDegreesPerSecond'], 1)
		self.assertEquals(to['devices'][1]['bladeRotationSpeedDegreesPerSecond'], 2)

if __name__ == '__main__':
	unittest.main()