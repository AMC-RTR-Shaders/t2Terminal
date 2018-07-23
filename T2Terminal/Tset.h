#pragma once
#ifndef _TSET_H_
#define _TSET_H
#include"Runway.h"

namespace Rushabh
{
	class Tset : public Rushabh::Runway
	{

	public :
		Tset();
		~Tset();

		void Render(HDC hdc);

	};
}

#endif
