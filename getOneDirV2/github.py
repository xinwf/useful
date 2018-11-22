import urllib2, lxml.html, sys, os, commands

header = {'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.75 Safari/537.36'}
homepage = False
no_file_link_list = []

def getDirAndFileList(url):
    global homepage
    global no_file_link_list
    req = urllib2.Request(url=url, headers=header)
    dirList = []
    fileList = []
    try:
        html = urllib2.urlopen(req, timeout=120).read()
        doc  = lxml.html.fromstring(html)
        if len(doc.xpath('//div[@class="signup-prompt-bg rounded-1"]')):
            # print("homepage")
            homepage = True
        else:
            # print("Not homepage")
            homepage = False
        itemList = doc.xpath('//div[@class="file-wrap"]/table/tbody/tr[@class="js-navigation-item"] | \
            //include-fragment[@class="file-wrap"]/table/tbody/tr[@class="js-navigation-item"]')
        for row in itemList:
            if 'directory' in row.xpath('td[@class="icon"]/svg/@class')[0]:
                if 'This path' in row.xpath('td[@class="content"]/span/a/@title')[0]:
                    dirList.append( row.xpath('td[@class="content"]/span/a/span/text()')[0] +
                        row.xpath('td[@class="content"]/span/a/text()')[0] )
                else:
                    dirList.append(row.xpath('td[@class="content"]/span/a/@title')[0])
            else:
                fileList.append(row.xpath('td[@class="content"]/span/a/@title')[0])
        if len(fileList) == 0:
            # print("Please make sure that this link doesn't contain files: %s " % url)
            no_file_link_list.append(url)
            # f = open('%s.html'%url.split('/')[-1], 'w')
            # f.write(html)
            # f.close()
        return dirList, fileList
    except Exception, e:
        print("Exception has happened: "+e.message)

def downloadFile(dirPath, fileList, url):
    origin_work_dir = os.getcwd()
    # print("origin_work_dir: %s" % origin_work_dir)
    os.chdir(dirPath)
    prefix = 'https://raw.githubusercontent.com'
    for fileName in fileList:
        downloadUrl = prefix + url.split('//')[1].replace('tree/', '').replace('github.com','')+'/'+fileName
        print("Downlading %s" % dirPath+'/'+fileName)
        commands.getstatusoutput('wget %s' % downloadUrl)
    os.chdir(origin_work_dir)

def createDir(dirPath, dirList):
    origin_work_dir = os.getcwd()
    os.chdir(dirPath)
    for dirItem in dirList:
        os.makedirs(dirItem)
    os.chdir(origin_work_dir)

def recursive(curDir, url):
    # print(url)
    subDirList, fileList = getDirAndFileList(url)
    urlSubDirList = subDirList
    if len(fileList) != 0:
        downloadFile(curDir, fileList, url)
    if homepage:
        urlSubDirList = [ 'tree/master/'+subdir for subdir in subDirList]
    if len(subDirList) != 0:
        createDir(curDir, subDirList)
        for dirItem in urlSubDirList:
            recursive(curDir+'/'+dirItem.replace('tree/master/', ''), url+'/'+dirItem)

def getSubDir(url, path):
    if len(path) != 0:
        if os.path.exists(path):
            os.chdir(path)
        else:
            print("Path doesn't exist. Create it for you first.")
            os.mkdir(path)
            os.chdir(path)
    curDir = url.split('/')[-1]
    if os.path.exists(curDir):
        print("%s exists, please change to another directory." % ( os.getcwd()+ '/' + curDir))
        exit(0)
    else:
        os.mkdir(curDir, 0755)
        # subDirList = []
        # rootDir = os.getcwd() + "/" + curDir
        recursive(curDir, url)
        if len(no_file_link_list) != 0:
            print("\nThese following links don't contain files, please confirm:")
            for url in no_file_link_list:
                print(url)
