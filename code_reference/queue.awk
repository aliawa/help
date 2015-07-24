#! /usr/bin/awk -f 


# Push an item into a queue "s". Return the size of the new queue.
function push(q,item) {     
    i = q[0]++
    q[i] = item
}


# Pop an item from a queue "q". Return the item.
function pop(q) {
    if (q[0] != q[1] ) {
        i = q[1]++
        item = q[i]
        delete q[i]
    } else {
        item=""
    }
    return item
}


BEGIN {
    queue[0]=2 # write pointer
    queue[1]=2 # read pointer
}



/push/ {
    push(queue, $2)
    print "wrote " $2
}

/pop/ {
    val = pop(queue)
    print "read " val
    next
}





