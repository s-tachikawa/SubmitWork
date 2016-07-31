//---------------------------------------------------------
// 
//	iruna_vertex_buffer.cpp
//	バーテクスバッファのラップ
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_vertex_buffer.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
VertexBuffer::VertexBuffer()
	: buffer	( 0 ),
	  vertexCnt	( 0 ),
	  stride	( 0 ),
	  format	( UNKNOWN )
{
	return;
}

// コピーコンストラクタ
VertexBuffer::VertexBuffer( const VertexBuffer& another )
	: buffer	( 0 ),
	  vertexCnt	( another.vertexCnt ),
	  stride	( another.stride ),
	  format	( another.format )
{
	// バーテクスバッファを作成
	CreateVertexBuffer();

	// コピーするためのvoidポインタの初期化
	void*	infoAnother	= 0;
	void*	infoThis	= 0;

	//	コピーするバッファとコピー先のバッファをロック
	another.buffer->Lock( 0, 0, &infoAnother, 0 );
	this->buffer->Lock(	  0, 0, &infoThis,	  0 );

	// ロックしたバッファの情報をコピー
	memcpy( infoThis, infoAnother, this->vertexCnt * this->stride );

	// コピーが完了したのでどちらもアンロック
	another.buffer->Unlock();
	this->buffer->Unlock();

	return;
}

// デストラクタ
VertexBuffer::~VertexBuffer()
{
	Release();

	return;
}

// 頂点バッファを作成する
bool VertexBuffer::CreateVertexBuffer()
{
	return SUCCEEDED( Device::GetDevice()->CreateVertexBuffer(
					vertexCnt * stride,
					D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
					0,
					D3DPOOL_DEFAULT,
					&buffer,
					0 )	);
}

// バッファを作成
bool VertexBuffer::Create( Format vertexFormat, U_LONG vertexCount )
{
	//頂点バッファサイズ
	static const int VERTEX_SIZE[] = {		
		sizeof( float ),		// D3DDECLTYPE_FLOAT1
		sizeof( float ) * 2,	// D3DDECLTYPE_FLOAT2
		sizeof( float ) * 3,	// D3DDECLTYPE_FLOAT3
		sizeof( float ) * 4,	// D3DDECLTYPE_FLOAT4
		sizeof( DWORD ),		// D3DDECLTYPE_D3DCOLOR
		sizeof( BYTE )  * 4,	// D3DDECLTYPE_UBYTE4
		sizeof( short ) * 2,	// D3DDECLTYPE_SHORT2
		sizeof( short ) * 4,	// D3DDECLTYPE_SHORT4
	};
	
	// UNKNOWNは-1なのではじく
	if( UNKNOWN == vertexFormat )
	{
		return false;
	}

	// 作成した情報を格納
	vertexCnt	= vertexCount;
	stride		= VERTEX_SIZE[ vertexFormat ];
	format		= vertexFormat;

	return CreateVertexBuffer();
}

// バッファに描きこむ
bool VertexBuffer::SetBuffer( const void* data, U_LONG begin, U_LONG end )
{
	// 作成するためバッファの情報を初期化
	void*	info	= 0;
	U_LONG	size	= ( end - begin ) * stride;
	U_LONG	offset	= begin * stride;

	// バッファをロックして情報を書き込む
	if( FAILED( buffer->Lock( offset, size, &info, D3DLOCK_DISCARD ) ) )
	{
		return false;
	}

	//	情報をバッファにコピー
	memcpy( info, data, size );

	// 作成が終わったのでアンロックする
	buffer->Unlock();

	return true;
}

// バッファをストリームに流す
bool VertexBuffer::IntoStream( U_LONG streamNum )
{
	return SUCCEEDED( Device::GetDevice()->SetStreamSource(
				streamNum,
				buffer,
				0,
				stride ) );
}

// バッファを解放する
void VertexBuffer::Release()
{
	SafeRelease( buffer );
	vertexCnt	= 0;
	stride		= 0;
	format		= UNKNOWN;

	return;
}

}	//	graphics	end
}	//	iruna		end