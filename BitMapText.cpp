#include "BitmapText.h"

const int maxImageNum = 256;

CBitmapText::CBitmapText()
{
	m_useflag = false;
	m_bgalpha = true;

	for (int i = 0; i < maxImageNum; i++)
	{
		m_fontMap[i] = -1;
	}
	R = G = B = 255;
	m_shadow_R = 64;
	m_shadow_G = 64;
	m_shadow_B = 64;

	m_shadowOffsetX = 1;
	m_shadowOffsetY = 1;

}

CBitmapText::~CBitmapText()
{
	// フォントイメージの解放
	if (m_useflag)
	{
		for (int i = 0; i < maxImageNum; i++)
		{
			DeleteGraph(m_fontImg[i]);
		}
	}
	m_useflag = false;
}

void CBitmapText::setFontImage(int Xnum, int Ynum)
{
	int tmpImg, imgX, imgY;

	// ファイル仮読み込み
	tmpImg = LoadGraph("img/Space Shooter - 1/Font20x20.png");
	//if (tmpImg == -1)
	//{
	//	printf("fontfile load failed:[%s]", fontImgfilename);
	//	return;
	//}
	//　画像サイズ縦横取得
	GetGraphSize(tmpImg, &imgX, &imgY);
	DeleteGraph(tmpImg);

	// フォント1個分の縦横サイズ取得
	m_sizeX = imgX / Xnum;
	m_sizeY = imgY / Ynum;

	// 画像読み込み
	LoadDivGraph("img/Space Shooter - 1/Font20x20.png", Xnum*Ynum, Xnum, Ynum, m_sizeX, m_sizeY, m_fontImg);
	m_useflag = true;
}

void CBitmapText::textDraw(int x, int y, char * string)
{
	//フォント使用可能か
	if (!m_useflag)
		return;

	//テキスト描画開始
	int text_x, text_y, img;
	text_x = x;
	text_y = y;

	while (*string)
	{

		// 文字が改行の場合は改行＋戻す
		if (*string == '\n')
		{
			text_x = x;
			text_y += m_sizeY;
			string++;
			continue;
		}

		//文字描画
		img = isString(*string);
		if (img >= 0)
		{
			DrawGraph(text_x, text_y, m_fontImg[img], m_bgalpha);
		}

		// 文字描画位置進める
		text_x += m_sizeX;
		string++;
	}

	SetDrawBright(255, 255, 255);
}

void CBitmapText::textDrawWithShadow(int x, int y, char * string)
{
	//影文字描画
	SetDrawBright(m_shadow_R, m_shadow_G, m_shadow_B);
	textDraw(x + m_shadowOffsetX, y + m_shadowOffsetY, string);

	//文字描画
	SetDrawBright(R, G, B);
	textDraw(x, y, string);

}

void CBitmapText::textDrawRandom(int x, int y, char* string, int maxRand, int countDown)
{
	char randloopWidth = 'z' - '!';
	char *randString;

	int cnt = 0;
	while (string[cnt])
		cnt++;

	randString = new char[cnt + 1];

	//現在の文字からランダム文字列作成
	cnt = 0;
	char randCount;
	while (*string)
	{
		randCount = (maxRand % randloopWidth - countDown) < 0 ? 0 : (maxRand % randloopWidth - countDown);
		randString[cnt] = *string + randCount;
		cnt++;
		string++;
	}
	randString[cnt] = '\0';

	textDraw(x, y, randString);

	delete[] randString;
}

void CBitmapText::textDrawMessage(int x, int y, char * string, unsigned int display_lengh)
{
	// 文字数をカウントし、表示文字数が本来の文字数より多ければそのまま表示
	size_t len = strlen(string);
	if (len < display_lengh)
	{
		textDraw(x, y, string);
		return;
	}

	// 文字数をdisplay_length内で表示
	char* tmpStr = new char[display_lengh + 1];
	for (unsigned int i = 0; i < display_lengh; i++)
	{
		tmpStr[i] = string[i];
	}
	tmpStr[display_lengh] = '\0';

	textDraw(x, y, tmpStr);

	delete[] tmpStr;
}

void CBitmapText::textDrawMessageWithShadow(int x, int y, char * string, unsigned int display_lengh)
{
	// 文字数をカウントし、表示文字数が本来の文字数より多ければそのまま表示
	size_t len = strlen(string);
	if (len < display_lengh)
	{
		textDrawWithShadow(x, y, string);
		return;
	}

	// 文字数をdisplay_length内で表示
	char* tmpStr = new char[display_lengh + 1];
	for (unsigned int i = 0; i < display_lengh; i++)
	{
		tmpStr[i] = string[i];
	}
	tmpStr[display_lengh] = '\0';

	textDrawWithShadow(x, y, tmpStr);

	delete[] tmpStr;
}


void CBitmapText::setFontColor(int r, int g, int b)
{
	R = r; G = g; B = b;
	SetDrawBright(R, G, B);
}

void CBitmapText::setFontColorShadow(int r, int g, int b)
{
	m_shadow_R = r;
	m_shadow_G = g;
	m_shadow_B = b;
}

void CBitmapText::setFontShadowOffset(int ofsX, int ofsY)
{
	m_shadowOffsetX = ofsX;
	m_shadowOffsetY = ofsY;
}

void CBitmapText::reMapText()
{
	int num = 0;
	const char *p;

	p = " ! #$%&'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\]^_ ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~";
	char n = 0;
	while (*p && n < 255)
	{
		m_fontMap[*p++] = n++;
	}

}

int CBitmapText::isString(char c)
{
	return m_fontMap[c];
}
