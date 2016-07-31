//---------------------------------------------------------
// 
//	iruna_camera.cpp
//	�J�����֘A	VIEW��PROJECTION�ȂǍs��̍쐬
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_camera.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
Camera::Camera()
{
	fovY	= 0;
	aspect	= 0;
	zNear	= 0;
	zFar	= 0;
	memset( &eye,		 0, sizeof( math::Vector3 ) );
	memset( &lookAt,	 0, sizeof( math::Vector3 ) );
	memset( &upVector,	 0, sizeof( math::Vector3 ) );

	return;
}

// �����o��fovY,aspect,zNear,zFar����v���W�F�N�V�����s����쐬����
math::Matrix Camera::GetProjection()
{
	math::Matrix	temp;

	D3DXMatrixPerspectiveFovLH( 
			&temp,
			fovY,
			aspect,
			zNear,
			zFar );

	return temp;
}

// �����o��eye,lookAt,upVector����r���[�s����쐬����
math::Matrix Camera::GetView()
{
	math::Matrix	temp;

	D3DXMatrixLookAtLH(
			&temp,
			&eye,
			&lookAt,
			&upVector );

	return temp;
}

}	//	graphics	end
}	//	iruna		end