
#include "../../iruna/Include/iruna.h"
#include "../Include/model_converter.h"

using namespace iruna;
using namespace	graphics;
using namespace core;

int WINAPI WinMain( HINSTANCE , HINSTANCE, LPTSTR, int )
{

	//_CrtSetBreakAlloc( 286273 );

	// ライブラリ管理クラス
	// ライブラリの起動、一番最初にする
	System*	system	= &System::GetInstance();
	if( !system->Setup( 800, 700, true,  "FBXConberter" ) )	// WS_POPUPで枠が消える
		return -1;

	ModelConverter* converter = new ModelConverter;

	//ModelLoader*		loader = new ModelLoader;
	//ModelRender*		render = new ModelRender;
	//DeviceController	render_device;

	// //カメラの設定
	//float cameraUp = 4.0f;
	//float cameraAngle= 0.0f;
	//Camera camera;
	//camera.eye		= math::Vector3( 0.f, 20.f, 50.f );
	//camera.lookAt	= math::Vector3( 0.f, 0.f, 0.f );
	//camera.upVector	= math::Vector3( 0.f, 1.f, 0.f );
	//camera.fovY		= D3DX_PI / cameraUp;
	//camera.aspect	= 800.f / 600.f;
	//camera.zNear	= 0.1f;
	//camera.zFar		= 1000.f;

	//loader->Load( "../Resource/model/tank_tex_anim.fbx" );
	//render->CreateModel( loader->GetModelData() );


	// メインループ
	while( system->Run() )
	{
	
		// ウィンドウがアクティブの時だけ実行
		if( system->IsActive() )
		{

			converter->UpDate();

			
		//if( io::CheckKeyState( DIK_LEFT ) == io::INPUT_PUSHED)
		//	cameraAngle	+= 0.1f;
		//if( io::CheckKeyState( DIK_RIGHT ) == io::INPUT_PUSHED )
		//	cameraAngle	-= 0.1f;

		//if( io::CheckKeyState( DIK_UP )== io::INPUT_PUSHED )
		//	cameraUp	 += 0.1f;
		//if( io::CheckKeyState( DIK_DOWN ) == io::INPUT_PUSHED)
		//	cameraUp	-= 0.1f;

		//	camera.fovY			= D3DX_PI / cameraUp;
		//	camera.eye.x		= sinf( cameraAngle ) * 300;
		//	camera.eye.z		= cosf( cameraAngle ) * 300;

		//	render_device.SetTransform( D3DTS_VIEW, camera.GetView() );
		//	render_device.SetTransform( D3DTS_PROJECTION, camera.GetProjection() );

		//	render->UpDate();

			ClearScreen();

			converter->Draw();
			

			//math::WoldMatrix mat;
			//mat.SetTranslation( 0, 0, 0 );
			//render->Draw( mat );

			//render_device.SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
			DrawFormatString( 0, 0, Color4( 255, 255, 0 ),  "FPS[%.1f]" , FrameRateManage::GetFrameRate() );

			// 描画終了
			SwapScreen();
		}

		// ウィンドウがノンアクティブの時の処理
		else
			system->Idle();

		
	}

	//loader->Relese();
	//SafeDelete( loader );
	//SafeDelete( render );

	SafeDelete( converter );

	// ライブラリの終了
	system->Release();

	return 0;
}
