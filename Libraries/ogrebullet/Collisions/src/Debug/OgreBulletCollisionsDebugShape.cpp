/***************************************************************************

This source file is part of OGREBULLET
(Object-oriented Graphics Rendering Engine Bullet Wrapper)

Copyright (c) 2007 tuan.kuranes@gmail.com (Use it Freely, even Statically, but have to contribute any changes)



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
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "OgreBulletCollisions.h"

#include "OgreBulletCollisionsShape.h"
#include "Debug/OgreBulletCollisionsDebugShape.h"
#include "Utils/OgreBulletConverter.h"

using namespace OgreBulletCollisions;
using namespace Ogre;

//------------------------------------------------------------------------------------------------
DebugCollisionShape::DebugCollisionShape(CollisionShape *shape, DebugCollisionShape::Mode mode) 
{
    setStatemode(mode);
    // try to draw debug wire frame of the shape
    mIsVisual = shape->drawWireFrame(this);

    // if no success (not possible or not implemented
    // does not draw, hence saving a segfault
    if (mIsVisual)
    {
        DebugLines::draw();
    }
}
//------------------------------------------------------------------------------------------------
void DebugCollisionShape::setStatemode(DebugCollisionShape::Mode mode)
{
	if (mode != mStatemode)
	{
		mStatemode = mode;
		switch(mStatemode)
		{
			case DebugCollisionShape::Mode_Enabled:
				setMaterial("OgreBulletCollisionsDebugLines/Enabled");
			break;

			case DebugCollisionShape::Mode_Disabled:
				setMaterial("OgreBulletCollisionsDebugLines/Disabled");

			break;

			case DebugCollisionShape::Mode_Static:
				setMaterial("OgreBulletCollisionsDebugLines/Static");
			break;
		}
	}
}
//------------------------------------------------------------------------------------------------
DebugCollisionShape::~DebugCollisionShape() 
{
}
//------------------------------------------------------------------------------------------------
bool DebugCollisionShape::getIsVisual() const
{
    return mIsVisual;
}
//------------------------------------------------------------------------------------------------
void DebugCollisionShape::setIsVisual( bool val )
{
    mIsVisual = val;
}
//------------------------------------------------------------------------------------------------
RayDebugShape::RayDebugShape(const Ogre::Vector3& start, 
							   const Ogre::Vector3& direction, 
							   const Ogre::Real length)
{
    const Ogre::Vector3 end(start + (direction.normalisedCopy() * length));
	addLine(start, end);

	draw();
}
//------------------------------------------------------------------------------------------------
void RayDebugShape::setDefinition(const Ogre::Vector3& start,
							const Ogre::Vector3& direction, 
							const Ogre::Real length)
{
	clear();

    const Ogre::Vector3 end(start + (direction.normalisedCopy() * length));
	addLine(start, end);

	draw();
}
//------------------------------------------------------------------------------------------------
RayDebugShape::~RayDebugShape()
{
}
