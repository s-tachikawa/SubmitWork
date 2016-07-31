//---------------------------------------------------------
// 
//	model_converter.h
//	�A�v���P�[�V�����̃��C��
//	�쐬�� 10��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef MODEL_CONVERTER_H
#define MODEL_CONVERTER_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../../iruna/Include/iruna.h"
#include "../Include/gui_frame.h"
#include "../Include/model_render.h"
#include "../Include/sgd_encoder.h"
#include "../Include/dialog_animetion_input.h"
#include "../Include/gui_slider.h"
#include "../Include/gui_twice_button.h"

/*----�l�[���X�y�[�X-------------------------------------------------*/
using namespace iruna;
using namespace core;
using namespace	graphics;
using namespace io;

//=====================================================================
//
//	�N���X��	:	ModelConverter
//	����		:	�R���o�[�^�[�S�̂̊Ǘ�
//
//=====================================================================
class ModelConverter
{
private:

	GuiFrame*			guiFrame;		//	�E��GUI�n�Ǘ��N���X
	TwiceButton*		guiTwiceBut;	//	�Đ���~�{�^��

	ModelLoader*		loader;			//	���f���̃f�R�[�_�[�N���X
	ModelRender*		render;			//	���f�������_�����O�N���X
	SgdEncoder*			encoder;		//	SGD�G���R�[�_�[
	bool				renderFlag;		//	�����_�����O�t���O
	Camera				camera;			//	�J����
	DeviceController	device_render;	//	�����_�����O�f�o�C�X

	AnimetionInput*		animeInput;		//	�A�j���[�V�����t���[���ݒ�N���X
	float				animeFlame;		//	�A�j���[�V�����t���[��

	BarIcon*			bar;			//	�o�[�A�C�R��

public:
	//--------------------------------------------------------------------
	// 
	//	����	:	�R���X�g���N�^
	// 
	//--------------------------------------------------------------------
	ModelConverter();

	//--------------------------------------------------------------------
	// 
	//	����	:	�f�X�g���N�^
	// 
	//--------------------------------------------------------------------
	~ModelConverter();

	//--------------------------------------------------------------------
	// 
	//	����	:	�X�V
	// 
	//--------------------------------------------------------------------
	void UpDate();

	//--------------------------------------------------------------------
	// 
	//	����	:	�`��
	// 
	//--------------------------------------------------------------------
	void Draw();

};

#endif	//	MODEL_CONVERTER_H	end