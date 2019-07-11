#!/bin/bash

#install basic tools
sudo apt install terminator curl meld

#install full vim
sudo apt remove vim-common  vim-tiny
sudo apt install vim

#add repository: vscode, fcitx
curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg
sudo mv microsoft.gpg /etc/apt/trusted.gpg.d/microsoft.gpg
sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list'

sudo add-apt-repository ppa:fcitx-team/nightly

#another choice for installing vscode 
#wget https://vscode.cdn.azure.cn/stable/a3db5be9b5c6ba46bb7555ec5d60178ecc2eaae4/code_1.32.3-1552606978_amd64.deb
#sudo dpkg -i code_1.32.3-1552606978_amd64.deb
#rm code_1.32.3-1552606978_amd64.deb


#install code, fcitx
sudo apt update
sudo install code fcitx fcitx-config-gtk fcitx-table-all im-switch -y
wget http://cdn2.ime.sogou.com/dl/index/1524572264/sogoupinyin_2.2.0.0108_amd64.deb?st=Wh1GOC3eFbNLzkn538sBMQ&e=1553609653&fn=sogoupinyin_2.2.0.0108_amd64.deb
sudo dpkg -i sogoupinyin_2.2.0.0108_amd64.deb
rm sogoupinyin_2.2.0.0108_amd64.deb

#install chrome browser
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo dpkg -i google-chrome-stable_current_amd64.deb
rm google-chrome-stable_current_amd64.deb


