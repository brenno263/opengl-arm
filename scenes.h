#pragma once

/*
 * Here we define scenes by creating all the appropriate transforms.
 * Each function must set the global root transform, and set up glutKeyboardFunc(keyboard).
 */


void render();

void cameraKeyboard(unsigned char key, int x, int y)
{
	double trans_inc = 0.1;

	switch (key)
	{
		case 'w':
			root->position += Vec3(0, -trans_inc, 0);
			break;
		case 'a':
			root->position += Vec3(trans_inc, 0, 0);
			break;
		case 's':
			root->position += Vec3(0, trans_inc, 0);
			break;
		case 'd':
			root->position += Vec3(-trans_inc, 0, 0);
			break;
		case 'q':
			root->rotateAngles += Vec3(0, 5, 0);
			break;
		case 'e':
			root->rotateAngles += Vec3(0, -5, 0);
			break;
		case 'r':
			root->position += Vec3(0, 0, -trans_inc);
			break;
		case 'f':
			root->position += Vec3(0, 0, trans_inc);
			break;
	}
}

void assignmentCameraKeyboard(unsigned char key, int x, int y)
{
	double trans_inc = 0.1;

	switch (key)
	{
		case 'x':
			root->position += Vec3(trans_inc, 0, 0);

			break;
		case 'X':
			root->position += Vec3(-trans_inc, 0, 0);
			break;
		case 'y':
			root->position += Vec3(0, trans_inc, 0);
			break;
		case 'Y':
			root->position += Vec3(0, -trans_inc, 0);
			break;
		case 'z':
			root->position += Vec3(0, 0, trans_inc);
			break;
		case 'Z':
			root->position += Vec3(0, 0, -trans_inc);
			break;
	}
}

bool handClosed = false;
void toggleGrab()
{
	Transform * joint3 = root
			->getChild("arm1")
			->getChild("arm2")
			->getChild("arm3")
			->getChild("joint3");

	Transform * finger1 = joint3->getChild("finger1");
	Transform * finger2 = joint3->getChild("finger2");
	Transform * finger3 = joint3->getChild("finger3");

	if(handClosed)
	{
		finger1->setRotation(Vec3(55, 0, 0));
		finger2->setRotation(Vec3(-30, 0, 40));
		finger3->setRotation(Vec3(-30, 0, -40));
	} else {
		finger1->setRotation(Vec3(0, 0, 0));
		finger2->setRotation(Vec3(0, 0, 0));
		finger3->setRotation(Vec3(0, 0, 0));
	}

	handClosed = !handClosed;
}

void armKeyboard(unsigned char key, int x, int y)
{
	assignmentCameraKeyboard(key, x, y);
	Transform * arm1 = root->getChild("arm1");
	Transform * arm2 = arm1->getChild("arm2");
	Transform * arm3 = arm2->getChild("arm3");

	switch (key)
	{
		case 'u':
			arm1->rotateAngles += Vec3(0, 0, 10);
			break;
		case 'U':
			arm1->rotateAngles += Vec3(0, 0, -10);
			break;
		case 'v':
			arm1->rotateAngles += Vec3(0, 10, 0);
			break;
		case 'V':
			arm1->rotateAngles += Vec3(0, -10, 0);
			break;
		case 'w':
			arm1->rotateAngles += Vec3(10, 0, 0);
			break;
		case 'W':
			arm1->rotateAngles += Vec3(-10, 0, 0);
			break;
		case 'c':
			arm2->rotateAngles += Vec3(0, 0, 10);
			break;
		case 'C':
			arm2->rotateAngles += Vec3(0, 0, -10);
			break;
		case 'r':
			arm2->rotateAngles += Vec3(0, 10, 0);
			break;
		case 'R':
			arm2->rotateAngles += Vec3(0, -10, 0);
			break;
		case 'p':
			arm3->rotateAngles += Vec3(0, 0, 10);
			break;
		case 'P':
			arm3->rotateAngles += Vec3(0, 0, -10);
			break;
		case 'a':
			arm3->rotateAngles += Vec3(10, 0, 0);
			break;
		case 'A':
			arm3->rotateAngles += Vec3(-10, 0, 0);
			break;
		case 'o':
			toggleOrthoPerspective();
		case 'g':
			toggleGrab();
			break;
	}

	render();
}

