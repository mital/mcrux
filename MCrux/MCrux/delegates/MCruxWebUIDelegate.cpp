#include "StdAfx.h"

#include "MCruxWebUIDelegate.h"

#include <comdef.h>

MCruxWebUIDelegate::MCruxWebUIDelegate()
: m_refCount(1),
  handler(NULL)
{
}

MCruxWebUIDelegate::~MCruxWebUIDelegate()
{
}


void MCruxWebUIDelegate::setUIHandler(IMCruxWebUIDelegateHandler * _handler)
{
	handler = _handler;
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
	return handler->createWebViewWithRequest(sender, request, newWebView);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate::webViewShow( 
		/* [in] */ IWebView *sender)
{
	return handler->webViewShow(sender);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewClose( 
		/* [in] */ IWebView *sender)
{
	return handler->webViewClose(sender);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewFocus( 
		/* [in] */ IWebView *sender)
{
	return handler->webViewFocus(sender);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewUnfocus( 
		/* [in] */ IWebView *sender)
{
	return handler->webViewUnfocus(sender);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ OLE_HANDLE *responderHWnd)
{
	return handler->webViewFirstResponder(sender, responderHWnd);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: makeFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE responderHWnd)
{
	return handler->makeFirstResponder(sender, responderHWnd);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setStatusText( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR text)
{
	return handler->setStatusText(sender, text);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewStatusText( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BSTR *text)
{
	return handler->webViewStatusText(sender, text);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewAreToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible)
{
	return handler->webViewAreToolbarsVisible(sender, visible);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible)
{
	return handler->setToolbarsVisible(sender, visible);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewIsStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible)
{
	return handler->webViewIsStatusBarVisible(sender, visible);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible)
{
	return handler->setStatusBarVisible(sender, visible);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewIsResizable( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *resizable)
{
	return handler->webViewIsResizable(sender, resizable);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setResizable( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL resizable)
{
	return handler->setResizable(sender, resizable);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setFrame( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *frame)
{
	return handler->setFrame(sender, frame);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewFrame( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *frame)
{
	return handler->webViewFrame(sender, frame);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setContentRect( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *contentRect)
{
	return handler->setContentRect(sender, contentRect);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: webViewContentRect( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *contentRect)
{
	return handler->webViewContentRect(sender, contentRect);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runJavaScriptAlertPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message)
{
	return handler->runJavaScriptAlertPanelWithMessage(sender, message);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runJavaScriptConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [retval][out] */ BOOL *result)
{
	return handler->runJavaScriptConfirmPanelWithMessage(sender, message, result);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runJavaScriptTextInputPanelWithPrompt( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ BSTR defaultText,
		/* [retval][out] */ BSTR *result)
{
	return handler->runJavaScriptTextInputPanelWithPrompt(sender, message, defaultText, result);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runBeforeUnloadConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ IWebFrame *initiatedByFrame,
		/* [retval][out] */ BOOL *result)
{
	return handler->runBeforeUnloadConfirmPanelWithMessage(sender, message, initiatedByFrame, result);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: runOpenPanelForFileButtonWithResultListener( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebOpenPanelResultListener *resultListener)
{
	return handler->runOpenPanelForFileButtonWithResultListener(sender, resultListener);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: mouseDidMoveOverElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *elementInformation,
		/* [in] */ UINT modifierFlags)
{
	return handler->mouseDidMoveOverElement(sender, elementInformation, modifierFlags);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: contextMenuItemsForElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *element,
		/* [in] */ OLE_HANDLE defaultItemsHMenu,
		/* [retval][out] */ OLE_HANDLE *resultHMenu)
{
	return handler->contextMenuItemsForElement(sender, element, defaultItemsHMenu, resultHMenu);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: validateUserInterfaceItem( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ BOOL defaultValidation,
		/* [retval][out] */ BOOL *isValid)
{
	return handler->validateUserInterfaceItem(webView, itemCommandID, defaultValidation, isValid);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: shouldPerformAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ UINT sender)
{
	return handler->shouldPerformAction(webView, itemCommandID, sender);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: dragDestinationActionMaskForDraggingInfo( 
		/* [in] */ IWebView *webView,
		/* [in] */ IDataObject *draggingInfo,
		/* [retval][out] */ WebDragDestinationAction *action)
{
	return handler->dragDestinationActionMaskForDraggingInfo(webView, draggingInfo, action);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: willPerformDragDestinationAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragDestinationAction action,
		/* [in] */ IDataObject *draggingInfo)
{
	return handler->willPerformDragDestinationAction(webView, action, draggingInfo);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: dragSourceActionMaskForPoint( 
		/* [in] */ IWebView *webView,
		/* [in] */ LPPOINT point,
		/* [retval][out] */ WebDragSourceAction *action)
{
	return handler->dragSourceActionMaskForPoint(webView, point, action);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: willPerformDragSourceAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragSourceAction action,
		/* [in] */ LPPOINT point,
		/* [in] */ IDataObject *pasteboard)
{
	return handler->willPerformDragSourceAction(webView, action, point, pasteboard);
}


/* [local] */ HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: contextMenuItemSelected( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *item,
		/* [in] */ IPropertyBag *element)
{
	return handler->contextMenuItemSelected(sender, item, element);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: hasCustomMenuImplementation( 
		/* [retval][out] */ BOOL *hasCustomMenus)
{
	return handler->hasCustomMenuImplementation(hasCustomMenus);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: trackCustomPopupMenu( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu,
		/* [in] */ LPPOINT point)
{
	return handler->trackCustomPopupMenu(sender, hMenu, point);
}


/* [local] */ HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: measureCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *measureItem)
{
	return handler->measureCustomMenuItem(sender, measureItem);
}


/* [local] */ HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: drawCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *drawItem)
{
	return handler->drawCustomMenuItem(sender, drawItem);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: addCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu)
{
	return handler->addCustomMenuDrawingData(sender, hMenu);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: cleanUpCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu)
{
	return handler->cleanUpCustomMenuDrawingData(sender, hMenu);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: canTakeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward,
		/* [out] */ BOOL *result)
{
	return handler->canTakeFocus(sender, forward, result);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: takeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward)
{
	return handler->takeFocus(sender, forward);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: registerUndoWithTarget( 
		/* [in] */ IWebUndoTarget *target,
		/* [in] */ BSTR actionName,
		/* [in] */ IUnknown *actionArg)
{
	return handler->registerUndoWithTarget(target, actionName, actionArg);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: removeAllActionsWithTarget( 
		/* [in] */ IWebUndoTarget *target)
{
	return handler->removeAllActionsWithTarget(target);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: setActionTitle( 
		/* [in] */ BSTR actionTitle)
{
	return handler->setActionTitle(actionTitle);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: undo()
{
	return handler->undo();
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: redo()
{
	return handler->redo();
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate:: canUndo( 
		/* [retval][out] */ BOOL *result)
{
	return handler->canUndo(result);
}


HRESULT STDMETHODCALLTYPE MCruxWebUIDelegate::canRedo( 
		/* [retval][out] */ BOOL *result)
{
	return handler->canRedo(result);
}
