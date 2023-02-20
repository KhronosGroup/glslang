####################################################################################################
#
# cmake settings to enable glslang to built directly as part of a 3rd party application or library.
#
# SOURCES var collects together all the required headers and files that need to be compiled
#
set(glslang_PREFIX ${CMAKE_CURRENT_LIST_DIR})


# Root directory for build-time generated include files
set(GLSLANG_GENERATED_INCLUDEDIR "${CMAKE_BINARY_DIR}/include")

################################################################################
# Build version information generation
################################################################################
include(${CMAKE_CURRENT_LIST_DIR}/parse_version.cmake)
set(GLSLANG_CHANGES_FILE      "${glslang_PREFIX}/CHANGES.md")
set(GLSLANG_BUILD_INFO_H_TMPL "${glslang_PREFIX}/build_info.h.tmpl")
set(GLSLANG_BUILD_INFO_H      "${GLSLANG_GENERATED_INCLUDEDIR}/glslang/build_info.h")

parse_version(${GLSLANG_CHANGES_FILE} GLSLANG)

function(configurate_version)
    set(major ${GLSLANG_VERSION_MAJOR})
    set(minor ${GLSLANG_VERSION_MINOR})
    set(patch ${GLSLANG_VERSION_PATCH})
    set(flavor ${GLSLANG_VERSION_FLAVOR})
    configure_file(${GLSLANG_BUILD_INFO_H_TMPL} ${GLSLANG_BUILD_INFO_H} @ONLY)
endfunction()

configurate_version()

################################################################################
# Set up SOURCES var
################################################################################
set(SPIRV_PREFIX "${glslang_PREFIX}/SPIRV")
set(SPIRV_SOURCES
        ${SPIRV_PREFIX}/disassemble.cpp
        ${SPIRV_PREFIX}/doc.cpp
        ${SPIRV_PREFIX}/GlslangToSpv.cpp
        ${SPIRV_PREFIX}/InReadableOrder.cpp
        ${SPIRV_PREFIX}/Logger.cpp
        ${SPIRV_PREFIX}/SpvBuilder.cpp
        ${SPIRV_PREFIX}/SpvPostProcess.cpp
        ${SPIRV_PREFIX}/SPVRemapper.cpp
        ${SPIRV_PREFIX}/SpvTools.cpp
)

set(OGLCompilersDLL_SOURCE ${glslang_PREFIX}/OGLCompilersDLL/InitializeDll.cpp)

# ${BISON_GLSLParser_OUTPUT_SOURCE}

set(GenericCodeGen_PREFIX "${glslang_PREFIX}/glslang/GenericCodeGen")
set(GenericCodeGen_SOURCES
    ${GenericCodeGen_PREFIX}/CodeGen.cpp
    ${GenericCodeGen_PREFIX}/Link.cpp
)

set(MachineIndependent_PREFIX "${glslang_PREFIX}/glslang/MachineIndependent")
set(MACHINEINDEPENDENT_SOURCES
    ${MachineIndependent_PREFIX}/glslang.m4
    ${MachineIndependent_PREFIX}/glslang.y
    ${MachineIndependent_PREFIX}/glslang_tab.cpp
    ${MachineIndependent_PREFIX}/attribute.cpp
    ${MachineIndependent_PREFIX}/Constant.cpp
    ${MachineIndependent_PREFIX}/iomapper.cpp
    ${MachineIndependent_PREFIX}/InfoSink.cpp
    ${MachineIndependent_PREFIX}/Initialize.cpp
    ${MachineIndependent_PREFIX}/IntermTraverse.cpp
    ${MachineIndependent_PREFIX}/Intermediate.cpp
    ${MachineIndependent_PREFIX}/ParseContextBase.cpp
    ${MachineIndependent_PREFIX}/ParseHelper.cpp
    ${MachineIndependent_PREFIX}/PoolAlloc.cpp
    ${MachineIndependent_PREFIX}/RemoveTree.cpp
    ${MachineIndependent_PREFIX}/Scan.cpp
    ${MachineIndependent_PREFIX}/ShaderLang.cpp
    ${MachineIndependent_PREFIX}/SpirvIntrinsics.cpp
    ${MachineIndependent_PREFIX}/SymbolTable.cpp
    ${MachineIndependent_PREFIX}/Versions.cpp
    ${MachineIndependent_PREFIX}/intermOut.cpp
    ${MachineIndependent_PREFIX}/limits.cpp
    ${MachineIndependent_PREFIX}/linkValidate.cpp
    ${MachineIndependent_PREFIX}/parseConst.cpp
    ${MachineIndependent_PREFIX}/reflection.cpp
    ${MachineIndependent_PREFIX}/preprocessor/Pp.cpp
    ${MachineIndependent_PREFIX}/preprocessor/PpAtom.cpp
    ${MachineIndependent_PREFIX}/preprocessor/PpContext.cpp
    ${MachineIndependent_PREFIX}/preprocessor/PpScanner.cpp
    ${MachineIndependent_PREFIX}/preprocessor/PpTokens.cpp
    ${MachineIndependent_PREFIX}/propagateNoContraction.cpp
)

