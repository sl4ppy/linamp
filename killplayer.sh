ps -aux | grep '/home/linamp/linamp/player' | grep -v 'grep' | awk '{print $2}' | xargs kill
