//---------------------------------------------------------
// 
//	iruna_dialog.h
//	windowsダイアログを出す
//	作成日 10月21日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
#ifndef IRUNA_DIALOG_H
#define IRUNA_DIALOG_H

#include "../Include/iruna_utility.h"

namespace iruna
{
namespace core
{

/*----グローバル変数定義---------------------------------*/
extern LPCTSTR			CD_FILTER_LOAD_MODEL;	//	読み込むファイル(モデル)
extern LPCTSTR			CD_FILTER_SAVE_MODEL;	//	書き込むファイル(モデル)
extern LPCTSTR			CD_FILTER_TEXTURE;		//	読み込むファイル(テクスチャ)
extern LPCTSTR			CD_FILTER_SHEDER;		//	読み込むファイル(シェーダー)

extern const DWORD		CD_FLAGS_SAVE;		//	ダイアログフラグ(SAVE)
extern const DWORD		CD_FLAGS_LOAD;		//	ダイアログフラグ(LOAD)

/*----グローバル関数定義---------------------------------*/
//--------------------------------------------------------------------
// 
//	処理	:	名前をつけて保存ダイアログの作成
//	製作者	:	立川 翔野
//	作成日	:	2011/10/21	- 作成
// 
//--------------------------------------------------------------------
extern int				SaveDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath );

//--------------------------------------------------------------------
// 
//	処理	:	開くダイアログの作成
//	製作者	:	立川 翔野
//	作成日	:	2011/10/21	- 作成
// 
//--------------------------------------------------------------------
extern int				LoadDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath );

}	//	core
}	//	iruna


#endif	//	IRUNA_DIALOG_H	end