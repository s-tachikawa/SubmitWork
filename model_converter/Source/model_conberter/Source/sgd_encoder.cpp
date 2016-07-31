//---------------------------------------------------------
// 
//	sgd_encoder.h
//	指定したモデルデータからSGDデータへ変換する
//	更新日 11月05日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード---------------------------------*/
#include "../Include/sgd_encoder.h"

//	コンストラクタ
SgdEncoder::SgdEncoder()
:	modelPath( NULL )
{
	return;
}

//	デストラクタ
SgdEncoder::~SgdEncoder()
{
	if( modelPath != NULL )
		SafeArrayDelete( modelPath );


	return;
}

//	モデルデータの保存
bool SgdEncoder::SgdEncode( std::string save_path, ModelData* saveData )
{
	if( saveData == NULL )
	{
		MessageBox( 0 , "モデルデータが破損しているかまたは作成されていません。", NULL , MB_OK);
		return false;
	}
	FILE* fp;

	int size = save_path.size();
	int npos = save_path.rfind( '\\', size );
	// スラッシュがある場所の長さから最大の長さを引き文字の長さを得る
	
	modelPath		= new char[ ( size - npos ) + 4 ];

	modelPath[ ( size - npos + 4 ) - 1 ] = '\0';
	
	for( int i = 0; ( i +  npos ) < size; i++ )
	{
		modelPath[ i ]		= save_path[ (npos + 1) + i ];
	
	}
	strcat( modelPath, ".sgd" );

	//	ファイル書き込み失敗
	fp = fopen( modelPath, "wb" );

	if( fp == NULL)
	{
		return false;
	}

	// メッシュカウント
	fwrite( &saveData->meshCount, sizeof( int ), 1, fp );

	//	アニメーションカウントの保存
	fwrite( &saveData->animeCount, sizeof( int ), 1, fp );
	
	// メッシュデータの書き込み
	for( int i = 0; i < ( int )saveData->mesh.size(); i++ )
	{
		// 頂点数
		fwrite( &saveData->mesh[ i ]->countData.vertexCount, sizeof( int ), 1, fp );

		//	頂点データ
		for( int k = 0; k < ( int )saveData->mesh[ i ]->countData.vertexCount; k++ )
		{
			fwrite( &saveData->mesh[ i ]->vertex[ k ].pos,			sizeof( float ) * 3, 1, fp );
			fwrite( &saveData->mesh[ i ]->vertex[ k ].normal,		sizeof( float ) * 3, 1, fp );
			fwrite( &saveData->mesh[ i ]->vertex[ k ].uv,			sizeof( float ) * 2, 1, fp );
			fwrite( saveData->mesh[ i ]->blending[ k ].boneIndex,	sizeof( int )	* 4, 1, fp );
			fwrite( saveData->mesh[ i ]->blending[ k ].weight,		sizeof( float ) * 4, 1, fp );
		}

		//	インデックス数,ポリゴン数
		fwrite( &saveData->mesh[ i ]->countData.indexCount, sizeof( int ), 1, fp );
		fwrite( &saveData->mesh[ i ]->countData.porygonCount, sizeof( int ), 1, fp );
		
		//	インデックスデータ
		for( int k = 0; k < saveData->mesh[ i ]->countData.indexCount; k++ )
		{
			fwrite( &saveData->mesh[ i ]->index[ k ], sizeof( int ), 1, fp );
		}

		//	マテリアルカウント
		fwrite( &saveData->mesh[ i ]->countData.materialCount, sizeof( int ), 1, fp );
		
		//	マテリアルデータ
		for( int k = 0; k < saveData->mesh[ i ]->countData.materialCount; k++ )
		{
			
			fwrite( &saveData->mesh[ i ]->material[ k ].material.diffuse	, sizeof( float ) * 4	, 1, fp );
			fwrite( &saveData->mesh[ i ]->material[ k ].material.ambient	, sizeof( float ) * 4	, 1, fp );
			fwrite( &saveData->mesh[ i ]->material[ k ].material.specular	, sizeof( float ) * 4	, 1, fp );
			fwrite( &saveData->mesh[ i ]->material[ k ].material.emissive	, sizeof( float ) * 4	, 1, fp );
			fwrite( &saveData->mesh[ i ]->material[ k ].power				, sizeof( float )		, 1, fp );

		}

		// ボーン数
		fwrite( &saveData->mesh[ i ]->boneCount	, sizeof( int ), 1, fp );

		// ボーンが存在しない場合は書き込まない
		if( saveData->mesh[ i ]->boneCount > 0 )
		{
			for( int k = 0; k < saveData->mesh[ i ]->boneCount; k++ )
			{
				//	ボーンの親ID
				fwrite( &saveData->mesh[ i ]->bone[ k ].parentId	, sizeof( int ), 1, fp );
				//	ボーンの初期姿勢
				fwrite( &saveData->mesh[ i ]->bone[ k ].init		, sizeof( float ) * 16, 1, fp );
				//	ボーンアニメーションデータの保存
				for( int j = 0; j < saveData->animeCount + 1; j++ )
				{
					fwrite( &saveData->mesh[ i ]->bone[ k ].boneMat[ j ]	, sizeof( float ) * 16, 1, fp );
				}
			}
			
		}
		//	階層アニメーションデータ
		for( int k = 0; k < saveData->animeCount + 1; k++ )
		{
			fwrite( &saveData->mesh[ i ]->tran[ k ]	, sizeof( float ) * 16, 1, fp );
		}
	}

	//	モデルのデータ書き込み完了
	fclose( fp );

	return true;
}