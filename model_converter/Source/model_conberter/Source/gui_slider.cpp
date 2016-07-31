//---------------------------------------------------------
// 
//	bar_icon.h
//	�w�肵�������Ńo�[�̃A�C�R�����쐬���A�Ǘ�����
//	�X�V�� 1��8��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h---------------------------------*/
#include "../Include/gui_slider.h"

//	�R���X�g���N�^
BarIcon::BarIcon()
{
	valueMax	= 0;
	barTex = new Texture;
	barSpr = new Sprite;
	barTex->Load( "../Resource/texture/bar.png" );
	barSpr->SetSize( math::Vector2( 128, 2 ) );
	cur = new Sprite;
	cur->SetSize( math::Vector2( 20, 40 ) );
	cur->SetColor( Color4( 255, 255, 255, 255 ) );

	pos = math::Vector2( 0, 0 );
	curPos = math::Vector2( 0, -20 );
	return;
}

//	�f�X�g���N�^
BarIcon::~BarIcon()
{
	SafeDelete( barTex );
	SafeDelete( barSpr );
	SafeDelete( cur );
	return;
}

//	�o�[�̏�����
void BarIcon::SetSliderMax( float max )
{

	valueMax	= max;
	curPos.x	= pos.x;
	return;
}

//	�`����W�̎w��
void BarIcon::SetPos( math::Vector2 setPos )
{
	pos = setPos;
	curPos = math::Vector2( setPos.x, setPos.y - 20 );
	//	�o�[���z���Ȃ��悤�ɂ���
	if( curPos.x > ( pos.x + 128 - 20.0f ) )
	{
		curPos.x = pos.x + 128.0f - 20.0f;
	}
	if( curPos.x < pos.x )
	{
		curPos.x = pos.x;
	}
	return;
}

//	�o�[�̍X�V
void BarIcon::UpDate()
{
	//	�}�E�X�̍��W���擾
	POINT temp = io::GetMousePosition();
	if( HitCursor() )
	{
		if( io::CheckMouseState( io::MouseButton::LEFT ) == io::INPUT_PUSH )
		{
			flag = true;
		}
		//	�}�E�X���J�[�\���ɂ������Ă���Ȃ�F��ς���
		cur->SetColor( Color4( 255, 0, 0, 255 ) );
	}
	else
	{
		cur->SetColor( Color4( 255, 255, 255, 255 ) );
	}

	if( io::CheckMouseState( io::MouseButton::LEFT ) == io::INPUT_PUSHED )
	{
		if( flag )
		{
			//	�}�E�X���J�[�\���ɂ������Ă���Ȃ�F��ς���
			cur->SetColor( Color4( 255, 0, 255, 255 ) );

			curPos = math::Vector2( ( float )temp.x - 8, curPos.y );
			//	�o�[���z���Ȃ��悤�ɂ���
			if( curPos.x > ( pos.x + 128 - 20.0f ) )
			{
				curPos.x = pos.x + 128.0f - 20.0f;
			}
			if( curPos.x < pos.x )
			{
				curPos.x = pos.x;
			}
		}
	}

	//	�}�E�X�������ꂽ��
	if( io::CheckMouseState( io::MouseButton::LEFT ) == io::INPUT_RELEASED )
	{
		flag = false;
		cur->SetColor( Color4( 255, 255, 255, 255 ) );
	}
	return;
}

//	�J�[�\���ƃ}�E�X�|�C���^�̓����蔻��
bool BarIcon::HitCursor()
{
	POINT temp = io::GetMousePosition();
	if( temp.x > curPos.x && temp.y > curPos.y && 
		temp.x < ( curPos.x + 20) && temp.y < ( curPos.y + 40 ) )
	{
		return true;
	}

	return false;
}

//	�o�[�̕`��
void BarIcon::Draw()
{
	render.SetTexture( 0, barTex->GetTexture() );
	barSpr->Draw( pos );

	render.SetTexture( 0, NULL );
	cur->Draw( curPos );

	return;
}

//	�o�[�̌��݂̗ʂ��擾
int BarIcon::GetValue()
{
	//�o�[�ƃJ�[�\���̈ʒu��
	float tempPos = curPos.x - pos.x;

	float tempValue = ( float )( valueMax / ( 128.0f - 20.0f ) );

	tempValue = tempPos * tempValue;
	
	return ( int )tempValue;
}
void BarIcon::SetValue( float setValue )
{

	float tempValue = ( float )( ( 128.0f - 20.0f ) / valueMax);

	curPos.x = pos.x + ( tempValue *  setValue );

	return;
}