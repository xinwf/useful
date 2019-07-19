#!/bin/bash

#install basic tools
sudo add-apt-repository ppa:gnome-terminator -y
sudo apt-get update
sudo apt install terminator curl meld git g++ -y

#install full vim
sudo apt remove vim-common  vim-tiny -y
sudo apt install vim -y

#add repository: vscode, fcitx
# curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg
# sudo mv microsoft.gpg /etc/apt/trusted.gpg.d/microsoft.gpg
# sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list'

# sudo add-apt-repository ppa:fcitx-team/nightly

#install code, fcitx
# sudo apt update
# sudo install code fcitx fcitx-config-gtk fcitx-table-all im-switch -y
# wget http://cdn2.ime.sogou.com/dl/index/1524572264/sogoupinyin_2.2.0.0108_amd64.deb?st=Wh1GOC3eFbNLzkn538sBMQ&e=1553609653&fn=sogoupinyin_2.2.0.0108_amd64.deb
# sudo dpkg -i sogoupinyin_2.2.0.0108_amd64.deb


