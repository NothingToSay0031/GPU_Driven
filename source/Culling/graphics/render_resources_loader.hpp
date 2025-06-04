#pragma once

#include "graphics/renderer.hpp"

namespace hydra {

struct FrameGraph;

//
//
struct RenderResourcesLoader {
  void init(hydra::Renderer* renderer, hydra::StackAllocator* temp_allocator,
            hydra::FrameGraph* frame_graph);
  void shutdown();

  GpuTechnique* load_gpu_technique(cstring json_path, bool use_shader_cache);
  TextureResource* load_texture(cstring path, bool generate_mipmaps = true);

  Renderer* renderer;
  FrameGraph* frame_graph;
  StackAllocator* temp_allocator;

};  // struct RenderResourcesLoader

}  // namespace hydra
