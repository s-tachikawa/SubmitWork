//---------------------------------------------------------
// 
//	iruna_device_controller.h
//	�f�o�C�X�̊Ԑڑ���
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_device_controller.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	// �ÓI�����o�ϐ��̎���
LPDIRECT3DDEVICE9*	DeviceController::ppD3dDevice	= 0;

// �R���X�g���N�^
DeviceController::DeviceController()
{
	if( !ppD3dDevice )
		ppD3dDevice	= &( Device::GetDevice() );

	return;
}

// �f�X�g���N�^
DeviceController::~DeviceController()
{
	return;
}

// �`������s(���_�f�[�^�̓\�t�g�E�F�A����)
bool DeviceController::DrawPrimitiveUp( Primitive::Type type, U_LONG polygonCnt, const void *vertexBuffer, U_LONG vertexStride )
{
	return SUCCEEDED( ( *ppD3dDevice )->DrawPrimitiveUP( 
				static_cast< D3DPRIMITIVETYPE >( type ),
				polygonCnt,
				vertexBuffer,
				vertexStride ) );
}

// �`������s(���_�f�[�^�̓n�[�h�E�F�A����)
bool DeviceController::DrawPrimitive( Primitive::Type type, U_LONG polygonCnt )
{
	return SUCCEEDED( ( *ppD3dDevice )->DrawPrimitive( 
				static_cast< D3DPRIMITIVETYPE >( type ),
				0,
				polygonCnt ) );
}

// �C���f�b�N�X���g�����`������s(���_�f�[�^�̓n�[�h�E�F�A����)
bool DeviceController::DrawIndexPrimitive( Primitive::Type type, U_LONG vertexCnt, U_LONG polygonCnt )
{
	return SUCCEEDED( ( *ppD3dDevice )->DrawIndexedPrimitive(
				static_cast< D3DPRIMITIVETYPE >( type ),
				0,
				0,
				vertexCnt,
				0,
				polygonCnt ) );
}

// Z�o�b�t�@�ɕ`�����ނ��`�����܂Ȃ����̐ݒ肷��
void DeviceController::SetZBufferState( bool flag )
{
	( *ppD3dDevice )->SetRenderState( D3DRS_ZENABLE,		flag );
	( *ppD3dDevice )->SetRenderState( D3DRS_ZWRITEENABLE,	flag );

	return;
}

// �f�o�C�X�ɕϊ��s����Z�b�g����
bool DeviceController::SetTransform( D3DTRANSFORMSTATETYPE target, math::Matrix matrix )
{
	return SUCCEEDED( ( *ppD3dDevice )->SetTransform( target, &matrix ) );
}

// �f�o�C�X�Ƀe�N�X�`�����Z�b�g����
bool DeviceController::SetTexture( U_LONG stage, LPDIRECT3DTEXTURE9 texture )
{
	return SUCCEEDED( ( *ppD3dDevice )->SetTexture( stage, texture ) );
}

// �f�o�C�X�Ƀ}�e���A�����Z�b�g����
bool DeviceController::SetMaterial( D3DMATERIAL9 material )
{
	return SUCCEEDED( ( *ppD3dDevice )->SetMaterial( &material ) );
}

// �����_�[�X�e�[�g�̐ݒ�
bool DeviceController::SetRenderState(  D3DRENDERSTATETYPE type ,U_LONG val  )
{
	return SUCCEEDED( ( *ppD3dDevice)->SetRenderState( type , val ) );
}


}	//	graphics	end
}	//	iruna		end

/*----�O���[�o���֐� ��`----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	�w�肵������ʂ��N���A����
bool ClearBackBuffer(  DWORD flag )
{
	return Device::ClearBackBuffer( flag );
}

//	����ʂ��N���A���A�`����J�n����
bool ClearScreen()
{
	return Device::ClearScreen();
}

//	�`����I�����A����ʂɕ`�������̂�\��ʂ֓]��
bool SwapScreen()
{
	return Device::SwapScreen();
}

}	//	graphics	end
}	//	iruna		end