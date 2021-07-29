import shutil
import os

destination_directory = 'release'

def copy_recursive(from_dir, to_dir):
	pass


def get_dir_path(path):
	if '/' in path:
		index = path.rfind('/')
		return path[:index]
	else:
		return path


# to_path is relative to destination root directory.
def copy_file(from_path, to_path):
	to_path = destination_directory + '/' + to_path
	if to_path[-1] == '/':
		index = from_path.rfind('/')
		filename = from_path[index + 1:]
		to_path = to_path + filename
	from_path = '../' + from_path

	to_parent = get_dir_path(to_path)
	if not os.path.exists(to_parent):
		os.makedirs(to_parent)
	shutil.copy(from_path, to_path)


def process_release():
	copy_paths = {
		'src/bin/Release/UAV Simulator.exe': 'bin/uavsim.exe',
		'src/bin/Debug/UAV Simulator.exe': 'bin/uavsim_debug.exe',
		'src/bin/Debug/glut32.dll': 'bin/'
	}
	for from_path, to_path in copy_paths.items():
		copy_file(from_path, to_path)
	dirs_to_completely_copy = [
		'data/htdocs',
		'data/templates',
		'client/python/data',
		'client/python/helpers',
		'client/python/unit_tests'
	]
	for dir_path in dirs_to_completely_copy:
		shutil.copytree('../' + dir_path, destination_directory + '/' + dir_path)
	paths_to_copy = [
		'client/python/FaBo9Axis_MPU9250.py',
		'client/python/all_tests.py',
		'client/python/machine.py',
		'client/python/picamera.py',
		'client/python/README.md',
		'README.md',
		'client/README.md',
		'data/README.md',
		'data/models/README.md',
		'data/models/grass-texture.jpg',
		'data/models/skybox_texture3.jpg',
		'data/models/water.jpg',
		'data/models/uav.wrl',
		'data/settings.default.json',
		'data/uav.default.json',
		'data/settings.json.example'
	]
	for path_to_copy in paths_to_copy:
		from_path = '../' + path_to_copy
		to_path = destination_directory + '/' + path_to_copy
		to_parent = get_dir_path(to_path)
		if not os.path.exists(to_parent):
			os.makedirs(to_parent)
		shutil.copy(from_path, to_path)


process_release()

