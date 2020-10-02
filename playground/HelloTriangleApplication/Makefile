CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTest: main.cpp
	mkdir -p bin
	g++ $(CFLAGS) -o bin/VulkanTest main.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	mkdir -p bin
	./bin/VulkanTest

clean:
	rm -f bin/VulkanTest
