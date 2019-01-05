#!/usr/bin/env python 
import os
import re
import sys
import codecs

def backup(dest_dir):
	if not os.path.exists(dest_dir):
		print("create %s" % dest_dir)
		os.makedirs(dest_dir)
	current_dir = os.getcwd()
	f = codecs.open(dest_dir+'/backup_dir', 'w', encoding='utf-8')
	f.write(current_dir)
	f.close()
	f = codecs.open('modified_list', 'r', encoding='utf-8')
	lines = f.readlines()
	f.close()
	fn_re = re.compile('.*/')
	for line in lines:
		if 'modified' in line:
			file_path = line.split(":")[1].replace(" ", '').replace("\n", '')
			fn = fn_re.sub('', file_path)
			print('cp %s/%s %s/' % (current_dir, file_path, dest_dir))
			os.system('cp %s/%s %s/' % (current_dir, file_path, dest_dir))
	os.system('cp %s %s/modified_list' % ('modified_list', dest_dir))
	print("backup files successfully.")

def recovery(from_dir):
	if from_dir[-1] == '/':
		from_dir = from_dir[:-1]
	if os.path.exists(from_dir + '/backup_dir') and os.path.exists(from_dir + '/modified_list'):
		f = codecs.open(from_dir + '/backup_dir', 'r', encoding='utf-8')
		lines = f.readlines()
		f.close()
		backup_dir = lines[0]
		f = codecs.open(from_dir + '/modified_list')
		lines = f.readlines()
		f.close()
		fn_re = re.compile('.*/')
		for line in lines:
			if 'modified' in line:
				fp = line.split(":")[1].replace(" ", '').replace("\n", '')
				fn = fn_re.sub('', fp)
				dst_fp = backup_dir + "/" + fp.replace(fn, '')
				print('cp %s %s' % (from_dir+"/"+fn, dst_fp))
				os.system('cp %s %s' % (from_dir+"/"+fn, dst_fp))
		print("recovery files successfully.")
		delete = raw_input("Delete tmp dir?(Y/y/N/n): ")
		if delete == 'Y' or delete == 'y':
			os.system('rm -rf %s' % from_dir)
	else:
		print("Open backup_dir/modified_list file failed from dir: %s" % from_dir)
		exit()

def main():
	usage = "Usage:  ./script -b/r dest_dir/from_dir\n \
input_file like this:\n \
	modified:   modules/dreamview/proto/hmi_config.proto\n \
	modified:   modules/dreamview/proto/hmi_status.proto\n \
	modified:   modules/dreamview/proto/simulation_world.proto\n \
	deleted:    modules/dreamview/proto/voice_detection.proto\n \
	modified:   modules/localization/BUILD\n \
	modified:   modules/localization/localization.cc\n \
	deleted:    modules/localization/msf/BUILD\n \
	modified:   modules/localization/msf/params/velodyne_params/velodyne16_novatel_extrinsics_example.yaml\n \
	modified:   modules/monitor/software/process_monitor.cc\n \
	modified:   modules/perception/conf/perception_lowcost.conf\n \
	modified:   modules/planning/proto/decision.proto"
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

