#include "Conveyor.h"
#include "Player.h"

void Conveyor::Initialize(Vector2 pos, Size size)
{
	pos_ = pos;
	size_ = size;
}

void Conveyor::Update()
{
}

void Conveyor::Draw()
{
}

void Conveyor::OnCollisionPlayer(Player* player)
{
}

Object Conveyor::GetObject()
{
	return Object({ pos_,size_ });
}
