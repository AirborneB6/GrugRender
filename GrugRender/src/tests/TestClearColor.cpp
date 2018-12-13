#include "TestClearColor.h"

namespace test
{
	TestClearColor::TestClearColor() : m_ClearColor{0.3f , 0.8f , 0.4f , 1.0f}
	{

	}
	TestClearColor::~TestClearColor()
	{

	}
	void TestClearColor::onUpdate(const float & deltaTime)
	{

	}
	void TestClearColor::onRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	}
	void TestClearColor::onImguiRender()
	{

	}
}