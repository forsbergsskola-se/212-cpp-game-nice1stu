#pragma once

#include <assert.h>
#include <stdio.h>


template <class T>
class CSingleton
{
protected:

			 CSingleton			(void) {s_pInstance = (T*)this;}
	virtual ~CSingleton			(void) {s_pInstance = nullptr;}

public:


	static void	Initialize		(void)
	{
	#ifdef _DEBUG
		assert(!s_pInstance);
	#endif

		new T;
	}


	static void	Deinitialize	(void)
	{
	#ifdef _DEBUG
		assert(s_pInstance);
	#endif

		delete s_pInstance;
	}

	static T&	GetInstance		(void)
	{
	#ifdef _DEBUG
		assert(s_pInstance);
	#endif

		return *s_pInstance;
	}


	static T*	GetInstancePtr	(void)
	{
	#ifdef _DEBUG
		assert(s_pInstance);
	#endif

		return s_pInstance;
	}

private:

	static T* s_pInstance;

};

template <class T> T* CSingleton<T>::s_pInstance = nullptr;