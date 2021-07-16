import requests
import config
import copy
import json
import time

class PhysicsRepository:
	def __init__(self, client_config):
		self.client_config = client_config
		self.repo = {}
		self.sending_repo = {}
		self.previous_t = time.time()
		self.session = requests.Session()
		self.refresh_cache()

	@staticmethod
	def get_instance():
		if not hasattr(PhysicsRepository, 'singleton'):
			PhysicsRepository.singleton = PhysicsRepository(config.client_config)
		return PhysicsRepository.singleton

	def refresh_cache(self):
		r = self.session.get(config.get_base_url() + 'api/physics', headers={'Cache-Control': 'no-cache'})
		assert r.status_code == 200
		self.repo = r.json()
		self.sending_repo = copy.deepcopy(self.repo)

		if 'devices' not in self.sending_repo:
			print('Something went wrong.  Maybe the UAVSim HTTP Server is not behaving correctly.')
			return

		# remove unimportant device information.
		for device in self.sending_repo['devices']:
			device_to_clean = device['device']
			keys = [key for key in device_to_clean]
			for key in keys:
				if key != 'name':
					del device_to_clean[key]

	def send_time_change(self, delta_t):
		data = json.dumps({
			'seconds': delta_t
		})
		self.session.post(config.get_base_url() + 'api/physics/time', data=data)

	def send_changes_to_server(self):
		data = json.dumps(self.sending_repo)
		#print('sending_repo is: ' + data)
		r = self.session.post(config.get_base_url() + 'api/physics', data=data)
		assert r.status_code == 200
		read_rate = self.client_config.get('communication', {}).get('readRate', 'ON_SEND')
		update_time_rate = self.client_config.get('communication', {}).get('updateTime', 'ON_SEND')
		if read_rate == 'ON_SEND':
			self.refresh_cache()
		if update_time_rate == 'ON_SEND':
			new_t = time.time()
			delta_t = new_t - self.previous_t
			self.previous_t = new_t
			self.send_time_change(delta_t)

	# Matches devices by name
	@staticmethod
	def merge_devices(from_val, to_val):
		for device in from_val:
			if 'device' in device and 'name' in device['device']:
				name = device['device']['name']
				to_device_matches = [d for d in to_val if 'device' in d and 'name' in d['device'] and d['device']['name'] == name]
				if len(to_device_matches) == 1:
					PhysicsRepository.merge_dict(device, to_device_matches[0])

	@staticmethod
	def safe_copy(from_val):
		if isinstance(from_val, (int, long, float, tuple, str)):
			return from_val
		else:
			return copy.deepcopy(from_val)

	@staticmethod
	def merge_dict(from_val, to_val):
		if isinstance(to_val, dict) and isinstance(from_val, dict):
			for key in from_val:
				if isinstance(from_val[key], (str, int, long, float)) or key not in to_val:
					to_val[key] = PhysicsRepository.safe_copy(from_val[key])
				elif key == 'devices' and 'devices' in to_val:
					PhysicsRepository.merge_devices(from_val[key], to_val[key])
				else:
					PhysicsRepository.merge_dict(from_val[key], to_val[key])
		else:
			print('merge_dict called but one of the parameters was not a dict.')

	def remove_key_from_device(self, device_name, key):
		for device in self.sending_repo['devices']:
			if device['device']['name'] == device_name and key in device:
				del device[key]

	def merge_into_sending_repo(self, updates):
		PhysicsRepository.merge_dict(updates, self.sending_repo)
		send_rate = self.client_config.get('communication', {}).get('sendRate', 'ON_MERGE')
		if send_rate == 'ON_MERGE':
			self.send_changes_to_server()