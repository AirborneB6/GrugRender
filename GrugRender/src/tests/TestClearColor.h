#pragma once

#include "Test.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"

#include "Asserts.h"

namespace test
{
	class TestClearColor : public Test
	{
	public:

		TestClearColor();
		~TestClearColor();

		void onUpdate(const float& deltaTime) override;
		void onRender() override;
		void onImguiRender() override;

	private:

		float m_ClearColor[4];

	};
}