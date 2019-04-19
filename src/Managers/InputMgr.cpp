/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreVector3.h>

#include "Engine.h"
#include "InputMgr.h"
#include "GfxMgr.h"
#include "EntityMgr.h"
#include "GameMgr.h"

#include "Player.h"

#include "UnitAI.h"
#include "OrientedPhysics3D.h"

using Ogre::Vector3;

class Command;
class Intercept;

InputMgr::InputMgr(Engine *eng) :
		Mgr(eng), mInputMgr(0), mMouse(0), mKeyboard(0) {

}

InputMgr::~InputMgr() {
	Ogre::WindowEventUtilities::removeWindowEventListener(
			engine->gfxMgr->mWindow, this);
	windowClosed(engine->gfxMgr->mWindow);
}

void InputMgr::Init() {
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	OIS::ParamList pl;
	size_t windowHandle = 0;
	std::ostringstream windowHandleStr;

	engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleStr << windowHandle;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

	pl.insert(
			std::make_pair(std::string("x11_mouse_grab"),
					std::string("false")));
	pl.insert(
			std::make_pair(std::string("x11_mouse_hide"),
					std::string("false")));
	pl.insert(
			std::make_pair(std::string("x11_keyboard_grab"),
					std::string("false")));
	pl.insert(
			std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));

	mInputMgr = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(
			OIS::OISKeyboard, true));
	mKeyboard->setEventCallback(this);
	mMouse = static_cast<OIS::Mouse*>(mInputMgr->createInputObject(
			OIS::OISMouse, true));
	mMouse->setEventCallback(this);

	pl.insert(
			std::make_pair(std::string("x11_mouse_grab"),
					std::string("false")));
	pl.insert(
			std::make_pair(std::string("x11_keyboard_grab"),
					std::string("false")));

	windowResized(engine->gfxMgr->mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->mWindow,
			this);
}

void InputMgr::Tick(float dt) {
	if (engine->gfxMgr->mWindow->isClosed()) {
		engine->keepRunning = false;
		return;
	}
	mKeyboard->capture();
	mMouse->capture();
	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) {
		engine->keepRunning = false;
		return;
	}

	UpdatePlayer(dt);
	//UpdateCamera(dt);
	//UpdateShipDesiredAttributes(dt);
	//UpdateSelection(dt);
}

void InputMgr::UpdatePlayer(float dt) {
	Player * player = engine->gameMgr->MainPlayer;

	// uses yghj
	Vector3 movement = Vector3::ZERO;
	if (mKeyboard->isKeyDown(OIS::KC_A)) {
		movement.x -= 1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_D)) {
		movement.x += 1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_W)) {
		movement.z -= 1;
	}
	if (mKeyboard->isKeyDown(OIS::KC_S)) {
		movement.z += 1;
	}

	// movement == zero, will tell the player to go back to idle animation
	player->Move(movement, dt);

}

