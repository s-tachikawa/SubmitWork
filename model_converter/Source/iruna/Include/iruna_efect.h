//---------------------------------------------------------
// 
//	iruna_efect.h
//	シェーダーファイル管理クラス
//	作成日 6月25日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_EFECT_H
#define IRUNA_EFECT_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//=====================================================================
//
//	クラス名	:	Effect
//	処理		:	シェーダーの管理
//	製作者		:	立川 翔野
//	作成日		:	2011/06/25	- 作成
//
//=====================================================================
class Effect
{
//	プライベート	メンバ変数
private:
	LPD3DXEFFECT		effect;			// エフェクト
	std::string			recoveryPath;	// ファイルパス

//	プライベート	メンバ変数
public:
	//--------------------------------------------------------------------
	// 
	//	処理	:	コンストラクタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	Effect();

	//--------------------------------------------------------------------
	// 
	//	処理	:	デストラクタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	~Effect();

	//--------------------------------------------------------------------
	// 
	//	処理	:	エフェクトファイルの読み込み
	//	第1引数	:	[in] path	- エフェクトファイルのパス
	//	第2引数	:	[in] flag	- コンパイルされているかどうかのフラグ
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool Create( std::string path, bool flag );

	//--------------------------------------------------------------------
	// 
	//	処理	:	シェーダーのバージョンチェック
	//	第1引数	:	[in] vertex_num	- 調べるバーテクスシェーダーのバージョン
	//	第2引数	:	[in] pixel_num	- 調べるピクセルシェーダーのバージョン
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool VersionCheck( U_INT vertex_num, U_INT pixel_num );

	//--------------------------------------------------------------------
	// 
	//	処理	:	テクニックのセット
	//	第1引数	:	[in] path	- シェーダー内のテクニックのパス
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetTechnique( std::string path );

	//--------------------------------------------------------------------
	// 
	//	処理	:	行列のセット
	//	第1引数	:	[in] path	- シェーダー内の行列変数のパス
	//	第2引数	:	[in] flag	- セットする行列
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetMatrix( std::string path,  math::Matrix mat );

	//--------------------------------------------------------------------
	// 
	//	処理	:	行列配列のセット
	//	第1引数	:	[in] path	- シェーダー内の行列変数のパス
	//	第2引数	:	[in] mat	- セットする行列
	//	第3引数	:	[in] size	- 配列のサイズ
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetMatrixArayy( std::string path, math::Matrix* mat, U_LONG size );

	//--------------------------------------------------------------------
	// 
	//	処理	:	float4型変数のセット
	//	第1引数	:	[in] path	- シェーダー内のfloat4型変数のパス
	//	第2引数	:	[in] flag	- セットするfloat4型の変数
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetVector( std::string path,  math::Vector4 vec );

	//--------------------------------------------------------------------
	// 
	//	処理	:	float3型変数のセット
	//	第1引数	:	[in] path	- シェーダー内のfloat3型変数のパス
	//	第2引数	:	[in] flag	- セットするfloat3型の変数
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetVector( std::string path,  math::Vector3 vec );

	//--------------------------------------------------------------------
	// 
	//	処理	:	float2型変数のセット
	//	第1引数	:	[in] path	- シェーダー内のfloat2型変数のパス
	//	第2引数	:	[in] flag	- セットするfloat2型の変数
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetVector( std::string path,  math::Vector2 vec );

	//--------------------------------------------------------------------
	// 
	//	処理	:	float2型変数のセット
	//	第1引数	:	[in] path		- シェーダー内のfloat4型配列のパス
	//	第2引数	:	[in] vecArayy	- セットするfloat4型の配列ポインタ
	//	第3引数	:	[in] size		- セットするfloat4型のサイズ
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetVectorArayy( std::string path, math::Vector4* vecArayy ,U_LONG size  );
	
	//--------------------------------------------------------------------
	// 
	//	処理	:	float型変数のセット
	//	第1引数	:	[in] path	- シェーダー内のfloat型変数のパス
	//	第2引数	:	[in] flag	- セットするfloat型の変数
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetFloat( std::string path,  float val );

	//--------------------------------------------------------------------
	// 
	//	処理	:	テクスチャーのセット
	//	第1引数	:	[in] path	- シェーダー内のテクスチャー変数のパス
	//	第2引数	:	[in] flag	- セットするテクスチャー
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetTexture( std::string path, const LPDIRECT3DTEXTURE9 texture );

	//--------------------------------------------------------------------
	// 
	//	処理	:	キューブマップテクスチャのセット
	//	第1引数	:	[in] path	- シェーダー内のテクスチャー変数のパス
	//	第2引数	:	[in] flag	- セットするテクスチャー
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/30	- 作成
	// 
	//--------------------------------------------------------------------
	bool SetTexture( std::string path, const LPDIRECT3DCUBETEXTURE9 texture );

	//--------------------------------------------------------------------
	// 
	//	処理	:	シェーダー内の値が変化させたことをデバイスに伝える
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool CommitChanges();

	//--------------------------------------------------------------------
	// 
	//	処理	:	シェーダーの開始
	//	第1引数	:	[in] path	- シェーダー内にあるパスの数
	//	第2引数	:	[in] flag	- デバイスステートを保持するか
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/25	- 作成
	// 
	//--------------------------------------------------------------------
	bool Begin( U_INT* num, DWORD flag );

	//--------------------------------------------------------------------
	// 
	//	処理	:	シェーダーの指定したパスの開始
	//	第1引数	:	[in] path	- シェーダー内のテクスチャー変数のパス
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/23	- 作成
	// 
	//--------------------------------------------------------------------
	bool BeginPass( U_INT pass );

	//--------------------------------------------------------------------
	// 
	//	処理	:	シェーダーの終了
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/23	- 作成
	// 
	//--------------------------------------------------------------------
	bool End();

	//--------------------------------------------------------------------
	// 
	//	処理	:	パスの終了
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/23	- 作成
	// 
	//--------------------------------------------------------------------
	bool EndPass();

};


}	//	graphics	end
}	//	iruna		end



#endif	//	IRUNA_EFECT_H	end