project(
  'tangi',
  'cpp',
  'c',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++20'],
)

cc = meson.get_compiler('cpp')

dependencies = [
  cc.find_library('d3d11', required: true)
]

exe = executable(
  'tangi',
  'tangi.cpp',
  'imgui/imconfig.h',
  'imgui/imgui.cpp',
  'imgui/imgui.h',
  'imgui/imgui_demo.cpp',
  'imgui/imgui_draw.cpp',
  'imgui/imgui_internal.h',
  'imgui/imgui_tables.cpp',
  'imgui/imgui_widgets.cpp',
  'imgui/imstb_rectpack.h',
  'imgui/imstb_textedit.h',
  'imgui/imstb_truetype.h',
  'imgui/imgui_impl_dx11.cpp',
  'imgui/imgui_impl_dx11.h',
  'imgui/imgui_impl_win32.cpp',
  'imgui/imgui_impl_win32.h',
  'miniaudio/miniaudio.c',
  'miniaudio/miniaudio.h',
  'tangi/tangi.hpp',
  'tangi/tangi.cpp',
  install : true,
  dependencies : dependencies,
)

test('basic', exe)
