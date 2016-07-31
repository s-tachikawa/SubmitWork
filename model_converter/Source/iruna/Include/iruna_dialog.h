//---------------------------------------------------------
// 
//	iruna_dialog.h
//	windows�_�C�A���O���o��
//	�쐬�� 10��21��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
#ifndef IRUNA_DIALOG_H
#define IRUNA_DIALOG_H

#include "../Include/iruna_utility.h"

namespace iruna
{
namespace core
{

/*----�O���[�o���ϐ���`---------------------------------*/
extern LPCTSTR			CD_FILTER_LOAD_MODEL;	//	�ǂݍ��ރt�@�C��(���f��)
extern LPCTSTR			CD_FILTER_SAVE_MODEL;	//	�������ރt�@�C��(���f��)
extern LPCTSTR			CD_FILTER_TEXTURE;		//	�ǂݍ��ރt�@�C��(�e�N�X�`��)
extern LPCTSTR			CD_FILTER_SHEDER;		//	�ǂݍ��ރt�@�C��(�V�F�[�_�[)

extern const DWORD		CD_FLAGS_SAVE;		//	�_�C�A���O�t���O(SAVE)
extern const DWORD		CD_FLAGS_LOAD;		//	�_�C�A���O�t���O(LOAD)

/*----�O���[�o���֐���`---------------------------------*/
//--------------------------------------------------------------------
// 
//	����	:	���O�����ĕۑ��_�C�A���O�̍쐬
//	�����	:	���� �Ė�
//	�쐬��	:	2011/10/21	- �쐬
// 
//--------------------------------------------------------------------
extern int				SaveDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath );

//--------------------------------------------------------------------
// 
//	����	:	�J���_�C�A���O�̍쐬
//	�����	:	���� �Ė�
//	�쐬��	:	2011/10/21	- �쐬
// 
//--------------------------------------------------------------------
extern int				LoadDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath );

}	//	core
}	//	iruna


#endif	//	IRUNA_DIALOG_H	end