void InputMgr::UpdateCamera(float dt) {
	float speedScalar = 1;
	if (mKeyboard->isKeyDown(OIS::KC_LSHIFT)) {
		speedScalar = 2;
	}

	//Translation
	Ogre::Vector3 cameraVelocity = Ogre::Vector3::ZERO;
	if (mKeyboard->isKeyDown(OIS::KC_A)) {
		cameraVelocity.x -= cameraSpeed;
	}
	if (mKeyboard->isKeyDown(OIS::KC_D)) {
		cameraVelocity.x += cameraSpeed;
	}
	if (mKeyboard->isKeyDown(OIS::KC_W)) {
		cameraVelocity.z -= cameraSpeed;
	}
	if (mKeyboard->isKeyDown(OIS::KC_S)) {
		cameraVelocity.z += cameraSpeed;
	}
	if (mKeyboard->isKeyDown(OIS::KC_F)) {
		cameraVelocity.y -= cameraSpeed;
	}
	if (mKeyboard->isKeyDown(OIS::KC_R)) {
		cameraVelocity.y += cameraSpeed;
	}
	Ogre::SceneNode *cam = engine->gfxMgr->mCameraNode;
	cam->translate(cameraVelocity * speedScalar * dt,
			Ogre::Node::TransformSpace::TS_LOCAL);
	if (cam->getPosition().y < engine->gameMgr->surfaceHeight + 5) {
		cam->setPosition(cam->getPosition().x,
				engine->gameMgr->surfaceHeight + 5, cam->getPosition().z);
	}

	//Rotation
	if (mKeyboard->isKeyDown(OIS::KC_Q)) {
		cam->rotate(Ogre::Vector3(0, 1, 0),
				Ogre::Radian(Ogre::Degree(cameraRotationSpeed)) * speedScalar
						* dt, Ogre::Node::TransformSpace::TS_WORLD);
	}
	if (mKeyboard->isKeyDown(OIS::KC_E)) {
		cam->rotate(Ogre::Vector3(0, 1, 0),
				-Ogre::Radian(Ogre::Degree(cameraRotationSpeed)) * speedScalar
						* dt, Ogre::Node::TransformSpace::TS_WORLD);
	}
	if (mKeyboard->isKeyDown(OIS::KC_Z)) {
		cam->rotate(Ogre::Vector3(1, 0, 0),
				Ogre::Radian(Ogre::Degree(cameraRotationSpeed)) * speedScalar
						* dt, Ogre::Node::TransformSpace::TS_LOCAL);
	}
	if (mKeyboard->isKeyDown(OIS::KC_X)) {
		cam->rotate(Ogre::Vector3(1, 0, 0),
				-Ogre::Radian(Ogre::Degree(cameraRotationSpeed)) * speedScalar
						* dt, Ogre::Node::TransformSpace::TS_LOCAL);
	}
}

void InputMgr::UpdateShipDesiredAttributes(float dt) {
	static bool leftArrow_DownLastFrame = false;
	static bool rightArrow_DownLastFrame = false;
	static bool upArrow_DownLastFrame = false;
	static bool downArrow_DownLastFrame = false;
	static bool pgUp_DownLastFrame = false;
	static bool pgDown_DownLastFrame = false;

	bool left = mKeyboard->isKeyDown(OIS::KC_LEFT);
	bool right = mKeyboard->isKeyDown(OIS::KC_RIGHT);
	bool up = mKeyboard->isKeyDown(OIS::KC_UP);
	bool down = mKeyboard->isKeyDown(OIS::KC_DOWN);
	bool pgUp = mKeyboard->isKeyDown(OIS::KC_PGUP);
	bool pgDown = mKeyboard->isKeyDown(OIS::KC_PGDOWN);

	Entity381 *cur =
			engine->entityMgr->entities[engine->entityMgr->currentEntity];
	OrientedPhysics3D *physics = cur->GetAspect<OrientedPhysics3D>();
	if (physics != NULL) {
		if (left && !leftArrow_DownLastFrame) {
			physics->desiredHeading -= shipAngleIncrement;
		}
		if (right && !rightArrow_DownLastFrame) {
			physics->desiredHeading += shipAngleIncrement;
		}
		if (up && !upArrow_DownLastFrame) {
			physics->desiredSpeed += shipSpeedIncrement;
		}
		if (down && !downArrow_DownLastFrame) {
			physics->desiredSpeed -= shipSpeedIncrement;
		}
		if (pgDown && !pgDown_DownLastFrame) {
			physics->desiredAltitude -= shipAltitudeIncrement;
		}
		if (pgUp && !pgUp_DownLastFrame) {
			physics->desiredAltitude += shipAltitudeIncrement;
		}

		//Disable movement
		if (mKeyboard->isKeyDown(OIS::KC_SPACE)) {
			physics->desiredSpeed = 0;
		}
	}

	leftArrow_DownLastFrame = left;
	rightArrow_DownLastFrame = right;
	upArrow_DownLastFrame = up;
	downArrow_DownLastFrame = down;
	pgUp_DownLastFrame = pgUp;
	pgDown_DownLastFrame = pgDown;
}

