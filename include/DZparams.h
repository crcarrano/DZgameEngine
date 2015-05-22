/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU Lesser General Public License as       *
 *   published by the Free Software Foundation; version 3 of the License. *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   Lesser General Public License for more details.                      *
 *   You should have received a copy of the Lesser GNU General Public     *
 *   License along with this program; if not, write to the Free Software  *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 05-21-2015	modified distribution license                             *
 * 03-09-2015	file created                                              *
 **************************************************************************/


#ifndef DZPARAMS_H
#define DZPARAMS_H

#include "DZvector2D.h"
#include "DZtextureManager.h"


/*****************************************************************
 *
 * Class:		DZparams
 *
 * Description:	Holds the parameters used by general object
 *				classes
 *
 * Interface:	Only the constructor. All the parameters
 *				are publicly accessible.
 *
 ****************************************************************/

class DZparams
{
	public:
		DZparams()
		{
			Position =				DZvector2D(0,0);
			Velocity = 				DZvector2D(0,0);
			Acceleration =			DZvector2D(0,0);
			RotationCenter = 		DZvector2D(0, 0);
			angular_position = 		0;
			angular_velocity = 		0;
			angular_acceleration =	0;
			Width = 				0;
			Height = 				0;
			CurrentRow = 			0;
			CurrentFrame = 			0;
			NumFrames = 			0;
			NumRows = 				0;
			TextureID = 			0;
			TextureManagerPtr = 	0;
			box_collision = 		false;
			circular_collision = 	false;
			flip = 					SDL_FLIP_NONE;
		}

		DZparams(DZvector2D position,
			 	 DZvector2D velocity,
			 	 DZvector2D acceleration,
			 	 DZvector2D rotationCenter,
			 	 float angularPosition,
			 	 float angularVelocity,
			 	 float angularAcceleration,
			 	 unsigned int width,
			 	 unsigned int height,
			 	 unsigned int current_row,
			 	 unsigned int current_frame,
			 	 unsigned int num_frames,
			 	 unsigned int num_rows,
			 	 unsigned int texture_id,
			 	 DZtextureManager* tm_ptr,
			 	 bool b_collision,
			 	 bool c_collision,
			 	 SDL_RendererFlip flag)
		{
			Position = 				position;
			Velocity = 				velocity;
			Acceleration = 			acceleration;
			RotationCenter = 		rotationCenter;
			angular_position = 		angularPosition;
			angular_velocity = 		angularVelocity;
			angular_acceleration = 	angularAcceleration;
			Width = 				width;
			Height = 				height;
			CurrentRow = 			current_row;
			CurrentFrame = 			current_frame;
			NumFrames = 			num_frames;
			NumRows = 				num_rows;
			TextureID = 			texture_id;
			TextureManagerPtr = 	tm_ptr;
			box_collision = 		b_collision;
			circular_collision = 	c_collision;
			flip = 					flag;
		}

		DZparams(const DZparams* parm_ptr)
		{
			Position = 	      		parm_ptr->Position;
			Velocity = 	       		parm_ptr->Velocity;
			Acceleration = 	       	parm_ptr->Acceleration;
			RotationCenter =       	parm_ptr->RotationCenter;
			angular_position =     	parm_ptr->angular_position;
			angular_velocity =     	parm_ptr->angular_velocity;
			angular_acceleration = 	parm_ptr->angular_acceleration;
			Width = 	       		parm_ptr->Width;
			Height = 	       		parm_ptr->Height;
			CurrentRow = 	       	parm_ptr->CurrentRow;
			CurrentFrame = 	       	parm_ptr->CurrentFrame;
			NumFrames = 	       	parm_ptr->NumFrames;
			NumRows = 	       		parm_ptr->NumRows;
			TextureID = 	       	parm_ptr->TextureID;
			TextureManagerPtr =    	parm_ptr->TextureManagerPtr;
			box_collision =	       	parm_ptr->box_collision;
			circular_collision =   	parm_ptr->circular_collision;
			flip =                 	parm_ptr->flip;
		}

		DZvector2D	   		Position;
		DZvector2D	   		Velocity;
		DZvector2D	   		Acceleration;
		DZvector2D	   		RotationCenter;
		float		   		angular_position;
		float		   		angular_velocity;
		float		   		angular_acceleration;
		unsigned int	   	Width;
		unsigned int	   	Height;
		unsigned int	   	CurrentRow;
		unsigned int	   	CurrentFrame;
		unsigned int	   	NumFrames;
		unsigned int	   	NumRows;
		unsigned int	   	TextureID;
		DZtextureManager*  	TextureManagerPtr;
		bool		   		box_collision;
		bool		   		pixel_collision;
		bool		   		circular_collision;
		DZarray<SDL_Rect>* 	pixel_collider;
		SDL_RendererFlip   	flip;

	protected:
	private:
};

#endif // DZPARAMS_H
