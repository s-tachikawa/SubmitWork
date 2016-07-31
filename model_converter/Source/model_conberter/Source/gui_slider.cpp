//---------------------------------------------------------
// 
//	bar_icon.h
//	指定した長さでバーのアイコンを作成し、管理する
//	更新日 1月8日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード---------------------------------*/
#include "../Include/gui_slider.h"

//	コンストラクタ
BarIcon::BarIcon()
{
	valueMax	= 0;
	barTex = new Texture;
	barSpr = new Sprite;
	barTex->Load( "../Resource/texture/bar.png" );
	barSpr->SetSize( math::Vector2( 128, 2 ) );
	cur = new Sprite;
	cur->SetSize( math::Vector2( 20, 40 ) );
	cur->SetColor( Color4( 255, 255, 255, 255 ) );

	pos = math::Vector2( 0, 0 );
	curPos = math::Vector2( 0, -20 );
	return;
}

//	デストラクタ
BarIcon::~BarIcon()
{
	SafeDelete( barTex );
	SafeDelete( barSpr );
	SafeDelete( cur );
	return;
}

//	バーの初期化
void BarIcon::SetSliderMax( float max )
{

	valueMax	= max;
	curPos.x	= pos.x;
	return;
}

//	描画座標の指定
void BarIcon::SetPos( math::Vector2 setPos )
{
	pos = setPos;
	curPos = math::Vector2( setPos.x, setPos.y - 20 );
	//	バーを越えないようにする
	if( curPos.x > ( pos.x + 128 - 20.0f ) )
	{
		curPos.x = pos.x + 128.0f - 20.0f;
	}
	if( curPos.x < pos.x )
	{
		curPos.x = pos.x;
	}
	return;
}

//	バーの更新
void BarIcon::UpDate()
{
	//	マウスの座標を取得
	POINT temp = io::GetMousePosition();
	if( HitCursor() )
	{
		if( io::CheckMouseState( io::MouseButton::LEFT ) == io::INPUT_PUSH )
		{
			flag = true;
		}
		//	マウスがカーソルにあたっているなら色を変える
		cur->SetColor( Color4( 255, 0, 0, 255 ) );
	}
	else
	{
		cur->SetColor( Color4( 255, 255, 255, 255 ) );
	}

	if( io::CheckMouseState( io::MouseButton::LEFT ) == io::INPUT_PUSHED )
	{
		if( flag )
		{
			//	マウスがカーソルにあたっているなら色を変える
			cur->SetColor( Color4( 255, 0, 255, 255 ) );

			curPos = math::Vector2( ( float )temp.x - 8, curPos.y );
			//	バーを越えないようにする
			if( curPos.x > ( pos.x + 128 - 20.0f ) )
			{
				curPos.x = pos.x + 128.0f - 20.0f;
			}
			if( curPos.x < pos.x )
			{
				curPos.x = pos.x;
			}
		}
	}

	//	マウスが離されたら
	if( io::CheckMouseState( io::MouseButton::LEFT ) == io::INPUT_RELEASED )
	{
		flag = false;
		cur->SetColor( Color4( 255, 255, 255, 255 ) );
	}
	return;
}

//	カーソルとマウスポインタの当たり判定
bool BarIcon::HitCursor()
{
	POINT temp = io::GetMousePosition();
	if( temp.x > curPos.x && temp.y > curPos.y && 
		temp.x < ( curPos.x + 20) && temp.y < ( curPos.y + 40 ) )
	{
		return true;
	}

	return false;
}

//	バーの描画
void BarIcon::Draw()
{
	render.SetTexture( 0, barTex->GetTexture() );
	barSpr->Draw( pos );

	render.SetTexture( 0, NULL );
	cur->Draw( curPos );

	return;
}

//	バーの現在の量を取得
int BarIcon::GetValue()
{
	//バーとカーソルの位置で
	float tempPos = curPos.x - pos.x;

	float tempValue = ( float )( valueMax / ( 128.0f - 20.0f ) );

	tempValue = tempPos * tempValue;
	
	return ( int )tempValue;
}
void BarIcon::SetValue( float setValue )
{

	float tempValue = ( float )( ( 128.0f - 20.0f ) / valueMax);

	curPos.x = pos.x + ( tempValue *  setValue );

	return;
}