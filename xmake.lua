add_rules("mode.debug", "mode.release")

-- test

target("test_sort")
    set_kind("binary")
    add_includedirs("sort")
    add_files("sort/sort.cpp", "test/test_sort.cpp")
    on_load(function(target)
        target:add(find_packages("vcpkg::gtest"))
    end)
    if is_mode("debug") then 
        add_cxxflags("/MDd")
    else 
        add_cxxflags("/MD")
    end

target("test_search")
    set_kind("binary")
    add_includedirs("search")
    add_files("search/search.cpp", "test/test_search.cpp")
    on_load(function(target)
        target:add(find_packages("vcpkg::gtest"))
    end)
    if is_mode("debug") then 
        add_cxxflags("/MDd")
    else 
        add_cxxflags("/MD")
    end

target("test_algs")
    set_kind("binary")
    set_languages("c++17")
    add_includedirs("algs")
    add_files("algs/algs.cpp", "test/test_algs.cpp")
    on_load(function(target)
        target:add(find_packages("vcpkg::gtest"))
    end)
    if is_mode("debug") then 
        add_cxxflags("/MDd")
    else 
        add_cxxflags("/MD")
    end

target("test_libs")
    set_kind("binary")
    set_languages("c++17")
    add_includedirs("libs")
    add_files("libs/*.cpp")
    on_load(function(target)
        target:add(find_packages("vcpkg::gtest"))
    end)
    if is_mode("debug") then 
        add_cxxflags("/MDd /EHsc")
    else 
        add_cxxflags("/MD")
    end

-- benchmark

target("benchmark_sorted")
    set_kind("binary")
    add_includedirs("sort")
    add_files("sort/sort.cpp")
    add_files("benchmark/sorted.cpp")
    on_load(function(target)
        target:add(find_packages("vcpkg::benchmark"))
    end)
    if is_mode("debug") then 
        add_cxxflags("/MDd")
    else 
        add_cxxflags("/MD")
    end

target("benchmark_reverse")
    set_kind("binary")
    add_includedirs("sort")
    add_files("sort/sort.cpp")
    add_files("benchmark/reverse_sort.cpp")
    on_load(function(target)
        target:add(find_packages("vcpkg::benchmark"))
    end)
    add_ldflags("/STACK:8388608")
    if is_mode("debug") then 
        add_cxxflags("/MDd")
    else 
        add_cxxflags("/MD")
    end

target("benchmark_random")
    set_kind("binary")
    add_includedirs("sort")
    add_files("sort/sort.cpp")
    add_files("benchmark/random_sort.cpp")
    on_load(function(target)
        target:add(find_packages("vcpkg::benchmark"))
    end)
    if is_mode("debug") then 
        add_cxxflags("/MDd")
    else 
        add_cxxflags("/MD")
    end

target("benchmark_repeted")
    set_kind("binary")
    add_includedirs("sort")
    add_files("sort/sort.cpp")
    add_files("benchmark/repeted_sort.cpp")
    on_load(function(target)
        target:add(find_packages("vcpkg::benchmark"))
    end)
    if is_mode("debug") then 
        add_cxxflags("/MDd")
    else 
        add_cxxflags("/MD")
    end
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
-- 
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

