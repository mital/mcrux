var socketObj;

function ReadDataHandler(event)
{
	alert("ReadDataHandler Handler Called We got the DayTime String back from Time server 'time.nist.gov'");
	alert(event.data);
	socketObj.disconnect();
}

function myFunction()
{
	alert("Pinging the time Server");

	socketObj = new mcrux.socket();
	socketObj.addEventListener("onRead", ReadDataHandler);
	socketObj.connect("time.nist.gov", "13");
}
