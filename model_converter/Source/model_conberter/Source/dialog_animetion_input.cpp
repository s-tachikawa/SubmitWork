//---------------------------------------------------------
// 
//	diaolg_animetion_input.h
//	アニメーションフレームをセットするダイアログの管理
//	作成日 1月5日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード-------------------------------------------------*/
#include "../Include/dialog_animetion_input.h"

/*----グローバル変数定義-------------------------------------------------*/
static LPCTSTR			CLASS_NAME			= _T( "_ANIMETION_SET_DIALOG" );
static const int		WND_COM_ID_OK		= 1;

//	コンストラクタ
AnimetionInput::AnimetionInput()
{
	dialog = NULL;

	return;
}

//	デストラクタ
AnimetionInput::~AnimetionInput()
{
	Relese();
	return;
}

//	ダイアログの初期化
int AnimetionInput::Init()
{
	//	ダイアログに使用する
	HINSTANCE			hInst			= GetModuleHandle( NULL );
	WNDCLASS			wndClass;

	wndClass.style				= ( CS_HREDRAW | CS_VREDRAW );
	wndClass.lpfnWndProc		= Procedure;
	wndClass.cbClsExtra			= 0;
	wndClass.cbWndExtra			= 0;
	wndClass.hInstance			= hInst;
	wndClass.hIcon				= LoadIcon( NULL, IDI_APPLICATION );
	wndClass.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wndClass.hbrBackground		= reinterpret_cast<HBRUSH>( GetStockObject( 0 ) );
	wndClass.lpszMenuName		= NULL;
	wndClass.lpszClassName		= CLASS_NAME;

	RegisterClass( &wndClass );

	dialog = CreateWindow(
		CLASS_NAME,
		_T( "アニメーションフレームの入力" ),
		0,
		400,
		300,
		200,
		150,
		NULL,
		NULL,
		hInst,
		NULL
	);

	if( dialog == NULL )
		return -1;

	animetionSet = CreateWindow(
		_T( "EDIT" ),
		_T( "" ),
		( WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT ),
		80,
		50,
		80,
		22,
		dialog,
		NULL,
		hInst,
		NULL
	);

	CreateWindow(
		_T( "BUTTON" ),
		_T( "OK" ),
		( WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT ),
		100,
		90,
		60,
		22,
		dialog,
		reinterpret_cast<HMENU>( WND_COM_ID_OK ),
		hInst,
		NULL
	);


	//	初期化に成功
	return 0;
}

//	解放処理
void AnimetionInput::Relese()
{
	if( dialog == NULL )
		return;

	DestroyWindow( animetionSet );
	DestroyWindow( dialog );

	UnregisterClass( CLASS_NAME, GetModuleHandle( NULL ) );
	return;
}

//	ダイアログの更新
void AnimetionInput::Show() const
{
	HDC			hdc			= GetDC( dialog );
	MSG			msg;

	System::GetInstance().Run();

	ShowWindow( dialog, SW_SHOW );

	TextOut( hdc, 30, 10, "flameCount", 10 );

	while( GetMessage( &msg, NULL, 0, 0 ) > 0 ){
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	ShowWindow( dialog, SW_HIDE );

	ReleaseDC( dialog, hdc );

	return;
}

//	アニメーションフレームの設定
void AnimetionInput::SetAnimetionFlame( int animetionFlame )
{
	TCHAR		temp[16];

	_itot_s( animetionFlame, temp, 16, 10 );
	SetWindowText( animetionSet, temp );
	return;
}

//	アニメーションフレームの取得
int AnimetionInput::GetAnimetionFlame() const
{
	TCHAR		temp[16];

	GetWindowText( animetionSet, temp, 16 );

	return static_cast< int >( atoi( temp ) );

}

LRESULT CALLBACK AnimetionInput::Procedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg ){
		case WM_COMMAND:
			if( LOWORD( wParam ) != WND_COM_ID_OK )
				break;

			PostQuitMessage( 0 );

			return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}
