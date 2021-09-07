# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 01:10:17 by asoursou          #+#    #+#              #
#    Updated: 2021/09/07 12:13:02 by sachouam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

usage='\033cPress Ctrl+C to quit'
binary='a.out'

echo -e "$usage"
while true; do
    pids=`pgrep $binary`
    if [ ! -z "$pids" ]; then
        echo -e "$usage"
        for pid in $pids; do
            echo "$binary ($pid): `lsof -p $pid | wc -l`"
            childs=`pgrep -P $pid`
            if [ -z "$childs" ]; then
                echo '  No childs process.'
            else
                echo '  Childs process:'
                for child in $childs; do
                    name=`ps -p $child | tail -n 1 | cut -d ' ' -f 7`
                    echo "    $name ($child): `lsof -p $child | wc -l`"
                done
            fi
        done
    fi
    sleep 2
done
