//---------------------------------------------------------
// 
//	iruna_types.h
//	�^��`
//	�쐬�� 6��22��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_TYPES_H
#define IRUNA_TYPES_H

/*----�C���N���[�h-------------------------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#include <xaudio2.h>

// dinput.h��ǂݍ��ޑO�ɐ錾���Ȃ���΂Ȃ�Ȃ�
#ifndef DIRECTINPUT_VERSION
	#define	DIRECTINPUT_VERSION	0x0800
#endif
#include <dinput.h>

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{

typedef unsigned char				U_CHAR;
typedef unsigned short				U_SHORT;
typedef unsigned int				U_INT;
typedef unsigned long				U_LONG;

} // iruna end


#endif // IRUNA_TYPES_H