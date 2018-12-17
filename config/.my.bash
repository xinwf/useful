#!/bin/bash

APOLLO_HOME='/home/ubuntu/apolloauto/auto/apollo'
APOLLO3_HOME='/home/ubuntu/apolloauto/apollo/apollo3.0/apollo3'
APOLLOM_HOME='/home/ubuntu/apolloauto/apollo/apollomaster/apollo-master'

#general
alias cln='printf "\033c"'
alias clr='clear'
alias kil='${APOLLO_HOME}/third_party/killProcess.py'
alias skil='sudo ${APOLLO_HOME}/third_party/killProcess.py'
alias monnvi='watch -d -n 1 nvidia-smi'
alias conz420='ssh ubuntu@192.168.0.99'

#docker relative
alias clndocker='docker volume rm $(docker volume ls -qf "dangling=true")'
alias stopdocker='docker stop $(docker ps -aq)'


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
