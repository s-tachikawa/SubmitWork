//---------------------------------------------------------
// 
//	gui_button.h
//	GUI上のボタンの管理
//	作成日 10月21日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード-------------------------------------------------*/
#include "../Include/gui_button.h"

/*----グローバル関数宣言-------------------------------------------------*/
extern void PushButton( GuiButton& button );		//	1回押したらすぐ戻るボタン

/*----グローバル変数宣言-------------------------------------------------*/
// ボタンの処理関数テーブル
GuiButton::ButtonFunc ButtonFouncTable[] =
{
	PushButton,
	PushButton,
	PushButton,

};

//	押すボタンの更新( グローバル関数 )
void PushButton( GuiButton& button )
{
	button.state = GuiButton::NORMAL;

	POINT mouse = io::GetMousePosition();
	INPUT_STATE mouseState = CheckMouseState( MouseButton::LEFT );

	if( button.size.top	< mouse.y && 
		button.size.left	< mouse.x &&
		button.size.bottom	> mouse.y &&
		button.size.right	> mouse.x	)
	{
		button.state = GuiButton::HIT;

		if( mouseState == INPUT_PUSH || mouseState ==  INPUT_PUSHED )
		{
			button.state = GuiButton::PUSH;
		}

		return;
	}

	return;
}

// ボタンの初期化
void GuiButton::Init()
{
	this->func = ButtonFouncTable[ type ];

	return;
}