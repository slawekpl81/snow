add_rules("plugin.compile_commands.autoupdate", {outputdir = "."})

add_rules("mode.debug", "mode.release")

if is_plat("mingw") then
    set_toolchains("mingw")
end

add_requires("raylib 6.0")

target("snow")
    set_kind("binary")
    set_languages("c++23")
    add_files("src/*.cpp")
    add_packages("raylib")

    if is_plat("mingw") then
        add_ldflags("-static", {force = true})
        if is_mode("release") then
            add_ldflags("-mwindows", {force = true})
        end
    end

    after_build(function (target)
        local asset_dir = path.join(os.projectdir(), "assets")
        if os.isdir(asset_dir) then
            os.cp(asset_dir, target:targetdir(), {force = true})
        end
    end)


    add_installfiles("(assets/**)", {prefixdir = "bin"})

