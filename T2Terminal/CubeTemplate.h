#pragma once
#ifndef _CUBETEMPLATE_H_
#define _CUBETEMPLATE_H_
#include"Cube.h"

namespace Rushabh
{
	class CubeTemplate : public Utility::Cube
	{
		private:
			float angle;
			float speed;

		public :
			CubeTemplate();
			~CubeTemplate();

			void Render(HDC hdc, struct Attributes attributes);
			void Update();
	};
}

#endif
