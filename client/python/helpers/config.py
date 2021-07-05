import json
import os
from os.path import abspath
import sys

http_server_port = 8080
client_config = {}

def get_settings_file_path():
	return abspath('..\\..\\data\\settings.json')

def get_client_config_file_path():
	return abspath('data\\config.json')

def init_server_config():
	global http_server_port
	filename = get_settings_file_path()
	if not os.path.isfile(filename):
		print('file not found: ' + filename)
		return
	with open(filename) as f:
		data = json.load(f)
		if 'httpServer' in data and 'port' in data['httpServer']:
			http_server_port = data['httpServer']['port']

def init_client_config():
	global client_config
	filename = get_client_config_file_path()
	if not os.path.isfile(filename):
		print('file not found: ' + filename)
		return
	with open(filename) as f:
		client_config = json.load(f)

def init():
	init_server_config()
	init_client_config()

init()