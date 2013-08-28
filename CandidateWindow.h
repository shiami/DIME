//
//
// Derived from Microsoft Sample IME by Jeremy '13,7,17
//
//



#pragma once

#include "private.h"
#include "BaseWindow.h"
#include "ShadowWindow.h"
#include "ScrollBarWindow.h"
#include "BaseStructure.h"
#include "Define.h"

enum CANDWND_ACTION
{
    CAND_ITEM_SELECT
};

typedef HRESULT (*CANDWNDCALLBACK)(void *pv, enum CANDWND_ACTION action);

class CCandidateWindow : public CBaseWindow
{
public:
    CCandidateWindow(_In_ CANDWNDCALLBACK pfnCallback, _In_ void *pv, _In_ CCandidateRange *pIndexRange, _In_ BOOL isStoreAppMode);
    virtual ~CCandidateWindow();

    BOOL _Create(_In_ UINT wndWidth, _In_ UINT fontSize, _In_opt_ HWND parentWndHandle);

	void _SetCandStringLength(_In_ UINT wndWidth) { _wndWidth = wndWidth; } // in chararacters
	UINT _GetWidth() { return _cxTitle + GetSystemMetrics(SM_CXVSCROLL) * 3/2  + CANDWND_BORDER_WIDTH *2;}


    void _Move(int x, int y);
	void _OnTimerID(UINT_PTR timerID);
    void _Show(BOOL isShowWnd);

	VOID _SetNumberColor(_In_ COLORREF crColor, _In_ COLORREF crBkColor);
    VOID _SetTextColor(_In_ COLORREF crColor, _In_ COLORREF crBkColor);
	VOID _SetSelectedTextColor(_In_ COLORREF crColor, _In_ COLORREF crBkColor);
    VOID _SetFillColor(_In_ COLORREF fiColor);

    LRESULT CALLBACK _WindowProcCallback(_In_ HWND wndHandle, UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
    void _OnPaint(_In_ HDC dcHandle, _In_ PAINTSTRUCT *pps);
    void _OnLButtonDown(POINT pt);
    void _OnLButtonUp(POINT pt);
    void _OnMouseMove(POINT pt);
    void _OnVScroll(DWORD dwSB, _In_ DWORD nPos);

    void _AddString(_Inout_ CCandidateListItem *pCandidateItem, _In_ BOOL isAddFindKeyCode);
    void _ClearList();
    UINT _GetCount() { return _candidateList.Count(); }
    UINT _GetSelection()  { return _currentSelection;}
    void _SetScrollInfo(_In_ int nMax, _In_ int nPage);

    DWORD _GetCandidateString(_In_ int iIndex, _Outptr_result_maybenull_z_ const WCHAR **ppwchCandidateString);
    DWORD _GetSelectedCandidateString(_Outptr_result_maybenull_ const WCHAR **ppwchCandidateString);

    BOOL _MoveSelection(_In_ int offSet, _In_ BOOL isNotify);
    BOOL _SetSelection(_In_ int iPage, _In_ BOOL isNotify);
    void _SetSelection(_In_ int nIndex);
    BOOL _MovePage(_In_ int offSet, _In_ BOOL isNotify);
    BOOL _SetSelectionInPage(int nPos);

    HRESULT _GetPageIndex(UINT *pIndex, _In_ UINT uSize, _Inout_ UINT *puPageCnt);
    HRESULT _SetPageIndex(UINT *pIndex, _In_ UINT uPageCnt);
    HRESULT _GetCurrentPage(_Inout_ UINT *pCurrentPage);
    HRESULT _GetCurrentPage(_Inout_ int *pCurrentPage);

private:
    void _HandleMouseMsg(_In_ UINT mouseMsg, _In_ POINT point);
    void _DrawList(_In_ HDC dcHandle, _In_ UINT iIndex, _In_ RECT *prc);
    void _DrawBorder(_In_ HWND wndHandle, _In_ int cx);
    BOOL _SetSelectionOffset(_In_ int offSet);
    BOOL _AdjustPageIndexForSelection();
    HRESULT _CurrentPageHasEmptyItems(_Inout_ BOOL *pfHasEmptyItems);

	// LightDismiss feature support, it will fire messages lightdismiss-related to the light dismiss layout.
    void _FireMessageToLightDismiss(_In_ HWND wndHandle, _In_ WINDOWPOS *pWndPos);

    BOOL _CreateMainWindow(_In_opt_ HWND parentWndHandle);
    BOOL _CreateBackGroundShadowWindow();
    BOOL _CreateVScrollWindow();

    HRESULT _AdjustPageIndex(_Inout_ UINT & currentPage, _Inout_ UINT & currentPageIndex);

    void _ResizeWindow();
    void _DeleteShadowWnd();
    void _DeleteVScrollBarWnd();

    friend COLORREF _AdjustTextColor(_In_ COLORREF crColor, _In_ COLORREF crBkColor);

private:
    INT _currentSelection;
    CTSFTTSArray<CCandidateListItem> _candidateList;
    CTSFTTSArray<UINT> _PageIndex;

	COLORREF _crNumberColor;
    COLORREF _crNumberBkColor;
    COLORREF _crTextColor;
    COLORREF _crBkColor;
	COLORREF _crSelectedTextColor;
    COLORREF _crSelectedBkColor;
    HBRUSH _brshBkColor;

    TEXTMETRIC _TextMetric;
    int _cyRow;
    int _cxTitle;
    UINT _wndWidth;
	UINT _fontSize;

    CCandidateRange* _pIndexRange;

    CANDWNDCALLBACK _pfnCallback;
    void* _pObj;

    CShadowWindow* _pShadowWnd;
    CScrollBarWindow* _pVScrollBarWnd;

    BOOL _dontAdjustOnEmptyItemPage;
    BOOL _isStoreAppMode;

	BYTE _animationStage;

	int _x;
	int _y;
};
