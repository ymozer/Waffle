#pragma once

namespace Waffle {

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(float ts) {}
		virtual void OnUIRender() {}
	};

}