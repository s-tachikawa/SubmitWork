//---------------------------------------------------------
// 
//	iruna_model_common.h
//	�Ǝ����f���f�[�^��`
//	�쐬�� 10��21��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_MODEL_DATA_H
#define IRUNA_MODEL_DATA_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_bone.h"
#include "../Include/iruna_math.h"
#include "../Include/iruna_material.h"
#include "../Include/iruna_vertex_buffer.h"
#include "../Include/iruna_index_buffer.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
//	�W�I���g���[�J�E���g
struct GeometryData
{

	int				vertexCount;	//	���_��
	int				porygonCount;	//	�|���S����
	int				indexCount;		//	�C���f�b�N�X��
	int				materialCount;	//	�}�e���A����
};
struct BoneIndex
{
	unsigned char indexOne;
	unsigned char indexTwo;
	unsigned char indexThree;
	unsigned char indexFour;
};

//	���_�f�[�^
struct VertexData
{
	math::Vector3 pos;				//	���_���W
	math::Vector3 normal;			//	�@��
	math::Vector2 uv;				//	UV���W

};

// ���_�u�����f�B���O
struct VertexBlending
{
	float		weight[ 4 ];		//	���_�u�����f�B���O
	int			boneIndex[ 4 ];		//	�e���{�[���C���f�b�N�X
};

//	�}�e���A���f�[�^
struct MaterialData
{
	Material					material;	//	�}�e���A��
	float						power;		//	���ߓx

};
//	�o�b�t�@�f�[�^
struct BufferData
{
	VertexBuffer*	vertexBuffer;
	IndexBuffer*	indexBuffer;
};

//	���b�V���f�[�^
struct MeshData
{
	int								meshId;			//	���b�V��ID
	int								parentId;		//	�e���b�V����ID
	GeometryData					countData;		//	�W�I���g���[�̃J�E���g�f�[�^
	std::vector< int >				childId;		//	�q���b�V��ID
	VertexData*						vertex;			//	���_�f�[�^
	VertexBlending*					blending;		//	���_�u�����f�B���O
	int*							index;			//	���_�C���f�b�N�X
	MaterialData*					material;		//	�}�e���A��
	std::vector< math::Matrix >		tran;			//	�A�j���[�V�������s�ړ��s��(�K�w�A�j���[�V����)
	VertexBuffer*					vertexBuffer;	//	���_�o�b�t�@
	IndexBuffer*					indexBuffer;	//	�C���f�b�N�X�o�b�t�@
	Bone*							bone;			//	�{�[���\����
	int								boneCount;		//	�{�[����
	
};

struct ModelData
{
	int								meshCount;		//	���b�V����
	std::vector< MeshData* >		mesh;			//	���b�V���f�[�^
	int								animeCount;		//	�A�j���[�V������
};


}	//	graphics	end
}	//	iruna		end

/*
����
���f���f�[�^�̃X�}�[�g�|�C���^�Ɏg�p��������
�������Z���̂ŁA����ModelLoader�������f���f�[�^�̍폜�����Ă���B
�R���o�[�^�[���̂͂����܂Ń|�C���^�R�s�[���N���Ȃ��̂ŁB
*/



#endif	//	IRUNA_MODEL_DATA_H	end