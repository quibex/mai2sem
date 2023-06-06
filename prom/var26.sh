#! /usr/bin/env bash


while IFS=: read -r id obj
do 
    if [[ "$obj" == "социология" ]]
    then
        id_suc=$id
    fi
done < subj


while IFS=: read -r id fac group
do
    nmb_of=0
    while IFS=: read -r id_prup facc grp
    do
        while IFS=: read -r id_stud id_obj mark #смотрим оценки
        do  
            if [[ "$id_obj"  "$id_obj" == "$id_suc" && "$mark" == *"4"* ]]; then # забыл проверить факультет
                nmb_of=$(( $nmb_of + 1 ))
            fi
        done < marks
    done < grp
    echo "$nmb_of fac: $fac" >> tmpfile
done < grp

echo $(sort -n tmpfile) > result
