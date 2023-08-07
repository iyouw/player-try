add_executable(main
  main.cpp
  Player.cpp
  Packet.cpp
  PacketQueue.cpp
  Frame.cpp
  FrameQueue.cpp
)

# include
set(INCLUDES .)
# libs
set(LINK_LIBS)

# SDL
set(SDL_HOME "C:/Program Files (x86)/SDL2")

# FFmpeg
set(FFMPEG_HOME D:/ffmpeg6.0)

# window os
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  # include
  list(APPEND INCLUDES ${SDL_HOME}/include ${FFMPEG_HOME}/include)
  # libs
  list(APPEND 
    LINK_LIBS 
    ${SDL_HOME}/lib/SDL2.lib 
    ${SDL_HOME}/lib/SDL2main.lib
  )
  
  list(APPEND 
    LINK_LIBS
    ${FFMPEG_HOME}/lib/avutil.lib
    ${FFMPEG_HOME}/lib/avformat.lib 
    ${FFMPEG_HOME}/lib/avcodec.lib
    ${FFMPEG_HOME}/lib/swresample.lib
  )
endif()

# final
target_include_directories(main PUBLIC ${INCLUDES})
target_link_libraries(main ${LINK_LIBS})

# move libs
include(../cmake/copy_target_dep.cmake)
copy_target_dep(
  main
  ${PROJECT_SOURCE_DIR}/lib/SDL2.dll
  ${PROJECT_SOURCE_DIR}/lib/avutil-58.dll
  ${PROJECT_SOURCE_DIR}/lib/swresample-4.dll
  ${PROJECT_SOURCE_DIR}/lib/avformat-60.dll
  ${PROJECT_SOURCE_DIR}/lib/avcodec-60.dll
)