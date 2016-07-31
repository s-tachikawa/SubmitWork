//---------------------------------------------------------
// 
//	gui_twice_button.h
//	2回押してもとに戻るボタン
//	更新日 10月25日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/gui_twice_button.h"

//	コンストラクタ
TwiceButton::TwiceButton()
{
	buttonTex = new Texture[ 2 ];
	buttonTex[ 0 ].Load( "../Resource/texture/再生ボタン.png" );
	buttonTex[ 1 ].Load( "../Resource/texture/停止ボタン.png" );
	buttonSpr = new Sprite;
	buttonSpr->SetSize( math::Vector2( 30, 30 ) );
	flag = false;	//	最初はストップボタンが押されている。


	return;
}

//	デストラクタ
TwiceButton::~TwiceButton()
{
	SafeArrayDelete( buttonTex );
	SafeDelete( buttonSpr );

	return;
}

//	初期化
void TwiceButton::Init( math::Vector2 in_pos, math::Vector2 in_size )
{
	pos = in_pos;
	size = in_size;
	rectSize = math::Rect(	( int )pos.x, 
							( int )pos.y, 
							( int )pos.x + size.x,
							( int )pos.y + size.y );
	
	return;
}

//	更新
void TwiceButton::UpDate()
{

	POINT mouse = io::GetMousePosition();
	INPUT_STATE mouseState = CheckMouseState( MouseButton::LEFT );

	if( rectSize.top	< mouse.y && 
		rectSize.left	< mouse.x &&
		rectSize.bottom	> mouse.y &&
		rectSize.right	> mouse.x	)
	{
		buttonSpr->SetColor( Color4( 200, 0, 0, 255 ) );

		if( mouseState ==  io::INPUT_RELEASED )
		{
			flag = !flag;
		}

		return;
	}
	else
	{
		buttonSpr->SetColor( Color4( 255, 255, 255, 255 ) );
	}

	return;
}

//	描画
void TwiceButton::Draw()
{

	if( flag )
	{
		render.SetTexture( 0, buttonTex[ 0 ].GetTexture() );
		buttonSpr->Draw( pos );
	}
	else
	{
		render.SetTexture( 0, buttonTex[ 1 ].GetTexture() );
		buttonSpr->Draw( pos );
	}
	
	return;
}

//	ボタンの状態を取得
bool TwiceButton::GetState()
{
	return flag;
}
