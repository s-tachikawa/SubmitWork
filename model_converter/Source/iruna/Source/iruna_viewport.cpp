//---------------------------------------------------------
// 
//	iruna_viewport.cpp
//	�r���[�|�[�g�֘A
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_viewport.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	// �R���X�g���N�^
Viewport::Viewport()
{
	memset( &viewport, 0, sizeof( D3DVIEWPORT9 ) );

	return;
}

// �R�s�[�R���X�g���N�^
Viewport::Viewport( const Viewport& another )
	: viewport( another.viewport ) 
{
	return;
}

// �f�X�g���N�^
Viewport::~Viewport()
{
	return;
}

// �r���[�|�[�g�̑傫�����w�肷��
void Viewport::SetSize( U_INT x, U_INT y, U_INT width, U_INT height )
{
	viewport.X		= x;
	viewport.Y		= y;
	viewport.Width	= width;
	viewport.Height	= height;

	return;
}

// �r���[�|�[�g�̑傫�����w�肷��(��`��)
void Viewport::SetSize( math::Rect rect )
{
	SetSize( rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top );

	return;
}

// �r���[�|�[�g���f�o�C�X�ɃZ�b�g
bool Viewport::SetViewport()
{
	return SUCCEEDED( Device::GetDevice()->SetViewport( &viewport ) );
}

// ������Z�q�I�[�o�[���[�h�AD3DVIEWPORT9�������߂�悤��
Viewport& Viewport::operator =( D3DVIEWPORT9 setViewport )
{
	viewport	= setViewport;

	return *this;
}

}	// graphics	end
}	// white	end

/*----�֐� ��`----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �f�o�C�X���猻�݃Z�b�g����Ă���r���[�|�[�g���擾
bool GetViewport( Viewport& viewport )
{
	D3DVIEWPORT9	temp;

	bool reslut = SUCCEEDED( Device::GetDevice()->GetViewport( &temp ) );

	viewport	= temp;

	return reslut;
}
}	//	graphics	end
}	//	iruna		end