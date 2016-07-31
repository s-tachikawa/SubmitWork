//---------------------------------------------------------
// 
//	model_converter.cpp
//	アプリケーションのメイン
//	作成日 10月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/model_converter.h"

ModelConverter::ModelConverter()
	:	guiFrame( NULL ),
		loader( NULL ),
		render( NULL )
{

	guiFrame		= new GuiFrame;
	loader			= new ModelLoader;
	render			= new ModelRender;
	encoder			= new SgdEncoder;

	// カメラの設定
	camera.eye		= math::Vector3( 0.f, 20.f, 50.f );
	camera.lookAt	= math::Vector3( 0.f, 0.f, 0.f );
	camera.upVector	= math::Vector3( 0.f, 1.f, 0.f );
	camera.fovY		= D3DX_PI / 4;
	camera.aspect	= 800.f / 600.f;
	camera.zNear	= 1.f;
	camera.zFar		= 500.f;

	renderFlag = false;

	animeInput = new AnimetionInput;
	animeInput->Init();

	bar = new BarIcon;
	bar->SetSliderMax( 0 );
	bar->SetPos( math::Vector2( 650, 300 ) );


	guiTwiceBut = new TwiceButton;
	guiTwiceBut->Init(	math::Vector2( 610, 285 ),
						math::Vector2( 30,30 ) );

	animeFlame = 0;

	return;
}
ModelConverter::~ModelConverter()
{
	if( guiFrame != NULL )
		SafeDelete( guiFrame );

	if( loader != NULL )
	{
		loader->Relese();
		SafeDelete( loader );
	}

	if( render != NULL )
		SafeDelete( render );

	if( encoder != NULL )
		SafeDelete( encoder );

	if( animeInput != NULL )
	{
		animeInput->Relese();
		SafeDelete( animeInput );
	}
	if( bar != NULL )
		SafeDelete( bar );

	if( guiTwiceBut != NULL )
		SafeDelete( guiTwiceBut );
	return;
}

void ModelConverter::UpDate()
{


	if( io::CheckMouseState( io::MouseButton::LEFT ) == io::INPUT_RELEASED )
	{
		TCHAR	path[3267];
	
		// モデルデータの読み込み
		if( guiFrame->GetButtonState( GuiButton::MODEL ) == GuiButton::PUSH )
		{
		
			LoadDialog( path, CD_FILTER_LOAD_MODEL, CD_FLAGS_LOAD, true );

			animeInput->SetAnimetionFlame( animeFlame );
			animeInput->Show();
			
			animeFlame = animeInput->GetAnimetionFlame();
			bar->SetSliderMax( animeFlame );

			int hr = MessageBox( NULL ,"モデルデータの読み込みを行います。以前のデータは消えてしまうので気をつけてください。" , "ModelLoad" , MB_YESNO );

			if( hr == IDYES )
			{
				if( loader != NULL )
				{
					loader->Relese();
					SafeDelete( loader );
					loader			= new ModelLoader;
				}
				if( loader->Load( path, animeFlame ))
				{
					render->CreateModel( loader->GetModelData() );
					renderFlag = true;
				}
			}

		}
		// テクスチャの読み込み
		if( guiFrame->GetButtonState( GuiButton::TEXTURE ) == GuiButton::PUSH )
		{
			LoadDialog( path, CD_FILTER_TEXTURE, CD_FLAGS_LOAD, true );
			int hr = MessageBox( NULL ,"テクスチャを上書きしますか？" , "TextureLoad" , MB_YESNO );

			if( hr == IDYES )
			{
				render->CreateTexture( path );
			}
		}

		//	SGDファイルで保存
		if( guiFrame->GetButtonState( GuiButton::SAVE ) == GuiButton::PUSH )
		{
			SaveDialog( path,CD_FILTER_SAVE_MODEL, CD_FLAGS_SAVE, true );
			encoder->SgdEncode( path, loader->GetModelData() );
		}

	}
	//	モデルの更新
	if( renderFlag )
	{
		if( guiTwiceBut->GetState() )
		{
			animeFlame += 0.5f;

			if( loader->GetModelData()->animeCount < animeFlame )
				animeFlame = 0;

			bar->SetValue( animeFlame );
		}
		else
		{
			animeFlame = bar->GetValue();
		}
		
		render->SetAnimetionFlame( animeFlame );
		render->UpDate();
	}


	//	GUIの更新
	guiFrame->UpDate();
	guiTwiceBut->UpDate();

	//	アニメーションバーの更新
	bar->UpDate();

	return;
}
void ModelConverter::Draw()
{

	
	if( renderFlag )
		render->Draw();

	device_render.SetTransform( D3DTS_VIEW ,camera.GetView());
	device_render.SetTransform( D3DTS_PROJECTION ,camera.GetProjection());
	guiFrame->Draw();

	guiTwiceBut->Draw( );

	DrawFormatString( 650, 250, Color4( 255,255,255,255 ), "anime:%d",bar->GetValue() );
	bar->Draw();

	return;
}