#include "GameScene.h"

GameScene::GameScene(std::vector<std::pair<Monster*, QPointF>> vectorMonsters, QString BackgroundTheme, QPointF playerPos, QObject* parent)
	: QGraphicsScene(parent), m_vectorMonsters(vectorMonsters)
{

	m_movingLeft = false;
	m_movingRight = false;

	QPixmap background(BackgroundTheme);
	addPixmap(background);
	setSceneRect(background.rect());

	m_player = new Player(this);
	addItem(m_player); // Добавляем на сцену
	m_player->setPos(playerPos); // Задаем положение

	for (auto monster : m_vectorMonsters)
	{
		addItem(monster.first); 
		monster.first->setPos(monster.second); 
		monster.first->startAnimation(); // Начинаем анимацию
	}

	m_gameTimer = new QTimer(this);
	connect(m_gameTimer, &QTimer::timeout, this, &GameScene::updateGame);

	m_gameTimer->start(15);
}

GameScene::~GameScene()
{
	// При удалении объекта сцены так же удаляются все ее монстры 
	for (auto monster : m_vectorMonsters)
	{
		if (monster.first) {
			monster.first->deleteLater();
		}
	}
}

void GameScene::updateGame()
{

	if (m_movingRight)
	{
		m_player->moveRight();
		m_player->startAnimation();
		//m_monster->moveLeft();
	}

	if (m_movingLeft)
	{
		m_player->moveLeft();
		m_player->startAnimation();
		//m_monster->moveRight();
	}

	if (!m_movingLeft && !m_movingRight)
	{
		m_player->stopAnimation();
	}

	QList<QGraphicsItem*> collisions =
		m_player->collidingItems();

	for (QGraphicsItem* item : collisions)
	{
		Monster* monster =
			dynamic_cast<Monster*>(item);

		if (monster)
		{
			// СТОЛКНОВЕНИЕ С МОНСТРОМ 
			qDebug() << "Столкновение!";

			emit CombatSignal(monster->getDifficulty()); // Отправляем сигнал о том что произошло столкновение 
			// с монстром сложности monster->getDifficulty() 


			monster->moveBy(-1000, -1000); // Визуально убираем монстра со сцены 

			m_gameTimer->stop(); // Останавливаем таймер для обновления игры
			numberDefeatedMonsters++; // Считаем монстра побежденным 
			m_combatBegin = true; // Флаг что бой начался
			m_movingLeft = false; 
			m_movingRight = false; 
			return;
		}
	}

}

// НАЖАТИЕ КЛАВИШ

void GameScene::keyPressEvent(QKeyEvent* event)
{
	if (m_combatBegin)
	{
		return;
	}
	// Чтобы событие не спамилось
	if (event->isAutoRepeat())
	{
		return;
	}

	if (event->key() == Qt::Key_D)
	{
		m_movingRight = true;
	}

	if (event->key() == Qt::Key_A)
	{
		m_movingLeft = true;
	}


	QGraphicsScene::keyPressEvent(event);
}

//ОТПУСКАНИЕ КЛАВИШ

void GameScene::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		return;
	}

	if (event->key() == Qt::Key_D)
	{
		m_movingRight = false;
	}

	if (event->key() == Qt::Key_A)
	{
		m_movingLeft = false;
	}

	QGraphicsScene::keyReleaseEvent(event);
}

// true - если на сцене все монстры побеждены
bool GameScene::AllMonstersDefeated()
{
	return numberDefeatedMonsters >= m_vectorMonsters.size();
}


void GameScene::ContinueGame()
{
	m_combatBegin = false; // Бой закончился

	m_gameTimer->start(); // Снова запускаем таймер
}
