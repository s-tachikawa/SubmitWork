//---------------------------------------------------------
// 
//	iruna_texture.cpp
//	�e�N�X�`���[�̊Ǘ�
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_texture.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
Texture::Texture()
	: texture( 0 )
{
	return;
}

// �f�X�g���N�^
Texture::~Texture()
{
	SafeRelease( texture );

	return;
}

// �摜�t�@�C������e�N�X�`����ǂݍ���
bool Texture::Load( std::string path, Color4 color, U_INT mipLevel, DWORD filter )
{
	if( FAILED( D3DXCreateTextureFromFileEx(
				Device::GetDevice(),
				path.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				mipLevel,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				filter,
				filter,
				color,
				0,
				0,
				&texture ) ) )
		return false;

	recoveryPath	= path;

	return true;
}

// �J���̓��I�e�N�X�`�����쐬����
bool Texture::Create( U_INT width, U_INT height, DWORD usage, U_INT mipLevel )
{
	return SUCCEEDED( D3DXCreateTexture( 
			Device::GetDevice(),
			width,
			height,
			mipLevel,
			usage,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&texture ) );
}

// �e�N�X�`�����������
void Texture::Release()
{
	SafeRelease( texture );
	recoveryPath.clear();

	return;
}

// �e�N�X�`�������b�N���A�A�N�Z�X���邽�߂�LockedRect��Ԃ�(���I�e�N�X�`���̂�)
bool Texture::Lock( LockedRect &rect, DWORD flag )
{
	return SUCCEEDED( texture->LockRect( 0, &rect, 0, flag ) );
}

// �e�N�X�`�����A�����b�N���A�A�N�Z�X�ł��Ȃ��悤�ɂ���(���I�e�N�X�`���̂�)
bool Texture::Unlock()
{
	return SUCCEEDED( texture->UnlockRect( 0 ) );
}

// �e�N�X�`�����擾
const LPDIRECT3DTEXTURE9& Texture::GetTexture()
{
	return texture;
}

// �e�N�X�`���̃T�C�Y���擾
POINT Texture::GetSize()
{
	POINT				temp;
	D3DSURFACE_DESC		desc;
	texture->GetLevelDesc( 0, &desc );

	temp.x	= desc.Width;
	temp.y	= desc.Height;

	return temp;
}

// �T�[�t�F�X���擾
bool Texture::GetSurface( Surface& surface )
{
	LPDIRECT3DSURFACE9	temp	= 0;

	if( FAILED( texture->GetSurfaceLevel( 0, &temp ) ) )
	{
		return false;
	}

	surface	= temp;
		
	return true;

}


}	//	graphics	end
}	//	iruna		end