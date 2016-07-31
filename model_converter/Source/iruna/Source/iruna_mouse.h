//---------------------------------------------------------
// 
//	iruna_mouse.h
//	マウス関連
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_MOUSE_H
#define IRUNA_MOUSE_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_input_common.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace io
{

//=====================================================================
//
//	クラス名	:	Mouse
//	処理		:	マウス管理クラス
//	製作者		:	立川 翔野
//	作成日		:	2011/06/24	- 作成
//
//=====================================================================
class Mouse
{
// プライベート	メンバ変数
private:
	LPDIRECTINPUTDEVICE8	pDIDevice;	// マウスデバイス
	static DIMOUSESTATE2*	nowState;	// 現在の状態(静的メンバ変数)
	static DIMOUSESTATE2*	oldState;	// 前回の状態(静的メンバ変数)
	static POINT			position;	// マウスの位置(静的メンバ変数)
	static HWND				hWindow;	// カーソルの位置修正用(静的メンバ変数)

// パブリック		メンバ関数
public:
	//--------------------------------------------------------------------
	// 
	//	処理	:	コンストラクタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	Mouse();

	//--------------------------------------------------------------------
	// 
	//	処理	:	デストラクタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	~Mouse();

	//--------------------------------------------------------------------
	// 
	//	処理	:	マウスデバイスを作成する
	//	第1引数	:	[in] hWindow	- ウィンドウハンドル
	//	第2引数	:	[in] pDInput	- ダイレクトインプット
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	bool	Create( HWND hWindow, LPDIRECTINPUT8 pDInput );

	//--------------------------------------------------------------------
	// 
	//	処理	:	マウスデバイスを更新する
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	bool	Update();

	//--------------------------------------------------------------------
	// 
	//	処理	:	指定したキーの状態を返す(静的メンバ関数)
	//	第1引数	:	[in] key	- 調べたいキー
	//	戻り値	:	押されたキーの状態
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	static INPUT_STATE	GetState( MouseButton::Type key );

	//--------------------------------------------------------------------
	// 
	//	処理	:	マウスカーソルの位置を返す(静的メンバ関数)
	//	戻り値	:	マウスカーソルの位置
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/26	- 作成
	// 
	//--------------------------------------------------------------------
	static POINT	GetPosition();

	//--------------------------------------------------------------------
	// 
	//	処理	:	マウスカーソルのホイールの回転を取得(静的メンバ関数)
	//	戻り値	:	マウスカーソルのホイールの回転角
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/26	- 作成
	// 
	//--------------------------------------------------------------------
	static LONG		GetAngle();
};

}	//	io		end
}	//	iruna	end

#endif	//	IRUNA_MOUSE_H	end