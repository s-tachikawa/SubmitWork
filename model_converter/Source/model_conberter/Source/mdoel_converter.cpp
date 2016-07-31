//---------------------------------------------------------
// 
//	model_converter.cpp
//	�A�v���P�[�V�����̃��C��
//	�쐬�� 10��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
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

	// �J�����̐ݒ�
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
	
		// ���f���f�[�^�̓ǂݍ���
		if( guiFrame->GetButtonState( GuiButton::MODEL ) == GuiButton::PUSH )
		{
		
			LoadDialog( path, CD_FILTER_LOAD_MODEL, CD_FLAGS_LOAD, true );

			animeInput->SetAnimetionFlame( animeFlame );
			animeInput->Show();
			
			animeFlame = animeInput->GetAnimetionFlame();
			bar->SetSliderMax( animeFlame );

			int hr = MessageBox( NULL ,"���f���f�[�^�̓ǂݍ��݂��s���܂��B�ȑO�̃f�[�^�͏����Ă��܂��̂ŋC�����Ă��������B" , "ModelLoad" , MB_YESNO );

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
		// �e�N�X�`���̓ǂݍ���
		if( guiFrame->GetButtonState( GuiButton::TEXTURE ) == GuiButton::PUSH )
		{
			LoadDialog( path, CD_FILTER_TEXTURE, CD_FLAGS_LOAD, true );
			int hr = MessageBox( NULL ,"�e�N�X�`�����㏑�����܂����H" , "TextureLoad" , MB_YESNO );

			if( hr == IDYES )
			{
				render->CreateTexture( path );
			}
		}

		//	SGD�t�@�C���ŕۑ�
		if( guiFrame->GetButtonState( GuiButton::SAVE ) == GuiButton::PUSH )
		{
			SaveDialog( path,CD_FILTER_SAVE_MODEL, CD_FLAGS_SAVE, true );
			encoder->SgdEncode( path, loader->GetModelData() );
		}

	}
	//	���f���̍X�V
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


	//	GUI�̍X�V
	guiFrame->UpDate();
	guiTwiceBut->UpDate();

	//	�A�j���[�V�����o�[�̍X�V
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