#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete particleMan;
	/*delete particleMan1;*/
}

void GameScene::Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon)
{
	// �p�[�e�B�N������
	particleMan = ParticleManager::Create();
	particleMan->LoadTexture(L"Resources/particle2.png");
	particleMan->Update();

	/*particleMan1 = ParticleManager::Create();
	particleMan1->LoadTexture(L"Resources/effect1.png");
	particleMan1->Update();*/

	// ���͂̏�����
	input = new Input();
	input->Initialize(winApp);

	// ImGui�̏�����
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dXCommon, winApp);

	camera = new Camera();

	// gTs
	gTS = new GameTitleScene();
	gTS->Initialize();
	
	// �I�u�W�F�N�g�̏�����
	ObjectInitialize(dXCommon);
	// �X�v���C�g�̏�����
	SpriteInitialize(dXCommon, spriteCommon);
	// �p�[�e�B�N���̏�����
	ParticleInitialize();
}

void GameScene::Update()
{
	// ImGui��t�J�n
	imGuiManager->Begin();

	// ���͂̍X�V
	input->Update();

	// gTS�̍X�V
	gTS->Update();

	static char buf[256]{};
	static float f = 0.0f;

	/*ImGui::Text("Hello%d", 123);
	if (ImGui::Button("Save")) {
		imGuiManager->MySaveFunction();

		ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	}*/

	camera->SetEye(eye[0]);
	if (input->PushKey(DIK_RIGHT)) {
		eye[0].x += 0.5;
	}
	if (input->PushKey(DIK_LEFT)) {
		eye[0].x -= 0.5;
	}

	// �I�u�W�F�N�g�̍X�V
	ObjectUpdate();
	// �X�v���C�g�̍X�V
	SpriteUpdate();
	// �p�[�e�B�N���̍X�V
	ParticleUpdate();
			
	// ImGui��t�I��
	imGuiManager->End();
}

void GameScene::Draw(DirectXCommon* dXCommon)
{
	// �`��O����
	dXCommon->PreDraw();

	// 3D�I�u�W�F�N�g�̕`��
	ObjectDraw(dXCommon);
	// �p�[�e�B�N���̕`��
	ParticleDraw(dXCommon);
	// �摜�`��
	GameDraw(dXCommon);
	gTS->Draw(dXCommon);
			
	// ImGui�`��
	imGuiManager->Draw(dXCommon);
	
	// �`��㏈��
	dXCommon->PostDraw();
}

void GameScene::Finalize()
{
	// ���͊J��
	delete input;
	input = nullptr;

	// imgui�̏I������
	imGuiManager->Finalize();
	// imgui�̉��
	delete imGuiManager;
	imGuiManager = nullptr;

	// �I�u�W�F�N�g�̉��
	ObjectFinalize();

	// �X�v���C�g�̉��
	SpriteFinalize();
}

void GameScene::ObjectInitialize(DirectXCommon* dXCommon) 
{
	// OBJ���烂�f���f�[�^��ǂݍ���
	Model[0] = Model::LoadFromOBJ("Wolf", "Wolf.png");
	//Model[0]->LoadTexture("effect1.png");
	Model[1] = Model::LoadFromOBJ("Gorilla", "Gorilla/Gorilla.png");
	//Model[2] = Model::LoadFromOBJ("skydome", "skydome/skydome.jpg");
	// 3D�I�u�W�F�N�g����
	for (int i = 0; i < 5; i++) {
		object3d[i] = Object3d::Create();
	}
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	object3d[0]->SetModel(Model[0]);
	object3d[1]->SetModel(Model[1]);
	object3d[2]->SetModel(Model[2]);
	// 3D�I�u�W�F�N�g�̈ʒu���w��
	position[0] = { -20,-5,0 };
	rotation[0] = { 0,90,0 };
	eye[0] = { 0, 0, -50 };
	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetScale({ 5, 5, 5 });
	object3d[0]->SetRotation(rotation[0]);
	object3d[0]->SetEye(eye[0]);

	position[1] = { 0,0,50 };
	object3d[1]->SetPosition(position[1]);
	object3d[1]->SetScale({ 5,5,5 });
	object3d[1]->SetRotation({ 0, 90, 0 });

	object3d[2]->SetPosition({ 0,-40,0 });
	object3d[2]->SetScale({ 100, 100, 100 });
	object3d[2]->SetRotation({0,100,20});
}

