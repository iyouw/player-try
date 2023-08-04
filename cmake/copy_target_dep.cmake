function(copy_target_dep target)
  add_custom_command(
    TARGET ${target} POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
        ${ARGN}
        ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
  )
endfunction()
