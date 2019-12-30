#!/bin/bash

# @Author: 文正•喵
# @E-Mail: ivlioioilvi@outlook.com

# @Modified by: Xin Wenfei
# @E-Mail: xinwf18@gmail.com
# @Note: Using crontab -e to set a timed task(This is a temporary method, it will lost after reboot, permanent method is
#          edit /etc/crontab)
# @Crontab usage description: https://blog.csdn.net/allenlinrui/article/details/7490206
# @New version(Using api with js): https://github.com/Cool-Pan/dotfiles/blob/master/files/power-pkg/profile/_bing

#
# 获取必应每日的主页图片作为壁纸
#

# 定义全局变量
#
# Bing 的网址
BING_URL="https://bing.com"
# 用于第一次粗略过滤时的关键字 (快速定位到图片链接所在行)
FIRST_FILTERING_RULE='<link id="bgLink" rel="preload"'
# 用于第二次精确过滤时的规则 (提取出未拼接的图片链接)
SECOND_FILTERING_RULE='BEGIN { FS = "\"|\"" } { print $6 }'

# 准备工作
preparation_Action() {
    # 判断存放壁纸的文件夹是否存在 (如果不存在就创建)
    if [ -d "$HOME/.config/Wallpaper" ]; then
        :
    else
        mkdir -p "$HOME/.config/Wallpaper/Backups"
    fi
}

# 开始执行 preparation_Action 函数
preparation_Action

# 提取文件名
get_File_Name() {
    # 获取传入的参数 1 (已拼接的图片链接)
    FULL_URL="$1"
    # 获取传入的参数 2 (未拼接的图片链接)
    HALF_URL="$2"

    # 获取当前日期
    TODAY=$(date +%Y%m%d)

    # 提取图片的名字
    FILE_NAME=$(echo -e "$HALF_URL" | cut -d "&" -f 1 | cut -d "_" -f 1 | cut -d "." -f 2)

    # 提取出图片的后缀
    TMP_FILE_TYPE=$(echo -e "$HALF_URL" | cut -d "&" -f 1 | cut -d "." -f 3)
    FILE_TYPE=".$TMP_FILE_TYPE"

    # 拼接图片最后的名字
    LAST_PIC_FILE_NAME=$TODAY"_"$FILE_NAME$FILE_TYPE
    
    # 下载主页图片到备份目录
    curl -sL "$FULL_URL" -o "$HOME/.config/Wallpaper/Backups/$LAST_PIC_FILE_NAME"

    # 复制壁纸到壁纸的存放目录
    cp -rf "$HOME/.config/Wallpaper/Backups/$LAST_PIC_FILE_NAME" "$HOME/.config/Wallpaper/Current$FILE_TYPE"
    # 通过 feh 设置壁纸
    # 你也可以注释掉下面这行，转而使用其它壁纸设置工具，如果你想的话
    # feh --randomize --no-fehbg --bg-scale ~/.config/Wallpaper/Current$FILE_TYPE
    gsettings set org.mate.background picture-filename "$(find ~/.config/Wallpaper -type f | shuf -n1)"
}

# 获取图片链接地址
get_Pictures_URL() {
    # 定义局部变量 (未拼接的图片链接)
    INCOMPLETE_URL=$(

    # 获取 Bing 网站的源码
    curl -sL "$BING_URL" |
    
    # 进行第一次粗略过滤时的关键字 (快速定位到图片链接所在行)
    grep "$FIRST_FILTERING_RULE" |
    
    # 进行第二次精确过滤时的规则 (提取出图片链接)
    awk "$SECOND_FILTERING_RULE" )

    # 开始执行 file_Name 函数并传入已拼接的 URL 和未拼接的 URL 两个参数
    get_File_Name "$BING_URL$INCOMPLETE_URL" "$INCOMPLETE_URL"
}

# 开始执行 get_Pictures 函数
get_Pictures_URL