void loadArmScene()
{
	delete root;
	root = new Transform("root");
	glutKeyboardFunc(armKeyboard);

	Vec3 jointColor(0.1, 0.3, 0.6);
	Vec3 arm1Color(0.9, 0.5, 0.4);
	Vec3 arm2Color(0.5, 0.9, 0.4);
	Vec3 arm3Color(0.5, 0.6, 0.9);
	Vec3 fingerColor(0.7, 0.4, 0.6);

	root
			->setObjectType(OBJ_SPHERE)
			->setPosition(Vec3(-0.8, 0, -2))
			->setRotation(Vec3(0, 0, -90))
			->setModelScale(Vec3(0.2, 0.2, 0.2))
			->setColor(jointColor);

	Transform *arm1 = root->makeChild("arm1")
			->setObjectType(OBJ_CYLINDER)
			->setPosition(Vec3(0, 0, 0))
			//->setRotation(Vec3(0, 0, -25))
			->setColor(arm1Color);

	arm1->makeChild("joint1")
			->setObjectType(OBJ_SPHERE)
			->setPosition(Vec3(0, 0.5, 0))
			->setModelScale(Vec3(0.2, 0.2, 0.2))
			->setColor(jointColor);

	Transform * arm2 = arm1->makeChild("arm2")
			->setObjectType(OBJ_CYLINDER)
			->setPosition(Vec3(0, 0.5, 0))
			//->setRotation(Vec3(0, 0, 25))
			->setColor(arm2Color);

	arm2->makeChild("joint2")
		->setObjectType(OBJ_SPHERE)
		->setPosition(Vec3(0, 0.5, 0))
		->setModelScale(Vec3(0.2, 0.2, 0.2))
		->setColor(jointColor);

	Transform * arm3 = arm2->makeChild("arm3")
			->setObjectType(OBJ_CYLINDER)
			->setPosition(Vec3(0, 0.5, 0))
			->setColor(arm3Color);

	Transform * joint3 = arm3->makeChild("joint3")
		->setObjectType(OBJ_SPHERE)
		->setPosition(Vec3(0, 0.5, 0))
		->setModelScale(Vec3(0.2, 0.2, 0.2))
		->setColor(jointColor);

	Vec3 fingerScale = Vec3(0.3, 0.5, 0.3);

	Transform * finger1 = joint3->makeChild("finger1")
			->setObjectType(OBJ_CYLINDER)
			->setPosition(Vec3(-0.03, 0.05, 0.04))
			->setRotation(Vec3(55, 0, 0))
			->setModelScale(fingerScale)
			->setColor(fingerColor);

	Transform * finger2 = joint3->makeChild("finger2")
			->setObjectType(OBJ_CYLINDER)
			->setPosition(Vec3(-0.03, 0.05, -0.04))
			->setRotation(Vec3(-30, 0, 40))
			->setModelScale(fingerScale)
			->setColor(fingerColor);

	Transform * finger3 = joint3->makeChild("finger3")
			->setObjectType(OBJ_CYLINDER)
			->setPosition(Vec3(0.05, 0.05, 0))
			->setRotation(Vec3(-30, 0, -40))
			->setModelScale(fingerScale)
			->setColor(fingerColor);

	Vec3 fingertipModelScale = Vec3(0.06, 0.06, 0.06);
	Vec3 fingertipPosition = Vec3(0, fingerScale.y() * 0.5, 0);

	finger1->makeChild("fingertip")
			->setObjectType(OBJ_SPHERE)
			->setPosition(fingertipPosition)
			->setModelScale(fingertipModelScale);

	finger2->makeChild("fingertip")
			->setObjectType(OBJ_SPHERE)
			->setPosition(fingertipPosition)
			->setModelScale(fingertipModelScale);

	finger3->makeChild("fingertip")
			->setObjectType(OBJ_SPHERE)
			->setPosition(fingertipPosition)
			->setModelScale(fingertipModelScale);
}