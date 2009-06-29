function myFunction()
{
	alert("Read Dir Example!"); 
	addTree(document.getElementById("body"), new Array({name:"C:", type:"dir"}), true);
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
		spanElm.innerHTML = childrenArray[childKey].name;// + " " +childrenArray[childKey].type;
		if(childrenArray[childKey].type=="dir")
		{
			childElm.className = "folderNode";
		//	alert(childrenArray[childKey].name + "dir");
		}
		else
		{
			childElm.className = "fileNode";
		//	alert(childrenArray[childKey].name + "file");
		}
		childElm.appendChild(spanElm);			
		childElm.filePath = rPath + childrenArray[childKey].name;
		rootElement.appendChild(childElm);
	}	
	if(!blnShow)
	{
		rootElement.className = "hidden";
	}
	parentElement.appendChild(rootElement);
	$(".folderNode span:first").unbind();
	$(".folderNode span:first").click(
		function (event)
		{
			folderClicked(this, event)
		}
	);
//	alert(parentElement.innerHTML);
}

$(".folderNode span:first").click(
	function (event)
	{
		folderClicked(this, event)
	}
);

function folderClicked(jFolder, event)
{
//	alert("folderNode Clicked");
//	alert($(jFolder).get(0).innerHTML);
//	alert($(jFolder).get(0).offsetTop + " . " + $(jFolder).get(0).offsetLeft + " . " + event.pageY + " . " +  event.pageX);
	if( event.pageX - $(jFolder).get(0).offsetLeft > 10)
	{
		//alert($(jFolder).parent(".folderNode").get(0).filePath);
	}
	else
	{
		if($(jFolder).parent(".folderNode").find("ul:first").size())
		{
			if($(jFolder).parent(".folderNode").find("ul:first").hasClass("hidden"))
			{
				$(jFolder).parent(".folderNode").find("ul:first").removeClass("hidden");
				$(jFolder).css("background-image","url(img/closeFolder.png)");
			}
			else
			{
				$(jFolder).parent(".folderNode").find("ul:first").addClass("hidden");
				$(jFolder).css("background-image","url(img/openFolder.png)");
			}
		}
		else
		{
	//			alert("loading directory");
			$(jFolder).css("background-image","url(img/closeFolder.png)");
			loadDirectory($(jFolder).parent(".folderNode").get(0));
		}
	}
}

var tempCounter=0;
function loadDirectory(folder)
{
	var rootElement = folder;
	alert("path: " + folder.filePath);
	//alert(folder.innerHTML);
	files = mcrux.filesystem.readDir(folder.filePath + "\\"); 
	//files = new Array({name:"A"+tempCounter++},{name:"B"+tempCounter++, type:"dir"},{name:"C"+tempCounter++},{name:"D"+tempCounter++},{name:"E"+tempCounter++},{name:"F"+tempCounter++});
	//alert(files.length);
	//alert(files[0].name);
	addTree(rootElement, files, true);
}