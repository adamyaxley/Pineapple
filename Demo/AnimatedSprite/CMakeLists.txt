cmake_minimum_required(VERSION 3.0)
project(AnimatedSprite)

glob_source_files(ANIMATEDSPRITE_SOURCES)
create_source_groups(${ANIMATEDSPRITE_SOURCES})

add_pineapple_app(AnimatedSprite ${ANIMATEDSPRITE_SOURCES})