#!/usr/bin/env python
import subprocess
import os.path
import sys

lines = []

def	call_exiv2(fullpath,fn):
	global lines
	
	cmd = "exiv2 " + "-Pkv " + fullpath
	
	p = subprocess.Popen(cmd,shell=True,stdin=subprocess.PIPE,stdout=subprocess.PIPE)

	for i in p.stdout.read().split('\n'):
		lst = i.split()
		if len(lst) > 0:
			if lst[0] == "Exif.Photo.ExposureTime":
				line = []
				ss = lst[1].split('/')
				denom = float(ss[0])
				num = float(ss[1])
				line.append(fn)
				line.append(num / denom)
				lines.append(line)

if __name__ == "__main__":
	argvs = sys.argv
	argc = len(argvs)

	if (argc != 2):
		print "Usage python make_list [image folder]"
		quit()
		
	srcfolder = argvs[1]
	
	if (not os.path.exists(srcfolder)) :
		print srcfolder, " does not exists."
		quit()
		
	filelst = os.listdir(srcfolder)
	
	#print "file list=", filelst
	
	for fn in filelst:
		name = os.path.splitext(fn)
		base = name[0]
		ext = name[1]
		
		if (ext != ".tif"):
			continue
			
		srcfn = os.path.join(srcfolder,fn)
		call_exiv2(srcfn,fn)
		
	lines = sorted(lines,reverse=True,key=lambda x: x[1])
	for line in lines:
		print line[0]," ",line[1]
