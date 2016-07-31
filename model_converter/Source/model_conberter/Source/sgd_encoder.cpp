//---------------------------------------------------------
// 
//	sgd_encoder.h
//	�w�肵�����f���f�[�^����SGD�f�[�^�֕ϊ�����
//	�X�V�� 11��05��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h---------------------------------*/
#include "../Include/sgd_encoder.h"

//	�R���X�g���N�^
SgdEncoder::SgdEncoder()
:	modelPath( NULL )
{
	return;
}

//	�f�X�g���N�^
SgdEncoder::~SgdEncoder()
{
	if( modelPath != NULL )
		SafeArrayDelete( modelPath );


	return;
}

//	���f���f�[�^�̕ۑ�
bool SgdEncoder::SgdEncode( std::string save_path, ModelData* saveData )
{
	if( saveData == NULL )
	{
		MessageBox( 0 , "���f���f�[�^���j�����Ă��邩�܂��͍쐬����Ă��܂���B", NULL , MB_OK);
		return false;
	}
	FILE* fp;

	int size = save_path.size();
	int npos = save_path.rfind( '\\', size );
	// �X���b�V��������ꏊ�̒�������ő�̒��������������̒����𓾂�
	
	modelPath		= new char[ ( size - npos ) + 4 ];

	modelPath[ ( size - npos + 4 ) - 1 ] = '\0';
	
	for( int i = 0; ( i +  npos ) < size; i++ )
	{
		modelPath[ i ]		= save_path[ (npos + 1) + i ];
	
	}
	strcat( modelPath, ".sgd" );

	//	�t�@�C���������ݎ��s
	fp = fopen( modelPath, "wb" );

	if( fp == NULL)
	{
		return false;
	}

	// ���b�V���J�E���g
	fwrite( &saveData->meshCount, sizeof( int ), 1, fp );

	//	�A�j���[�V�����J�E���g�̕ۑ�
	fwrite( &saveData->animeCount, sizeof( int ), 1, fp );
	
	// ���b�V���f�[�^�̏�������
	for( int i = 0; i < ( int )saveData->mesh.size(); i++ )
	{
		// ���_��
		fwrite( &saveData->mesh[ i ]->countData.vertexCount, sizeof( int ), 1, fp );

		//	���_�f�[�^
		for( int k = 0; k < ( int )saveData->mesh[ i ]->countData.vertexCount; k++ )
		{
			fwrite( &saveData->mesh[ i ]->vertex[ k ].pos,			sizeof( float ) * 3, 1, fp );
			fwrite( &saveData->mesh[ i ]->vertex[ k ].normal,		sizeof( float ) * 3, 1, fp );
			fwrite( &saveData->mesh[ i ]->vertex[ k ].uv,			sizeof( float ) * 2, 1, fp );
			fwrite( saveData->mesh[ i ]->blending[ k ].boneIndex,	sizeof( int )	* 4, 1, fp );
			fwrite( saveData->mesh[ i ]->blending[ k ].weight,		sizeof( float ) * 4, 1, fp );
		}

		//	�C���f�b�N�X��,�|���S����
		fwrite( &saveData->mesh[ i ]->countData.indexCount, sizeof( int ), 1, fp );
		fwrite( &saveData->mesh[ i ]->countData.porygonCount, sizeof( int ), 1, fp );
		
		//	�C���f�b�N�X�f�[�^
		for( int k = 0; k < saveData->mesh[ i ]->countData.indexCount; k++ )
		{
			fwrite( &saveData->mesh[ i ]->index[ k ], sizeof( int ), 1, fp );
		}

		//	�}�e���A���J�E���g
		fwrite( &saveData->mesh[ i ]->countData.materialCount, sizeof( int ), 1, fp );
		
		//	�}�e���A���f�[�^
		for( int k = 0; k < saveData->mesh[ i ]->countData.materialCount; k++ )
		{
			
			fwrite( &saveData->mesh[ i ]->material[ k ].material.diffuse	, sizeof( float ) * 4	, 1, fp );
			fwrite( &saveData->mesh[ i ]->material[ k ].material.ambient	, sizeof( float ) * 4	, 1, fp );
			fwrite( &saveData->mesh[ i ]->material[ k ].material.specular	, sizeof( float ) * 4	, 1, fp );
			fwrite( &saveData->mesh[ i ]->material[ k ].material.emissive	, sizeof( float ) * 4	, 1, fp );
			fwrite( &saveData->mesh[ i ]->material[ k ].power				, sizeof( float )		, 1, fp );

		}

		// �{�[����
		fwrite( &saveData->mesh[ i ]->boneCount	, sizeof( int ), 1, fp );

		// �{�[�������݂��Ȃ��ꍇ�͏������܂Ȃ�
		if( saveData->mesh[ i ]->boneCount > 0 )
		{
			for( int k = 0; k < saveData->mesh[ i ]->boneCount; k++ )
			{
				//	�{�[���̐eID
				fwrite( &saveData->mesh[ i ]->bone[ k ].parentId	, sizeof( int ), 1, fp );
				//	�{�[���̏����p��
				fwrite( &saveData->mesh[ i ]->bone[ k ].init		, sizeof( float ) * 16, 1, fp );
				//	�{�[���A�j���[�V�����f�[�^�̕ۑ�
				for( int j = 0; j < saveData->animeCount + 1; j++ )
				{
					fwrite( &saveData->mesh[ i ]->bone[ k ].boneMat[ j ]	, sizeof( float ) * 16, 1, fp );
				}
			}
			
		}
		//	�K�w�A�j���[�V�����f�[�^
		for( int k = 0; k < saveData->animeCount + 1; k++ )
		{
			fwrite( &saveData->mesh[ i ]->tran[ k ]	, sizeof( float ) * 16, 1, fp );
		}
	}

	//	���f���̃f�[�^�������݊���
	fclose( fp );

	return true;
}