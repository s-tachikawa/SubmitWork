//---------------------------------------------------------
// 
//	bar_icon.h
//	�w�肵�������Ńo�[�̃A�C�R�����쐬���A�Ǘ�����
//	�X�V�� 1��8��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----���d�C���N���[�h---------------------------------*/
#ifndef ICON_BAR_H
#define ICON_BAR_H

/*----�C���N���[�h---------------------------------*/
#include "../../iruna/Include/iruna.h"

/*----�l�[���X�y�[�X-------------------------------------------------*/
using namespace iruna;
using namespace	graphics;

//=====================================================================
//
//	�N���X��	:	BarIcon
//	����		:	�w�肵���T�C�Y�̃o�[���쐬����
//
//=====================================================================
class BarIcon
{
//	�v���C�x�[�g	�����o�ϐ�
private:
	float				valueMax;		//	�o�[�̍ő�l
	math::Vector2		pos;			//	�o�[�`����W
	Texture*			barTex;			//	GUI��̃o�[�Ɏg�p����摜
	Sprite*				barSpr;			//	�o�[�`��p�X�v���C�g
	math::Vector2		curPos;			//	�J�[�\���`����W
	Sprite*				cur;			//	�o�[����ړ�����J�[�\���X�v���C�g
	bool				flag;			//	�o�[�J�[�\������t���O
	DeviceController	render;			//	�����_�����O�f�o�C�X

//	�v���C�x�[�g	�����o�֐�
private:

	bool HitCursor();

//	�p�u���b�N	�����o�֐�
public:

	//--------------------------------------------------------------------
	// 
	//	����	:	�R���X�g���N�^
	// 
	//--------------------------------------------------------------------
	BarIcon();

	//--------------------------------------------------------------------
	// 
	//	����	:	�f�X�g���N�^
	//
	//--------------------------------------------------------------------
	~BarIcon();

	//--------------------------------------------------------------------
	// 
	//	����	:	�X���C�_�[�̍ő�l��ݒ肷��
	//	��1���� :	�X���C�_�[�̍ő�l
	// 
	//--------------------------------------------------------------------
	void SetSliderMax( float max );

	//--------------------------------------------------------------------
	// 
	//	����	:	�X���C�_�[�̍X�V
	// 
	//--------------------------------------------------------------------
	void UpDate();

	//--------------------------------------------------------------------
	// 
	//	����	:	�X���C�_�[�̕`��
	// 
	//--------------------------------------------------------------------
	void Draw();

	//--------------------------------------------------------------------
	// 
	//	����	:	�X���C�_�[��̃A�C�R���̍��W��ݒ�
	//	��1����	:	�w�肷��Vector2�^�̍��W
	// 
	//--------------------------------------------------------------------
	void SetPos( math::Vector2 setPos );

	//--------------------------------------------------------------------
	// 
	//	����	:	���݂̃X���C�_�[�̒l���擾
	//	�߂�l	:	���݃A�C�R��������ʒu�̒l
	// 
	//--------------------------------------------------------------------
	int GetValue();

	//--------------------------------------------------------------------
	// 
	//	����	:	�X���C�_�[�ɒl���Z�b�g����
	//	��1���� :	���Ă�����l
	// 
	//--------------------------------------------------------------------
	void SetValue( float setValue );

};

#endif	//	ICON_BAR_H	end