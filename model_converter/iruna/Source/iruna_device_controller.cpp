//---------------------------------------------------------
// 
//	iruna_device_controller.h
//	デバイスの間接操作
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_device_controller.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	// 静的メンバ変数の実体
LPDIRECT3DDEVICE9*	DeviceController::ppD3dDevice	= 0;

// コンストラクタ
DeviceController::DeviceController()
{
	if( !ppD3dDevice )
		ppD3dDevice	= &( Device::GetDevice() );

	return;
}

// デストラクタ
DeviceController::~DeviceController()
{
	return;
}

// 描画を実行(頂点データはソフトウェア側版)
bool DeviceController::DrawPrimitiveUp( Primitive::Type type, U_LONG polygonCnt, const void *vertexBuffer, U_LONG vertexStride )
{
	return SUCCEEDED( ( *ppD3dDevice )->DrawPrimitiveUP( 
				static_cast< D3DPRIMITIVETYPE >( type ),
				polygonCnt,
				vertexBuffer,
				vertexStride ) );
}

// 描画を実行(頂点データはハードウェア側版)
bool DeviceController::DrawPrimitive( Primitive::Type type, U_LONG polygonCnt )
{
	return SUCCEEDED( ( *ppD3dDevice )->DrawPrimitive( 
				static_cast< D3DPRIMITIVETYPE >( type ),
				0,
				polygonCnt ) );
}

// インデックスを使った描画を実行(頂点データはハードウェア側版)
bool DeviceController::DrawIndexPrimitive( Primitive::Type type, U_LONG vertexCnt, U_LONG polygonCnt )
{
	return SUCCEEDED( ( *ppD3dDevice )->DrawIndexedPrimitive(
				static_cast< D3DPRIMITIVETYPE >( type ),
				0,
				0,
				vertexCnt,
				0,
				polygonCnt ) );
}

// Zバッファに描きこむか描きこまないかの設定する
void DeviceController::SetZBufferState( bool flag )
{
	( *ppD3dDevice )->SetRenderState( D3DRS_ZENABLE,		flag );
	( *ppD3dDevice )->SetRenderState( D3DRS_ZWRITEENABLE,	flag );

	return;
}

// デバイスに変換行列をセットする
bool DeviceController::SetTransform( D3DTRANSFORMSTATETYPE target, math::Matrix matrix )
{
	return SUCCEEDED( ( *ppD3dDevice )->SetTransform( target, &matrix ) );
}

// デバイスにテクスチャをセットする
bool DeviceController::SetTexture( U_LONG stage, LPDIRECT3DTEXTURE9 texture )
{
	return SUCCEEDED( ( *ppD3dDevice )->SetTexture( stage, texture ) );
}

// デバイスにマテリアルをセットする
bool DeviceController::SetMaterial( D3DMATERIAL9 material )
{
	return SUCCEEDED( ( *ppD3dDevice )->SetMaterial( &material ) );
}

// レンダーステートの設定
bool DeviceController::SetRenderState(  D3DRENDERSTATETYPE type ,U_LONG val  )
{
	return SUCCEEDED( ( *ppD3dDevice)->SetRenderState( type , val ) );
}


}	//	graphics	end
}	//	iruna		end

/*----グローバル関数 定義----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	指定した裏画面をクリアする
bool ClearBackBuffer(  DWORD flag )
{
	return Device::ClearBackBuffer( flag );
}

//	裏画面をクリアし、描画を開始する
bool ClearScreen()
{
	return Device::ClearScreen();
}

//	描画を終了し、裏画面に描いたものを表画面へ転送
bool SwapScreen()
{
	return Device::SwapScreen();
}

}	//	graphics	end
}	//	iruna		end