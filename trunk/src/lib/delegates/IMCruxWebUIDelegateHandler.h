/**
 * copyright (C) 2008 Mital Vora. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of MCrux nor the names of its contributors may be 
 *     used to endorse or promote products derived from this software 
 *     without specific prior written permission.
 *
 * @author: Mital Vora.
 **/

#pragma once

#include <WebKit/WebKit.h>

class IMCruxWebUIDelegateHandler
{

public:

	IMCruxWebUIDelegateHandler() { }
	virtual ~IMCruxWebUIDelegateHandler() { }

	// IWebUIDelegate
	virtual HRESULT STDMETHODCALLTYPE createWebViewWithRequest( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebURLRequest *request,
		/* [retval][out] */ IWebView **newWebView) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewShow( 
		/* [in] */ IWebView *sender) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewClose( 
		/* [in] */ IWebView *sender) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewFocus( 
		/* [in] */ IWebView *sender) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewUnfocus( 
		/* [in] */ IWebView *sender) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ OLE_HANDLE *responderHWnd) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE makeFirstResponder( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE responderHWnd) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE setStatusText( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR text) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewStatusText( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BSTR *text) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewAreToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE setToolbarsVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewIsStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *visible) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE setStatusBarVisible( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL visible) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewIsResizable( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ BOOL *resizable) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE setResizable( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL resizable) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE setFrame( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *frame) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewFrame( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *frame) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE setContentRect( 
		/* [in] */ IWebView *sender,
		/* [in] */ RECT *contentRect) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE webViewContentRect( 
		/* [in] */ IWebView *sender,
		/* [retval][out] */ RECT *contentRect) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptAlertPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [retval][out] */ BOOL *result) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE runJavaScriptTextInputPanelWithPrompt( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ BSTR defaultText,
		/* [retval][out] */ BSTR *result) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE runBeforeUnloadConfirmPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message,
		/* [in] */ IWebFrame *initiatedByFrame,
		/* [retval][out] */ BOOL *result) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE runOpenPanelForFileButtonWithResultListener( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebOpenPanelResultListener *resultListener) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE mouseDidMoveOverElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *elementInformation,
		/* [in] */ UINT modifierFlags) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE contextMenuItemsForElement( 
		/* [in] */ IWebView *sender,
		/* [in] */ IPropertyBag *element,
		/* [in] */ OLE_HANDLE defaultItemsHMenu,
		/* [retval][out] */ OLE_HANDLE *resultHMenu) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE validateUserInterfaceItem( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ BOOL defaultValidation,
		/* [retval][out] */ BOOL *isValid) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE shouldPerformAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ UINT itemCommandID,
		/* [in] */ UINT sender) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE dragDestinationActionMaskForDraggingInfo( 
		/* [in] */ IWebView *webView,
		/* [in] */ IDataObject *draggingInfo,
		/* [retval][out] */ WebDragDestinationAction *action) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE willPerformDragDestinationAction( 
		/* [in] */ IWebView *webView,
		/* [in] */ WebDragDestinationAction action,
		/* [in] */ IDataObject *draggingInfo) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE dragSourceActionMaskForPoint( 
		/* [in] */ IWebView *webView,
		/* [in] */ LPPOINT point,
		/* [retval][out] */ WebDragSourceAction *action) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE willPerformDragSourceAction( 
        /* [in] */ IWebView *webView,
        /* [in] */ WebDragSourceAction action,
        /* [in] */ LPPOINT point,
        /* [in] */ IDataObject *pasteboard,
        /* [retval][out] */ IDataObject **newPasteboard) { return E_NOTIMPL; }

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE contextMenuItemSelected( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *item,
		/* [in] */ IPropertyBag *element) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE hasCustomMenuImplementation( 
		/* [retval][out] */ BOOL *hasCustomMenus) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE trackCustomPopupMenu( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu,
		/* [in] */ LPPOINT point) { return E_NOTIMPL; }

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE measureCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *measureItem) { return E_NOTIMPL; }

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE drawCustomMenuItem( 
		/* [in] */ IWebView *sender,
		/* [in] */ void *drawItem) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE addCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE cleanUpCustomMenuDrawingData( 
		/* [in] */ IWebView *sender,
		/* [in] */ OLE_HANDLE hMenu) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE canTakeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward,
		/* [out] */ BOOL *result) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE takeFocus( 
		/* [in] */ IWebView *sender,
		/* [in] */ BOOL forward) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE registerUndoWithTarget( 
		/* [in] */ IWebUndoTarget *target,
		/* [in] */ BSTR actionName,
		/* [in] */ IUnknown *actionArg) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE removeAllActionsWithTarget( 
		/* [in] */ IWebUndoTarget *target) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE setActionTitle( 
		/* [in] */ BSTR actionTitle) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE undo() { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE redo() { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE canUndo( 
		/* [retval][out] */ BOOL *result) { return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE canRedo( 
		/* [retval][out] */ BOOL *result) { return E_NOTIMPL; }

    virtual HRESULT STDMETHODCALLTYPE printFrame( 
        /* [in] */ IWebView *webView,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE ftpDirectoryTemplatePath( 
        /* [in] */ IWebView *webView,
        /* [retval][out] */ BSTR *path) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE webViewHeaderHeight( 
        /* [in] */ IWebView *webView,
        /* [retval][out] */ float *result) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE webViewFooterHeight( 
        /* [in] */ IWebView *webView,
        /* [retval][out] */ float *result) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE drawHeaderInRect( 
        /* [in] */ IWebView *webView,
        /* [in] */ RECT *rect,
        /* [in] */ OLE_HANDLE drawingContext) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE drawFooterInRect( 
        /* [in] */ IWebView *webView,
        /* [in] */ RECT *rect,
        /* [in] */ OLE_HANDLE drawingContext,
        /* [in] */ UINT pageIndex,
        /* [in] */ UINT pageCount) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE webViewPrintingMarginRect( 
        /* [in] */ IWebView *webView,
        /* [retval][out] */ RECT *rect) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE canRunModal( 
        /* [in] */ IWebView *webView,
        /* [retval][out] */ BOOL *canRunBoolean) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE createModalDialog( 
        /* [in] */ IWebView *sender,
        /* [in] */ IWebURLRequest *request,
        /* [retval][out] */ IWebView **newWebView) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE runModal( 
        /* [in] */ IWebView *webView) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE isMenuBarVisible( 
        /* [in] */ IWebView *webView,
        /* [retval][out] */ BOOL *visible) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE setMenuBarVisible( 
        /* [in] */ IWebView *webView,
        /* [in] */ BOOL visible) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE runDatabaseSizeLimitPrompt( 
        /* [in] */ IWebView *webView,
        /* [in] */ BSTR displayName,
        /* [in] */ IWebFrame *initiatedByFrame,
        /* [retval][out] */ BOOL *allowed) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE paintCustomScrollbar( 
        /* [in] */ IWebView *webView,
        /* [in] */ HDC hDC,
        /* [in] */ RECT rect,
        /* [in] */ WebScrollBarControlSize size,
        /* [in] */ WebScrollbarControlState state,
        /* [in] */ WebScrollbarControlPart pressedPart,
        /* [in] */ BOOL vertical,
        /* [in] */ float value,
        /* [in] */ float proportion,
        /* [in] */ WebScrollbarControlPartMask parts) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE paintCustomScrollCorner( 
        /* [in] */ IWebView *webView,
        /* [in] */ HDC hDC,
        /* [in] */ RECT rect) { return E_NOTIMPL; }
};
