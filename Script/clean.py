import os
import re
import sys
import subprocess
from string import whitespace
import common

def addHeaders(dir, headerFile, start, end):
	with open(headerFile) as f:
		header = f.readlines()

	header.insert(0, start)
	header += ['\n', end, '\n']
	# Get all files
	files = common.getFiles(dir, ".h;.cpp;.inl")
	for file in files:
		with open(file, 'r+') as f:
			data = f.readlines()
			if data.count(end) > 0:
				i = data.index(end)
				del data[0:i + 1]
			
			# Add header
			data = header + data
			f.seek(0)
			f.writelines(data)
			f.truncate()
			print("\t" + file)

def indentPreprocessorDirectives(file):
	notDirective = whitespace + '#'
	indentation = 0
	with open(file, 'r+') as f:
		data = f.readlines()
		for index in range(0, len(data) - 1):
			line = data[index]
			stripped = line.lstrip()
			if stripped.startswith('#'):
				directive = stripped.lstrip(notDirective)
				oneTimeIndendataion = 0
				if directive.startswith('endif'):
					indentation -= 1
				if directive.startswith('elif') or directive.startswith('else'):
					oneTimeIndendataion = -1
				data[index] = '{}#{}'.format('\t' * (indentation + oneTimeIndendataion), directive)
				if directive.startswith('if'):
					indentation += 1
		f.seek(0)
		f.writelines(data)

def format(dir):
	files = common.getFiles(dir, ".h;.cpp;.inl")
	
	for file in files:
		subprocess.call(['clang-format', '-style=file', '-i', file])
		indentPreprocessorDirectives(file)
		print("\t", file)

def main():
	start = "/*------------------------------------------------------------------------------\n"
	end   = "------------------------------------------------------------------------------*/\n"
	headerFile = "Script/header.txt"
	print("Adding headers to Source")
	addHeaders("Source", headerFile, start, end)
	print("Style formatting all code")
	format("Source")
	format("Demo")
	format("Test")

if __name__ == "__main__":
	main()