#!/bin/bash

APOLLO_HOME='/home/ubuntu/auto/apollo'
APOLLO3_HOME='/home/ubuntu/apollo/apollo3.0/apollo'

#general
alias cln='printf "\033c"'
alias clr='clear'

#docker relative
alias clndocker='docker volume rm $(docker volume ls -qf "dangling=true")'
alias stopdocker='docker stop $(docker ps -aq)'


#apollo relative
alias clnlog='rm -rf ${APOLLO_HOME}/data/log/*'
alias clncore='rm -rf ${APOLLO_HOME}/data/core/*'
alias startdocker='bash ${APOLLO_HOME}/docker/scripts/dev_start.sh -C -l -t apollo'
alias intodocker='bash ${APOLLO_HOME}/docker/scripts/dev_into.sh'

#apollo3.0 and docker relative
alias clnlog3='rm -rf ${APOLLO3_HOME}/data/log/*'
alias clncore3='rm -rf ${APOLLO3_HOME}/data/core/*'
alias startdocker3='bash ${APOLLO3_HOME}/docker/scripts/dev_start.sh -C -l -t apollo'
alias intodocker3='bash ${APOLLO3_HOME}/docker/scripts/dev_into.sh'

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
alias grm='git rm'

alias kil='${APOLLO_HOME}/third_party/killProcess.py'
alias skil='sudo ${APOLLO_HOME}/third_party/killProcess.py'
