#pragma once
#pragma once

class CManager;
class CSound;
class BitmapText;

//シーンの基底クラス
class CScene
{
protected:
	CManager * manager;
public:
	CScene(CManager *pManager) { manager = pManager; };
	virtual ~CScene() {};
	//描画
	virtual void Update(CSound *sound) {};
	//更新
	virtual void Render(BitmapText *text) {};
};

//シーン管理クラス
class CManager
{
	//キー
	char *key;
	char *control;
public:
	//今のシーンのポインタ
	CScene * scene;
	CManager(char *pKey, char *pControl) { key = pKey; control = pControl; };
	~CManager() { delete scene; };
	char *GetKey() { return key; }
	char *GetControl() { return control; }
	//描画
	void Update(CSound *sound) { scene->Update(sound); };
	//更新
	void Render(BitmapText *text) { scene->Render(text); };

};