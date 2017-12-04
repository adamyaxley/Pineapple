import os
import errno
import subprocess

def getFiles(dir = ".", exts = ""):
	files = []
	
	for dirname, dirnames, filenames in os.walk(dir):
		for filename in filenames:
			for ext in exts.split(";"):
				if filename.endswith(ext):
					files.append(os.path.join(dirname, filename))
					break
	
	return files

def getRoot():
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
    
def mkdir(dir):
    try:
        os.makedirs(dir)
    except OSError as e:
        if e.errno != errno.EEXIST:
            raise

def callBlockingWithOutput(command):
    with subprocess.Popen(command, stdout=subprocess.PIPE, bufsize=1, universal_newlines=True) as p:
        for line in p.stdout:
            print(line, end='')