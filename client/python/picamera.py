import helpers.config as config
import helpers.file_system as file_system

class PiCamera:
	def __init__(self):
		self.rotation = 0
	def start_preview(self):
		pass
	def capture(self, filename):
		filename = file_system.map_path(filename)
		
		pass
	def stop_preview(self):
		pass
	def close(self):
		pass
	