#! /usr/bin/awk -f 



# Push an item into a stack "s". Return the size of the new stack.
function push(s,item) {
    i = ++s[0]
    s[i] = item
    return i
}


# Pop an item from a stack "s". Return the item.
function pop(s) {
    if (s[0] > 0 ) {
        i = s[0]--
          item = s[i]
        delete s[i]
    } else {
    item=""
}
return item
                                                        }


BEGIN {
    stack[0]=0 # read/write pointer
}



/push/ {
    push(stack, $2)
    print "wrote " $2
}

/pop/ {
    val = pop(stack)
    print "read " val
    next
}





