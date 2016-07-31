//---------------------------------------------------------
// 
//	iruna_bone.h
//	モデルボーン管理クラス
//	作成日 11月01日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----多重インクルード---------------------------------*/
#ifndef IRUNA_BONE_H
#define IRUNA_BONE_H

/*----インクルード---------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

struct Bone
{
public:

	
	int id;									//	ボーンID
	int	parentId;							//	親のID

	std::vector< math::Matrix >		boneMat;//	アニメーション用平行移動行列
	math::Matrix init;						//	初期姿勢
	math::Matrix offset;					//	オフセット行列
	math::Matrix tran;						//	平行移動行列
	math::Matrix comb;						//	合成行列
	math::Matrix skin;						//	スキニング行列

	std::vector< Bone* > child;

public:
	Bone();
	void BoneRun( math::Matrix* parentOffset );
	void BoneUpDate( math::Matrix parent );
	void SetInitMatrix( math::Matrix initMat );
	void SetInitMatrix( math::Vector3 bonePos );

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_BONE_H	end