#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
    }

private:
	GLFWwindow* window;
	VkInstance instance;

    void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

    void initVulkan() {
		createInstance();
    }

	void createInstance() {
		VkApplicationInfo appInfo {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create instance!");
		}

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		std::cout << "Available extensions:\n";

		for (const auto& extension : extensions) {
			std::cout << "\t" << extension.extensionName << "\n";
		}

		if (!requiredExtensionsAreAvailable(glfwExtensions, glfwExtensionCount,  extensions)) {
			throw std::runtime_error("Required extensions are not available");
		}
	}

	bool requiredExtensionsAreAvailable(const char** glfwExtensions, int glfwExtensionCount, std::vector<VkExtensionProperties>& extensions) {
		for (int i = 0; i < glfwExtensionCount; i++) {
			bool isAvailable = false;

			for (const auto& extension : extensions) {
				if (strcmp(glfwExtensions[i], extension.extensionName) == 0) {
					isAvailable = true;
					break;
				}
			}

			if (!isAvailable) return false;
		}

		return true;
	}

    void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
    }

    void cleanup() {
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
		app.run();
    }
    catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}