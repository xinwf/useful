#!/usr/bin/env python 
import os
import re
import sys
import codecs

git_diff = 'git_diff'

def backup(dest_dir):
	if not os.path.exists(dest_dir):
		print("create %s" % dest_dir)
		os.makedirs(dest_dir)
	current_dir = os.getcwd()
	f = codecs.open(dest_dir+'/backup_dir', 'w', encoding='utf-8')
	f.write(current_dir)
	f.close()
	f = codecs.open(git_diff, 'r', encoding='utf-8')
	lines = f.readlines()
	f.close()
	fn_re = re.compile('.*/')
	added = False
	for line in lines:
		if len(line.replace(" ", '').replace("\n", '')) == 0:
			continue
		elif 'modified' in line:
			file_path = line.split(":")[1].replace(" ", '').replace("\n", '')
			fn = fn_re.sub('', file_path)
			print('cp %s/%s %s/' % (current_dir, file_path, dest_dir))
			os.system('cp %s/%s %s/' % (current_dir, file_path, dest_dir))
		elif 'what will be committed' in line:
			# print("set added to True")
			added = True
		elif 'no changes added to commit' in line:
			# print("set added to False")
			added = False
			pass
		elif added:
			# print("backup added files ...")
			fp = line.replace(" ", '').replace("\n", '')
			# print(fp)
			if os.path.exists(fp):
				print('cp %s/%s %s/' % (current_dir, fp, dest_dir))
				os.system('cp %s/%s %s/' % (current_dir, fp, dest_dir))
		else:
			pass
	os.system('cp %s %s/' % (git_diff, dest_dir))
	print("backup files successfully.")

def recovery(from_dir):
	if from_dir[-1] == '/':
		from_dir = from_dir[:-1]
	if os.path.exists(from_dir + '/backup_dir') and os.path.exists(from_dir + '/' + git_diff):
		f = codecs.open(from_dir + '/backup_dir', 'r', encoding='utf-8')
		lines = f.readlines()
		f.close()
		backup_dir = lines[0]
		f = codecs.open(from_dir + '/' + git_diff)
		lines = f.readlines()
		f.close()
		fn_re = re.compile('.*/')
		recovery_added = False
		recovery_modified = False
		for line in lines:
			if len(line.replace(" ", '').replace("\n", '')) == 0:
				continue
			elif 'modified' in line:
				fp = line.split(":")[1].replace(" ", '').replace("\n", '')
				fn = fn_re.sub('', fp)
				dst_fp = backup_dir + "/" + fp.replace(fn, '')
				print('cp %s %s' % (from_dir+"/"+fn, dst_fp))
				os.system('cp %s %s' % (from_dir+"/"+fn, dst_fp))
				recovery_modified = True
			elif 'what will be committed' in line and recovery_modified:
				recovery_added = True
			elif 'no changes added to commit' in line:
				recovery_added = False
				pass
			elif recovery_added:
				fp = line.replace(" ", '').replace("\n", '')
				fn = fn_re.sub('', fp)
				dst_fp = backup_dir + "/" + fp.replace(fn, '')
				print('cp %s %s' % (from_dir+"/"+fn, dst_fp))
				os.system('cp %s %s' % (from_dir+"/"+fn, dst_fp))
			else:
				pass
		print("recovery files successfully.")
		delete = raw_input("Delete tmp dir?(Y/y/N/n): ")
		if delete == 'Y' or delete == 'y':
			os.system('rm -rf %s' % from_dir)
	else:
		print("Open backup_dir/modified_list file failed from dir: %s" % from_dir)
		exit()

def main():
	usage = 'Usage:  ./script -b/r dest_dir/from_dir\n \
	-b: backup to dest_dir \n \
	-r  recovery from from_dir \n \
	Note: dest_dir should be consistent with from_dir in one time operation of backup and recovery \n \
input_file like this:\n \
	Changes not staged for commit: \n \
	  (use "git add <file>..." to update what will be committed) \n \
	  (use "git checkout -- <file>..." to discard changes in working directory) \n \
 \n \
		modified:   .gitignore \n \
		modified:   modules/perception/cuda_util/BUILD \n \
		modified:   modules/perception/cuda_util/block_uf.cu \n \
		modified:   modules/perception/cuda_util/region_output.cu \n \
		modified:   modules/perception/obstacle/camera/filter/object_camera_extended_kalman_filter.cc \n \
		modified:   modules/perception/obstacle/camera/filter/object_camera_extended_kalman_filter.h \n \
		modified:   modules/perception/obstacle/fusion/probabilistic_fusion/pbf_track.cc \n \
		modified:   modules/perception/traffic_light/projection/multi_camera_projection.cc \n \
 \n \
	Untracked files: \n \
	  (use "git add <file>..." to include in what will be committed) \n \
 \n \
		modules/perception/cuda_util/CMakeLists.txt \n \
 \n \
	no changes added to commit (use "git add" and/or "git commit -a")'
	if len(sys.argv) != 3:
		print(usage)
		exit()
	elif sys.argv[1] == '-r':
		print("Recovery modified files ...")
		recovery(sys.argv[2])
	elif sys.argv[1] == '-b':
		print("Backup modified files ...")
		backup(sys.argv[2])

if __name__ == '__main__':
	main()
