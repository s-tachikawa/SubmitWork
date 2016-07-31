//---------------------------------------------------------
// 
//	gui_twice_button.h
//	2�񉟂��Ă��Ƃɖ߂�{�^��
//	�X�V�� 10��25��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/gui_twice_button.h"

//	�R���X�g���N�^
TwiceButton::TwiceButton()
{
	buttonTex = new Texture[ 2 ];
	buttonTex[ 0 ].Load( "../Resource/texture/�Đ��{�^��.png" );
	buttonTex[ 1 ].Load( "../Resource/texture/��~�{�^��.png" );
	buttonSpr = new Sprite;
	buttonSpr->SetSize( math::Vector2( 30, 30 ) );
	flag = false;	//	�ŏ��̓X�g�b�v�{�^����������Ă���B


	return;
}

//	�f�X�g���N�^
TwiceButton::~TwiceButton()
{
	SafeArrayDelete( buttonTex );
	SafeDelete( buttonSpr );

	return;
}

//	������
void TwiceButton::Init( math::Vector2 in_pos, math::Vector2 in_size )
{
	pos = in_pos;
	size = in_size;
	rectSize = math::Rect(	( int )pos.x, 
							( int )pos.y, 
							( int )pos.x + size.x,
							( int )pos.y + size.y );
	
	return;
}

//	�X�V
void TwiceButton::UpDate()
{

	POINT mouse = io::GetMousePosition();
	INPUT_STATE mouseState = CheckMouseState( MouseButton::LEFT );

	if( rectSize.top	< mouse.y && 
		rectSize.left	< mouse.x &&
		rectSize.bottom	> mouse.y &&
		rectSize.right	> mouse.x	)
	{
		buttonSpr->SetColor( Color4( 200, 0, 0, 255 ) );

		if( mouseState ==  io::INPUT_RELEASED )
		{
			flag = !flag;
		}

		return;
	}
	else
	{
		buttonSpr->SetColor( Color4( 255, 255, 255, 255 ) );
	}

	return;
}

//	�`��
void TwiceButton::Draw()
{

	if( flag )
	{
		render.SetTexture( 0, buttonTex[ 0 ].GetTexture() );
		buttonSpr->Draw( pos );
	}
	else
	{
		render.SetTexture( 0, buttonTex[ 1 ].GetTexture() );
		buttonSpr->Draw( pos );
	}
	
	return;
}

//	�{�^���̏�Ԃ��擾
bool TwiceButton::GetState()
{
	return flag;
}
