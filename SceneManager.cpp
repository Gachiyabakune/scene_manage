#include "SceneManager.h"
#include <cassert>

#include "SceneTitle.h"
#include "SceneMain.h"

SceneManager::SceneManager()
{
	m_kind = kSceneKindTitle;
	m_pScene = nullptr;
}
SceneManager::~SceneManager()
{

}

void SceneManager::init(SceneKind kind)
{
	m_kind = kind;
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_pScene = new SceneTitle;
		break;
	case SceneManager::kSceneKindMain:
		m_pScene = new SceneMain;
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
	m_pScene->init();
}

void SceneManager::end()
{
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->end();
	delete m_pScene;
}

void SceneManager::update()
{
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->update();

	bool isEnd = false;

	if (m_pScene->isEnd())
	{
		//ƒV[ƒ“‚ÌI—¹ˆ—
		m_pScene->end();
		delete m_pScene;

		switch (m_kind)
		{
		case SceneManager::kSceneKindTitle:
			init(kSceneKindMain);
			break;
		case SceneManager::kSceneKindMain:
			init(kSceneKindTitle);
			break;
		case SceneManager::kSceneKindNum:
		default:
			assert(false);
			break;
		}
	}
}

void SceneManager::draw()
{
	assert(m_pScene);
	if(!m_pScene) return;

	m_pScene->end();
	m_pScene->draw();
}