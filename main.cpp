#include "DxLib.h"

#include "game.h"

#include "SceneTitle.h"
#include "SceneMain.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	SceneTitle title;
	SceneMain main;

	int sceneNo = 0;
	switch (sceneNo)
	{
	case 0:
		title.init();
		break;
	case 1:
		main.init();
		break;
	}
	

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		switch (sceneNo)
		{
		case 0:
			title.update();
			title.draw();

			if (title.isEnd())
			{
				title.end();
				main.init();
				sceneNo = 1;
			}
			break;
		case 1:
			main.update();
			main.draw();

			if (main.isEnd())
			{
				main.end();
				title.init();
				sceneNo = 0;
			}
			break;
		}

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	switch (sceneNo)
	{
	case 0:
		title.end();
		break;
	case 1:
		main.end();
		break;
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}