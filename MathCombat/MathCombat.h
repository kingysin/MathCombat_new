#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MathCombat.h"
#include "Utils.h"
#include "GameScene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MathCombatClass; };
QT_END_NAMESPACE

// Основное окно игры, на котором находятся все виджеты 
class MathCombat : public QMainWindow
{
	Q_OBJECT

public:
	MathCombat(QWidget* parent = nullptr);
	~MathCombat();

	bool IsLevelPassed(); 

	// Сцена на уровнях
	void ShowFirstLevel();
	void ShowSecondLevel();
	void ShowThirdLevel();

	void ShowCongratulation();

public slots:
	void StartNewGame(); 
	void StartCombat(Difficulty diff); // Начинает математический бой с заданным уровнем сложности
	void EndCombat(bool result);  // Обрабатывает результат боя

private:
	void ContinueGame(); 
	void ShowErrorDialog(); // Показывает диалог об ошибке, если пользователь ввел неправильный ответ

	int currentLevel = 1; // текущий уровень игры

	GameScene* m_scene; 

	Ui::MathCombatClass* ui;
};
