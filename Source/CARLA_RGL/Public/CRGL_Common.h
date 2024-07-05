#pragma once
#include "rgl/api/core.h"



DECLARE_LOG_CATEGORY_EXTERN(LogCarlaRGL, Log, Log);



void CheckRGLResult(int32_t status);



rgl_mat3x4f ToRGLTransform(
  const FTransform& Transform);



template <typename T>
class FCarlaRGLHandleMixin
{
	T handle;
public:

	constexpr FCarlaRGLHandleMixin() : handle() { }
	FCarlaRGLHandleMixin(const FCarlaRGLHandleMixin&) = default;
	FCarlaRGLHandleMixin& operator=(const FCarlaRGLHandleMixin&) = default;
	~FCarlaRGLHandleMixin() = default;

	constexpr auto GetHandle() const
	{
		return handle;
	}

protected:

	constexpr auto GetHandlePtr()
	{
		return &handle;
	}

	constexpr auto GetHandlePtr() const
	{
		return &handle;
	}

	constexpr void SetHandle(T new_handle)
	{
		check(handle == T());
		handle = new_handle;
	}
};