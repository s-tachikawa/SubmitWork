//---------------------------------------------------------
// 
//	iruna.h
//	iruna���C�u�����̈ꊇ�C���N���[�h
//	�쐬�� 6��22��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_H
#define IRUNA_H

/*----�C���N���[�h-------------------------------------------------*/

// �R�A�n
#include "../Include/iruna_core.h"

// �V�X�e���n
#include "../Include/iruna_system.h"

// �O���t�B�b�N�X�n
#include "../Include/iruna_graphics.h"

// I/O�n
#include "../Include/iruna_io.h"

// ���w�n
#include "../Include/iruna_math.h"

// ���[�e�B���e�B�n
#include "../Include/iruna_utility.h"

// �T�E���h�n
#include "../Include/iruna_sound.h"

/*----�v���v���Z�b�T�f�B���N�e�B�u---------------------------------*/
#ifdef _DEBUG
#pragma comment ( lib, "iruna_d.lib"	)

#else
#pragma comment ( lib, "iruna.lib"	)

#endif


#endif	//	IRUNA_H	end