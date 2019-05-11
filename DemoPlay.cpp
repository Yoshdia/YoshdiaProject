#include"Manager.h"
#include"DemoPlay.h"
#include"Sound.h"
#include"BitMapFont.h"
#include"Define.h"
#include"Title.h"

CDemoPlay::CDemoPlay(CManager * pManager) :CScene(pManager)
{
	manager = pManager;

	demoPlayMovie = -1;

	if (demoPlayMovie = -1)
	{
		demoPlayMovie = LoadGraph("img/Movie/DemoPlayMovie.mp4");
	}

	PlayMovieToGraph(demoPlayMovie);
}

CDemoPlay::~CDemoPlay()
{
	DeleteGraph(demoPlayMovie);
}

void CDemoPlay::Update(CSound * sound)
{
	//demoPlayMovie�̍Đ����I�����͍Đ�����Enter�AA,B�������ꂽ�Ƃ��Ƀt���O�����ă^�C�g���ɖ߂�
	bool backTitle = false;
	if (GetMovieStateToGraph(demoPlayMovie) == 0)
	{
		PauseMovieToGraph(demoPlayMovie);
		SeekMovieToGraph(demoPlayMovie, 0);
		backTitle = true;
	}

	if (manager->GetKey()[KEY_INPUT_RETURN] == 1 ||
		//B�{�^��
		(manager->GetControl()[CONTROL_B] == 1) ||
		//A�{�^��
		(manager->GetControl()[CONTROL_A] == 1))
	{
		backTitle = true;
	}

	if (backTitle == true)
	{
		manager->scene = new CTitle(manager);
		delete this;
	}

}

void CDemoPlay::Render(BitmapText * text)
{
	DrawGraph(0, 0, demoPlayMovie, TRUE);
}
