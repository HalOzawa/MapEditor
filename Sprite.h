#pragma once
#include <vector>
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;
using std::vector;

struct CONSTANT_BUFFER2D
{
	XMMATRIX	matW;
};

struct VERTEX2D
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Sprite
{
	uint64_t vertexNum_;//���_��
	vector<VERTEX2D> vertices_;
	uint64_t indexNum_;//���_��
	vector<int> indices_;
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;//�e�N�X�`���ւ̃|�C���^

public:
	Sprite();//�R���X�g���N�^
	~Sprite();//�f�X�g���N�^
    HRESULT Load(std::string fileName);

	void Draw(Transform & transform);//�`��֐�
	void Release();//�������
private:
	void InitVertexDate();
	HRESULT CreateVertexDate();

	void InitIndexDate();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture(std::string fileName);

	void PassDateToCB(DirectX::XMMATRIX worldMatrix);
	void SetBufferToPipeline();

};



