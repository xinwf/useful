#!/bin/bash

#install basic tools and common apps
sudo add-apt-repository ppa:gnome-terminator -y
sudo apt-get update
sudo apt install -y terminator curl git meld sshpass openssh-server shutter screen

#install full vim
sudo apt remove -y vim-common vim-tiny
sudo apt install -y vim

cd /tmp

#add repository: vscode, fcitx
curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg
sudo mv microsoft.gpg /etc/apt/trusted.gpg.d/microsoft.gpg
sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list'
sudo sh -c 'echo "deb http://archive.ubuntukylin.com:10006/ubuntukylin xenial main" > /etc/apt/sources.list.d/sogoupinyin.list'

sudo add-apt-repository ppa:fcitx-team/nightly

#install code, fcitx, sogou pinyin
sudo apt update
sudo apt install code fcitx fcitx-config-gtk fcitx-table-all im-switch sogoupinyin -y
# wget http://cdn2.ime.sogou.com/dl/index/1524572264/sogoupinyin_2.2.0.0108_amd64.deb?st=Wh1GOC3eFbNLzkn538sBMQ&e=1553609653&fn=sogoupinyin_2.2.0.0108_amd64.deb
# sudo dpkg -i sogoupinyin_2.2.0.0108_amd64.deb
# rm sogoupinyin_2.2.0.0108_amd64.deb

#install chrome browser
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo dpkg -i google-chrome-stable_current_amd64.deb
rm google-chrome-stable_current_amd64.deb


