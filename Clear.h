#pragma once

class CManager;
class CSound;
class BitmapText;

class CClear :public CScene
{
	CManager *manager;
public:
	CClear(CManager *pManager);
	~CClear();

	void Update(CSound *sound);
	void Render(BitmapText *text);
private:
	int *graphic;
};