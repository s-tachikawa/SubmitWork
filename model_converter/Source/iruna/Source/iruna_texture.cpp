//---------------------------------------------------------
// 
//	iruna_texture.cpp
//	テクスチャーの管理
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_texture.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
Texture::Texture()
	: texture( 0 )
{
	return;
}

// デストラクタ
Texture::~Texture()
{
	SafeRelease( texture );

	return;
}

// 画像ファイルからテクスチャを読み込む
bool Texture::Load( std::string path, Color4 color, U_INT mipLevel, DWORD filter )
{
	if( FAILED( D3DXCreateTextureFromFileEx(
				Device::GetDevice(),
				path.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				mipLevel,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				filter,
				filter,
				color,
				0,
				0,
				&texture ) ) )
		return false;

	recoveryPath	= path;

	return true;
}

// カラの動的テクスチャを作成する
bool Texture::Create( U_INT width, U_INT height, DWORD usage, U_INT mipLevel )
{
	return SUCCEEDED( D3DXCreateTexture( 
			Device::GetDevice(),
			width,
			height,
			mipLevel,
			usage,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&texture ) );
}

// テクスチャを解放する
void Texture::Release()
{
	SafeRelease( texture );
	recoveryPath.clear();

	return;
}

// テクスチャをロックし、アクセスするためのLockedRectを返す(動的テクスチャのみ)
bool Texture::Lock( LockedRect &rect, DWORD flag )
{
	return SUCCEEDED( texture->LockRect( 0, &rect, 0, flag ) );
}

// テクスチャをアンロックし、アクセスできないようにする(動的テクスチャのみ)
bool Texture::Unlock()
{
	return SUCCEEDED( texture->UnlockRect( 0 ) );
}

// テクスチャを取得
const LPDIRECT3DTEXTURE9& Texture::GetTexture()
{
	return texture;
}

// テクスチャのサイズを取得
POINT Texture::GetSize()
{
	POINT				temp;
	D3DSURFACE_DESC		desc;
	texture->GetLevelDesc( 0, &desc );

	temp.x	= desc.Width;
	temp.y	= desc.Height;

	return temp;
}

// サーフェスを取得
bool Texture::GetSurface( Surface& surface )
{
	LPDIRECT3DSURFACE9	temp	= 0;

	if( FAILED( texture->GetSurfaceLevel( 0, &temp ) ) )
	{
		return false;
	}

	surface	= temp;
		
	return true;

}


}	//	graphics	end
}	//	iruna		end