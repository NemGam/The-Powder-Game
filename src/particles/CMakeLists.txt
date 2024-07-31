target_sources(${PROJECT_NAME} PRIVATE
    particle.cpp
    gas/gas_particle.cpp
    gas/air.cpp
    liquid/liquid_particle.cpp
    liquid/water.cpp
    solid/solid_particle.cpp
    solid/immovable/immovable_solid_particle.cpp
    solid/immovable/stone.cpp
    solid/immovable/border_rock.cpp
    solid/movable/movable_solid_particle.cpp
    solid/movable/sand.cpp
)