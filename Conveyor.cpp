#include "Conveyor.h"

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

Object Conveyor::GetObject()
{
	return Object({ pos_,size_ });
}
