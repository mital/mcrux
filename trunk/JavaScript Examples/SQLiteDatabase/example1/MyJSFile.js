function myFunction()
{
	alert("sqlite Example ! creating mydb object with new operator");
	var mydb = new sqlite_database();
	alert("mydb created successfully now calling someFunction() over it");
	mydb.someFunction();
	alert("after SomeFunction call");
}
