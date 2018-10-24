#general
alias cln='printf "\033c"'
alias clr='clear'

#apollo and docker relative
alias clnlog='rm -rf /home/ubuntu/auto/apollo/data/log/*'
alias clncore='rm -rf /home/ubuntu/auto/apollo/data/core/*'
alias clndocker='docker rmi $(docker images -f "dangling=true" -q)'
alias stopdocker='docker stop $(docker ps -aq'
alias startdocker='bash /home/ubuntu/auto/apollo/docker/scripts/dev_start.sh -C -l -t base_apollo'
alias intodocker='bash /home/ubuntu/auto/apollo/docker/scripts/dev_into.sh'

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

alias kil='sudo /home/ubuntu/auto/apollo/third_party/killProcess.py'