void GameScene::ObjectUpdate()
{
	// 3D�I�u�W�F�N�g�X�V
	for (int i = 0; i < 5; i++) {
		object3d[i]->Update();
	}

	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetRotation(rotation[0]);
	object3d[0]->SetEye(eye[0]);
	object3d[1]->SetPosition(position[1]);

	/*if (input->PushKey(DIK_RIGHT)){
		eye[0].x += 0.5;
	}
	if (input->PushKey(DIK_LEFT)) {
		eye[0].x -= 0.5;
	}*/

	if (input->PushKey(DIK_W)) {
		position[0].y += 0.4;
	}

	/*if (input->PushKey(DIK_A)) {
		position[0].x -= 0.4;
		isPush_A = true;
	}*/
	else {
		isPush_A = false;
	}
	if (isPush_D == false) {
		if (isPush_A == true) {
			if (rotation[0].x >= -20) {
				rotation[0].x -= 1;
			}
			if (rotation[0].x <= -20) {
				rotation[0].x = -20;
			}
		}
		else {
			if (rotation[0].x >= -20) {
				rotation[0].x += 1;
			}
			if (rotation[0].x >= 0) {
				rotation[0].x = 0;
			}
		}
	}

	if (input->PushKey(DIK_S)) {
		position[0].y -= 0.4;
	}

	/*if (input->PushKey(DIK_D)) {
		position[0].x += 0.4;
		isPush_D = true;
	}*/
	else {
		isPush_D = false;
	}
	if (isPush_A == false) {
		if (isPush_D == true) {
			if (rotation[0].x <= 20) {
				rotation[0].x += 1;
			}
			if (rotation[0].x >= 20) {
				rotation[0].x = 20;
			}
		}
		else {
			if (rotation[0].x <= 20) {
				rotation[0].x -= 1;
			}
			if (rotation[0].x <= 0) {
				rotation[0].x = 0;
			}
		}
	}
	
}

void GameScene::ObjectDraw(DirectXCommon* dXCommon)
{
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dXCommon->GetCommandList());

	// 3D�I�u�W�F�N�g�̕`��
	for (int i = 0; i < 5; i++) {
		object3d[i]->Draw();
	}

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
}

void GameScene::ObjectFinalize()
{
	// 3D�I�u�W�F�N�g���
	for (int i = 0; i < 5; i++) {
		delete object3d[i];
	}
	// 3D���f�����
	for (int i = 0; i < 5; i++) {
		delete Model[i];
	}
}

void GameScene::SpriteInitialize(DirectXCommon* dXCommon, SpriteCommon& spriteCommon)
{
	// �X�v���C�g
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);

	// �摜�P
	hP.LoadTexture(spriteCommon_, 3, L"Resources/a.png", dXCommon->GetDevice());
	hP.SetColor(XMFLOAT4(1, 1, 1, 1));
	hP.SpriteCreate(dXCommon->GetDevice(), 50, 50, 3, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	hP.SetPosition(XMFLOAT3(0, 0, 0));
	hP.SetScale(XMFLOAT2(50 * 1, 50 * 1));
	hP.SetRotation(0.0f);
	hP.SpriteTransferVertexBuffer(hP, spriteCommon, 3);
	hP.SpriteUpdate(hP, spriteCommon_);
	// �摜�Q
	hP1.LoadTexture(spriteCommon_, 4, L"Resources/b.png", dXCommon->GetDevice());
	hP1.SetColor(XMFLOAT4(1, 1, 1, 1));
	hP1.SpriteCreate(dXCommon->GetDevice(), 50, 50, 4, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	hP1.SetPosition(XMFLOAT3(50, 0, 0));
	hP1.SetScale(XMFLOAT2(50 * 1, 50 * 1));
	hP1.SetRotation(0.0f);
	hP1.SpriteTransferVertexBuffer(hP1, spriteCommon, 4);
	hP1.SpriteUpdate(hP1, spriteCommon_);

	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());
}

void GameScene::SpriteUpdate()
{
}

void GameScene::GameDraw(DirectXCommon* dXCommon)
{
	sprite->PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	hP.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP.vbView);
	hP1.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP1.vbView);

	sprite->PostDraw();
}

void GameScene::SpriteFinalize()
{
	// �X�v���C�g���
	delete sprite;
	sprite = nullptr;
}

void GameScene::ParticleInitialize()
{
	for (int i = 0; i < 100; i++) {
		// X,Y,Z���ׂ�[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float md_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		// X,Y,Z�S��[-0.05f,+0.05f]�Ń����_�����z
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		// �d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_�����z
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		// �ǉ�
		particleMan->Add(100, pos, vel, acc, 1.0f, 0.0);
	}
}

void GameScene::ParticleUpdate()
{
	// �J�����ړ�
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}

	particleMan->Update();
}

void GameScene::ParticleDraw(DirectXCommon* dXCommon)
{
	// �R�}���h���X�g�̎擾
	//ID3D12GraphicsCommandList* cmdList = dXCommon->GetCommandList();

	// 3D�I�u�W�F�N�g�`��O����
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	// 3D�I�u�N�W�F�N�g�̕`��
	particleMan->Draw();

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	ParticleManager::PostDraw();
}

void GameScene::GameReset()
{
	// 3D�I�u�W�F�N�g�̈ʒu���w��
	position[0] = { -20,-5,0 };
	rotation[0] = { 0,90,0 };
	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetScale({ 5, 5, 5 });
	object3d[0]->SetRotation(rotation[0]);
	position[1] = { 0,5,50 };
	object3d[1]->SetPosition(position[1]);
	object3d[1]->SetRotation({ 0, 90, 0 });
	object3d[1]->SetScale({ 5,5,5 });

	playerHp = 3;
	time = 0;
}