#pragma once

namespace test
{
	class Test
	{
	public:

		Test();
		virtual ~Test();

		virtual void onUpdate(const float& deltaTime);
		virtual void onRender();
		virtual void onImguiRender();

	private:

	};
}