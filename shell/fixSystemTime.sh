#!/bin/bash

ROBOT_USER="tic"
ROBOT_PWD="tic123"
ROBOT_IP="192.168.8.88"
ROBOT_DEST="$ROBOT_USER@$ROBOT_IP"

function getCurrentTime()
{
    current_date=$(date +%m/%d/%Y)
    current_time=$(date +%H:%M:%S)
    echo $current_date' '$current_time > $1
}

function generateUpdateScript()
{
    echo "
#!/bin/bash

export IFS=\" \"
read sys_time < $2

sys_time=(\$sys_time)

cur_date=\${sys_time[0]}
cur_time=\${sys_time[1]}

echo '$ROBOT_PWD' | sudo -S date -s \$cur_date
echo '$ROBOT_PWD' | sudo -S date -s \$cur_time
echo '$ROBOT_PWD' | sudo -S hwclock --systohc

# echo \$cur_date
# echo \$cur_time

rm $2
rm $1

sudo reboot
    " > $1
}

function updateSystemTime()
{
    cur_time=".cur_time"
    updateScript=".update_time.sh"
    generateUpdateScript $updateScript $cur_time
    getCurrentTime $cur_time
    ssh-keygen -f "${HOME}/.ssh/known_hosts" -R $ROBOT_IP
    sshpass -p$ROBOT_PWD scp -o stricthostkeychecking=no $cur_time $ROBOT_DEST:
    sshpass -p$ROBOT_PWD scp -o stricthostkeychecking=no $updateScript $ROBOT_DEST:
    sshpass -p$ROBOT_PWD ssh -o stricthostkeychecking=no $ROBOT_DEST << EOF
        chmod +x .update_time.sh 
        ./.update_time.sh
EOF
    rm $cur_time
    rm $updateScript
    echo -e "\nFix system time successfully. Restarting the machine ...\n"
}

updateSystemTime