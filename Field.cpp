#include "Field.h"
#include "Engine/Model.h"

Field::Field(GameObject* parent)
{
}

Field::~Field()
{
}

void Field::Initialize()
{
}

void Field::Update()
{
}

void Field::Draw()
{
	for (auto& data : fieldData_) {
		Model::SetTransform(data.hModel, data.transform);
		Model::Draw(data.hModel);
	}
}

void Field::Release()
{
}
