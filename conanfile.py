from conans import ConanFile, CMake
import shutil

class CmlConan(ConanFile):
    name = "cml"
    url = "https://git.barco.com/projects/BAT/repos/3rd_cml"
    description = "Vector math library"
    generators = "cmake", "cmake_find_package"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "cml/*", "CMakeLists.txt"


    def build(self):
        cmake_generator=None
        if self.settings.os == "Windows":
            cmake_generator="NMake Makefiles"
        cmake = CMake(self, generator=cmake_generator)

        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", src="cml", dst="include/cml")

    def package_info(self):
        self.cpp_info.filenames["cmake_find_package"] = "cml"
        self.cpp_info.names["cmake_find_package"] = "cml"
        self.cpp_info.includedirs = ["include"]

