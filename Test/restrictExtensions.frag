#version 450

#if defined(GL_KHR_shader_subgroup_ballot)
#extension GL_KHR_shader_subgroup_ballot : enable
#endif

#if defined(GL_EXT_ray_query)
#extension GL_EXT_ray_query : enable
#endif

layout(location = 0) out vec4 color;

void main()
{
#if defined(GL_KHR_shader_subgroup_ballot)
    color = vec4(subgroupBallot(true));
#else
    color = vec4(0.0);
#endif
}
