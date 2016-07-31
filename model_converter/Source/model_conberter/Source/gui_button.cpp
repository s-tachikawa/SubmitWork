//---------------------------------------------------------
// 
//	gui_button.h
//	GUI��̃{�^���̊Ǘ�
//	�쐬�� 10��21��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/gui_button.h"

/*----�O���[�o���֐��錾-------------------------------------------------*/
extern void PushButton( GuiButton& button );		//	1�񉟂����炷���߂�{�^��

/*----�O���[�o���ϐ��錾-------------------------------------------------*/
// �{�^���̏����֐��e�[�u��
GuiButton::ButtonFunc ButtonFouncTable[] =
{
	PushButton,
	PushButton,
	PushButton,

};

//	�����{�^���̍X�V( �O���[�o���֐� )
void PushButton( GuiButton& button )
{
	button.state = GuiButton::NORMAL;

	POINT mouse = io::GetMousePosition();
	INPUT_STATE mouseState = CheckMouseState( MouseButton::LEFT );

	if( button.size.top	< mouse.y && 
		button.size.left	< mouse.x &&
		button.size.bottom	> mouse.y &&
		button.size.right	> mouse.x	)
	{
		button.state = GuiButton::HIT;

		if( mouseState == INPUT_PUSH || mouseState ==  INPUT_PUSHED )
		{
			button.state = GuiButton::PUSH;
		}

		return;
	}

	return;
}

// �{�^���̏�����
void GuiButton::Init()
{
	this->func = ButtonFouncTable[ type ];

	return;
}