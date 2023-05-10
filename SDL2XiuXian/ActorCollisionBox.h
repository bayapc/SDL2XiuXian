#pragma once

class ActorCollisionBox
{
public:
	ActorCollisionBox(int ax,int ay,int bx,int by);
	~ActorCollisionBox();
private:
	int Ax, Ay, Bx, By;
};

