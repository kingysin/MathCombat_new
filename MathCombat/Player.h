#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QTimer>

// Класс главного героя.
class Player : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:

	Player(QObject* parent);
	~Player();

	void moveLeft(); // Двигает героя влево с анимацией бега	
	void moveRight(); 

	void startAnimation(); 
	void stopAnimation();  
	 
	void nextFrame(); // Меняет спрайт

private:
	QVector<QPixmap> walkRightFrames;  
	QVector<QPixmap> walkLeftFrames;  

	QPixmap idleRight;  // Стоит на месте смотрит вправо 
	QPixmap idleLeft;   

	QTimer* animationTimer;  

	int currentFrame;  // Индекс текущей картинки анимации
	bool movingLeft;   // Происходит движение влево 
	bool movingRight;  

};
