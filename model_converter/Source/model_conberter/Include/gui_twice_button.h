//---------------------------------------------------------
// 
//	gui_twice_button.h
//	2回押してもとに戻るボタン
//	更新日 10月25日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----多重インクルード防止-------------------------------------------------*/
#ifndef GUI_TWICE_BUTTON_H
#define GUI_TWICE_BUTTON_H

/*----インクルード-------------------------------------------------*/
#include "../../iruna/Include/iruna.h"
#include "../Include/gui_button.h"

/*----ネームスペース-------------------------------------------------*/
using namespace iruna;
using namespace	graphics;
using namespace	io;

//=====================================================================
//
//	クラス名	:	TwiceButton
//	処理		:	2回押して元に戻るボタン
//
//=====================================================================
class TwiceButton
{

//	プライベート	メンバ変数
private:

	Texture*			buttonTex;		//	ボタン用テクスチャ
	bool				flag;			//	押下フラグ
	Sprite*				buttonSpr;		//	描画用スプライト
	math::Rect			rectSize;		//	ボタンの範囲
	math::Vector2		pos;			//	描画座標
	math::Vector2		size;			//	描画サイズ
	DeviceController	render;			//	レンダリングデバイス


public:

	//--------------------------------------------------------------------
	// 
	//	処理	:	コンストラクタ
	// 
	//--------------------------------------------------------------------
	TwiceButton();

	//--------------------------------------------------------------------
	// 
	//	処理	:	デストラクタ
	// 
	//--------------------------------------------------------------------
	~TwiceButton();

	//--------------------------------------------------------------------
	// 
	//	処理	:	ボタンの初期化
	//	第1引数 :	ボタンの座標
	//	第2引数 :	ボタンの大きさ
	// 
	//--------------------------------------------------------------------
	void Init( math::Vector2 in_pos, math::Vector2 in_size );

	//--------------------------------------------------------------------
	// 
	//	処理	:　ボタンの更新
	// 
	//--------------------------------------------------------------------
	void UpDate();

	//--------------------------------------------------------------------
	// 
	//	処理	:	ボタンの描画
	// 
	//--------------------------------------------------------------------
	void Draw( );

	//--------------------------------------------------------------------
	// 
	//	処理	:	現在どっちのボタンが押しているかを取得
	//	戻り値	:	結果フラグ　ture : 最初に設定したボタン　false :　2個目に設定したボタン 
	// 
	//--------------------------------------------------------------------
	bool GetState();

};

#endif	//	GUI_ONCE_BUTTON_H	end