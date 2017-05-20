#pragma once
#include "../PCH.h"

namespace BasicEngine {
	class IObject {
	public :
		template <class C>
		void AddComponent(std::shared_ptr<C> component) {
			for (auto& existingComponent : components) {
				if (std::dynamic_pointer_cast<C>(existingComponent)) {
					existingComponent = component;
					return;
				}
			}
			components.emplace_back(component);
		}
		template <class C>
		std::shared_ptr<C> GetComponent() {
			for (auto& existingComponent : components) {
				if (std::dynamic_pointer_cast<C>(existingComponent)) {
					return std::dynamic_pointer_cast<C>(existingComponent);
				}
			}
			return nullptr;
		}
	private:
		std::vector<std::shared_ptr<IComponent>> components;
	};
}