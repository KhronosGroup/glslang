#version 450

#extension GL_GOOGLE_include_directive : require
#include "spv.debuginfo.include.struct.glsl.h"

struct MainStruct {
	float mainMember;
};

layout(binding = 0) uniform UBO {
	HeaderStruct fromHeader;
	MainStruct fromMain;
};

layout(location = 0) out vec4 outColor;

void main() {
	outColor = vec4(fromHeader.headerMember + fromMain.mainMember);
}
