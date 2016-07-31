//---------------------------------------------------------
// 
//	iruna_bone.h
//	���f���{�[���Ǘ��N���X
//	�쐬�� 11��01��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----���d�C���N���[�h---------------------------------*/
#ifndef IRUNA_BONE_H
#define IRUNA_BONE_H

/*----�C���N���[�h---------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

struct Bone
{
public:

	
	int id;									//	�{�[��ID
	int	parentId;							//	�e��ID

	std::vector< math::Matrix >		boneMat;//	�A�j���[�V�����p���s�ړ��s��
	math::Matrix init;						//	�����p��
	math::Matrix offset;					//	�I�t�Z�b�g�s��
	math::Matrix tran;						//	���s�ړ��s��
	math::Matrix comb;						//	�����s��
	math::Matrix skin;						//	�X�L�j���O�s��

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