function myFunctionInJavaScript()
{
	alert("myFunctionInJavaScript Called");
}

function myJSPassedFunction()
{
	alert("Hello, everyone.");  
}  


function myFunction()
{
	alert("CallJSFunction Example!");
	mcrux.callJavaScriptFunction("myFunctionInJavaScript", myJSPassedFunction);
}

function myFunctionInJavaScript()
{
	alert("myFunctionInJavaScript Called");
}