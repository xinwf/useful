#!/usr/bin/bash

APOLLO_HOME='/home/ubuntu/auto/apollo'

#general
alias cln='printf "\033c"'
alias clr='clear'

#apollo and docker relative
alias clnlog='rm -rf ${APOLLO_HOME}/data/log/*'
alias clncore='rm -rf ${APOLLO_HOME}/data/core/*'
alias clndocker='docker volume rm $(docker volume ls -qf "dangling=true")'
alias stopdocker='docker stop $(docker ps -aq)'
alias startdocker='bash ${APOLLO_HOME}/docker/scripts/dev_start.sh -C -l -t apollo'
alias intodocker='bash ${APOLLO_HOME}/docker/scripts/dev_into.sh'

#git relative
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

alias kil='sudo ${APOLLO_HOME}/third_party/killProcess.py'
