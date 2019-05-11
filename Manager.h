#pragma once
#pragma once

class CManager;
class CSound;
class BitmapText;

//�V�[���̊��N���X
class CScene
{
protected:
	CManager * manager;
public:
	CScene(CManager *pManager) { manager = pManager; };
	virtual ~CScene() {};
	//�`��
	virtual void Update(CSound *sound) {};
	//�X�V
	virtual void Render(BitmapText *text) {};
};

//�V�[���Ǘ��N���X
class CManager
{
	//�L�[
	char *key;
	char *control;
public:
	//���̃V�[���̃|�C���^
	CScene * scene;
	CManager(char *pKey, char *pControl) { key = pKey; control = pControl; };
	~CManager() { delete scene; };
	char *GetKey() { return key; }
	char *GetControl() { return control; }
	//�`��
	void Update(CSound *sound) { scene->Update(sound); };
	//�X�V
	void Render(BitmapText *text) { scene->Render(text); };

};