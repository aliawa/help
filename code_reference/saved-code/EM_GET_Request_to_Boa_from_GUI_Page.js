//----------------------------------------------------------------------
// This requires a link in /home/httpd/data/routing.js to 
// /var/mand/routing.js
// To do this: in $OSTOP/vendors/Edgewater/E4600/Makefile
// romfs:
//    $(ROMFSINST) -s /var/mand/routing.js /home/httpd/data/routing.js
//----------------------------------------------------------------------



// cross browser requestObject
function requestObject() {
  if (window.XMLHttpRequest)
    return new XMLHttpRequest();
  else if (window.ActiveXObject)
    return new ActiveXObject("Msxml2.XMLHTTP");
  else
    throw new Error("Could not create HTTP request object.");
}

// wrapper for asynchronous get request
// On success the "success" call back function is called
// On failure the "failure" call back function is called
function simpleHttpRequest(url, success, failure) {
  var request = requestObject();
  request.open("GET", url, true);
  request.onreadystatechange = function() {
    if (request.readyState == 4) {
      if (request.status == 200 || !failure)
        success(request.responseText);
      else if (failure)
        failure(request.status, request.statusText);
    }
  };
  request.send(null);
}


function evalJSON(json) {
  return  eval("(" + json + ")");
}

var rgroups = {};
function gotData(data)
{
    rgroups = evalJSON(data);
    console.log(rgroups);
    updateRGStatus();
}



// simple request
function onPageLoad() {
    simpleHttpRequest("/data/routing.js", gotData);
}




