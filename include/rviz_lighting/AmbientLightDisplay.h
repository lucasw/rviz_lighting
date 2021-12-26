/** @file AmbientLightDisplay.h
 *  Copyright 2017 NASA Ames Research Center
 *
 *  This software was created by Terry Welsh for the Intelligent Robotics Group
 *  at NASA Ames Research Center. Copies and derivatives of this file must
 *  retain this paragraph. There are no other restrictions on the use of this
 *  software.
 *
 *  @author Terry Welsh (terence.m.welsh@nasa.gov)
 */

#ifndef RVIZ_LIGHTING_AMBIENTLIGHTDISPLAY_H
#define RVIZ_LIGHTING_AMBIENTLIGHTDISPLAY_H

#include <rviz/display.h>


namespace rviz
{
class ColorProperty;
}

namespace rviz_lighting
{


/**
 * \class AmbientLightDisplay
 * \brief This class wraps OGRE::SceneManager::setAmbientLight()
 *
 * \todo: make it so you can add only one AmbientLight to an rviz config
 */
class AmbientLightDisplay : public rviz::Display
{
Q_OBJECT
public:
  // RViz requires plugins to use default constructor with no arguments
  AmbientLightDisplay();
  virtual ~AmbientLightDisplay();

protected:
  void onInitialize() override;

  void onEnable() override;

  void onDisable() override;

  void reset() override;

private Q_SLOTS:
  void updateColor();

private:
  // User-editable property variables
  rviz::ColorProperty* color_property_;
};


}  // end namespace rviz_lighting

#endif  // RVIZ_LIGHTING_AMBIENTLIGHTDISPLAY_H
