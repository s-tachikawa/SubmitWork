//---------------------------------------------------------
// 
//	iruna_device.cpp
//	�f�o�C�X�̊Ǘ��Ɛ���
//	�쐬�� 6��22��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Source/iruna_device.h"

/*----�v���v���Z�b�T�f�B���N�e�B�u---------------------------------*/
#ifdef _DEBUG
#pragma comment ( lib, "d3dx9d.lib"	)

#else
#pragma comment ( lib, "d3dx9.lib"	)

#endif

#pragma comment ( lib, "d3d9.lib"	)
#pragma comment ( lib, "d3dxof.lib"	)
#pragma comment ( lib, "dxguid.lib"	)
#pragma comment ( lib, "dxerr.lib"  )


/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �ÓI�����o�ϐ��̎���
LPDIRECT3DDEVICE9	Device::pD3dDevice	= 0;
HRESULT				Device::deviceState	= 0;

//	�R���X�g���N�^
Device::Device()
	: pD3d( 0 )
{
	// Direct3D�̏�����
	memset( &d3dpp, 0, sizeof( D3DPRESENT_PARAMETERS ) );
	pD3d		= Direct3DCreate9( D3D_SDK_VERSION );
	return;
}

//	�f�X�g���N�^
Device::~Device()
{
	SafeRelease( pD3dDevice );
	SafeRelease( pD3d		);

	return;
}

// �����ݒ肷��
void Device::InitSetting()
{
	pD3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	//�e�N�X�`�������̐ݒ�
	pD3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,	D3DTOP_MODULATE );
	pD3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE );
	pD3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE );

	//�A���t�@�����̐ݒ�
	pD3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	D3DTOP_MODULATE );
	pD3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );
	pD3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE );

	//�e�N�X�`�������̐ݒ�
	pD3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,	D3DTOP_MODULATE );
	pD3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG1,	D3DTA_TEXTURE );
	pD3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG2,	D3DTA_DIFFUSE );

	//�A���t�@�����̐ݒ�
	pD3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,	D3DTOP_MODULATE );
	pD3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );
	pD3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE );

	// �W���I�ȐF�̐ݒ�
	pD3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	pD3dDevice->SetRenderState( D3DRS_BLENDOP,			D3DBLENDOP_ADD );
	pD3dDevice->SetRenderState( D3DRS_SRCBLEND,			D3DBLEND_SRCALPHA );
	pD3dDevice->SetRenderState( D3DRS_DESTBLEND,		D3DBLEND_INVSRCALPHA );

	//z�o�b�t�@���g��
	pD3dDevice->SetRenderState( D3DRS_ZENABLE, true );
	pD3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, true );

	pD3dDevice->SetRenderState(	D3DRS_LIGHTING,	false );

	return;
}

// �v���[���g�p�����[�^��ݒ肷��
bool Device::SetPresentParameters( U_LONG width, U_LONG height, bool mode )
{
	
	if( !pD3d )
	{
		//	Direct3D���������s���Ă���
		return false;
	}

	D3DDISPLAYMODE	DisplayMode;
	pD3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &DisplayMode );

	d3dpp.BackBufferWidth			= width;	//	�ٽ�ذݎ��͉𑜓x���w�肵�Ȃ���΂Ȃ�Ȃ�
	d3dpp.BackBufferHeight			= height;	//	�V
	d3dpp.BackBufferFormat			= DisplayMode.Format;
	d3dpp.BackBufferCount			= 1;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed					= mode;
	d3dpp.EnableAutoDepthStencil	= true;	
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	return true;
}

// �f�o�C�X���쐬����
bool Device::Create( HWND hWindow )
{
	//	�n�[�h���\�t�g�E�F�A�𒲂ׂ邽�߂̃e�[�u��
	const DWORD		 VERTEX_SHADER_TYPE[] = {
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING
	};
	//	HAL��REF�𒲂ׂ邽�߂̃e�[�u��
	const D3DDEVTYPE PIXEL_SHADER_TYPE[] = {
		D3DDEVTYPE_HAL,
		D3DDEVTYPE_REF
	};

	if( !pD3d )
	{
		//	Direct3D���쐬����Ă��܂���
		return false;
	}

	// �ȉ��̏��ɍ쐬�����݂�A���������炻���ŏI��
	//	�@ VertexShader�FHARDWARE	PixelShader�FHARDWARE
	//	�A VertexShader�FSOFTWARE	PixelShader�FHARDWARE
	//	�B VertexShader�FHARDWARE	PixelShader�FSOFTWARE
	//	�C VertexShader�FSOFTWARE	PixelShader�FSOFTWARE
	for( int i = 0; i < 2; i++ )
		for( int k = 0; k < 2; k++ )
			if( SUCCEEDED( pD3d->CreateDevice( 
						D3DADAPTER_DEFAULT,
						PIXEL_SHADER_TYPE[ i ],
						hWindow,
						VERTEX_SHADER_TYPE[ k ] | D3DCREATE_MULTITHREADED,
						&d3dpp,
						&pD3dDevice	) ) )
			{
				InitSetting();

				return true;
			}

	return false;
}

// �w�肵������ʂ��N���A����(�ÓI�����o�֐�)
bool Device::ClearBackBuffer( DWORD flag )
{
	return SUCCEEDED( pD3dDevice->Clear(
				0,
				0,
				flag,
				0xFF000000,	// A R G B
				1.0f,
				0 ) );
}

// ����ʂ��N���A���A�`����J�n����(�ÓI�����o�֐�)
bool Device::ClearScreen()
{
	bool	clear = SUCCEEDED( pD3dDevice->Clear(
				0,
				0,
				D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				0xFF000000,	// A R G B
				1.0f,
				0 ) );

	bool	begin = SUCCEEDED( pD3dDevice->BeginScene() );

	return ( clear && begin );
}

// �`����I�����A����ʂɕ`�������̂�\��ʂ֓]��(�ÓI�����o�֐�)
bool Device::SwapScreen()
{
	bool	end = SUCCEEDED( pD3dDevice->EndScene() );

	deviceState = pD3dDevice->Present( 0, 0, 0, 0 );

	return ( end && SUCCEEDED( deviceState ) );
}

// �f�o�C�X���擾����(�ÓI�����o�֐�)
LPDIRECT3DDEVICE9& Device::GetDevice()
{
	return pD3dDevice;
}

// �f�o�C�X���擾����(�ÓI�����o�֐�)
HRESULT Device::GetDeviceState()
{
	return deviceState;
}

}//	graphics	end
}//	iruna		end
