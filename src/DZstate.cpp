/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; version 2 of the License.              *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   General Public License for more details.                             *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 03-13-2015	added pointer back to DZstateMachine					  *
 * 03-10-2015	file created                                              *
 **************************************************************************/


#include "DZstate.h"
#include "DZstateMachine.h"
#include "DZengine.h"
#include <string>
#include "DZproject.h"


DZstate::DZstate()
{
	levelPtr = 0;
	textureManagerPtr = 0;
}


void DZstate::onEnter()
{
	textureManagerPtr = new DZtextureManager;

	// get parser to retrieve all configuration data
	DZxmlParser* doc = DZengine::getStateMachine()->Parser();
	doc->getFirstState();
	while (doc->getStateID() != getStateID())
	{
		doc->getNextState();
		if (doc->getStateID() == 0)
		{
			// no more states to process
			DZ_LOG(DZ_LOG_WARN, "No state match");
			return;
		}
	}

	// got correct state - we can now proceed with the allocation
	// of the textures and objects

	// load all textures from parsed config file in texture manager
	doc->getFirstTexture();
	while (doc->getTextureID() != 0)
	{
		textureManagerPtr->load(string(doc->getTextureFilename()), doc->getTextureID());
		doc->getNextTexture();
	}

	// load all objects from parsed config file
	doc->getFirstObject();
	while (doc->getObjectID() != 0)
	{
		DZparams params;

		switch (doc->getCollisionType())
		{
			case DZ_COLLISION_BOX:
				params.box_collision = true;
				break;

			case DZ_COLLISION_CIRCULAR:
				params.circular_collision = true;
				break;

			case DZ_COLLISION_NONE:
			default:
				break;
		}

		params.Position.setX(doc->getObjectXposition());
		params.Position.setY(doc->getObjectYposition());
		params.Velocity.setX(doc->getObjectXvelocity());
		params.Velocity.setY(doc->getObjectYvelocity());
		params.Acceleration.setX(doc->getObjectXacceleration());
		params.Acceleration.setY(doc->getObjectYacceleration());
		params.RotationCenter.setX(doc->getObjectXrotationCenter());
		params.RotationCenter.setY(doc->getObjectYrotationCenter());
		params.angular_position = doc->getObjectAngularPosition();
		params.angular_velocity = doc->getObjectAngularVelocity();
		params.angular_acceleration = doc->getObjectAngularAcceleration();
		params.Width = doc->getObjectWidth();
		params.Height = doc->getObjectHeight();
		params.NumFrames = doc->getObjectNumFrames();
		params.CurrentRow = doc->getObjectCurrentRow();
		params.CurrentFrame = doc->getObjectCurrentFrame();
		params.NumRows = doc->getObjectNumRows();
		params.TextureID = doc->getObjectTextureID();
		params.flip = doc->getObjectFlipValue();
		params.TextureManagerPtr = textureManagerPtr;

		objectList[doc->getObjectID()] = DZcreateObject(doc->getObjectID(), &params, &objectList);

		doc->getNextObject();
	}

	if (doc->getStateLevel() == 0)
	{
		DZ_LOG(DZ_LOG_INFO, "Not using levels");
	}
	else
	{
		levelPtr = new DZlevel(this);
		levelPtr->onEnter(doc->getStateLevel());
	}
}


void DZstate::onExit()
{
	// delete all objects in the object list
	for (unsigned int i=0 ; i < objectList.getSize() ; i++)
	{
		if (objectList[i] != 0)
		{
			delete objectList[i];
		}
	}

	// delete texture manager along with all the contained textures
	if (textureManagerPtr != 0)
	{
		delete textureManagerPtr;
	}

	if (levelPtr != 0)
	{
		levelPtr->onExit();
		delete levelPtr;
	}
}



void DZstate::render()
{
	unsigned int num_objects = objectList.getSize();

	if (levelPtr != 0)
	{
		levelPtr->render(LAYER_BACKGROUND);
		levelPtr->render(LAYER_FOREGROUND);
	}

	for (unsigned int i=0 ; i < num_objects ; i++)
	{
		if (objectList[i] != 0)
		{
			objectList[i]->draw();
		}
	}

	if (levelPtr != 0)
	{
		levelPtr->render(LAYER_TOP);
	}
}


void DZstate::update()
{
	unsigned int num_objects = objectList.getSize();

	for (unsigned int i=0 ; i < num_objects ; i++)
	{
		if (objectList[i] != 0)
		{
			objectList[i]->update();
		}
	}
}


void DZstate::add_texture(const char* filename, unsigned int id)
{
	textureManagerPtr->load(string(filename), id);
}


DZtextureManager* DZstate::getTextureManager()
{
	return textureManagerPtr;
}


