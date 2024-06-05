#include "Quad.h"
#include "Camera.h"
using namespace Direct3D;

HRESULT hr;
Quad::Quad()
{
}

Quad::~Quad()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

HRESULT Quad::Initialize()
{
	// ���_��� 
	XMVECTOR vertices[] =
	{

		//�l�p��
		XMVectorSet(-2.0f,  0.0f, 1.0f, 0.0f),	//����
		XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f),    //�V��
		XMVectorSet(2.0f,  0.0f, 1.0f, 0.0f),	//�E��
		XMVectorSet(1.0f, 0.0f, -2.0f, 0.0f),	//�E��
		XMVectorSet(-1.0f, 0.0f, -2.0f, 0.0f),	//����

		////�܊p�`(�z�[���x�[�X�^)
		//XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),//����
		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	//��
		//XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	//�E��
		//XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),	//�E��
		//XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f),	//����
	
		//�l�p�`
		//XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),//����
		//XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	//�E��
		//XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	//�E��
		//XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),//����	
	};

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"���_�o�b�t�@�̍쐬�Ɏ��s",L"Error", MB_OK);
		return hr;
	}

	////�C���f�b�N�X��� �l�p�`
	//int index[] = { 0,2,3, 0,1,2 };
	////�C���f�b�N�X���@�܊p�`
	//int index[] = { 0,1,2, 0,2,3, 0,3,4 };
	//�C���f�b�N�X���@�Z�p�`
	/*int index[] = { 0,1,2, 0,2,3, 0,3,4, 0,4,5 };*/

	//�C���f�b�N�X���@�l�p��
	//int index[] = { 0,1,2, 0,2,3, 1,2,4, 2,3,4, 0,1,4};
	int index[] = {4,1,3, 4,0,3, 0,1,4, 0,1,2, 0,2,3, 2,1,3};
	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s", L"Error", MB_OK);
		return hr;
	}

	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s", L"Error", MB_OK);
		return hr;
	}
}

void Quad::Draw(XMMATRIX& worldMatrix)
{
	////�R���X�^���g�o�b�t�@�ɓn�����
	//XMVECTOR position = { 0, 3, -10, 0 };	//�J�����̈ʒu
	//XMVECTOR target = { 0, 0, 0, 0 };	//�J�����̏œ_
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//�r���[�s��
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4/*4���̃΁@45�x*/, 800.0f / 600.0f, 0.1f, 100.0f);//�ˉe�s��@05 22   2 14 55�J�N�j��

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix* Camera::GetViewMatrix() * Camera::GetProjectionMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃��\�[�X�A�N�Z�X���ꎞ�~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);

	//���_�o�b�t�@
	UINT stride = sizeof(XMVECTOR);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	Direct3D::pContext->DrawIndexed(18, 0, 0);//�O�p���������̒��_�̐�
}

void Quad::Release()
{
}