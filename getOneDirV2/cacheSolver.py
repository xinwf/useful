import os

def ReadOrWrite(file_path, io = 'r', downloaded_list = [], current_file = ''):
    if not os.path.exists(file_path):
        os.system("touch %s" % file_path)
        return []
    elif io == 'r':
        f = open(file_path, 'r')
        lines = f.readlines()
        f.close()

        downloaded_list = []
        for line in lines:
            downloaded_list.append(line.replace('\n', ''))
        # print("downloaded list len after read: %d" % len(downloaded_list))
        return downloaded_list
    elif io == 'w':
        if len(current_file) != 0:
            f = open(file_path, 'a')
            f.write(current_file+'\n')
            f.close()
        else:
            if len(downloaded_list) != 0:
                f = open(file_path, 'w')
                for line in downloaded_list:
                    f.write('%s\n' % line)
                f.close()
            