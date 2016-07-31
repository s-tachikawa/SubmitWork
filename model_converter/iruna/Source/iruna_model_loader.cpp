//---------------------------------------------------------
// 
//	iruna_model_loader.h
//	�w�肵�����f���f�[�^�ǂݍ���
//	�쐬�� 10��21��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
#include "../Include/iruna_model_loader.h"
#include "../Source/iruna_model_decoder.h"
#include "../Source/iruna_sgd_decoder.h"
#include "../Source/iruna_fbx_decoder.h"

namespace iruna
{
namespace graphics
{
//	�R���X�g���N�^
ModelLoader::ModelLoader()
	:loader( NULL )
{
	return;
}

//	�f�X�g���N�^
ModelLoader::~ModelLoader()
{
	Relese();

	return;
}

// �������
void ModelLoader::Relese()
{

	if( loader != NULL )
	{
		loader->Relese();
		SafeDelete( loader );
	}
	return;
}

// �w�肵���t�@�C���̓ǂݍ���
bool ModelLoader::Load( std::string in_path, int in_flame )
{		
	int size = in_path.size();
	int npos = in_path.rfind( '.', size );
	char temp[ 5 ];
	
	temp[ 4 ] = '\0';

	for(  int i = 0; i < 4;i++ )
	{
		temp[ i ] = in_path[ npos + i ];
	}

	//	SGD�Ƃ��ēǂݍ���
	if( strcmp( temp, ".sgd" ) == 0 )
	{
		loader = new SgdDecoder;
	}

	// FBX�Ƃ��ēǂݍ���
	if( strcmp( temp, ".fbx" ) == 0 ||  strcmp( temp, ".FBX" ) == 0)
	{
		loader = new FbxDecoder;
	}

	//	�ݒ肳��Ă��Ȃ��g���q
	if( loader == NULL )
	{
		MessageBox( NULL ,"�Ή����Ă��Ȃ����f���g���q�ł��B" , "ModelLoader" , MB_OK );
		return false;
	}

	loader->Init();

	
	return loader->Decode( in_path, in_flame );

}

ModelData* ModelLoader::GetModelData()
{
	if( loader != NULL )
		return loader->GetModelData();

	return NULL;
}

}	//	graphics	end
}	//	iruna		end