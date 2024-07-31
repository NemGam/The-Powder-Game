add_subdirectory(core)
add_subdirectory(rendering)
add_subdirectory(particles)

target_sources(${PROJECT_NAME} PRIVATE
    brush.cpp
    glad.c
    main.cpp
    particle_creator.cpp
    sim_matrix.cpp
    simulation.cpp
)