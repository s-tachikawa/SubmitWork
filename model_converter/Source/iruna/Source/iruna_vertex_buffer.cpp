//---------------------------------------------------------
// 
//	iruna_vertex_buffer.cpp
//	�o�[�e�N�X�o�b�t�@�̃��b�v
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_vertex_buffer.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
VertexBuffer::VertexBuffer()
	: buffer	( 0 ),
	  vertexCnt	( 0 ),
	  stride	( 0 ),
	  format	( UNKNOWN )
{
	return;
}

// �R�s�[�R���X�g���N�^
VertexBuffer::VertexBuffer( const VertexBuffer& another )
	: buffer	( 0 ),
	  vertexCnt	( another.vertexCnt ),
	  stride	( another.stride ),
	  format	( another.format )
{
	// �o�[�e�N�X�o�b�t�@���쐬
	CreateVertexBuffer();

	// �R�s�[���邽�߂�void�|�C���^�̏�����
	void*	infoAnother	= 0;
	void*	infoThis	= 0;

	//	�R�s�[����o�b�t�@�ƃR�s�[��̃o�b�t�@�����b�N
	another.buffer->Lock( 0, 0, &infoAnother, 0 );
	this->buffer->Lock(	  0, 0, &infoThis,	  0 );

	// ���b�N�����o�b�t�@�̏����R�s�[
	memcpy( infoThis, infoAnother, this->vertexCnt * this->stride );

	// �R�s�[�����������̂łǂ�����A�����b�N
	another.buffer->Unlock();
	this->buffer->Unlock();

	return;
}

// �f�X�g���N�^
VertexBuffer::~VertexBuffer()
{
	Release();

	return;
}

// ���_�o�b�t�@���쐬����
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

// �o�b�t�@���쐬
bool VertexBuffer::Create( Format vertexFormat, U_LONG vertexCount )
{
	//���_�o�b�t�@�T�C�Y
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
	
	// UNKNOWN��-1�Ȃ̂ł͂���
	if( UNKNOWN == vertexFormat )
	{
		return false;
	}

	// �쐬���������i�[
	vertexCnt	= vertexCount;
	stride		= VERTEX_SIZE[ vertexFormat ];
	format		= vertexFormat;

	return CreateVertexBuffer();
}

// �o�b�t�@�ɕ`������
bool VertexBuffer::SetBuffer( const void* data, U_LONG begin, U_LONG end )
{
	// �쐬���邽�߃o�b�t�@�̏���������
	void*	info	= 0;
	U_LONG	size	= ( end - begin ) * stride;
	U_LONG	offset	= begin * stride;

	// �o�b�t�@�����b�N���ď�����������
	if( FAILED( buffer->Lock( offset, size, &info, D3DLOCK_DISCARD ) ) )
	{
		return false;
	}

	//	�����o�b�t�@�ɃR�s�[
	memcpy( info, data, size );

	// �쐬���I������̂ŃA�����b�N����
	buffer->Unlock();

	return true;
}

// �o�b�t�@���X�g���[���ɗ���
bool VertexBuffer::IntoStream( U_LONG streamNum )
{
	return SUCCEEDED( Device::GetDevice()->SetStreamSource(
				streamNum,
				buffer,
				0,
				stride ) );
}

// �o�b�t�@���������
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