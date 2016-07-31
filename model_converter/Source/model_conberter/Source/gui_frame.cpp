//---------------------------------------------------------
// 
//	gui_frame.cpp
//	GUI上の全ボタンを管理する
//	作成日 10月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/gui_frame.h"

/*----グローバル変数定義-------------------------------------------------*/

//	ボタンサイズ
const math::Vector2 ButtonSize[] = 
{
	math::Vector2( 150, 50 ),	//	ModelButton
	math::Vector2( 150, 50 ),	//	TextureButton
	math::Vector2( 150, 50 ),	//	SaveButton
};

// ボタンの座標
const math::Vector2 ButtonPostion[] = 
{
	math::Vector2( 620, 20 ),	//	ModelButton
	math::Vector2( 620, 120 ),	//	TextureButton
	math::Vector2( 620, 400 ),	//	SaveButton
};

// コンストラクタ
GuiFrame::GuiFrame()
	:	texture( NULL ),
		sprite( NULL ),
		button( NULL )
{
	texture = new Texture;
	sprite = new Sprite;

	//GUIフレーム系
	texture->Load( "../Resource/texture/GuiFrame.png" );
	sprite->SetSize( math::Vector2( 200, 700 ));
	
	//	GUIボタン系
	button = new GuiButton[ GuiButton::BUTTON_MAX ];

	button[ GuiButton::MODEL ].texture		= new Texture;
	button[ GuiButton::TEXTURE ].texture	= new Texture;
	button[ GuiButton::SAVE ].texture		= new Texture;


	
	button[ GuiButton::MODEL ].texture->Load( "../Resource/texture/Model.png" );
	button[ GuiButton::TEXTURE ].texture->Load( "../Resource/texture/Texture.png" );
	button[ GuiButton::SAVE ].texture->Load( "../Resource/texture/Save.png" );
	
	buttonSprite = new Sprite;

	for( int i = 0; i < GuiButton::BUTTON_MAX; i++ )
	{
		button[ i ].size.top	= ( long )ButtonPostion[ i ].y;
		button[ i ].size.left	= ( long )ButtonPostion[ i ].x;
		button[ i ].size.bottom	= ( long )ButtonPostion[ i ].y + ( long )ButtonSize[ i ].y;
		button[ i ].size.right	= ( long )ButtonPostion[ i ].x + ( long )ButtonSize[ i ].x;
		button[ i ].state = GuiButton::NORMAL;
		button[ i ].type = i;
		button[ i ].Init();
	}
	
	//　GUIカーソル系
	cursor = new Texture;
	curSprite = new Sprite;
	cursor->Load( "../Resource/texture/cursor.png" );

	//	ボタン押下判定
	type		= -1;
	

	return;
}

//	デストラクタ
GuiFrame::~GuiFrame()
{
	if( texture != NULL )
		SafeDelete( texture );

	if( sprite != NULL )
		SafeDelete( sprite );
	if( buttonSprite != NULL )
		SafeDelete( buttonSprite );

	for( int i = 0;i < GuiButton::BUTTON_MAX; i++ )
	{
		if( button[ i ].texture != NULL )
			SafeDelete( button[ i ].texture );
	}
	if( button != NULL )
		SafeDelete( button );

	if( cursor != NULL )
		SafeDelete( cursor );

	if( curSprite != NULL )
		SafeDelete( curSprite );


	return;
}
//	GUIの更新
void GuiFrame::UpDate()
{
	// ボタンの更新
	for( int i = 0; i < GuiButton::BUTTON_MAX; i++ )
	{
		button[ i ].func.UpDate( button[ i ] );
	}

	return;
}

// GUIの描画
void GuiFrame::Draw()
{

	// GUIフレーム系
	render.SetTexture( 0, texture->GetTexture() );
	sprite->Draw( math::Vector2( 600, 0 ) );

	//　GUIボタン系
	for( int i = 0; i < GuiButton::BUTTON_MAX; i++ )
	{
		
		render.SetTexture( 0, button[ i ].texture->GetTexture() );
		buttonSprite->SetSize( ButtonSize[ i ] );
		buttonSprite->Draw( ButtonPostion[ i ] );
		
	

		//	GUIカーソル系
		if( button[ i ].state == GuiButton::HIT || 
			button[ i ].state == GuiButton::PUSH)
		{
			if( button[ i ].state == GuiButton::PUSH )
				curSprite->SetColor( Color4( 250, 0, 250 ) );

			if( button[ i ].state == GuiButton::HIT )
				curSprite->SetColor( Color4( 250, 0, 0 ) );


			render.SetTexture( 0, cursor->GetTexture() );
			curSprite->SetSize( ButtonSize[ i ] );
			curSprite->Draw( ButtonPostion[ i ] );

		}
	}
	

	return;
}

// 指定したボタンの押下を取得する
int GuiFrame::GetButtonState( int button_type )
{
	return button[ button_type ].state;
}