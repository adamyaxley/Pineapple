import os

def getFiles(dir = ".", exts = ""):
	files = []
	
	for dirname, dirnames, filenames in os.walk(dir):
		for filename in filenames:
			for ext in exts.split(";"):
				if filename.endswith(ext):
					files.append(os.path.join(dirname, filename))
					break
	
	return files
