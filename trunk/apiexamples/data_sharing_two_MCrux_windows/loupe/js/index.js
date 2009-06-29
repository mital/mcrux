$(document).ready(function (){
	$("#editor").keypress(function (event){
		if (mcrux.loupeEventHandler)
			mcrux.loupeEventHandler(String.fromCharCode(event.which));
	});
});
