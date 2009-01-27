function myFunction()
{
//	alert("Read Dir Example!"); 
	addTree(document.getElementById("body"), new Array("C:"), true);
}

function addTree(parentElement, childrenArray, blnShow)
{
	var rPath="";
	if(parentElement.filePath)
		rPath = parentElement.filePath + "\\";
		
	var rootElement = document.createElement("ul");
	rootElement.className = "fileBrowser";
	for(childKey in childrenArray)
	{		
		var childElm =  document.createElement("li");
		var spanElm =  document.createElement("span");
		spanElm.innerHTML = childrenArray[childKey];
		childElm.className = "folderNode";
		childElm.appendChild(spanElm);			
		childElm.filePath = rPath + childrenArray[childKey];
		rootElement.appendChild(childElm);			
	}	
	if(!blnShow)
	{
		rootElement.className = "hidden";
	}
	parentElement.appendChild(rootElement);
	$(".folderNode span:first").unbind();
	$(".folderNode span:first").click(
		function ()
		{
			folderClicked(this)
		}
	);
//	alert(parentElement.innerHTML);
}

$(".folderNode span:first").click(
	function ()
	{
		folderClicked(this)
	}
);

function folderClicked(jFolder)
{
//	alert("folderNode Clicked");
//	alert($(jFolder).get(0).innerHTML);
	if($(jFolder).parent(".folderNode").find("ul:first").size())
	{
		if($(jFolder).parent(".folderNode").find("ul:first").hasClass("hidden"))
		{
			$(jFolder).parent(".folderNode").find("ul:first").removeClass("hidden");
			$(jFolder).parent(".folderNode").css("list-style-image","url(img/closeFolder.png)");
		}
		else
		{
			$(jFolder).parent(".folderNode").find("ul:first").addClass("hidden");
			$(jFolder).parent(".folderNode").css("list-style-image","url(img/openFolder.png)");
		}
	}
	else
	{
//			alert("loading directory");
		$(jFolder).parent(".folderNode").css("list-style-image","url(img/closeFolder.png)");
		loadDirectory($(jFolder).parent(".folderNode").get(0));
	}
}

function loadDirectory(folder)
{
	var rootElement = folder;
	//alert(folder.filePath);
	//alert(folder.innerHTML);
	files = filesystem.readDir(folder.filePath); 
	//files = new Array("A","B","C","D","E","F");
	addTree(rootElement, files, true);
}