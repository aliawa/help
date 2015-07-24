// check the type of event target
if (event.target.type !== 'checkbox') 


// prevent bubbling of events
event.preventDefault();
return false;

// Arrays
"http://www.hunlock.com/blogs/Mastering_Javascript_Arrays"


// Replace the content of a table cell
var firstEl = row.cells[0].firstChild;
if (isEmpty(firstEl.nodeValue) ) {
    row.cells[0].replaceChild(delRowBtn,firstEl);
}


// Example of setUserData
var d = document.implementation.createDocument('', 'test', null);   
d.documentElement.setUserData('key', 15, {handle:function (o, k, d, s, ds) {alert(o+'::'+k+'::'+d+'::'+s+'::'+ds)}}); // 2::key::15::[object Element]::[object Element]  
alert(d.documentElement.getUserData('key')); // 15  
var e = document.importNode(d.documentElement, true); // causes handler to be called  
alert(e.getUserData('key')); // null since user data is not copied  

// somehow delRowBtn.onclick = "f()" does not work however the following works
delRowBtn.setAttribute("onclick", "f()");


//Good CSS selector reference
http://www.w3.org/TR/selectors/


// Nice definition list formating
http://www.maxdesign.com.au/articles/definition/


// Event handling
http://www.quirksmode.org/js/introevents.html 



// Event bubbling 

chrome:
handler() {
    event.stopPropagation();
}

firefox
handler(e) {
    e.stopPropagation();
}

ie8
handler(){
    window.event.cancelBubble="true";
}

combined:
handler(e){
    if (e.stopPropagation){
        e.stopPropagation();
    }else {
        window.event.cancelBubble="true";
    }
}



// Accessing objects in form:
var sel_ctrl = document.getElementsByName('dirSelect')[0];
var sel_opt = direction_ctrl.options[direction_ctrl.selectedIndex];

var frm = document.mainForm.dirSelect;
var value = frm.dirSelect.selected.text;

var value = window["dirSelect"].selected.text;




// Java script reference
www.diveintojavascript.com
