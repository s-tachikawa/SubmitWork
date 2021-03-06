//---------------------------------------------------------
// 
//	iruna_cube_texture.h
//	キューブテクスチャー管理クラス
//	作成日 6月28日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_CUBE_TEXTURE_H
#define IRUNA_CUBE_TEXTURE_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_surface.h"
#include "../Include/iruna_color4.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//=====================================================================
//
//	クラス名	:	CubeTexture
//	処理		:	キューブテクスチャ管理クラス
//	製作者		:	立川 翔野
//	作成日		:	2011/06/28	- 作成
//
//=====================================================================
class CubeTexture
{

//	プライベート	メンバ変数
private:
	LPDIRECT3DCUBETEXTURE9	texture;		// テクスチャ
	std::string				recoveryPath;	// テクスチャのパス

//	パブリック		メンバ関数
public:
	//--------------------------------------------------------------------
	// 
	//	処理	:	コンストラクタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/28	- 作成
	// 
	//--------------------------------------------------------------------
	CubeTexture();

	//--------------------------------------------------------------------
	// 
	//	処理	:	デストラクタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/28	- 作成
	// 
	//--------------------------------------------------------------------
	~CubeTexture();

	//--------------------------------------------------------------------
	// 
	//	処理	:	ファイルからキューブテクスチャを読み込む
	//	第1引数	:	[in] path		- ファイルへのパス
	//	第2引数	:	[in] color		- カラーキー、透過色の設定(デフォルトは0)
	//	第3引数	:	[in] mipLevel	- ミップマップレベル、0〜8を指定(デフォルトは1)
	//	第4引数	:	[in] filter		- フィルタリング(デフォルトはD3DX_FILTER_LINEAR)
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/28	- 作成
	// 
	//--------------------------------------------------------------------
	bool Load( std::string path, Color4 color = 0, U_INT mipLevel = 0, DWORD filter = D3DX_FILTER_LINEAR );

	//--------------------------------------------------------------------
	// 
	//	処理	:	テクスチャーの解放
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/28	- 作成
	// 
	//--------------------------------------------------------------------
	void Release();

	//--------------------------------------------------------------------
	// 
	//	処理	:	テクスチャの取得
	//	戻り値	:	テクスチャのポインタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/28	- 作成
	// 
	//--------------------------------------------------------------------
	const LPDIRECT3DCUBETEXTURE9& GetTexture();

	//--------------------------------------------------------------------
	// 
	//	処理	:	テクスチャのサーフェースの取得
	//	第1引数	:	[in] num		-	どの面のテクスチャサーフェースを取得するか
	//	第2引数	:	[out] surface	-	サーフェースを格納するクラスポインタ
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/28	- 作成
	// 
	//--------------------------------------------------------------------
	bool	GetSurface( U_INT num, Surface& surface );

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_CUBE_TEXTURE_H