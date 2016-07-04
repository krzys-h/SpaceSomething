set(SOURCE_FILES
    main.cpp
    Game.cpp
    Game.h
    GameResources.cpp
    GameResources.h
    stringutils.h
    objects/Player.cpp
    objects/Player.h
    objects/Enemy.cpp
    objects/Enemy.h
    objects/GameSprite.cpp
    objects/GameSprite.h
    objects/Bullet.cpp
    objects/Bullet.h
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(. ${SFML_INCLUDE_DIR} ${SFGUI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFGUI_LIBRARY})