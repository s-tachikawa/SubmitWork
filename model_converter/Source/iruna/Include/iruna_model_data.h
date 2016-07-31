//---------------------------------------------------------
// 
//	iruna_model_common.h
//	独自モデルデータ定義
//	作成日 10月21日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_MODEL_DATA_H
#define IRUNA_MODEL_DATA_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_bone.h"
#include "../Include/iruna_math.h"
#include "../Include/iruna_material.h"
#include "../Include/iruna_vertex_buffer.h"
#include "../Include/iruna_index_buffer.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
//	ジオメトリーカウント
struct GeometryData
{

	int				vertexCount;	//	頂点数
	int				porygonCount;	//	ポリゴン数
	int				indexCount;		//	インデックス数
	int				materialCount;	//	マテリアル数
};
struct BoneIndex
{
	unsigned char indexOne;
	unsigned char indexTwo;
	unsigned char indexThree;
	unsigned char indexFour;
};

//	頂点データ
struct VertexData
{
	math::Vector3 pos;				//	頂点座標
	math::Vector3 normal;			//	法線
	math::Vector2 uv;				//	UV座標

};

// 頂点ブレンディング
struct VertexBlending
{
	float		weight[ 4 ];		//	頂点ブレンディング
	int			boneIndex[ 4 ];		//	影響ボーンインデックス
};

//	マテリアルデータ
struct MaterialData
{
	Material					material;	//	マテリアル
	float						power;		//	透過度

};
//	バッファデータ
struct BufferData
{
	VertexBuffer*	vertexBuffer;
	IndexBuffer*	indexBuffer;
};

//	メッシュデータ
struct MeshData
{
	int								meshId;			//	メッシュID
	int								parentId;		//	親メッシュのID
	GeometryData					countData;		//	ジオメトリーのカウントデータ
	std::vector< int >				childId;		//	子メッシュID
	VertexData*						vertex;			//	頂点データ
	VertexBlending*					blending;		//	頂点ブレンディング
	int*							index;			//	頂点インデックス
	MaterialData*					material;		//	マテリアル
	std::vector< math::Matrix >		tran;			//	アニメーション平行移動行列(階層アニメーション)
	VertexBuffer*					vertexBuffer;	//	頂点バッファ
	IndexBuffer*					indexBuffer;	//	インデックスバッファ
	Bone*							bone;			//	ボーン構造体
	int								boneCount;		//	ボーン数
	
};

struct ModelData
{
	int								meshCount;		//	メッシュ数
	std::vector< MeshData* >		mesh;			//	メッシュデータ
	int								animeCount;		//	アニメーション数
};


}	//	graphics	end
}	//	iruna		end

/*
メモ
モデルデータのスマートポインタに使用か検討中
期限が短いので、今はModelLoader側がモデルデータの削除をしている。
コンバーター自体はそこまでポインタコピーが起きないので。
*/



#endif	//	IRUNA_MODEL_DATA_H	end