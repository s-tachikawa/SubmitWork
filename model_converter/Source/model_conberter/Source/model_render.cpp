#include "../Include/model_render.h"

ModelRender::ModelRender()
		:	texture( NULL ),
			effect( NULL ),
			dec( NULL )
{

	//頂点デクラレーションの設定
	static VertexDeclaration::Element MODEL_ELEMENT[] = {
				{0 , 0 , D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_POSITION , 0 },

				{1 , 0 , D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_NORMAL , 0 },

				{2 , 0 , D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_TEXCOORD , 0 },

				{3 , 0 , D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_BLENDWEIGHT , 0 },

				{4 , 0 , D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_BLENDINDICES , 0 },
				D3DDECL_END()	
	 };

	dec = new VertexDeclaration;
	dec->Create( MODEL_ELEMENT );

	//シェーダー設定
	effect = new Effect;
	bool a = effect->Create( "../Resource/effect/SkinningStandard.fx", 1 );
	effect->SetTechnique( "SkinningStandard" );

	texture = new Texture;
	texture->Load( "../Resource/texture/StandardTex.png" );

	modelPos = math::Vector3( 0.0f,0,0 );
	modelAngle = math::Vector3( 0.0f,0,0 );
	wold.SetTranslation( modelPos.x, modelPos.y, modelPos.z );

	animeFlame = 0;

	//	カメラの初期化
	cameraUp = 4.0f;
	cameraAngle= 0.0f;
	camera.eye		= math::Vector3( 0.f, 20.f, 200.f );
	camera.lookAt	= math::Vector3( 0.f, 0.f, 0.f );
	camera.upVector	= math::Vector3( 0.f, 1.f, 0.f );
	camera.fovY		= D3DX_PI / cameraUp;
	camera.aspect	= 800.f / 700.f;
	camera.zNear	= 1.f;
	camera.zFar		= 1000.f;

	oldPos.x = 400;
	oldPos.y = 350;
	newPos = oldPos;

	modelScale = 1.0f;

	return;
}
ModelRender::~ModelRender()
{
	if( texture != NULL )	
		SafeDelete( texture );
	if( effect != NULL )
		SafeDelete( effect );
	if( dec != NULL )
		SafeDelete( dec );

}
// モデル更新
void ModelRender::UpDate()
{
		
	////	アニメーションフレームが超えないようにする
	//if( animeFlame > modelData->animeCount ) animeFlame = 0.0f;

	//スキニング行列の作成( FBXから取得した行列はすでに姿勢行列になっているのでそのままオフセット行列のかければいい )
	for( int i = 0; i < ( int )modelData->mesh.size(); i++ )
	{
		for( int k = 0; k < modelData->mesh[ i ]->boneCount; k++ )
		{
			modelData->mesh[ i ]->bone[ k ].skin = modelData->mesh[ i ]->bone[ k ].offset * modelData->mesh[ i ]->bone[ k ].boneMat[ (int)animeFlame ];
		}
	}

	// モデルの拡大･移動･回転処理
	modelScale += ( io::GetMouseWheel() * 0.01f );
	wold.SetScal( modelScale * -1,modelScale,modelScale );

	//	マウスでのモデル操作
	POINT temp = io::GetMousePosition();
	if( temp.x < 600 )
	{
		if( io::CheckMouseState(io::MouseButton::LEFT ) == io::INPUT_PUSH ||
			io::CheckMouseState(io::MouseButton::RIGHT ) == io::INPUT_PUSH)
			newPos = io::GetMousePosition();

		if( io::CheckMouseState(io::MouseButton::LEFT ) == io::INPUT_PUSHED )
		{
			oldPos = io::GetMousePosition();
			modelPos.x = -( oldPos.x - newPos.x ) * 0.1f;
			modelPos.y = -( oldPos.y - newPos.y ) * 0.1f;
			wold.SetTranslation( modelPos.x, modelPos.y, 0.0f );
		}
		if( io::CheckMouseState(io::MouseButton::RIGHT ) == io::INPUT_PUSHED )
		{
			oldPos = io::GetMousePosition();
			modelAngle.y = (oldPos.x - newPos.x) * 0.01f;
			modelAngle.x = (oldPos.y - newPos.y) * 0.01f;
			wold.SetRotation( modelAngle.x, modelAngle.y, 0.0f );

		}
	}

	return;
}
// 描画するモデルデータの作成
void ModelRender::CreateModel( ModelData* data )
{
	
	if( data != NULL && modelData != NULL )
	{
		modelData = data;
	}

	return;
}

//	アニメーションフレームをセットする
void ModelRender::SetAnimetionFlame( float in_flame )
{
	animeFlame = in_flame;
	return;
}

//	モデルに貼り付けるテクスチャの作成
void ModelRender::CreateTexture( std::string in_path )
{
	if( texture != NULL )
	{
		SafeDelete( texture );
		texture = new Texture;

		texture->Load( in_path.c_str() );
	}
	return;
}

//	モデルの描画
void ModelRender::Draw()
{

	render.SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	

	effect->SetMatrix( "view", camera.GetView() );
	effect->SetMatrix( "projection", camera.GetProjection() );
	effect->SetTexture( "tex", texture->GetTexture() );

	for( int i = 0; i < ( int )modelData->mesh.size(); i++ )
	{
		bool flag = false;
		if( modelData->mesh[ i ]->boneCount > 0 )
			flag = true;

		//	スキニング行列のセット
		math::Matrix mat[ 35 ];
		for( int k = 0; k < 35; k++ )
			D3DXMatrixIdentity( &mat[ k ] );

		for( int k = 0; k < modelData->mesh[ i ]->boneCount; k++)
		{
			mat[ k ] = modelData->mesh[ i ]->bone[ k ].skin;
		}
		effect->SetMatrixArayy( "skinMat" , mat, 35 );


		if( modelData->mesh[ i ]->tran.size() > 0 )
		{
			effect->SetMatrix( "world", modelData->mesh[ i ]->tran[ (int)animeFlame ] * wold.GetWoldMatrix() );
		}	
		else
		{
			effect->SetMatrix( "world", wold.GetWoldMatrix() );
		}

		modelData->mesh[ i ]->vertexBuffer[ 0 ].IntoStream( 0 );
		modelData->mesh[ i ]->vertexBuffer[ 1 ].IntoStream( 1 );
		modelData->mesh[ i ]->vertexBuffer[ 2 ].IntoStream( 2 );
		modelData->mesh[ i ]->vertexBuffer[ 3 ].IntoStream( 3 );
		modelData->mesh[ i ]->vertexBuffer[ 4 ].IntoStream( 4 );
		modelData->mesh[ i ]->indexBuffer->IntoIndices();

		dec->Set();

		effect->Begin( 0, 0 );
		if( flag )
		{
			effect->BeginPass( 0 );
		}
		else 
		{
			effect->BeginPass( 1 );
		}

		render.SetTexture( 0, texture->GetTexture() );
		render.SetMaterial( modelData->mesh[ i ]->material[ 0 ].material );
		render.DrawIndexPrimitive(	Primitive::TRIANGLE_LIST,
									modelData->mesh[ i ]->countData.vertexCount,
									modelData->mesh[ i ]->countData.porygonCount
									);
	
		effect->EndPass();
		effect->End();
	}

	return;
}