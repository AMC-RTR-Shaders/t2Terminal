/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#pragma once
#ifndef _KEY_BOARD_H_
#define _KEY_BOARD_H_

namespace Event
{
	class KeyBoard
	{
	public:

		//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

		enum KEYS
		{
			A = 0x41,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z
		};

	};

}

#endif