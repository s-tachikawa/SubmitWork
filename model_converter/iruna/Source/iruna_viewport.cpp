//---------------------------------------------------------
// 
//	iruna_viewport.cpp
//	ビューポート関連
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_viewport.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	// コンストラクタ
Viewport::Viewport()
{
	memset( &viewport, 0, sizeof( D3DVIEWPORT9 ) );

	return;
}

// コピーコンストラクタ
Viewport::Viewport( const Viewport& another )
	: viewport( another.viewport ) 
{
	return;
}

// デストラクタ
Viewport::~Viewport()
{
	return;
}

// ビューポートの大きさを指定する
void Viewport::SetSize( U_INT x, U_INT y, U_INT width, U_INT height )
{
	viewport.X		= x;
	viewport.Y		= y;
	viewport.Width	= width;
	viewport.Height	= height;

	return;
}

// ビューポートの大きさを指定する(矩形版)
void Viewport::SetSize( math::Rect rect )
{
	SetSize( rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top );

	return;
}

// ビューポートをデバイスにセット
bool Viewport::SetViewport()
{
	return SUCCEEDED( Device::GetDevice()->SetViewport( &viewport ) );
}

// 代入演算子オーバーロード、D3DVIEWPORT9をつっこめるように
Viewport& Viewport::operator =( D3DVIEWPORT9 setViewport )
{
	viewport	= setViewport;

	return *this;
}

}	// graphics	end
}	// white	end

/*----関数 定義----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// デバイスから現在セットされているビューポートを取得
bool GetViewport( Viewport& viewport )
{
	D3DVIEWPORT9	temp;

	bool reslut = SUCCEEDED( Device::GetDevice()->GetViewport( &temp ) );

	viewport	= temp;

	return reslut;
}
}	//	graphics	end
}	//	iruna		end