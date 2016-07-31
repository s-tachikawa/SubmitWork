//---------------------------------------------------------
// 
//	iruna_efect.cpp
//	シェーダーファイル管理クラス
//	作成日 6月25日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_efect.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	コンストラクタ
Effect::Effect()
	:	effect( 0 )
{
	return;
}

//	デストラクタ
Effect::~Effect()
{
	SafeRelease( effect );
}

//	エフェクトの読み込み
bool Effect::Create( std::string path, bool flag )
{
	if( FAILED( D3DXCreateEffectFromFile(
					Device::GetDevice(),
					path.c_str(),
					0,
					0,
					flag,
					0,
					&effect,
					0 ) ) )
		return false;

	
	recoveryPath	= path;

	return true;
}
//	シェーダーのバージョンチェック
bool Effect::VersionCheck( U_INT vertex_num, U_INT pixel_num )
{
	D3DCAPS9 caps;
	Device::GetDevice()->GetDeviceCaps( &caps );

	return  caps.VertexShaderVersion	>= D3DVS_VERSION( vertex_num, 0 ) &&
			caps.PixelShaderVersion		>= D3DPS_VERSION( pixel_num, 0 );
}

//	テクニックのセット
bool Effect::SetTechnique( std::string path )
{
	return SUCCEEDED( effect->SetTechnique( path.c_str() ) );
}

//	行列のセット
bool Effect::SetMatrix( std::string path,  math::Matrix mat )
{
	return SUCCEEDED( effect->SetMatrix( path.c_str(), &mat ) );
}

// 行列の配列セット
bool Effect::SetMatrixArayy(std::string path, iruna::math::Matrix* mat, iruna::U_LONG size)
{
	return SUCCEEDED( effect->SetMatrixArray( path.c_str(), mat, size ) );
}

//	float4型変数のセット
bool Effect::SetVector( std::string path,  math::Vector4 vec )
{
	return SUCCEEDED( effect->SetVector( path.c_str(), &vec ) );
}

//	float3型変数のセット
bool Effect::SetVector( std::string path,  math::Vector3 vec )
{
	math::Vector4 temp = math::Vector4( vec.x, vec.y, vec.z, 0 );

	return SUCCEEDED( effect->SetVector( path.c_str(), &temp ) );
}

//	float2型変数のセット
bool Effect::SetVector( std::string path,  math::Vector2 vec )
{
	math::Vector4 temp = math::Vector4( vec.x, vec.y, 0, 0 );
	return SUCCEEDED( effect->SetVector( path.c_str(), &temp ) );
}

//	float4型の配列のセット
bool Effect::SetVectorArayy( std::string path, math::Vector4* vecArayy ,U_LONG size )
{
	return SUCCEEDED( effect->SetVectorArray( path.c_str() , vecArayy , size ) );
}

//	float型変数のセット
bool Effect::SetFloat( std::string path,  float val )
{
	return SUCCEEDED( effect->SetFloat( path.c_str(), val ) );
}

//	テクスチャーのセット
bool Effect::SetTexture( std::string path, const LPDIRECT3DTEXTURE9 texture )
{
	return SUCCEEDED( effect->SetTexture( path.c_str(), texture ) );
}

//	キューブテクスチャのセット
bool Effect::SetTexture(std::string path, const LPDIRECT3DCUBETEXTURE9 texture)
{
	return SUCCEEDED( effect->SetTexture( path.c_str(), texture ) );
}

//デバイスに値が変更したことを伝える
bool Effect::CommitChanges()
{
	return SUCCEEDED( effect->CommitChanges() );
}

//	シェーダーの開始
bool Effect::Begin( U_INT *num, DWORD flag )
{
	return SUCCEEDED( effect->Begin( num, flag ) );
}

// パスの開始
bool Effect::BeginPass( U_INT pass )
{
	return SUCCEEDED( effect->BeginPass( pass ) );
}

//	シェーダーの終了
bool Effect::End()
{
	return SUCCEEDED( effect->End() );
}

// パスの終了
bool Effect::EndPass()
{
	return SUCCEEDED( effect->EndPass() );
}

}	//	graphics	end
}	//	iruna		end