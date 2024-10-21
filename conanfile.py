from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class Recipe(ConanFile):
    name = "udp_socket"
    version = "0.1.0"

    # Binary configuration
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps"
    requires = []

    def config_options(self):
        pass

    def layout(self):
        cmake_layout(self)
        self.cpp.source.includedirs = ["."]        

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["udp_socket"]
