#include "StdAfx.h"
#include <comdef.h>
#include "MCruxWebUIDelegate.h"

MCruxWebUIDelegate::MCruxWebUIDelegate()
{
}

MCruxWebUIDelegate::~MCruxWebUIDelegate()
{
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate::QueryInterface(REFIID riid, void** ppvObject)
{
    *ppvObject = 0;
    if (IsEqualGUID(riid, IID_IUnknown))
		*ppvObject = static_cast<IWebUIDelegate*>(this);
	else if (IsEqualGUID(riid, IID_IWebUIDelegate))
        *ppvObject = static_cast<IWebUIDelegate*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG STDMETHODCALLTYPE MCruxWebUIDelegate::AddRef(void)
{
    return ++m_refCount;
}

ULONG STDMETHODCALLTYPE MCruxWebUIDelegate::Release(void)
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate::createWebViewWithRequest( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebURLRequest *request,
		/* [retval][out] */ IWebView **newWebView)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate::webViewShow( 
		/* [in] */ IWebView *sender)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewClose( 
		/* [in] */ IWebView *sender)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewFocus( 
		/* [in] */ IWebView *sender)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewUnfocus( 
		/* [in] */ IWebView *sender)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ OLE_HANDLE *responderHWnd)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: makeFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE responderHWnd)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setStatusText( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR text)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewStatusText( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BSTR *text)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewAreToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewIsStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewIsResizable( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *resizable)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setResizable( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL resizable)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setFrame( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *frame)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewFrame( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *frame)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setContentRect( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *contentRect)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewContentRect( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *contentRect)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runJavaScriptAlertPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message)
{
	::MessageBoxA(0, (CHAR*)_bstr_t(message), "test", MB_OK);
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runJavaScriptConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [retval][out] */ BOOL *result)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runJavaScriptTextInputPanelWithPrompt( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ BSTR defaultText,
		/* [retval][out] */ BSTR *result)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runBeforeUnloadConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ IWebFrame *initiatedByFrame,
		/* [retval][out] */ BOOL *result)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runOpenPanelForFileButtonWithResultListener( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebOpenPanelResultListener *resultListener)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: mouseDidMoveOverElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *elementInformation,
		/* [in] */ UINT modifierFlags)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: contextMenuItemsForElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *element,
		/* [in] */ OLE_HANDLE defaultItemsHMenu,
		/* [retval][out] */ OLE_HANDLE *resultHMenu)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: validateUserInterfaceItem( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ BOOL defaultValidation,
		/* [retval][out] */ BOOL *isValid)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: shouldPerformAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ UINT sender)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: dragDestinationActionMaskForDraggingInfo( 
		/* [in] */ IWebView *webView,
		/* [in] */ IDataObject *draggingInfo,
		/* [retval][out] */ WebDragDestinationAction *action)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: willPerformDragDestinationAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragDestinationAction action,
		/* [in] */ IDataObject *draggingInfo)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: dragSourceActionMaskForPoint( 
		/* [in] */ IWebView *webView,
		/* [in] */ LPPOINT point,
		/* [retval][out] */ WebDragSourceAction *action)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: willPerformDragSourceAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragSourceAction action,
		/* [in] */ LPPOINT point,
		/* [in] */ IDataObject *pasteboard)
{
	return S_OK;
}


/* [local] */ HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: contextMenuItemSelected( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *item,
		/* [in] */ IPropertyBag *element)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: hasCustomMenuImplementation( 
		/* [retval][out] */ BOOL *hasCustomMenus)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: trackCustomPopupMenu( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu,
		/* [in] */ LPPOINT point)
{
	return S_OK;
}


/* [local] */ HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: measureCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *measureItem)
{
	return S_OK;
}


/* [local] */ HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: drawCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *drawItem)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: addCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: cleanUpCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: canTakeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward,
		/* [out] */ BOOL *result)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: takeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: registerUndoWithTarget( 
		/* [in] */ IWebUndoTarget *target,
		/* [in] */ BSTR actionName,
		/* [in] */ IUnknown *actionArg)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: removeAllActionsWithTarget( 
		/* [in] */ IWebUndoTarget *target)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setActionTitle( 
		/* [in] */ BSTR actionTitle)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: undo( void)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: redo( void)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: canUndo( 
		/* [retval][out] */ BOOL *result)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate::canRedo( 
		/* [retval][out] */ BOOL *result)
{
	return S_OK;
}


