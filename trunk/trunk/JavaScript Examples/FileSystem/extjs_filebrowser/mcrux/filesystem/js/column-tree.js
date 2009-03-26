/*
 * Ext JS Library 2.2.1
 * Copyright(c) 2006-2009, Ext JS, LLC.
 * licensing@extjs.com
 * 
 * http://extjs.com/license
 */

function makeprettysize ( n, precision )
{
 if ( n == 0 )
  return '0 B';
 var s = 'kMGTPEZY';
 var times = Math.floor( Math.log( n ) / Math.log( 1024 ) );
 return Math.round( ( n / Math.pow( 1024, times ) ) * Math.pow( 10, precision ) ) / Math.pow( 10, precision ) + ' ' + s.charAt( times - 1 ) + 'B';
}

Ext.onReady(function(){
	var tree = new Ext.tree.ColumnTree({
		width: 650,
		height: 300,
		rootVisible:false,
		autoScroll:true,
		title: 'MCrux Filesystem',
		renderTo: Ext.getBody(),
		
		columns:[{
			header:'filename',
			width:350,
			dataIndex:'name'
		},{
			header:'Size',
			width:120,
			dataIndex:'size'
		},{
			header:'Last Modified Time',
			width:175,
			dataIndex:'last_modified_time'
		}],

		loader: new Ext.tree.TreeLoader({
			dataUrl:'http://www.mcrux.com/',
			uiProviders:{
				'col': Ext.tree.ColumnNodeUI
			}
		}),

		root: new Ext.tree.AsyncTreeNode({
			text:'Tasks'
		})
	});
});

Ext.override(Ext.tree.TreeLoader,{
	requestData : function(node, callback){
		if(this.fireEvent("beforeload", this, node, callback) !== false){
			/*	success: this.handleResponse,
				failure: this.handleFailure,
				scope: this,
				argument: {callback: callback, node: node},
			*/
			//var params = this.getParams(node);
			
			var response = {argument: {callback: callback, node: node}};
			if(node.attributes.filePath && typeof node.attributes.filePath == "string")
			{
				response.responseText = mcrux.filesystem.readDir(node.attributes.filePath);
			}
			else
			{
				response.responseText = [{name: 'C:\\', size: '0', last_modified_time: ''}];
			}
			for(key in response.responseText)
			{
			    response.responseText[key].last_modified_time = new Date(response.responseText[key].last_modified_time  * 1000); 
				response.responseText[key].size = makeprettysize(response.responseText[key].size , 0);
				response.responseText[key].uiProvider='col';
				response.responseText[key].cls='master-task';
				if(response.responseText[key].type=="file")
				{
    				response.responseText[key].iconCls='task';
					response.responseText[key].leaf='true';
				}
				else
				{
    				//response.responseText[key].iconCls='task-folder';
				}
			}
			this.handleResponse(response);
		}else{
			// if the load is cancelled, make sure we notify
			// the node that we are done
			if(typeof callback == "function"){
				callback();
			}
		}
	}
	,
	
	processResponse : function(response, node, callback){
		//var json = response.responseText;
		
		var o = response.responseText;
		try {
			//var o = eval("("+json+")");
			node.beginUpdate();
			for(var i = 0, len = o.length; i < len; i++){
				var n = this.createNode(o[i]);
				if(n){
					node.appendChild(n);
					var rPath="";
					if(node.attributes.filePath)
						rPath = node.attributes.filePath;
					n.attributes.filePath = rPath + o[i].name + "\\";
				}
			}
			node.endUpdate();
			if(typeof callback == "function"){
				callback(this, node);
			}
		}catch(e){
			this.handleFailure(response);
		}
	}
})