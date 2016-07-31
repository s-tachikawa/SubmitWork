//---------------------------------------------------------
// 
//	model_converter.h
//	アプリケーションのメイン
//	作成日 10月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----多重インクルード防止-------------------------------------------------*/
#ifndef MODEL_CONVERTER_H
#define MODEL_CONVERTER_H

/*----インクルード-------------------------------------------------*/
#include "../../iruna/Include/iruna.h"
#include "../Include/gui_frame.h"
#include "../Include/model_render.h"
#include "../Include/sgd_encoder.h"
#include "../Include/dialog_animetion_input.h"
#include "../Include/gui_slider.h"
#include "../Include/gui_twice_button.h"

/*----ネームスペース-------------------------------------------------*/
using namespace iruna;
using namespace core;
using namespace	graphics;
using namespace io;

//=====================================================================
//
//	クラス名	:	ModelConverter
//	処理		:	コンバーター全体の管理
//
//=====================================================================
class ModelConverter
{
private:

	GuiFrame*			guiFrame;		//	右のGUI系管理クラス
	TwiceButton*		guiTwiceBut;	//	再生停止ボタン

	ModelLoader*		loader;			//	モデルのデコーダークラス
	ModelRender*		render;			//	モデルレンダリングクラス
	SgdEncoder*			encoder;		//	SGDエンコーダー
	bool				renderFlag;		//	レンダリングフラグ
	Camera				camera;			//	カメラ
	DeviceController	device_render;	//	レンダリングデバイス

	AnimetionInput*		animeInput;		//	アニメーションフレーム設定クラス
	float				animeFlame;		//	アニメーションフレーム

	BarIcon*			bar;			//	バーアイコン

public:
	//--------------------------------------------------------------------
	// 
	//	処理	:	コンストラクタ
	// 
	//--------------------------------------------------------------------
	ModelConverter();

	//--------------------------------------------------------------------
	// 
	//	処理	:	デストラクタ
	// 
	//--------------------------------------------------------------------
	~ModelConverter();

	//--------------------------------------------------------------------
	// 
	//	処理	:	更新
	// 
	//--------------------------------------------------------------------
	void UpDate();

	//--------------------------------------------------------------------
	// 
	//	処理	:	描画
	// 
	//--------------------------------------------------------------------
	void Draw();

};

#endif	//	MODEL_CONVERTER_H	end