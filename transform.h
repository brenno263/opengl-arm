#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#define OBJ_CYLINDER 0
#define OBJ_LINE 1
#define OBJ_SPHERE 2

class Transform
{
public:
	int objectType;
	Vec3 scale;
	Vec3 modelScale;
	Vec3 position;
	Vec3 rotateAngles;
	Vec3 color;
	Transform * parent;
	std::unordered_map<std::string, Transform *> children;
	std::string name;

	Transform(std::string _name, Transform * _parent = nullptr)
	{
		objectType = 0;
		scale = Vec3(1, 1, 1);
		modelScale = Vec3(1, 1, 1);
		position = Vec3();
		rotateAngles = Vec3(0, 0, 1);
		color = Vec3(1, 1, 1);
		parent = _parent;
		name = std::move(_name);
		children = std::unordered_map<std::string, Transform *>();
	}

	~Transform()
	{
		for(const auto& pair : children)
		{
			delete pair.second;
		}
	}

	Transform * applyGlobalTransformations()
	{
		glTranslated(position.x(), position.y(), position.z());

		glRotated(rotateAngles.x(), 1, 0, 0);
		glRotated(rotateAngles.y(), 0, 1, 0);
		glRotated(rotateAngles.z(), 0, 0, 1);

		glScaled(scale.x(), scale.y(), scale.z());
		glColor3d(color.x(), color.y(), color.z());

		return this;
	}

	Transform * applyLocalTransformations()
	{
		glScaled(modelScale.x(), modelScale.y(), modelScale.z());

		return this;
	}

	Transform * setObjectType(int _objectType)
	{
		objectType = _objectType;
		return this;
	}

	Transform * setScale(const Vec3& _scale)
	{
		scale = _scale;
		return this;
	}

	Transform * setModelScale(const Vec3& _modelScale)
	{
		modelScale = _modelScale;
		return this;
	}

	Transform * setPosition(const Vec3& _pos)
	{
		position = _pos;
		return this;
	}

	Transform * setRotation(const Vec3& angles)
	{
		rotateAngles = angles;
		return this;
	}

	Transform * setColor(const Vec3& _color)
	{
		color = _color;
		return this;
	}

	Transform * addChild(Transform * child)
	{
		children.emplace(child->name, child);
		return this;
	}

	Transform * makeChild(std::string child_name)
	{
		Transform * child = new Transform(child_name, this);
		children.emplace(child->name, child);
		return child;
	}

	Transform * getChild(const std::string& child_name)
	{
		return children.at(child_name);
	}
};