Parse command line
----------------------------------------------------------------------
zparseopts -D -F -A args -- -sd: -ed: -since: b: t:

if [[ -n $args[-b] ]];then
    show_bug $args[-b]
elif [[ -n $args[-t] ]];then
    select_on_tag $args[-t]
elif [[ -n $args[-a] ]];then
    select_on_area $args[-a]
else 
    show_bugs_period "$args[--sd]" "$args[--ed]" "$args[--since]"
fi

