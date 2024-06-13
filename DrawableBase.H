#pragma once
#include "Drawable.h"
#include "IndexBuffer.h"

template<class T>
class DrawableBase : public Drawable
{
protected:
	 bool IsStaticInitialized() const noexcept
	{
		return !staticBinds.empty();
	}
	static void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept (!IS_DEBUG)
	{
		assert("*Must* use AddStaticIndexBuffer to bind index buffer");
		staticBinds.push_back(std::move(bind));
	}
	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> iBuf) noexcept (!IS_DEBUG)
	{
		assert("*Must* use AddIndexBuffer to bind index buffer");
		pIndexBuffer = iBuf.get();
		staticBinds.push_back(std::move(iBuf));
	}
	void SetIndexFromStatic() noexcept(!IS_DEBUG)
	{
		assert("Attempting to add index buffer a second time");
		for (const auto& b : staticBinds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
			{
				pIndexBuffer = p;
				return;
			}
		}
	}
private:
	const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept
	{
		return staticBinds;
	}
private:
	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};
template<class T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::staticBinds;