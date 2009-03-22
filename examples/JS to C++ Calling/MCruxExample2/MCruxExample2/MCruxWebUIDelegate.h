#pragma once

#include <WebKit.h>

class MCruxWebUIDelegate :
	public IWebUIDelegate
{
    ULONG m_refCount;

public:

	MCruxWebUIDelegate();
	~MCruxWebUIDelegate();

	// IUnknown
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);
    virtual ULONG STDMETHODCALLTYPE AddRef(void);
    virtual ULONG STDMETHODCALLTYPE Release(void);

	// IWebUIDelegate
	virtual HRESULT STDMETHODCALLTYPE createWebViewWithRequest( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebURLRequest *request,
		/* [retval][out] */ IWebView **newWebView);

	virtual HRESULT STDMETHODCALLTYPE webViewShow( 
		/* [in] */ IWebView *sender);

	virtual HRESULT STDMETHODCALLTYPE webViewClose( 
		/* [in] */ IWebView *sender);

	virtual HRESULT STDMETHODCALLTYPE webViewFocus( 
		/* [in] */ IWebView *sender);

	virtual HRESULT STDMETHODCALLTYPE webViewUnfocus( 
		/* [in] */ IWebView *sender);

	virtual HRESULT STDMETHODCALLTYPE webViewFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ OLE_HANDLE *responderHWnd);

	virtual HRESULT STDMETHODCALLTYPE makeFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE responderHWnd);

	virtual HRESULT STDMETHODCALLTYPE setStatusText( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR text);

	virtual HRESULT STDMETHODCALLTYPE webViewStatusText( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BSTR *text);

	virtual HRESULT STDMETHODCALLTYPE webViewAreToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible);

	virtual HRESULT STDMETHODCALLTYPE setToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible);

	virtual HRESULT STDMETHODCALLTYPE webViewIsStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible);

	virtual HRESULT STDMETHODCALLTYPE setStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible);

	virtual HRESULT STDMETHODCALLTYPE webViewIsResizable( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *resizable);

	virtual HRESULT STDMETHODCALLTYPE setResizable( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL resizable);

	virtual HRESULT STDMETHODCALLTYPE setFrame( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *frame);

	virtual HRESULT STDMETHODCALLTYPE webViewFrame( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *frame);

	virtual HRESULT STDMETHODCALLTYPE setContentRect( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *contentRect);

	virtual HRESULT STDMETHODCALLTYPE webViewContentRect( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *contentRect);

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptAlertPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message);

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [retval][out] */ BOOL *result);

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptTextInputPanelWithPrompt( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ BSTR defaultText,
		/* [retval][out] */ BSTR *result);

	virtual HRESULT STDMETHODCALLTYPE runBeforeUnloadConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ IWebFrame *initiatedByFrame,
		/* [retval][out] */ BOOL *result);

	virtual HRESULT STDMETHODCALLTYPE runOpenPanelForFileButtonWithResultListener( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebOpenPanelResultListener *resultListener);

	virtual HRESULT STDMETHODCALLTYPE mouseDidMoveOverElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *elementInformation,
		/* [in] */ UINT modifierFlags);

	virtual HRESULT STDMETHODCALLTYPE contextMenuItemsForElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *element,
		/* [in] */ OLE_HANDLE defaultItemsHMenu,
		/* [retval][out] */ OLE_HANDLE *resultHMenu);

	virtual HRESULT STDMETHODCALLTYPE validateUserInterfaceItem( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ BOOL defaultValidation,
		/* [retval][out] */ BOOL *isValid);

	virtual HRESULT STDMETHODCALLTYPE shouldPerformAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ UINT sender);

	virtual HRESULT STDMETHODCALLTYPE dragDestinationActionMaskForDraggingInfo( 
		/* [in] */ IWebView *webView,
		/* [in] */ IDataObject *draggingInfo,
		/* [retval][out] */ WebDragDestinationAction *action);

	virtual HRESULT STDMETHODCALLTYPE willPerformDragDestinationAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragDestinationAction action,
		/* [in] */ IDataObject *draggingInfo);

	virtual HRESULT STDMETHODCALLTYPE dragSourceActionMaskForPoint( 
		/* [in] */ IWebView *webView,
		/* [in] */ LPPOINT point,
		/* [retval][out] */ WebDragSourceAction *action);

	virtual HRESULT STDMETHODCALLTYPE willPerformDragSourceAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragSourceAction action,
		/* [in] */ LPPOINT point,
		/* [in] */ IDataObject *pasteboard);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE contextMenuItemSelected( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *item,
		/* [in] */ IPropertyBag *element);

	virtual HRESULT STDMETHODCALLTYPE hasCustomMenuImplementation( 
		/* [retval][out] */ BOOL *hasCustomMenus);

	virtual HRESULT STDMETHODCALLTYPE trackCustomPopupMenu( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu,
		/* [in] */ LPPOINT point);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE measureCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *measureItem);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE drawCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *drawItem);

	virtual HRESULT STDMETHODCALLTYPE addCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu);

	virtual HRESULT STDMETHODCALLTYPE cleanUpCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu);

	virtual HRESULT STDMETHODCALLTYPE canTakeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward,
		/* [out] */ BOOL *result);

	virtual HRESULT STDMETHODCALLTYPE takeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward);

	virtual HRESULT STDMETHODCALLTYPE registerUndoWithTarget( 
		/* [in] */ IWebUndoTarget *target,
		/* [in] */ BSTR actionName,
		/* [in] */ IUnknown *actionArg);

	virtual HRESULT STDMETHODCALLTYPE removeAllActionsWithTarget( 
		/* [in] */ IWebUndoTarget *target);

	virtual HRESULT STDMETHODCALLTYPE setActionTitle( 
		/* [in] */ BSTR actionTitle);

	virtual HRESULT STDMETHODCALLTYPE undo( void);

	virtual HRESULT STDMETHODCALLTYPE redo( void);

	virtual HRESULT STDMETHODCALLTYPE canUndo( 
		/* [retval][out] */ BOOL *result);

	virtual HRESULT STDMETHODCALLTYPE canRedo( 
		/* [retval][out] */ BOOL *result);

};
