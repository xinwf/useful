#!/bin/bash

APOLLO_HOME='/home/ubuntu/apolloauto/auto/apollo'
APOLLO3_HOME='/home/ubuntu/apolloauto/apollo3.0/apollo3'
APOLLOM_HOME='/home/ubuntu/apolloauto/apollo/apollomaster/apollo-master'

#general
alias cln='printf "\033c"'
alias clr='clear'
alias kil='${HOME}/Public/xwf_github/useful/python/killProcess.py'
alias skil='sudo ${HOME}/Public/xwf_github/useful/python/killProcess.py'
alias monnvi='watch -d -n 1 nvidia-smi'
alias conz420='ssh ubuntu@192.168.0.99'
alias psgc='ps aux | grep '
alias getOneDir='python ${HOME}/Public/xwf_github/useful/getOneDirV2/getOneDir.py'
alias lsf='ls -l |grep "^-"'
alias lsd='ls -l |grep "^d"'
alias wcf='ls -l |grep "^-" | wc -l'
alias wcd='ls -l |grep "^d" | wc -l'

#docker relative
alias clndocker='docker volume rm $(docker volume ls -qf "dangling=true")'
alias stopdocker='docker stop $(docker ps -aq)'
alias start_ismart_website='docker run --name ismart-website -p 8080:8080 -v /wwwroot:/usr/share/nginx/html:ro -d nginx'


#apollo relative
alias clnlog='rm -rf ${APOLLO_HOME}/data/log/*'
alias clncore='rm -rf ${APOLLO_HOME}/data/core/*'
alias startdocker='bash ${APOLLO_HOME}/docker/scripts/dev_start.sh -C -l -t apollo'
alias startdockerper='bash ${APOLLO_HOME}/docker/scripts/dev_start_per.sh -l -t perception_apollo'
alias intodocker='bash ${APOLLO_HOME}/docker/scripts/dev_into.sh'

#apollo3.0 relative
alias clnlog3='rm -rf ${APOLLO3_HOME}/data/log/*'
alias clncore3='rm -rf ${APOLLO3_HOME}/data/core/*'
alias startdocker3='bash ${APOLLO3_HOME}/docker/scripts/dev_start.sh -C -l -t apollo3.0_pure'
alias startdockerper3='bash ${APOLLO3_HOME}/docker/scripts/dev_start_per.sh -C -l -t apollo3-per'
alias intodocker3='bash ${APOLLO3_HOME}/docker/scripts/dev_into.sh'

#apollo master relative
alias clnlogm='rm -rf ${APOLLOM_HOME}/data/log/*'
alias clncorem='rm -rf ${APOLLOM_HOME}/data/core/*'
alias startdockerm='bash ${APOLLOM_HOME}/docker/scripts/dev_start_per.sh -C -l -t apollo-master-perception'
alias intodockerm='bash ${APOLLOM_HOME}/docker/scripts/dev_into.sh'

#git relative
alias gcl='git clone'
alias gcb='git clone -b'
alias gbr='git branch'
alias gcm='git commit -m'
alias gck='git checkout'
alias gpl='git pull'
alias gps='git push'
alias gad='git add'
alias gst='git status'
alias gdf='git diff'
alias gfc='git fetch'
alias glg='git log'
alias grm='git rm'
alias grs='git reset'
alias gsh='git show'
alias gtg='git tag'

#ros and catkin_make relative
export ROS_HOSTNAME=localhost
export ROS_MASTER_URI=http://localhost:11311/
alias pub='rostopic pub -1'
alias reser='roslaunch ist_room_exploration room_exploration_action_server.launch'
alias recli='roslaunch ist_room_exploration room_exploration_client.launch'
alias cmiiopwd='catkin_make_isolated --install --only-pkg-with-deps'
alias cmiifp='catkin_make_isolated --install --from-pkg'
alias cmiip='catkin_make_isolated --install --pkg'
alias cmii='catkin_make_isolated --install'
alias cmi='catkin_make install'
alias cmopwd='catkin_make --only-pkg-with-deps'
alias cm='catkin_make'

# catkin_make with specific packages
cmarg() {
 pkglist=''
 for key in "$@"
 do
    #pkglist=$key';'$pkglist
    pkglist=$pkglist';'$key
 done
 #echo ${pkglist%;*}
 #echo ${pkglist#*;}
 #catkin_make -DCATKIN_WHITELIST_PACKAGES=${pkglist%;*}
 catkin_make -DCATKIN_WHITELIST_PACKAGES=${pkglist#*;}
}

# delete files except specific files
rmfe() {
 whitelist=''
 for fn in "$@"
 do
    whitelist=$whitelist'|'$fn
 done
 #echo ${whitelist#*|}
 rm !(${whitelist#*|})
}
