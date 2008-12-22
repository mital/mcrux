#pragma once

#include <WebKit.h>


class IMCruxWebUIDelegateHandler
{

public:

	IMCruxWebUIDelegateHandler() { }
	virtual ~IMCruxWebUIDelegateHandler() { }

	// IWebUIDelegate
	virtual HRESULT STDMETHODCALLTYPE createWebViewWithRequest( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebURLRequest *request,
		/* [retval][out] */ IWebView **newWebView) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewShow( 
		/* [in] */ IWebView *sender) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewClose( 
		/* [in] */ IWebView *sender) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewFocus( 
		/* [in] */ IWebView *sender) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewUnfocus( 
		/* [in] */ IWebView *sender) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ OLE_HANDLE *responderHWnd) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE makeFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE responderHWnd) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE setStatusText( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR text) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewStatusText( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BSTR *text) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewAreToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE setToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewIsStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE setStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewIsResizable( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *resizable) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE setResizable( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL resizable) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE setFrame( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *frame) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewFrame( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *frame) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE setContentRect( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *contentRect) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE webViewContentRect( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *contentRect) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptAlertPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [retval][out] */ BOOL *result) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptTextInputPanelWithPrompt( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ BSTR defaultText,
		/* [retval][out] */ BSTR *result) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE runBeforeUnloadConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ IWebFrame *initiatedByFrame,
		/* [retval][out] */ BOOL *result) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE runOpenPanelForFileButtonWithResultListener( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebOpenPanelResultListener *resultListener) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE mouseDidMoveOverElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *elementInformation,
		/* [in] */ UINT modifierFlags) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE contextMenuItemsForElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *element,
		/* [in] */ OLE_HANDLE defaultItemsHMenu,
		/* [retval][out] */ OLE_HANDLE *resultHMenu) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE validateUserInterfaceItem( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ BOOL defaultValidation,
		/* [retval][out] */ BOOL *isValid) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE shouldPerformAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ UINT sender) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE dragDestinationActionMaskForDraggingInfo( 
		/* [in] */ IWebView *webView,
		/* [in] */ IDataObject *draggingInfo,
		/* [retval][out] */ WebDragDestinationAction *action) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE willPerformDragDestinationAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragDestinationAction action,
		/* [in] */ IDataObject *draggingInfo) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE dragSourceActionMaskForPoint( 
		/* [in] */ IWebView *webView,
		/* [in] */ LPPOINT point,
		/* [retval][out] */ WebDragSourceAction *action) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE willPerformDragSourceAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragSourceAction action,
		/* [in] */ LPPOINT point,
		/* [in] */ IDataObject *pasteboard) { return S_OK; }

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE contextMenuItemSelected( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *item,
		/* [in] */ IPropertyBag *element) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE hasCustomMenuImplementation( 
		/* [retval][out] */ BOOL *hasCustomMenus) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE trackCustomPopupMenu( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu,
		/* [in] */ LPPOINT point) { return S_OK; }

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE measureCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *measureItem) { return S_OK; }

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE drawCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *drawItem) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE addCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE cleanUpCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE canTakeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward,
		/* [out] */ BOOL *result) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE takeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE registerUndoWithTarget( 
		/* [in] */ IWebUndoTarget *target,
		/* [in] */ BSTR actionName,
		/* [in] */ IUnknown *actionArg) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE removeAllActionsWithTarget( 
		/* [in] */ IWebUndoTarget *target) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE setActionTitle( 
		/* [in] */ BSTR actionTitle) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE undo() { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE redo() { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE canUndo( 
		/* [retval][out] */ BOOL *result) { return S_OK; }

	virtual HRESULT STDMETHODCALLTYPE canRedo( 
		/* [retval][out] */ BOOL *result) { return S_OK; }

};
