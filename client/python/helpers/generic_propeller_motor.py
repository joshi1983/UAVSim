from physics_repository import PhysicsRepository

class GenericPropellerMotor:
	def __init__(self, name):
		self.name = name
		self.physics_repo = PhysicsRepository.get_instance()

	def set_rotation_speed_rpm(self, new_blade_speed_rpm):
		self.physics_repo.merge_into_sending_repo({
			'devices': [
				{
					'device': {
						"name": self.name
					},
					'bladeAccelerationDegreesPerSecondPerSecond': 0,
					'bladeRotationSpeedDegreesPerSecond': new_blade_speed_rpm
				}
			]
		})
		self.physics_repo.remove_key_from_device(self.name, 'bladeAngleDegrees')

