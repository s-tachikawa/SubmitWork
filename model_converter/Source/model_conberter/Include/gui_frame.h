//---------------------------------------------------------
// 
//	gui_frame.h
//	GUI上のボタン全てを管理する
//	作成日 10月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----多重インクルード防止-------------------------------------------------*/
#ifndef GUI_FRAME_H
#define GUI_FRAME_H

/*----インクルード-------------------------------------------------*/
#include "../../iruna/Include/iruna.h"
#include "../Include/gui_button.h"

/*----ネームスペース-------------------------------------------------*/
using namespace iruna;
using namespace core;
using namespace	graphics;
using namespace io;

class GuiFrame
{
private:

	//	GUIフレーム系
	Texture*	texture;
	Sprite*		sprite;

	//	カーソル系
	Texture*		cursor;
	Sprite*			curSprite;

	//	ボタン系
	Sprite*			buttonSprite;
	GuiButton*		button;
	int				type;

	DeviceController render;

public:

	//--------------------------------------------------------------------
	// 
	//	処理	:	コンストラクタ
	// 
	//--------------------------------------------------------------------
	GuiFrame();

	//--------------------------------------------------------------------
	// 
	//	処理	:	デストラクタ
	// 
	//--------------------------------------------------------------------
	~GuiFrame();

	//--------------------------------------------------------------------
	// 
	//	処理	:	フレームの更新
	// 
	//--------------------------------------------------------------------
	void	UpDate();

		//--------------------------------------------------------------------
	// 
	//	処理	:	フレームの描画
	// 
	//--------------------------------------------------------------------
	void	Draw();

	//--------------------------------------------------------------------
	// 
	//	処理	:	指定したボタンの構造体を取得
	//	第1引数 :	取得したいボタン番号
	//	戻り値	:	ボタン構造体
	// 
	//--------------------------------------------------------------------
	int 	GetButtonState( int button_type );
	

};


#endif	//	GUI_FRAME_H	end