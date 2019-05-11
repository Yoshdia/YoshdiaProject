#pragma once

class CManager;
class CSound;
class BitmapText;

class COver :public CScene
{
	CManager *manager;
public:
	COver(CManager *pManager);
	~COver();

	void Update(CSound *sound);
	void Render(BitmapText *text);
private:
	int *graphic;
};