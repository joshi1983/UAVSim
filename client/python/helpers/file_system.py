from config import client_config

def map_path(path):
	if 'fileSystem' not in client_config:
		return path
	if 'mappings' not in client_config['fileSystem']:
		return path
	if not isinstance(client_config['fileSystem']['mappings'], list):
		return path
	for mapping in client_config['fileSystem']['mappings']:
		path = path.replace(mapping['from'], mapping['to'])
	return path