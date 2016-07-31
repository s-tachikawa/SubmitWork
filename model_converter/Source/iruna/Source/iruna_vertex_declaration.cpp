//---------------------------------------------------------
// 
//	iruna_vertex_declaration.h
//	�o�[�e�N�X�f�B�N�����[�V�����̃��b�v
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_vertex_declaration.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
VertexDeclaration::VertexDeclaration()
	: declaration( 0 ),
	  element	 ( 0 )
{
	return;
}

// �R�s�[�R���X�g���N�^
VertexDeclaration::VertexDeclaration( const VertexDeclaration& another )
	: declaration( another.declaration )
{
	declaration->AddRef();

	return;
}

// �f�X�g���N�^
VertexDeclaration::~VertexDeclaration()
{
	Release();

	return;
}

// ���_�錾���쐬����A�����G�������g��˂����񂾏ꍇ�Q�ƃJ�E���g���C���N�������g
bool VertexDeclaration::Create( Element* vertexElement )
{
	// ���ɍ���Ă��āA�������_�G�������g��������Q�ƃJ�E���g���C���N�������g
	if( declaration && element == vertexElement )
	{
		declaration->AddRef();
	}

	// ��������Ȃ��Ă�����Ă�����I��
	if( declaration )
	{
		return false;
	}

	// �G�������g�̃R�s�[
	element	= vertexElement;

	return SUCCEEDED( Device::GetDevice()->CreateVertexDeclaration( 
					vertexElement,
					&declaration ) );	
}

// ���_�錾���f�o�C�X�ɃZ�b�g����
bool VertexDeclaration::Set()
{
	return SUCCEEDED( Device::GetDevice()->SetVertexDeclaration( declaration ) );
}

// ���_�錾���J������A�Q�ƃJ�E���g��0�ɂȂ�����폜����
void VertexDeclaration::Release()
{
	
	if( !declaration )
	{
		// �f�B�N�����[�V�����f�[�^������ꍇ�͉�����Ȃ�
		return;
	}

	// �Q�ƃJ�E���g��0�Ȃ���
	if( 0 == declaration->Release() )
	{
		declaration	= 0;
		element		= 0;
	}

	return;
}

}	//	graphics	end
}	//	iruna		end