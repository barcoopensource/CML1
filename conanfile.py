from conans import ConanFile, CMake
import shutil

class CmlConan(ConanFile):
    name = "cml"
    url = "https://git.barco.com/projects/BAT/repos/3rd_cml"
    license = "Boost Software License - Version 1.0"
    description = "Vector math library"
    settings = []
    exports_sources = "cml/*", "CMakeLists.txt"

    def package_id(self):
        self.info.header_only()

    def package(self):
        self.copy("*.h", src="cml", dst="include/cml")

    def package_info(self):
        self.cpp_info.filenames["cmake_find_package"] = "cml"
        self.cpp_info.names["cmake_find_package"] = "cml"
        self.cpp_info.includedirs = ["include"]
