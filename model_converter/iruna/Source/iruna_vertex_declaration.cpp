//---------------------------------------------------------
// 
//	iruna_vertex_declaration.h
//	バーテクスディクラレーションのラップ
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_vertex_declaration.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
VertexDeclaration::VertexDeclaration()
	: declaration( 0 ),
	  element	 ( 0 )
{
	return;
}

// コピーコンストラクタ
VertexDeclaration::VertexDeclaration( const VertexDeclaration& another )
	: declaration( another.declaration )
{
	declaration->AddRef();

	return;
}

// デストラクタ
VertexDeclaration::~VertexDeclaration()
{
	Release();

	return;
}

// 頂点宣言を作成する、同じエレメントを突っ込んだ場合参照カウントをインクリメント
bool VertexDeclaration::Create( Element* vertexElement )
{
	// 既に作られていて、同じ頂点エレメントだったら参照カウントをインクリメント
	if( declaration && element == vertexElement )
	{
		declaration->AddRef();
	}

	// 同じじゃなくても作られていたら終了
	if( declaration )
	{
		return false;
	}

	// エレメントのコピー
	element	= vertexElement;

	return SUCCEEDED( Device::GetDevice()->CreateVertexDeclaration( 
					vertexElement,
					&declaration ) );	
}

// 頂点宣言をデバイスにセットする
bool VertexDeclaration::Set()
{
	return SUCCEEDED( Device::GetDevice()->SetVertexDeclaration( declaration ) );
}

// 頂点宣言を開放する、参照カウントが0になったら削除する
void VertexDeclaration::Release()
{
	
	if( !declaration )
	{
		// ディクラレーションデータがある場合は解放しない
		return;
	}

	// 参照カウントが0なら解放
	if( 0 == declaration->Release() )
	{
		declaration	= 0;
		element		= 0;
	}

	return;
}

}	//	graphics	end
}	//	iruna		end