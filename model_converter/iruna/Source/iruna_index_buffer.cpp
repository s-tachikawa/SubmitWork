//---------------------------------------------------------
// 
//	iruna_index_buffer.cpp
//	�C���f�b�N�X�o�b�t�@�̃��b�v
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_index_buffer.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
IndexBuffer::IndexBuffer()
	: buffer	( 0 ),
	  indexCnt	( 0 ),
	  stride	( 0 ),
	  format	( UNKNOWN )
{
	return;
}

// �R�s�[�R���X�g���N�^
IndexBuffer::IndexBuffer( const IndexBuffer& another )
	: buffer	( 0 ),
	  indexCnt	( another.indexCnt ),
	  stride	( another.stride ),
	  format	( another.format )
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	CreateIndexBuffer();

	// �R�s�[����void�|�C���^�̏�����
	void*	infoAnother	= 0;
	void*	infoThis	= 0;

	// �o�b�t�@�����b�N���ă|�C���^�ɃR�s�[
	another.buffer->Lock( 0, 0, &infoAnother, 0 );
	this->buffer->Lock(	  0, 0, &infoThis,	  0 );

	// �R�s�[��ɃR�s�[
	memcpy( infoThis, infoAnother, this->indexCnt * this->stride );

	// �R�s�[�����������̂ŃA�����b�N����
	another.buffer->Unlock();
	this->buffer->Unlock();

	return;
}

// �f�X�g���N�^
IndexBuffer::~IndexBuffer()
{
	Release();

	return;
}

// �C���f�b�N�X�o�b�t�@���쐬����
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

// �o�b�t�@���쐬
bool IndexBuffer::Create( Format indexFormat, U_LONG indexCount )
{
	//�C���f�b�N�X�o�b�t�@�T�C�Y
	static const int INDEX_SIZE[] = {
		sizeof( short ),	// D3DFMT_INDEX16
		sizeof( int )		// D3DFMT_INDEX32
	};
	
	// UNKNOWN��-1�Ȃ̂ł͂���
	if( UNKNOWN == indexFormat )
	{
		return false;
	}

	// �쐬���������i�[
	indexCnt	= indexCount;
	stride		= INDEX_SIZE[ indexFormat ];
	format		= indexFormat;

	return CreateIndexBuffer();
}

// �o�b�t�@�ɕ`������
bool IndexBuffer::SetBuffer( const void* data, U_LONG begin, U_LONG end )
{
	// �o�b�t�@�ɏ������ޏ���������
	void*	info	= 0;
	U_LONG	size	= ( end - begin ) * stride;
	U_LONG	offset	= begin * stride;

	// �o�b�t�@�����b�N���ď�������
	if( FAILED( buffer->Lock( offset, size, &info, D3DLOCK_DISCARD ) ) )
	{
		return false;
	}

	// �������񂾏����R�s�[
	memcpy( info, data, size );

	// �쐬�I�������̂Ńo�b�t�@���A�����b�N
	buffer->Unlock();

	return true;
}

// �o�b�t�@���X�g���[���ɗ���
bool IndexBuffer::IntoIndices()
{
	return SUCCEEDED( Device::GetDevice()->SetIndices( buffer ) );
}

// �o�b�t�@���������
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