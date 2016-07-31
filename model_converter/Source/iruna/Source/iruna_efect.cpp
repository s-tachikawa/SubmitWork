//---------------------------------------------------------
// 
//	iruna_efect.cpp
//	�V�F�[�_�[�t�@�C���Ǘ��N���X
//	�쐬�� 6��25��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_efect.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	�R���X�g���N�^
Effect::Effect()
	:	effect( 0 )
{
	return;
}

//	�f�X�g���N�^
Effect::~Effect()
{
	SafeRelease( effect );
}

//	�G�t�F�N�g�̓ǂݍ���
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
//	�V�F�[�_�[�̃o�[�W�����`�F�b�N
bool Effect::VersionCheck( U_INT vertex_num, U_INT pixel_num )
{
	D3DCAPS9 caps;
	Device::GetDevice()->GetDeviceCaps( &caps );

	return  caps.VertexShaderVersion	>= D3DVS_VERSION( vertex_num, 0 ) &&
			caps.PixelShaderVersion		>= D3DPS_VERSION( pixel_num, 0 );
}

//	�e�N�j�b�N�̃Z�b�g
bool Effect::SetTechnique( std::string path )
{
	return SUCCEEDED( effect->SetTechnique( path.c_str() ) );
}

//	�s��̃Z�b�g
bool Effect::SetMatrix( std::string path,  math::Matrix mat )
{
	return SUCCEEDED( effect->SetMatrix( path.c_str(), &mat ) );
}

// �s��̔z��Z�b�g
bool Effect::SetMatrixArayy(std::string path, iruna::math::Matrix* mat, iruna::U_LONG size)
{
	return SUCCEEDED( effect->SetMatrixArray( path.c_str(), mat, size ) );
}

//	float4�^�ϐ��̃Z�b�g
bool Effect::SetVector( std::string path,  math::Vector4 vec )
{
	return SUCCEEDED( effect->SetVector( path.c_str(), &vec ) );
}

//	float3�^�ϐ��̃Z�b�g
bool Effect::SetVector( std::string path,  math::Vector3 vec )
{
	math::Vector4 temp = math::Vector4( vec.x, vec.y, vec.z, 0 );

	return SUCCEEDED( effect->SetVector( path.c_str(), &temp ) );
}

//	float2�^�ϐ��̃Z�b�g
bool Effect::SetVector( std::string path,  math::Vector2 vec )
{
	math::Vector4 temp = math::Vector4( vec.x, vec.y, 0, 0 );
	return SUCCEEDED( effect->SetVector( path.c_str(), &temp ) );
}

//	float4�^�̔z��̃Z�b�g
bool Effect::SetVectorArayy( std::string path, math::Vector4* vecArayy ,U_LONG size )
{
	return SUCCEEDED( effect->SetVectorArray( path.c_str() , vecArayy , size ) );
}

//	float�^�ϐ��̃Z�b�g
bool Effect::SetFloat( std::string path,  float val )
{
	return SUCCEEDED( effect->SetFloat( path.c_str(), val ) );
}

//	�e�N�X�`���[�̃Z�b�g
bool Effect::SetTexture( std::string path, const LPDIRECT3DTEXTURE9 texture )
{
	return SUCCEEDED( effect->SetTexture( path.c_str(), texture ) );
}

//	�L���[�u�e�N�X�`���̃Z�b�g
bool Effect::SetTexture(std::string path, const LPDIRECT3DCUBETEXTURE9 texture)
{
	return SUCCEEDED( effect->SetTexture( path.c_str(), texture ) );
}

//�f�o�C�X�ɒl���ύX�������Ƃ�`����
bool Effect::CommitChanges()
{
	return SUCCEEDED( effect->CommitChanges() );
}

//	�V�F�[�_�[�̊J�n
bool Effect::Begin( U_INT *num, DWORD flag )
{
	return SUCCEEDED( effect->Begin( num, flag ) );
}

// �p�X�̊J�n
bool Effect::BeginPass( U_INT pass )
{
	return SUCCEEDED( effect->BeginPass( pass ) );
}

//	�V�F�[�_�[�̏I��
bool Effect::End()
{
	return SUCCEEDED( effect->End() );
}

// �p�X�̏I��
bool Effect::EndPass()
{
	return SUCCEEDED( effect->EndPass() );
}

}	//	graphics	end
}	//	iruna		end