set(MACHINEINDEPENDENT_HEADERS
    ${MachineIndependent_PREFIX}/attribute.h
    ${MachineIndependent_PREFIX}/glslang_tab.cpp.h
    ${MachineIndependent_PREFIX}/gl_types.h
    ${MachineIndependent_PREFIX}/Initialize.h
    ${MachineIndependent_PREFIX}/iomapper.h
    ${MachineIndependent_PREFIX}/LiveTraverser.h
    ${MachineIndependent_PREFIX}/localintermediate.h
    ${MachineIndependent_PREFIX}/ParseHelper.h
    ${MachineIndependent_PREFIX}/reflection.h
    ${MachineIndependent_PREFIX}/RemoveTree.h
    ${MachineIndependent_PREFIX}/Scan.h
    ${MachineIndependent_PREFIX}/ScanContext.h
    ${MachineIndependent_PREFIX}/SymbolTable.h
    ${MachineIndependent_PREFIX}/Versions.h
    ${MachineIndependent_PREFIX}/parseVersions.h
    ${MachineIndependent_PREFIX}/propagateNoContraction.h
    ${MachineIndependent_PREFIX}/preprocessor/PpContext.h
    ${MachineIndependent_PREFIX}/preprocessor/PpTokens.h
)

if(WIN32)
    set(GSDEPENDENT_SOURCE ${glslang_PREFIX}/glslang/OSDependent/Windows/ossource.cpp)
else()
    set(GSDEPENDENT_SOURCE ${glslang_PREFIX}/glslang/OSDependent/Unix/ossource.cpp)
endif()

set(GLSLANG_C_HEADERS
    ${glslang_PREFIX}/glslang/Include/glslang_c_interface.h
    ${glslang_PREFIX}/glslang/Include/glslang_c_shader_types.h
)

set(GLSLANG_C_SOURCES
    ${glslang_PREFIX}/CInterface/glslang_c_interface.cpp
)

set(GLSLANG_HEADERS
    ${glslang_PREFIX}/glslang/Public/ShaderLang.h
    ${glslang_PREFIX}/glslang/Public/ResourceLimits.h
    ${glslang_PREFIX}/glslang/Public/resource_limits_c.h
    ${glslang_PREFIX}/glslang/Include/arrays.h
    ${glslang_PREFIX}/glslang/Include/BaseTypes.h
    ${glslang_PREFIX}/glslang/Include/Common.h
    ${glslang_PREFIX}/glslang/Include/ConstantUnion.h
    ${glslang_PREFIX}/glslang/Include/InfoSink.h
    ${glslang_PREFIX}/glslang/Include/InitializeGlobals.h
    ${glslang_PREFIX}/glslang/Include/intermediate.h
    ${glslang_PREFIX}/glslang/Include/PoolAlloc.h
    ${glslang_PREFIX}/glslang/Include/ResourceLimits.h
    ${glslang_PREFIX}/glslang/Include/ShHandle.h
    ${glslang_PREFIX}/glslang/Include/SpirvIntrinsics.h
    ${glslang_PREFIX}/glslang/Include/Types.h)

set(STANDALONE_SOURCES
    ${glslang_PREFIX}/StandAlone/ResourceLimits.cpp
)

set(SOURCES ${SOURCES}
    ${GenericCodeGen_SOURCES}
    ${MACHINEINDEPENDENT_HEADERS}
    ${MACHINEINDEPENDENT_SOURCES}
    ${GSDEPENDENT_SOURCE}
    ${OGLCompilersDLL_SOURCE}
    ${GLSLANG_HEADERS}
    ${GLSLANG_SOURCES}
    ${STANDALONE_SOURCES}
    ${SPIRV_SOURCES}
)
