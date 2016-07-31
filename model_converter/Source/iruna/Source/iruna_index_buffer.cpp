//---------------------------------------------------------
// 
//	iruna_index_buffer.cpp
//	インデックスバッファのラップ
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_index_buffer.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
IndexBuffer::IndexBuffer()
	: buffer	( 0 ),
	  indexCnt	( 0 ),
	  stride	( 0 ),
	  format	( UNKNOWN )
{
	return;
}

// コピーコンストラクタ
IndexBuffer::IndexBuffer( const IndexBuffer& another )
	: buffer	( 0 ),
	  indexCnt	( another.indexCnt ),
	  stride	( another.stride ),
	  format	( another.format )
{
	// インデックスバッファの作成
	CreateIndexBuffer();

	// コピーするvoidポインタの初期化
	void*	infoAnother	= 0;
	void*	infoThis	= 0;

	// バッファをロックしてポインタにコピー
	another.buffer->Lock( 0, 0, &infoAnother, 0 );
	this->buffer->Lock(	  0, 0, &infoThis,	  0 );

	// コピー先にコピー
	memcpy( infoThis, infoAnother, this->indexCnt * this->stride );

	// コピーが完了したのでアンロックする
	another.buffer->Unlock();
	this->buffer->Unlock();

	return;
}

// デストラクタ
IndexBuffer::~IndexBuffer()
{
	Release();

	return;
}

// インデックスバッファを作成する
bool IndexBuffer::CreateIndexBuffer()
{
	return SUCCEEDED( Device::GetDevice()->CreateIndexBuffer(
					indexCnt * stride,
					D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
					( format == IndexBuffer::BIT16 ) ? ( D3DFMT_INDEX16 ) : ( D3DFMT_INDEX32 ),
					D3DPOOL_DEFAULT,
					&buffer,
					0 ) );
}

// バッファを作成
bool IndexBuffer::Create( Format indexFormat, U_LONG indexCount )
{
	//インデックスバッファサイズ
	static const int INDEX_SIZE[] = {
		sizeof( short ),	// D3DFMT_INDEX16
		sizeof( int )		// D3DFMT_INDEX32
	};
	
	// UNKNOWNは-1なのではじく
	if( UNKNOWN == indexFormat )
	{
		return false;
	}

	// 作成した情報を格納
	indexCnt	= indexCount;
	stride		= INDEX_SIZE[ indexFormat ];
	format		= indexFormat;

	return CreateIndexBuffer();
}

// バッファに描きこむ
bool IndexBuffer::SetBuffer( const void* data, U_LONG begin, U_LONG end )
{
	// バッファに書き込む情報を初期化
	void*	info	= 0;
	U_LONG	size	= ( end - begin ) * stride;
	U_LONG	offset	= begin * stride;

	// バッファをロックして書き込む
	if( FAILED( buffer->Lock( offset, size, &info, D3DLOCK_DISCARD ) ) )
	{
		return false;
	}

	// 書き込んだ情報をコピー
	memcpy( info, data, size );

	// 作成終了したのでバッファをアンロック
	buffer->Unlock();

	return true;
}

// バッファをストリームに流す
bool IndexBuffer::IntoIndices()
{
	return SUCCEEDED( Device::GetDevice()->SetIndices( buffer ) );
}

// バッファを解放する
void IndexBuffer::Release()
{
	SafeRelease( buffer );
	indexCnt	= 0;
	stride		= 0;
	format		= UNKNOWN;

	return;
}

}	//	graphics	end
}	//	iruna		end