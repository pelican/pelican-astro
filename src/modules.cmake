add_subdirectory(data)      # Depends on: nothing.
add_subdirectory(utility)   # Depends on: nothing.

add_subdirectory(adapters)  # Depends on: data.

add_subdirectory(modules)   # Depends on: data, utility.

add_subdirectory(pipelines) # Depends on: data, utility, modules.
