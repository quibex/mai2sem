#! /usr/bin/env bash   

while (( $# > 0 ))
do
    if [[ "$1" == "-d" ]] || [[ "$1" == "--dir" ]]
    then
        shift
        dir="$1"
        shift
    elif [[ "$1" == "-s" ]] || [[ "$1" == "--size" ]]
    then 
        shift
        maxsize="$1"
        shift
    elif [[ "$1" == "-p" ]] || [[ "$1" == "--prefix" ]]
    then
        shift
        pref="$1"
        shift
    elif [[ "$1" == "-n" ]] || [[ "$1" == "--need-to-confirm" ]]
    then
        ntc="true"
        shift
    elif [[ "$1" == "-c" ]] || [[ "$1" == "--config" ]]
    then
        shift
        config="$1"
        shift
    elif [[ "$1" == "-h" ]] || [[ "$1" == "--help" ]] || [[ "$1" == "?" ]]
    then 
        echo $"Usage: $0 [OPTION] ARGUMENT [OPTION] ARGUMENT ...
   or: Use a config file
Options with a required argument:
    -d, --dir               the directory from which you want to delete files
    -s, --size              required maximum directory size in bytes
    -p, --pref              prefix of files to be deleted
    -c, --config            use config file

Usage config file: 
    directory=[directory name]
    max_size=[max directory size in bytes]
    prefix=[prefix]
        "
        exit 1
    fi
done 
if [[ -n "$config" ]]
then 
    while IFS='=' read a1 a2
    do 
        if [[ "$a1" == "directory" ]] && [[ -z "$dir" ]]
        then 
            dir="$a2"
        elif [[ "$a1" == "max_size" ]] && [[ -z "$maxsize" ]]
        then 
            maxsize="$a2"
        elif [[ "$a1" == "prefix" ]] && [[ -z "$pref" ]]
        then 
            pref="$a2"
        fi
    done < "$config"
fi

if [[ -z $dir ]] || [[ -z $maxsize ]] || [[ -z $pref ]]
then 
    echo "Missing parameters!"    
fi 

while ! [[ -d "$dir" ]]
do 
    echo -e "'"$dir"': No such directory \nEnter correct directory: "
    read dir
done
re='^[0-9]+$'
while ! [[ $maxsize =~ $re ]]
do
    echo -e "'"$maxsize"': Not a number \nEnter size directory in bytes: "
    read maxsize
done
while [[ -z "$pref" ]]
do  
    echo "No prefix. Enter prefix: "
    read pref
done


sumfiles=$(du -s "$dir" | awk '{print $1}')
count=0

while read filesize filename
do
    if [[ $maxsize -gt $sumfiles ]] 
    then
        echo "Done, directory size: $sumfiles B"
        break
    elif [[ grep "$pref" "$filename" ]]
    then 
        continue
    else 
        rm "$filename"
        sumfiles=$((sumfiles - sizefile))
        ((count++))
    fi
done < <(du -a "$dir" | sort -n )
echo "deleted $count files"

if [[ $maxsize -le $sumfiles ]] 
then
    echo "There are no more files with this prefix left. Directory size: $sumfiles B"
fi