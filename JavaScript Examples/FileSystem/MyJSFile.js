function myFunction()
{
		alert("Read Dir Example!"); 
		files = filesystem.readDir("C:/"); 
		for(file in files)
		{
			alert(files[file]);
		}
		alert("Read Dir Example after call!"); 
}
