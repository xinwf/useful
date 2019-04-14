#!/usr/bin/env python
import os

path='/home/ismart/tmp/Mar/merge'

fileList = os.listdir(path)
fileListCopy = fileList
for item in fileList:
	if 'wechat_invoice' in item:
		fp_code = item.split('_')[3].split('-')[0]
		for it in fileListCopy:
			if it == item:
				continue
			else:
				if fp_code in it:
					print("rm %s" % it)
					os.system("rm %s" % it)
					fileListCopy.remove(it)
					# fileList.remove(it)
