


#macro(subDirList result curdir)
#    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
#    set(dirlist "")
#    foreach(child ${children})
#        if(IS_DIRECTORY ${curdir}/${child})
#            list(APPEND dirlist ${child})
#        endif()
#    endforeach()
#    set(${result} ${dirlist})
#endmacro()

#subDirList(subDirs .)

#foreach(subDir ${subDirs})
#    add_subdirectory(${subDir})
#endforeach()

add_subdirectory(boating)
add_subdirectory(chart)
add_subdirectory(dashboard)
add_subdirectory(native)
add_subdirectory(web)