void InputMgr::UpdateSelection(float dt) {
	static bool tab_DownLastFrame = false;
	bool tab = mKeyboard->isKeyDown(OIS::KC_TAB);
	if (tab && !tab_DownLastFrame) {
		engine->entityMgr->entities[engine->entityMgr->currentEntity]->isSelected =
				false;
		engine->entityMgr->currentEntity =
				(engine->entityMgr->currentEntity + 1)
						% engine->entityMgr->entities.size();
		engine->entityMgr->entities[engine->entityMgr->currentEntity]->isSelected =
				true;
	}
	tab_DownLastFrame = tab;
}

void InputMgr::LoadLevel() {

}

void InputMgr::Stop() {

}

void InputMgr::windowResized(Ogre::RenderWindow* rw) {
	int left, top;
	unsigned int width, height, depth;

	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void InputMgr::windowClosed(Ogre::RenderWindow* rw) {
	if (rw == engine->gfxMgr->mWindow) {
		if (mInputMgr) {
			mInputMgr->destroyInputObject(mMouse);
			mInputMgr->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputMgr);
			mInputMgr = 0;
		}
	}
}

std::pair<bool, Ogre::Vector3> InputMgr::GetClickedPosition(
		const OIS::MouseEvent& me) {
	Ogre::Viewport* vp = engine->gfxMgr->mViewport;
	Ogre::Real x = me.state.X.abs / Ogre::Real(vp->getActualWidth());
	Ogre::Real y = me.state.Y.abs / Ogre::Real(vp->getActualHeight());

	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(x, y);

	std::pair<bool, Ogre::Real> point = mouseRay.intersects(engine->gameMgr->mPlane);

	if (point.first) {
		Ogre::Vector3 intersect = mouseRay.getPoint(point.second);
		return std::pair<bool, Ogre::Vector3>(true, intersect);
	} else {
		return std::pair<bool, Ogre::Vector3>(false, Ogre::Vector3::ZERO);
	}
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me) {
	std::pair<bool, Ogre::Vector3> intersection = GetClickedPosition(me);
	if (intersection.first) {
		engine->gameMgr->MainPlayer->LookAt(intersection.second);
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id) {
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id) {
	std::pair<bool, Ogre::Vector3> intersection = GetClickedPosition(me);
	if (intersection.first) {
		Ogre::Vector3 cameraPos = engine->gfxMgr->mCameraNode->getPosition();
		Ogre::Vector3 intersect = intersection.second;

		float shortestDistance = -1;
		Entity381 *best = NULL;
		for (unsigned int i = 0; i < (engine->entityMgr->entities).size();
				++i) {
			Entity381 *cur = engine->entityMgr->entities[i];
			Ogre::Vector3 pos = cur->position;
			float distance =
					(pos - intersect).crossProduct(pos - cameraPos).length()
							/ (intersect - cameraPos).length();
			if ((distance < shortestDistance || shortestDistance == -1)
					&& distance <= selectionDistanceThreshold) {
				shortestDistance = distance;
				best = cur;
			}
		}

		if (id == OIS::MouseButtonID::MB_Left) {
			if (shortestDistance >= 0) {
				engine->entityMgr->entities[engine->entityMgr->currentEntity]->isSelected =
						false;
				engine->entityMgr->currentEntity = best->entityId;
				engine->entityMgr->entities[engine->entityMgr->currentEntity]->isSelected =
						true;
			}
		} else if (id == OIS::MouseButtonID::MB_Right) {
			Entity381 *cur =
					engine->entityMgr->entities[engine->entityMgr->currentEntity];
			UnitAI *unitAI = cur->GetAspect<UnitAI>();
			if (unitAI != NULL) {
				if (shortestDistance >= 0) {
					unitAI->SetCommand(new Intercept(cur, best));
				} else {
					if (mKeyboard->isKeyDown(OIS::KC_LSHIFT)) {
						unitAI->AddCommand(new MoveTo(cur, intersect));
					} else {
						unitAI->SetCommand(new MoveTo(cur, intersect));
					}
				}
			}
		}
		//engine->entityMgr->CreateEntityOfTypeAtPosition(EntityType::Sphere, intersect);
	}
	return true;
}

#include "Enemy.h"

bool InputMgr::keyPressed(const OIS::KeyEvent& ke) {

	switch (ke.key) {
	default:
		break;
	}
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke) {
	return true;
}

