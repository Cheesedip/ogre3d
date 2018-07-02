#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <OgreApplicationContext.h>
#include <OgreCameraMan.h>

#include <ois/OISMouse.h>
#include <ois/OISKeyboard.h>

using namespace Ogre;
using namespace OgreBites;

class TutorialApplication
        : public ApplicationContext
        , public InputListener
{
public:
    TutorialApplication();
    virtual ~TutorialApplication();

    //void setup();
    bool keyPressed(const KeyboardEvent& evt);

    protected:
      virtual void createScene();
      virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

    private:
      SceneManager* m_scnMgr;
      OIS::Mouse *m_mouse;
      OIS::Keyboard *m_keyboard;
      bool processUnbufferedInput(const Ogre::FrameEvent& fe);
};


