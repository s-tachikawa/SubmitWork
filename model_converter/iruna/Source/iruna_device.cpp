//---------------------------------------------------------
// 
//	iruna_device.cpp
//	デバイスの管理と生成
//	作成日 6月22日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Source/iruna_device.h"

/*----プリプロセッサディレクティブ---------------------------------*/
#ifdef _DEBUG
#pragma comment ( lib, "d3dx9d.lib"	)

#else
#pragma comment ( lib, "d3dx9.lib"	)

#endif

#pragma comment ( lib, "d3d9.lib"	)
#pragma comment ( lib, "d3dxof.lib"	)
#pragma comment ( lib, "dxguid.lib"	)
#pragma comment ( lib, "dxerr.lib"  )


/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// 静的メンバ変数の実体
LPDIRECT3DDEVICE9	Device::pD3dDevice	= 0;
HRESULT				Device::deviceState	= 0;

//	コンストラクタ
Device::Device()
	: pD3d( 0 )
{
	// Direct3Dの初期化
	memset( &d3dpp, 0, sizeof( D3DPRESENT_PARAMETERS ) );
	pD3d		= Direct3DCreate9( D3D_SDK_VERSION );
	return;
}

//	デストラクタ
Device::~Device()
{
	SafeRelease( pD3dDevice );
	SafeRelease( pD3d		);

	return;
}

// 初期設定する
void Device::InitSetting()
{
	pD3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	//テクスチャ成分の設定
	pD3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,	D3DTOP_MODULATE );
	pD3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE );
	pD3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE );

	//アルファ成分の設定
	pD3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	D3DTOP_MODULATE );
	pD3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );
	pD3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE );

	//テクスチャ成分の設定
	pD3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,	D3DTOP_MODULATE );
	pD3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG1,	D3DTA_TEXTURE );
	pD3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG2,	D3DTA_DIFFUSE );

	//アルファ成分の設定
	pD3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,	D3DTOP_MODULATE );
	pD3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );
	pD3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE );

	// 標準的な色の設定
	pD3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	pD3dDevice->SetRenderState( D3DRS_BLENDOP,			D3DBLENDOP_ADD );
	pD3dDevice->SetRenderState( D3DRS_SRCBLEND,			D3DBLEND_SRCALPHA );
	pD3dDevice->SetRenderState( D3DRS_DESTBLEND,		D3DBLEND_INVSRCALPHA );

	//zバッファを使う
	pD3dDevice->SetRenderState( D3DRS_ZENABLE, true );
	pD3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, true );

	pD3dDevice->SetRenderState(	D3DRS_LIGHTING,	false );

	return;
}

// プレゼントパラメータを設定する
bool Device::SetPresentParameters( U_LONG width, U_LONG height, bool mode )
{
	
	if( !pD3d )
	{
		//	Direct3Dが生成失敗している
		return false;
	}

	D3DDISPLAYMODE	DisplayMode;
	pD3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &DisplayMode );

	d3dpp.BackBufferWidth			= width;	//	ﾌﾙｽｸﾘｰﾝ時は解像度を指定しなければならない
	d3dpp.BackBufferHeight			= height;	//	〃
	d3dpp.BackBufferFormat			= DisplayMode.Format;
	d3dpp.BackBufferCount			= 1;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed					= mode;
	d3dpp.EnableAutoDepthStencil	= true;	
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	return true;
}

// デバイスを作成する
bool Device::Create( HWND hWindow )
{
	//	ハードかソフトウェアを調べるためのテーブル
	const DWORD		 VERTEX_SHADER_TYPE[] = {
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING
	};
	//	HALかREFを調べるためのテーブル
	const D3DDEVTYPE PIXEL_SHADER_TYPE[] = {
		D3DDEVTYPE_HAL,
		D3DDEVTYPE_REF
	};

	if( !pD3d )
	{
		//	Direct3Dが作成されていません
		return false;
	}

	// 以下の順に作成を試みる、成功したらそこで終了
	//	① VertexShader：HARDWARE	PixelShader：HARDWARE
	//	② VertexShader：SOFTWARE	PixelShader：HARDWARE
	//	③ VertexShader：HARDWARE	PixelShader：SOFTWARE
	//	④ VertexShader：SOFTWARE	PixelShader：SOFTWARE
	for( int i = 0; i < 2; i++ )
		for( int k = 0; k < 2; k++ )
			if( SUCCEEDED( pD3d->CreateDevice( 
						D3DADAPTER_DEFAULT,
						PIXEL_SHADER_TYPE[ i ],
						hWindow,
						VERTEX_SHADER_TYPE[ k ] | D3DCREATE_MULTITHREADED,
						&d3dpp,
						&pD3dDevice	) ) )
			{
				InitSetting();

				return true;
			}

	return false;
}

// 指定した裏画面をクリアする(静的メンバ関数)
bool Device::ClearBackBuffer( DWORD flag )
{
	return SUCCEEDED( pD3dDevice->Clear(
				0,
				0,
				flag,
				0xFF000000,	// A R G B
				1.0f,
				0 ) );
}

// 裏画面をクリアし、描画を開始する(静的メンバ関数)
bool Device::ClearScreen()
{
	bool	clear = SUCCEEDED( pD3dDevice->Clear(
				0,
				0,
				D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				0xFF000000,	// A R G B
				1.0f,
				0 ) );

	bool	begin = SUCCEEDED( pD3dDevice->BeginScene() );

	return ( clear && begin );
}

// 描画を終了し、裏画面に描いたものを表画面へ転送(静的メンバ関数)
bool Device::SwapScreen()
{
	bool	end = SUCCEEDED( pD3dDevice->EndScene() );

	deviceState = pD3dDevice->Present( 0, 0, 0, 0 );

	return ( end && SUCCEEDED( deviceState ) );
}

// デバイスを取得する(静的メンバ関数)
LPDIRECT3DDEVICE9& Device::GetDevice()
{
	return pD3dDevice;
}

// デバイスを取得する(静的メンバ関数)
HRESULT Device::GetDeviceState()
{
	return deviceState;
}

}//	graphics	end
}//	iruna		end
