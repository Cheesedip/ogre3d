/*-------------------------------------------------------------------------
This source file is a part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/


Copyright (c) 2000-2013 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:


The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE
-------------------------------------------------------------------------*/

//! [starter]

#include <exception>
#include <iostream>
#include <OgreTest.h>

TutorialApplication::TutorialApplication()
    : ApplicationContext("OgreTutorialApp")
{
}


TutorialApplication::~TutorialApplication()
{
}


void TutorialApplication::createScene()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    root->addFrameListener(this);

    m_scnMgr = root->createSceneManager();


    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(m_scnMgr);

    // -- tutorial section start --
    //! [cameracreate]
    SceneNode* camNode = m_scnMgr->getRootSceneNode()->createChildSceneNode();
    Camera* cam = m_scnMgr->createCamera("myCam");
    //! [cameracreate]

    //! [cameraposition]
    camNode->setPosition(200, 800, 800);
    camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);
    //! [cameraposition]

    //! [cameralaststep]
    cam->setNearClipDistance(5);
    camNode->attachObject(cam);
    //! [cameralaststep]

    //! [addviewport]
    Viewport* vp = getRenderWindow()->addViewport(cam);
    //! [addviewport]

    //! [viewportback]
    vp->setBackgroundColour(ColourValue(0, 0, 0));
    //! [viewportback]

    //! [cameraratio]
    cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    //! [cameraratio]

    //! [ninja]
    Entity* ninjaEntity = m_scnMgr->createEntity("ninja.mesh");
    ninjaEntity->setCastShadows(true);

    m_scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ninjaEntity);
    //! [ninja]

    //! [plane]
    Plane plane(Vector3::UNIT_Y, 0);
    //! [plane]

    //! [planedefine]
    MeshManager::getSingleton().createPlane(
            "ground",
            ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane,
            3000, 3000, 20, 20,
            true,
            1, 5, 5,
            Vector3::UNIT_Z);
    //! [planedefine]

    //! [planecreate]
    Entity* groundEntity = m_scnMgr->createEntity("ground");
    m_scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    //! [planecreate]

    //! [planenoshadow]
    groundEntity->setCastShadows(false);
    //! [planenoshadow]

    //! [planesetmat]
    groundEntity->setMaterialName("Examples/Rockwall");
    //! [planesetmat]

    //! [lightingsset]
    m_scnMgr->setAmbientLight(ColourValue(1, 1, 1));
    m_scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
    //! [lightingsset]

    /*
    //! [spotlight]
    Light* spotLight = m_scnMgr->createLight("SpotLight");
    //! [spotlight]

    //! [spotlightcolor]
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    //! [spotlightcolor]

    //! [spotlighttype]
    spotLight->setType(Light::LT_SPOTLIGHT);
    //! [spotlighttype]

    //! [spotlightposrot]
    SceneNode* spotLightNode = m_scnMgr->getRootSceneNode()->createChildSceneNode();
    spotLightNode->attachObject(spotLight);
    spotLightNode->setDirection(-1, -1, 0);
    spotLightNode->setPosition(Vector3(200, 200, 0));
    //! [spotlightposrot]

    //! [spotlightrange]
    spotLight->setSpotlightRange(Degree(35), Degree(50));
    //! [spotlightrange]

    //! [directlight]
    Light* directionalLight = m_scnMgr->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    //! [directlight]

    //! [directlightcolor]
    directionalLight->setDiffuseColour(ColourValue(0.4, 0, 0));
    directionalLight->setSpecularColour(ColourValue(0.4, 0, 0));
    //! [directlightcolor]

    //! [directlightdir]
    SceneNode* directionalLightNode = m_scnMgr->getRootSceneNode()->createChildSceneNode();
    directionalLightNode->attachObject(directionalLight);
    directionalLightNode->setDirection(Vector3(0, -1, 1));
    //! [directlightdir]
    */

    //! [pointlight]
    Light* pointLight = m_scnMgr->createLight("PointLight");
    pointLight->setType(Light::LT_POINT);
    //! [pointlight]

    //! [pointlightcolor]
    pointLight->setDiffuseColour(0.3, 0.3, 0.3);
    pointLight->setSpecularColour(0.3, 0.3, 0.3);
    //! [pointlightcolor]

    //! [pointlightpos]
    SceneNode* pointLightNode = m_scnMgr->getRootSceneNode()->createChildSceneNode();
    pointLightNode->attachObject(pointLight);
    pointLightNode->setPosition(Vector3(0, 150, 250));
    //! [pointlightpos]
    // -- tutorial section end --
}

/*
void TutorialApplication::createScene()
{
  mSceneMgr->setAmbientLight(Ogre::ColourValue(.25, .25, .25));

  Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
  pointLight->setType(Ogre::Light::LT_POINT);
  pointLight->setPosition(250, 150, 250);
  pointLight->setDiffuseColour(Ogre::ColourValue::White);
  pointLight->setSpecularColour(Ogre::ColourValue::White);

  Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("ninja.mesh");
  Ogre::SceneNode* ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
  ninjaNode->attachObject(ninjaEntity);

}
*/

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  bool ret = FrameListener::frameRenderingQueued(fe);

  if(!processUnbufferedInput(fe))
    return false;

  return ret;
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
    static bool mouseDownLastFrame = false;
    static Ogre::Real toggleTimer = 0.0;
    static Ogre::Real rotate = .13;
    static Ogre::Real move = 250;

    m_mouse->capture();
    bool leftMouseDown = m_mouse->getMouseState().buttonDown(OIS::MB_Left);

    if (leftMouseDown && !mouseDownLastFrame)
    {
      Ogre::Light* light = m_scnMgr->getLight("PointLight");
      light->setVisible(!light->isVisible());
    }

    mouseDownLastFrame = leftMouseDown;

    return true;
}

bool TutorialApplication::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}


int main(int argc, char **argv)
{
    try
    {
        TutorialApplication app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [starter]
