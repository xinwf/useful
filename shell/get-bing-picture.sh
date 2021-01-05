#!/bin/bash

# @Author: 文正•喵
# @E-Mail: ivlioioilvi@outlook.com

# @Modified by: Xin Wenfei
# @E-Mail: xinwf18@gmail.com
# @Note: Using crontab -e to set a timed task(This is a temporary method, it will lost after reboot, permanent method is
#          edit /etc/crontab)
#  example: 0 10 * * * /home/xwf/Public/xwf_github/useful/shell/get-bing-picture.sh
# @Crontab usage description: https://blog.csdn.net/allenlinrui/article/details/7490206
# @New version(Using api with js): https://github.com/Cool-Pan/wz-bing

#
# 获取必应每日的主页图片作为壁纸
#

# 定义图片基本 URL
SET_URL_BASE="https://cn.bing.com"
# 定义 API 地址
SET_API="https://bing.com/HPImageArchive.aspx?format=js&idx=0&n=1"

# Define two different versions
SET_API_EN="https://cn.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1&ensearch=1"
SET_API_CN="https://cn.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1&ensearch=0"

WallpaperBackup=$HOME/.config/Wallpaper/Backups

# The following setting is pretty significant, due to the cron uses /bin/sh as the script's interpreter, which doesn't
# support sufficient environment variable, hence, we do some work to fix it(This was added for ubuntu mate)
# PID=$(pgrep mate-session)
# export DBUS_SESSION_BUS_ADDRESS=$(grep -z DBUS_SESSION_BUS_ADDRESS /proc/$PID/environ|cut -d= -f2-)

# 准备工作
Preparation_Action() {
    # 判断存放壁纸的文件夹是否存在，如果不存在就创建
    if [ -d "$WallpaperBackup" ]; then
        echo "hello"
    else
        mkdir -p "$WallpaperBackup"
    fi
}

# 开始执行 preparation_Action 函数
Preparation_Action

# 提取文件名
Set_Wallpaper() {
    # 获取传入的参数 1 (已拼接的图片链接)
    FILE_NAME="$1"
    # 获取传入的参数 2 (未拼接的图片链接)
    FILE_TYPE=".$2"

    TODAY="$3"

    # 拼接图片最后的名字
    LAST_PIC_FILE_NAME=$TODAY"_"$FILE_NAME$FILE_TYPE

    # 复制壁纸到壁纸的存放目录
    cp -f "$WallpaperBackup/$LAST_PIC_FILE_NAME" "$HOME/.config/Wallpaper/Current$FILE_TYPE"
    # 通过 feh 设置壁纸
    # 你也可以注释掉下面这行，转而使用其它壁纸设置工具，如果你想的话
    # feh --randomize --no-fehbg --bg-scale ~/.config/Wallpaper/Current$FILE_TYPE

    # this is for ubuntu-mate
    # gsettings set org.mate.background picture-filename "$(find ~/.config/Wallpaper -maxdepth 1 -type f | shuf -n1)"
    
    # this is for linux mint
    gsettings set org.cinnamon.desktop.background picture-uri "file://$(find $HOME/.config/Wallpaper -maxdepth 1 -type f | shuf -n1)"
}

CheckIfExist() {
    existed=false
    for fn in $(ls $WallpaperBackup)
    do
        pic_name=${fn#*_}
        pic_name=${pic_name%.*}
        if [ "$1" == "$pic_name" ];then
            existed=true
            break
        fi
    done
    echo $existed
}

# 获取图片链接地址
Get_Pictures() {
    # 获取图片具体 URL(default)
    # GET_URL=$(curl -sL "$SET_API_CN" | awk -F '"' '{ print $18 }')
    
    # set two timers with crontab
    hour=$(date +%H)
    # minute=$(date +%M)
    # if [ $minute -gt 10 ]; then
    if [ $hour -lt 13 ]; then
        echo "morning"
        GET_URL=$(curl -sL "$SET_API_EN" | awk -F '"' '{ print $18 }')
    else
        echo "afternoon"
        GET_URL=$(curl -sL "$SET_API_CN" | awk -F '"' '{ print $18 }')
    fi

    # 获取图片名
    GET_NAME=$(echo -e "$GET_URL" | cut -d "_" -f 1 | cut -d "." -f 2)
    # 获取图片格式
    GET_TYPE=$(echo -e "$GET_URL" | cut -d "&" -f 2 | cut -d "." -f 2)

    # 获取当前日期
    TODAY=$(date +%Y%m%d)

    if [ "`CheckIfExist $GET_NAME`" != true ];then
        # 下载图片
        curl -L "$SET_URL_BASE$GET_URL" -o "$WallpaperBackup/$TODAY"_"$GET_NAME.$GET_TYPE"

        # 设置壁纸
        Set_Wallpaper "$GET_NAME" "$GET_TYPE" "$TODAY"
    else
        echo $GET_NAME" exists"
    fi
}

# 开始执行 get_Pictures 函数
Get_Pictures
