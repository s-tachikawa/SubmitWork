//---------------------------------------------------------
// 
//	iruna_text.h
//	文字列描画
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_TEXT_H
#define IRUNA_TEXT_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"
#include "../Include/iruna_sprite.h"
#include "../Include/iruna_color4.h"
#include "../Include/iruna_font.h"
#include "../Include/iruna_device_controller.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//=====================================================================
//
//	クラス名	:	Text
//	処理		:	文字列表示クラス(シングルトン)
//	製作者		:	立川 翔野
//	作成日		:	2011/05/28	- 作成
//
//=====================================================================
class Text
{
// プライベート	型定義
private:
	// 文字テクスチャ動的配列
	typedef std::vector < Font* > 	FontArray;

// プライベート	メンバ変数
private:
	FontArray			fontArray;	// 文字テクスチャの動的配列
	DeviceController*	render;		// デバイスを間接的に操作する
	Sprite*				sprite;		// 2Dビルボード
	U_INT				nowFont;	// 使う文字テクスチャクラスの番号
	static Text*		instance;	// インスタンス(静的メンバ関数)

// プライベート	メンバ関数
private:
	//--------------------------------------------------------------------
	// 
	//	処理	:	コンストラクタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	Text();

// パブリック	メンバ関数
public:
	//--------------------------------------------------------------------
	// 
	//	処理	:	デストラクタ
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	~Text();

	//--------------------------------------------------------------------
	// 
	//	処理	:	テキストクラスの唯一のインスタンス生成する関数(静的メンバ関数)
	//	戻り値	:	インスタンス
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	static Text*&	GetInstance();

	//--------------------------------------------------------------------
	// 
	//	処理	:	使いたい文字の書式を設定する
	//	第1引数	:	[in] size	- 文字のサイズ
	//	第2引数	:	[in] type	- 文字の書体
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	void	SetStyle( int size, std::string type );

	//--------------------------------------------------------------------
	// 
	//	処理	:	指定した位置に文字を表示する
	//	第1引数	:	[in] x		- x座標（原点は左上）
	//	第2引数	:	[in] y		- y座標（原点は左上）
	//	第3引数	:	[in] str	- 表示したい文字列
	//	第4引数	:	[in] color	- 表示する文字の色
	//	戻り値	:	結果フラグ	ture：成功　false：失敗
	//	製作者	:	立川 翔野
	//	作成日	:	2011/06/24	- 作成
	// 
	//--------------------------------------------------------------------
	bool	Draw( float x, float y, LPCSTR str, Color4 color );
};

}	//	graphics	end
}	//	iruna		end

/*----グローバル関数 宣言----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//--------------------------------------------------------------------
// 
//	処理	:	表示する文字の書式の設定をする
//	第1引数	:	[in] size	- 文字の大きさ
//	第2引数	:	[in] type	- 文字の書体
//	製作者	:	立川 翔野
//	作成日	:	2011/06/24	- 作成
// 
//--------------------------------------------------------------------
void	SetFontStyle( U_INT size, std::string type );

//--------------------------------------------------------------------
// 
//	処理	:	指定した位置に文字を表示する
//	第1引数	:	[in] x		- x座標（原点は左上）
//	第2引数	:	[in] y		- y座標（原点は左上）
//	第3引数	:	[in] str	- 表示したい文字列
//	第4引数	:	[in] color	- 表示する文字の色(デフォルトは白)
//	戻り値	:	結果フラグ	ture：成功　false：失敗
//	製作者	:	立川 翔野
//	作成日	:	2011/06/24	- 作成
// 
//--------------------------------------------------------------------
bool	DrawString( float x, float y, LPCSTR str, Color4 color = 0xFFFFFFFF );

//--------------------------------------------------------------------
// 
//	処理	:	指定した位置に文字＋数値を表示する
//	第1引数	:	[in] x		- x座標（原点は左上）
//	第2引数	:	[in] y		- y座標（原点は左上）
//	第3引数	:	[in] color	- 表示する文字の色
//	第4引数	:	[in] str	- 表示したい文字列
//	第5引数	:	[in] ...	- つっこみたい数値とか
//	戻り値	:	結果フラグ	ture：成功　false：失敗
//	製作者	:	立川 翔野
//	作成日	:	2011/06/24	- 作成
// 
//--------------------------------------------------------------------
bool	DrawFormatString( float x, float y, Color4 color, LPCSTR str, ... );

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_TEXT_H	end