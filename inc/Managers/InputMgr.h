/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_INPUTMGR_H_
#define INC_INPUTMGR_H_

#include <OgreWindowEventUtilities.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "Mgr.h"

class InputMgr : public Mgr,
                 public Ogre::WindowEventListener,
                 public OIS::MouseListener,
                 public OIS::KeyListener{
public:
    InputMgr(Engine *eng);
    ~InputMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();

    OIS::InputManager* mInputMgr;
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;
protected:
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);
private:
    virtual bool mouseMoved(const OIS::MouseEvent& me);
    virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
    virtual bool keyPressed(const OIS::KeyEvent& ke);
    virtual bool keyReleased(const OIS::KeyEvent& ke);

    void UpdateShipDesiredAttributes(float dt);
    void UpdateSelection(float dt);
    void UpdateCamera(float dt);
    void UpdatePlayer(float dt);

    float shipAngleIncrement = 45;
    float shipSpeedIncrement = 10;
    float shipAltitudeIncrement = 10;
    float cameraSpeed = 400;
    float cameraRotationSpeed = 30;
    float selectionDistanceThreshold = 100;
};

#endif /* INC_INPUTMGR_H_ */
